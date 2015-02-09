#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QScrollArea>
#include <string>
#include <algorithm>
#include "mapstar.h"
#include "solver.h"

class MapStar;
class Solver;

using namespace std;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
    void info(string txt); //show some information
    QColor color(); //return the color corresponding to the element chosen in settings
    int mapLength(); //return the length written in the text editor
    int mapWidth(); //return the width written in the text editor
    bool isSeen(); //return true if seencheck is checked
    void updateSize(); //update the size of the widget
    Solver * getSolver(); //return the solver

signals:

public slots:
    void solve(); //solve the problem

protected:
    void resizeEvent ( QResizeEvent * event ); //handles resizing events to fit the scroller

private:
    QScrollArea* scroller; //widget scroller
    QWidget *mainwidget; //main widget, inside the scroller

    QVBoxLayout *mainlayout; //layout of mainwidget
    QHBoxLayout *sizelayout; //layout of size widget
    QHBoxLayout *setlayout; //layout of settings widget
    QHBoxLayout *solvelayout; //layout of solving widget
    QGridLayout *maplayout; //layout of mapping widget
    QHBoxLayout *infolayout; //layout of information widget

    QLineEdit *length; //length text editor
    QLineEdit *width; //width text editor
    QPushButton *generate; //button to generate a solver with given width and length

    QRadioButton *inradio; //button to set an entry
    QRadioButton *wallradio; //button to set a wall
    QRadioButton *outradio; //button to set an exit
    QRadioButton *delradio; //button to delete an element

    QCheckBox *seencheck; //checkbox to make visited states appear
    QPushButton *solveb; //button to solve
    QPushButton *clearb; //button to clear green and yellow states (path and visited states)

    MapStar *map; //map widget
    Solver *solver; //handles the problem and its resolution

    QLabel *infolabel; //information label

};

#endif // MAINWINDOW_H
