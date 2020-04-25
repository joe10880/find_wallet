
#include <Pixy2.h>
#include <PIDLoop.h>
// This is the main Pixy object 
Pixy2 pixy;
PIDLoop panLoop(200, 0, 400, true);
PIDLoop tiltLoop(200, 0, 500, true);
String colour;
int choose=0,number=0;
int count=5;
int32_t panOffset, tiltOffset;
bool find=false,swite=false;
int u=20,push=20,t=10;
void setup()
{
  Serial.begin(115200);
  pinMode(7,OUTPUT);
  digitalWrite(7,1);
  Serial.println("Which wallet do you want to find?\n Pink\n Yellow\n Green\n");
  pixy.init();
  
  
}

void loop()
{ 
  if(find==false){
    
    
    if(choose==0){
    while (Serial.available()){
    delay(300);
    char text=Serial.read();
    colour+=text;
  }
  colour.trim();
  if(colour.length()>0){
    if(colour=="pink"){
      Serial.println("We will find pink wallet for you");
      choose=1;
    }else if(colour=="yellow"){
      Serial.println("We will find yellow wallet for you");
      choose=2;
    }else if(colour=="green"){
      Serial.println("We will find Green wallet for you");
      choose=3;
    }else{
      Serial.println("We don't have this option for you.\nPlease select again");
    }
    colour="";
    
  }
  }else{
   panOffset=0;
  tiltOffset =0;
  panLoop.update(panOffset);
  tiltLoop.update(tiltOffset);
  pixy.setServos(panLoop.m_command, tiltLoop.m_command);
  delay(500);
  panOffset=1200;
  tiltOffset =0;
  panLoop.update(panOffset);
  tiltLoop.update(tiltOffset);
  pixy.setServos(panLoop.m_command, tiltLoop.m_command);
  delay(500);
  int i; 
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks)
  {
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
       Serial.print(pixy.ccc.blocks[i].m_signature);
       Serial.print(":");
       Serial.println(choose);
      if(pixy.ccc.blocks[i].m_signature==choose){
        Serial.println("I found your wallet");
        find=true; 
           
        break;
      }
    }
  }  
  }
  }else{
    if(number>count){
      //หยุดดัง
      digitalWrite(7,1);
    }else{
      number++;
      digitalWrite(7,0);
    }
    delay(1000);
  }
  
}
