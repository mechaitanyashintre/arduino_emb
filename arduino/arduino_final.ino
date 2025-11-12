//defining Inputs
#define LS 6 //left sensor
#define RS 7 //right sensor

//defining Outputs...
#define LM1 2 // left motor
#define LM2 3 //left motor
#define RM1 4 // right motor
#define RM2 5 // right motor

const int buttonPin1 = 8;
const int buttonPin2 = 9;
const int buttonPin3 = 10;



int count=0;
int initial=0;
int buttonState=0;

void setup ()
{
pinMode(buttonPin1, INPUT);
digitalWrite(buttonPin1,LOW);
pinMode(buttonPin2, INPUT);
digitalWrite (buttonPin2, LOW);
pinMode(buttonPin3, INPUT);
digitalWrite(buttonPin3, LOW);

Serial.begin(9600);
delay(10);
}
void line()
{
Serial.println("line follower start");
while(count!=0)
{
 if(!digitalRead(LS) && digitalRead(RS))
  {
    Serial.println("Right");
   digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    }

 if(digitalRead(LS) && !digitalRead(RS))
  {
    Serial.println("Left");
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    }
  
if(!digitalRead(LS) && !digitalRead(RS))
  {
    Serial.println("Forward");
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    }
    
 if(digitalRead(LS) && digitalRead(RS))
  {
    {
      Serial.println("Stop");
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    }   
count--;
delay(1000);
Serial.println(count);
forward();
}

}

if (count==0)
{
Serial.println("permanently stop");
digitalWrite(LM1, LOW);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, LOW);
}
}

void forward()
{
if ((digitalRead(LS)) && (digitalRead(RS)))//STOP
{
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    
}
delay (500);
}
void loop()
{
buttonState = digitalRead(buttonPin1);
if (buttonState==HIGH && initial<=0){
Serial.println("Table 1");
count=1;
initial=count;
line();
}

buttonState = digitalRead(buttonPin2);
if (buttonState==HIGH && initial==1){
Serial.println("Table 2");
count=1;
initial=2;
line();
}

buttonState = digitalRead(buttonPin3);
if (buttonState==HIGH && initial==1){
Serial.println("Table 3");
count=2;
initial=3;
line();
}


buttonState = digitalRead(buttonPin3);
if (buttonState==HIGH && initial==2){
Serial.println("Table 3");
count=1;
initial=3;
line();
}


buttonState = digitalRead(buttonPin1);
if (buttonState==HIGH && initial==2){
Serial.println("Table 1");
count=2;
initial=1;
line();
}


buttonState = digitalRead(buttonPin2);
if (buttonState==HIGH && initial==3){
Serial.println("Table 2");
count=2;
initial=2;
line();
}

buttonState = digitalRead(buttonPin1);
if (buttonState==HIGH && initial==3){
Serial.println("Table 1");
count=1;
initial=1;
line();
}






buttonState = digitalRead(buttonPin2);
if (buttonState==HIGH && initial<=0){
Serial.println("Table 2");
count=2;
initial=count;
line();
}



buttonState = digitalRead(buttonPin3);
if (buttonState==HIGH && initial<=0){
Serial.println("Table 3");
count=3;
initial=count;
line();
}




}
