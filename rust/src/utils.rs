
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
        let input_y = b"y\n";
        let result_y = cli_confirms(Cursor::new(&input_y[..]));

        let input_yes = b"yes\n";
        let result_yes = cli_confirms(Cursor::new(&input_yes[..]));
        
        assert_eq!(result_y, true);
        assert_eq!(result_yes, true);
    }

    #[test]
    fn cli_confirms_negative_test() {
        let input_n = b"n\n";
        let result_n = cli_confirms(Cursor::new(&input_n[..]));
        
        let input_no = b"no\n";
        let result_no = cli_confirms(Cursor::new(&input_no[..]));
        
        assert_eq!(result_n, false);
        assert_eq!(result_no, false);
    }
}
