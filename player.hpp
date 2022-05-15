#pragma once
#include <string>

// un jucator
class Player
{
private:
    // prenumele
    std::string firstName;
    // numele
    std::string secondName;
    // punctele de experienta
    int points;

public:
    // constructor cu prenume, nume si puncte
    Player(std::string firstName, std::string secondName, int points) : firstName(firstName), secondName(secondName), points(points)
    {
    }

    // returneaza punctele jucatorului
    int getPoints()
    {
        return points;
    }
};
