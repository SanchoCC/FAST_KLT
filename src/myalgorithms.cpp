#include "myalgorithms.h"
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

void ImageScalableResize(int DesiredWidth, int DesiredHeight, cv::Mat ImageInput, cv::Mat& ImageOutput)
{
    int currentWidth = ImageInput.cols;
    int currentHeight = ImageInput.rows;
    int newWidth, newHeight;
    if (currentWidth > currentHeight) {
        newWidth = DesiredWidth;
        newHeight = static_cast<int>(DesiredWidth * static_cast<float>(currentHeight) / currentWidth);
    }
    else {
        newHeight = DesiredHeight;
        newWidth = static_cast<int>(DesiredHeight * static_cast<float>(currentWidth) / currentHeight);
    }
    cv::resize(ImageInput, ImageOutput, cv::Size(newWidth, newHeight));
}

void FAST_Implementaion(cv::Mat Image, std::vector<cv::KeyPoint>& keypoints, int Density)
{
    std::array<uint8_t, 16> PixelCircle;

    for (int rows = 3; rows < Image.rows - 3; ++rows)
    {
        for (int cols = 3; cols < Image.cols - 3; ++cols)
        {
            uint8_t LowerIntensity = 0;
            uint8_t HigherIntensity = 0;

            uint8_t PixelIntensity = Image.at<uint8_t>(rows, cols);
            int16_t PixelIntensityLowerBound = PixelIntensity - Density;
            int16_t PixelIntensityUpperBound = PixelIntensity + Density;

            PixelCircle[0] = Image.at<uint8_t>(rows - 3, cols);
            PixelCircle[4] = Image.at<uint8_t>(rows, cols + 3);
            PixelCircle[8] = Image.at<uint8_t>(rows + 3, cols);
            PixelCircle[12] = Image.at<uint8_t>(rows, cols - 3);
            
            // Ñhecking the side top and bottom pixels
            if (PixelCircle[0] < PixelIntensityLowerBound)
            {
                ++LowerIntensity;
            }
            else if (PixelCircle[0] > PixelIntensityUpperBound)
            {
                ++HigherIntensity;
            }
            if (PixelCircle[8] < PixelIntensityLowerBound)
            {
                ++LowerIntensity;
            }
            else if (PixelCircle[8] > PixelIntensityUpperBound)
            {
                ++HigherIntensity;
            }

            // If both pixels are similar to the central one, continue searching
            if (LowerIntensity == 0 && HigherIntensity == 0)
            {
                continue;
            }

            // Else cheking two another pixels
            else
            {
                if (PixelCircle[4] < PixelIntensityLowerBound)
                {
                    ++LowerIntensity;
                }
                else if (PixelCircle[4] > PixelIntensityUpperBound)
                {
                    ++HigherIntensity;
                }
                if (PixelCircle[12] < PixelIntensityLowerBound)
                {
                    ++LowerIntensity;
                }
                else if (PixelCircle[12] > PixelIntensityUpperBound)
                {
                    ++HigherIntensity;
                }
            }

            // If at least 3 pixels are suitable, continue checking 
            if (HigherIntensity >= 3 || LowerIntensity >= 3)
            {
                LowerIntensity = 0;
                HigherIntensity = 0;

                // Make an array of consecutive pixels

                PixelCircle[1] = Image.at<uint8_t>(rows - 3, cols + 1);
                PixelCircle[2] = Image.at<uint8_t>(rows - 2, cols + 2);
                PixelCircle[3] = Image.at<uint8_t>(rows - 1, cols + 3);

                PixelCircle[5] = Image.at<uint8_t>(rows + 1, cols + 3);
                PixelCircle[6] = Image.at<uint8_t>(rows + 2, cols + 2);
                PixelCircle[7] = Image.at<uint8_t>(rows + 3, cols + 1);

                PixelCircle[9] = Image.at<uint8_t>(rows - 3, cols - 1);
                PixelCircle[10] = Image.at<uint8_t>(rows + 2, cols - 2);
                PixelCircle[11] = Image.at<uint8_t>(rows + 1, cols - 3);

                PixelCircle[13] = Image.at<uint8_t>(rows - 1, cols - 3);
                PixelCircle[14] = Image.at<uint8_t>(rows - 2, cols - 2);
                PixelCircle[15] = Image.at<uint8_t>(rows + 3, cols - 1);


                // Checking if at least 12 pixels are going in a row
                for (int i = 0; i < PixelCircle.size(); ++i)
                {
                    if (PixelCircle[i] < PixelIntensityLowerBound)
                    {
                        ++LowerIntensity;
                        if (i > 4 && HigherIntensity > 0)
                        {
                            break;
                        }
                        HigherIntensity = 0;
                    }
                    else if (PixelCircle[i] > PixelIntensityUpperBound)
                    {
                        ++HigherIntensity;
                        if (i > 4 && LowerIntensity > 0)
                        {
                            break;
                        }
                        LowerIntensity = 0;
                    }
                    if (i > 3 && HigherIntensity == 0 && LowerIntensity == 0)
                    {
                        break;
                    }
                    if (i >= 12 && HigherIntensity >= 12 || LowerIntensity >= 12)
                    {
                        keypoints.emplace_back(cols, rows, 0);
                        break;
                    }
                }
            }
        }
    }
}