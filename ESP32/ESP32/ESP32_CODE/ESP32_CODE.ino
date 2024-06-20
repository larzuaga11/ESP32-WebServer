/**
* @file ES32_code.cpp
* @author Angel G. Fonseca y Luis R. Arzuaga
* @brief This code is in charge of creating the websocket
server, and sending the info to the web page.
* @version 0.1
* @date 2024-05-09
*
* @copyright Copyright (c) 2024
*
*/

/// @brief This initializes the wifi signal
#include <WiFi.h>
/// @brief This gives the function to initialize the server
#include <WebSocketsServer.h>
/// @brief This is for the UART communication
#include <HardwareSerial.h>
/// @brief This is to send the information to the client
#include <WebServer.h>
/// @brief The .h contains the basica webpage
#include "html_page.h"
/// @brief
#include <string>
/// @brief Declare the pins for UART communication
#define RXp2 16
/// @brief Declare the pins for UART communication
#define TXp2 17
/// @brief The id of the wifi
const char* ssid = "iPhone";
/// @brief The password to connect to the wifi
const char* password = "123456789";
/// @brief Create a WebServer object with the port 80
WebServer server(80);
/// @brief Create a WebSocketsServer object with the port
81
WebSocketsServer webSocket = WebSocketsServer(81);
/// @brief Declare Strings p1, p2, JSONtxt y JSONtxt2.
String p1, p2, JSONtxt, JSONtxt2;

/// @brief Functioh Signal that recieves two strings
void Signal(String, String);
void setup() {
Serial.begin(115200);
///Connect to access point
Serial.println("Connecting");
///This function begins the connection to the WiFi
WiFi.begin(ssid,password);
///Unitl the it connects to the wifi it will print dots.
while(WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
WiFi.mode(WIFI_STA);
///Print that it has connected.
Serial.println("Connected!");
Serial.print("My IP address");
///Print the IP address of the server.
Serial.println(WiFi.localIP());
///On HTTP request for root, provide index.html file
server.on("/", webpage);
server.begin();
///Start WebSocket Serer and assign callback
webSocket.begin();
webSocket.onEvent(onWebSocketEvent);
///UART data
Serial2.begin(9600,SERIAL_8N1, RXp2, TXp2);
}
/**
* @brief
*
*/
void loop() {
webSocket.loop();
server.handleClient();
///Reads the info recieve through the UART port until it
reaches 'a' and then saves it.
String spot1 = Serial2.readStringUntil('a');
///Reads the info recieve through the UART port until it
reaches 'b' and then saves it.
String spot2 = Serial2.readStringUntil('b');
Serial.println(spot1);
Serial.println(spot2);
///Manda la informacion recibida a la funcion que se
encargara de comparar los valores y mandar la info a la
web.
///Sends the info stored in spot1 and spot2 to the function
that compares the values and sends the info to the web.
signal(spot1, spot2);
}
/**
* @brief handle function: send webpage to client
*
*/
void webpage()
{
server.send(200,"text/html", webpageCode);
}
/**
* @brief Called when receiving any WebSocket Message
*
* @param num
* @param type
* @param payload
* @param length
*/
void onWebSocketEvent(uint8_t num, WStype_t type,
uint8_t* payload, size_t length)
{
///Figure out the type of WebSocket event
switch(type)
{
///Client has disconnected
case WStype_DISCONNECTED:
Serial.printf("[%u] Disconnected!\n", num);
break;
///New client has connected
case WStype_CONNECTED:
{
IPAddress ip = webSocket.remoteIP(num);
Serial.printf("[%u] Connection from ", num);
Serial.println(ip.toString());
}
break;
///Echo text message back to client
case WStype_TEXT:
Serial.printf("[%u] Text: %s\n", num, payload);
webSocket.sendTXT(num, payload);
break;
///For everything else: do nothing
default:
break;
}
}
/**
* @brief This function is in charged of compairing the
recieve Strings and sending the signal to the web.
*
* @param spot1 Saves the info of parking 1.
* @param spot2 Saves the info of parking 2.
*/
void signal(String spot1, String spot2)
{
///Compares the information with the string "P2 OC", if
they are equal, save "Occupied" in P2, to then save it in a
string in JSON style to then send it to the website.
if(spot2.compareTo("P2 OC") == 0)
{
p2 = "Occupied";
JSONtxt2 = "{\"p2\":\""+p2+"\"}";
///This function is in charge of sending the info to the
JavaScript.
webSocket.broadcastTXT(JSONtxt2);
}
///Compares the information with the string "P2 F", if
they are equal, save "Free" in P2, to then save it in a string
in JSON style to then send it to the website.
else if(spot2.compareTo("P2 F") == 0)
{
p2 = "Free";
JSONtxt2 = "{\"p2\":\""+p2+"\"}";
///This function is in charge of sending the info to the
JavaScript.
webSocket.broadcastTXT(JSONtxt2);
}
///Compares the information with the string "P1 OC", if
they are equal, save "Occupied" in P1, to then save it in a
string in JSON style to then send it to the website.
if(spot1.compareTo("P1 OC") == 0)
{
p1 = "Occupied";
JSONtxt = "{\"p1\":\""+p1+"\"}";
///This function is in charge of sending the info to the
JavaScript.
webSocket.broadcastTXT(JSONtxt);
}
///Compares the information with the string "P1 F", if they
are equal, save "Free" in P1, to then save it in a string in
JSON style to then send it to the website.
else if(spot1.compareTo("P1 F") == 0)
{
p1 = "Free";
JSONtxt = "{\"p1\":\""+p1+"\"}";
///This function is in charge of sending the info to the
JavaScript.
webSocket.broadcastTXT(JSONtxt);
}
}