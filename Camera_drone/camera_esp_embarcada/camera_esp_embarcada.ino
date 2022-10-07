#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "Base64.h"
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

#define TIME_LIMIT 100

int imgNumber = 0;
long int timeInitial = millis();
const char *ssid = "LAB_ROBOTICA";
const char *password = "UAV1X500";
const char *host = "script.google.com";
String myScript = "/macros/s/AKfycbz7iDncvnFwt6t1I3Ti-KtcFTciWLF2Vck-w8-aL2N3hkBXUDWBOI7KA-46VSQ_W_kO/exec";

String mimeType = "&mimetype=image/jpeg";
String img = "&data=";

void wifiConect(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  int tempoConexao = millis();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);

    
    if((tempoConexao + 20000) < millis()) {
      Serial.println("\nTime limit for conect wifi, restarting ESP");
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
  config.jpeg_quality = 17;
  config.frame_size = FRAMESIZE_VGA;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    ESP.restart();
    return;
  }

  wifiConect(ssid, password);
}

void loop() {
  String nameFile = "&fileName=Bc_" + String(imgNumber) + ".jpg";
  
  if(capImg(nameFile)) {
    imgNumber++;
  }
}

bool capImg(String nameFile) {
  Serial.println("Connecting at " + String(host) + ".");

  WiFiClientSecure client;
  client.setInsecure();

  if(client.connect(host, 443)) {
    Serial.println("Connected with succesfuly.");

    camera_fb_t *fb = nullptr;

    fb = esp_camera_fb_get();

    if(!fb) {
      Serial.println("Image capture failed.");
      delay(1000);
      ESP.restart();
      return false;
    }

    char *input = (char*)fb->buf;
    char output[base64_enc_len(3)];
    String imageFile = "";

    for(int i = 0; i < fb->len; i++) {
      base64_encode(output, (input++), 3);
      if(i % 3 == 0) {
        imageFile += urlEncode(String(output));
      } 
    }

    String Data = nameFile + mimeType + img;

    esp_camera_fb_return(fb);
    
    Serial.println("Sending img for cloud, waiting answer.");
    
    client.println("POST " + myScript + " HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Content-Length: " + String(Data.length() + imageFile.length()));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println();
  
    client.print(Data);
    Serial.println(Data);
    //Serial.println(imageFile);
    
    for(int index = 0; index < imageFile.length(); index += 1000) {
      client.print(imageFile.substring(index, (index + 1000)));
    }

    long int tempoConexao = millis();

    while(!client.available()) {
      Serial.print('.');
      delay(100);
      if((tempoConexao + TIME_LIMIT) < millis()) {
        Serial.println("\nDon't received anser, send failed.\n");
        break;
      }
    }

    Serial.println();
    
    client.stop();
    return true;  
  } else {
    Serial.println("Connection at " + String(host) + " //failed.");
    client.stop();
    return false;
  }
}

String urlEncode(String str) {
  String encodedString = "";
  char c;
  char code0, code1, code2;

  for(int i = 0; i < str.length(); i++) {
      c = str.charAt(i);

      if(c == ' ' || isalnum(c)) {
        encodedString += c;
      } else {
        code1 = (c & 0xf) + '0';
        
        if((c & 0xf) > 9) {
          code1 = (c & 0xf) - 10 + 'A';
        }

        c = (c >> 4) & 0xf;
        code0 = c + '0';

        if(c > 9) {
          code0 = c - 10 + 'A';
        }

        code2 = '\0';
        encodedString += '%';
        encodedString += code0;
        encodedString += code1;
      }

      yield();
  }

  return encodedString;
}
