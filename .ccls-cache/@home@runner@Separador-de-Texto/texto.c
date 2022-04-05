#include "texto.h"

/*
void delay(int a)
{
	int add;
	int time;
	int i;

	time= a *1000000000;
	for(i=0;i<time;i++)
	{
		add*=i;
		add++;
		add++;
	}
}*/

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

int comparar(const char* text1,const char* text2)
{
  int l,menor;
  if(strlen(text1)<strlen(text2))
  {
    menor=1;
  }else if(strlen(text1)>strlen(text2)){
    menor=2;
  }else{
    menor=0;
  }
  if(menor==2){l=strlen(text1);}else{l=strlen(text2);}
  for(int i=0;i<l;i++)
  {
    if (i<strlen(text1)&&i<strlen(text2))
    {  
      if(CodigoAnsi(text1[i])!=CodigoAnsi(text2[i]))
      {  
        return 0;
      }
    }else{
      if(menor==2)
      {  
        if(CodigoAnsi(text1[i])!=CodigoAnsi(' '))
        {  
          return 0;
        }
      }else{
        if(CodigoAnsi(text2[i])!=CodigoAnsi(' '))
        {  
          return 0;
        }
      }
    }
  }
  return 1;
}

const char* armarJson(const char* clave,const char* valor)
{
  const int lenClave = strlen(clave);
  const int lenValor = strlen(valor);
  char word[lenClave+lenValor+8];
  word[0] = CodigoAnsi('{');
  word[1] = CodigoAnsi('"');
  for(int i=0;i<lenClave;i++)
  {
      word[2+i] = clave[i];
  }
  word[lenClave+2] = CodigoAnsi('"');
  word[lenClave+3] = CodigoAnsi(':');
  word[lenClave+4] = CodigoAnsi('"');
  for(int i=0;i<lenValor;i++)
  {
    word[lenClave+5+i] = CodigoAnsi(valor[i]);
  }
  word[lenClave+lenValor+5] = CodigoAnsi('"');
  word[lenClave+lenValor+6] = CodigoAnsi('}');
  word[lenClave+lenValor+7] ='\0';
  printf(":word: %i %s\n",strlen(word),word);
  return word;
}

void gps_data_by_gprmc(const char* gprmc,char *hora,char *lat,char *lon,char *fecha){
  if(comparar("$GPRMC\0",encontrarXchar(gprmc,0,','))){
    strcpy(hora,encontrarXchar(gprmc,1,','));    
    strcpy(lat,encontrarXchar(gprmc,3,','));
    strcpy(lon,encontrarXchar(gprmc,5,','));
    strcpy(fecha,encontrarXchar(gprmc,9,','));
  }
}

void know_len(const char* restrict name,const char* restrict texto){
  printf(":%s: %i =>%s\n",name,strlen(texto),texto);
}

int calcularjson(const char* restrict name,char* restrict hora,char* restrict lat,char* restrict lon,char* restrict fecha){ 
  return strlen(name)+strlen(hora)+strlen(lat)+strlen(lon)+strlen(fecha)+1+2+1+2+1+1;
}

void json_gps_data_by_gprmc(const char* restrict name,char* restrict hora,char* restrict lat,char* restrict lon,char* restrict fecha,char *json){
  int j=0;
  json[j]='{';j++;
  json[j]='"';j++;
  for(int i=0;i<strlen(name);i++){
    json[j+i]=name[i];
  }
  j+=strlen(name);
  json[j]='"';j++;
  json[j]=':';j++;
  json[j]='"';j++;
  for(int i=0;i<strlen(fecha);i++){
    json[j+i]=fecha[i];
  }
  j+=strlen(fecha);
  json[j]=',';j++;
  for(int i=0;i<strlen(lon);i++){
    json[j+i]=lon[i];
  }
  j+=strlen(lon); 
  json[j]=',';j++;
  for(int i=0;i<strlen(lat);i++){
    json[j+i]=lat[i];
  }
  j+=strlen(lat);
  json[j]=',';j++;
  for(int i=0;i<strlen(hora);i++){
    json[j+i]=hora[i];
  }
  j+=strlen(hora);
  json[j]='"';j++;
  json[j]='}';j++;
  json[j]='\0';
}







/*
void calcularjson(const char* restrict name,char* restrict hora,char* restrict lat,char* restrict lon,char* restrict fecha,int *l){
  l=strlen(name)+strlen(hora)+strlen(lat)+strlen(lon)+strlen(fecha)+1+2+1+2+1+1;
  printf(":: %i  \n",l);
  //l=&l;
}
*/
  //printf(":valor: %i %s\n",lenValor,valor);
  //printf("           000000000011111111112222222222333333333344444444445555555555\n");
  //printf("           012345678901234567890123456789012345678901234567890123456789\n");

/*
void json_gps_data_by_gprmcsff(const char* restrict name,char* restrict hora,char* restrict lat,char* restrict lon,char* restrict fecha,char *json){
  int j=0;
  //printf(":eyes: %c",json[j]);
  json[j]='{';j++;
  //printf(":eyes: %c",json[j]);
  //know_len("eyes",json[0]);
  json[j]='"';j++;
  for(int i=0;i<strlen(name);i++){
    json[j+i]=name[i];
  }
  //know_len("name",json);
  j+=strlen(name);
  json[j]='"';j++;
  json[j]=':';j++;
  json[j]='"';j++;
  for(int i=0;i<strlen(hora);i++){
    json[j+i]=hora[i];
  }
  //know_len("hora",json);
  j+=strlen(hora);
  json[j]=',';j++;
  for(int i=0;i<strlen(lat);i++){
    json[j+i]=lat[i];
    printf(":eyes: %c\n",json[j+i]);
  }
  //know_len("lat",json);
  //know_len("lat",lat);
  //know_len("lon",lon);
  j+=strlen(lat);
  json[j]=',';j++;
  for(int i=0;i<strlen(lon);i++){
    json[j+i]=lon[i];
    //printf(":eyes: %c\n",json[j+i]);
  }
  //know_len("lon",json);
  //know_len("lon",lon);
  j+=strlen(lon);
  json[j]=',';j++;
  for(int i=0;i<strlen(fecha);i++){
    json[j+i]=fecha[i];
  }
  //know_len("fecha",json);
  //know_len("fecha",fecha);
  j+=strlen(fecha);
  json[j]='"';j++;
  json[j]='}';j++;
  json[j]='\0';
  //know_len("json",json);
}



int llenadochar(char* origen,char* texto,int j){
  for(int i=0;i<strlen(texto);i++){
    origen[j+i]=texto[i];
  }
  know_len("eyes",origen);
  j=strlen(texto);
  return j;
}
*/
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



/*
printf("enNse %i\n",encontrarNseparador(origin,ansi));
printf("len %i\n",len);
dimencion[encontrado]++;
printf(":eyes: %i %i\n",encontrado,dimencion[encontrado]);
*/
