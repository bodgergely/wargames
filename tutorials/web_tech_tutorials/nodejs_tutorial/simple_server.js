var http = require('http');
var fs = require('fs')

var port = 3000
var filePath = __dirname + '/readme.txt'

function bufferedSend(filePath, resp) {
  var myReadStream = fs.createReadStream(filePath, 'utf8')
  myReadStream.pipe(resp)
}

function send(filePath, resp) {
  var data = fs.readFileSync(filePath, 'utf8') 
  resp.end(data)
}

var server = http.createServer(function(req, resp) {
  console.log('request was made: ' + req.url)
  resp.writeHead(200, {'Content-Type': 'text/plain'});
  if (req.url.endsWith('buffered')) {
    console.log('Buffered send requested.')
    bufferedSend(filePath, resp)
  } else {
    console.log('Non buffered send requested.')
    send(filePath , resp)
  }
});


server.listen(port, '127.0.0.1')
console.log(`yo dawgs, now listening on port ${port}`)
