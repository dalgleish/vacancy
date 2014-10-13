
/******************************************************************************
  Tested with:
   - Arduino Duemilanove ATmega328 (http://arduino.cc/en/Main/arduinoBoardDuemilanove)
   - CuHead WiFi shield Version 2.0 (http://store.linksprite.com/cuhead-wifi-shield-v2-0-for-arduino)
   - Wide Angle PIR Sensor ST-00081 (http://shopsimplytronics.com/wide-angle-pir-sensor)

  Author: Andrew Dalgleish <andrew@dalgleish.info>
 *****************************************************************************/
 
#include <WiServer.h>

// Passive Infrared pin out
#define PIR_OUT (6)

//---------------------------------------------------------------------------

uint8 ip[] = { 192,168,1,3 };
int port = 8081;
unsigned char local_ip[] = { 192,168,1,2 };
unsigned char gateway_ip[] = { 192,168,1,1 };
unsigned char subnet_mask[] = { 255,255,255,0 };
const prog_char ssid[] PROGMEM = { "YOUR_NETWORK_SSID" };

// 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2
unsigned char security_type = 3;

// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = { "YOUR_NETWORK_KEY" };

// 1 - access point; 2 - adhoc;
unsigned char wireless_mode = 1;

// These need to be defined
unsigned char ssid_len;
unsigned char security_passphrase_len;
prog_uchar wep_keys[] PROGMEM = { 
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 1
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 2
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Key 3
};

//---------------------------------------------------------------------------

// Most recent state; 0 - vacant; 1 - occupied
int state = -1;
// Time (in ms) when the next status is sent
long nextStatusTime = 0;
// Interval (in ms) between status updates
int statusInterval = 1000*10;
// Flag indicating motion detected since last status update
long detected = 0;

void sendStatusResponse(char* data, int len) {
  // Uncomment if you care about the response data
  //  while (len-- > 0) {
  //    Serial.print(*(data++));
  //  }
}

void sendStatusRequest() {
  if (state == 0) {
    WiServer.println("status=VACANT");
    Serial.println("status=VACANT");
  } 
  else {
    WiServer.println("status=OCCUPIED");
    Serial.println("status=OCCUPIED");
  }
}

POSTrequest sendStatus(ip, port, "server", "/status", sendStatusRequest);

void setup() {
  Serial.begin(9600);
  Serial.println("begin setup");

  WiServer.init(NULL);
  WiServer.enableVerboseMode(false);
  sendStatus.setReturnFunc(sendStatusResponse);
  Serial.println("wifi ready");

  pinMode(PIR_OUT, INPUT);
  Serial.println("pir ready");

  Serial.println("setup complete");
  
  // Send initial state
  state = digitalRead(PIR_OUT);
  sendStatus.submit();
}

void loop() {
  // Check if it's time to sent next status update
  if (millis() >= nextStatusTime) {
    if (detected == 1) {
      detected = 0;
      if (state == 0) {
        state = 1;
        sendStatus.submit();
      }
    } else {
      if (state == 1) {
        state = 0;
        sendStatus.submit();
      }
    }

    nextStatusTime += statusInterval;
  } else {
      if (digitalRead(PIR_OUT) == HIGH) {
        // Trip detected flag
        detected = 1;
      }
  }

  // Process any network I/O tasks
  WiServer.server_task();
  delay(10);
}




