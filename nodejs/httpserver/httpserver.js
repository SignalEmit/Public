var http = require('http');
var path = require('path');
var fs = require('fs');
var url = require('url');

class HTTPServer {
    constructor(routes, encoding = "utf8", lp = null) {
        this.routes = routes;
        this.httpServer = http.createServer((req, res) => {
            let pathObj = url.parse(req.url, true);
            let handleFn = routes[pathObj.pathname];
            if (handleFn) {
                req.query = pathObj.query;    //获取post提交方式数据
                let msg = '';
                req.setEncoding(encoding)
                req.on('data', function (chunk) {
                    msg += chunk;		      //获取post提交方式数据
                }).on('end', function () {
                    handleFn(msg, res, lp);
                });
            } else {
                let staticPath = path.join(__dirname, 'act');
                let filePath = path.join(staticPath, pathObj.pathname);
                fs.readFile(filePath, 'binary', function (err, fileContent) {
                    if (err) {
                        res.writeHead(404, "Notasdasdas Found");
                        res.end('<h1>404 Not Found!</h1>')
                    } else {
                        res.writeHead(200, 'ok');
                        res.write(fileContent, 'binary');
                        res.end();
                    }
                });
            }
        });
    }

    listen(port) {
        this.httpServer.listen(port);
    }
}


module.exports = {
    HTTPServer
}
