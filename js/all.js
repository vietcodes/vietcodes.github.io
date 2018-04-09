function loadComments() {
    document.getElementById("btn-load-cmt").innerHTML="Loading...";
    // Load the plugin, code from Disqus's documents
    (function() {
        var d = document, s = d.createElement('script');
        s.src = 'https://vascal.disqus.com/embed.js';
        s.setAttribute('data-timestamp', +new Date());
        s.onload = loadWindow;
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
}

//var owa_baseUrl = 'https://nilotic-misleads.000webhostapp.com/owa/1.6.0/';
//var owa_cmds = owa_cmds || [];
//owa_cmds.push(['setSiteId', 'd0a9cbff99c9a71664103fda526c3244']);
//owa_cmds.push(['trackPageView']);
//owa_cmds.push(['trackClicks']);
//owa_cmds.push(['trackDomStream']);

(function() {
    if (window.location.hostname == "vietcodes.github.io") {
        loadComments();
        //var _owa = document.createElement('script'); _owa.type = 'text/javascript'; _owa.async = true;
        //owa_baseUrl = ('https:' == document.location.protocol ? window.owa_baseSecUrl || owa_baseUrl.replace(/http:/, 'https:') : owa_baseUrl );
        //_owa.src = owa_baseUrl + 'modules/base/js/min.js';
        //var _owa_s = document.getElementsByTagName('script')[0]; _owa_s.parentNode.insertBefore(_owa, _owa_s);
    }
})();
