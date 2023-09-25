#ifndef RING_H
#define RING_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class Ring
{
public:
    Ring(int N, cv::Scalar C, int W);
    void SetPosition(int P);
    void SetHeightStep(int H);
    int GetHeightStep();
    int GetWidth();
    int GetNumber();
    int GetPosition();
    cv::Scalar GetColor();
    void SetA(cv::Point x);
    void SetB(cv::Point x);
    cv::Point GetA();
    cv::Point GetB();

private:
    int Position, Width, HeightStep, Number;
    cv::Scalar Color;
    cv::Point A, B;
};

#endif // RING_H
