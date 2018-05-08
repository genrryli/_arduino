//定义接口
const int speed_input = 3;
//定义读取按钮的参数
int get_button=0; 
String button_data;
//定义角度的参数
int angle_data = 0;
//定义速度的参数
double speed_data=0;
double s = 1.884;
double looper;
double timer=0;
double pulse=0;
//定义心率参数
int heart_data=0;

void setup() {
  pinMode(speed_input,INPUT);
  Serial.begin(115200);
  
  attachInterrupt(1,stateChange,FALLING);
}

void loop() {
    //读取角度
    angle_data=analogRead(A0);
    //读取速度
    if(timer>=0.06)
    {
      looper=pulse/48;
      speed_data=looper*s/0.06;
      pulse=0;
      timer=0;
    }  
    timer=timer+0.02;
   
    //读取按钮
    get_button = analogRead(A1);  
    if  (get_button <= 450){button_data=(";ready;");}
    else if(get_button <= 480&&get_button > 450){button_data=(";off;");}
    else if(get_button > 480&&get_button <= 510) {button_data=(";on;");}
    else {button_data=(";hold;");}
    
    //读取心率
    heart_data=analogRead(A2);
    
    //输出
    Serial.print(angle_data);
    Serial.print(button_data);
    Serial.print(speed_data);
    Serial.print(";");
    Serial.println(heart_data);
    //延迟20毫秒   
    delay(20);   
}

void stateChange()
{
  pulse=pulse+1;
//  Serial.println(pulse);
}
