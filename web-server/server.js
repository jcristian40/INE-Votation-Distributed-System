var config = require('./config.json');

var udp_config = config.udp;
var http_config = config.http;

// Votation Dynamics

var votes = new Map();
var votation = {
	total : 0,
	votes: {
		"PRI": 0,
		"PAN": 0,
		"PRD": 0,
		"P_T": 0,
		"VDE": 0,
		"MVC": 0,
		"NVA": 0,
		"MOR": 0,
		"HUM": 0,
		"ENC": 0,
		"FRD": 0
	}
};


var updateVote = function(){
	socket.emit('update', votation);
}

var appendVote = function(vote){

	votation.total++;

	if(votes.has(vote.curp) && votes.has(vote.rfc)){

		votation.votes["FRD"]++;

	}else{

		votes.set(vote.curp, vote);
		votes.set(vote.rfc, vote);

		votation.votes[vote.party]++;
	}

	updateVote();
}

setInterval(updateVote, 1000);

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

	var vote = JSON.parse(msg.toString());
	console.log("received message from: ",rinfo.address, ":", rinfo.port);

	appendVote(vote);
	
	var res = new Buffer('OK');
	var client = dgram.createSocket("udp4");

	client.send(res, 0, res.length, rinfo.port, rinfo.host, function(err, bytes){
		client.close();
	});

});

udpServer.bind(udp_config.port, udp_config.host);

// HTTP Server

var http = require('http');
var io = require('socket.io');

var static = require('node-static');
var fileServer = new static.Server('./public');

var httpServer = http.createServer(function(req, res){

	req.addListener('end', function(){

		fileServer.serve(req, res);	
	
	}).resume();;
});

var socket = io(httpServer);

httpServer = httpServer.listen(http_config.port, http_config.host);
console.log("HTTP Server listening ", http_config.host, ":", http_config.port);
