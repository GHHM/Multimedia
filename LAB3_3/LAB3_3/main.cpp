//
//  main.cpp
//  LAB3_3
//
//  Created by Hyemi Kim on 2018. 4. 12..
//  Copyright © 2018년 Hyemi Kim. All rights reserved.
//

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    string imageName ("./lena_noise.png");
    
    Mat image, gaussImage, M;  //Median
    image = imread(imageName.c_str(),IMREAD_GRAYSCALE);
    M = Mat::zeros(image.size(),image.type());   //copy
    
    if(image.empty()){
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    
    int p = 1;
    //int p = (int)(n-n/2))-1;   //padding
    
    //Median Filter
    float stack[9] = {0,};
    int idx=0;
    
    for(int y=p;y<image.rows-p;y++){
        for(int x=p;x<image.cols-p;x++){
            idx=0;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    stack[idx] = image.at<uchar>(x+i,y+j);
                    idx++;
                }
            }
            sort(stack, stack+9, std::greater<float>());
            M.at<uchar>(x,y)=saturate_cast<uchar>(stack[4]);
        }
    }
    
    
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display original image", image);
    imshow("Display newImage", M);
    
    waitKey(0);
    return 0;
}
