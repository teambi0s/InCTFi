use std::process;
use std::env;
use std::fs;

pub enum Opcode {
    Appu,
    Daun,
    Hidari,
    Tadashi,
    Yamete
}

impl From<u8> for Opcode {
    fn from(byte: u8) -> Self {
        match byte {
            106 => Opcode::Appu,
            107 => Opcode::Daun,
            104 => Opcode::Hidari,
            108 => Opcode::Tadashi,
            _ => Opcode::Yamete
        }
    }
}

pub struct Kikai {
    pub movs: usize,
    counter: usize,
    miz : [[usize; 25]; 25],
    pub cursx: usize,
    pub cursy: usize
}

impl Kikai {
    pub fn new() -> Kikai {
        Kikai {
            movs : 10,
            counter : 0,
            miz : [[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
            ,[1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1]
            ,[1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1]
            ,[1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1]
            ,[1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1]
            ,[1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1]
            ,[1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1]
            ,[1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1]
            ,[1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1]
            ,[1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1]
            ,[1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1]
            ,[1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1]
            ,[1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1]
            ,[1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1]
            ,[1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1]
            ,[1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1]
            ,[1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1]
            ,[1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1]
            ,[1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1]
            ,[1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1]
            ,[1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1]
            ,[1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1]
            ,[1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1]
            ,[1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1]
            ,[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1]],
            cursx: 1,
            cursy: 13
        }
    }   
    fn Furagu_o_toru(&self){
        let contents = fs::read_to_string("flag").expect("Yamete");
        println!("hehe {}", contents);
        process::exit(0x0100);
    }
    
    pub fn Dekodo_ido(&mut self,Shiji: &mut Vec<u8>) -> Opcode{
        if self.counter == Shiji.len(){
            process::exit(0x0100);
        }
        let Meirei = Opcode::from(Shiji[self.counter]);
        self.counter = self.counter + 1;
        Meirei
    }
    pub fn Jikko_suru(&mut self,Shiji: &mut Vec<u8>) -> bool{
        match self.Dekodo_ido(Shiji){
            Opcode::Appu => {
                let sexx: usize = self.cursx;
                let sexy: usize = self.cursy;
                if (sexx == 0){
                    process::exit(0x0100);

                }
                if (self.miz[sexx-1][sexy] == 0){
                    self.cursx = sexx - 1;
                }
                else{
                    if(self.miz[sexx-1][sexy] == 2)
                    {
                        self.Furagu_o_toru();
                    }
                    process::exit(0x0100); 
                }
            },
            Opcode::Daun => {
                let sexx = self.cursx;
                let sexy = self.cursy;
                if (sexx == 24){
                    process::exit(0x0100);
                }
                if self.miz[sexx+1][sexy] == 0{
                    self.cursx = sexx + 1;
                }
                else{
                    if self.miz[sexx+1][sexy] == 2{
                        self.Furagu_o_toru();
                    }
                    process::exit(0x0100); 
                }
            },
            Opcode::Hidari => {
                let sexx = self.cursx;
                let sexy = self.cursy;
                if (sexy == 0){
                    process::exit(0x0100);
                }
                if self.miz[sexx][sexy-1] == 0{
                    self.cursy = sexy - 1;
                }
                else{
                    if self.miz[sexx][sexy-1] == 2{
                        self.Furagu_o_toru();
                    }
                    process::exit(0x0100); 
                }
            },
            Opcode::Tadashi => {
                let sexx = self.cursx;
                let sexy = self.cursy;
                
                if (sexy == 24){
                    process::exit(0x0100);
                }
                if self.miz[sexx][sexy] == 0{
                    self.cursy = sexy + 1;
                }
                else{
                    if self.miz[sexx][sexy] == 2{
                        self.Furagu_o_toru();
                    }
                    process::exit(0x0100); 
                }
            },
            Opcode::Yamete => {
            },
            _ => {
                println!("Yamete something is really wrong here");
            }
        }
        true
    }
    pub fn run(&mut self,Shiji: &mut Vec<u8>) {
        let mut fuck = true;
        while fuck {
            fuck = self.Jikko_suru(Shiji);
        }
    }
}