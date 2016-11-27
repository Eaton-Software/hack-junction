var express = require('express');
var request = require('request');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

var app = express();


app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());

var api = 'https://9h21iuqi9g.execute-api.eu-central-1.amazonaws.com/v1';

app.get('/officeEmpty', function(req, res) {
    var info;
    var devices = [];

    request(api + '/gateways/34/devices', function(error, response, body){ 
        if(!error && response.statusCode == 200) {
            info = JSON.parse(body);
            console.log(info);

            for(var i = 0; i < info.length; i++) 
            devices.push(info[i].device);

            for(var i = 0; i < devices.length; i++) {
                console.log(devices[i]);
                request({
                    url: api + '/gateways/34/devices/' + devices[i] + '/setlevel', //URL to hit
                    qs: {from: 'blog example', time: + new Date()}, //Query string data
                    method: 'POST',
                    //Lets post the following key/values as form
                    json: {
                        "level": 0,
                        "disablePIR": "00"
                    }
                }, function(error, response, body){
                    if(error) {
                        console.log(error);
                    } else {
                        console.log(response.statusCode, body);
                    }
                });
            }
        }
        else {
            console.log(error);
            console.log(response.statusCode);
        }
    });

    res.status(200);
    res.send("Turning lights off");
});

app.get('/peoplePresent', function(req, res) {
    var info;
    var devices = [];

    request(api + '/gateways/34/devices', function(error, response, body){ 
        if(!error && response.statusCode == 200) {
            info = JSON.parse(body);
            console.log(info);

            for(var i = 0; i < info.length; i++) 
            devices.push(info[i].device);

            for(var i = 0; i < devices.length; i++) {
                console.log(devices[i]);
                request({
                    url: api + '/gateways/34/devices/' + devices[i] + '/setlevel', //URL to hit
                    qs: {from: 'blog example', time: + new Date()}, //Query string data
                    method: 'POST',
                    //Lets post the following key/values as form
                    json: {
                        "level": 100,
                        "disablePIR": "00"
                    }
                }, function(error, response, body){
                    if(error) {
                        console.log(error);
                    } else {
                        console.log(response.statusCode, body);
                    }
                });
            }
        }
        else {
            console.log(error);
            console.log(response.statusCode);
        }
    });

    res.status(200);
    res.send("Turning lights on");
});

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
});

// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
  app.use(function(err, req, res, next) {
      res.status(err.status || 500);
      res.send("Error: " + err.message);
  });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
  res.status(err.status || 500);
  res.send("Error: " + err.message);
});


module.exports = app;
