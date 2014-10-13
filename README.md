# VACANCY

Real-time notification of room occupancy, using a wifi-enabled microcontroller and PIR sensor and a NodeJS-powered websockets-enabled Web Application.

## Hardware

Tested with the following:

 - Arduino Duemilanove ATmega328  
   (http://arduino.cc/en/Main/arduinoBoardDuemilanove/)
 - CuHead WiFi shield Version 2.0
   (http://store.linksprite.com/cuhead-wifi-shield-v2-0-for-arduino/)
 - Wide Angle PIR Sensor ST-00081
   (http://shopsimplytronics.com/wide-angle-pir-sensor/)

### Wiring diagram

TODO

### Firmware

Requires [Arduino software](http://arduino.cc/)
*app/*

You must change the following variables in *app/sketch/sketch.ino*

```C
// The IP address of the server
// Unfortunately, DNS is not supported
uint8 ip[] = { 192,168,1,3 };

// The port the server is listening on
int port = 8081;

// The local IP assigned tp the device (this may not be needed)
// Unfortunately, DHCP is not supported
unsigned char local_ip[] = { 192,168,1,2 };

// The IP of the router or gateway on the local network
unsigned char gateway_ip[] = { 192,168,1,1 };

// Subnet mask for local network
unsigned char subnet_mask[] = { 255,255,255,0 };

// Wifi network name
// NOTE: Only 802.11b is supported
const prog_char ssid[] PROGMEM = { "YOUR_NETWORK_SSID" };

// Network security
// OPEN: 0 | WEP: 1 | WPA: 2 | WPA2: 3
unsigned char security_type = 3;

// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = { "YOUR_NETWORK_KEY" };

// Access point network (usual): 1
// Adhoc network: 2
unsigned char wireless_mode = 1;
```

### Server
*server/*

Running the server requires [NodeJS](http://nodejs.org/).

Change to the server directory
`cd server`

Just once, install modules.
`npm install`

Start the server
`node app.js`

Server runs on port 8081.
It listens for `POST /:room` requests from the Arduino.
Also, it serves the web application from `server/public`.
Currently this is a single page app: `GET localhost:8081` will serve **server/public/index.html**.


### Web Application
*server/public*

Uses Twitter bootstrap, jQuery & socket.io.

