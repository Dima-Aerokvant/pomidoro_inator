#include <DynamixelWorkbench.h>
bool flag = false;
uint8_t dxl_id[6] = {1, 2, 3, 4, 5, 6}; //айдишники движков
DynamixelWorkbench dxl_wb;  //объектик

void setup() 
{
  Serial.begin(57600); //запуск монитора
  //while(!Serial); // пока не включится монитор - ждем

  dxl_wb.begin("3", 1000000); //говорим через какой порт и с какой скоростью работаем с устр-ми

  //тут "пингуем", инициализация движков. Если не сделать - работать не будут
  dxl_wb.ping(dxl_id[0]);
  dxl_wb.ping(dxl_id[1]);
  dxl_wb.ping(dxl_id[2]);
  dxl_wb.ping(dxl_id[3]);
  dxl_wb.ping(dxl_id[4]);
  dxl_wb.ping(dxl_id[5]);


  //включаю режим шарнира
  //0 ~ 1,023(0x3FF) can be used, and the unit is about 0.111rpm.
  //0 - максимальные обороты без контроля
  //1023 - 
  //For example, if it is set to 300, it is about 33.3 rpm.
  dxl_wb.jointMode(dxl_id[0],50,50);
  dxl_wb.jointMode(dxl_id[1],50,50);
  dxl_wb.jointMode(dxl_id[2],50,50);
  dxl_wb.jointMode(dxl_id[3],50,50);
  dxl_wb.jointMode(dxl_id[4],50,50);
  dxl_wb.jointMode(dxl_id[5],50,50);

  dxl_wb.goalPosition(dxl_id[0], 2048);
  dxl_wb.goalPosition(dxl_id[1], 2048);
  dxl_wb.goalPosition(dxl_id[2], 2048);
  dxl_wb.goalPosition(dxl_id[3], 2048);
  dxl_wb.goalPosition(dxl_id[4], 512);
  delay(1000);
  dxl_wb.goalPosition(dxl_id[5], 512);
  delay(800);
  Serial.println('true');
  
 
}

void loop() 
{
      // заглушка. Пока буфер порта пустой (== 0) - ничего не делать
  // как только появляются данные - программа продолжит работу
  while (Serial.available() == 0)
  {

  }

  // читаю из буфера прилетевшие данные
  // 10/10/10/10/10/10\n
  String strrr = Serial.readStringUntil('\n');
  strrr.trim();
  int m1, m2, m3, m4, m5, m6;
  if (flag == false) {
  sscanf(strrr.c_str(), "%d/%d/%d/%d/%d/%d", &m1, &m2, &m3, &m4, &m5, &m6);
  flag = true;
  }
  dxl_wb.goalPosition(dxl_id[0], m1);
  dxl_wb.goalPosition(dxl_id[1], m2);
  dxl_wb.goalPosition(dxl_id[2], m3); 
  dxl_wb.goalPosition(dxl_id[3], m4); 
  dxl_wb.goalPosition(dxl_id[4], m5);
  delay(1000);
  dxl_wb.goalPosition(dxl_id[5], m6);
  delay(800);
  Serial.println('true');
  flag = false;

  delay (200);
}
