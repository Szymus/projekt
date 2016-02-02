#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;


void CallBackFunc(int event,int x,int y, int flags, void* userdata)

{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Lewy przycisk myszy został kliknięty - pozycja (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
          cout << "prawy przycisk myszy został kliknięty  - pozycja (" << x << ", " << y << ")" << endl;
     }
      //else if ( event == EVENT_MOUSEMOVE )
     //{
     //     cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
//
 //    }
}

int main(int argc, char* argv[])
{
    VideoCapture cap(0); // uruchomienie kamery 0

    if (!cap.isOpened())  // jak sie nie uda
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

 namedWindow("Control", CV_WINDOW_AUTOSIZE); //wygeneruj okno o nazwie "Control"
 
 int iLowH = 85;
 int iHighH = 103;

 int iLowS = 83; 
 int iHighS = 148;

 int iLowV = 148;
 int iHighV = 255;
 
  int iLastX = -1; 
 int iLastY = -1;

 //suwaki w oknie "Control"
 cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
 cvCreateTrackbar("HighH", "Control", &iHighH, 179);

 cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 cvCreateTrackbar("HighS", "Control", &iHighS, 255);

 cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
 cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //szerokosc obrazu
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //wysokosc obrazu	

    cout << "Wymiary ramki : " << dWidth << " x " << dHeight << endl;
    
    Mat imgTmp; //zapisuje tymczasowy obraz
	cap.read(imgTmp);

    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //tworzy okno "MyVideo"
    Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;//tworzy czarny obraz wielkosci kamery

    while (1)
    {
        Mat frame;

        bool bSuccess = cap.read(frame); // wczytywanie klatek z kamery

        if (!bSuccess) //jak sie nie uda wczytac klatki
        {
             cout << "Nie można zczytywać obrazu z kamery" << endl;
             break;
        }
        
        Mat imgHSV;
        
        cvtColor(frame,imgHSV,COLOR_BGR2HSV); //konwertuje obraz z frame z bgr na hsv
        
        Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
        
        
        //morphological opening (remove small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

		//morphological closing (fill small holes in the foreground)
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		
		 Moments oMoments = moments(imgThresholded);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		if (dArea > 10000)
			{
		//calculate the position of the ball
		int posX = dM10 / dArea;
		int posY = dM01 / dArea;        
        
		if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
			{
		//Draw a red line from the previous point to the current point
		line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
   }

		iLastX = posX;
		iLastY = posY;
  }
		
		imshow("Thresholded Image", imgThresholded); //obraz po konwersji
		frame=frame+imgLines;
		imshow("MyVideo", frame); //Pokaż oryginalny obraz
		setMouseCallback("MyVideo",CallBackFunc,NULL);
		
        if (waitKey(30) == 27) //wcisnij esc aby wyjsc
       {
            cout << "esc zostało wciśniętee" << endl;
            break; 
       }
    }
    return 0;

}
