#include "ESP32_FTPClient.h"

String ftp_server = "";
String ftp_port = "";
String ftp_user = "";
String ftp_pass = "";

void configure_ftp() {

  ftp_server = readStringFromFile("/ftp_server.txt");
  ftp_port = readStringFromFile("/ftp_port.txt");
  ftp_user = readStringFromFile("/ftp_user.txt");
  ftp_pass = readStringFromFile("/ftp_pass.txt");
  
}
