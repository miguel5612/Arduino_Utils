// Read the file and print its contents.
var fs = require('fs')
var SerialPort = require('serialport');
var child_process = require('child_process');

var portNumber = process.argv[2];
var port = new SerialPort(portNumber,{
    baudRate:250000
});

port.on('open', function() {
  console.log("Arduino conectado en el puerto"+portNumber);
});

fs.unlink('\programa.txt');

var wstream = fs.createWriteStream("programa.txt");

port.on('data', function (data) {
	console.log(data.toString());
	if(data.toString().includes(" END/&PROGRAMA;PROGR@MA%FINALIZADO "))
	{
		wstream.write('\n'+"-----END CERTIFICATE-----", function (line) {
			if(line){
		        wstream = fs.createWriteStream("programa.txt");		
		   	}
		 });
		wstream.close();
		child_process.exec('txt2exe.bat', function(error, stdout, stderr) {	
		console.log('programa escrito correctamente en .exe');
		});
	}else
	{
	    wstream.write(data.toString(), function (line) {
			if(line){
		        wstream = fs.createWriteStream("programa.txt");		
		   	}
		 });
		//console.log("LLega la informacion del programa...");
		console.log(data.toString());
	}
});