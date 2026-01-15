#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>

using namespace std;

Board::Board() {
    // Заполняем всё поле пустыми клетками
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            grid[i][j] = EMPTY;
}

void Board::Print(bool hideShips) const {
    cout << "\n   ";
    for (int i = 1; i <= SIZE; i++) cout << i << " ";
    cout << "\n";

    for (int i = 0; i < SIZE; i++) {
        cout << char('A' + i) << "  ";
        for (int j = 0; j < SIZE; j++) {
            char ch = '.';

            if (grid[i][j] == SHIP && !hideShips) ch = '#';
            if (grid[i][j] == HIT) ch = 'X';
            if (grid[i][j] == MISS) ch = '*';

            cout << ch << " ";
        }
        cout << "\n";
    }
}

/*
  Проверяем, можно ли поставить корабль:
  - не выходит ли за границы
  - нет ли рядом других кораблей (даже по диагонали)
*/
bool Board::CanPlace(int r, int c, int len, bool horiz) const {
    for (int i = 0; i < len; i++) {
        int nr = r + (horiz ? 0 : i);
        int nc = c + (horiz ? i : 0);

        if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE)
            return false;

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                int rr = nr + dr;
                int cc = nc + dc;

                if (rr >= 0 && rr < SIZE && cc >= 0 && cc < SIZE) {
                    if (grid[rr][cc] == SHIP)
                        return false;
                }
            }
        }
    }
    return true;
}

void Board::Place(int r, int c, int len, bool horiz) {
    for (int i = 0; i < len; i++) {
        int nr = r + (horiz ? 0 : i);
        int nc = c + (horiz ? i : 0);
        grid[nr][nc] = SHIP;
    }
}

void Board::AutoPlace() {
    int ships[] = { 4,3,3,2,2,2,1,1,1,1 };

    for (int len : ships) {
        while (true) {
            int r = rand() % SIZE;
            int c = rand() % SIZE;
            bool h = rand() % 2;

            if (CanPlace(r, c, len, h)) {
                Place(r, c, len, h);
                break;
            }
        }
    }
}

/*
  Ручная расстановка:
  - ввод координаты
  - если корабль больше 1 клетки — спрашиваем направление
*/
void Board::manualSetup() {
    int ships[] = { 4,3,3,2,2,2,1,1,1,1 };

    for (int len : ships) {
        while (true) {
            Print(false);

            cout << "\nКорабль длиной " << len << endl;
            cout << "Введите координату (например A1): ";

            string s;
            cin >> s;

            int r = toupper(s[0]) - 'A';
            int c = stoi(s.substr(1)) - 1;

            bool horiz = true;

            // Направление имеет смысл только если корабль длиннее 1 клетки
            if (len > 1) {
                cout << "Направление (H - горизонтально, V - вертикально): ";
                char d;
                cin >> d;
                horiz = (toupper(d) == 'H');
            }

            if (CanPlace(r, c, len, horiz)) {
                Place(r, c, len, horiz);
                break;
            }
            else {
                cout << "Сюда поставить нельзя, попробуйте снова.\n";
            }
        }
    }
}

/*
  Выстрел:
  - попадание ? HIT
  - промах ? MISS
*/
bool Board::ShootAt(int r, int c) {
    if (grid[r][c] == HIT || grid[r][c] == MISS)
        return false;

    if (grid[r][c] == SHIP) {
        grid[r][c] = HIT;
        cout << "Попадание!\n";
        return true;
    }

    grid[r][c] = MISS;
    cout << "Мимо.\n";
    return false;
}

bool Board::HasShips() const {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (grid[i][j] == SHIP)
                return true;

    return false;
}
