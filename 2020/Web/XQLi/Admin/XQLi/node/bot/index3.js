const puppeteer = require('puppeteer');
const mysql = require('mysql2/promise');

const pool = mysql.createPool({
    host: 'db',
    user: 'root',
    database: 'URL',
    password: 'star7ricks',
    waitForConnections: true,
    connectionLimit: 10,
    queueLimit: 0
});

async function run(id) {
    return new Promise(async function(resolve, reject) {
            console.log(id);
            while (true){
                const number = await pool.query("select count(*) as aaa from www");
                // console.log(number[0][0].aaa);
                if (id<=(number[0][0].aaa-1)){
                    break
                }
            }
            // console.log("doneee");
            const result = await pool.query('SELECT * from www limit  ? ,1', [id]);
            // console.log("result[0]=>"+result[0][0].value);
        
            resolve(result[0][0].value);
    });
}


async function url_visit (url) {
    var quote;
    return new Promise(async function(resolve, reject) {
        // console.log(url);
        const browser = await puppeteer.launch({ args: ['--no-sandbox'] });
        const page = await browser.newPage();
        await page.setDefaultNavigationTimeout(1000);
        // await page.setCookie(cookie);
        await page.goto("http://web/").then(()=>{
            page.evaluate(()=>document.cookie = 'whoami=I_ez_administrator_s_assistant; path=/');  
        });
        await page.reload();
        try{
            // await page.goto(url);
            // await page.screenshot({path: 'screenshot.png'});
            var result = await page.goto(url);
            // var y = (await result.text());
        }
        catch(e){
            console.log("timeout exceeded");
        }
        await browser.close();
        resolve(quote);
    });
}



async function rn(){
    var z = 3;
    while(true){
        a = await run(z);
        console.log("return value=>"+a);
        q = await url_visit(a);
        z+=5;
    }
}


rn()
