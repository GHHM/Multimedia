//
//  main.cpp
//  LAB3_4
//
//  Created by Hyemi Kim on 2018. 4. 12..
//  Copyright © 2018년 Hyemi Kim. All rights reserved.
//

//Derivative Filters
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
    
    Mat image;
    Mat G;
    image = imread(imageName.c_str(),IMREAD_GRAYSCALE);
    G = Mat::zeros(image.size(),image.type());   //copy
    
    if(image.empty()){
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    
    int n = 3;
    int p = 1;
    //int p = (int)(n-n/2))-1;   //padding

    //make 3*3 sobel filter
    float sobelX[3][3] = {{-1,0,1},{-1,0,1},{-1,0,1}};
    float sobelY[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
    
    //Obtain Prewitt operator gx,gy and convolved to g
    for(int y=p;y<image.rows-p;y++){
        for(int x=p;x<image.cols-p;x++){
            int gx =0;
            int gy =0;
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    gx = gx+sobelX[i][j]*image.at<uchar>(x+(i-p),y+(j-p));
                    gy = gy+sobelY[i][j]*image.at<uchar>(x+(i-p),y+(j-p));
                }
            }
            int g = (int)sqrt((gx*gx)+(gy*gy));
            G.at<uchar>(x,y)=g;
        }
    }
    
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display original image", image);
    imshow("Display newImage", G);
    
    waitKey(0);
    return 0;
}
