#pragma once
#include <string>
#include <list>
#include "player.hpp"

// o echipa
class Team
{
private:
    // numele echipei
    std::string teamName;
    // lista jucatorilor
    std::list<Player*> players;
    // punctele echipei
    float points = 0;

public:
    // constructor cu numele echipei
    Team(std::string teamName) : teamName(teamName)
    {
    }

    // destructor care distruge jucatorii
    ~Team()
    {
        for(auto&& player : players)
        {
            delete player;
        }
    }

    // returneaza lista de jucatori
    std::list<Player*> &getPlayers()
    {
        return players;
    }

    // returneaza numele echipei
    std::string getTeamName()
    {
        return teamName;
    }

    // returneaza punctele echipei
    float getPoints()
    {
        return points;
    }

    // seteaza points la media punctelor jucatorilor
    void computePoints()
    {
        points = 0;
        // punem in points suma
        for (Player *player: players) {
            points += player->getPoints();
        }
        // impartim la numarul jucatorilor pentru a face media
        points /= players.size();
    }

    // adauga puncte la echipa
    void addPoints(float increment)
    {
        points += increment;
    }

    // verifica daca echipa care apeleaza are scor mai mic sau egal ca al echipei data ca parametru
    bool compare(Team* other)
    {
        return points <= other->getPoints();
    }

};
