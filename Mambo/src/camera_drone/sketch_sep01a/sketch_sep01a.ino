/* 
Programa da câmera IP baseado no programa original desenvolvido por Rui Santos
 
  IMPORTANTE!!! 
   - Em Placa selecione "ESP32 Wrover Module"
   - Em Partion Scheme selecione "Huge APP (3MB No OTA)"
   - Para carregar o código é necessário que o GPIO 0 esteja conectado ao GND
*/
 
#include "esp_camera.h"
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
 
#define PART_BOUNDARY "123456789000000000000987654321"
 
// Configuração do modelo de câmera (CAMERA_MODEL_AI_THINKER)
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

ESPino32Cam cam;

//Configuração da rede WiFi
const char* ssid = "LAB_ROBOTICA";
const char* password = "UAV1X500";

void WifiConnect(string ssid, string password) {
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("/nWifi conected./n")/
}



void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  
  Serial.begin(115200);
  Serial.setDebugOutput(false);
   
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
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 20;
  config.fb_count = 1;
   
  // Iniciação da câmera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  
  // Conexão WiFi
  WifiConnect(ssid, password);
   
  // Início da transmissão no servidor Web
  Serial.print("Camera Stream Ready! Go to: http://");
  Serial.print(WiFi.localIP());

  tempoAnt = tempoPos = millis();
}
 
void loop() {
  if((tempoAnt - tempoPos) <= 100000) {
    camera_fb_t *fb = NULL;
    fb = camera_fb_get();
     
  }
}
