pub trait Summary {
    fn summarize(&self) -> String {
        String::from("(Read more...)")
    }
}

fn hehe<T>(a: T) -> String
where
    T: Summary,
{
    a.summarize()
}

fn doit<T: Summary>(a: T) -> String {
    a.summarize()
}

struct Tweet {
    tw: String,
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}", self.tw)
    }
}
fn returns_summarizable() -> impl Summary {
    Tweet {
        tw: "hehehe".to_string(),
    }
}

fn main() {
    let v = returns_summarizable();
    println!("{}", doit(v));
}
