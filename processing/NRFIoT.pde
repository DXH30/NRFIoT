import processing.serial.*;
Serial myPort;
int x = 0;

PShape sapi;

void setup() {
  //size(600, 400, P3D); // Uncomment untuk menggunakan shape 3D
  size(600, 400);
  //println(Serial.list());  //list of available serial ports
  //String portName = Serial.list()[0]; //replace 0 with whatever port you want to use
  String portName = "/dev/ttyUSB0"; // Uncomment bagian diatas untuk menggunakan Serial.list[0]
  myPort = new Serial(this, portName, 9600);
  //sapi = loadShape("sapi.obj");
  //sapi.scale(50.0);
  background(0);
}

// Timer bisa diatur untuk mengatur frekuensi sampling
String val;
float rad_to_deg = 180.0/PI;
void draw() {
  //background(0);
  //lights();
  //translate(width/2, height/2 +100, -200);
  if(myPort.available() != 0) {
    val = myPort.readStringUntil('\n');
 if (val != null) {
        String[] data = val.split(",");
        int panjang = data.length;
        if (panjang == 7) {
          print("|ax : "); print(data[0]); print("\t");
          print("|ay : "); print(data[1]); print("\t");
          print("|az : "); print(data[2]);   
          print("|gx : "); print(data[3]); print("\t");
          print("|gy : "); print(data[4]); print("\t");
          print("|gz : "); print(data[5]); print("\t");
          print("|d  : "); print(data[6]); print("\t");
          print("|");
          float ax = Float.parseFloat(data[0]), ang_x = ax / 16384.0;
          float ay = Float.parseFloat(data[1]), ang_y = ay / 16384.0;
          float az = Float.parseFloat(data[2]), ang_z = az / 16384.0;
          float gx = Float.parseFloat(data[3]), gyr_x = gx / 131.0;
          float gy = Float.parseFloat(data[4]), gyr_y = gy / 131.0;
          float gz = Float.parseFloat(data[5]), gyr_z = gz / 131.0;
          float d = Float.parseFloat(data[6]);
          int skala = 10;
          
          // Definisikan nilai Accelerometer dalam derajat
          //float rad_to_deg = 180.0/PI; //Rumus Euler untuk menentukan ang_x dan ang_y dari data raw MPU6050
          //float ang_x = (atan((ay)/sqrt(pow((ax),2) + pow((az),2)))*rad_to_deg);
          //float ang_y = ((atan(-1*(ax)/sqrt(pow((ay),2) + pow((az),2)))*rad_to_deg));
          stroke(50, 100, 100);
          line(x, height, x, height - ang_x*skala);
          stroke(100, 50, 100);
          line(x, height, x, height - ang_y*skala);
          stroke(100, 100, 50);
          line(x, height, x, height - ang_z*skala);
          stroke(50, 50, 100);
          line(x, height, x, height - gyr_x*skala);
          stroke(50, 100, 50);
          line(x, height, x, height - gyr_y*skala);
          stroke(100, 50, 50);
          line(x, height, x, height - gyr_z*skala);
          //print("ax : ");print(ang_x);
          //print("ay : ");print(ang_y);
          //print("az : ");print(ang_z);
          //print("gx : ");print(gyr_x);
          //print("gy : ");print(gyr_y);
          //print("gz : ");print(gyr_z);
          //print(PI);
          //rotateY(ang_y);
          //rotateZ(ang_z);
          
        }
        //print("\n");
      }
      if (x >=width) {
      x=0;
      background(0);
      }
      x++;
  //}
    //stroke(90, 76, 99);
    //if (x >=width) {
    //  x=0;
    //  background(0);
  }
    //x++;
}

void serialEvent(Serial myPort) {
 
}
