//
//  main.cpp
//  LAB3_4
//
//  Created by Hyemi Kim on 2018. 4. 12..
//  Copyright © 2018년 Hyemi Kim. All rights reserved.
//

//Derivative Filters

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    string imageName ("./lena.jpg");
    
    Mat image, gaussImage, L;  //Laplacian
    image = imread(imageName.c_str(),IMREAD_GRAYSCALE);
    gaussImage = Mat::zeros(image.size(),image.type());
    L = Mat::zeros(image.size(),image.type());   //copy
    
    if(image.empty()){
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    
    int p = 1;
    //int p = (int)(n-n/2))-1;   //padding
    
    //Gaussian Blur
    GaussianBlur(image, gaussImage, Size(5 ,5), 0);
    
    //Laplacian Filter
    float lapMask[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    
    for(int y=p;y<image.rows-p;y++){
        for(int x=p;x<image.cols-p;x++){
            int result=0;
            //Iterate mask
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    result = result + lapMask[i][j]*image.at<uchar>(x+(i-p),y+(j-p));
                }
            }
            L.at<uchar>(x,y)= gaussImage.at<uchar>(x,y)+saturate_cast<uchar>(result);
        }
    }
    
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display original image", gaussImage);
    imshow("Display newImage", L);
    
    waitKey(0);
    return 0;
}
