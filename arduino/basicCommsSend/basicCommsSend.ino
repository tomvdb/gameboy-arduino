// Tom Van den Bon
// 2012/12/21
// Send Data to Gameboy via Link Cable

// Link Cable     Arduino      Desc
// 6              GND          GND
// 5              3            SC
// 2              4            SI
// 3              5            SO

int volatile CLOCK_PIN = 3;
int volatile SO_PIN = 5;

void setup() {                
  pinMode(SO_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  byte dataToSend = 'H';
  byte counter = 0;
  
  for ( counter = 0; counter < 8; counter++ )
  {
    if ( dataToSend & 0x80 )
    {
      Serial.println( "1" );
      digitalWrite( SO_PIN, HIGH );
      digitalWrite( CLOCK_PIN, LOW );
      delayMicroseconds( 50);
      digitalWrite( CLOCK_PIN, HIGH );
      delayMicroseconds( 50);
    }
    else
    {
      Serial.println( "0" );
      digitalWrite( SO_PIN, LOW );
      digitalWrite( CLOCK_PIN, LOW );
      delayMicroseconds( 50);
      digitalWrite( CLOCK_PIN, HIGH );
      delayMicroseconds( 50);
    }
    
    dataToSend = dataToSend << 1;
  }
  delay(10000);
}
