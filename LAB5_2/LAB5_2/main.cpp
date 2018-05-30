//
//  main.c
//  LAB5_2
//  Bilinear interpolation
//  Created by Hyemi Kim on 2018. 5. 24..
//  Copyright © 2018년 Hyemi Kim. All rights reserved.
//
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

void setImageValue(Vec3b Area, Mat image, int px, int py){
    Area = image.at<Vec3b>(py,px);
}

int main(int argc, const char * argv[]) {
    std::cout << "Write input image name and output image name x and y scaling factor" << std::endl;
    std::cout << "Example: input.jpg output.jpg 1.5 1.5\n" << std::endl;
    
    string inputFileName("wanderer.jpg");
    string outputFileName("output.jpg");
    double Xscale=2.0;
    double Yscale=1.5;
    
    std::cin >> inputFileName;
    std::cin >> outputFileName;
    std::cin >> Xscale;
    std::cin >> Yscale;

    //get image
    Mat image = imread(inputFileName, IMREAD_COLOR);
    Mat newImage = Mat::zeros((int)(image.rows * Yscale), (int)(image.cols * Xscale), image.type());
  
    Vec3b E11, E12, E21, E22;
    
    for (int y = 0; y < newImage.rows; y++) {
        for (int x = 0; x < newImage.cols; x++) {
            //pixel
            int px = (int)(x / Xscale);
            int py = (int)(y / Yscale);
            
            double gx1 = (double)x / (double)Xscale - (double)px;
            double gx2 = 1 - gx1;
            double gy1 = (double)y / (double)Yscale - (double)py;
            double gy2 = 1 - gy1;
            
            //weight
            double weight1 = gx2 * gy2;
            double weight2 = gx1 * gy2;
            double weight3 = gx2 * gy1;
            double weight4 = gx1 * gy1;
            
            if (px == image.cols - 1 && py == image.rows - 1) {
                E11 = image.at<Vec3b>(py, px);
                E12 = image.at<Vec3b>(py, px);
                E21 = image.at<Vec3b>(py, px);
                E22 = image.at<Vec3b>(py, px);
            }
            else if (px == image.cols - 1 || py == image.rows - 1) {
                if (px == image.cols - 1) {
                    E11 = image.at<Vec3b>(py, px);
                    E12 = image.at<Vec3b>(py, px);
                    E21 = image.at<Vec3b>(py + 1, px);
                    E22 = image.at<Vec3b>(py + 1, px);
                }
                else {
                    E11 = image.at<Vec3b>(py, px);
                    E12 = image.at<Vec3b>(py, px + 1);
                    E21 = image.at<Vec3b>(py, px);
                    E22 = image.at<Vec3b>(py, px + 1);
                }
            }
            else {
                E11 = image.at<Vec3b>(py, px);
                E12 = image.at<Vec3b>(py, px + 1);
                E21 = image.at<Vec3b>(py + 1, px);
                E22 = image.at<Vec3b>(py + 1, px + 1);
            }
            //interpolation
            newImage.at<Vec3b>(y, x) = weight1 * E11 + weight2 * E12 + weight3 * E21 + weight4 * E22;
        }
    }

    imshow("origin", image);
    imshow("result", newImage);
    imwrite(outputFileName, newImage);
    waitKey(0);
    return 0;
}

