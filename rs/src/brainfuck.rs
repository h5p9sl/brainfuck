pub struct BrainFuck {
    buf: Vec<u8>,
    buf_index: usize,
    loops: Vec<usize>,
}

impl BrainFuck {
    pub fn new(buf_len: usize) -> Self {
        Self {
            buf: Vec::with_capacity(buf_len),
            buf_index: 0,
            loops: Vec::new(),
        }
    }

    // Gets the char at current index
    fn get_char(&self) -> char {
        self.buf[self.buf_index] as char
    }

    // Gets the u8 at current index
    fn get_u8(&self) -> u8 {
        self.buf[self.buf_index]
    }

    pub fn run(&mut self, source: &str) {
        self.buf.clear();
        self.buf.resize(self.buf.capacity(), 0);

        let mut i = 0;
        while i < source.len() {
            let mut c = source.chars().nth(i).unwrap();
            match c {
                '?' => { 
                    print!("{}", self.get_u8());
                }
                '.' => {
                    print!("{}", self.get_char());
                }
                '>' => {
                    self.buf_index += 1;
                }
                '<' => {
                    self.buf_index -= 1;
                }
                '+' => {
                    self.buf[self.buf_index] += 1;
                }
                '-' => {
                    self.buf[self.buf_index] -= 1;
                }
                '[' => {
                    if self.get_u8() == 0 {
                        // Skip over loop
                        let mut ignore = 0;
                        while c != ']' && ignore != 0 {
                            i += 1;
                            c = source.chars().nth(i).unwrap();
                            match c {
                                '[' => ignore += 1,
                                ']' => ignore -= 1,
                                _ => {}
                            }
                        }
                    } else {
                        self.loops.push(i);
                    }
                }
                ']' => {
                    if self.get_u8() != 0 {
                        // Go to start of loop
                        i = self.loops.pop().unwrap() - 1;
                    } else {
                        self.loops.pop();
                    }
                }
                _ => {} // Ignore other characters
            }
            i += 1;
        }
    }
}
