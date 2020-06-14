 #include <LiquidCrystal.h>
 #include <TimerOne.h>
 #define pwm1 9 //Timer1
 #define pwm2 10 //Timer1
 #define adj_vAC A0
 #define fdbckAC A1
 const int PIN_RS = 13;
 const int PIN_E = 12;
 const int PIN_DB4 = 11;
 const int PIN_DB5 = 8;
 const int PIN_DB6 = 6; 
 const int PIN_DB7 = 5;  

int f_sine=50;//default nilai GANTI DENGAN RUMUS UNTUK ADJUSTABLE
int f_pwm=20000;//Hz //adjustable due to transformer frekwensi primer sebelum difilter, semakin tinggi semakin halus
float sinus[200];  
float phi=3.14;
int flag = 0;
int sample=0;
int adjust_vAC;
int feedbackAC_eror; //feedback AC Volt with DB back to A2 for PID :D
int total_sample;
int A; //amplifier tegangan AC 
int max_power=900;

LiquidCrystal lcd(PIN_RS, PIN_E, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

 void setup()
{
  lcd.begin(16,2);
  lcd.clear();
  total_sample =round((((1000000./f_sine)/(1000000./f_pwm))/2.)); //mencari jumlah sample per satu bukit sinyal 400/2=200
 // ======$
  float T_pwm=(1000000./f_pwm);//periode SPMW=interrupt each50us
  delay(10); // original delay 1000========**********+++++++++========
  pinMode(adj_vAC, INPUT);
  pinMode(fdbckAC, INPUT);
  pinMode(13,OUTPUT);
  A = 0;
  Timer1.initialize(T_pwm);   // initialize Timer1, and set seiap periode dari variabel T_pwm
  Timer1.attachInterrupt(generate_sinus); //interrupt ke fungsi generate_sinus
  //Timer1.pwm(pwm1,(sinus[sample]* A));//nilai sample ada pada fungsi generate_sinus pada attachinterrupt
  //Timer1.pwm(pwm2,(sinus[sample]* A));

  //START Generating Look Up Table for each degree 0-180/half period
  for (int sudut=0;sudut<total_sample;sudut++)//looping sudut sample 0-200
  { 
  float radian= sudut*(180./total_sample)*phi/180;
  sinus[sudut]=sin(radian);
//=====%
   adjust_vAC = round(analogRead(adj_vAC)/4.016);
   feedbackAC_eror = round(analogRead(fdbckAC)/4.016);
   lcd.setCursor(1, 0);
   lcd.print("adj_vAC = ");
   lcd.print(adj_vAC);

 //=======  
   }
  
 //======$
 
}

void loop() 
 {
   
   //======%
    while (feedbackAC_eror < adjust_vAC  )//selama feedback lebih kecil dari input value
    {
     if (A >= max_power)
      {
       adjust_vAC = analogRead(adj_vAC);
       feedbackAC_eror = analogRead(fdbckAC);
      }
     else 
     {
       A = A + 1;
       adjust_vAC = analogRead(adj_vAC);
       feedbackAC_eror = analogRead(fdbckAC); 
     }
   }
   while (feedbackAC_eror>adjust_vAC ) 
   {
     if (A == 0)
     {
       adjust_vAC = analogRead(adj_vAC);
       feedbackAC_eror = analogRead(fdbckAC);
     
     }
     else
     {
       A = A - 1;
       adjust_vAC = analogRead(adj_vAC);
       feedbackAC_eror = analogRead(fdbckAC);
     }
   }
   
   
 } //==================================================================akhir void loop

void generate_sinus()
{
generate();
 }

 void generate()
{
 if(sample>total_sample && flag==0)
   {
   flag=1;
   sample=1;
   } 
 if(sample>total_sample && flag==1)
   {
   flag=0;
   sample=1;
   }
   
 sample++;
 
 if(flag==0)
   {
   Timer1.pwm(pwm1,sinus[sample]*A);
   Timer1.pwm(pwm2,0);
   }
 
 if(flag==1)
   {
   Timer1.pwm(pwm1,0);
   Timer1.pwm(pwm2,sinus[sample]*A);
   }
}
