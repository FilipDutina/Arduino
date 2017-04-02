/*2) TRCECA REKLAMA - Napisati program koji omogucava unos teksta reklame koja treba da
se prikazuje na LCD displeju. Prilikom unosa teksta, kursor treba da bude ukljucen.
Pomeranje kursora duz displeja vrsi se pomocu tastera LEFT i RIGHT, a izbor karaktera
koji se prikazuje na trenutnoj poziciji pomocu tastera UP i DOWN. Nakon sto je unesen ceo
tekst reklame, pritiskom na taster SELECT kursor se iskljucuje i tekst reklame se pomera
(skroluje) po displeju s desna na levo.*/

#include<LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define DUZINA 16

char mojNiz[DUZINA];
int i;

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
  for(i = 0; i < DUZINA; i++)
  {
    mojNiz[i] = 'A';  
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  unsigned int x = 0;
  while(ocitajTaster() != 1)
  {
    lcd.print(mojNiz[x]);
    if(ocitajTaster() == 3)
    {
      mojNiz[x]--;
      delay(150);
    }
    if(ocitajTaster() == 4)
    {
      mojNiz[x]++;
      delay(150);
    }
    if(ocitajTaster() == 2)
    {
      x--;
      delay(150);
    }
    if(ocitajTaster() == 5)
    {
      x++;
      delay(150);
    }
    x = x % DUZINA; //ovo ga uvke drzi na displeju (ne moze dobiti vecu vrednost od 16)
    lcd.setCursor(x, 0);  
  }
  while(1)
  {
    delay(200);
    lcd.scrollDisplayLeft();
  }
}
