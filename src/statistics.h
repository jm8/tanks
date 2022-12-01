#pragma once
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

struct Statistic {
    int numberOfShots;
    array<char, 3> name;

    string to_string() {
        return string(name.begin(), name.end()) + " " +
               std::to_string(numberOfShots);
    }
};

// Returns true if left is worse than right (i.e. has a higher numberOfShots).
// Falls back to alphabetical order.
inline bool operator<(Statistic left, Statistic right) {
    if (left.numberOfShots > right.numberOfShots)
        return true;
    if (left.numberOfShots < right.numberOfShots)
        return false;
    return !lexicographical_compare(left.name.begin(), left.name.end(),
                                    right.name.begin(), right.name.end());
}

class Statistics {
  public:
    void load() {
        ifstream file(filename);
        while (!statistics.empty())
            statistics.pop();
        if (!file.is_open()) {
            return;
        }
        Statistic statistic;
        while (file >> statistic.name[0] >> statistic.name[1] >>
               statistic.name[2] >> statistic.numberOfShots) {
            statistics.push(statistic);
        }
    }

    void save() {
        ofstream file(filename);
        for (Statistic statistic : topTen()) {
            file << statistic.to_string() << "\n";
        }
    }

    vector<Statistic> topTen() {
        vector<Statistic> result;
        priority_queue<Statistic> copy(statistics);
        for (int i = 0; i < 10 && !copy.empty(); i++) {
            result.push_back(copy.top());
            copy.pop();
        }
        return result;
    }

    void push(Statistic statistic) {
        statistics.push(statistic);
    }

  private:
    priority_queue<Statistic> statistics;

  private:
    constexpr static char *const filename = "tanks_leaderboard.txt";
};