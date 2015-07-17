var port = 7777;
var host = "127.0.0.1";

var dgram = require("dgram");
var server = dgram.createSocket("udp4"); 

server.on("error",function(err){
	console.log("Server error:\n", err.stack);
	server.close();
});

server.on("listening", function(){
	var address = server.address();
	console.log("Server listening ", address.address, ":", address.port);
});

server.on("message", function(msg, rinfo){
	console.log("message: ", msg, rinfo.address, ":", rinfo.port);

	var res = new Buffer('OK');
	var client = dgram.createSocket("udp4");
	client.send(res, 0, res.length, rinfo.port, rinfo.host, function(err, bytes){
		client.close();
	});

});

server.bind(port, host);