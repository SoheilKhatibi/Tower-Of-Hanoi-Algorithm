#include "tower.h"
#include <iostream>
Tower::Tower(int N)
{
    Population = 0;
    Number = N;
}

void Tower::AddRing()
{
    Population++;
}

int Tower::GetPopulation()
{
    return Population;
}

int Tower::GetNumber()
{
    return Number;
}

void Tower::MinusRing()
{
    Population--;
}
