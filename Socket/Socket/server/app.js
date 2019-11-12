var net = require('net');

let locIP = "127.0.0.1";
let globIP = "0.0.0.0";

// MessageTypes
const msgStartServer = "startServer\r";
const msgStopServer = "stopServer\r";
const msgRoomNumber = "room ";
const msgJoin = "join "
const msgIPAddress = "ip ";

// Room number counter
let roomCounter = 0;

// Store all connected sockets
let connections = {};

// Store servers
let servers = {};


function storeConnection(ip, port, socket) {
	console.log(`${ip}:${port} connected.`);
	if (connections[ip] == undefined) {
		connections[ip] = {};
	}
	connections[ip][port] = socket;
}
function removeConnection(ip, port) {
	console.log(`${ip}:${port} disconnected.`);
	connections[ip][port] = undefined;
}

function storeServer(roomNum, ip, port) {
	console.log(`${ip}:${port} stored as server.`)
	servers[roomNum] = {
		"ip": ip,
		"port": port
	};
}
function removeServer(roomNum) {
	if (servers[roomNum]) {
		console.log(`${servers[roomNum]["ip"]}:${servers[roomNum]["port"]} removed from server list.`)
		servers[roomNum] = undefined;
	}
}

var server = net.createServer((socket) => {
	let ip = socket.remoteAddress;
	let port = socket.remotePort;
	let serverPort = 3030;
	let roomNumber = undefined;

	storeConnection(ip, port, socket);


	socket.on('end', (s) => {
		removeConnection(ip, port);
		removeServer(roomNumber);
	});


	socket.on('error', (e) => {
		console.log("EEE:",e);
	});


	socket.on('data', (d) => {
		let data = d.toString();
		console.log(`${ip}:${port} emitted: ${data}`);

		// Start Server
		if (data == msgStartServer) {
			roomNumber = roomCounter++;
			storeServer(roomNumber, ip, serverPort);
			socket.write(msgRoomNumber + roomNumber + '\r');
		}

		// Stop Server
		if (data == msgStopServer) {
			removeServer(roomNumber);
			roomNumber = undefined;
		}

		// Join team
		if (data.length > msgJoin.length) {
			if(data.substring(0,5) == msgJoin) {
				let room = d.toString().replace(msgJoin, "").replace('\r', '');
				let data = servers[room];
				if (data) {
					socket.write(msgIPAddress + data["ip"] + ":" + data["port"] + '\r');
					console.log(`${ip}:${port} joins room ${room}.`);
				}
				else {
					socket.write(msgIPAddress + "-1" + '\r');
				}
			}
		}
	});

	
	socket.pipe(socket);

	for (let i = 0; i < 1; i++) {
		setTimeout(function() {
			let data = `Echo from server ${i}`;
			if(socket.writable) {
				console.log(`Sent "${data}" to ${ip}:${port}`)
				// socket.write('\r');
				socket.write(data + '\r');
			}
		}, i*2000);
	}
});

server.listen(process.env.PORT || 3000, locIP, () => {
	console.log(`server bound ${server.address().address} ${server.address().port}`);
});