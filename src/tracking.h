#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

enum Directions{left, right, stay};

class Tracking
{
public:
    Tracking(const std::size_t screen_width, const std::size_t screen_height);
    void tracking_color();
    int getX_position();

private:
    void load_video_capture();

    char _charCheckForEscKey{0};
    bool _webCamOpened{0};
    std::string _window_name_original;
    std::string _window_name_blue;

    //Image processing variables
    cv::Scalar _blueLower;
    cv::Scalar _blueUpper;
    std::vector<cv::Vec4i> _hierarchy;
    std::vector<std::vector<cv::Point>> _contours;
    std::vector<cv::Mat> _images;
    Directions _current_direction;
    double _x_pos;
    double _y_pos;
};