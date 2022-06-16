#include "settings.h"
#include "camera.h"
#include "wifi.h"
#include "ftp.h"

const char ftp_remote_dir[]   = "/pics";

void setup() {
  
  Serial.begin(115200);
  Serial.println("Serial          [OK]");

  if(!SD_MMC.begin()){
    Serial.println("SD Card Mount Failed");
    return;
  }
  Serial.println("SD Card         [OK]");

  if (cameraInit())
  Serial.println("CAMERA          [OK]");
  
  wifi_connect();
  Serial.println("WIFI            [OK]");

  configure_ftp();
  Serial.println("FTP             [OK]");
  
}

void loop() {
    
    char  ftp_server_c [20];
    char  ftp_user_c [20];
    char  ftp_pass_c [20];

    strcpy (ftp_server_c, ftp_server.c_str());
    strcpy (ftp_user_c, ftp_user.c_str());
    strcpy (ftp_pass_c, ftp_pass.c_str());

    ESP32_FTPClient ftp(ftp_server_c, 21, ftp_user_c, ftp_pass_c, 1000, 2);

    int pictureNumber = readIntFromFile("/picno.txt") + 1;
    delay(1000); // say cheese!!
    
    String path = "pic_" + String(pictureNumber) +".jpg";


    camera_fb_t *fb = NULL;
    fb = esp_camera_fb_get();

    if (!fb) {
        Serial.println("Camera capture failed");
        return;
    }

    delay(500);  // not even sure why... :-/

    ftp.OpenConnection();
    ftp.InitFile("Type I");
    ftp.ChangeWorkDir(ftp_remote_dir);
    ftp.NewFile(path.c_str());
    ftp.WriteData(fb->buf, fb->len);
    ftp.CloseFile();
    

    esp_camera_fb_return(fb);
    
    writeIntToFile("/picno.txt", pictureNumber);
    
    delay(5000);
    delay(5000);
}
