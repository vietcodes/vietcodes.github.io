const M: usize = 1000001;

fn sieve(a: Vec<usize>) -> Vec<usize> {
    let mut in_a = Vec::with_capacity(M);
    in_a.resize(M, false);
    for x in a {
        in_a[x] = true;
    }
    let mut res = Vec::with_capacity(M);
    res.resize(M, 0usize);
    for x in 1..M {
        let mut j = i;
        while j < M {
            if in_a[j] {
                res[i] = j;
            }
            j += i;
        }
    }
    res
}

fn main() {
    use std::io::stdin;
    use std::io::Read;
    let (a, b) = {
        let mut inp = String::new();    
        stdin().read_to_string(&mut inp).unwrap();
        let mut a: Vec<_> = inp.split_whitespace().skip(1).collect();
        let n = a.len();
        let b = a.split_off(n / 2);
        (a.into_iter().map(|s| s.parse::<usize>().unwrap()).collect::<Vec<_>>(),
         b.into_iter().map(|s| s.parse::<usize>().unwrap()).collect::<Vec<_>>())
    };
    let a = sieve(a);
    let b = sieve(b);
    for (x, y) in a.into_iter().zip(b.into_iter()).rev() {
        if x > 0 && y > 0 {
            println!("{}", x + y);
            break;
        }
    }
}
