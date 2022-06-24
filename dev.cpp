#include<iostream>
#include <cstring>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include<math.h>
#include <algorithm>

using namespace std;

class Point {
    private:
    int x, y;   // assuming limit of -1e9=<x<=1e9, -1e9=<y<=1e9

    public:
    Point() {
        this->x = 0;
        this->y = 0;
    }

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int GetX() {
        return x;
    }

    int GetY() {
        return y;
    }
};

class Grid: public Point{
    private:
    vector<Point*> aliveCells;

    bool CheckForAliveInNextGen(int xCord, int yCord) {
        int aliveNeigbours = 0;
        int dX[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
        int dY[8] = {0, -1, -1, -1, 0, 1, 1, 1};

        for(int i = 0; i < 8; i++) {
            if(checkAliveCell(xCord+dX[i], yCord+dY[i])) {
                aliveNeigbours++;
            }
        }

        if(checkAliveCell(xCord, yCord)) {
            if((aliveNeigbours > 3) || (aliveNeigbours < 2)) {
                return false;
            }
        } else if(aliveNeigbours != 3) {
            return false;
        }
        return true;
    }

    bool checkAliveCell(int xCord, int yCord) {
        for(int i = 0; i < aliveCells.size(); i++) {
            if((aliveCells[i]->GetX() == xCord) && (aliveCells[i]->GetY() == yCord)) {
                return true;
            }
        }
        return false;
    }

     Point* GetLeftBottom() {
        int mnx = 1e9, mny = 1e9;
        for(int i = 0; i < aliveCells.size(); i++) {
            mnx = min(mnx, aliveCells[i]->GetX());
            mny = min(mny, aliveCells[i]->GetY());
        }

        return new Point(mnx, mny);
    }

    Point* GetRightBottom() {
        int mnx = -1e9, mny = 1e9;
        for(int i = 0; i < aliveCells.size(); i++) {
            mnx = max(mnx, aliveCells[i]->GetX());
            mny = min(mny, aliveCells[i]->GetY());
        }

        return new Point(mnx, mny);
    }

    Point* GetLeftTop() {
        int mnx = 1e9, mny = -1e9;
        for(int i = 0; i < aliveCells.size(); i++) {
            mnx = min(mnx, aliveCells[i]->GetX());
            mny = max(mny, aliveCells[i]->GetY());
        }

        return new Point(mnx, mny);
    }

    Point* GetRightTop() {
        int mnx = -1e9, mny = -1e9;
        for(int i = 0; i < aliveCells.size(); i++) {
            mnx = max(mnx, aliveCells[i]->GetX());
            mny = max(mny, aliveCells[i]->GetY());
        }

        return new Point(mnx, mny);
    }

    public:
    Grid() {
        aliveCells = vector<Point*>();
    }

    void Add(int x, int y) {
        Point *p = new Point(x, y);
        aliveCells.push_back(p);
    }

    void PrintNextGeneration() {
        Point *leftBottom, *leftTop, *rightBottom, *rightTop;

        leftBottom = GetLeftBottom();
        leftTop = GetLeftTop();

        rightBottom = GetRightBottom();
        rightTop = GetRightTop();

        vector<Point*> nextGenAliveCells = GetNextGenAliveCells(leftBottom, leftTop, rightBottom, rightTop);
        for(int i = 0; i < nextGenAliveCells.size(); i++) {
            cout << nextGenAliveCells[i]->GetX() << " " << nextGenAliveCells[i]->GetY() << "\n";
        }
    }

    vector<Point*> GetNextGenAliveCells(Point *leftBottom, Point *leftTop, Point *rightBottom, Point *rightTop) {
        vector<Point*> nextGenAliveCells;
        for(int x = leftBottom->GetX() - 1; x <= rightBottom->GetX() + 1; x++) {
            for(int y = leftBottom->GetY() - 1; y <= leftTop->GetY() + 1; y++) {
                if(CheckForAliveInNextGen(x, y)) {
                    Point *p = new Point(x, y);
                    nextGenAliveCells.push_back(p);
                }
            }
        }
        return nextGenAliveCells;
    }
};

int main() {
    while (1) {
       cout << "Welcome to Game Of Life. List of Options: \n" \
            << "1 to continue...\n" \
            << "2 to exit.\n" \
            << "##################\n";
        
        int choice;
        cin >> choice;
        if(choice == 2) {
            cout << "you choose to exit the Game OF Life.\n";
            break;
        }
        cout << "you choose to continue the Game OF Life.\n";

        int numberOfAliveInitialCells, xCord, yCord;

        cout << "Enter number of initial alive cells in universe: ";
        cin >> numberOfAliveInitialCells;

        Grid *infinteGrid = new Grid();
        while(numberOfAliveInitialCells--) {
            cin >> xCord >> yCord;
            infinteGrid->Add(xCord, yCord);
        }

        cout << "next generation alive cells \n";
        infinteGrid->PrintNextGeneration();
        cout << "\n";
    }
}