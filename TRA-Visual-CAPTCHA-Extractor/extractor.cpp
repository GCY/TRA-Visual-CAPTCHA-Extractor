#include "extractor.h"

Extractor::Extractor(char *name)
{
   image = cvLoadImage(name,1);
}

long Extractor::Average()
{
   cvSmooth(image,image,CV_BLUR);

   avg = 0;

   for(int y = 0;y < 3;++y){
      for(int x = 0;x < 3;++x){
	 long temp = 0;
	 temp += image->imageData[y * image->widthStep + (x * 3)] + image->imageData[y * image->widthStep + (x * 3) + 1] + image->imageData[y * image->widthStep + (x * 3) + 2];
	 avg += temp / 3;
      }
   }


   for(int y = image->height - 1;y > image->height - 4;--y){
      for(int x = 0;x < 3;++x){
	 long temp = 0;
	 temp += image->imageData[y * image->widthStep + (x * 3)] + image->imageData[y * image->widthStep + (x * 3) + 1] + image->imageData[y * image->widthStep + (x * 3) + 2];
	 avg += temp / 3;
      }
   }

   for(int y = 0;y < 3;++y){
      for(int x = image->width - 1;x > image->width - 4;--x){
	 long temp = 0;
	 temp += image->imageData[y * image->widthStep + (x * 3)] + image->imageData[y * image->widthStep + (x * 3) + 1] + image->imageData[y * image->widthStep + (x * 3) + 2];
	 avg += temp / 3;
      }
   }

   for(int y = image->height - 1;y > image->height - 4;--y){
      for(int x = image->width - 1;x > image->width - 4;--x){
	 long temp = 0;
	 temp += image->imageData[y * image->widthStep + (x * 3)] + image->imageData[y * image->widthStep + (x * 3) + 1] + image->imageData[y * image->widthStep + (x * 3) + 2];
	 avg += temp / 3;
      }
   }

   avg /= 36;


   return avg ;
}

void Extractor::BackgroundErase()
{
   long range = 20;

   for(int y = 0;y < image->height;++y){
      for(int x = 0;x < image->widthStep;++x){
	 long temp = (image->imageData[y * image->widthStep + x] + 
	       image->imageData[y * image->widthStep + x + 1] +
	       image->imageData[y * image->widthStep + x + 2]) / 3;
	 if(temp  < (avg + range) && temp > (avg - range)){
	    image->imageData[y * image->widthStep + x] = image->imageData[y * image->widthStep + x + 1] = image->imageData[y * image->widthStep + x + 2] = 255;
	 }
      }
   }
}

void Extractor::ColorFull()
{
   for(int y = 0;y < image->height;++y){
      for(int x = 0;x < image->widthStep - 3;x += 3){
	 long temp = (image->imageData[y * image->widthStep + x] + 
	       image->imageData[y * image->widthStep + x + 1] +
	       image->imageData[y * image->widthStep + x + 2]) / 3;
	 if(temp > 0){
	    image->imageData[y * image->widthStep + x] = image->imageData[y * image->widthStep + x + 1] = image->imageData[y * image->widthStep + x + 2] = 0;
	 }
      }
   }
}

void Extractor::NoiseClear()
{
   int range = 20;
   IplImage *itemp = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);
   cvCopy(image,itemp);

   for(int y = 0;y < itemp->height;++y){
      for(int x = 0;x < itemp->widthStep - 3;x += 3){
	 long temp = (itemp->imageData[y * itemp->widthStep + x] + 
	       itemp->imageData[y * itemp->widthStep + x + 1] +
	       itemp->imageData[y * itemp->widthStep + x + 2]) / 3;

	 long ref =  (itemp->imageData[(y - 1) * itemp->widthStep + x] + 
	       itemp->imageData[(y - 1) * itemp->widthStep + x + 1] +
	       itemp->imageData[(y - 1) * itemp->widthStep + x + 2] / 3)
	    +
	    (itemp->imageData[(y + 1) * itemp->widthStep + x]  +
	     itemp->imageData[(y + 1) * itemp->widthStep + x + 1] +
	     itemp->imageData[(y + 1) * itemp->widthStep + x + 1] / 3)
	    +
	    (itemp->imageData[y * itemp->widthStep + (x + 3)] + 
	     itemp->imageData[y * itemp->widthStep + (x + 3) + 1] +
	     itemp->imageData[y * itemp->widthStep + (x + 3) + 2] / 3)
	    +
	    (itemp->imageData[y * itemp->widthStep + (x - 3)] + 
	     itemp->imageData[y * itemp->widthStep + (x - 3) + 1] +
	     itemp->imageData[y * itemp->widthStep + (x - 3) + 2] / 3)
	    +
	    (itemp->imageData[(y + 1) * itemp->widthStep + (x - 3)]  +
	     itemp->imageData[(y + 1) * itemp->widthStep + (x - 3) + 1] +
	     itemp->imageData[(y + 1) * itemp->widthStep + (x - 3) + 1] / 3)
	    +
	    (itemp->imageData[(y + 1) * itemp->widthStep + (x + 3)]  +
	     itemp->imageData[(y + 1) * itemp->widthStep + (x + 3) + 1] +
	     itemp->imageData[(y + 1) * itemp->widthStep + (x + 3) + 1] / 3)
	    +
	    (itemp->imageData[(y - 1) * itemp->widthStep + (x + 3)] + 
	     itemp->imageData[(y - 1) * itemp->widthStep + (x + 3) + 1] +
	     itemp->imageData[(y - 1) * itemp->widthStep + (x + 3) + 2] / 3)
	    +
	    (itemp->imageData[(y - 1) * itemp->widthStep + (x - 3)] + 
	     itemp->imageData[(y - 1) * itemp->widthStep + (x - 3) + 1] +
	     itemp->imageData[(y - 1) * itemp->widthStep + (x - 3) + 2] / 3)
	    ;

	 ref /= 8;

	 if((temp + range) < ref){
	    image->imageData[y * image->widthStep + x] = image->imageData[y * image->widthStep + x + 1] = image->imageData[y * image->widthStep + x + 2] = 255;
	 }
      }
   }
}

void Extractor::Cut()
{
   IplImage *gray = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U ,1);
   cvCvtColor(image,gray,CV_RGB2GRAY);

   cvCanny(gray,gray,30,90);
   cvSmooth(gray,gray,CV_BLUR);
   cvSmooth(gray,gray,CV_BLUR);
   cvSmooth(gray,gray,CV_BLUR);

   std::multimap<int,CvRect> list;

   CvMemStorage* storage = cvCreateMemStorage( 0 );
   CvSeq* contours = NULL;
   cvFindContours(gray, storage, &contours, sizeof( CvContour ), CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
   for( ; contours != NULL; contours = contours->h_next ){
      CvRect rect = cvBoundingRect( contours, 0 );
      //cvRectangle(image, cvPoint( rect.x, rect.y ),cvPoint( rect.x + rect.width, rect.y + rect.height ), cvScalar(0,0,255), 0 );
      list.insert(std::make_pair(rect.width * rect.height,rect));
   }

   //cvSaveImage("find.jpg",image);

   
   int captcha_numbers = 5;
   std::multimap<int,CvRect> result;
   std::multimap<int,CvRect>::reverse_iterator rit = list.rbegin();
   for(int i = 0;rit != list.rend() && i < captcha_numbers;++rit,++i){
      result.insert(std::make_pair(rit->second.x,rit->second));
   }

   char name[] = "1.jpg";
   std::multimap<int,CvRect>::iterator it = result.begin();
   for(;it != result.end();++it){
      cvSetImageROI(image,it->second);
      cvSaveImage(name,image);
      name[0] += 1;
      //std::cout << it->first << std::endl;
   }
}
