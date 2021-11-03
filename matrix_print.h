
#include "colors.h"
#include "temperatures.h"

//Matrix pins
#define CLK  15
#define OE  33
#define LAT 32
#define A   12
#define B   16
#define C   17
#define D   18

String inputMessage;// message from htm page 

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);


void scroll() {
  // Do nothing -- image doesn't change
  matrix.drawLine(0, 23, 31, 23, matrix.Color333(1, 0, 4));
  matrix.setTextColor(matrix.Color333(rtext, gtext, btext));
  for (int i = 33; i > -100; i--) {
    matrix.setCursor(i, 24);
    matrix.println(inputMessage);
    delay(50);
    matrix.fillRect(0, 24, 32, 8, matrix.Color333(0, 0, 0));

  }
}

void matrixprint() {
  time_t t;
  static time_t last_t;
  struct tm *tm;


  t = time(NULL);
  if (last_t == t) return; // draw each second
  last_t = t;
  tm = localtime(&t);
  //draw some text!
  matrix.setCursor(1, 0);    // start at top left, with one pixel of spacing
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); //
  int temperatureC = sensors.getTempCByIndex(0);
  // print each letter with a rainbow color
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  matrix.setTextColor(matrix.Color333(rtime, gtime, btime));
  int hour_time = tm->tm_hour - 6;
  if (hour_time < 10) {
    matrix.print('0');
  }
  matrix.print(hour_time);
  matrix.print(':');
  int minute_time = tm->tm_min;
  if (minute_time < 10) {
    matrix.print('0');
  }
  matrix.println(minute_time);
  matrix.drawLine(0, 7, 31, 7, matrix.Color333(1, 0, 4));
  matrix.setTextColor(matrix.Color333(rdate, gdate, bdate));
  //matrix.print(' ');
  matrix.setCursor(1, 8);
  int day_time = tm->tm_mday;
  if (day_time < 10) {
    matrix.print('0');
  }
  matrix.print(day_time);
  matrix.print('/');
  int month_time = tm->tm_mon + 1;
  if (month_time < 10) {
    matrix.print('0');
  }
  matrix.println(month_time);
  matrix.drawLine(0, 15, 31, 15, matrix.Color333(1, 0, 4));
  matrix.fillRect(0, 16, 32, 7, matrix.Color333(0, 0, 0));
  matrix.setTextColor(matrix.Color333(rtemp, gtemp, btemp));
  matrix.setCursor(-1, 16);
  matrix.print('I');
  matrix.setCursor(4, 16);
  matrix.print('N');
  matrix.drawPixel(10, 18, matrix.Color333(rtempin, gtempin, btempin));
  matrix.drawPixel(10, 20, matrix.Color333(rtempin, gtempin, btempin));
  matrix.setCursor(12, 16);
  matrix.print(temperatureC);
  matrix.println('C');
  scroll();
  delay(1000);
  matrix.fillRect(0, 16, 32, 7, matrix.Color333(0, 0, 0));
  matrix.setTextColor(matrix.Color333(rtempin, gtempin, btempin));
  matrix.setCursor(0, 16);
  matrix.print('O');
  matrix.setCursor(6, 16);
  matrix.print('U');
  matrix.setCursor(12, 16);
  matrix.print('T');
  matrix.drawPixel(18, 18, matrix.Color333(rtemp, gtemp, btemp));
  matrix.drawPixel(18, 20, matrix.Color333(rtemp, gtemp, btemp));
  matrix.setCursor(20, 16);
  int out_temp = get_temp();
  matrix.print(out_temp);
  scroll();
}
