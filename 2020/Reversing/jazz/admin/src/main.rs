use mersenne_twister::MersenneTwister;
use rand::{Rng, SeedableRng};
use std::env;

use crypto::{ symmetriccipher, buffer, aes, blockmodes };
use crypto::buffer::{ ReadBuffer, WriteBuffer, BufferResult };

fn encrypt(data: &[u8], key: &[u8], iv: &[u8]) -> Result<Vec<u8>, symmetriccipher::SymmetricCipherError> {
    let mut encryptor = aes::cbc_encryptor(
            aes::KeySize::KeySize256,
            key,
            iv,
            blockmodes::PkcsPadding);

    let mut final_result = Vec::<u8>::new();
    let mut read_buffer = buffer::RefReadBuffer::new(data);
    let mut buffer = [0; 4096];
    let mut write_buffer = buffer::RefWriteBuffer::new(&mut buffer);

    loop {
        let result = encryptor.encrypt(&mut read_buffer, &mut write_buffer, true)?;

        final_result.extend(write_buffer.take_read_buffer().take_remaining().iter().map(|&i| i));

        match result {
            BufferResult::BufferUnderflow => break,
            BufferResult::BufferOverflow => { }
        }
    }

    Ok(final_result)
}


fn main () {
    let seed: u64 = 0xdeadbeefcafebabe; // Key replace later
    // Create the default RNG.
    let mut rng: MersenneTwister = SeedableRng::from_seed(seed);

    let mut ascii: Vec<u8> = Vec::new();

    let mut random_lists: Vec<Vec<u8>> = Vec::new();
    // start grabbing randomness from rng...

    let args: Vec<String> = env::args().collect();

    println!("Night and stars above that shine so bright ...");

    if args.len() < 2 {
        println!("Please say something ...");
        return
    }

    for i in 0..=255 {
        ascii.push(i);
    }

    // let ascii_original = ascii.clone();

    let no_of_lists = 37;

    for _ in 0..no_of_lists { // Number of tables
        rng.shuffle(&mut ascii);
        random_lists.push(ascii.clone());
    }

    let input: Vec<u8> = Vec::from(args[1].as_bytes());

    let mut final_output: Vec<u8> = Vec::new();

    for i in 0..input.len() {
        final_output.push(random_lists[i%no_of_lists][input[i] as usize]);
    }

    // println!("Advanced Super Secure Cipher Complete ...");

    let mut key: [u8; 32] = [0; 32];
    let mut iv: [u8; 16] = [0; 16];

    rng.fill_bytes(&mut key);
    rng.fill_bytes(&mut iv);

    // println!("{:?}", key);
    // println!("{:?}", iv);
    // println!("{:?}", encrypt(&final_output[..], &key, &iv).ok().unwrap());

    let flag = vec![188, 192, 10, 188, 94, 249, 182, 213, 197, 8, 77, 177, 85, 9,
                    52, 149, 18, 206, 103, 8, 251, 138, 241, 210, 26, 216, 43,
                    100, 40, 194, 57, 114, 180, 66, 104, 122, 56, 35, 207, 4, 144,
                    52, 152, 225, 232, 176, 12, 105, 29, 34, 185, 97, 31, 23, 42,
                    93, 225, 255, 92, 125, 49, 190, 26, 107, 215, 31, 162, 67, 24,
                    171, 204, 87, 208, 141, 95, 204, 67, 44, 67, 105, 150, 236,
                    206, 120, 169, 6, 221, 142, 17, 161, 254, 202, 52, 11, 144,
                    203];

    // println!("Comparing with flag now ...");

    if encrypt(&final_output[..], &key, &iv).ok().unwrap() == flag {
        println!("You got it!");
    } else {
        println!("Nope")
    }
}
