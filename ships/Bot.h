#pragma once
#include <vector>

struct Coord {
    int r, c;
};

struct Bot {
    std::vector<Coord> memory;

    Coord MakeMove(int size) {
        if (!memory.empty()) {
            Coord c = memory.back();
            memory.pop_back();
            return c;
        }
        return { rand() % size, rand() % size };
    }

    // 
    void RememberHit(Coord c) {
        memory.push_back({ c.r + 1, c.c });
        memory.push_back({ c.r - 1, c.c });
        memory.push_back({ c.r, c.c + 1 });
        memory.push_back({ c.r, c.c - 1 });
    }
};
