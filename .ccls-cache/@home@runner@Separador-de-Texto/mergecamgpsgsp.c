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

//const char* ssid = "TIMOS";
//const char* password = "Timos2o2o.";

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
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
  
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality  //for larger pre-allocated frame buffer.
  if(psramFound()){
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  SerialGSM.begin(115200);
  while(!SerialGSM){;}
  protocoloweb();
}

void loop(){//delay(10000);
  //protocologpsopen();
  String ubicacion = obtenerubicacion();
  //protocoloclose();
  Serial.println(ubicacion);
  
  String picture =classifyImage();
  Serial.println(picture);
  //protocoloweb();
    
  //protocoloweb();
  postweb(picture,ubicacion);
  //protocoloclose();
  
  picture = "";
  ubicacion = "";
  
  //Serial.print(":jsonfinal:");Serial.print(respuesta);Serial.println(":cierre:");
  //delay(500);
  
}

String classifyImage() {
  String response;
  // Capture picture
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  if(!fb) {
    Serial.println("Camera capture failed");
    return "Camera capture failed";
  } else {
    Serial.println("Camera capture OK");
  }
  size_t size = fb->len;
  String buffer = base64::encode((uint8_t *) fb->buf, fb->len);
  String imgPayload = "\"base64\":\""+ buffer+"\"}\r\0";//\n
  buffer = "";
  /*
  //Serial.println(imgPayload);
  protocologpsopen();
  String ubicacion =obtenerubicacion();
  protocoloclose();
  //Serial.print(":jsonfinal:");Serial.print(respuesta);Serial.println(":cierre:");
  //delay(500);
  protocoloweb();
  postweb(imgPayload,ubicacion);
  protocoloclose();
  imgPayload = "";
  ubicacion = "";
  */
  esp_camera_fb_return(fb);
  // Generic model
  String model_id = "General";
  return imgPayload;
}

void protocologpsopen()
{
  Serial.println("Iniciando... protocolo gps");delay(2000);
  
  SerialGSM.write("AT\r");serialCheck(500);
  SerialGSM.write("AT+CGATT?\r");serialCheck(500);
  SerialGSM.write("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r");serialCheck(500);
  SerialGSM.write("AT+SAPBR=3,1,\"APN\",\"internet.claro.com.ec\"\r");serialCheck(500);
  SerialGSM.write("AT+SAPBR=1,1\r");serialCheck(500);
  SerialGSM.write("AT+SAPBR=2,1\r");serialCheck(500);
}
void protocoloclose()
{
  SerialGSM.write("AT+SAPBR=0,1\r");serialCheck(500);
  Serial.println("Cerrando... protocolo gps");delay(2000);
}
void protocoloweb()
{
  Serial.println("Iniciando... protocolo web");delay(2000);
  
  SerialGSM.write("AT\r");serialCheck(500);
  SerialGSM.write("AT+CGATT?\r");serialCheck(500);
  SerialGSM.write("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r");serialCheck(500);
  SerialGSM.write("AT+SAPBR=3,1,\"APN\",\"internet.claro.com.ec\"\r");serialCheck(500);
  SerialGSM.write("AT+SAPBR=1,1\r");serialCheck(500);
}

void serialCheck(int espera)
{
  while(Serial.available()){
    SerialGSM.write(Serial.read());
  }
  while(SerialGSM.available()){
    Serial.write(SerialGSM.read());
  }
  delay(espera);
}
void postweb(String image,String Gps)
{
  Serial.println("Iniciando... post web"); delay(2000);
  
  SerialGSM.write("AT+HTTPINIT\r");serialCheck(500);
  SerialGSM.write("AT+HTTPPARA=\"CID\",1\r");serialCheck(500);
  SerialGSM.write("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r");serialCheck(500);
  SerialGSM.write("AT+HTTPPARA=\"URL\",\"http://dev--timoscontrolaforo.timospro.autocode.gg/\"\r");serialCheck(500);
  SerialGSM.write("AT+HTTPPARA=\"CONTENT\",\"application/json\"\r");serialCheck(500);
  SerialGSM.write("AT+HTTPDATA=10000,10000\r");serialCheck(500);
  
  String json ;
  json.concat(Gps);
  json.concat(image);
  int l =json.length();
  char pay[l];
  json.toCharArray(pay,l);
  Serial.println(pay);
  json="";
  
  SerialGSM.write(pay);serialCheck(10500);
  SerialGSM.write("AT+HTTPACTION=1\r");serialCheck(500);
  SerialGSM.write("AT+HTTPREAD\r");serialCheck(500);
  SerialGSM.write("AT+HTTPTERM\r");serialCheck(500);
}

String obtenerubicacion()
{
  String valor,texto;
  int datoscorrectos=1;
  do {
    SerialGSM.write("AT+CIPGSMLOC=1,1\r");Serial.println("atsend");
    while (SerialGSM.available()>0)
    {
      texto = SerialGSM.readString();//valor.concat(SerialGSM.readString());
    }
    String str1 = Separador(texto,'\n',1);
    if ((str1.compareTo("ERROR")==0)||(str1.compareTo("")==0)||(str1.compareTo("AT+CIPGSMLOC=1,1")==0)){
      Serial.print(":recaptura de datos:");Serial.println(str1);
      //delay(1000);
      serialCheck(2000);
      //SerialGSM.write("AT+CIPGSMLOC=1,1\r");  
    }else{
      if( (Separador(str1,' ',0).compareTo("+CIPGSMLOC:"))==0){
        //(latitud.compareTo("0.00000")==0)||(latitud.compareTo("")==0)||(longitud.compareTo("0.00000")==0)||(longitud.compareTo("")==0)
        //String latitud = Separador(str1,',',1);
        //String longitud = Separador(str1,',',2);
        
        if((Separador(str1,',',1).compareTo("0.00000")==0)||(Separador(str1,',',1).compareTo("")==0)||(Separador(str1,',',2).compareTo("0.00000")==0)||(Separador(str1,',',2).compareTo("")==0)){
          Serial.print(":data no valida:");Serial.print(str1);Serial.println(":cierre:");
        }else{
          Serial.print(":data valida:");;Serial.print(str1);Serial.println(":cierre:");
        }
        datoscorrectos=0;texto=str1;
      } 
    }
  }while (datoscorrectos);
  
  valor= "{\"ubi\":\"";
  Serial.print(":información recogida:");Serial.print(texto);Serial.println(":cierre:");
  //String str1 = Separador(texto,'\n',1);//texto = SerialGSM.readString();//Serial.print(":recogida doble:");Serial.print(texto);Serial.println(":cierre:");
  valor.concat(Separador(texto,' ',1));//serialCheckubi(2000);//valor.concat(texto);//postubicacion.concat(ubicacion);
  valor.concat("\",");
  //Serial.print(":json:");Serial.print(valor);Serial.println(":before:");  
  return valor;
}

String Separador(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

  
/************************************linkografia************************************
 * https://www.elecrow.com/wiki/images/2/20/SIM800_Series_AT_Command_Manual_V1.09.pdf
 * 
 *
 *
 */