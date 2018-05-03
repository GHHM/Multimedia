//
//  main.cpp
//  LAB4_2
//
//  Created by Hyemi Kim on 2018. 5. 3..
//  Copyright © 2018년 Hyemi Kim. All rights reserved.
//
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    string imageName("./Lena_color.png");
    
    Mat image, imageYCbCr, imageCMY, imageHSV;
    
    image = imread(imageName.c_str(),IMREAD_COLOR);
    if(image.empty()){
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    
    imageYCbCr = Mat::zeros(image.size(), image.type());
    imageCMY = Mat::zeros(image.size(), image.type());
    imageHSV = Mat::zeros(image.size(), image.type());
    
    cvtColor(image, imageYCbCr, CV_BGR2YCrCb);
    cvtColor(image, imageHSV, CV_BGR2HSV);
    
    for(int y=0;y<image.rows;y++){
        for(int x=0;x<image.cols;x++){
            for(int c=0;c<3;c++){
                imageCMY.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(255.0 - image.at<Vec3b>(y,x)[c]);
            }
        }
    }
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Original image", image);
    imshow("YCbCr", imageYCbCr);
    imshow("CMY", imageCMY);
    imshow("HSV", imageHSV);
    
    waitKey(0);
    return 0;
    
}
