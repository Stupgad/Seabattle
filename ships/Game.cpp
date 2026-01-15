#include "Game.h"
#include <iostream>
#include <ctime>
#include <string>
#include <limits>

using namespace std;

static void pause() {
    cout << "\nНажмите Enter, чтобы продолжить...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

Coord readCoord() {
    string s;
    cin >> s;
    return { toupper(s[0]) - 'A', stoi(s.substr(1)) - 1 };
}

void Game::Run() {
    srand((unsigned)time(nullptr));

    cout << "=========================\n";
    cout << "       МОРСКОЙ БОЙ\n";
    cout << "=========================\n\n";

    cout << "Выберите режим игры:\n";
    cout << "1. Игра на двоих\n";
    cout << "2. Игра против компьютера\n";
    cout << "Ваш выбор: ";
    int mode;
    cin >> mode;

    cout << "\nКак расставлять корабли?\n";
    cout << "1. Автоматически\n";
    cout << "2. Вручную\n";
    cout << "Ваш выбор: ";
    int setup;
    cin >> setup;

    int botLevel = 1;
    if (mode == 2) {
        cout << "\nСложность компьютера:\n";
        cout << "1. Лёгкая\n";
        cout << "2. Средняя\n";
        cout << "Ваш выбор: ";
        cin >> botLevel;
    }

    Board p1, p2;
    Bot bot;

    if (setup == 1) {
        
        p1.AutoPlace();
        p2.AutoPlace();
    }
    else {
        
        cout << "\nИгрок 1 расставляет корабли\n";
        p1.manualSetup();
        pause();

        if (mode == 1) {
          
            cout << "\nИгрок 2 расставляет корабли\n";
            p2.manualSetup();
            pause();
        }
        else {
          
            p2.AutoPlace();
            cout << "\nКомпьютер расставил свои корабли.\n";
            pause();
        }
    }


    bool turn = true;

    // Основной игровой цикл
    while (p1.HasShips() && p2.HasShips()) {
        Board& enemy = turn ? p2 : p1;

        cout << "\n-----------------------------\n";
        cout << "Ход: " << (turn ? "Игрок 1" : (mode == 1 ? "Игрок 2" : "Компьютер")) << endl;
        cout << "-----------------------------\n";

        enemy.Print(true);

        Coord c;
        if (!turn && mode == 2) {
            c = bot.MakeMove(SIZE);
            cout << "Компьютер стреляет: " << char('A' + c.r) << c.c + 1 << endl;
        }
        else {
            cout << "Введите координаты (например A5): ";
            c = readCoord();
        }

        bool hit = enemy.ShootAt(c.r, c.c);

        // Если бот попал на средней сложности — добавляем клетки вокруг в память
        if (hit && !turn && botLevel == 2)
            bot.RememberHit(c);

        if (!hit)
            turn = !turn;

        pause();
    }

    cout << "\n=========================\n";
    cout << "        ПОБЕДА!\n";
    cout << "=========================\n";

    if (p1.HasShips())
        cout << "Победил Игрок 1\n";
    else
        cout << "Победил " << (mode == 1 ? "Игрок 2" : "Компьютер") << "\n";

    cout << "\nСпасибо за игру!\n";
}
