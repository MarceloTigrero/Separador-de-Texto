#include "texto.h"
void gps_data_by_gprmc(const char* gprmc,char *hora,char *lat,char *lon,char *fecha){
  if(comparar("$GPRMC\0",encontrarXchar(gprmc,0,','))){
    strcpy(hora,encontrarXchar(gprmc,1,','));    
    strcpy(lat,encontrarXchar(gprmc,3,','));
    strcpy(lon,encontrarXchar(gprmc,5,','));
    strcpy(fecha,encontrarXchar(gprmc,9,','));
    hora[9]='\0';
    lat[10]='\0';
    lon[11]='\0';
    fecha[6]='\0';
  }
}
void know_len(const char* restrict name,const char* restrict texto){
  printf(":%s: %i  %s\n",name,strlen(texto),texto);
}
void calcularjson(const char* restrict name,char* restrict hora,char* restrict lat,char* restrict lon,char* restrict fecha,int *l){
  
  l=strlen(name)+strlen(hora)+strlen(lat)+strlen(lon)+strlen(fecha)+1+2+1+2+1+1;
  printf(":: %i  \n",l);
}
int calcularjson2(const char* restrict name,char* restrict hora,char* restrict lat,char* restrict lon,char* restrict fecha){ 
  return strlen(name)+strlen(hora)+strlen(lat)+strlen(lon)+strlen(fecha)+1+2+1+2+1+1;
  //printf(":: %i  \n",l);
}
void json_gps_data_by_gprmc(const char* restrict name,char* restrict hora,char* restrict lat,char* restrict lon,char* restrict fecha,int l,char *json){
  int j;
  json[0]='{';j++;
  json[1]='"';j++;
  for(int i=0;i<strlen(name);i++){
    json[j+i]=name[i];
  }
  know_len("json",json);
  j+=strlen(name);
  json[j]='"';j++;
  json[j]=':';j++;
  json[j]='"';j++;
  for(int i=0;i<strlen(hora);i++){
    json[j+i]=hora[i];
  }
  know_len("json",json);
  j+=strlen(hora);
  json[j]=',';j++;
  for(int i=0;i<strlen(lat);i++){
    json[j+i]=lat[i];
  }
  know_len("json",json);
  j+=strlen(lat);
  json[j]=',';j++;
  for(int i=0;i<strlen(lon);i++){
    json[j+i]=lon[i];
  }
  know_len("json",json);
  j+=strlen(lon);
  json[j]=',';j++;
  for(int i=0;i<strlen(fecha);i++){
    json[j+i]=fecha[i];
  }
  know_len("json",json);
  j+=strlen(fecha);
  json[j]='"';j++;
  json[j]='}';j++;
  json[j]='\0';
  know_len("json",json);
}
int main() {

  //    desde el modulo gps gtu7 
  //$GPRMC,173225.00,A,0208.77699,S,07954.27105,W,0.871,,040422,,,A*73
  //uint8_t* data_gps = (uint8_t*) malloc(1024+1);
  //uint8_t data_gps;
  char gprmc[100]="$GPRMC,173225.00,A,0208.77699,S,07954.27105,W,0.871,,040422,,,A*73\0";
  know_len("gprmc",gprmc);
  char hora[10];
  char lat[11];
  char lon[12];
  char fecha[7];
  printf(" ------------------------------------------------------\n");
  gps_data_by_gprmc(gprmc,&hora,&lat,&lon,&fecha);
  know_len("hora",hora);
  know_len("lat",lat);
  know_len("lon",lon);
  know_len("fecha",fecha);
  //printf(" %s\n",hora);
  //printf(" %s\n",lat);
  //printf(" %s\n",lon);
  //printf(" %s\n",fecha)
  int l;
  printf(":: %i  \n",calcularjson2("GPS",hora,lat,lon,fecha));
  calcularjson("GPS",hora,lat,lon,fecha,&l);
  printf(":: %i  \n",l);
  char newjson[calcularjson2("GPS",hora,lat,lon,fecha)];
  
  printf(" ------------------------------------------------------\n");
  know_len("newjson",newjson);
  printf(" ------------------------------------------------------\n");
  json_gps_data_by_gprmc("GPS\0",hora,lat,lon,fecha,l,&newjson);
  know_len("newjson",newjson);
  
  
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
  
  return 0;
}
