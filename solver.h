#ifndef SOLVER_H
#define SOLVER_H

#include <QtWidgets>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include "mainwindow.h"
#include "mapstar.h"

class MainWindow;
class MapStar;

using namespace std;

class Solver
{
public:
    Solver(MainWindow *parentwindow, MapStar *parentmap);
    ~Solver();
    void setPoint(QPoint pos,QColor c); //set a point in the matrix
    QPoint entry(); //return the entry (in)
    QPoint exit(); //return the exit (out)
    void setEntry(QPoint pos); //set the entry
    void setExit(QPoint pos); //set the exit
    void generateMat(int l, int w); //generate a new matrix with given size
    string matToString(); //convert the matrix into string (correction tool)
    int getWidth(); //get width
    int getLength(); //get length
    void solve(); //solve the problem

private:
    void insert(QPoint pos); //insert *pos into *todo ordered relatively to *ecost (first positions in *todo have lost cost in *ecost)
    int dist(QPoint p,QPoint q); //return the distance between two points (manhattan distance)
    bool adm(QPoint q); //return true if *q is admissible (avoid out of range exceptions)

    MainWindow *window; //widget containing the solver
    MapStar *map; //map to draw

    int width; //width of the problem (mat width)
    int length; //length of the problem (mat length)
    vector< vector<int> > mat; //matrix representing the problem (0:nothing ; 1:entry ; -1:exit ; 2:wall)
    vector< vector<int> > process; //matrix of current processing (0:unprocessed ; 1:position to process (open list); 2:position processed (close list)),
    vector< vector<int> > cost; //cost from the entry to the position
    vector< vector<int> > ecost; //estimated cost from the entry to the exit through the position
    vector< vector<QPoint> > back; //parent to the position (to return optimal path)
    list<QPoint> todo; //positions to process
    QPoint in; //entry
    QPoint out; //exit
};

#endif // SOLVER_H
