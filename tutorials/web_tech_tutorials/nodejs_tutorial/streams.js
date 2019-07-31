var fs = require('fs')

var stuff = require('./stuff')

var myReadStream = fs.createReadStream(__dirname + '/readme.txt', 'utf8')
//var myReadStream = fs.createReadStream('/usr/bin/vim.gtk')
var myWriteStream = fs.createWriteStream(__dirname + '/writeme.txt')

var readChunkCounter = 0
myReadStream.on('data', function (chunk) {
  ++readChunkCounter
  // console.log(`(${readChunkCounter}) new chunk received, length: ${chunk.length}:`)
  // console.log(chunk)
  myWriteStream.write(chunk)
})




