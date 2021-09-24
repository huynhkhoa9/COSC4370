#include <iostream>
#include "BMP.h"
#include <cmath>

struct Color
{
  float red, green, blue, alpha;
};

void draw8WayPoints(BMP& bmpNew, int x, int y, int centerX, int centerY, Color& color)
{
  bmpNew.set_pixel(x, y, 255, 255, 255, 0);
  bmpNew.set_pixel(y, x, 255, 255, 255, 0);
  bmpNew.set_pixel((-x+centerX) + centerX, y,255, 255, 255, 0);
  bmpNew.set_pixel((-y+centerY) + centerY, x,255, 255, 255, 0);
  bmpNew.set_pixel((-x+centerX) + centerX, (-y+centerY) + centerY,255, 255, 255, 0);
  bmpNew.set_pixel((-y+centerY) + centerY, (-x+centerX) + centerX,255, 255, 255, 0);
  bmpNew.set_pixel(x, (-y+centerY) + centerY, 255, 255, 255, 0);
  bmpNew.set_pixel(y, (-x+centerX) + centerX, 255, 255, 255, 0);
}

void drawCircle(BMP& bmpNew, int centerX, int centerY, int radius, Color&& color)
{
  int x = centerX;
  int y = centerY + radius;
  int d = 1 - radius;
  int deltaE= 3;
  int deltaSE= -2 *radius+ 5;  
  draw8WayPoints(bmpNew, x, y, centerX, centerY, color);
  while(y > x)
  {
    if (d < 0) 
    {      
      d +=deltaE;
      deltaE+= 2;
      deltaSE += 2; 
    }
    else 
    { 
      d += deltaSE;
      deltaE+= 2;
      deltaSE += 4; 
      y--; 
    } 
    x++;
    draw8WayPoints(bmpNew, x, y, centerX, centerY, color);
  }
}


int main() 
{
  int canvasWidth = 1600;
  int canvasHeight = 800;

  BMP bmpNew(canvasWidth,canvasHeight,false);
  bmpNew.fill_region(0, 0, canvasWidth, canvasHeight, 0, 0, 0, 0);
  
  //drawCircle(bmpNew, 500, 500, 200, Color{255,255,255,0});
  int d = -11;
  int a = 786;
  int b = 384;

  int aSquared = a*a;
  int bSquared = b*b;

  int x = 0;
  int y = b;

  while(bSquared*(x+1) <= aSquared*(y-0.5f))
  {
    if(d < 0) //Choose E
    {
      d+= bSquared*(2*x + 3);
    }
    else // Choose SE
    {
      d+= (bSquared*(2*x +3) + aSquared*(-2*y+2));
      y--;
    }
    x++;
    bmpNew.set_pixel(x+800, y+400, 255, 255, 255, 0);
    bmpNew.set_pixel(-x+800, y+400, 255, 255, 255, 0);//-x,y

  }
 
  d= bSquared*((x+0.5f)*(x+0.5f)) + aSquared *((y-1)*(y-1)) - aSquared*bSquared;
  while( y >= 0)
  {
    if(d < 0 ) //Choose SE
    {
      d+= (bSquared*(2*x +2) + aSquared*(-2*y+3));
      x++;
    }
    else//Choose S
    {
      d+= (aSquared * (-2*y + 3));
    } 
    y--;
    
    bmpNew.set_pixel(x+800, y+400, 255, 255, 255, 0);
    bmpNew.set_pixel(-x+800, y+400, 255, 255, 255, 0);//-x,y

  }


  bmpNew.write("output.bmp");
}