# INE-Votation-Distributed-System
This is distrubuted system project simulating a SMS distributed solution for Mexico INE votation using C++ UDP Sockets and SQLite


## Distribution

<img src="./screenshot.png" width="100%;"/>

## Web Server

Server that listens UDP request from votation and sends updates to **web clients** through [socket.io](http://socket.io/).

### Prerequisites

- [Node.js](https://nodejs.org/) (with NPM)

### Installation

- `git clone <repository-url>` this repository
- change into the new directory
- `cd web-server`
- `npm install`

### Configuration

- open `config.json` file
- update `udp`, `http` and `express` default server settings


```
{
	"udp": {
		"host": "0.0.0.0",
		"port": 7777
	},
	"http": {
		"host": "0.0.0.0",
		"port": 8080
	},
	"express": {
		"host": "0.0.0.0",
		"port": 8081
	}
}
```


### Running

- ``node server``
- Visit app at [http://localhost:8080](http://localhost:8080)

	