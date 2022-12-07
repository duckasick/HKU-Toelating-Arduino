// Aangeven welke poort voor wat wordt gebruikt
const int PwmPoort = 5;
const int KnopHoger = 3;
const int KnopLager = 4;

int aantalStanden = 4;			// Hier stel je in hoeveel standen je nodig hebt. 

  
// Geheugen
int toestand = 0; 
long TijdSindsIngedrukt = 0;      // Voor rekensommetje om uit te rekenen of er genoeg tijd sinds de laatste druk is verlopen.     
long tijd = 0;                    //  --
long LaatsteDruk = 0;             //  --


  
void setup() {
 // Stel alle poorten correct in.
 Serial.begin(9600);
 pinMode(PwmPoort, OUTPUT);
 pinMode(KnopHoger, INPUT_PULLUP);
 pinMode(KnopLager, INPUT_PULLUP);
}

 	
void loop() {
tijd = millis();                                                // Hou de huidige tijd bij
TijdSindsIngedrukt = tijd - LaatsteDruk;                        // Berekent wanneer je voor het laatst de knop hebt ingedrukt
  
bool PwmHoger = !digitalRead(KnopHoger);      // Lees de knop voor hogere snelheid af
bool PwmLager = !digitalRead(KnopLager);      // Lees de knop voor lagere snelheid af
  
  if (PwmHoger && toestand - 1 < aantalStanden && TijdSindsIngedrukt > 250) {   // Controleert of de knop is ingedrukt, of de motor niet al volledig aan staat en of er genoeg tijd sinds de laatste knopdruk is verlopen. 
    toestand ++;                                                            // Zet de toestand 1 verder
    LaatsteDruk = millis();                                                 // Houdt bij wanneer de knop voor het laatst is ingedrukt
 	}
    
  else if (PwmLager && toestand - 1 > 0 && TijdSindsIngedrukt > 250) {   // Controleert of de knop is ingedrukt, of de motor niet al uit staat en of er genoeg tijd sinds de laatste knopdruk is verlopen. 
    toestand --;                                                     // Zet de toestand 1 terug       
    LaatsteDruk = millis();                                          // Houdt bij wanneer de knop voor het laatst is ingedrukt
	}
  analogWrite(PwmPoort, toestand * 255 / (aantalStanden - 1));       // Berekent duty-cycle, (-1 is nodig, want anders heb je een extra stand)
}


 