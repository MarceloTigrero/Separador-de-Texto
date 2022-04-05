
#include "texto.h"

int main() {
  //    desde el modulo gps gtu7 
  //$GPRMC,173225.00,A,0208.77699,S,07954.27105,W,0.871,,040422,,,A*73
  char gprmc[100]="$GPRMC,173225.00,A,0208.77699,S,07954.27105,W,0.871,,040422,,,A*73\0";
  char hora[12];
  char lat[12];
  char lon[13];
  char fecha[8];
  gps_data_by_gprmc(gprmc,&hora,&lat,&lon,&fecha);
  int l=calcularjson("GPS",hora,lat,lon,fecha);
  char* newjson;
  newjson = (char*)malloc (l*sizeof(char) );
  json_gps_data_by_gprmc("GPS",hora,lat,lon,fecha,&newjson);
  printf(" %s ",&newjson);
  return 0;
}

/*
  //uint8_t* data_gps = (uint8_t*) malloc(1024+1);
  //uint8_t data_gps;
  //int8_t
  char gprmc[100]="$GPRMC,173225.00,A,0208.77699,S,07954.27105,W,0.871,,040422,,,A*73\0";
  //know_len("gprmc",gprmc);
  char hora[12];
  char lat[12];
  char lon[13];
  char fecha[8];
  //printf(" ------------------------------------------------------\n");
  gps_data_by_gprmc(gprmc,&hora,&lat,&lon,&fecha);
  //know_len("hora",hora);
  //know_len("lat",lat);
  //know_len("lon",lon);
  //know_len("fecha",fecha);
  int l=calcularjson("GPS",hora,lat,lon,fecha);
  //printf(":l: %i  \n",l);
  char* newjson;
  newjson = (char*)malloc (l*sizeof(char) );
  //char newjson[l];
  //newjson = (char*)malloc (l*sizeof(char) );
  //printf(" ------------------------------------------------------\n");
  //rintf(" ------------------------------------------------------\n");
  json_gps_data_by_gprmc("GPS",hora,lat,lon,fecha,&newjson);
  //know_len("newjson",newjson);
  printf(" %s ",&newjson);
*/

//know_len("newjson",newjson);
  //know_len("hora",hora);
  //know_len("lat",lat);
  //know_len("lon",lon);
  //know_len("fecha",fecha);
//know_len("newjson",newjson);
  //printf(" ------------------------------------------------------\n");
  //know_len("hora",hora);
  //know_len("lat",lat);
  //know_len("lon",lon);
  //know_len("fecha",fecha);
  //know_len("newjson",newjson);
  //free(newjson);
  /*
  #include <stdlib.h>

  int* ptr;
  int* ptr2;
  ptr = (int*)malloc ( 300*sizeof(int) );
  ptr[33] = 15;
  rellena_de_ceros (10,ptr);
  ptr2 = ptr + 15;
  free(ptr);	
  */
  /*
  int l = encontrarDchar(gprmc,0,',');
  printf(" %i\n",l);
  char dato[l];
  strcpy(dato,encontrarXchar(gprmc,0,','));
  printf(" %s\n",dato);
  int d =comparar("$GPRMC\0",dato);
  printf(" %i\n",d);
  */
  //encontrarXchar(
  //printf("val2 %s\n",gprmc);
  //int l = encontrarDchar(val2,1,' ');
  //printf(" %i\n",l);
  //char dato[l];
  //strcpy(dato,encontrarXchar(val2,1,' '));
  //printf(" %s\n",dato);
  //printf("json %s\n",armarJson("clave\0",dato));

  
  /*    desde la sim
  char val[12]="+CIPGSMLOC:\0";
  char val2[52]="+CIPGSMLOC: 0,0.000000,0.000000,2022/03/14,21:58:02\0";
  char val5[12]="+CIPGSMLOC:\0";
  printf("val %s\n",val);
  printf("val2 %s\n",val2);
  int l = encontrarDchar(val2,1,' ');
  printf(" %i\n",l);
  char dato[l];
  strcpy(dato,encontrarXchar(val2,1,' '));
  printf(" %s\n",dato);
  printf("json %s\n",armarJson("clave\0",dato));
  */



  
  //printf("     000000000011111111112222222222333333333344444444445555555555\n");
  //printf("     012345678901234567890123456789012345678901234567890123456789\n");
  
  /*
  int l = encontrarDchar(val2,1,' ');
  printf(" %i\n",l);
  char dato[l];
  strcpy(dato,encontrarXchar(val2,1,' '));
  printf(" %s\n",dato);
  char json[11+l];
  strcpy(json,"{\"ubi\":\"");
  for(int i=0;i<l+1;i++)
  {
    json[8+i]=dato[i];
  }
  json[l+9] =34;//"
  json[l+10] =125;//}
  json[l+11] ='\0';//}
  
  printf(" %s\n",json);
  printf(":json: %i %s\n",strlen(json),json);
  printf(" %s\n",val);
  printf(" %s\n",val2);
  printf(" %s\n",dato);
*/

  //printf(":eyes: %i %s\n",encontrarDchar(json,0,' '),encontrarXchar(json,0,' '));
  
  //char dato[l] = encontrarXchar(val2,1,' ');
  /*
  printf(":eyes: %i %s\n",encontrarDchar(val2,1,' '),encontrarXchar(val2,1,' '));
  printf(" %s\n",val);
  printf(" %s\n",val2);
  */
  
/*
  int l = encontrarDchar(val2,1,' ');
  char dato[l] = encontrarXchar(val2,1,' ');
  printf(":eyes: %i %s\n",l,dato);
  char json[10+l] = "{\"ubi\":\"";
  for(int i=0;i<l;i++)
  {
    json[8+i]=dato[i];
  }
  json[l+9] =34;//"
  json[l+10] =125;//}

  printf(":json: %i %s\n",strlen(json),json);
  */

  /*
  char newstr[11]="";
  char oldstr[44]="";//44
  char objs[50]="{\"ubi\":\"";
  for(int i=0;i<55;i++)
  {
    if(val[i]==val2[i])
    {
      oldstr[i] = val2[i];
    }else{
      newstr[i-11]  = val2[i+1];
      objs[i-3]  = val2[i+1];
    }
  }
  objs[47] =34;//"
  objs[48] =125;//}
  printf("old %s\n",oldstr);
  printf("new %s\n",newstr);
  printf("objs %s\n",objs);
  //const int len = strlen(objs);
  printf("lenob %i\n",strlen(objs));
  printf("hola lol,o %i\n",encontrarNseparador("hola lol",CodigoAnsi('o')));
  printf("objs,, %i\n",encontrarNseparador(objs,CodigoAnsi(',')));
  printf("objs %s\n",objs);
  printf("     000000000011111111112222222222333333333344444444445555555555\n");
  printf("     012345678901234567890123456789012345678901234567890123456789\n");
  int al = 0;
  printf("Dobjs %i\n",encontrarDchar(objs,4,','));
  printf(":eyes: %i %s\n",encontrarDchar(objs,3,','),encontrarXchar(objs,3,','));
  printf(":json: %s\n",armarJson("ubi",encontrarXchar(objs,3,',')));
  */
  /*
  char* hora;
  hora= (char*)malloc (12*sizeof(char));
  char* lat;
  lat= (char*)malloc (12*sizeof(char));
  char* lon;
  lon= (char*)malloc (13*sizeof(char));
  char* fecha;
  fecha= (char*)malloc (8*sizeof(char));
  */