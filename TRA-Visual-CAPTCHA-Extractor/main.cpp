#include "extractor.h"

int main(int argc,char**argv)
{
   char *name = argv[1];

   if(name){

      Extractor extractor(name);

      /*************pipeline*************/

      extractor.Average();

      extractor.BackgroundErase();

      extractor.ColorFull();

      extractor.NoiseClear();

      extractor.Cut();
   }
   return 0;
}
