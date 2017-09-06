const B: u64 = 1000000000; // Base
const SIZE: usize = 9; // Digit size
const M: [u64; SIZE] = [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000];

fn alloc(n: usize) -> Vec<u64> {
    let mut r = Vec::with_capacity(n);
    r.resize(n, 0);
    r
}

// x += a * b
fn mul(x: &mut [u64], a: &[u64], b: u64) {
    let mut rem = 0;
    for (x, a) in x.iter_mut().zip(a.iter()) {
        rem += *a * b + *x;
        *x = rem % B;
        rem /= B;
    }
    for x in x.iter_mut().skip(a.len()) {
        if rem == 0 {
            break;
        }
        rem += *x;
        *x = rem % B;
        rem /= B;
    }
}

// a -= b
fn sub(a: &mut [u64], b: &[u64]) {
    let mut rem = 0i64;
    for (a, b) in a.iter_mut().zip(b.iter()) {
        rem += *a as i64 - *b as i64;
        if rem < 0 {
            *a = (rem + B as i64) as u64;
            rem = -1;
        } else {
            *a = rem as u64;
            rem = 0;
        }
    }
    for a in a.iter_mut().skip(b.len()) {
        if rem == 0 {
            break;
        }
        rem += *a as i64;
        if rem < 0 {
            *a = (rem + B as i64) as u64;
            rem = -1;
        } else {
            *a = rem as u64;
            rem = 0;
        }
    }
}

// a += b
fn sum(a: &mut [u64], b: &[u64]) {
    let mut rem = 0;
    for (a, b) in a.iter_mut().zip(b.iter()) {
        rem += *a + *b;
        if rem > B {
            *a = rem - B;
            rem = 1;
        } else {
            *a = rem;
            rem = 0;
        }
    }
    for a in a.iter_mut().skip(b.len()) {
        if rem == 0 {
            break;
        }
        rem += *a;
        if rem > B {
            *a = rem - B;
            rem = 1;
        } else {
            *a = rem;
            rem = 0;
        }
    }
}

// remove leading zeroes
fn shift(a: &mut Vec<u64>) {
    let n = a.len() - a.iter().rev().take_while(|&x| *x == 0).count();
    a.truncate(n);
}

// compute `m` in the formula bellow
fn split_size(a: usize, b: usize) -> usize {
    let r = std::cmp::min(a, b) / 2;
    if a - r == r || b - r == r {
        r - 1
    } else {
        r
    }
}

// xy = (B^2m + b^m)x1y1 + (b + 1)x0y0 - b(x1 - x0)(y1 - y0)
// With:
// x1*B^m + x0 = x
// y1*B^m + y0 = y
// x1 > x0
// y1 > y0
fn karatsuba(mut x: Vec<u64>, mut y: Vec<u64>) -> Vec<u64> {
    if x.is_empty() || y.is_empty() {
        return Vec::new();
    }
    if x.len() <= 16 {
        std::mem::swap(&mut x, &mut y);
    }
    if y.len() <= 16 {
        // perform single digit multiplications
        let mut r = alloc(x.len() + y.len());
        for (i, y) in y.into_iter().enumerate() {
            mul(&mut r[i..], &x, y);
        }
        shift(&mut r);
        return r;
    }
    let m = split_size(x.len(), y.len());
    let size = x.len() + y.len();
    let x1 = x.split_off(m);
    let y1 = y.split_off(m);
    shift(&mut x);
    shift(&mut y);
    let mut sx = x1.clone();
    let mut sy = y1.clone();
    sub(&mut sx, &x);
    shift(&mut sx);
    sub(&mut sy, &y);
    shift(&mut sy);
    let xy0 = karatsuba(x, y);
    let xy1 = karatsuba(x1, y1);
    let xy = karatsuba(sx, sy);
    let mut r = alloc(size);
    sum(&mut r, &xy0);
    sum(&mut r[m..], &xy0);
    sum(&mut r[m..], &xy1);
    sum(&mut r[2*m..], &xy1);
    sub(&mut r[m..], &xy);
    shift(&mut r);
    r
}

// Read big-number from string
fn read(s: &[u8]) -> Vec<u64> {
    let size = if s.len() % SIZE == 0 { s.len() / SIZE }
    else { s.len() / SIZE + 1};
    let mut r = alloc(size);
    let mut s = s.iter().rev();
    for x in &mut r {
        for i in &M {
            *x += i * (s.next().unwrap_or(&48) - 48) as u64;
        }
    }
    shift(&mut r);
    r
}

// Append big-number to string
fn push(s: &mut String, a: &[u64]) {
    if a.is_empty() {
        *s += "0";
    } else {
        *s += &format!("{}", a.last().unwrap());
        for a in a.iter().rev().skip(1) {
            *s += &format!("{:09}", *a);
        }
    }
    *s += "\n";
}

fn main() {
    // Read pairs of numbers and multiply them
    let mut s = String::new();
    use std::io::Read;
    let _ = std::io::stdin().read_to_string(&mut s);
    let mut i = s.split_whitespace();
    let m = read(i.next().unwrap().as_bytes())[0] as usize;
    let mut out = String::new();
    for _ in 0..m {
        let a = read(i.next().unwrap().as_bytes());
        let b = read(i.next().unwrap().as_bytes());
        push(&mut out, &karatsuba(a, b));
    }
    print!("{}", out);
}
