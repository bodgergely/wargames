var http = require('http');
var fs = require('fs')

var port = 3000


var server = http.createServer(function(req, resp) {
  console.log('request was made: ' + req.url)
  resp.writeHead(200, {'Content-Type': 'application/json'});
  var myObj = {
    name: 'Ryu',
    job: 'Ninja',
    age: 29
  }
  resp.end(JSON.stringify(myObj))

});


server.listen(port, '127.0.0.1')
console.log(`yo dawgs, now listening on port ${port}`)
