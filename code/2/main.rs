use std::cmp::max;

struct Interval {
    l: i64,
    r: i64,
}

impl Interval {
    fn new(l: i64, r: i64) -> Interval {
        Interval { l: l, r: r }
    }
    fn inside(&self, a: &Interval) -> bool {
        a.l <= self.l && self.r <= a.r
    }
    fn intersect(&self, a: &Interval) -> bool {
        !(a.r < self.l || self.r < a.l)
    }
    fn mid(&self) -> i64 {
        self.l + (self.r - self.l) / 2
    }
}

struct Node {
    range: Interval,
    value: i64,
    lazy: i64,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

impl Node {
    fn new(range: Interval) -> Node {
        Node {
            range: range,
            value: 0,
            lazy: 0,
            left: None,
            right: None,
        }
    }
    fn update(&mut self, q: &Interval, value: i64) {
        if !self.range.intersect(&q) {
            return;
        }
        if self.range.inside(&q) {
            self.value += value;
            self.lazy += value;
        } else if self.range.l < self.range.r {
            if self.left.is_none() || self.right.is_none() {
                let mid = self.range.mid();
                self.left = Some(Box::new(Node::new(Interval::new(self.range.l, mid))));
                self.right = Some(Box::new(Node::new(Interval::new(mid + 1, self.range.r))));
            }
            self.lazy_down();
            self.value = {
                let (left, right) = self.get_child();
                left.update(&q, value);
                right.update(&q, value);
                max(left.value, right.value)
            }
        }
    }
    fn get_child(&mut self) -> (&mut Node, &mut Node) {
        (self.left.as_mut().unwrap(), self.right.as_mut().unwrap())
    }
    fn get(&mut self, q: &Interval) -> i64 {
        if !self.range.intersect(&q) {
            std::i64::MIN
        } else if self.range.inside(&q) {
            self.value
        } else {
            self.lazy_down();
            let (left, right) = self.get_child();
            max(left.get(&q), right.get(&q))
        }
    }
    fn lazy_down(&mut self) {
        {
            let t = self.lazy;
            let (left, right) = self.get_child();
            left.value += t;
            left.lazy += t;
            right.value += t;
            right.lazy += t;
        }
        self.lazy = 0;
    }
}

fn main() {
    use std::io::stdin as inp;

    let (n, m) = {
        let mut text = String::new();
        inp().read_line(&mut text).unwrap();
        let mut i = text.split_whitespace();
        (i.next().unwrap().parse::<i64>().unwrap(), i.next().unwrap().parse::<usize>().unwrap())
    };

    let mut tree = Node::new(Interval::new(1, n));
    for _ in 0..m {
        let (l, r, k) = {
            let mut text = String::new();
            inp().read_line(&mut text).unwrap();
            let mut i = text.split_whitespace().map(|x| x.parse::<i64>().unwrap());
            (i.next().unwrap(), i.next().unwrap(), i.next().unwrap())
        };
        tree.update(&Interval::new(l, r), k);
    }
    println!("{}", tree.get(&Interval::new(1, n)));
}

