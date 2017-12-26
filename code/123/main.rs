struct Graph {
    ke: Vec<Vec<usize>>,
    cha: Vec<usize>,
}
 
impl Graph {
    fn new(n: usize) -> Graph {
        let mut ke = Vec::new();
        ke.resize(n+1, Vec::new());
        let mut cha = Vec::new();
        cha.resize(n+1, 0);
        Graph {
            ke: ke,
            cha: cha,
        }
    }
 
    fn add_edge(&mut self, u: usize, v: usize) {
        self.ke[u].push(v);
        self.ke[v].push(u);
    }
 
    fn bfs(&mut self, s: usize) -> usize {
        if self.cha[s] != 0 {
            return 0;
        }
        use std::collections::VecDeque;
        let mut queue: VecDeque<usize> = VecDeque::new();
        let mut cnt = 0;
        queue.push_back(s);
        while !queue.is_empty() {
            let u = queue.pop_front().unwrap();
            for v in &self.ke[u] {
                if self.cha[u] != *v {
                    self.cha[*v] = u;
                    queue.push_back(*v);
                    let tmp = if u == s {
                        self.ke[*v].len()-1
                    } else {
                        self.ke[*v].len()
                    };
                    if self.ke[u].len() < tmp { cnt += 1; }
                }
            }
        }
        cnt
    }
}
 
fn main() {
    let mut input = String::new();
    use std::io::Read;
    std::io::stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_whitespace();
    let mut next = || iter.next().unwrap().parse::<usize>().unwrap();
 
    let n = next();
    let mut g = Graph::new(n);
    let m = next();
    for _ in 0..m {
        g.add_edge(next(), next());
    }
    let mut res = 0;
    for i in 1..n+1 {
        res += g.bfs(i);
    }
    println!("{}", res);
}
