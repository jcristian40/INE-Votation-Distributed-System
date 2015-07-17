
var servers = {
	udp: {
		host: "127.0.0.1",
		port: 7777
	},
	http: {
		host: "127.0.0.1",
		port: 8080
	}
}

var votes = [];
var status = {
	total : 0
};

// UDP Server

var dgram = require("dgram");
var udpServer = dgram.createSocket("udp4"); 

udpServer.on("error",function(err){
	console.log("Server error:\n", err.stack);
	udpServer.close();
});

udpServer.on("listening", function(){
	var address = udpServer.address();
	console.log("UDP Server listening ", address.address, ":", address.port);
});

udpServer.on("message", function(msg, rinfo){
	console.log("message: ", msg, rinfo.address, ":", rinfo.port);

	votes.push({id: votes.length});

	status.total++;
	io.emit('vote', status);
	
	var res = new Buffer('OK');
	var client = dgram.createSocket("udp4");
	client.send(res, 0, res.length, rinfo.port, rinfo.host, function(err, bytes){
		client.close();
	});

});

udpServer.bind(servers.udp.port, servers.udp.host);

// HTTP Server

var http = require('http');

var httpServer = http.createServer(function(req, res){
	res.writeHead(200, 'Content-Type: text/html');

	var html = '<!DOCTYPE html>';
	html += '<html>';
	html += '	<head>';
	html += '		<meta charset="UTF-8">';
	html += '		<script src="https://cdn.socket.io/socket.io-1.3.6.js"></script>';
	html += '		<script type="text/javascript">';
	html += '			var socket = io("http://localhost:8080");';
	html += '			socket.on("vote", function(data){';
	html += '				document.getElementById("content").innerHTML = JSON.stringify(data);';
	html += '			});';
	html += '		</script>';
	html += '	</head>';
	html += '	<body>';
	html += '		<div id="content">'+JSON.stringify(status)+'</div>';
	html += '	</body>';
	html += '</html>';

	res.end(html);
});

var io = require('socket.io')(httpServer);

httpServer = httpServer.listen(servers.http.port, servers.http.host);

console.log("HTTP Server listening ", servers.http.host, ":", servers.http.port);