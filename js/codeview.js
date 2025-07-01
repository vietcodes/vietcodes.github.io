(function() {
    document.querySelectorAll('.selectable-code').forEach(function(node) {
        node.addEventListener("keydown", function (e) {
            if (e.ctrlKey) {
                if(![86, 88].includes(e.keyCode)) {
                    return;
                }
            }
            if (33 <= e.keyCode && e.keyCode <= 40) {
                return;
            }
            e.preventDefault();
        });
        node.addEventListener("cut", function(e){
            e.preventDefault();
        });
        node.addEventListener("paste", function(e){
            e.preventDefault();
        });
    });
})();
