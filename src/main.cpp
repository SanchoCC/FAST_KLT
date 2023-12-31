#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <array>
#include <myalgorithms.h>

const int kDensity = 30;

int main(int argc, char** argv) {

    //Image file  

    char* ImageFile = argv[1];

    //OR
 
    //char* ImageFile = "YOUR_IMAGE_PATH";
    
    if (kDensity < std::numeric_limits<int16_t>::min() || kDensity > std::numeric_limits<int16_t>::max()-std::numeric_limits<uint8_t>::max()) 
    {
    std::cerr << "kDensity is outside the range" << std::endl;
    }
    // Mat objects for storing data 
    cv::Mat ImageColor, ImageGrayscale, ImageResult, ImageResultResized;	              
    ImageColor = imread(ImageFile, cv::IMREAD_COLOR);
    ImageGrayscale = imread(ImageFile, cv::IMREAD_GRAYSCALE);
    if (ImageColor.empty() || ImageGrayscale.empty())
    {
        std::cerr << "Could not open or find the image: " << ImageFile << std::endl;
        return -1;
    }
    //Creating vector of Keypoints
    std::vector<cv::KeyPoint> Keypoints;

    // Measuring execution time
    auto StartTime = std::chrono::high_resolution_clock::now();
    // Calling FAST
    FAST_Implementaion(ImageGrayscale, Keypoints, kDensity);

    // Measuring execution time
    auto EndTime = std::chrono::high_resolution_clock::now();
    auto Duration = std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);

    cv::drawKeypoints(ImageColor, Keypoints, ImageResult, cv::Scalar(255, 0, 0));

    // Resizing the image
    ImageScalableResize(800, 600, ImageResult, ImageResultResized);

    cv::imshow("FAST Keypoints", ImageResultResized);

    // Writing image to build directory
    cv::imwrite("ResultImage.jpg", ImageResult);

    // Displaying the number of points and the time they were found
    std::cout << "Number of keypoints: " << Keypoints.size() << ", Detection time: " << Duration.count() << " microseconds" << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}