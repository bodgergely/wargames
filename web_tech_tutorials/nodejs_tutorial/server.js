var http = require('http');
var fs = require('fs');

var port = 3000;

var server = http.createServer(function(req, resp) {
  console.log('request was made: ' + req.url)
  if (req.url === '/home' || req.url === '/') {
    resp.writeHead(200, {'Content-Type': 'text/html'})
    fs.createReadStream(__dirname + '/index.html').pipe(resp)
  } else if (req.url === '/contact') {
    resp.writeHead(200, {'Content-Type': 'text/html'})
    fs.createReadStream(__dirname + '/contact.html').pipe(resp)
  } else if (req.url === '/api/ninjas') {
    var ninjas = [{name: 'ryu', age: 32}, {name: 'yoshi', age: 29}]
    resp.writeHead(200, {'Content-Type': 'application/json'})
    resp.end(JSON.stringify(ninjas))
  } else {
    resp.writeHead(404, {'Content-Type': 'text/html'})
    fs.createReadStream(__dirname + '/404.html').pipe(resp)
  }
});

server.listen(port, '127.0.0.1');
console.log(`yo dawgs, now listening on port ${port}`);
