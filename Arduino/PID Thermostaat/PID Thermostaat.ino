// Definieer de poorten.
const int stuurPoort = 5;

// Geheugen
long vorigeTijd = -1; // Voorkomt dat deze op 0 start. 
float vorigeFout = 0;
float foutInt = 0;
float doelTemp = 1.4; // tot maximaal 1.8, want in deze test opstelling heeft de sensor maximaal 1.8 volt afgelezen

// PID instellingen
const float KP = 62;       
const float KI = 0.004;
const float KD = 150;

// Mini- en maximale actie voor antiwindup beviliging
const float minActie = 0;
const float maxActie = 5;


void setup() {
 // Stel alle poorten correct in.
 Serial.begin(9600);
 pinMode(stuurPoort, OUTPUT);
}
void loop() {
 // Bepaal de tijdstap
 long tijd = millis();
 long dt = tijd - vorigeTijd;

 float huidigeTemp = analogRead(A0) * (5.0 / 1023.0);  // Meet de spanning over de temperatuursensor
 float doelTemp = analogRead(A1) * (5.0 / 1023.0);  // Meet de referentiespanning

 // Bereken de fout en afgeleide voor het PID systeem
 float fout = doelTemp - huidigeTemp;
 float foutAfgeleide = (fout - vorigeFout)/dt;

 // Bepaal de actie volgens de betreffende regeling en pas deze toe.
 float actie = KP*fout + KI*foutInt + KD*foutAfgeleide; // Volt
 float actieBegrenst = max(min(actie, 5), 0); // Begrens tussen 0 en 5 volt.
 float pwmActie = actieBegrenst * 255 / 5; // Zet om naar PWM-bereik.
 analogWrite(stuurPoort, pwmActie);         // Stuur de waarde voor het PWM-bereik naar de juiste poort. 

 // Integreer de fout met anti-windup beveiliging voor het PID systeem. 
 if (actie > minActie && actie < maxActie){
  foutInt = foutInt + fout*dt;
  }

Serial.print(huidigeTemp);
Serial.print("\t");
Serial.print(pwmActie);
Serial.print("\t");
Serial.print(fout);
Serial.print("\t");
Serial.print(foutInt);
Serial.print("\t");
Serial.print("\t");
Serial.print("\t");
Serial.println(doelTemp);

// Onthoud waarden voor de volgende loop.
vorigeFout = fout;
vorigeTijd = tijd;
}
