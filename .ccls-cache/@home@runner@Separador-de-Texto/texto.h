#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int CodigoAnsi(unsigned char caracter);
/*  CodigoAnsi(',') -> 44 
*   te devuelve  el numero de cada ansi (https://elcodigoascii.com.ar/)*/
int encontrarNseparador(const char* origin,int ansi);
/*  encontrarNseparador("ho,la,soy,demo",44) -> 4 
*   el numero de char encontrados*/
int encontrarDchar(const char* origin,int ubicacion,unsigned char caracter);
/*  encontrarDchar("ho,la,soy,demo",2,',')  ->  3  
*    la dimencion del texto en esa posicion   */  
int encontrarUchar(const char* origin,int ubicacion,unsigned char caracter);
/*  encontrarUchar("ho,la,soy,demo",2,',')  ->  6  
*    la ubicaion dentro del texto anterior en esa posicion   */  
const char* encontrarXchar(const char* origin,int ubicacion,unsigned char caracter);
/*  encontrarXchar("ho,la,soy,demo",2,',')  ->  soy  
*    el char en esa posicion en esa posicion   */
int comparar(const char* text1,const char* text2);
/*  comparar("holo","holo")  ->  1
*    1  si dos textos son iguales y 0 si no   */
const char* armarJson(const char* clave,const char* valor);
/*  armarJson("clave","valor") -> {"clave":"valor"}
*    te devuelve un char con el jason armado */
void gps_data_by_gprmc(const char* gprmc,char *hora,char *lat,char *lon,char *fecha);
/*  gps_data_by_gprmc(gprmc,&hora,&lat,&lon,&fecha) -> null
*    te da los valores de hora lat lon fecha como ficheros */
void know_len(const char* restrict name,const char* restrict texto);
/*  know_len("hora",hora); -> :hora: 4 ->hola /hora=hola    
*    te da la variable y su length por consola*/
int calcularjson(const char* restrict name,char* restrict hora,char* restrict lat,char* restrict lon,char* restrict fecha);
/*  int l=calcularjson("GPS",hora,lat,lon,fecha);   
*   te devuelve la cantidad de espacios necesarios para armar el string */
void json_gps_data_by_gprmc(const char* restrict name,char* restrict hora,char* restrict lat,char* restrict lon,char* restrict fecha,char *json);
/*  json_gps_data_by_gprmc("GPS",hora,lat,lon,fecha,&newjson); -> NULL
*    te devuelve el json armado*/




/*
struct palabra{    
 int dimencion;
 char bar2[785];
};

struct foo fun() {
 struct foo fooObj;
 return fooObj;
}*/
//void delay(int a);
