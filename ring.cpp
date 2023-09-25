#include "ring.h"

Ring::Ring(int N, cv::Scalar C, int W)
{
    Number = N;
    Color = C;
    Width = W;
}

void Ring::SetPosition(int P)
{
    Position = P;
}

void Ring::SetHeightStep(int H)
{
    HeightStep = H;
}

int Ring::GetHeightStep()
{
    return HeightStep;
}

int Ring::GetWidth()
{
    return Width;
}

int Ring::GetNumber()
{
    return Number;
}

int Ring::GetPosition()
{
    return Position;
}

cv::Scalar Ring::GetColor()
{
    return Color;
}

void Ring::SetA(cv::Point x)
{
    A = x;
}

void Ring::SetB(cv::Point x)
{
    B = x;
}

cv::Point Ring::GetA()
{
    return A;
}

cv::Point Ring::GetB()
{
    return B;
}
