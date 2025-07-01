class Cache {
    constructor(server) {
        this.server = server;
        this.version = "voj-status-0";
    }

    save_problems(range, problems) {
        if (localStorage === undefined) return;
        let key = this.version + "." + range;
        localStorage[key] = JSON.stringify({
            expire_time: new Date().getTime() + 3 * 60 * 1000,
            data: problems,
        });
    }

    async problems(range) {
        return this._do_generic_caching_stuffs(range, async () => {
            return this._fetch_problems(range);
        });
    }

    async solutions() {
        return this._do_generic_caching_stuffs("solutions", async () => {
            return (await fetch("/code/voj.json")).json();
        });
    }

    async _do_generic_caching_stuffs(name, fetch_resource) {
        if (localStorage === undefined) return fetch_resource();
        let key = this.version + "." + name;
        let cache = null;
        if (key in localStorage) {
            cache = JSON.parse(localStorage[key]);
            if (new Date().getTime() >= cache.expire_time) cache = null;
        }
        if (cache === null) {
            let data = await fetch_resource();
            cache = {
                expire_time: new Date().getTime() + 3 * 60 * 1000,
                data,
            };
            localStorage[key] = JSON.stringify(cache);
        }
        return cache.data;
    }

    async _fetch_problems(range) {
        let url = this.server + "/" + range;
        return (await fetch(url)).json();
    }
}

function sort(problems, view) {
    let field = view.order.field;
    let sorter = view.order.sorter[field];
    let with_index = problems.map((p, i) => ({ data: p, index: i }));
    let mul = view.order.orientation === "desc" ? -1 : 1;
    with_index.sort((a, b) => {
        let ret = mul * sorter(a.data[field], b.data[field]);
        if (ret == 0) return a.index - b.index;
        else return ret;
    });
    return with_index.map(d => d.data);
}

function paginate(problems, view) {
    let start = view.page * view.page_size;
    return problems.slice(start, start + view.page_size);
}

function search(problems, view) {
    let pattern = view.searchText.toLocaleLowerCase();
    return problems.filter(p => p.title.toLocaleLowerCase().includes(pattern) || p.problem_id.toLocaleLowerCase().includes(pattern));
}

function compute_max_page(problems, view) {
    let p = Math.floor(problems.length / view.page_size);
    // Page start from 0
    return problems.length % view.page_size === 0 ? p - 1 : p;
}

function add_solution(problems, solutions) {
    let solmap = {};
    solutions.forEach(sol => {
        solmap[sol.problem] = sol.link;
    });
    return problems.map(p => {
        let sol = solmap[p.problem_id];
        let sols = sol === undefined ? [] : [sol];
        p.solutions = sols;
        return p;
    });
}

function add_hidden(problems, hidden) {
    return problems.map(p => {
        p.hidden = p.problem_id in hidden;
        return p;
    });
}

function filter_hidden(problems, view) {
    if (view.showHidden) {
        return problems;
    } else {
        return problems.filter(p => !p.hidden);
    }
}

class Database {
    constructor(server) {
        this.cache = new Cache(server);
    }

    async render(view) {
        let [problems, solutions] = await Promise.all([
            this.cache.problems(view.range),
            this.cache.solutions(),
        ]);

        let max_page = compute_max_page(problems, view);

        problems = add_solution(problems, solutions);
        problems = add_hidden(problems, this.getHiddenProblems());
        problems = sort(problems, view);
        this.cache.save_problems(view.range, problems);
        problems = search(problems, view);
        problems = filter_hidden(problems, view);
        problems = paginate(problems, view);

        return { data: problems, max_page };
    }

    toggleHidden(problem_id) {
        let key = "voj-status-0.hidden_problems";
        if (!(key in localStorage)) {
            localStorage[key] = JSON.stringify({});
        }
        let hidden = JSON.parse(localStorage[key]);
        if (problem_id in hidden) {
            delete hidden[problem_id];
        } else {
            hidden[problem_id] = 1;
        }
        localStorage[key] = JSON.stringify(hidden);
    }

    getHiddenProblems() {
        let key = "voj-status-0.hidden_problems";
        if (!(key in localStorage)) {
            localStorage[key] = JSON.stringify({});
        }
        return JSON.parse(localStorage[key]);
    }
}