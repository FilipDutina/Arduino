#include<LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte smajli[8] = {B00000, B00000, B01010, B00000, B10001, B01110, B00000, B00000};
int osaX;
int osaY;

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
  lcd.createChar(0, smajli);
}

//promenljive
int vrstaMine;
int i;
int pozicijaMine[16];
int kucicaX;
int kucicaY;
int zlatnikX1;
int zlatnikY1;
int zlatnikX2;
int zlatnikY2;
int zlatnikX3;
int zlatnikY3;

int brojacZlatnika;

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  osaX = random(1, 8)*2 - 1;
  osaY = random(0, 2);

  kucicaX = random(1, 8)*2 - 1;
  if(kucicaX == osaX)
    kucicaX += 2;
  kucicaY = random(0, 2);
  lcd.setCursor(kucicaX, kucicaY);
  lcd.print('X');

  zlatnikX1 = random(1, 8)*2 - 1;
  if(zlatnikX1 == kucicaX || zlatnikX1 == osaX)
    zlatnikX1 += 2;
  zlatnikY1 = random(0, 2);
  lcd.setCursor(zlatnikX1, zlatnikY1);
  lcd.print('@');

  zlatnikX2 = random(1, 8)*2 - 1;
  if(zlatnikX2 == kucicaX || zlatnikX2 == osaX || zlatnikX2 == zlatnikX1)
    zlatnikX2 += 2;
  zlatnikY2 = random(0, 2);
  lcd.setCursor(zlatnikX2, zlatnikY2);
  lcd.print('@');

  zlatnikX3 = random(1, 8)*2 - 1;
  if(zlatnikX3 == kucicaX || zlatnikX3 == osaX || zlatnikX3 == zlatnikX1 || zlatnikX3 == zlatnikX2)
    zlatnikX3 += 2;
  zlatnikY3 = random(0, 2);
  lcd.setCursor(zlatnikX3, zlatnikY3);
  lcd.print('@');

  lcd.setCursor(osaX, osaY);
  lcd.write(byte(0));
  delay(115);

  Serial.println(" ");

  for(i = 0; i < 15; i++) //ceo niz punim nulama
  {
    pozicijaMine[i] = 5;  
  }

  for(i = 0; i < 15; i++)   //postavljanje mina
  {
    if(i % 2 == 0)
    {
      vrstaMine = random(0, 2);
      if(vrstaMine == 0)
      {
        pozicijaMine[i] = 0;
      }
      else
      {
        pozicijaMine[i] = 1;
      }
      lcd.setCursor(i, vrstaMine);
      lcd.write('*');
    }
  }

  for(i = 0; i < 15; i++) 
  {
    Serial.print(pozicijaMine[i]);
  }

  brojacZlatnika = 0;
  
  while(ocitajTaster() != 1)  //*************************GLAVNI WHILE*************************
  {
    lcd.setCursor(osaX, osaY);
    lcd.write(byte(0));
    delay(150);
    lcd.setCursor(kucicaX, kucicaY);
    lcd.print('X');
    
    if(ocitajTaster() == 5 && osaX < 15)
    {
      lcd.setCursor(osaX, osaY);
      lcd.print(" ");
      osaX++;
    }
    else if(ocitajTaster() == 2 && osaX > 0)  
    {
      lcd.setCursor(osaX, osaY);
      lcd.print(" ");
      osaX--;
    }

    //************************************************************
    else if(ocitajTaster() == 3 && osaY > 0)
    {
      lcd.setCursor(osaX, osaY);
      lcd.print(" ");
      osaY--;
    }
    else if(ocitajTaster() == 4 && osaY < 1)
    {
      lcd.setCursor(osaX, osaY);
      lcd.print(" ");
      osaY++;
    }

    //********************
    //provera stanja
    if(osaY == pozicijaMine[osaX])
    {
      lcd.clear();
      lcd.print("mrtav");
      while(1);
    }

    if(osaX == zlatnikX1 && osaY == zlatnikY1)
    {
      brojacZlatnika++;
      zlatnikX1 = 0;
      zlatnikY1 = 0;
    }

    if(osaX == zlatnikX2 && osaY == zlatnikY2)
    {
      brojacZlatnika++;
      zlatnikX2 = 0;
      zlatnikY2 = 0;
    }

    if(osaX == zlatnikX3 && osaY == zlatnikY3)
    {
      brojacZlatnika++;
      zlatnikX3 = 0;
      zlatnikY3 = 0;
    }

    Serial.println(brojacZlatnika);

    if(brojacZlatnika >= 3 && osaX == kucicaX && osaY == kucicaY)
    {
      lcd.clear();
      lcd.print("POBEDIO :)");
      while(1);
    }
  }

}
