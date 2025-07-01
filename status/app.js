Vue.component('sortus', {
    props: ['field', 'order'],
    template:
        `<span class="pull-right">
        <i class="fa fa-caret-down" aria-hidden="true" v-if="order.field == field && order.orientation == 'desc'"></i>
        <i class="fa fa-caret-up" aria-hidden="true" v-else-if="order.field == field && order.orientation == 'asc'"></i>
        <i style="color:lightgray" class="fa fa-sort" aria-hidden="true" v-else></i>
        </span>`,
});

var db = new Database("https://vietcodes.com/");

new Vue({
    el: "#app",
    data: {
        view: {
            page: 0,
            page_size: 10,
            range: "today",
            order: {
                field: "count",
                orientation: "desc",
                sorter: {
                    count: (a, b) => a - b,
                    title: (a, b) => a.localeCompare(b),
                    solutions: (a, b) => a.length - b.length,
                },
            },
            searchText: "",
            showHidden: false,
        },
        table: [],
        max_page: 0,
        loading: false,
    },
    computed: {
        pages: function () {
            let left = 4;
            let pages = [this.view.page];
            for (let i = 1; left > 0; i++) {
                let ok = false;
                if (this.view.page + i <= this.max_page) {
                    pages.push(this.view.page + i);
                    left -= 1;
                    ok = true;
                }
                if (this.view.page - i >= 0) {
                    pages.push(this.view.page - i);
                    left -= 1;
                    ok = true;
                }
                if (!ok) break;
            }
            pages.sort((a, b) => a - b);
            return pages;
        },
    },
    methods: {
        reload: async function () {
            try {
                this.loading = true;
                this.view.page = 0;
                let res = await db.render(this.view);
                this.table = res.data;
                this.max_page = res.max_page;
            } catch (error) {
                alert("Đã có lỗi xảy ra");
                console.log(error);
            } finally {
                this.loading = false;
            }
        },
        sortBy: function (field) {
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
        toggleHidden: function (problem_id) {
            db.toggleHidden(problem_id);
            this.reload();
        }
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
        max_page: function (val) {
            this.view.page = Math.min(this.view.page, val);
        },
    },
})
