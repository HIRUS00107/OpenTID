#include "TID12_10.h"
TID MyTid(20,21,13); //D20->SDA, D21->SCL, D13->MRQ
byte dalej = 1;
byte lastdalej = 1;
byte potwierdz = 1;
byte lastpotwierdz = 1;
byte licznik= 0;
byte wyswietlane=0;

bool aktywacja;
unsigned long milisek, milisek1, microsek, microsek1;
unsigned long interwal_milisek, interwal_microsek;
double spalanieh;
float dystans; 
byte predkosc;
//Stałe
const float R1=300000.0;  //Rezystor 1 do dzielnika napięcia (300K) - układ napięcia akumulatora
const float R2=100000.0;  //Rezystor 2 do dzielnika napięcia (100K) - układ napięcia akumulatora

const float R3=100000.0;  //Rezystor 1 do dzielnika napięcia (100K) - układ napięcia wskaźnika paliwa
const float R4=100000.0;  //Rezystor 2 do dzielnika napięcia (100K) - układ napięcia wskaźnika paliwa

const float R5=560.0;  //Rezystor 1 do omomierza (560)

const float U=5.0; //Napiecie zasilania

const float SFactor=1.0; //Mnożnik dystansu
const float VFactor=1.0; //Mnożnik prędkości
const float FFactor=1.0; //Mnożnik paliwa

const int N=4; //ilość wtrysków
const int L=155; //stała wtrysku ml/min

void setup() {

MyTid.space1_init(0,0); //(first position,last position) (i. e. just the first digit)
MyTid.space2_init(1,9); //use digit 2 to 10
MyTid.clear_space(1);
MyTid.clear_space(2);
pinMode(52,INPUT_PULLUP); //Przycisk R
pinMode(50,INPUT_PULLUP); //Przycisk S
pinMode(22,INPUT_PULLUP);

pinMode(48,OUTPUT); //Przekaźnik 1
pinMode(46,OUTPUT); //Przekaźnik 2
pinMode(44,OUTPUT); //Przekaźnik 3

digitalWrite(48,HIGH); //Przekaźnik 1
digitalWrite(46,HIGH); //Przekaźnik 2
digitalWrite(44,HIGH); //Przekaźnik 3
digitalWrite(42,HIGH); //Przekaźnik 4
}

void loop() {
//Menu
  dalej = digitalRead(52);
  potwierdz = digitalRead(50);
  
  if (dalej != lastdalej) 
  {
    if (dalej == LOW) 
    {
      if(licznik == 11)
      {
        licznik = 0;
      }
      licznik++;
      MyTid.clear_space(2);
      wyswietlane=0;
      delay(250);
      digitalWrite(48,HIGH);
      digitalWrite(46,HIGH);
      digitalWrite(44,HIGH);
      digitalWrite(42,HIGH);
    }
  delay(50);
  }


switch(licznik){
case 1:
  //MyTid.clear_space(2);
  if (wyswietlane==0){
  MyTid.display_message("Ch.spala.",4,2);
  }
  if (potwierdz != lastpotwierdz || wyswietlane==1) 
  {
    if (potwierdz == LOW) 
    {
      MyTid.clear_space(2);
    }
    if (potwierdz == LOW || wyswietlane==1) 
    {
      wyswietlane=1;
      Chwilowe_spalanie();
    }
  }

  
  break;
case 2: 
  //MyTid.clear_space(2);
  if (wyswietlane==0){
  MyTid.display_message("Sr.spala.",4,2);
  }
  if (potwierdz != lastpotwierdz || wyswietlane==1) 
  {
    if (potwierdz == LOW) 
    {
      MyTid.clear_space(2);
    }
    if (potwierdz == LOW || wyswietlane==1) 
    {
      wyswietlane=1;
      Srednie_spalanie();
    }
  }

  
  break;
case 3: 
  //MyTid.clear_space(2);
  if (wyswietlane==0){
  MyTid.display_message("Zasieg",4,2);
  }
  if (potwierdz != lastpotwierdz || wyswietlane==1) 
  {
    if (potwierdz == LOW) 
    {
      MyTid.clear_space(2);
    }
    if (potwierdz == LOW || wyswietlane==1) 
    {
      wyswietlane=1;
      Zasieg();
    }
  }

  
  break;
case 4: 
  //MyTid.clear_space(2);
  if (wyswietlane==0){
  MyTid.display_message("Radio",4,2);
  }
  if (potwierdz != lastpotwierdz || wyswietlane==1) 
  {
    if (potwierdz == LOW) 
    {
      MyTid.clear_space(2);
    }
    if (potwierdz == LOW || wyswietlane==1) 
    {
      wyswietlane=1;
      Radio();
    }
  }

  
  break;
case 5:
  //MyTid.clear_space(2);
  if (wyswietlane==0){
  MyTid.display_message("Napiecie",4,2);
  }
  if (potwierdz != lastpotwierdz || wyswietlane==1) 
  {
    if (potwierdz == LOW) 
    {
      MyTid.clear_space(2);
    }
    if (potwierdz == LOW || wyswietlane==1) 
    {
      wyswietlane=1;
      Akumulator();
    }
  }

  
  break;
case 6: 
  //MyTid.clear_space(2);
  if (wyswietlane==0){
  MyTid.display_message("Paliwo",4,2);
  }
  if (potwierdz != lastpotwierdz || wyswietlane==1) 
  {
    if (potwierdz == LOW) 
    {
      MyTid.clear_space(2);
    }
    if (potwierdz == LOW || wyswietlane==1) 
    {
      wyswietlane=1;
      Stan_paliwa();
    }
  }
  
  break;
case 7: 
  //MyTid.clear_space(2);
  if (wyswietlane==0){
  MyTid.display_message("Data",4,2);
  }
  if (potwierdz == LOW) 
    {
      MyTid.clear_space(2);
    }
  if (potwierdz != lastpotwierdz || wyswietlane==1) 
  {
    if (potwierdz == LOW || wyswietlane==1) 
    {
      wyswietlane=1;
      Data();
    }
  }


  break;
case 8:
  //MyTid.clear_space(2);
  if (wyswietlane==0){
  MyTid.display_message("RPM",4,2);
  }
  if (potwierdz != lastpotwierdz || wyswietlane==1) 
  {
    if (potwierdz == LOW) 
    {
      MyTid.clear_space(2);
    }
    if (potwierdz == LOW || wyswietlane==1) 
    {
      wyswietlane=1;
      RPM();
    }
  }

  
  break;
case 9: 
  //MyTid.clear_space(2);
  if (wyswietlane==0){
  MyTid.display_message("Predkosc",4,2);
  }
  if (potwierdz != lastpotwierdz || wyswietlane==1) 
  {
    if (potwierdz == LOW) 
    {
      MyTid.clear_space(2);
    }
    if (potwierdz == LOW || wyswietlane==1) 
    {
      wyswietlane=1;
      Predkosc();
    }
  }

  
  break;
case 10: 
  //MyTid.clear_space(2);
  if (wyswietlane==0){
  MyTid.display_message("Sr.Pred.",4,2);
  }
  if (potwierdz != lastpotwierdz || wyswietlane==1) 
  {
    if (potwierdz == LOW) 
    {
      MyTid.clear_space(2);
    }
    if (potwierdz == LOW || wyswietlane==1) 
    {
      wyswietlane=1;
      SrPredkosc();
    }
  }

  
  break;
default:
  MyTid.display_message("Wybierz Menu ",4,2);
  break;
}

}
//Menu

void Chwilowe_spalanie(){
  if (digitalRead(22) == LOW)
  {
    microsek = micros();
  }
  else
  {
    microsek1 = micros(); 
    interwal_microsek = microsek1 - microsek; 
    spalanieh=N*(L/60.0)*3.6*(interwal_microsek/1000000.0);
    MyTid.display_message(String(spalanieh),16,2);
  }


  //MyTid.display_message("l/100km",4,2);
}

void Srednie_spalanie(){
  //MyTid.clear_space(2);
  MyTid.display_message("l/h",4,2);
}
void Zasieg(){
  //MyTid.clear_space(2);
  MyTid.display_message("km",4,2);
}
void Radio(){
  digitalWrite(48,LOW);
  digitalWrite(46,LOW);
  digitalWrite(44,LOW);
}
void Akumulator(){
  double odczytzPinu = analogRead(A0);
  double napiecie = odczytzPinu * (U / 1023.0);
  napiecie=napiecie / (R2/(R1+R2));

  MyTid.display_message("V "+String(napiecie),4,2);
}
void Stan_paliwa(){
  //Dostosowanie odczytu do stablilizatora napięcia samochodu
  double odczytzPinu = analogRead(A1);
  double U1 = odczytzPinu * (U / 1023.0);
  U1 = U1 / (R4/(R3+R4));
  //Pomiar oporności
  double U2 = U1 * (analogRead(A2)/1023.0);
  double Ohm = (U1*R5/U2) - R5;

  MyTid.display_message("Ohm "+String(Ohm),4,2);
}
void Data(){
  digitalWrite(42,LOW);
}
void RPM(){
  MyTid.clear_space(2);
  //kod załączający pomiar rpm
}
void Predkosc(){
  if (digitalRead(24) == HIGH)
  {
    dystans = dystans + 1;
    predkosc=(dystans/16.0)*VFactor*3.6;
    MyTid.display_message(String(predkosc)+"km/h  ",4,2);
  }
}
void SrPredkosc(){
  MyTid.clear_space(2);
  //kod załączający Predkosc
}







// Spalanie

/*
float Spalanieh(float czas_wtrysku){
  
  
  return int(N*(L/60)*(czas_wtrysku/1000000)*36);
}
*/

//stała wtysku 155ml/min = 0,0025834 l/s lub 160ml/min = 0,0026667 l/s dla silnika Z16XE

/*
Pierdoły do zrobienia
chwilowe spalanie
średnie spalanie
test zegarów -
przełączanie radio/arduino  x
Data x
pomiar napięcia akumulatora x
wyświetlanie prędkości i rpm jak będzie mi się chciało
ewentualnie AFR i temp dolotu i jak znajdę to ciśnienie na map sensorze
temperatura silnika i stan paliwa
jakiś ładny napis powitalny
*/