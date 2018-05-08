//定义接口
const int buttonPin = 2;
const int speed_input = 3;
//定义读取按钮的参数
int buttonState = 0; 
int late_data = 0;
int early_data = 0;
String button_data;
//定义角度的参数
int angle_data = 0;
//定义速度的参数
double speed_data=0;
double s = 1.884;
double looper;
double timer=0;
double pulse=0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(speed_input,INPUT);
  Serial.begin(115200);
  
  attachInterrupt(1,stateChange,FALLING);
}

void loop() {
    //读取角度
    angle_data=analogRead(A0);
    //读取速度
//    speed_data=0;
    if(timer>=0.06)
    {
      looper=pulse/48;
      speed_data=looper*s/0.06;
      pulse=0;
      timer=0;
    }  
    timer=timer+0.02;
   
    //读取按钮
    buttonState = digitalRead(buttonPin);  
    late_data = early_data;
    if (buttonState == HIGH) { early_data = 1; }
    else { early_data = 0; }    
    if(late_data-early_data == -1){button_data=(";down;");}
    else if(late_data-early_data==1){button_data=(";up;");}
    else if(late_data-early_data==0&&late_data+early_data==2){button_data=(";on;");}
    else {button_data=(";off;");}
    //输出
    Serial.print(angle_data);
    Serial.print(button_data);
    Serial.println(speed_data);
    //延迟20毫秒   
    delay(20);   
}

void stateChange()
{
  pulse=pulse+1;
//  Serial.println(pulse);
}
