var five = require("johnny-five");
var express = require('express');
var pixel = require("node-pixel");

var strip = null;

var app = express.createServer(
    express.bodyParser(),
    express.static('public')
);

// web server listen on port 3000
app.listen(3000);
var io = require('socket.io').listen(app);

var max_speed_l = 100;
var max_speed_r = 100;

// set up the input
var stdin = process.openStdin();
require('tty').setRawMode(true);

var board = new five.Board({port: process.argv[2]});

var l_motor = r_motor = null;
var distance;

board.on("ready", function(err) {

    if (err){
        console.log(err);
        return;
    }
    l_motor = new five.Motor({pins: {pwm: 6, dir: 7}});
    r_motor = new five.Motor({pins: {pwm: 5, dir: 4}});

    console.info("Board connected. Robot set up. LRUD to control");
    
    // Uses proximity sensor on the front to tell the distance from the object
    // Assumes prox sensor is plugged into port 2 - if not change the pin to use
    // the pin for appropriate port and the second pin within it.  
    var proximity = new five.Proximity({
        controller: "HCSR04",
        pin: 10,
        freq: 200
      });
    
    // mbot maps WS2812 pixels in a 2 pixel strip attached to pin 13.
    strip = new pixel.Strip({
        data: 13,
        length: 2,
        board: this,
        controller: "FIRMATA",
    });
    
    // leds on
    strip.on("ready", function() {
        var colors = ["#880066", "#00AA88"]; 
        strip.pixel(0).color(colors[0]);
        strip.pixel(1).color(colors[1]);
        strip.show();
    });  
    
    // on a socket connection
    io.sockets.on('connection', function(socket) {

        socket.on('motor', function(data) {
            max_speed_l = data.speed;
            max_speed_r = data.speed;
        });

        proximity.on("data", function() {
            distance = this.cm;
            socket.emit('sonar', { distance: distance });
        }); 

    });   
});

stdin.on('keypress', function(chunk, key) {
	// process the keypresses

	if (key) {
		switch (key.name) {
			case "up":
                l_motor.reverse(max_speed_l);
                r_motor.forward(max_speed_r);
				break;
			case "down":
                r_motor.reverse(max_speed_r);
                l_motor.forward(max_speed_l);
				break;
			case "left":
                l_motor.forward(max_speed_l);
                r_motor.forward(max_speed_r);
				break;
			case "right":
                r_motor.reverse(max_speed_r);
                l_motor.reverse(max_speed_l);
				break;
			case "space":
                l_motor.stop();
                r_motor.stop();
				break;
		}
	}
});