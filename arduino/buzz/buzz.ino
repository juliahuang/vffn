
int b1 = 2;
int b2 = 4;
int b3 = 6;
int b4 = 8;
int b5 = 10;
int rs = 12;

boolean b1lock = false;
boolean b2lock = false;
boolean b3lock = false;
boolean b4lock = false;
boolean b5lock = false;

boolean resetlock = false;

boolean lock = false;
boolean test = false;

void setup() {
  Serial.begin(9600);
  pinMode(b1, INPUT);
  digitalWrite(b1, HIGH); 
  pinMode(b2, INPUT);
  digitalWrite(b2, HIGH);  
  pinMode(b3, INPUT);
  digitalWrite(b3, HIGH);  
  pinMode(b4, INPUT);
  digitalWrite(b4, HIGH);  
  pinMode(b5, INPUT);
  digitalWrite(b5, HIGH);
  
  pinMode(rs, INPUT);
  digitalWrite(rs, HIGH);
  
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  
  digitalWrite(9, HIGH);
  digitalWrite(11, HIGH);
}

void loop() {
  if (!lock || test){
    
    if (digitalRead(b1) == LOW && !b1lock) {
      Serial.write('1');    
      b1lock = true;
      resetlock = false;
    } else if (digitalRead(b2) == LOW && !b2lock && digitalRead(rs) != LOW) {
      Serial.write('2');   
      b2lock = true; 
      resetlock = false;
    } else if (digitalRead(b3) == LOW && !b3lock && digitalRead(rs) != LOW) {
      Serial.write('3');   
      b3lock = true; 
      resetlock = false;
    } else if (digitalRead(b4) == LOW && !b4lock && digitalRead(rs) != LOW) {
      Serial.write('4');   
      b4lock = true; 
      resetlock = false;
    } else if (digitalRead(b5) == LOW && !b5lock && digitalRead(rs) != LOW) {
      Serial.write('5');  
      b5lock = true;
      resetlock = false;
    }
  }
  
  if  (digitalRead(rs) == LOW && !resetlock) {
    // lock = false;
    Serial.write("R");
    b1lock = false;
    b2lock = false;
    b3lock = false;
    b4lock = false;
    b5lock = false;
    resetlock = true;
  } 
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {

  }
}


