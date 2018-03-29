//
//  main.cpp
//  LAB3
//
//  Created by Hyemi Kim on 2018. 3. 29..
//  Copyright © 2018년 Hyemi Kim. All rights reserved.
//

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;

using namespace std;

int main(int argc, const char * argv[]) {
    
    string imageName ("./lena.jpg");
    if(argc>1){
        imageName = argv[1];
    }
    
    Mat image,resizeImage, grayImage, equalizeImage;
    
    image = imread(imageName.c_str(),IMREAD_COLOR);
    if(image.empty()){
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    resize(image, resizeImage, cvSize(256, 256), 0, 0, CV_INTER_LINEAR);
    
    grayImage = Mat::zeros(resizeImage.size(),resizeImage.type());
    equalizeImage = Mat::zeros(resizeImage.size(),resizeImage.type());
    
    cvtColor(resizeImage,grayImage, CV_BGR2GRAY);
    equalizeHist(grayImage,equalizeImage);
    
    imshow("source image", resizeImage);
    imshow("grayscale image", grayImage);
    imshow("equalize the histogram",equalizeImage);
    
    waitKey(0);
    
    return 0;
}

