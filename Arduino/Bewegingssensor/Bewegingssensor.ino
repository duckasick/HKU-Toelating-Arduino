// Maak geheugen aan.
long vorigeTijd = -1; // Voorkom dat dt in het begin nul is.
int toestand = 0;
float foutAfegeleide = 0;
float foutInt = 0;
long timer = 0;
long wachttijd = 0;
const int lamp = 2; //port 2 wordt gebruikt voor de LED. 

void setup() {
 Serial.begin(9600);
pinMode(lamp, OUTPUT);   //zet port 2 op output
}

void loop() {
 // Bepaal de tijdstap.
long tijd = millis();
long dt = tijd - vorigeTijd;

wachttijd = tijd - timer;           //Rekent uit hoe lang geleden iemand langs de lamp is gelopen.       

 // Meet de invoer.
 float spanning = analogRead(A0) * (5.0 / 1023.0);
 // Bereken de afgeleide
 float spanningAfgeleide = ((spanning - vorigeSpanning)/dt)*1000; // * 1000, want dat maakt de afgeleide gebruiken wat makkelijker. 



if (spanningAfgeleide <= -2){     // Controlleert of spanningsverandering snel genoeg is. Hoe dichter je bij 0 komt, hoe gevoelliger het systeem is.  
  toestand = 1;                   // Zet de toestand naar 1.
  digitalWrite(lamp, true);       // Zet de lamp aan. 
  timer = millis();               // Start een timer om de wachttijd uit te rekenen
  }


else if (toestand == 1 && wachttijd >= 6000){ // Controleert of de lamp aan staat en of hij lang genoeg heeft gebrand, zodat de lamp niet constant aan en uit gaat.
  toestand = 0;                               // Zet de toestand naar 0.
  digitalWrite(lamp, false);                  // Zet de lamp uit.
}

// Onthoud waarden voor de volgende loop.
 vorigeTijd = tijd;
 vorigeSpanning = spanning;

}
