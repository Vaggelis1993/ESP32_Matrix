//Wi-Fi Configuration
const char* ssid   = "replace_me";
const char* pass   = "replace_me";
//**********************************************************

AsyncWebServer Server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    Text: <input type="text" name="Text">
    <input type="submit" value="Submit">
 </form>
</body></html>)rawliteral";

void WiFi_Connection() {
  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid);                   // print the network name (SSID);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

//NTP Configuration
void NTP_Server() {
#define TZ (9*60*60)
  configTime(TZ, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp"); // enable NTP
  const long  gmtOffset_sec = 3600;
  const int   daylightOffset_sec = 3600;
  const char* ntpServer = "pool.ntp.org";
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String inputParam;                    // variables from scrolling text
const char* PARAM_INPUT_1 = "Text";

void AsyncWebServer1() {
  // Send web page with input fields to client
  Server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  Server.on("/get", HTTP_GET, [] (AsyncWebServerRequest * request) {

    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }

    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);

    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field ("
                  + inputParam + ") with value: " + inputMessage +
                  "<br><a href=\"/\">Return to Home Page</a>");
  });
  Server.onNotFound(notFound);
}
