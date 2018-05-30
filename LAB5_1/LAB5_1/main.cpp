//
//  main.cpp
//  LAB5_1
//  Nearest neighbour interpolation
//  Created by Hyemi Kim on 2018. 5. 10..
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

int main(int argc, char** argv)
{
    
    std::cout << "Write input image name and output image name x and y scaling factor" << std::endl;
    std::cout << "Example: input.jpg output.jpg 1.5 1.5\n" << std::endl;
    
    string inputFileName("wanderer.jpg");
    string outputFileName("output.jpg");
    double Xscale;
    double Yscale;
    int scale_d = 2;
    
    std::cin >> inputFileName;
    std::cin >> outputFileName;
    std::cin >> Xscale;
    std::cin >> Yscale;
    
    Mat image = imread(inputFileName, IMREAD_COLOR);
    
    Mat newImage = Mat::zeros(image.rows * Xscale, image.cols * Yscale, image.type());

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            if(Xscale > 1) {
            for(int s = 0; s < Xscale; s++) {
                for(int c = 0; c < 3; c++) {
                    newImage.at<Vec3b>(Yscale * y + s, Xscale * x)[c] = image.at<Vec3b>(y, x)[c];
                    newImage.at<Vec3b>(Yscale * y, Xscale * x + s)[c] = image.at<Vec3b>(y, x)[c];
                    newImage.at<Vec3b>(Yscale * y + s, Xscale * x + s)[c] = image.at<Vec3b>(y, x)[c];
                }
            }
        } else {
            if(y % scale_d == 0 || x % scale_d == 0)
                continue;
            else {
                for(int c = 0; c < 3; c++) {
                    newImage.at<Vec3b>(Xscale * y, Xscale * x)[c] = image.at<Vec3b>(y, x)[c];
                }
            }
        }
        }
    }
    imshow("origin", image);
    imshow("result", newImage);
    imwrite(outputFileName, newImage);
    waitKey(0);
    return 0;
    
    
}
