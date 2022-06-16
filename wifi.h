#include <WiFi.h>

String wifi = "";
String pwd = "";


void wifi_connect() {
  wifi = readStringFromFile("/wifi.txt");
  pwd = readStringFromFile("/wifi_pwd.txt");

  //Serial.println("Found wifi credentials:");
  //Serial.println(wifi);
  //Serial.println(pwd);

  WiFi.begin(wifi.c_str(), pwd.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("!");
}
