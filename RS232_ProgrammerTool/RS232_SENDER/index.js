// Read the file and print its contents.
var fs = require('fs')
var SerialPort = require('serialport');
var child_process = require('child_process');
var exec = require('child_process').execFile;
var LineByLineReader = require('line-by-line');


var filename = 'sender.txt'
var portNumber = process.argv[2];

fs.unlink('\sender.txt');

var port = new SerialPort(portNumber,{
    baudRate:250000
});
port.on('open', function() {
  console.log("Modulo conectado en el puerto"+portNumber);
	child_process.exec('exe2txt.bat', function(error, stdout, stderr) {
    	console.log(stdout);
    	
	    lr = new LineByLineReader(filename);

		lr.on('error', function (err) {
			console.log("ERROR:  "+err);
			// 'err' contains error object
		});

		lr.on('line', function (line) {
			console.log(line);
			port.write(line + '\n');
			// 'line' contains the current line without the trailing newline character.
		});

		lr.on('end', function () {
			port.write(" END/&PROGRAMA;PROGR@MA%FINALIZADO ");
			console.log("Transmision Finalizada");
			// All lines are read, file is closed now.
		});
	});
});

