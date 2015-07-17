
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
	res.writeHead(200, 'Content-Type: text/json');
	res.end('{}');
});

httpServer = httpServer.listen(servers.http.port, servers.http.host);

console.log("HTTP Server listening ", servers.http.host, ":", servers.http.port);