#include <HardwareSerial.h>
//#include <String.h>
//#include <Arduino.h>
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
*/


unsigned long respuesta;
String ubicacion;
//unsigned long ubicacion;
String postubicacion;

HardwareSerial SerialGSM(1);



void setup()
{
  Serial.begin(115200);//serial0
  while(!Serial)
  {
    ;
  }
  SerialGSM.begin(38400);//serial1
  protocoloweb();
}
 


void loop()
{
   
   ///obtenerubicacion();
   //String respuesta =obtenerubicacion();
   //Serial.println(":eyes:");
   //Serial.println(respuesta);
   //Serial.println(":???:");
   //delay(500);
   postweb();
   delay(3000);
}
void postweb()
{
  Serial.println("informacion de ubicacion y hora"); 
  delay(2000);
  
  char pay[100];
  String respuesta =obtenerubicacion();
  respuesta.toCharArray(pay,100);
  
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
  SerialGSM.write("AT+HTTPDATA=10000,10000\r");
  serialCheck(200);
  
  //SerialGSM.write("{\"ubi\":\"-2.146283,-79.804327\",\"dt\":\"02/30/2022,10:15:05\"}\r");
  /*
  char pay[100];
  String respuesta =obtenerubicacion();
  respuesta.toCharArray(pay,100);
  */
  SerialGSM.write(pay);
  serialCheck(10500);
  
  SerialGSM.write("AT+HTTPACTION=1\r");
  serialCheck(500);
  
  SerialGSM.write("AT+HTTPREAD\r");
  serialCheck(500);
  
  SerialGSM.write("AT+HTTPTERM\r");
  serialCheck(500);
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



void serialCheckubi(int espera)
{
  char respuesta[100];
  
  while (Serial.available()) 
  {
    SerialGSM.write(Serial.read());
  }
  while(SerialGSM.available()) 
  {
    //respuesta[x] = Serial.read();
    //ubicacion = SerialGSM.read();
    Serial.write(SerialGSM.read());
    ubicacion = Serial.read();
  }
  delay(espera);
  /*
     x = 0;
     anterior = millis();

     // Este bucle espera la respuesta
     do{
       if(Serial.available() != 0){    // Si hay datos en el búfer de entrada de UART, léalo y verifica la respuesta
          respuesta[x] = Serial.read();
//          Serial.print(respuesta[x]);
          x++;
        if (strstr(respuesta, respEsperada) != NULL) {   //Verificar si la respuesta deseada (OK) 
          responde = true;                               //está en la respuesta del módulo
         }
       }
     }while((!responde) && ((millis() - anterior) < retardo));
 */
}

  
String obtenerubicacion()
{
  //String valor;
  String valor,texto;
  SerialGSM.write("AT+CIPGSMLOC=1,1\r");
  valor= "{\"ubi\":\"";

  while (SerialGSM.available()>0)
  {
    texto = SerialGSM.readString();
    //valor.concat(SerialGSM.readString());//texto = SerialGSM.readString();
  }
  /*
  int l =texto.length();
  char prueba[l];
  texto.toCharArray(prueba,l);
  l = encontrarDchar(prueba,1,'\n');
  char dato[l];
  strcpy(dato,encontrarXchar(prueba,1,'\n'));
  texto="";
  texto=String(texto+dato);
  */
  valor.concat(Separador(texto,'\n',1));
  //serialCheckubi(2000);//valor.concat(texto);//postubicacion.concat(ubicacion);
  valor.concat("\"}\r"); 
  Serial.println(":eyes:");
  Serial.println(valor);
  Serial.println(":???:");
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
/*
void lecturaGMS()
{
  if (SerialGSM.available()>0)
  {
    Serial.write(SerialGSM.read());
  }  
}*/




/*
int CodigoAnsi(unsigned char caracter)
{
  for(int i=0;i<127;i++)//255
  {
    if(caracter==i)
    {
      return i;
    }else{
      if(126==i)
      { 
        return 0;
      }
    }
  }
}

int encontrarNseparador(const char* origin,int ansi)
{
  const int len = strlen(origin);
  int encontrado=0;
  for(int i=0;i<len+1;i++)
  {
    if(origin[i]==ansi)
    {
      encontrado++;
    }
  }
  return encontrado;
}

int encontrarDchar(const char* origin,int ubicacion,unsigned char caracter)
{
  int ansi =CodigoAnsi(caracter);
  const int len = strlen(origin);
  int encontrado=0;
  int dimencion[encontrarNseparador(origin,ansi)];
  int ubi[encontrarNseparador(origin,ansi)-1];
  for(int i=0;i<len-1;i++)
  {
    if(i==0){dimencion[encontrado]=0;}
    if(origin[i]==ansi)
    {
      ubi[encontrado]=i+1;
      encontrado++;
      dimencion[encontrado]=0;
    }else{
      dimencion[encontrado]+=1;
    }
  }
  return dimencion[ubicacion];
}

int encontrarUchar(const char* origin,int ubicacion,unsigned char caracter)
{
  int ansi =CodigoAnsi(caracter);
  const int len = strlen(origin);
  int encontrado=0;
  int dimencion[encontrarNseparador(origin,ansi)];
  int ubi[encontrarNseparador(origin,ansi)-1];
  for(int i=0;i<len-1;i++)
  {
    if(i==0){dimencion[encontrado]=0;}
    if(origin[i]==ansi)
    {
      ubi[encontrado]=i+1;
      encontrado++;
      dimencion[encontrado]=0;
    }else{
      dimencion[encontrado]+=1;
    }
  }
  if(ubicacion == 0)
  {
    return 0;
  }else{
    return ubi[ubicacion-1];
  }
}

const char* encontrarXchar(const char* origin,int ubicacion,unsigned char caracter)
{
  int ansi = CodigoAnsi(caracter);
  int dim=encontrarDchar(origin,ubicacion,ansi);
  int ubi=encontrarUchar(origin,ubicacion,ansi);
  char word[dim];
  for(int i=0;i<=dim;i++)
  { 
    word[i]=origin[ubi+i];
    if(word[i]==ansi)
    {
      word[i]='\0';
    }
  }
  return word;
}
*/