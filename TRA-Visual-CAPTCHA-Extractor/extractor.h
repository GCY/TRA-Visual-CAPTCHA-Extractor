#ifndef __EXTRACTOR__
#define __EXTRACTOR__

#include<cv.h>
#include<cxcore.h>
#include<highgui.h>

#include <iostream>
#include <map>

class Extractor
{
   public:
      Extractor(char*);
      long Average();		//It depends
      void BackgroundErase();	//It depends
      void ColorFull();
      void NoiseClear();	//It depends
      void Cut();
   private:
      long avg;
      IplImage *image;
};

#endif
