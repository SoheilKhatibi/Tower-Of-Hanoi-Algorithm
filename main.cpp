#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

#include "ring.h"
#include "tower.h"

// void Init(std::vector<Tower> Towers, std::vector<Ring> Rings);
void Init(int a);
void PutTheRingThere(int ringnumber, int towernumber);
void MoveTheRing(int ringnumber, int towernumber);
void hanoi(int first, int last, int i, int j);
void PartiallyMove(int ringnumber);

const int RingsNumber = 8;
float TimeStep = 1.0;
Ring *Rings[RingsNumber];
Tower *Towers[3];

cv::Mat A, B, C;

int main()
{
    A = cv::Mat(700, 1300, CV_8UC3, cv::Scalar(0, 0, 0));
    //    cv::circle(A, cv::Point(), 5, cv::Scalar(0,0,255), -1, 4, 0);

    //    std::vector<Tower> *Towers;
    //    std::vector<Ring> *Rings;

    cv::Scalar Colors[] = {cv::Scalar(103, 25, 255), cv::Scalar(0, 0, 255), cv::Scalar(0, 69, 255), cv::Scalar(25, 254, 255), cv::Scalar(25, 204, 99), cv::Scalar(0, 153, 0), cv::Scalar(255, 165, 76), cv::Scalar(153, 76, 0)};

    for (int i = 0; i < 3; i++)
    {
        Towers[i] = new Tower(i);
    }

    for (int i = 0; i < RingsNumber; i++)
    {
        Rings[i] = new Ring(i, Colors[i], 48 + (i + 1) * 14);
    }

    cv::line(A, cv::Point(150, 600), cv::Point(350, 600), cv::Scalar(255, 255, 255), 2, 8, 0);
    cv::line(A, cv::Point(550, 600), cv::Point(750, 600), cv::Scalar(255, 255, 255), 2, 8, 0);
    cv::line(A, cv::Point(950, 600), cv::Point(1150, 600), cv::Scalar(255, 255, 255), 2, 8, 0);

    cv::line(A, cv::Point(250, 300), cv::Point(250, 600), cv::Scalar(255, 255, 255), 2, 8, 0);
    cv::line(A, cv::Point(650, 300), cv::Point(650, 600), cv::Scalar(255, 255, 255), 2, 8, 0);
    cv::line(A, cv::Point(1050, 300), cv::Point(1050, 600), cv::Scalar(255, 255, 255), 2, 8, 0);
    Init(0);
    hanoi(0, RingsNumber - 1, 0, 2);
    return 0;
}

// void Init(std::vector<Tower> Towers, std::vector<Ring> Rings){
void Init(int a)
{
    A.copyTo(B);
    for (int i = RingsNumber - 1; i >= 0; i--)
        PutTheRingThere(i, a);
}

void hanoi(int first, int last, int i, int j)
{
    if (last >= 0)
    {
        hanoi(first, last - 1, i, 3 - i - j);
        MoveTheRing(last, j);
        hanoi(first, last - 1, 3 - i - j, j);
    }
}

void PutTheRingThere(int ringnumber, int towernumber)
{
    Rings[ringnumber]->SetPosition(Towers[towernumber]->GetNumber());
    Rings[ringnumber]->SetHeightStep(Towers[towernumber]->GetPopulation());
    Towers[towernumber]->AddRing();
    Rings[ringnumber]->SetA(cv::Point(250 + Towers[towernumber]->GetNumber() * 400 - Rings[ringnumber]->GetWidth() / 2, 600 - (Rings[ringnumber]->GetHeightStep() + 1) * 20));
    Rings[ringnumber]->SetB(cv::Point(250 + Towers[towernumber]->GetNumber() * 400 + Rings[ringnumber]->GetWidth() / 2, 600 - (Rings[ringnumber]->GetHeightStep()) * 20));
    rectangle(B, Rings[ringnumber]->GetA(), Rings[ringnumber]->GetB(), Rings[ringnumber]->GetColor(), cv::FILLED, 8, 0);
}

void MoveTheRing(int ringnumber, int towernumber)
{
    A.copyTo(B);

    Towers[Rings[ringnumber]->GetPosition()]->MinusRing();
    Rings[ringnumber]->SetPosition(Towers[towernumber]->GetNumber());
    Rings[ringnumber]->SetHeightStep(Towers[towernumber]->GetPopulation());
    Towers[towernumber]->AddRing();

    for (int i = RingsNumber - 1; i >= 0; i--)
    {
        if (Rings[i]->GetNumber() != Rings[ringnumber]->GetNumber())
        {
            rectangle(B, Rings[i]->GetA(), Rings[i]->GetB(), Rings[i]->GetColor(), cv::FILLED, 8, 0);
        }
    }
    double DeltaT = 0, V;
    clock_t InitialTime, CurrentTime;
    InitialTime = CurrentTime = clock();
    cv::Point Q, Z;
    Q = Rings[ringnumber]->GetA();
    Z = Rings[ringnumber]->GetB();
    V = (200 - Q.y) / TimeStep;
    while (DeltaT < TimeStep)
    {
        B.copyTo(C);
        CurrentTime = clock();
        DeltaT = (double)(CurrentTime - InitialTime) / CLOCKS_PER_SEC;
        Rings[ringnumber]->SetA(cv::Point(Rings[ringnumber]->GetA().x, V * DeltaT + Q.y));
        Rings[ringnumber]->SetB(cv::Point(Rings[ringnumber]->GetB().x, V * DeltaT + Z.y));
        rectangle(C, Rings[ringnumber]->GetA(), Rings[ringnumber]->GetB(), Rings[ringnumber]->GetColor(), cv::FILLED, 8, 0);
        imshow("salam", C);
        cv::waitKey(1);
    }

    DeltaT = 0;
    InitialTime = CurrentTime = clock();
    Q = Rings[ringnumber]->GetA();
    Z = Rings[ringnumber]->GetB();
    V = (((250 + Towers[towernumber]->GetNumber() * 400) - Rings[ringnumber]->GetWidth() / 2) - Q.x) / TimeStep;
    while (DeltaT < TimeStep)
    {
        B.copyTo(C);
        CurrentTime = clock();
        DeltaT = (double)(CurrentTime - InitialTime) / CLOCKS_PER_SEC;
        Rings[ringnumber]->SetA(cv::Point(V * DeltaT + Q.x, Rings[ringnumber]->GetA().y));
        Rings[ringnumber]->SetB(cv::Point(V * DeltaT + Z.x, Rings[ringnumber]->GetB().y));
        rectangle(C, Rings[ringnumber]->GetA(), Rings[ringnumber]->GetB(), Rings[ringnumber]->GetColor(), cv::FILLED, 8, 0);
        imshow("salam", C);
        cv::waitKey(1);
    }
    DeltaT = 0;
    InitialTime = CurrentTime = clock();
    Q = Rings[ringnumber]->GetA();
    Z = Rings[ringnumber]->GetB();
    V = ((600 - ((Towers[towernumber]->GetPopulation()) * 20)) - Q.y) / TimeStep;
    while (DeltaT < TimeStep)
    {
        B.copyTo(C);
        CurrentTime = clock();
        DeltaT = (double)(CurrentTime - InitialTime) / CLOCKS_PER_SEC;
        Rings[ringnumber]->SetA(cv::Point(Rings[ringnumber]->GetA().x, V * DeltaT + Q.y));
        Rings[ringnumber]->SetB(cv::Point(Rings[ringnumber]->GetB().x, V * DeltaT + Z.y));
        rectangle(C, Rings[ringnumber]->GetA(), Rings[ringnumber]->GetB(), Rings[ringnumber]->GetColor(), cv::FILLED, 8, 0);
        imshow("salam", C);
        cv::waitKey(1);
    }
}

void PartiallyMove(int ringnumber)
{
    double DeltaT = 0, V;
    clock_t InitialTime, CurrentTime;
    InitialTime = CurrentTime = clock();
    cv::Point Q, Z;
    Q = Rings[ringnumber]->GetA();
    Z = Rings[ringnumber]->GetB();
    V = (200 - Q.y) / TimeStep;
    while (DeltaT < TimeStep)
    {
        B.copyTo(C);
        CurrentTime = clock();
        DeltaT = (double)(CurrentTime - InitialTime) / CLOCKS_PER_SEC;
        Rings[ringnumber]->SetA(cv::Point(Rings[ringnumber]->GetA().x, V * DeltaT + Q.y));
        Rings[ringnumber]->SetB(cv::Point(Rings[ringnumber]->GetB().x, V * DeltaT + Z.y));
        rectangle(C, Rings[ringnumber]->GetA(), Rings[ringnumber]->GetB(), Rings[ringnumber]->GetColor(), cv::FILLED, 8, 0);
        imshow("salam", C);
        cv::waitKey(1);
    }
}
