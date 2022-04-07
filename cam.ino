#include "Arduino.h"
#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <base64.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <HardwareSerial.h>

#define CAMERA_MODEL_AI_THINKER

//CAMERA_MODEL_AI_THINKER
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

HardwareSerial SerialGSM(1);
const char* ssid = "TIMOS";
const char* password = "Timos2o2o.";

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  SerialGSM.begin(115200);//serial1
  protocoloweb();
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
  
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(psramFound()){
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
/*
#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif
*/
  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

/*
  #if defined(CAMERA_MODEL_M5STACK_WIDE)
    s->set_vflip(s, 1);
    s->set_hmirror(s, 1);
  #endif
*/
/*
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  */
  //classifyImage();
  //Serial.println("\nSleep....");
  //esp_deep_sleep_start();
}

void loop(){
  delay(10000);
  classifyImage();
}

void classifyImage() {
  String response;
  // Capture picture
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  if(!fb) {
    Serial.println("Camera capture failed");
    return;
  } else {
    Serial.println("Camera capture OK");
  }
  size_t size = fb->len;
  String buffer = base64::encode((uint8_t *) fb->buf, fb->len);
  String imgPayload = "{\"base64\": \"" + buffer + "\"}\r\0";//\n
  
  buffer = "";
  // Uncomment this if you want to show the payload
  Serial.println(imgPayload);
  postweb(imgPayload);
  
  esp_camera_fb_return(fb);
  // Generic model
  String model_id = "General";


///////////  HTTPClient http;
/////////  http.begin("http://dev--timoscontrolaforo.timospro.autocode.gg/" /+ model_id + "/outputs"/);
/**/
/*
  http.addHeader("Content-Type", "application/json");     
  http.addHeader("Authorization", "c7f894790533332388e23d4d21278321"); 
  int httpResponseCode = http.POST(imgPayload);
  if(httpResponseCode>0){
    Serial.print(httpResponseCode);
    Serial.print(" Returned String: ");
    Serial.println(http.getString());
  } else {      
    Serial.print("POST Error: ");
    Serial.print(httpResponseCode);
  }                      
  // Parse the json response: Arduino assistant
  const int jsonSize = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(20) + 3*JSON_OBJECT_SIZE(1) + 6*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 20*JSON_OBJECT_SIZE(4) + 2*JSON_OBJECT_SIZE(6);  
  StaticJsonDocument<jsonSize> doc;
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, response); 
  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }  
  Serial.println(jsonSize);
  Serial.println(response);
  for (int i=0; i < 10; i++) {
//    const name = doc["outputs"][0]["data"]["concepts"][i]["name"];
//    const float p = doc["outputs"][0]["data"]["concepts"][i]["value"];
    const char* name = doc["outputs"][0]["data"]["concepts"][i]["name"];
    const char* p = doc["outputs"][0]["data"]["concepts"][i]["value"];    
    Serial.println("=====================");
    Serial.print("Name:");
    Serial.println(name[i]);
    Serial.print("Prob:");
    Serial.println(p);
    Serial.println();
  }
  */
}


void protocoloweb()
{
  
  Serial.println("Iniciando... protocolo web"); 
  delay(2000);

  SerialGSM.write("AT\r");
  serialCheck(500);
 
  SerialGSM.write("AT+CGATT?\r");
  serialCheck(500);

  SerialGSM.write("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r");
  serialCheck(500);
  
  SerialGSM.write("AT+SAPBR=3,1,\"APN\",\"internet.claro.com.ec\"\r");
  serialCheck(500);

  SerialGSM.write("AT+SAPBR=1,1\r");
  serialCheck(500);
}

void serialCheck(int espera)
{
  while (Serial.available()) 
  {
    SerialGSM.write(Serial.read());
  }
  while(SerialGSM.available()) 
  {
    Serial.write(SerialGSM.read());
  }
  delay(espera);
}
void postweb(String texto)
{
  Serial.println("Iniciando... post web"); 
  delay(2000);

  SerialGSM.write("AT+HTTPINIT\r");
  serialCheck(500);
 
  SerialGSM.write("AT+HTTPPARA=\"CID\",1\r");
  serialCheck(500);

  SerialGSM.write("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r");
  serialCheck(500);
  
  SerialGSM.write("AT+HTTPPARA=\"URL\",\"http://dev--timoscontrolaforo.timospro.autocode.gg/\"\r");
  serialCheck(500);

  SerialGSM.write("AT+HTTPPARA=\"CONTENT\",\"application/json\"\r");
  serialCheck(500);

  SerialGSM.write("AT+HTTPDATA=10000,10000\r");
  serialCheck(200);
  
  //SerialGSM.write("{\"ubi\":\"-2.146283,-79.804327\",\"dt\":\"02/30/2022,10:15:05\"}\r");
  int l =texto.length();
  char pay[l];
  texto.toCharArray(pay,l);
  SerialGSM.write(pay);
  serialCheck(10500);
  
  SerialGSM.write("AT+HTTPACTION=1\r");
  serialCheck(500);
  
  SerialGSM.write("AT+HTTPREAD\r");
  serialCheck(500);
  
  SerialGSM.write("AT+HTTPTERM\r");
  serialCheck(500);
}