#include<LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//za definisanje dozvoljenih vrednosti
int minBr = 48;
int maxBr = 58;
int minVelSlo = 65;
int maxVelSlo = 91;
int minMalSlo = 97;
int maxMalSlo = 123;
char string[10];  //string koji korisnik unosi
int duzina;

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
  randomSeed(analogRead(99));
}

int velicinaNiza;
int i;
int rasporedjivac;
int nula;

void loop() {
  // put your main code here, to run repeatedly:

  lcd.clear();

  velicinaNiza = random(5, 9);
  nula = 0;

  char mojNiz[velicinaNiza];

  for(i = 0; i < velicinaNiza; i++)
  {
    rasporedjivac = random(0, 3);
    
    if(rasporedjivac == 0)
      mojNiz[i] = random(minBr, maxBr);
    else if(rasporedjivac == 1)
      mojNiz[i] = random(minVelSlo, maxVelSlo);
    else
      mojNiz[i] = random(minMalSlo, maxMalSlo);
  }

  lcd.print(mojNiz);
  Serial.println("Niz koji morate reprodukovati je: ");
  Serial.println(mojNiz);
  Serial.println(" ");
  Serial.println("Unesite zadati niz: ");

  while(!Serial.available());
  delay(100);
  duzina = Serial.available();
  Serial.readBytes(string, duzina);
  string[duzina] = 0;
  Serial.println(string);

  lcd.setCursor(0, 1);
  
  for(i = 0; i < velicinaNiza; i++)
  {
    if(string[i] != mojNiz[i])
      nula++;
  }

  if(nula == 0)
    lcd.print("ECCE HOMO!");
  else if(nula != 0)
    lcd.print("BOT");

  while(ocitajTaster() != 1);
}
