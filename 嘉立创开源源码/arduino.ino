int temp=0;
int count=0;
int state=0;
int nolaser=0;
int nolaser_flag=0;
int temp2=0;
void setup() {
  // put your setup code here, to run once:
   pinMode(13,OUTPUT);
   pinMode(10,INPUT);
   pinMode(11,INPUT);
   Serial.begin(9600);
 
}


int reverse(int pin,int state){
  if(state == 1){
    digitalWrite(pin,0);
    return 0;
    }
   if(state == 0){
    digitalWrite(pin,1);
    return 1;
   }
  }

void loop() {
  // put your main code here, to run repeatedly:
  temp=digitalRead(11);
  temp2=digitalRead(10);
  if(temp == 0  && nolaser_flag==1 ){
    count++;
    nolaser--;
    if(nolaser<0){
      nolaser=0;
      }
    }
     if(temp2 == 0  && nolaser_flag==1 ){
    count++;
    nolaser--;
    if(nolaser<0){
      nolaser=0;
      }
    }
    if(temp == 1 && temp2 ==1){
      nolaser++;
      if(nolaser>100){
        nolaser=100;
        nolaser_flag=1;
        }
        else{
          nolaser_flag=0;
          }
      }
    if(temp == 1 && temp2 ==1){
      count-=10;
      if(count <0){
        count=0;
         
        }
      }
  if(count > 300){
    state=reverse(13,state);
    count=0;
    }
  delay(1);
  Serial.println(temp);
}
