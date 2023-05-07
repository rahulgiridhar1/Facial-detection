// face detection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;

priority_queue<int> pq;

bool compt(const Point& one, const Point& two, const Point& three, const Point& four) {
    return ((one.x > three.x && two.x > four.x));
}
int main()
{
   
    CascadeClassifier faceDetect;
    if (!faceDetect.load("C:\\Users\\rahul\\Downloads\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml")) {
        cout << "Did not load image" << endl;
            exit(0);
    }

    //images to test = IMG-7744 & IMG-6947
    char path[100] = "C:\\gs\\IMG-6447.jpg";
    cout << "Type image location in computer: " << endl;
    cin.getline(path, 100);
   
    Mat img = imread(path, IMREAD_UNCHANGED);
    Mat cropped[3];
    Mat faceROI[3];
    double area = 0;
    if (img.empty()) {
        cout << "Did not load image" << endl;

    }
    else {
        
        cout << "Image found" << endl;
       

        vector<Rect> face;
        vector<pair<Point, Point>> vec(1);
        vec[0].first = Point(0);
        vec[0].second = Point(0);
        faceDetect.detectMultiScale(img, face);

        for (int i = 0; i < face.size(); i++) {
            //faceROI[i] = img(face[i]);
            //cropped[i] = faceROI[i];
            Point pt1(face[i].x, face[i].y);
            Point pt2((face[i].x + face[i].height), (face[i].y + face[i].width));
            /*if (compt(pt1, pt2, vec[0].first, vec[0].second)) {
                faceROI[0] = img(face[i]);
                cropped[0] = faceROI[0];
                vec[0].first = pt1;
                vec[0].second = pt2;
            }
            */
            if (face[i].area() > area) {
                rectangle(img, pt1, pt2, Scalar(0, 0, 255), 2, 8, 0);
                area = face[i].area();
            }
            else {
                continue;
            }
        }
        int index = 0;
        area = 0;
        double cool = 0;
        for (int i = 0; i < face.size(); i++) {
            //faceROI[i] = img(face[i]);
            //cropped[i] = faceROI[i];
            //double area = 0;
            if (face[i].area() > area) {
                area = face[i].area();
                //index = i;
                //faceROI[0] = img(face[i]);
                cropped[0] = img(face[i]);
                cool = face[i].area();
            }

            else {
                //face[i].area() = 0;
                img(face[i]).resize(0);
                //face.erase(face.begin() + i);
            }
            
        }
        imwrite("C:\\gs\\output.jpg", img);

        cout << "Detected a face" << endl;
   
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
