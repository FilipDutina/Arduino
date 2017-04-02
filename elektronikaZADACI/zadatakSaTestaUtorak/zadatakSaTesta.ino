#include<LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//reci koje pogadjam
char rec1[] = "zdravo";
char rec2[] = "pas";
char rec3[] = "macka";
char rec4[] = "glava";
char rec5[] = "konj";
char rec6[] = "gitara";
char rec7[] = "ekran";
char rec8[] = "sto";
char rec9[] = "stolica";
char rec10[] = "arduino";
//niz reci
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

//promenljive
char mojaRec[16]; //rec koju pogadjam
int redniBrojReci;  //broj moje reci u nizu reci
int i;  
int duzinaReci;
int brojZivota;
char unos[1]; //unos sa tastature
int duzina;
int pomocniBrojac;  //pomocne promenljive za pamcenje vrednosti
int pomocniBrojac2;
int pomocniBrojac3;
char direktanUnos = 'a';  //za direktan unos sa arduina

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  Serial.println(" ");
  
  redniBrojReci = random(0, 10);
  for(i = 0; i < 15; i++)
  {
    mojaRec[i] = reci[redniBrojReci][i];
  }
  Serial.println(mojaRec);  //provera da li se rec pravilno prekopirala
  for(i = 0; i < 16; i++)
  {
    if(mojaRec[i] == '\0')
      break;
    duzinaReci++;
  }
  Serial.print("Duzina reci: ");
  Serial.println(duzinaReci); //proveravam da li je duzina reci odgovarajuca

  //******************************************************************************************
  //imam rec i njenu duzinu, sada pravim vesalo
  
  brojZivota = 10;
  pomocniBrojac = 0;  //pomocu njega znam da li treba da oduzmem zivot u tekucoj iteraciji
  pomocniBrojac2 = 0; //ukoliko se desi da je pomocniBrojac2 == duzinaReci znaci da sam pronasao sva slova koja sacinjavaju
                      //datu rec

  //**********************************
  //zastita ako se unose slova koja su vec pronadjena(uneta)
  char unetaSlova[16];  //niz gde mi se smestaju pronadjena slova
  for(i = 0; i < 15; i++)
  {
     unetaSlova[i] = '0'; //punim ovaj niz nulama(moze bilo koji znak, samo da nije malo slovo)
  }
  int a = 0;  //indeks niza unetaSlova(na kraju glavne while petlje ga inkrementiram)
  int b = 0;
  //*********************************
  
  for(i = 0; i < duzinaReci; i++) //ispis crtica i max broja zivota
  {
    lcd.setCursor(i, 0);  //pomeram kursor za jedno mesto udesno
    lcd.print('_'); 
  }
  lcd.setCursor(0, 1);
  lcd.print(brojZivota);
  

  while(1)  //glavni while
  {
    //unos sa tastature
    /*while(!Serial.available()); 
    delay(100);
    duzina = Serial.available();
    Serial.readBytes(unos, duzina);
    unos[duzina] = 0;
    Serial.println(unos);*/

    //direktan unos
    while(ocitajTaster() != 1)
    {
      lcd.setCursor(15, 1);
      lcd.print(direktanUnos);
      if(ocitajTaster() == 3)
      {
        if(direktanUnos != 97)  //zastita kako bih unosio samo mala slova
          direktanUnos--;
        else
          direktanUnos = 'z';
        delay(250);
      }
      if(ocitajTaster() == 4)
      {
        if(direktanUnos != 122)
          direktanUnos++;
        else
          direktanUnos = 'a';
        delay(250);
      }
    }
    delay(500);

    pomocniBrojac = 0;  //pre svakog prolaza kroz rec pomocniBrojac moram vratiti na nulu

    for(i = 0; i < duzinaReci; i++) //ako se uneto slovo vec nalazi u nizu za proveru povecavam b za 1(znaci da je vec uneto ranije)
    {
      if(direktanUnos == unetaSlova[i])
        b++;
    }

    
    for(i = 0; i < duzinaReci; i++) //glavni for
    { 
      if(direktanUnos == mojaRec[i] && b == 0)  //umesto direktanUnos staviti unos[0] za unos sa tastature
      {                                         //ako je b == 0 to znaci da se uneto slovo ne nalazi u nizu za proveru(znaci da ga korisnik prvi put unosi) 
        lcd.setCursor(i, 0);
        lcd.print(direktanUnos);    //umesto direktanUnos staviti unos[0] za unos sa tastature
        pomocniBrojac++;  //nasao sam slovo koje se nalazi u reci
        pomocniBrojac2++; //broj pronadjenih slova
      }
      
      if(pomocniBrojac == 0 && i == duzinaReci-1)  //ako je pomocniBrojac == 0 znaci da nisam nasao zadato slovo
      {                                   //i == duzinaReci-1 --> dosao sam do kraja reci
        lcd.setCursor(0, 1);              
        lcd.print("    ");  //brisem prethodno stanje
        brojZivota--;
        lcd.setCursor(0, 1);
        lcd.print(brojZivota);
      }
      if(brojZivota == 0)
      {
        lcd.clear();
        lcd.print("dead");
        lcd.setCursor(14, 1);
        lcd.print("   ");
        lcd.setCursor(0, 1);
        lcd.print("press reset");
        while(1);
      }
      if(pomocniBrojac2 == duzinaReci)  //pronasao sam sva slova od kojih se sastoji rec
      {
        lcd.clear();
        lcd.print("alive");
        lcd.setCursor(14, 1);
        lcd.print("   ");
        lcd.setCursor(0, 1);
        lcd.print("press reset");
        while(1);
      }
    }
    Serial.println("Pronadjena slova: ");
    Serial.println(pomocniBrojac2);
    unetaSlova[a] = direktanUnos; //unosim uneto slovo u zastitni niz
    a++;  //indeks zastitnog niza(unetaSlova) pomocu kog se pomeram za jedno mesto nakon svake glavne for petlje
    b = 0;  //promenljiva za proveru se vraca na nulu
  }

}
