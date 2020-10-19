
void jedan(){
  digitalWrite(8, 0); //A
  digitalWrite(7, 1); //B
  digitalWrite(10, 1);//C
  digitalWrite(11, 0);//D
  digitalWrite(12, 0);//E
  digitalWrite(13, 0);//F
  digitalWrite(0, 0);//G
  digitalWrite(6,0);

}
void dva(){
  digitalWrite(8, 1); //A
  digitalWrite(7, 1); //B
  digitalWrite(10, 0);//C
  digitalWrite(11, 1);//D
  digitalWrite(12, 1);//E
  digitalWrite(13, 0);//F
  digitalWrite(0, 1);//G
  digitalWrite(6,0);
 
}
void tri(){
  digitalWrite(8, 1); //A
  digitalWrite(7, 1); //B
  digitalWrite(10, 1);//C
  digitalWrite(11, 1);//D
  digitalWrite(12, 0);//E
  digitalWrite(13, 0);//F
  digitalWrite(0, 1);//G
  digitalWrite(6,0);
 
}
void cetiri(){
  digitalWrite(8, 0); //A
  digitalWrite(7, 1); //B
  digitalWrite(10, 1);//C
  digitalWrite(11, 0);//D
  digitalWrite(12, 0);//E
  digitalWrite(13, 1);//F
  digitalWrite(0, 1);//G
  digitalWrite(6,0);
 
}
void pet(){
  digitalWrite(8, 1); //A
  digitalWrite(7, 0); //B
  digitalWrite(10, 1);//C
  digitalWrite(11, 1);//D
  digitalWrite(12, 0);//E
  digitalWrite(13, 1);//F
  digitalWrite(0, 1);//G
  digitalWrite(6,0);
 
}
void sest(){
  digitalWrite(8, 1); //A
  digitalWrite(7, 0); //B
  digitalWrite(10, 1);//C
  digitalWrite(11, 1);//D
  digitalWrite(12, 1);//E
  digitalWrite(13, 1);//F
  digitalWrite(0, 1);//G
  digitalWrite(6,0);
 
}
void sedam(){
  digitalWrite(8, 1);
  digitalWrite(7, 1);
  digitalWrite(10, 1);
  digitalWrite(11, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
  digitalWrite(0, 0);
  digitalWrite(6,0);
}
void osam(){
  digitalWrite(8, 1); //A
  digitalWrite(7, 1); //B
  digitalWrite(10, 1);//C
  digitalWrite(11, 1);//D
  digitalWrite(12, 1);//E
  digitalWrite(13, 1);//F
  digitalWrite(0, 1);//G
  digitalWrite(6,0);
 
}
void devet(){
  digitalWrite(8, 1); //A
  digitalWrite(7, 1); //B
  digitalWrite(10, 1);//C
  digitalWrite(11, 1);//D
  digitalWrite(12, 0);//E
  digitalWrite(13, 1);//F
  digitalWrite(0, 1);//G
  digitalWrite(6,0);
 
}
void nula(){
  digitalWrite(8, 1); //A
  digitalWrite(7, 1); //B
  digitalWrite(10, 1);//C
  digitalWrite(11, 1);//D
  digitalWrite(12, 1);//E
  digitalWrite(13, 1);//F
  digitalWrite(0, 0);//G
  digitalWrite(6,0);
 
}
void prva(){
  digitalWrite(6,HIGH);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
}
void druga(){
  digitalWrite(3, LOW);
  digitalWrite(2, HIGH);
}

void ugasi_crvene(){
  digitalWrite(3, HIGH);
  digitalWrite(2, HIGH);
}
void prva_plava(){
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}
void druga_plava(){
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
}

void ugasi_plave(){
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}

void pisi(int a, int pozicija, int vrsta){
  if(a==1) jedan();
  if(a==2) dva();
  if(a==3) tri();
  if(a==4) cetiri();
  if(a==5) pet();
  if(a==6) sest();
  if(a==7) sedam();
  if(a==8) osam();
  if(a==9) devet();
  if(a==0) nula();

  if(vrsta==1){
    ugasi_plave();
    if(pozicija==1) prva();
    if(pozicija==2) druga();
  }
  if(vrsta==2){
    ugasi_crvene();
    if(pozicija==1) prva_plava();
    if(pozicija==2) druga_plava();
  }
  delayMicroseconds(300);
}
int ADCsingleREAD(uint8_t adctouse)
{
    int ADCval;

    ADMUX = adctouse;         // use #1 ADC
    ADMUX |= ( (1<<REFS0) );   // use AVcc as the reference
    ADMUX &= ~(1 << ADLAR);   // clear for 10 bit resolution
    
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale for 8Mhz
    ADCSRA |= (1 << ADEN);    // Enable the ADC

    ADCSRA |= (1 << ADSC);    // Start the ADC conversion

    while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish 


    ADCval = ADCL;
    ADCval = (ADCH << 8) + ADCval;    // ADCH is read so ADC can be updated again

    return ADCval;
}
float stp=5.12;
void setup() {
  
    pinMode(0, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);

    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(20, OUTPUT);
    pinMode(21, OUTPUT);

    pinMode(14, INPUT);
    pinMode(19, INPUT);
    pinMode(9, OUTPUT);
    Serial.begin(9600);

    pinMode(15, INPUT);
    
}
void loop() {
  UCSRB =0b00000000;
  int niz[2]={0,0};
  int sensorValue = ADCsingleREAD(5);
  float voltage = sensorValue* (5.0/ 1024.0); //daje napon od 0-100 treba pomnozit sa 200 da se dobiju rez
  int voltage10=voltage*10;
  int i=1;
  while(voltage10>0){
    niz[i]=voltage10%10;
    voltage10=voltage10/10;
    i--;
  }
  pisi(niz[0],1,1);
  pisi(niz[1],2,1);

  niz[0]=0;
  niz[1]=0;
  sensorValue = ADCsingleREAD(0);
  voltage = sensorValue* (9.7*5.0/ 1024.0);
  voltage10=voltage;
  i=1;
  while(voltage10>0){
    niz[i]=voltage10%10;
    voltage10=voltage10/10;
    i--;
  }
  pisi(niz[0],1,2);
  pisi(niz[1],2,2);
  

  if(ADCsingleREAD(1)*5.0/1024.0>4.0){
    stp=stp+5.12;
    delay(50);
  }
  analogWrite(9,stp);
 
}
