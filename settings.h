#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32


int readIntFromFile(const char * path){
    char c;
    String number;
    fs::FS &fs = SD_MMC;
    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return 0;
    }

    while(file.available()){
        c = file.read();
        number.concat(c);
    }
    return number.toInt();
}

void writeIntToFile(const char * path, int nr){
    fs::FS &fs = SD_MMC;
    File file = fs.open(path, FILE_WRITE);
    
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    
    file.print(nr);
    Serial.println(nr);
}

String readStringFromFile(const char * path){
    char c;
    String str;
    fs::FS &fs = SD_MMC;
    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return "";
    }

    while(file.available()){
        c = file.read();
        str.concat(c);
    }
    return str;
}
