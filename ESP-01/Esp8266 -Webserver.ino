#include <ESP8266WiFi.h>

const char* ssid = "AP-SSID";
const char* password = "AP-PASSWORD";

WiFiServer server(80);
int led = 2;

void setup()
{
  Serial.begin(9600);
  delay(100);

  pinMode(led, OUTPUT);
  digitalWrite(led, 0);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
  }


  server.begin();
  
  Serial.println("");
  delay(1000);
  Serial.println(WiFi.localIP());
}

void loop()

{

Serial.println(WiFi.localIP());
delay(500);
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  //Serial.println("new client");

  while (!client.available())
  {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  // Serial.println(req);

  client.flush();

  //-----------------------------------------
  if (req.indexOf("/q") != -1)
  {
    digitalWrite(led, 1);
  }
  else if (req.indexOf("/u") != -1)
  {
    digitalWrite(led, 0);
  }
  //-----------------------------------------
  client.flush();
  //-----------------------------------------

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += "<head>";
  s += "<meta charset=\"utf-8\">";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  s += "<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>";
  s += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">";
  s += "</head>";

  s += "<div class=\"container\">";
  s += "<h1>Device Control</h1>";
  s += "<div class=\"row\">";

  s += "<div class=\"col-md-2\"><input class=\"btn btn-block btn-lg btn-success\"style=\"font-size:28px;border-radius:100%;height:100px;width:100px;\"type=\"button\" value=\"ON\" onclick=\"on()\"></div>";
  s += "<div class=\"col-md-2\"><input class=\"btn btn-block btn-lg btn-danger\"style=\"font-size:28px;border-radius:100%;height:100px;width:100px;\" type=\"button\" value=\"OFF\" onclick=\"off()\"></div>";
  s += "</div></div>";

  s += "<script>function on() {$.get(\"/q\");}</script>";
  s += "<script>function off() {$.get(\"/u\");}</script>";

  client.print(s);
  delay(1);









}
