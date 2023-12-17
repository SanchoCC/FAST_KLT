#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <chrono>
#include <array>

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
            int LowerIntensity = 0;
            int HigherIntensity = 0;

            uint8_t PixelIntensity = Image.at<uint8_t>(rows, cols);
            int16_t PixelIntensityLowerBound = PixelIntensity - Density;
            int16_t PixelIntensityUpperBound = PixelIntensity + Density;
         
            PixelCircle[0] = Image.at<uint8_t>(rows - 3, cols);
            PixelCircle[4] = Image.at<uint8_t>(rows, cols + 3);
            PixelCircle[8] = Image.at<uint8_t>(rows + 3, cols);
            PixelCircle[12] = Image.at<uint8_t>(rows, cols - 3);          
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
            if (LowerIntensity < 2 && HigherIntensity < 2)
            {
                continue;
            }
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
            if (HigherIntensity >= 3 || LowerIntensity >= 3)
            {   
                LowerIntensity = 0;
                HigherIntensity = 0;

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
                
                for (int i = 0; i < PixelCircle.size(); ++i)
                {
                    uint8_t IntensityValue = PixelCircle[i];
                    if (IntensityValue < PixelIntensityLowerBound)
                    {
                        ++LowerIntensity;
                        if(HigherIntensity > 0 && i > 3)
                        {                            
                            break;                                                       
                        }
                        HigherIntensity = 0;
                    }
                    else if (IntensityValue > PixelIntensityUpperBound)
                    {
                        ++HigherIntensity;
                        if (LowerIntensity > 0 && i > 3)
                        {
                            break;                               
                        }
                        LowerIntensity = 0;
                    }
                    if (i>3&&HigherIntensity == 0&&LowerIntensity == 0)
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

int main(int argc, char** argv) {

    //image file 
    //char* ImageFile = argv[1];

    const int kDensity = 20;

    char* ImageFile = "signal-2023-12-14-212155_002.jpeg";
    //mat objects for storing data 
    cv::Mat ImageColor, ImageGrayscale, ImageResult, ImageResultResized;	              
    ImageColor = imread(ImageFile, cv::IMREAD_COLOR);
    ImageGrayscale = imread(ImageFile, cv::IMREAD_GRAYSCALE);

    std::vector<cv::KeyPoint> Keypoints;
    // Measuring execution time
    auto StartTime = std::chrono::high_resolution_clock::now();
    // Calling FAST
    FAST_Implementaion(ImageGrayscale, Keypoints, kDensity);
    // Measuring execution time
    auto EndTime = std::chrono::high_resolution_clock::now();
    auto Duration = std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);

    cv::drawKeypoints(ImageColor, Keypoints, ImageResult, cv::Scalar(255, 0, 0));

    ImageScalableResize(800, 600, ImageResult, ImageResultResized);
    cv::imshow("FAST Keypoints", ImageResultResized);
    cv::imwrite("ResultImage.jpg", ImageResult);
    // Displaying the number of points and the time they were found
    std::cout << "Number of keypoints: " << Keypoints.size() << ", Detection time: " << Duration.count() << " microseconds" << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}