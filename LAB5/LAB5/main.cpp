// OpenCV.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    
    Mat fImage = imread("foreground.jpg", IMREAD_COLOR);
    Mat bImage = imread("background.jpg", IMREAD_COLOR);
    Mat new_fImage = Mat::zeros(fImage.size(), fImage.type());
    Mat new_bImage = Mat::zeros(bImage.size(), bImage.type());
    
    cvtColor(fImage, new_fImage, CV_BGR2YCrCb);
    cvtColor(bImage, bImage, CV_BGR2YCrCb);
    
    cv::Scalar chromaYCrCb = cv::Scalar(new_fImage.at<Vec3b>(0, 0)[0], new_fImage.at<Vec3b>(0, 0)[1], new_fImage.at<Vec3b>(0, 0)[2], 0); // Convert a single BGR value to YCrCb.
    const cv::Vec3d key(chromaYCrCb[0], chromaYCrCb[1], chromaYCrCb[2]);
    
    float tinner=100, touter=120;
    double alpha = 0.0;
    
    float green[3] = {19,255,59}; // background green color: 19, 255, 59
    double Cb_key = 128 + -0.168736*green[0] - 0.331264*green[1] + 0.5*green[2];
    double Cr_key = 128 + 0.5*19 - 0.418688*255 - 0.081312*59;

    for (int y = 0; y <new_fImage.rows; y++) {
        for (int x = 0; x < new_fImage.cols; x++) {
            
            double Cb_p = new_fImage.at<Vec3b>(y, x)[2];
            double Cr_p = new_fImage.at<Vec3b>(y, x)[1];
            double distance = sqrt(pow((Cb_key-Cb_p), 2) + pow((Cr_key-Cr_p), 2));
            
            if (distance < tinner) {
                alpha = 0;
            }
            else if (distance > touter) {
                alpha = 1;
            }
            else {
                alpha = (distance - tinner) / (touter - tinner);
            }

            new_bImage.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(new_fImage.at<Vec3b>(y, x)[0] * alpha + (1 - alpha)*bImage.at<Vec3b>(y, x)[0]);
            new_bImage.at<Vec3b>(y, x)[1] = saturate_cast<uchar>(new_fImage.at<Vec3b>(y, x)[1] * alpha + (1 - alpha)*bImage.at<Vec3b>(y, x)[1]);
            new_bImage.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(new_fImage.at<Vec3b>(y, x)[2] * alpha + (1 - alpha)*bImage.at<Vec3b>(y, x)[2]);
        }
    }
    
    cvtColor(new_bImage, new_bImage, CV_YCrCb2BGR);
    
    imshow("result", new_bImage);
    imwrite("output.png", new_bImage);
    
    waitKey(0);
    return 0;
}
