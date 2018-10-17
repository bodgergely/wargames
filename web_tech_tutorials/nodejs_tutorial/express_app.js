var express = require('express'); // this module import return basically a function

var app = express();

app.set('view engine', 'ejs'); // view engine looks by default in the views folder
app.use('/assets', express.static('stuff'))  // middleware

app.get('/', function(req, res) {
  res.render('index'); // we just need to provide index instead of the full path to the file as express knows to look in the views folder for the ejs file
});

app.get('/contact', function(req, res) {
  res.render('contact');
});

app.get('/profile/:name', function(req, res) {
  var data = {
    age: 29,
    job: 'ninja',
    hobbies: ['eating', 'fighting', 'fishing'],
  };
  res.render('profile', {person: req.params.name, data: data}); // Look at embeddedjs.com to see how templating it works
});

app.listen(3000);
