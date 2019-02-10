/*Simon Says igrca*/

/*Poimenujemo zvočnik, različne intižerje in števec.*/
#include <Tone.h> //vključuje knjižnico "Tone" v C:\Program Files (x86)\Arduino\libraries.
Tone speakerpin; //poimenovali smo zvočnik in bo zdej uporabljal knjižnico "Tone".
int starttune[] = {NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4}; //to je začetna pesem, ki jo Arduino zaigra ko se zažene. Za starttune smo izbrali 13 ton (0-12), ki jih bo zvočnik izpustil.
int duration2[] = {100, 200, 100, 200, 100, 400, 100, 100, 100, 100, 200, 100, 500}; //to je čas vsakega tona za starttune, 1000 = 1 sekunda in tako naprej.
int note[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5}; //to je pesem, ko zaigra ko vam uspe taprav gumb pretisnat.
int duration[] = {100, 100, 100, 300, 100, 300}; //to je čas vsakega tona za note, 1000 = 1 sekunda, 100 = 0.1 sekunda in tako naprej.
int button[] = {2, 3, 4, 5}; //input pini za 4 gumbe.
int ledpin[] = {8, 9, 10, 11};  //output pini za 4 LED diode.
int turn = 0;  //števec, ki šteje kolikokrat vam je uspelo uganit.
int buttonstate = 0;  //preverja stanje gumba, če je uporabnik ga pritisnal.
int randomArray[100]; //izmislil si bo 100 naključnih rezultatov, ki jih more uporabnik ugotovit.
int inputArray[100];  //hrani okrog 100 naključnih inputov.

/*Dekleriramo LED diode (da so outputi), gumbe (da so inputi) in da, zaigra začetno pesem*/
void setup() 
{
  Serial.begin(9600); //nastavimo 9600 bitov na sekundo.
    speakerpin.begin(12); //zvočnik smo nastavli na pin 12.

      for(int x=0; x<4; x++)  //dekleriramo vse 4 LED diode (0-3) na OUTPUT.
        {
          pinMode(ledpin[x], OUTPUT); //deklerira vsako LED diodo.
        }
  
      for(int x=0; x<4; x++) //dekleriramo vseh 4 gumbov (0-3) na INPUT.
        {
          pinMode(button[x], INPUT);  //deklerira vsakega gumba.
          digitalWrite(button[x], HIGH);  //da napetost 5V na vsakega gumba.
        }

    randomSeed(analogRead(0)); //dodal sem, da bo ustvarila večjo naključnosti, da je bolj random, z randomArray za izhode.
    
  for (int thisNote = 0; thisNote < 13; thisNote ++)  //tule ti zaigra začetno pesem, "starttune" (0-13)
  {
     speakerpin.play(starttune[thisNote]); //začne igrat tone iz starttune.
     
        if (thisNote==0 || thisNote==2 || thisNote==4 || thisNote== 6) //če je 0,2,4 ali 6 se vklopi rdeča LED dioda.
        {
          digitalWrite(ledpin[0], HIGH); //rdeča LED dioda bo zastevtla, ko bo zvočnik izpustil tone.
        }
        if (thisNote==1 || thisNote==3 || thisNote==5 || thisNote== 7 || thisNote==9 || thisNote==11) //če je 1,3,5 in 7 se vklopi zelena LED dioda.
        {
          digitalWrite(ledpin[1], HIGH); //zelena LED dioda bo zastevtla, ko bo zvočnik izpustil tone.
        }
        if (thisNote==8 || thisNote==12) //če je 8 ali 12 se vklopi rumena LED dioda.
        {
          digitalWrite(ledpin[2], HIGH); //rumena LED dioda bo zastevtla, ko bo zvočnik izpustil tone.
        }  
        if (thisNote==10) //če je 10 se vklopi modra LED dioda.
        {   
          digitalWrite(ledpin[3], HIGH); //modra LED dioda bo zastevtla, ko bo zvočnik izpustil tone.
        }
          delay(duration2[thisNote]); //čas čakanja za naslednjo tono.
          speakerpin.stop(); //zvočnik se ugasne.
              digitalWrite(ledpin[0], LOW); //LED dioda se ugasne.
              digitalWrite(ledpin[1], LOW); //LED dioda se ugasne.
              digitalWrite(ledpin[2], LOW); //LED dioda se ugasne.
              digitalWrite(ledpin[3], LOW); //LED dioda se ugasne.
          delay(25);
  }
  delay(1000); //čaka 1 sekundo, in nato bo šlo na naslednjo tono.
}

/*Arduino izbere naključno število od (1-4) in se določena LED dioda zasveti in si jo mora uporabnik zapomnit*/
void loop() 
{   
  for (int y=0; y<=99; y++) //da lahko uporabnik igra do 100 (0-99).
  {
      digitalWrite(ledpin[0], HIGH); //LED dioda se prežge.
      digitalWrite(ledpin[1], HIGH); //LED dioda se prežge.
      digitalWrite(ledpin[2], HIGH); //LED dioda se prežge.
      digitalWrite(ledpin[3], HIGH); //LED dioda se prežge.
  
    for (int thisNote = 0; thisNote < 6; thisNote ++) //tule ti zaigra začetno pesem, "note" (0-5)
    {
      speakerpin.play(note[thisNote]); //začne igrat tone iz note.
      delay(duration[thisNote]); //čas čakanja za naslednjo tono.
      speakerpin.stop(); //zvočnik se ugasne.
      delay(25);
    }
    
      digitalWrite(ledpin[0], LOW); //LED dioda se ugasne.
      digitalWrite(ledpin[1], LOW); //LED dioda se ugasne.
      digitalWrite(ledpin[2], LOW); //LED dioda se ugasne.
      digitalWrite(ledpin[3], LOW); //LED dioda se ugasne.
      delay(1000); 
  
    for (int y=turn; y <= turn; y++)
    { 
      Serial.println(""); //nova vrstica, ki se zapisuje v serijski vmesnik.
      Serial.print("Turn: "); //natisne števec Turn v serijski vmesnik.
      Serial.print(y); //natisne vrednost y v serijski vmesnik.
      Serial.println(""); //nova vrstica v serijski vmesniku.
      randomArray[y] = random(1, 5); //določanje naključnega števila (1-4).
      for (int x=0; x <= turn; x++)
      {
        Serial.print(randomArray[x]); //natisne ti nakljućno število od 1 do 4. 
      
        for(int y=0; y<4; y++)
        {
      
          if (randomArray[x] == 1 && ledpin[y] == 8) //da izvrši prižig določene LED luči in tona, to indikira kater gumb more stisnat.
          {  
            digitalWrite(ledpin[y], HIGH); //rdeča LED dioda se bo zastevtla.
            speakerpin.play(NOTE_G3, 100); //zaigra tono, ko se LED dioda prežge.
            delay(400); //čas svetlobe.
            digitalWrite(ledpin[y], LOW); //LED dioda se ugasne.
            delay(100);
          }

          if (randomArray[x] == 2 && ledpin[y] == 9) //da izvrši prižig določene LED luči in tona, to indikira kater gumb more stisnat.
          {
            digitalWrite(ledpin[y], HIGH); //zelena LED dioda se bo zastevtla.
            speakerpin.play(NOTE_A3, 100); //zaigra tono, ko se LED dioda prežge.
            delay(400); //čas svetlobe.
            digitalWrite(ledpin[y], LOW); //LED dioda se ugasne.
            delay(100);
          }
  
          if (randomArray[x] == 3 && ledpin[y] == 10) //da izvrši prižig določene LED luči in tona, to indikira kater gumb more stisnat.
          {
            digitalWrite(ledpin[y], HIGH); //rumena LED dioda se bo zastevtla.
            speakerpin.play(NOTE_B3, 100); //zaigra tono, ko se LED dioda prežge.
            delay(400); //čas svetlobe.
            digitalWrite(ledpin[y], LOW); //LED dioda se ugasne
            delay(100);
          }

          if (randomArray[x] == 4 && ledpin[y] == 11) //da izvrši prižig določene LED luči in tona, to indikira kater gumb more stisnat.
          {
            digitalWrite(ledpin[y], HIGH); //modra LED dioda se bo zastevtla.
            speakerpin.play(NOTE_C4, 100); //zaigra tono, ko se LED dioda prežge.
            delay(400); //čas svetlobe.
            digitalWrite(ledpin[y], LOW); //LED dioda se ugasne
            delay(100);
          }
        }
      }
    }
    input(); //uporablja, naslednjo kodo.
  }
}

/*Uporabnik more pretisnat gumb, kjer se je zasvetla LED dioda, če mu uspe gre naprej*/
void input() //Funkcija omogoča uporabnikov vnos in preverjanje vhod proti ustvarjeni niz.
{ 
  for (int x=0; x <= turn;) //izjava nadzorovana s štetjem turn.
  { 
    for(int y=0; y<4; y++) //za vsak gumb
    {    
      buttonstate = digitalRead(button[y]); //preveri, kater gumb je uporabnik pretisnal.
    
        if (buttonstate == LOW && button[y] == 2) //potem ko stisneš se prežge LED dioda in se izvrši ton, ter izpiše  vmesnik kateri gumb si stisnu.
        { 
            digitalWrite(ledpin[0], HIGH); //rdeča LED dioda zasveti.
            speakerpin.play(NOTE_G3, 100); //izpusti Tono.
            delay(200); //čas čakanja.
            digitalWrite(ledpin[0], LOW); //LED dioda se ugasne.
            inputArray[x] = 1; //nastavimo na 1, da preveri v naslednjem if stavku.
            delay(250); //čas čakanja.
            Serial.print(" "); //nova vrstica v serijski vmesniku.
            Serial.print(1); //vpiše 1 v Serijski vmesnik.
              if (inputArray[x] != randomArray[x]) //Pregleda vrednost, ki jo je uporabnik vnesu.
              { 
                fail(); //če uporabnik napačen gumb pretisnal, gre na nasledno kodo.                        
              }                                      
                x++; //x se poveča za 1.
              }
              
         if (buttonstate == LOW && button[y] == 3) //potem ko stisneš se prežge LED dioda in se izvrši ton, ter izpiše  vmesnik kateri gumb si stisnu.
         {
             digitalWrite(ledpin[1], HIGH); //zelena LED dioda zasveti.
             speakerpin.play(NOTE_A3, 100); //izpusti Tono.
             delay(200); //čas čakanja.
             digitalWrite(ledpin[1], LOW); //LED dioda se ugasne.
             inputArray[x] = 2; //nastavimo na 2, da preveri v naslednjem if stavku.
             delay(250); //čas čakanja.
             Serial.print(" "); //nova vrstica v serijski vmesniku.
             Serial.print(2); //vpiše 2 v Serijski vmesnik.
               if (inputArray[x] != randomArray[x]) //Pregleda vrednost, ki jo je uporabnik vnesu.
               {
                 fail(); //če uporabnik napačen gumb pretisnal, gre na nasledno kodo.     
               } 
             ++; //x se poveča za 1.
           }
                  
        if (buttonstate == LOW && button[y] == 4) //potem ko stisneš se prežge LED dioda in se izvrši ton, ter izpiše  vmesnik kateri gumb si stisnu.
        { 
            digitalWrite(ledpin[2], HIGH); //rumena LED dioda zasveti.
            speakerpin.play(NOTE_B3, 100); //izpusti Tono.
            delay(200); //čas čakanja.
            digitalWrite(ledpin[2], LOW); //LED dioda se ugasne.
            inputArray[x] = 3; //nastavimo na 3, da preveri v naslednjem if stavku.
            delay(250); //čas čakanja.
            Serial.print(" "); //nova vrstica v serijski vmesniku.
            Serial.print(3); //vpiše 3 v Serijski vmesnik.
              if (inputArray[x] != randomArray[x]) //Pregleda vrednost, ki jo je uporabnik vnesu.
              {
                fail(); //če uporabnik napačen gumb pretisne, gre na nasledno kodo.       
              }
            x++; //x se poveča za 1.
        }

        if (buttonstate == LOW && button[y] == 5) //potem ko stisneš se prežge LED dioda in se izvrši ton, ter izpiše  vmesnik kateri gumb si stisnu.
        {
            digitalWrite(ledpin[3], HIGH); //modra LED dioda zasveti.
            speakerpin.play(NOTE_C4, 100); //izpusti Tono.
            delay(200); //čas čakanja.
            digitalWrite(ledpin[3], LOW); //LED dioda se ugasne.
            inputArray[x] = 4; //nastavimo na 4, da preveri v naslednjem if stavku.
            delay(250); //čas čakanja.
            Serial.print(" "); //nova vrstica v serijski vmesniku.
            Serial.print(4); //vpiše 4 v Serijski vmesnik.
              if (inputArray[x] != randomArray[x]) //Pregleda vrednost, ki jo je uporabnik vnesu.
              {
                fail(); //če uporabnik napačen gumb pretisne, gre na nasledno kodo.       
              }
            x++; //x se poveča za 1.
          } 
      }
  }
    delay(500);
    turn++; //poveča Turn števec za 1, preden znova zaženete izhodno funkcijo.
}

/*Če uporabnik zgrši se števec resetira in gre od začetka*/
void fail() //funkcija uporablja, če igralec ne ujemajo zaporedje
{ 
  for (int y=0; y<=2; y++) //utripajo LED diode za neuspeh
  { 
    
    digitalWrite(ledpin[0], HIGH); //LED dioda se prežege.
    digitalWrite(ledpin[1], HIGH); //LED dioda se prežege.
    digitalWrite(ledpin[2], HIGH); //LED dioda se prežege.
    digitalWrite(ledpin[3], HIGH); //LED dioda se prežege.
    speakerpin.play(NOTE_G3, 300); //izpusti tono.
    delay(200); //čas čakanja
    digitalWrite(ledpin[0], LOW); //LED dioda se ugasne.
    digitalWrite(ledpin[1], LOW); //LED dioda se ugasne.
    digitalWrite(ledpin[2], LOW); //LED dioda se ugasne.
    digitalWrite(ledpin[3], LOW); //LED dioda se ugasne.
    speakerpin.play(NOTE_C3, 300); //izpusti tono.
    delay(200); //čas čakanja
  }
  delay(500);
  turn = -1; //resetira turn števec in greš nazaj na začetek.
}


