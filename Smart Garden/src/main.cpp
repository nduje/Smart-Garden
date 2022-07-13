#include "Sensors.h"
#include "Calculation.h"
#include "Wireless.h"

#define motor 7
#define sensorPower 8
#define sensorPin A0
#define led 13

#define soilWet 500
#define soilDry 750

SENSORS sensor;

typedef enum {
  READ_SERIAL,
  READ_SENSORS,
  TURNON_LED,
  TURNOFF_LED,
  PUMP_WATER
} StateType;

StateType ledState = READ_SERIAL;
StateType soilState = READ_SERIAL;

int timer = 0;
float temp = 0;
float hum = 0;
uint16_t lux = 0;
int soil = 0;

int checkTimer();
void blinkLed(uint16_t lux);
void pumpWater(int soil);
int readSoil();

char ssid[] = "smartgarden";
char pass[] = "smartgarden123";
int keyIndex = 0;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

WiFiClient client = server.available();

void connectWiFi();
void printWeb();

void setup() {
  Serial.begin(9600);

  Serial.println("Access Point Web Server");
  enableWiFi();
  connectWiFi();

  delay(10000);

  server.begin();

  printWiFiStatus();

  Serial.println("");
  
  pinMode(motor, OUTPUT);
  pinMode(sensorPower, OUTPUT);
  pinMode(led, OUTPUT);

  digitalWrite(sensorPower, LOW);

  sensor.DHT_init();

  Serial.println("");

  timer = checkTimer();
  lux = calculateRandomLight();

  Serial.println("");

  delay(100);
}

void loop() {
  lux = calculateRandomLight();

  int currentTime = calculateCurrentTime();

  Serial.print("Current time: ");
  Serial.println(currentTime);

  blinkLed(lux);

  if (timer <= currentTime) {
    soil = readSoil();
    pumpWater(soil);
  }

  if (status != WiFi.status()) {
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      Serial.println("Device connected to AP");
    } else {
      Serial.println("Device disconnected from AP");
    }
  }

  client = server.available();

  if (client) {
    printWeb();
  }

  Serial.println("");

  delay(2000);
}

int checkTimer() {
  temp = sensor.readTemp();
  hum = sensor.readHum();

  int startTime = calculateCurrentTime();
  int calculatedTime = calculateTime(temp, hum);

  int sum = startTime + calculatedTime;

  Serial.print("Timer: ");
  Serial.println(sum);

  return sum;
}

void blinkLed(uint16_t lux) {
  switch (ledState) {
    case READ_SERIAL:
      ledState = READ_SENSORS;
      break;
    
    case READ_SENSORS:
      if (lux < 100)
        ledState = TURNON_LED;
      else
        ledState = TURNOFF_LED;
      break;

    case TURNON_LED:
      digitalWrite(led, HIGH);
      ledState = READ_SERIAL;
      break;

    case TURNOFF_LED:
      digitalWrite(led, LOW);
      ledState = READ_SERIAL;
      break;

    default:
      break;
  }

  return;
}

void pumpWater(int soil) {
  switch (soilState) {
    case READ_SERIAL:
      soilState = READ_SENSORS;
      break;
    
    case READ_SENSORS:
      if (soil >= soilDry)
        soilState = PUMP_WATER;
      else if (soil <= soilWet) {
        soilState = READ_SERIAL;
        timer = checkTimer();
      }
      else
        soilState = READ_SERIAL;
      break;

    case PUMP_WATER:
      digitalWrite(motor, HIGH);
      delay(1000);
      digitalWrite(motor, LOW);
      timer = checkTimer();
      soilState = READ_SERIAL;
      break;

    default:
      break;
  }

  return;
}

int readSoil() {
  digitalWrite(sensorPower, HIGH);
  delay(10);

  int soil = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);

  Serial.print("Soil: ");
  Serial.println(soil);

  return soil;
}

void connectWiFi() {
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    while (true);
  }
}

void printWeb() {
  if (client) {                             // if you get a client,
    // Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        // Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Refresh: 5");
            client.println();
           
            //create the buttons
            client.print("<p>Temperature: ");
            client.print(temp);
            client.print(" degree Celsius</p>");

            client.print("<p>Humidity: ");
            client.print(hum);
            client.print("%</p>");

            client.print("<p>Light: ");
            client.print(lux);
            client.print(" lx</p>");

            client.print("<p>Soil: ");
            client.print(soil);
            client.print("</p>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    // Serial.println("client disconnected");
  }
}