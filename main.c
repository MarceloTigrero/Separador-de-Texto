#include "texto.h"

int main() {
  char val[12]="+CIPGSMLOC:\0";
  char val2[52]="+CIPGSMLOC: 0,0.000000,0.000000,2022/03/14,21:58:02\0";
  char val5[12]="+CIPGSMLOC:\0";
  ///char val4[11]="+CIPGSMLOC:";
  
  printf("val %s\n",val);
  printf("val2 %s\n",val2);
  /*
  printf("val5 %s\n",val5);
  printf("----------------------------------------------------------------------------\n");
  printf("comparar val con corte val2 %i \n",comparar(val,encontrarXchar(val2,0,' ')));
  printf("----------------------------------------------------------------------------\n");
  printf("comparar val5 con corte val5 %i \n",comparar(val5,encontrarXchar(val2,0,' ')));
*/
  int l = encontrarDchar(val2,1,' ');
  printf(" %i\n",l);
  char dato[l];
  strcpy(dato,encontrarXchar(val2,1,' '));
  printf(" %s\n",dato);
  
  printf("json %s\n",armarJson("clave\0",dato));
  printf("     000000000011111111112222222222333333333344444444445555555555\n");
  printf("     012345678901234567890123456789012345678901234567890123456789\n");
  
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
