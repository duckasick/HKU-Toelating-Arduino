// Definieer de gebruikte poorten.
const int knopPoort = 2;
const int groenPoort = 3;
const int geelPoort = 4;
const int roodPoort = 5;
// Maak geheugen aan.
int toestand = 0;
int start = 0;
unsigned long laatsteTransitie = 0;
void setup() {


 // Stel alle poorten correct in.
 Serial.begin(9600);
 pinMode(knopPoort, INPUT_PULLUP);
 pinMode(groenPoort, OUTPUT);
 pinMode(geelPoort, OUTPUT);
 pinMode(roodPoort, OUTPUT);
 digitalWrite(roodPoort, true);
}

void loop() {
 // Lees de invoer.
 bool isKnopIngedrukt = !digitalRead(knopPoort);
 unsigned long huidigeTijd = millis();)



 // Regel alle transities. (Nu is nog maar de eerste geïmplementeerd.)
 unsigned long tijdNaTransitie = huidigeTijd - laatsteTransitie;
 if (toestand == 0 && isKnopIngedrukt && wachttijd != 0) {
 digitalWrite(roodPoort, false);
 digitalWrite(groenPoort, true);
 toestand = 1;
 laatsteTransitie = huidigeTijd;
 }
else if (toestand == 1 && tijdNaTransitie >= 500) {
 digitalWrite(geelPoort, true);
 digitalWrite(groenPoort, false);
 toestand = 2;
 laatsteTransitie = huidigeTijd;
 }
else if (toestand == 2 && tijdNaTransitie >= 500) {
 digitalWrite(roodPoort, true);
 digitalWrite(geelPoort, false);
 toestand = 0;
 laatsteTransitie = huidigeTijd;
 }

}


 }

 
