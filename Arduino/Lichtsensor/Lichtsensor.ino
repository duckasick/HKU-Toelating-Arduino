const int lamp = 2;           // Welke port geeft stroom voor de lamp
int toestandlamp = 0;         // Geeft aan of de lamp aan of uit is
float hystereseMarge = 0.2;   // Volt

void setup() {
 Serial.begin(9600);
 pinMode(lamp, OUTPUT);     // Zet port 2 op output modus
}

void loop() {
 // Meet de twee spanningen
 float referentieSpanning = analogRead(A0) * (5.0 / 1023.0);
 float sensorSpanning = analogRead(A1) * (5.0 / 1023.0);

  
if (sensorSpanning >= referentieSpanning) {                               // Controleert of de controlle spanning hoger is dat de referentiespanning  
  referentieSpanning = analogRead(A0) * (5.0 / 1023.0);                   // Zet de referentie spanning naar zijn normale waarde  
  toestandlamp = 0;                                                       // Zet de toestand naar 0
  digitalWrite(lamp, false);                                              // Zet de lamp uit
}
else if (referentieSpanning >= sensorSpanning) {                          // Controleert of de referentiespanning groter is dan de sensor spanning
 referentieSpanning = analogRead(A0) * (5.0 / 1023.0) + hystereseMarge;   // Telt de hystereMarge bij de referenatie spanning op, en zet dat als referentie waarde
 toestandlamp = 1;                                                        // Zet de toestand naar 1
 digitalWrite(lamp, true);                                                // Zet de lamp aan
  }

}
