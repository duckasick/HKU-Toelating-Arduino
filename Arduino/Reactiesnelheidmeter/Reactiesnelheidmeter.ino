// Definieer de gebruikte poorten.
const int knopPoort = 2;
const int groenPoort = 3;
const int roodPoort = 4;


// Maak geheugen aan.
int toestand = 0;
int start = 0;
int eind = 0;
unsigned long laatsteTransitie = 1000; // Dit getal begint bewust op 1000 zodat je niet hoeft te wachten zodra de arduino zijn code heeft geladen


void setup() {
 // Stel alle poorten correct in.
 Serial.begin(9600);
 pinMode(knopPoort, INPUT_PULLUP);
 pinMode(groenPoort, OUTPUT);
 pinMode(roodPoort, OUTPUT);
}


void loop() {

 // Lees de invoer.
 bool isKnopIngedrukt = !digitalRead(knopPoort);      // Geeft aan dat de knop gelezen moet worden
 unsigned long huidigeTijd = millis();                // Start een interne teller
 unsigned long wachttijd = random(3000, 10000);       // Kiest een willekeurig getal tussen 3000 en 10000 zodat je niet kan timen wanneer het groene lampje aangaat.


 // Verwerk de invoer.
 unsigned long tijdNaTransitie = huidigeTijd - laatsteTransitie; // Rekent uit hoeveel tijd er na de laatste transitie is verlopen


 // Regel alle transities.
if (toestand == 0 && isKnopIngedrukt && tijdNaTransitie >= 1000) {    // Controleert de toestand, of de knop is ingedrukt en of er een seconde is voorbij gegaan na de laatste toestand om jitter tegen te gaan. 
  digitalWrite(roodPoort, true);                                      // Zet het rode lampje aan.
  laatsteTransitie = huidigeTijd;                                     // Houdt bij wanneer we deze toestand verlaten.
  toestand = 1;                                                       // Zet de toestand een stap verder.
 }

else if (toestand == 1 && isKnopIngedrukt && tijdNaTransitie < wachttijd && tijdNaTransitie > 1000) { // Controleert de toestand, of de knop is ingedrukt voordat het groene lampje aan staat en gaat jitter tegen.
  Serial.println("Niet valsspelen!");                                                                 // Print "Niet valsspelen!"
  digitalWrite(roodPoort, true);                                                                      // Zet het groene...
  digitalWrite(groenPoort, true);                                                                     // En rode lampje aan als waarschuwing.
  laatsteTransitie = huidigeTijd;                                                                     // Houdt bij wanneer we deze toestand verlaten.
  toestand = 3;                                                                                       // Zet de toestand naar de waarschuwings toestand (5).
  } 

else if (toestand == 3 && tijdNaTransitie >= 4000) {                                                  // Controleert of we in de waarschuwings toestand staan, en of er 4 seconden voorbij zijn 
  digitalWrite(roodPoort, false);                                                                     // Zet het groene...
  digitalWrite(groenPoort, false);                                                                    // En rode lampje uit
  toestand = 0;                                                                                       // Zet de toestand terug naar de begintoestand
  }


else if (toestand == 1 && tijdNaTransitie >= wachttijd) {   // Controleert de toestand en vergelijkt de tijd na de laatste transitie met de wachttijd
  digitalWrite(groenPoort, true);                           // Zet het groene lampje aan...
  digitalWrite(roodPoort, false);                           // En de rode uit. 
  start = millis();                                         // Houdt bij wanneer het groene lampje aan gaat.
  laatsteTransitie = huidigeTijd;                           // Houdt bij wanneer we deze toestand verlaten.
  toestand = 2;                                             // Zet de toestand een stap verder
 }

else if (toestand == 2 && isKnopIngedrukt) {                // Controlleert de toestand en of je de knop in drukt. 
  eind = millis();                                           // Houdt bij wanneer jij de knop in klikt.
  Serial.print("Je reactietijd was ");                      // Print het eerste gedeelte van het bericht van jouw reactiesnelheid.
  Serial.print(eind-start);                                 // Rekent uit wat jouw reactiesnelheid is, en print het uit. 
  Serial.println("ms!");                                    // Print "ms!", zodat je weet dat je reactiesnelheid in ms is gemeten. 
  digitalWrite(groenPoort, false);                          // Zet het groene lampje uit.
  laatsteTransitie = huidigeTijd;                           // Houdt bij wanneer we deze toestand verlaten.
  toestand = 0;                                             // Zet de reactiesnelheidmeter terug naar de begintoestand.
 }

}


// verdikkie
