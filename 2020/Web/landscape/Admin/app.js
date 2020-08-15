const {NodeVM} = require('vm2');
const express = require('express');
const app = express();
const vm = new NodeVM();

const error = "You are a n00b aren't you? I SAID NO HACKING"

app.use(express.static('public'));

app.get('/', function (req, res) {
    res.sendFile( __dirname + "/" + "index.html" );
});

app.get('/run',function(req,res){
    var code = req.query.code;
    if(typeof(code)==='object'){
	res.send("Nope, not that easy");
        return;
    }
    try{
        if(!code) {
	    console.log("oops this is wrong");
            res.sendFile( __dirname + "/" + "index.html" );
            return;
        }
  
        const blacklists = ['for', 'while', 'exec', 'eval','spawn', 'prototype', 'child', '+', '`','$'];
      
        if(blacklists.map(v=>code.includes(v)).filter(v=>v).length !== 0) {
            res.send(error);
            return;
        }
        
        var result = vm.run(code);
        res.send(result);
    } catch(ex) {
        res.send(ex.toString());
        console.log('it\'s here')
    }
});


const server = app.listen(1337,()=>{
    const host = server.address().address;
    const port = server.address().port;
    console.log("app is running on 'http://"+host+"/"+port+"'");
});

