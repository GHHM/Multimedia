//
//  main.cpp
//  LAB5_5
//
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

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    Point2f inputQuad[4];
    Point2f outputQuad[4];
    
    Mat warp_mat(2,4,CV_32FC1);
    Mat input, output;
    
    input = imread("wanderer.jpg", 1);
    output = Mat::zeros(input.rows, input.cols, input.type());
    
    inputQuad[0] = Point2f( -30,-60 );
    inputQuad[1] = Point2f( input.cols+50,-50);
    inputQuad[2] = Point2f( input.cols+100,input.rows+50);
    inputQuad[3] = Point2f( -50,input.rows+50 );
  
    outputQuad[0] = Point2f( 0,0 );
    outputQuad[1] = Point2f( input.cols-1,0);
    outputQuad[2] = Point2f( input.cols-1,input.rows-1);
    outputQuad[3] = Point2f( 0,input.rows-1 );

    warp_mat = getPerspectiveTransform( inputQuad, outputQuad );
 
    warpPerspective(input, output, warp_mat, output.size() );
    
    imshow("origin", input);
    imshow("result", output);
  
    waitKey(0);
    return 0;
}
