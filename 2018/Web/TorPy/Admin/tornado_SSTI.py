import tornado.template
import tornado.ioloop
import tornado.web

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        name = self.get_argument('name', '')
        if(name=="index.html"):
        	template_data = open("index.html").read()
        	t = tornado.template.Template(template_data)
        	self.write(t.generate(name=name))
        else:
        	blacklist=['import','os','class','subclasses','mro','request','args','eval','if','for','%','subprocess','file','open','popen','builtins','+','compile','execfile','getattr',']','[','from_pyfile','tornado','config','app']
        	flag=0
        	for i in blacklist:
        		if i in name:
        			flag=1
        			break
        	if(flag==1):
        		template_data = open("index.html").read().replace("index.html","Sorry, but some keywords are blacklisted in your payload!!!")
		        t = tornado.template.Template(template_data)
		        self.write(t.generate(name=name))
        	else:
        		if(name.count("{")>2 or name.count("}")>2):
        			template_data = open("index.html").read().replace("index.html","you can only use two '{' and two '}'")
        			t = tornado.template.Template(template_data)
		        	self.write(t.generate(name=name))
		        else:
			        template_data = open("index.html").read().replace("index.html",name)
			        t = tornado.template.Template(template_data)
			        self.write(t.generate(name=name))

application = tornado.web.Application([
    (r"/", MainHandler),
], debug=False, static_path=None, template_path=None)

if __name__ == '__main__':
    application.listen(8000)
    tornado.ioloop.IOLoop.instance().start()
