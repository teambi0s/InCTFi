pub mod bacharu;
use bacharu::Kikai;
use std;

fn main() {
    let mut prog = Kikai::new();
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).expect("input");
    
    let mut shij: Vec<u8> = line.as_bytes().to_vec();
    prog.run(&mut shij);
}