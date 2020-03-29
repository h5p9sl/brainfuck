use std::fs::File;

mod brainfuck;
use brainfuck::BrainFuck;

fn load_file(file_path: &String) -> Option<String> {
    use std::io::Read;
    let mut buf = String::new();
    if let Some(mut file) = File::open(file_path).ok() {
        file.read_to_string(&mut buf).ok();
        return Some(buf);
    }
    None
}

fn main() {
    let mut argv = std::env::args();
    if argv.len() <= 1 {
        if let Some(exec) = argv.nth(0) {
            println!("Usage: {} <bf file>", exec);
            return;
        }
    }

    let bf_file = argv.nth(1).unwrap();

    let mut bf = BrainFuck::new(30*1000, false);
    if let Some(file) = load_file(&bf_file) {
        bf.run(&file);
    } else {
        eprintln!("Unable to open file {}...", bf_file);
    }
}
