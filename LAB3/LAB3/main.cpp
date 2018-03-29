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

#define SCALE 0.2

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    string imageName ("./lena.jpg");
    if(argc>1){
        imageName = argv[1];
    }
    
    Mat inputImg;
    Mat greyImg;
    Mat equalizeImg;
    
    inputImg = imread(imageName.c_str(), IMREAD_COLOR);
    resize(inputImg, inputImg, cvSize(256, 256), 0, 0, CV_INTER_LINEAR);
    // grayscale
    cvtColor(inputImg, greyImg, CV_BGR2GRAY);
    //equalize image
    equalizeHist(greyImg,equalizeImg);
    
    MatND histogram, histogram2;
    const int* channel_numbers = { 0 };
    float channel_range[] = { 0.0, 255.0 };
    const float* channel_ranges = channel_range;
    int number_bins = 255;
    
    // Plot the histogram
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double)hist_w / number_bins);
   
    // calculate (make) histogram
    calcHist(&greyImg, 1, channel_numbers, Mat(), histogram, 1, &number_bins, &channel_ranges);
    calcHist(&equalizeImg, 1, channel_numbers, Mat(), histogram2, 1, &number_bins, &channel_ranges);
    
    // nomarlize histogram
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
    Mat histEqualImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
    normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(histogram2, histogram2, 0, histEqualImage.rows, NORM_MINMAX, -1, Mat());
    
    //draw histogram
    for (int i = 1; i < number_bins; i++)
    {
        line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
             Point(bin_w*(i), hist_h - cvRound(histogram.at<float>(i))),
             Scalar(255, 0, 0), 2, 8, 0);
    }
    for (int i = 1; i < number_bins; i++)
    {
        line(histEqualImage, Point(bin_w*(i - 1), hist_h - cvRound(histogram2.at<float>(i - 1))),
             Point(bin_w*(i), hist_h - cvRound(histogram2.at<float>(i))),
             Scalar(255, 0, 0), 2, 8, 0);
    }
    
    //display
    namedWindow("Greyscale image", CV_WINDOW_AUTOSIZE);
    namedWindow("Equalized image", CV_WINDOW_AUTOSIZE);
    namedWindow("Greyscale histogram", CV_WINDOW_AUTOSIZE);
    namedWindow("Equalized histogram", CV_WINDOW_AUTOSIZE);
    
    moveWindow("Greyscale image", 100, 100);
    moveWindow("Equalized image", 120, 120);
    moveWindow("Greyscale histogram", 140, 140);
    moveWindow("Equalized histogram", 160, 160);
    
    imshow("Greyscale image", greyImg);
    imshow("Equalized image",equalizeImg);
    imshow("Greyscale histogram", histImage);
    imshow("Equalized histogram", histEqualImage);
    
    waitKey(0);
    return 0;
    
}

