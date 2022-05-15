#pragma once
// liste, stive, cozi
#include <list>
// input/output cu fisier
#include <fstream>
// citire input dintr-un string (folosit la citirea pe linii in task1)
#include <sstream>
// printare cu anumita precizie
#include <iomanip>

// clasele pentru tema
#include "player.hpp"
#include "team.hpp"
#include "match.hpp"

// ruleaza taskul 1, citind date din fisierul dat ca parametru
void task1(char *inputPath);
// ruleaza taskul 2
void task2();
// ruleaza taskul 3
void task3();

// incepe un taskul dat prin index. inputPath este necesar doar pentru taskul 1
void startTask(int index, char *inputPath);

// verifica daca number e putere a lui 2 prin cautarea unui singur bit de 1
bool isPowerOf2(int number);

// printeaza echipele dintr-o lista
void printTeams(std::list<Team*> list);
// printeaza echipele dintr-un meci pe aceeasi linie cu spatii si '-'
void printMatchedTeams(Match *match);
// printeaza o echipa si punctele sale
void printTeamScore(Team *team);

template <class T>
// elibereaza referintele dintr-o stiva si o si goleste
void freeStackContents(std::list<T*> &stack);
