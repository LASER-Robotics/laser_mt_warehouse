#include "esp_camera.h"
#include <WiFi.h>
#include <base64.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#define CAMERA_MODEL_AI_THINKER

#if defined(CAMERA_MODEL_AI_THINKER)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#endif


//const char *ssid = "LAB_ROBOTICA";
//const char *password = "UAV1X500";
const char *ssid = "NTGR_B9CC";
const char *password = "3bKo6A6X";
WiFiClient client;
const char *host = "192.168.0.106";
const int port = 4000;


void wifiConnect(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  int tempoConexao = millis();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);


    if ((tempoConexao + 20000) < millis()) {
      Serial.println("\nTime limit for connect wifi, restarting ESP");
      ESP.restart();
      return;
    }
  }

  Serial.println("\nWifi connected with sucessfuly");
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_SVGA;
  config.jpeg_quality = 14;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    ESP.restart();
    return;
  }

  wifiConnect(ssid, password);

  if (!client.connect(host, port)) {
    Serial.println("client not connected");
    ESP.restart();
  }
}

void loop() {
  capImg();
}


void capImg() {
  Serial.println("Connected with succesfuly.");

  camera_fb_t *fb = esp_camera_fb_get();

  if (!fb) {
    Serial.println("Image capture failed.");
    delay(1000);
    ESP.restart();
    return;
  }

  String imageData = imageEncodeToBase64(fb);
  
  esp_camera_fb_return(fb);
  
  Serial.println("send image for cloud.");
  client.print("[");
  for (int index = 0; index < imageData.length(); index += 1000) {
      client.print(imageData.substring(index, (index + 1000)));
  }
  client.print("]");
}

String imageEncodeToBase64(const camera_fb_t* fb) {
  String encodedImage;
  encodedImage = base64::encode(fb->buf, fb->len);

  return encodedImage;
}
