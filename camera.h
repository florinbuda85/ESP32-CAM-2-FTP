#include "esp_camera.h"
#include "esp_timer.h"
#include "img_converters.h"

#include "fb_gfx.h"
#include "fd_forward.h"
#include "fr_forward.h"

bool cameraInit() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer   = LEDC_TIMER_0;
    config.pin_d0       = 5;
    config.pin_d1       = 18;
    config.pin_d2       = 19;
    config.pin_d3       = 21;
    config.pin_d4       = 36;
    config.pin_d5       = 39;
    config.pin_d6       = 34;
    config.pin_d7       = 35;
    config.pin_xclk     = 0;
    config.pin_pclk     = 22;
    config.pin_vsync    = 25;
    config.pin_href     = 23;
    config.pin_sscb_sda = 26;
    config.pin_sscb_scl = 27;
    config.pin_pwdn     = 32;
    config.pin_reset    = -1;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 16;         // 0-63 lower means higher quality
    config.fb_count = 2;

    // camera init
    esp_err_t err = esp_camera_init(&config);

    if (err != ESP_OK) {
        Serial.println("Camera init failed:");
        Serial.println(err);

        return false;
    }

    sensor_t *s = esp_camera_sensor_get();
    s->set_vflip(s, true);
    s->set_hmirror(s, true);

    return true;
}
