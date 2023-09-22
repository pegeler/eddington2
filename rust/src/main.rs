use std::collections::HashMap;
use std::fs::File;
use std::io::Read;
use structopt::StructOpt;

#[derive(StructOpt)]
struct Cli {
    #[structopt(short, long)]
    cumulative: bool,
    #[structopt(parse(from_os_str))]
    file: std::path::PathBuf
}

#[derive(Default)]
struct Eddington {
    current: i32,
    above: i32,
    cumulative: Vec<i32>,
    hashmap: HashMap<i32, i32>
}

impl Eddington {
    pub fn update(mut self, rides: &Vec<i32>) -> Self {
        for ride in rides {
            if ride > &self.current {
                self.above += 1;
                if (ride.to_owned() as usize) < rides.len() {
                    *self.hashmap.entry(ride.to_owned()).or_default() += 1;
                }

                if &self.above > &self.current {
                    self.current += 1;
                    match self.hashmap.get(&self.current) {
                        Some(v) => self.above -= v,
                        _ => ()
                    }
                }
            }
            self.cumulative.push(ride.to_owned())
        }
        self
    }
}

fn get_rides(path: &std::path::PathBuf) -> std::io::Result<Vec<f64>> {
    let mut data = Vec::<f64>::new();
    let mut buffer = String::new();
    File::open(path)?.read_to_string(&mut buffer)?;

    for line in buffer.lines() {
        match line.trim().parse() {
            Ok(f) => data.push(f),
            Err(_) => eprintln!("Error parsing line")
        }
    }
    Ok(data)
}

fn main() {
    let args = Cli::from_args();
    let rides = match get_rides(&args.file) {
        Ok(rides) => rides.into_iter().map(|x| x as i32).collect::<Vec<_>>(),
        Err(_) => panic!("Error parsing file")
    };
    let e: Eddington = Default::default();
    if args.cumulative {
        println!("{:?}", e.update(&rides).cumulative);
    } else {
        println!("{}", e.update(&rides).current);
    }
}
