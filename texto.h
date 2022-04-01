#include <stdio.h>
#include <string.h>

struct palabra{    
 int dimencion;
 char bar2[785];
};

/*
struct foo fun() {
 struct foo fooObj;
 return fooObj;
}*/
//void delay(int a);

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
