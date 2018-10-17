var fs = require('fs');


var stuff = require('./stuff.js')
//console.log(stuff.adder(5,6))

function directory_ops(argument) {
//    fs.mkdirSync('stuff')
//    fs.rmdirSync('stuff')
/*      fs.rmdir('stuff', function (err) {
          if(!err) {
             console.log('Removed dir') 
          }
      })
*/

    
}

function async_read_write() {
  fs.readFile('readme.txt', 'utf8', function(err, data) {
      console.log('File has been read.')
    if (!err) {
        fs.writeFile('writeMe.txt', data, function(err) {
            if (!err) {
                console.log("Writing the file finished.")
            } else {
                console.log("Error writing the file.")
            }
        });
        console.log('File write initiated.')
    } else {
      console.log('Error writing file');
    }
  });
  console.log('File reading initiated.')
}

function sync_read_write() {
  var readme = fs.readFileSync('readme.txt', 'utf8');
  fs.writeFileSync('writeMe.txt', readme);
}

