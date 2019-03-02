//
// Created by meynadier on 20/02/19.
//

#ifndef TP2_PRECESS_H
#define TP2_PRECESS_H

#include <core/mat.hpp>
#include <opencv.hpp>
#include <imgproc.hpp>
#include <iostream>

class Filter{

public:
    Filter(const std::string url);
    virtual ~Filter();
    Filter operator =(const Filter &rhs) const;
    void test();

private:
    cv::Mat sourceImg;
    cv::Mat openImg(std::string url);
    cv::Mat greyscale8U();
    cv::Mat greyscale8UC3();
    cv::Mat blurFilter();
    cv::Mat filtreMedian();
    cv::Mat filtreSobel();
    int blur(const int &rows, const int &cols);
    int median(int rows, int cols);


};



#endif //TP2_PRECESS_H
