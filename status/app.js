Vue.component('sortus', {
    props: ['field', 'order'],
    template:
    '<span class="pull-right">' +
    '<i class="fa fa-caret-down" aria-hidden="true" v-if="order.field == field && order.orientation == \'desc\'"></i>' +
    '<i class="fa fa-caret-up" aria-hidden="true" v-else-if="order.field == field && order.orientation == \'asc\'"></i>' +
    '<i style="color:lightgray" class="fa fa-sort" aria-hidden="true" v-else></i>' +
    '</span>',
});

var db = new Database("http://ec2-35-170-34-9.compute-1.amazonaws.com/oj-status/");

new Vue({
    el: "#app",
    data: {
        view: {
            page: 0,
            count: 10,
            range: 1,
            order: {
                field: "count",
                orientation: "desc",
                sorter: {
                    count: function(a, b) { return a-b; },
                    title: function(a, b) { return a.localeCompare(b); },
                },
            },
            origins: {
                NTUCoder: true,
                VOJ: true,
            },
            searchText: "",
        },
        table: [],
        count: 0,
        initiated: false,
        loading: false,
    },
    computed: {
        max_page: function() { return Math.floor(this.count / this.view.count); },
        pages: function() {
            var I = this;
            if (I.max_page < 1) return [];
            var left = 4;
            var res = [I.view.page];
            for (var i = 1; left > 0; i++) {
                var ok = false;
                if (I.view.page + i <= I.max_page) res.push(I.view.page + i), left -= 1, ok = true;
                if (I.view.page - i >= 0) res.push(I.view.page - i), left -= 1, ok = true;
                if (!ok) break;
            }
            res.sort(function(a, b) { return a-b; });
            return res;
        },
    },
    methods: {
        reload: function() {
            var I = this;
            I.loading = true;
            db.render(I.view).then(function(res) {
                I.table = res.data;
                I.count = res.count;
                I.loaded = true;
                I.loading = false;
            }).catch(function(error) {
                alert("Đã có lỗi xảy ra");
                console.log(error);
            });
        },
        sortBy: function(field) {
            if (this.view.order.field == field) {
                if (this.view.order.orientation == "desc") {
                    this.view.order.orientation = "asc";
                } else {
                    this.view.order.orientation = "desc";
                }
            } else {
                this.view.order.field = field;
            }
        },
    },
    mounted() {
        this.reload();
    },
    watch: {
        view: {
            handler() {
                this.reload();
            },
            deep: true,
        },
        max_page: function(val) {
            this.view.page = Math.min(this.view.page, val);
        },
    },
})
