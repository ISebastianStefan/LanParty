#pragma once
#include "team.hpp"

// un meci dintre 2 echipe
class Match
{
private:
    // pointeri la echipe
    Team *firstTeam;
    Team *secondTeam;

public:
    // constructor cu parametrii referinte la echipe
    Match(Team *firstTeam, Team *secondTeam) : firstTeam(firstTeam), secondTeam(secondTeam)
    {
    }

    // returneaza prima echipa (nu conteaza scorul ei)
    Team *getFirstTeam()
    {
        return firstTeam;
    }

    // returneaza a doua echipa (nu conteaza scorul ei)
    Team *getSecondTeam()
    {
        return secondTeam;
    }

    // compara experienta si returneaza echipa care castiga meciul
    Team *getWinner()
    {
        if (firstTeam->compare(secondTeam))
            return secondTeam;
        return firstTeam;
    }

    // compara experienta si returneaza echipa care pierde meciul
    Team *getLoser()
    {
        if (firstTeam->compare(secondTeam))
            return firstTeam;
        return secondTeam;
    }
};
