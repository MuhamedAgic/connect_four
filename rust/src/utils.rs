
use std::io::{stdin, stdout, Write};

pub fn get_cli_input<R>(mut reader: R) -> String where R: std::io::BufRead {
    std::io::stdout().flush().unwrap();
    let mut input = String::new();
    reader.read_line(&mut input).expect("Failed to read input");
    input
}

pub fn cli_confirms<R>(mut reader: R) -> bool where R: std::io::BufRead {
    loop {
        let input = get_cli_input(&mut reader).trim().to_lowercase();
        match input.as_str() {
            "y" | "yes" => return true,
            "n" | "no" => return false,
            _ => println!("Please enter 'y' or 'n'."),
        }
    }
}


#[cfg(test)]
mod utils_tests {
    use std::io::Cursor;
    use super::*;

    #[test]
    fn get_cli_input_test() {
        let input = b"y\n";
        let result = get_cli_input(Cursor::new(&input[..]));
        assert_eq!(result.as_bytes(), input);
    }

    #[test]
    fn cli_confirms_positive_test() {
        let input = b"y\n";
        let result = cli_confirms(Cursor::new(&input[..]));
        assert_eq!(result, true);
    }

    #[test]
    fn cli_confirms_negative_test() {
        let input = b"n\n";
        let result = cli_confirms(Cursor::new(&input[..]));
        assert_eq!(result, false);
    }
}
