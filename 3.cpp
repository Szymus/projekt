#include "opencv2/highgui/highgui.hpp"
#include <iostream>

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
      else if ( event == EVENT_MOUSEMOVE )
     {
          cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

     }
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

 int iLowH = 0;
 int iHighH = 179;

 int iLowS = 0; 
 int iHighS = 255;

 int iLowV = 0;
 int iHighV = 255;

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

    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //tworzy okno "MyVideo"

    while (1)
    {
        Mat frame;

        bool bSuccess = cap.read(frame); // wczytywanie klatek z kamery

        if (!bSuccess) //jak sie nie uda wczytac klatki
        {
             cout << "Nie można zczytywać obrazu z kamery" << endl;
             break;
        }

        imshow("MyVideo", frame); //pokaz frame w oknie "MyVideo" 
        
		setMouseCallback("MyVideo",CallBackFunc,NULL);
		
        if (waitKey(30) == 27) //wcisnij esc aby wyjsc
       {
            cout << "esc zostało wciśniętee" << endl;
            break; 
       }
    }
    return 0;

}
