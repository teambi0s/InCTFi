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
            119 => Opcode::Appu,
            115 => Opcode::Daun,
            97 => Opcode::Hidari,
            100 => Opcode::Tadashi,
            _ => Opcode::Yamete
        }
    }
}