#include<LiquidCrystal.h>
#define DUZINA 15

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

char rec1[] = "zdravo";
char rec2[] = "pas";
char rec3[] = "kuca";
char rec4[] = "glava";
char rec5[] = "drvo";
char rec6[] = "gitara";
char rec7[] = "kontrabas";
char rec8[] = "arduino";
char rec9[] = "pokazivac";
char rec10[] = "port";

char* reci[] = {rec1, rec2, rec3, rec4, rec5, rec6, rec7, rec8, rec9, rec10};

byte ocitajTaster()
{
  int temp = analogRead(0);

  if(temp < 700 && temp > 600)
    return 1; //select
  else if(temp < 460 && temp > 360)
    return 2; //left
  else if(temp < 150 && temp > 50)
    return 3; //up
  else if(temp < 300 && temp > 200)
    return 4; //down
  else if(temp < 49)
    return 5; //right
  else
    return 0; //nista nije pritisnuto
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  randomSeed(analogRead(1));
}

char mojaRec[20];
int redniBrojReci;
int i;
int velicinaReci;
int brojZivota;
int duzina;
char string[DUZINA];
char pomocni[DUZINA];
int pomocniBrojac;
int pomocniBrojac2;
char pom = "A";

void loop() {
  // put your main code here, to run repeatedly:
  redniBrojReci = random(0, 10);
  Serial.println(redniBrojReci);
  for(i = 0; i < 16; i++)
  {
    mojaRec[i] = reci[redniBrojReci][i];
  }
  Serial.println(mojaRec);
  for(i = 0; i < 20; i++)
  {
    if(mojaRec[i] == '\0')
      break;
    velicinaReci++;
  }
  Serial.println(velicinaReci);

  //**********************************************************************
  //imam rec i njenu duzinu; sad pravim vesalo
  unsigned int x = 0;
  brojZivota = 10;
  for(i = 0; i < velicinaReci; i++)
    {
      lcd.setCursor(i, 0);
      lcd.print('_');
    }
  lcd.setCursor(0, 1);
  lcd.print(brojZivota);
  pomocniBrojac = 0;
  while(1)
  {
    /*while(!Serial.available());
    delay(100);
    duzina = Serial.available();
    Serial.readBytes(string, duzina);
    string[duzina] = 0;
    Serial.println(string);*/
  
   while(ocitajTaster() != 1)
    {
      lcd.setCursor(15, 1);
      lcd.print(pom);
      if(ocitajTaster() == 3)
      {
        pom--;
        delay(200);
      }
      if(ocitajTaster() == 4)
      {
        pom++;
        delay(200);
      }
    }
    delay(500);

    //duzina = 1;
    string[0] = pom;
    string[1] = 0;
    Serial.println(string[0]);
    
    
    pomocniBrojac2 = 0;
    
    for(i = 0; i < velicinaReci; i++)
    { 
       if(string[0] == mojaRec[i])
       {
          lcd.setCursor(i, 0);
          lcd.print(string);
          pomocniBrojac2++;
          pomocniBrojac++;
       }
    }
    if(pomocniBrojac2 == 0)
    {
       lcd.setCursor(0, 1);
       lcd.print("      ");
       brojZivota--;
       lcd.setCursor(0, 1);
       lcd.print(brojZivota);
    }
    if(brojZivota == 0)
     {
       lcd.clear();
       lcd.print("obesen :(");
       break;
     }
    if(pomocniBrojac == velicinaReci)
    {
       lcd.clear();
       lcd.print("preziveo :)");
       break;
    }
    
  }
  
  while(1);
}
