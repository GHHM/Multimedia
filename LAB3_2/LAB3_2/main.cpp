//
//  main.cpp
//  LAB3_2
//
//  Created by Hyemi Kim on 2018. 4. 5..
//  Copyright © 2018년 Hyemi Kim. All rights reserved.
//

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
    
    Mat image, newImage;
    image = imread(imageName.c_str(),IMREAD_GRAYSCALE);
    newImage = Mat::zeros(image.size(),image.type());   //copy
    
    if(image.empty()){
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    
    int n = 5;
    double sigma = 0.8;
    double r, s = 2.0 * sigma * sigma;
    int p = ((int)(n-n/2))-1;   //padding
    cout << "padding: ";
    cout << p << std::endl;
    
    //make average mask filter : w
    float w[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            w[i][j] = 1.0/(n*n);
        }
    }
    
    // make gaussian mask filter : w2
    // sum is for normalization
    double sum = 0.0;
    double w2[n][n];
    for (int x = -p; x <= p; x++)
    {
        for(int y = -p; y <= p; y++)
        {
            r = sqrt(x*x + y*y);
            w2[x+2][y+2] = (exp(-(r*r)/s))/(M_PI * s);
            sum +=w2[x+2][y+2];
        }
    }
    
    //normalize
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 5; ++j){
            w2[i][j] /= sum;
            cout << w2[i][j];
            cout << " ";
        }
        cout << "\n";
    }

    for(int y=p;y<image.rows-p;y++){
        for(int x=p;x<image.cols-p;x++){
            int result =0;
            //counting for mask
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    result = result+w2[i][j]*image.at<uchar>(x+(i-p),y+(j-p));
                }
            }
            newImage.at<uchar>(x,y)=result;
        }
    }
    
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display original image", image);
    imshow("Display newImage", newImage);
    
    waitKey(0);
    
    return 0;

}

