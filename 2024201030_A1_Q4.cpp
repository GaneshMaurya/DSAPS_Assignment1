#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat myImage;                     // declaring a matrix named myImage//
    namedWindow("PhotoFrame");       // declaring the window to show the image//
    myImage = imread("lakshmi.jpg"); // loading the image named lakshme in the matrix//
    if (myImage.empty())
    { // If the image is not loaded, show an error message//
        cout << "Couldn't load the image." << endl;
        system("pause"); // pause the system and wait for users to press any key//
        return -1;
    }
    imshow("PhotoFrame", myImage); // display the image which is stored in the 'myImage' in the "myWindow" window//
    destroyWindow("Photoframe");   // close the window and release allocate memory//
    waitKey(0);                    // wait till user press any key
    return 0;

    return 0;
}