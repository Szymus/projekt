#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

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

    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //tworzy okno "MuVideo"

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

        if (waitKey(30) == 27) //wcisnij esc aby wyjsc
       {
            cout << "esc zostało wciśnięte" << endl;
            break; 
       }
    }
    return 0;

}
