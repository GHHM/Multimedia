//
//  main.cpp
//  LAB4
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
    
    Mat image, newImage,imageY, imageCr, imageCb;
    
    image = imread(imageName.c_str(),IMREAD_COLOR);
    newImage = Mat::zeros(image.size(), image.type());
    imageY = Mat::zeros(image.size(),CV_8UC1);
    imageCr = Mat::zeros(image.size(),CV_8UC1);
    imageCb = Mat::zeros(image.size(),CV_8UC1);
    
    if(image.empty()){
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    
    for(int y=0;y<newImage.rows;y++){
        for(int x=0;x<newImage.cols;x++){
            //get RGB value
            int r=image.at<Vec3b>(y,x)[0];
            int g=image.at<Vec3b>(y,x)[1];
            int b=image.at<Vec3b>(y,x)[2];
        
            //RGB to YCbCr
            //nomalize
            float fr = (float)r/255.0;
            float fg = (float)g/255.0;
            float fb = (float)b/255.0;
            
            float Y = (float)(65.481 * fr + 128.553 * fg + 24.966 * fb)+16;
            float Cb = (float)(-37.797 * fr -74.203 * fg + 112 * fb)+128;
            float Cr = (float)(112 * fr -93.786 * fg -18.214 * fb)+128;
            
            cout << "Y Cb Cr : " << Y << " "<< Cb<< " "<<Cr << std::endl;
            
            newImage.at<Vec3b>(y,x)[0] = Y;
            newImage.at<Vec3b>(y,x)[1] = Cb;
            newImage.at<Vec3b>(y,x)[2] = Cr;
            
            imageY.at<uchar>(y,x)=Y;
            imageCr.at<uchar>(y,x)=Cb;
            imageCb.at<uchar>(y,x)=Cr;
        }
    }
    
    //cvtColor(image, newImage, CV_BGR2YCrCb);

    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Original image", image);
    imshow("Display newimage", newImage);
    imshow("Display R", imageY);
    imshow("Display G", imageCr);
    imshow("Display B", imageCb);
    
    waitKey(0);
    return 0;
}
