#include "mapstar.h"

MapStar::MapStar(MainWindow *parentwindow,QWidget *parent) : QWidget(parent)
{
    window=parentwindow;
    setAttribute(Qt::WA_StaticContents);
    painting=false;
    color=Qt::white;
    scale=10;
    image=new QImage(0,0,QImage::Format_RGB32);
    image->fill(Qt::white);
    painter=new QPainter(image);
    maplabel=new QLabel(this);
    maplabel->setPixmap(QPixmap::fromImage(*image));
    setMinimumSize(image->size());

}

MapStar::~MapStar()
{

}

QSize MapStar::imageSize()
{
    return image->size();
}

void MapStar::print(){
    maplabel->setPixmap(QPixmap::fromImage(*image));
}

void MapStar::clearColor(int l, int w){
    for(int i=0;i<w;i++){
        for(int j=0;j<l;j++){
            if(QColor(image->pixel(scale*j,scale*i))==Qt::green || QColor(image->pixel(scale*j,scale*i))==Qt::yellow) pixel(QPoint(j,i),Qt::white);
        }
    }
}

void MapStar::draw(const QPoint & pos){
    if(scale!=0){
    painter->setPen(QPen(color,scale));
    painter->fillRect(scale*floor(pos.x()/scale),scale*floor(pos.y()/scale),scale,scale,color);
    QPoint p(floor(pos.x()/scale),floor(pos.y()/scale));
    window->getSolver()->setPoint(p,color);
    if(p==window->getSolver()->entry() && color!=Qt::blue) window->getSolver()->setEntry(QPoint(-1,0));
    if(p==window->getSolver()->exit() && color!=Qt::red) window->getSolver()->setExit(QPoint(-1,0));
    if(p!=window->getSolver()->entry() && color==Qt::blue) {if(window->getSolver()->entry().x()>=0) {
            window->getSolver()->setPoint(window->getSolver()->entry(),Qt::white);
            pixel(window->getSolver()->entry(),Qt::white);}
        window->getSolver()->setEntry(p);}
    if(p!=window->getSolver()->exit() && color==Qt::red) {if(window->getSolver()->exit().x()>=0) {
            window->getSolver()->setPoint(window->getSolver()->exit(),Qt::white);
            pixel(window->getSolver()->exit(),Qt::white);}
        window->getSolver()->setExit(p);}
    //window->info(window->getSolver()->matToString());
    print();
    }
}

void MapStar::pixel(const QPoint & pos, QColor c){
    if(scale!=0){
    painter->setPen(QPen(c,scale));
    painter->fillRect(scale*pos.x(),scale*pos.y(),scale,scale,c);
    print();
    }
}

void MapStar::generate(){
    delete painter;delete image;
    image=new QImage(scale*window->mapLength(),scale*window->mapWidth(),QImage::Format_RGB32);
    image->fill(Qt::white);
    painter=new QPainter(image);
    maplabel->setMinimumSize(image->size());
    maplabel->setPixmap(QPixmap::fromImage(*image));
    maplabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setMinimumSize(image->size());
    print();
    window->getSolver()->generateMat(window->mapLength(),window->mapWidth());
    //window->info(window->getSolver()->matToString());
    window->updateSize();
}

void MapStar::changeColor(){
    color=window->color();
}

void MapStar::clear(){
    clearColor(window->getSolver()->getLength(),window->getSolver()->getWidth());
}

void MapStar::mousePressEvent(QMouseEvent *event)
 {

    if (event->button() == Qt::LeftButton)  {
        draw(event->pos());
        lastpoint=event->pos();
        painting = true;
    }
}

void MapStar::mouseMoveEvent(QMouseEvent *event)
 {
    if ((event->buttons() & Qt::LeftButton) && painting && (color==Qt::white || color==Qt::black))  {
        int r=10;
        for(int i=1;i<=r;i++)    draw(i*event->pos()/r+(r-i)*lastpoint/r);
        lastpoint=event->pos();
    }

}

void MapStar::mouseReleaseEvent(QMouseEvent *event)
 {
    if (event->button() == Qt::LeftButton && painting && (color==Qt::white || color==Qt::black))  {
        draw(event->pos());
        painting = false;
    }
}



