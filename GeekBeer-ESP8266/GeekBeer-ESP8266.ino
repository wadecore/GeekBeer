/*
 *        +-----------------+
 *        | GeekBeer Order! |
 *        +-----------------+
 *            _.._..,_,_
 *           (          )
 *            ]~,"-.-~~[
 *          .=])' (;  ([
 *          | ]:: '    [
 *          '=]): .)  ([
 *            |:: '    |
 *             ~~----~~
 * 
 *  This sketch is for the ESP2866.
 *  Here, we're running a Web Server
 *  that uses a form post to send
 *  serial data to the Geekduino.
 *  The Geekduino Parses the data
 *  and uses it to call on functions.
 * 
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Fill in your WiFi router SSID and password
const char* ssid = "TRNet";
const char* password = "TRbot69u2!";
MDNSResponder mdns;

int val;
int BUSYvalue = 0;


ESP8266WebServer server(80);

const char INDEX_HTML[] =
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
"<title>GeekBeer Order</title>"
"<style>"
".container {"
"    position: absolute;"
"    top: 50%;"
"    left: 50%;"
"    -moz-transform: translateX(-50%) translateY(-50%);"
"    -webkit-transform: translateX(-50%) translateY(-50%);"
"    transform: translateX(-50%) translateY(-50%);"
"}"
"#rcorners {"
"    font-family: Century Gothic;"
"    background: #0f0f0f;"
"    border-radius: 15px;"
"    border: 2px solid #ffffff;"
"    padding: 10px; "   
"    box-shadow: 0 8px 16px 0 rgba(0,0,0,0.7), 0 6px 20px 0 rgba(0,0,0,0.7);"
"}"
".select-style {"
"    border: none"
"    width: 100px;"
"    border-radius: 4px;"
"    overflow: hidden;"
"    background: #ffffff;"
"    display: inline-block;"
"}"
".select-style select {"
"    padding: 5px 8px;"
"    width: 130%;"
"    border: none;"
"    box-shadow: none;"
"    background: transparent;"
"    background-image: none;"
"    -webkit-appearance: none;"
"}"
".select-style select:focus {"
"    outline: none;"
"}"
".button {"
"    border-radius: 4px;"
"    background-color: #4CAF50;"
"    border: none;"
"    color: white;"
"    padding: 5px 8px;"
"    text-align: center;"
"    text-decoration: none;"
"    display: inline-block;"
"    font-family: Century Gothic;"
"    font-size: 20px;"
"    margin: 4px 2px;"
"    cursor: pointer;"
"}"
"</style>"
"<META HTTP-EQUIV=\"refresh\" CONTENT=\"30\">"
"</head>"
"<body background='http://www.designyourway.net/diverse/darkpat/COLOURlovers.com-Gothic_Devine.jpg' text=#ffffff font='Garamound' alink=#fafafa vlink=#fafafa>"
"<div class=\"container\" id=\"rcorners\">"
"    <span>"
"<center>"
"<h1 style=\"text-decoration: underline overline;\">GeekBeer Order</h1>"
"<img src=\"http://icons.iconarchive.com/icons/flat-icons.com/flat/512/Beer-icon.png\" width=\"300\">"
"<FORM action=\"/\" method=\"post\">"
"<br>Get "
"<div class=\"select-style\">"
"<select name=\"NAME\">"
"<option name=\"NAME\" value=\"0\">Matt</option>"
"<option name=\"NAME\" value=\"1\">Rick</option>"
"<option name=\"NAME\" value=\"2\">Kevin</option>"
"<option name=\"NAME\" value=\"3\">Wade</option>"
"</select></div>"
" a "
"<div class=\"select-style\">"
"<select name=\"BEER\">"
"<option name=\"BEER\" value=\"0\">Budweiser</option>"
"<option name=\"BEER\" value=\"1\">Bud Light</option>"
"<option name=\"BEER\" value=\"2\">Rolling Rock</option>"
"</select></div>"
"<br><INPUT type=\"submit\" class=\"button\" value=\"Place Order\">"
"</FORM>"
"</center></span></div>"
"</body>"
"</html>";

const char BUSY_HTML[] =
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
"<title>GeekBeer Order</title>"
"<style>"
".container {"
"    position: absolute;"
"    top: 50%;"
"    left: 50%;"
"    -moz-transform: translateX(-50%) translateY(-50%);"
"    -webkit-transform: translateX(-50%) translateY(-50%);"
"    transform: translateX(-50%) translateY(-50%);"
"}"
"#rcorners {"
"    font-family: Century Gothic;"
"    background: #0f0f0f;"
"    border-radius: 15px;"
"    border: 2px solid #ffffff;"
"    padding: 10px; "   
"    box-shadow: 0 8px 16px 0 rgba(0,0,0,0.7), 0 6px 20px 0 rgba(0,0,0,0.7);"
"}"
".select-style {"
"    border: none"
"    width: 100px;"
"    border-radius: 4px;"
"    overflow: hidden;"
"    background: #ffffff;"
"    display: inline-block;"
"}"
".select-style select {"
"    padding: 5px 8px;"
"    width: 130%;"
"    border: none;"
"    box-shadow: none;"
"    background: transparent;"
"    background-image: none;"
"    -webkit-appearance: none;"
"}"
".select-style select:focus {"
"    outline: none;"
"}"
".button {"
"    border-radius: 4px;"
"    background-color: #4CAF50;"
"    border: none;"
"    color: white;"
"    padding: 5px 8px;"
"    text-align: center;"
"    text-decoration: none;"
"    display: inline-block;"
"    font-family: Century Gothic;"
"    font-size: 20px;"
"    margin: 4px 2px;"
"    cursor: pointer;"
"}"
"</style>"
"<META HTTP-EQUIV=\"refresh\" CONTENT=\"30\">"
"</head>"
"<body background='http://www.designyourway.net/diverse/darkpat/COLOURlovers.com-Gothic_Devine.jpg' text=#ffffff font='Garamound' alink=#fafafa vlink=#fafafa>"
"<div class=\"container\" id=\"rcorners\">"
"    <span>"
"<center>"
"<h1>GeekBot is on a Delivery!</h1>"
"</center></span></div>"
"</body>"
"</html>";

void handleRoot()
{  
  if (server.hasArg("NAME")) 
  {
    handleSubmit();
  }
  else 
  {
    int incoming = Serial.available();  
    if (incoming > 0)
    {
      val = Serial.parseInt();  //Reads integers as integer rather than ASCII. Anything else returns 0
      Serial.println(val);
     
      if (val == 9999)
      {
        BUSYvalue = 0; 
      }
      else if (val == 1111)
      {
        BUSYvalue = 1;
      }
    }
      
    if (BUSYvalue == 0) 
    {
      server.send(200, "text/html", INDEX_HTML);
    }
    else if (BUSYvalue == 1) 
    {
      server.send(200, "text/html", BUSY_HTML);
    }
  }
}

void returnFail(String msg)
{
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(500, "text/plain", msg + "\r\n");
}

void handleSubmit()
{
  String NAMEvalue;
  String BEERvalue;

  if (!server.hasArg("NAME")) return returnFail("BAD ARGS");
  NAMEvalue = server.arg("NAME");
  if (NAMEvalue == "0") 
  {
    Serial.print("70");
    server.send(200, "text/html", BUSY_HTML);
  }
  else if (NAMEvalue == "1") 
  {
    Serial.print("71");
    server.send(200, "text/html", BUSY_HTML);
  }
  else if (NAMEvalue == "2") 
  {
    Serial.print("72");
    server.send(200, "text/html", BUSY_HTML);
  }
  else if (NAMEvalue == "3") 
  {
    Serial.print("73");
    server.send(200, "text/html", BUSY_HTML);
  }
  else {
    returnFail("Bad NAME value");
  }

  if (!server.hasArg("BEER")) return returnFail("BAD ARGS");
  BEERvalue = server.arg("BEER");
  if (BEERvalue == "0") 
  {
    Serial.print("80");
    server.send(200, "text/html", BUSY_HTML);
  }
  else if (BEERvalue == "1") 
  {
    Serial.print("81");
    server.send(200, "text/html", BUSY_HTML);
  }
  else if (BEERvalue == "2") 
  {
    Serial.print("82");
    server.send(200, "text/html", BUSY_HTML);
  }
  else {
    returnFail("Bad BEER value");
  }
  returnOK();
}

void returnOK()
{
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OK\r\n");
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void)
{

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("GeekBeer", WiFi.localIP())) 
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.print("Connect to http://esp8266WebForm.local or http://");
  Serial.println(WiFi.localIP());
}

void loop(void)
{
  server.handleClient();
}
