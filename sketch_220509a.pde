
import processing.serial.*;



Serial myPort;  // Create object from Serial class

int samples = 64;
float[] peak = new float[32];
String val = "010";
String val2 = "010";
int index = 0;
float db = 0;
int conditionG = 0;
float x = 0, y = 0,x2, y2 ;
float[] mu = new float[3];
float[] sigma = new float[3];
float[] weight = new float[3];
int selectG = 3;



void setup() 
{
  size(500,500); 
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 115200);
  while(myPort.available() <0);
  frameRate(115200);
}

void draw() {
    
    val = myPort.readStringUntil('\n');
    
    if(val!=null)
    {
      val2 = val;
      if(val.charAt(0) == 'A')
      {
        if(val.substring(1) != null)
        {
          
          db = Float.valueOf(val.substring(1));
          
        }
      }
      else if(val.charAt(0) == 'u')
      {
        if(val.substring(1) != null)
        {
          if(selectG<2)
          {
            selectG++;
          }
          else
          {
            selectG = 0;
          }
          
          mu[selectG] = Float.valueOf(val.substring(1));
          
        }
      }
      else if(val.charAt(0) == 's')
      {
        if(val.substring(1) != null)
        {
          
          sigma[selectG] = Float.valueOf(val.substring(1));
          
        }
      }
      else if(val.charAt(0) == 'w')
      {
        if(val.substring(1) != null)
        {
          
          weight[selectG] = Float.valueOf(val.substring(1));
          
        }
      }
      else
      {
        if(val.charAt(0) == '9')
        {
          index = val2.charAt(1);
          index -=48;
        }
        else if(val.charAt(0) != '1')
        {
          index = val2.charAt(1);
          index -=38;
        }
        else if(val.charAt(0) != '2')
        {
          index = val2.charAt(1);
          index -=28;
        }
        else if(val.charAt(0) != '3')
        {
          index = val2.charAt(1);
          index -=18;
        }   
      }
      
      fill(255,255,255);
      rect(0,0,1000,700);
      
      if(val.length() > 3)
      {
        if(val.substring(2) != null)
        {
          peak[index] = Float.valueOf(val.substring(2));
        }
      }
      
      if(conditionG == 0)
      {
        
      
      textSize(20);
      
      
       fill(200,0,0);
      
      
      rect(20,60,3*db - 30,20);
      text(db + "dB",3*db ,80);
      
        
      for(int i=0; i< samples/2; i++)
      {
        rect(i*15 + 5, abs(500 - (peak[i]*3)) , 10, (peak[i]*3));
      }
      }
      else
      {
        fill(200,0,0);
        
          x = 0;
          y = 0;
          x2 = 0;
          y2 = 0;
          for(float i = -80; i < 80; i += 0.25) {
            x = x2;
            y = y2;
            x2 = i;
            y2 = 0;
            for(int j =0; j<3; j++)
            {
            y2 = weight[j] *(1/(sigma[j] * sqrt(2 * PI)))*(exp((-1 * sq(x2 - mu[j])) / (2 * sq(sigma[j])) )) + y2;
                  
            }
            text(mu[0],20,20);
            text(mu[1],120,20);
            text(mu[2],240,20);
            text(weight[0],20,60);
            text(weight[1],120,60);
            text(weight[2],240,60);
            
            x2 = map(x2, -40, 40, 0, width);
            y2 = map(y2, 0, 0.2, 0, height);
            //point(x2, y2);
            strokeWeight(2); 
            line(x,500-y, x2, 500-y2);
        } 
      }   
    }
}

void mousePressed()
{
  if(conditionG == 0)
  {
    conditionG=1;
  }
  else
  {
    conditionG = 0;
  }
}
