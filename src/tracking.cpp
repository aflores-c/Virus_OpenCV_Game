#include "tracking.h"

Tracking::Tracking(const std::size_t screen_width, const std::size_t screen_height)
{
    //Set windows names
    _window_name_original = "Original_image";
    _window_name_blue = "Blue_image";
    cv::namedWindow(_window_name_original, cv::WINDOW_NORMAL);
    cv::namedWindow(_window_name_blue, cv::WINDOW_NORMAL);
    cv::resizeWindow(_window_name_original, screen_width, screen_height);
    cv::resizeWindow(_window_name_blue, screen_width, screen_height);

    cv::Mat imgOriginal;
    _images.push_back(imgOriginal);         //Original image
    _images.push_back(imgOriginal.clone()); //Image with gaussian blur
    _images.push_back(imgOriginal.clone()); //Temp image to find contours

    //Define blue color limits
    _blueLower = cv::Scalar(100, 67, 0);
    _blueUpper = cv::Scalar(255, 128, 50);
}

//Compare the area of two contours
bool compareContourAreas(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2)
{
    double i = fabs(contourArea(cv::Mat(contour1)));
    double j = fabs(contourArea(cv::Mat(contour2)));
    return (i < j);
}

void Tracking::tracking_color()
{
    //Initiliaze video capture
    cv::VideoCapture capWebCam(0);
    _webCamOpened = capWebCam.isOpened();

    if (_webCamOpened == false)
    {
        std::cout << "Error: webcam connect unsuccesful\n";
    }

    //Capturing video while 'ESC' is not pressed
    while (_charCheckForEscKey != 27 && _webCamOpened)
    {
        bool blnFrameReadSuccessfully = capWebCam.read(_images.at(0)); //Get the next fram
        if (!blnFrameReadSuccessfully || _images.at(0).empty())        // If frame read unsuccessfully
        {
            std::cout << "error: frame can't read \n"; // Print error message
            break;                                     // Jump out of loop
        }

        //Thresholding of the image and filter the image
        cv::inRange(_images.at(0), _blueLower, _blueUpper, _images.at(1));
        cv::GaussianBlur(_images.at(1), _images.at(1), cv::Size(3, 3), 0);

        //Find contours
        _images.at(1).copyTo(_images.at(2)); //A copy of the image in order to not lose the original image
        cv::findContours(_images.at(2), _contours, _hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        //Check if there are blue colors
        if (_contours.size() > 0)
        {
            // Sort contours vector by area
            std::sort(_contours.begin(), _contours.end(), compareContourAreas);

            // Just draw the biggest contour in the original image
            cv::drawContours(_images.at(0), _contours, int(_contours.size() - 1), cv::Scalar(0, 255, 0), 2, cv::LINE_8, _hierarchy);
            cv::Moments m = cv::moments(_contours.at(int(_contours.size() - 1)));
            _x_pos = m.m10 / m.m00;
            _y_pos = m.m01 / m.m00;
            cv::Point p(_x_pos, _y_pos);
            cv::circle(_images.at(0), p, 5, cv::Scalar(128, 0, 0), -1);
            //std::cout << _x_pos << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        //Show the original
        cv::imshow(_window_name_original, _images.at(0));
        cv::imshow(_window_name_blue, _images.at(1));

        _charCheckForEscKey = cv::waitKey(1); // delay and get key press
    }
}

int Tracking::getX_position()
{
    return int(_x_pos);
}
