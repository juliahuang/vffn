var SerialPort;
try {
  SerialPort = require("serialport").SerialPort;
} catch (e) {
  console.log(e);
}
var events = require('events');
var eventEmitter = new events.EventEmitter();

function serialConnection(io) {
  var CONNECTION_PORT = "/dev/tty.usbmodem1411"
  var portFound = false;
  var serialPort;
  var io = io;
  var s; // extremely dangerous
  
  
  io.sockets.on('connection', function (socket) {
    s = socket;
    console.log(s);
  });
        
  this.init = function(){
    initPorts = function(){
      try {
        var s = require("serialport");
        s.list(function (err, ports) {
          ports.forEach(function(port) {
            if (port.comName.replace("cu","") == CONNECTION_PORT.replace("tty","")){
              console.log('port verified, serialHelloConnect');
              
              eventEmitter.emit('serialHelloConnect');
              portFound = true;
            }
          });
          if (!portFound){
            console.log('port not found - defaulting to debug mode');
          }
        });
      } catch (e) {
        console.log(e);
        console.log('serialport not found - defaulting to debug mode');
      }
    }
    
    serialHelloConnect = function(){
      serialPort = new SerialPort(CONNECTION_PORT, {
        baudrate: 9600
      });
      
      serialPort.on('open', function (err) {
        console.log('serial connection established...');
      }); 
      
      serialPort.on('data', function(data) {
        console.log('received data...' + data);
        var data = data;
        s.emit('news', { kp: String.fromCharCode(data[0]) });
      }); 
    }
    
    eventEmitter.on('serialHelloConnect', serialHelloConnect);
    initPorts();
  }
 
  this.serialwrite = function(data, tryHard){
    if (portFound){
      console.log(data);
      if (tryHard == false) {
          serialPort.write(data, function(err, results) {
            if (err != undefined){
              console.log(err);
            }
          }); 
      } else {
        for (i = 0; i < 5; i ++) {
          serialPort.write(data, function(err, results) {
            if (err != undefined){
              console.log(err);
            }
          });
        }
      }
      
      
    } else {
      console.log(data);
    }
  }
  
  this.init();
}

module.exports = serialConnection;