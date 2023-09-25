#ifndef TOWER_H
#define TOWER_H

class Tower
{
public:
    Tower(int N);
    void AddRing();
    int GetPopulation();
    int GetNumber();
    void MinusRing();

private:
    int Population, Number;
};

#endif // TOWER_H
