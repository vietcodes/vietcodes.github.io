extern crate cgmath;

use cgmath::Vector2;
use cgmath::vec2;
use cgmath::prelude::*;

fn f(a: &[Vector2<f64>], x: &Vector2<f64>) -> f64 {
    a.iter().map(|u| (x - u).magnitude()).sum()
}
fn gradient(a: &[Vector2<f64>], x: &Vector2<f64>) -> Vector2<f64> {
    a.iter().map(|u| (x - u).normalize()).sum()
}

fn compute(a: &[Vector2<f64>]) -> f64 {
    let epsilon = 1e-7;
    let mut gamma = 0.01;
    let mut x1 = a.iter().sum();
    x1 /= a.len() as f64;
    let mut f1 = f(a, &x1);
    let mut g1 = gradient(a, &x1);
    loop {
        let x0 = x1;
        let f0 = f1;
        let g0 = g1;
        x1 -= g1 * gamma;
        f1 = f(a, &x1);
        g1 = gradient(a, &x1);
        gamma = (x1 - x0).dot(g1 - g0) / (g1 - g0).magnitude2();
        if f64::abs(f1 - f0) <= epsilon {
            break;
        }
    }
    f1
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let a = s.lines().skip(1).map(|s| {
        let mut a = s.split_whitespace();
        vec2(a.next().unwrap().parse::<f64>().unwrap(), a.next().unwrap().parse::<f64>().unwrap())
    }).collect::<Vec<_>>();
    println!("{}", compute(&a));
}
