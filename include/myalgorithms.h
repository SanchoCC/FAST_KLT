#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

void ImageScalableResize(int DesiredWidth, int DesiredHeight, cv::Mat ImageInput, cv::Mat& ImageOutput);

void FAST_Implementaion(cv::Mat Image, std::vector<cv::KeyPoint>& keypoints, int Density);