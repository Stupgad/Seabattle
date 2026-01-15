#pragma once

const int SIZE = 10;

enum Cell { EMPTY, SHIP, HIT, MISS };

class Board {
    Cell grid[SIZE][SIZE];

public:
    Board();

    void Print(bool hideShips) const;

    bool CanPlace(int r, int c, int len, bool horiz) const;
    void Place(int r, int c, int len, bool horiz);

    void AutoPlace();
    void manualSetup();

    bool ShootAt(int r, int c);
    bool HasShips() const;
};
