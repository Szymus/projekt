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
}

int main(int argc, char* argv[])
{
    VideoCapture cap(0); // uruchomienie kamery 0

    if (!cap.isOpened())  // jak sie nie uda
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

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
