var express = require('express');
var http = require('http');
var util = require('util');
var bodyParser = require('body-parser')

var port = 8081;
var status;

var app = express();

app.use(bodyParser.urlencoded({ extended: false }))

app.post('/men', function(req, res) {
  if (req.body.status) {
    status = req.body.status;

    console.log('Room is ', status);
  } else {
    console.err('body didn\'t contain a status\n', req.body);
  }

  res.set('Content-Type', 'text/plain');
  res.send('ok');
});

app.post('/women', function(req, res) {
  res.send('hello world');
});

app.get('/', function(req, res) {

  // TODO: Serve web content
  res.send('hello world');
});

app.listen(port);
