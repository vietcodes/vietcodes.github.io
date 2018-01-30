function Database(server) {
    this.server = server;
    this.cache = {};
    this.today = null;
    this.todayId = 0;
}

Database.prototype.fetchTodayId = function() {
    var I = this;
    if (this.todayId !== 0) return Promise.resolve();
    else return axios.get(this.server + "/today_id").then(function(resp) {
        I.todayId = parseInt(resp.data);
    });
}

function fetchMissedCaches(list, server) {
    return Promise.all(list.map(function(id) {
        return axios.get(server + "/past/" + id).then(function(resp) {
            if (resp.data.length === 0) return [];
            else return JSON.parse(resp.data[0].data);
        });
    }));
}

Database.prototype.fetchToday = function() {
    var I = this;
    return axios.get(this.server + "/today").then(function(resp) {
        I.today = resp.data;
    });
}

function htmlDecode(text) {
    var ta = document.createElement("textarea");
    ta.innerHTML = text;
    return ta.value;
}

function origin(link) {
    if (link.startsWith("vn.spoj.com")) return "VOJ";
    if (link.startsWith("ntucoder.net")) return "NTUCoder";
    return "";
}

function getVOJProblemCode(link) {
    var re = /\/problems\/([^\/]*)$/;
    return re.exec(link)[1];
}

function transform(data) {
    return data.map(function(x) {
        x.origin = origin(x.link);
        x.title = htmlDecode(x.title);
        if (x.origin === "VOJ") x.title = getVOJProblemCode(x.link) + " - " + x.title;
        x.link = "http://" + x.link;
        return x;
    })
}

function match(text, regex) {
    try {
        return text.match(new RegExp(regex, "i"));
    } catch(error) {
        return text.includes(regex);
    }
}

Database.prototype.render = function(viewConfig) {
    var I = this;
    return this.fetchTodayId().then(function() {
        if (I.today) return Promise.resolve(I.today);
        else return I.fetchToday();
    }).then(function() {
        var missed = [];

        for (var i = 1; i < viewConfig.range; i++) if (!I.cache[I.todayId - i]) {
            var id = I.todayId - i;
            if (typeof(Storage) !== "undefined" && localStorage.getItem("day." + id)) {
                I.cache[id] = JSON.parse(localStorage.getItem("day." + id));
            } else {
                missed.push(id);
            }
        }

        return fetchMissedCaches(missed, I.server).then(function(cache) {
            cache.forEach(function(item, i) {
                I.cache[missed[i]] = item;
                localStorage["day." + missed[i]] = JSON.stringify(item);
            });
        }).then(function() {
            var res = {};

            var setOrAdd = function(item) {
                if (res[item.link]) res[item.link].count += item.count;
                else res[item.link] = JSON.parse(JSON.stringify(item));
            }

            I.today.forEach(setOrAdd);
            for (var i=1; i < viewConfig.range; i++) I.cache[I.todayId - i].forEach(setOrAdd);

            res = Object.values(res);

            res = transform(res).filter(function(x) {
                return viewConfig.origins[x.origin] && match(x.title, viewConfig.searchText);
            });

            res.sort(function(a, b) {
                var field = viewConfig.order.field;
                return viewConfig.order.sorter[field](a[field], b[field]);
            });
            if (viewConfig.order.orientation === "desc") res.reverse();

            var start = viewConfig.page * viewConfig.count;
            return {
                data: res.slice(start, start + viewConfig.count),
                count: res.length,
            };
        });
    })
}
