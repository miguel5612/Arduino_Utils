// Read the file and print its contents.
var fs = require('fs')
var SerialPort = require('serialport');

var portNumber = process.argv[2];
var port = new SerialPort(portNumber,{
    baudRate:9600
});

port.on('open', function() {
  console.log("Arduino conectado en el puerto"+portNumber);
});
var wstream = fs.createWriteStream("programa.js");

port.on('data', function (data) {
        wstream.write(data.toString('utf-8') + '\n', function (line) {
	if(line){
            wstream = fs.createWriteStream("programa.js");		
        }
 	});
	console.log("LLega la informacion del programa...");	
});