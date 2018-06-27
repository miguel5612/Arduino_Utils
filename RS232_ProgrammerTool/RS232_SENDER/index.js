// Read the file and print its contents.
var fs = require('fs')
var SerialPort = require('serialport');

var filename = process.argv[2];
var portNumber = process.argv[3];
var port = new SerialPort(portNumber,{
    baudRate:9600
});

port.on('open', function() {
  console.log("Arduino conectado en el puerto"+portNumber);
});

fs.readFile(filename, 'utf-8', function(err, data) {
  if (err) throw err;
  console.log('OK: ' + filename);
  console.log(data.toString());
  port.write(data.toString());
});