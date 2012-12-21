// Tom Van den Bon
// 2012/12/21
// Send Data to Gameboy via Link Cable

// Link Cable     Arduino      Desc
// 6              GND          GND
// 5              3            SC
// 2              4            SI
// 3              5            SO

// the setup routine runs once when you press reset:
int volatile SI_PIN = 4;
int volatile data = 0;
int volatile counter = 0;
int volatile val = 0;

unsigned volatile long lastReceive = 0;

void setup() {                
  pinMode(SI_PIN, INPUT);
  digitalWrite( SI_PIN, HIGH);
  Serial.begin(9600);
  attachInterrupt( 0, clock, RISING );
}

void clock()
{
  unsigned long t = 0;
  
  if ( lastReceive > 0 )
  {
    if ( micros() - lastReceive > 120 )  // too long, must be a new sequence (takes about 120 microsecs for a bit)
    {
      counter = 0;
      val = 0;      
    }
  }
       
  data = digitalRead(SI_PIN);
  
  if ( data == HIGH )
    val |= ( 1 << (7-counter) );
    
  if ( counter == 7 )
  {
    Serial.println( val, DEC );    
    val = 0;
    counter = -1;
  }
    
  counter++;
  lastReceive = micros();
}

// the loop routine runs over and over again forever:
void loop() {
}
