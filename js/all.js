function loadComments() {
    if (document.getElementById("btn-load-cmt") === null) return;
    document.getElementById("btn-load-cmt").innerHTML="Loading comments...";
    // Load the plugin, code from Disqus's documents
    (function() {
        var d = document, s = d.createElement('script');
        s.src = 'https://vascal.disqus.com/embed.js';
        s.setAttribute('data-timestamp', +new Date());
        s.onload = loadWindow;
        s.onerror = showError;
        (d.head || d.body).appendChild(s);
    })();
    function loadWindow() {
        // Remove the load button
        var btn = document.getElementById("btn-load-cmt");
        btn.outerHTML = "";
        delete btn;
        // Show disqus-window a.k.a remove .hide class
        document.getElementById("disqus-window").classList.remove("hide");
    }
    function showError(error) {
        console.error(error);
        document.getElementById("btn-load-cmt").innerHTML="Disqus is down.";
    }
}

(function() {
    if (window.location.hostname == "vietcodes.github.io" || window.location.hostname == "blog.vietcodes.com") {
        loadComments();
    }
})();
