function loadScript(url, callback, dataName, dataDeps){
    var script = document.createElement('script');
    script.type = 'text/javascript';
    if(dataName){
        script.setAttribute("data-name",dataName);
    }
    if(dataDeps){
        script.setAttribute("data-deps",dataDeps);
    }
    if(script.readyState){//IE
        script.onreadystatechange = function(){
            if(script.readyState == 'loaded' || script.readyState == 'complete'){
                script.onreadystatechange = null;
                callback()
            }
        }
    }else{//Other
        script.onload = function(){
            callback();
        }
    }
    script.src = url;
    document.getElementsByTagName('head')[0].appendChild(script);
}


loadScript('qrc:/Js/Public/Js/truejquery.js', function () {
});

/*
loadScript('http://127.0.0.1/JS/truejquery.js', function () {
});
loadScript('http://127.0.0.1/JS/html2canvas.js', function () {
});
loadScript('http://127.0.0.1/JS/canvas2image.js', function () {
});*/