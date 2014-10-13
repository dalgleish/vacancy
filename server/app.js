var util = require('util');
var bodyParser = require('body-parser')

var express = require('express.io');
var app = express();
app.http().io();

var port = 8081;
var status;

var rooms = {
  men: {
    status: 'offline'
  },
  women: {
    status: 'offline'
  }
};

app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static(__dirname + '/public'));

app.post('/men', function(req, res) {
  if (req.body.status) {
    status = req.body.status.trim().toLowerCase();

    // vacant or occupied
    req.io.broadcast(status + ':men');

    console.log('Room is ', status);
  } else {
    console.err('body didn\'t contain a status\n', req.body);
  }

  res.set('Content-Type', 'text/plain');
  res.send('ok');
});

// TODO: Not implemented
//app.post('/women', function(req, res) { });

app.io.route('reserve:men', function(req) {
  console.log('reserve:men');
  rooms.men.status = 'reserved';
  app.io.broadcast('reserved:men');
  // Everyone, except me:
  //req.io.broadcast('reserved:men');
});

app.io.route('ready', function(req) {
  console.log('client connected', req.socket.id);
});

app.listen(port);
