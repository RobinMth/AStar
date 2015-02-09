#ifndef MAPSTAR_H
#define MAPSTAR_H

#include <QtWidgets>
#include <QString>
#include <QImage>
#include <QPainter>
#include <cmath>
#include "mainwindow.h"

class MainWindow;

class MapStar : public QWidget
{
    Q_OBJECT
public:
    MapStar(MainWindow *parentwindow,QWidget *parent = 0);
    ~MapStar();
    QSize imageSize(); //return the size of the image (in pixels)
    void draw( const QPoint & position); //draw a pixel after a click and process the changes (position in pixels)
    void pixel(const QPoint & pos, QColor c); //draw a pixel (no processing and the position refers to the solver, i.e in pixel/scale)
    void print(); //print the image (update)
    void clearColor(int l, int w); //clear colors which are not {entry,wall,exit}, i.e green and yellow


public slots:
    void generate(); //generate a new map
    void changeColor(); //change current color
    void clear(); //see clearColor()

protected:
    void mousePressEvent(QMouseEvent *event); //handles mouse pressing events
    void mouseMoveEvent(QMouseEvent *event); //handles mouse moving events
    void mouseReleaseEvent(QMouseEvent *event); //handles mous releasing events

private:
    MainWindow *window; //widget containing the map
    bool painting; //true if the map is being painted
    QPainter *painter; //painter of the image
    QColor color; //current color
    QImage *image; //image to show and draw
    QLabel *maplabel; //label that contains the image
    QPoint lastpoint; //last point drawn
    int scale; //scale
};

#endif // MAPSTAR_H
