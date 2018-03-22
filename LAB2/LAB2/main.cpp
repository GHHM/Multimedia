//
//  main.cpp
//  LAB2
//
//  Created by Hyemi Kim on 2018. 3. 22..
//  Copyright © 2018년 Hyemi Kim. All rights reserved.
//

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
    
    double alpha = 2.2;
    int beta = 50;
    Mat image, newImage;
    image = imread(imageName.c_str(),IMREAD_COLOR);
    newImage = Mat::zeros(image.size(),image.type());   //copy
    
    if(image.empty()){
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    
    for(int y=0;y<image.rows;y++){
        for(int x=0;x<image.cols;x++){
            for(int c=0;c<3;c++){
                newImage.at<Vec3b>(y,x)[c]=
                saturate_cast<uchar>(alpha * (image.at<Vec3b>(y,x)[c]) + beta);
            }
        }
    }
    
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", image);
    imshow("New image",newImage);
    
    waitKey(0);
    
    return 0;
}

