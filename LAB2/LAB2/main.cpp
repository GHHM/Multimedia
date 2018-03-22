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
    string imageName2 ("./HappyRabbit.jpg");

    if(argc>1){
        imageName = argv[1];
    }
    
    double alpha = 0.3;
    double beta = 1-alpha;
    Mat image1, resize_image1, image2, newImage;
    
    image1 = imread(imageName.c_str(),IMREAD_COLOR);
    image2 = imread(imageName2.c_str(),IMREAD_COLOR);
    newImage = Mat::zeros(image2.size(),image2.type());   //copy
    
    if(image1.empty()||image2.empty()){
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    
    for(int y=0;y<newImage.rows;y++){
        for(int x=0;x<newImage.cols;x++){
            for(int c=0;c<3;c++){
                newImage.at<Vec3b>(y,x)[c]=
                saturate_cast<uchar>(alpha * (image1.at<Vec3b>(y,x)[c]) + beta*(image2.at<Vec3b>(y,x)[c]));
            }
        }
    }
    
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window1", image1);
    imshow("Display window2", image2);
    imshow("New image",newImage);
    
    waitKey(0);
    
    return 0;
}

