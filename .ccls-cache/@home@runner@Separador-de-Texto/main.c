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

//http://informatica.dgenp.unam.mx/recomendaciones/codigo-ascii
//alt+39 ''
//da el codigo ansi del char a encontrar
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

//numeros de chars encontrados en el texto enviado
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

//encuantra la longitud del char a encontrar
int encontrarDchar(const char* origin,int ubicacion,unsigned char caracter)//texto,int,','
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
  //printf("encontrado %i\n",encontrado);
  return dimencion[ubicacion];
}


//encuentra la ubicacion del char a encontrar
int encontrarUchar(const char* origin,int ubicacion,unsigned char caracter)//texto,int,','
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
  //printf("encontrado %i\n",encontrado);
  if(ubicacion == 0)
  {
    return 0;
  }else{
    return ubi[ubicacion-1];
  }
}
/*
printf("enNse %i\n",encontrarNseparador(origin,ansi));
printf("len %i\n",len);
dimencion[encontrado]++;
printf(":eyes: %i %i\n",encontrado,dimencion[encontrado]);
*/

// encontrar el la palabra del char
const char* encontrarXchar(const char* origin,int ubicacion,unsigned char caracter)//texto,int,','
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
      word[i]=0;
    }
  }
  return word;
}

//concatenar armar json
const char* armarJson(const char* nombre,const char* dato)//texto,int,','
{
  const int lenNombre = strlen(nombre);
  printf(":name: %i %s\n",lenNombre,nombre);
  const int lenDato = strlen(dato);
  printf(":data: %i %s\n",lenDato,dato);
  char word[lenNombre+lenDato+7];
  word[0] = CodigoAnsi('{');
  word[1] = CodigoAnsi('"');
  for(int i=0;i<lenNombre;i++)
  {
      word[2+i] = nombre[i];
      //printf(":eyes: %i %s\n",i,word);
  }
  word[lenNombre+2] = CodigoAnsi('"');
  word[lenNombre+3] = CodigoAnsi(':');
  word[lenNombre+4] = CodigoAnsi('"');
  for(int i=0;i<lenDato;i++)
  {
    word[lenNombre+5+i] = CodigoAnsi(dato[i]);
    //printf(":eyes: %i %s\n",i,word);
    printf(":eyes: %i %i %c\n",lenDato,i,dato[i]);
  }
  word[lenNombre+5+lenDato] = CodigoAnsi('"');
  word[lenNombre+6+lenDato] = CodigoAnsi('}');
  return word;
}


int main() {
  char val[11]="+CIPGSMLOC:";
  char val2[53]="+CIPGSMLOC: 0,0.000000,0.000000,2022/03/14,21:58:02";
  
  printf(" %s\n",val);
  printf(" %s\n",val2);
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
  json[l+11] =CodigoAnsi(' ');
  json[l+12] =CodigoAnsi(' ');
  json[l+13] =CodigoAnsi(' ');
  json[l+14] =CodigoAnsi(' ');
  //printf(" %s\n",json);
  printf(":json: %i %s\n",strlen(json),json);
  printf(" %s\n",val);
  printf(" %s\n",val2);
  printf(" %s\n",dato);
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
