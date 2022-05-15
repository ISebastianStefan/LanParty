#include <iostream>
#include "lanParty.hpp"

using namespace std;

// lista de echipe
list<Team *> teams;
// stive cu echipe castigatoare, pierzatoare, respectiv cu top 8 cele mai bune echipe
list<Team *> winnerStack, loserStack, topEight;
// coada de meciuri
list<Match *> matches;

// fisier de output declarat global
ofstream outputFile;

bool isPowerOf2(int number)
{
    // daca s-a gasit un bit de 1
    bool foundBit = false;
    while (number > 0)
    {
        // verific daca number are ultimul bit 1
        if (number & 1)
            // daca am gasit pentru prima oara setez foundBit la true
            if (!foundBit)
                foundBit = true;
            // daca am gasit mai mult de un bit 1 atunci nu este putere a lui 2
            else
                return false;
        // shiftez la dreapta (impart la 2)
        number >>= 1;
    }
    // returnez foundBit care va fi true pentru un singur bit si false pentru niciun bit
    return foundBit;
}

void printTeams(std::list<Team*> list)
{
    // scriu echipele pe linii diferite in fisier
    for (Team *team : teams)
        outputFile << team->getTeamName() << endl;
}

void printMatchedTeams(Match *match)
{
    // iau numele echipelor
    string firstName = match->getFirstTeam()->getTeamName();
    string secondName = match->getSecondTeam()->getTeamName();
    // calculez cate space-uri trebuie sa pun
    int spaces1 = 33 - firstName.size(), spaces2 = 33 - secondName.size();;
    // initializez linia cu numele primei echipe
    string line = firstName;
    // adaug numarul calculat de spatii dintre primul nume si '-'
    for (int i = 0; i < spaces1; ++i)
        line += " ";
    // adaug '-'
    line += "-";
    // adaug numarul calculat de spatii dintre '-' si second nume
    for (int i = 0; i < spaces2; ++i)
        line += " ";
    // adaug numele celei de a doua echipe
    line += secondName;
    // printez linia in fisier
    outputFile << line << endl;
}

void printTeamScore(Team *team)
{
    // iau numele echipei
    string name = team->getTeamName();
    // calculez cate space-uri trebuie sa pun
    int spaces = 34 - name.size();
    // initializez linia cu numele echipei
    string line = name;
    for (int i = 0; i < spaces; ++i)
        line += " ";
    // adaug numarul calculat de spatii dintre nume si '-'
    line += "- ";
    // printez linia in fisier, cu precizie fixa de 2 zecimale la scor
    outputFile << line << " " << fixed << setprecision(2) << team->getPoints() << endl;
}

template <class T>
void freeStackContents(std::list<T*> &stack)
{
    // scot referinte din stiva si le eliberez
    while (!stack.empty())
    {
        delete stack.front();
        stack.pop_front();
    }
}

void startTask(int index, char *inputPath)
{
    // doar taskurile 1-3 sunt tratate, celelalte nu fac nimic
    switch (index)
    {
    case 1:
        task1(inputPath);
        break;
    case 2:
        task2();
        break;
    case 3:
        task3();
        break;
    default:
        break;
    }
}

void task1(char *inputPath)
{
    // deschid fisierul din care citesc echipele
    ifstream inputFile(inputPath, ios::in);

    // numarul total de echipe pe care il citesc
    int teamCounter;
    inputFile >> teamCounter;

    // numarul de jucatori pe care trebuie sa ii mai citesc din echipa curenta
    int playerCounter = 0;

    // referinta la echipa curenta
    Team *latestTeam;

    // cat timp mai am echipe sau jucatori de citit
    while (teamCounter > 0 || playerCounter > 0)
    {
        // daca am ajuns la sfarsitul fisierului, ies din while
        if (inputFile.eof())
        {
            break;
        }

        // citesc o linie si o salvez in line
        string line;
        getline(inputFile, line);

        //daca linia e goala, o ignor
        if (line.empty())
        {
            continue;
        }

        // folosesc splitter pentru a parsa linia
        stringstream splitter(line);

        // daca playerCounter e mai mai mare ca 0, vom citi un jucator
        if (playerCounter > 0)
        {
            --playerCounter;

            string firstName, secondName;
            int points;

            // pun in secondName numele de familie
            splitter >> secondName;
            // pun in firstName prenumele
            splitter >> firstName;
            // pun in points punctele jucatorului
            splitter >> points;
            // pun jucatorul in lista de jucatori a ultimei echipe
            latestTeam->getPlayers().push_front(new Player(firstName, secondName, points));
        }
        // daca playerCounter e 0 inseamna ca vom citi o echipa
        else
        {
            --teamCounter;
            string teamName, word;

            // pun in playerCounter numarul de jucatori pentru a stii cati jucatori voi citi in continuare
            splitter >> playerCounter;

            // concatenez restul cuvintelor pentru a crea numele echipei
            while (splitter >> word)
            {
                // pun un space in fata fiecarui cuvant din nume, in afara de primul cuvant
                if (!teamName.empty())
                    teamName = teamName.append(" ");
                // adaug cuvantul la nume
                teamName = teamName.append(word);
            }
            // construiesc o noua echipa, o memorez in latestTeam si o pun in lista de echipe
            latestTeam = new Team(teamName);
            teams.push_front(latestTeam);
        }
    }

    // calculez punctajele de baza ale echipelor
    for (Team *team : teams)
        team->computePoints();

    // inchid fisierul de input
    inputFile.close();
}

void task2()
{
    // cat timp numarul echipelor nu e putere a lui 2
    while (!isPowerOf2(teams.size()))
    {
        // -1 reprezinta faptul ca minimul nu a fost setat
        float minimumPoints = -1;
        Team *removedTeam;
        // calculam punctaj
        for (auto it = teams.begin(); it != teams.end(); ++it)
        {
            Team *team = *it;
            // daca minimul este -1 (nesetat) sau mai mare ca punctajul
            if (minimumPoints == -1 || minimumPoints > team->getPoints())
            {
                // setam minimul nou
                minimumPoints = team->getPoints();
                // memoram referinta la echipa
                removedTeam = team;
            }
        }
        // stergem echipa din lista
        teams.remove(removedTeam);
        // eliberam echipa din memorie
        delete removedTeam;
    }
}

void task3()
{
    int roundCounter = 0;
    do
    {
        // cresc runda (va incepe cu 1)
        ++roundCounter;

        // iau 2 cate 2 echipe si creez meciuri
        while (!teams.empty())
        {
            Team *firstTeam = teams.front();
            teams.pop_front();
            Team *secondTeam = teams.front();
            teams.pop_front();
            matches.push_back(new Match(firstTeam, secondTeam));
        }

        // printez meciurile si pun castigatorii/pierzatorii in stivele respective
        outputFile << endl << "--- ROUND NO:" << roundCounter << endl;
        while (!matches.empty())
        {
            Match *match = matches.front();
            matches.pop_front();
            printMatchedTeams(match);
            Team *winner = match->getWinner();
            winner->addPoints(1);
            winnerStack.push_front(winner);
            loserStack.push_front(match->getLoser());
            delete match;
        }

        // printez castigatorii si ii pun inapoi in lista teams
        outputFile << endl << "WINNERS OF ROUND NO:" << roundCounter << endl;
        while (!winnerStack.empty())
        {
            Team *winner = winnerStack.front();
            printTeamScore(winner);
            teams.push_back(winner);
            winnerStack.pop_front();
        }

        // daca am exact 8 echipe, pun referintele lor si in topEight
        if (teams.size() == 8)
        {
            for (Team *team : teams)
                topEight.push_front(team);
        }
        // distrug echipele pierzatoare
        if (teams.size() >= 8)
        {
           freeStackContents(loserStack);
        }
        // nu distrug echipele care sunt in topEight, doar golesc stiva
        else
            loserStack.clear();

    // daca mai e doar o echipa in lista se iese din do while
    } while (teams.size() > 1);

    // distrug echipele din topEight
    freeStackContents(topEight);

    /* golesc stiva teams pentru a evita distrugerea echipei ramase, deoarece
    deja am distrus-o din topEight
    */
    teams.clear();
}

int main(int argc, char *argv[])
{
    // coada de valori booleane citite din fisier
    list<bool> tasks;
    // variabila auxiliara pentru citire
    bool taskOn;

    // deschid fisiere de citire si scriere
    ifstream inputFile(argv[1], ios::in);

    // citesc coada din input
    while (inputFile >> taskOn)
        tasks.push_back(taskOn);

    // inchid fisierul de input
    inputFile.close();

    // deschid fisierul de output
    outputFile = ofstream(argv[3], ios::out);

    // rulez cele 5 taskuri
    for (int i = 0; i < 5; ++i)
    {
        // inainte de task 3 printez echipele in fisier
        if (i == 2)
            printTeams(teams);
        // scot valorile citite din coada si rulam taskul i daca valoarea scoasa nu e 0
        if (tasks.front())
            startTask(i + 1, argv[2]);
        tasks.pop_front();
    }

    // eliberez lista de echipe
    freeStackContents(teams);

    // inchid fisierul de output
    outputFile.close();

    return 0;
}
