#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow()
{

    //Layout
mainlayout=new QVBoxLayout;
sizelayout=new QHBoxLayout;
setlayout=new QHBoxLayout;
solvelayout=new QHBoxLayout;
maplayout=new QGridLayout;
infolayout=new QHBoxLayout;infolayout->setSizeConstraint(QLayout::SetMinimumSize);

    //Widgets
QGroupBox *sizebox = new QGroupBox("Dimensions");
length=new QLineEdit;length->setMaximumWidth(25);
width=new QLineEdit;width->setMaximumWidth(25);
generate=new QPushButton("Générer");generate->setMaximumWidth(60);

QGroupBox *setbox = new QGroupBox("Placer");
inradio=new QRadioButton("Entrée");
wallradio=new QRadioButton("Mur");
outradio=new QRadioButton("Sorties");
delradio=new QRadioButton("Effacer");

QGroupBox *solvebox = new QGroupBox("Résoudre");
seencheck=new QCheckBox("États visités");
solveb=new QPushButton("Résoudre");solveb->setMaximumWidth(60);
clearb=new QPushButton("Nettoyer");solveb->setMaximumWidth(60);

QGroupBox *mapbox = new QGroupBox("Carte");
map=new MapStar(this);

QGroupBox *infobox = new QGroupBox("Informations");
infolabel=new QLabel(" Informations ");



    //Integration
sizebox->setLayout(sizelayout);
mainlayout->addWidget(sizebox);
setbox->setLayout(setlayout);
mainlayout->addWidget(setbox);
solvebox->setLayout(solvelayout);
mainlayout->addWidget(solvebox);
mapbox->setLayout(maplayout);
mainlayout->addWidget(mapbox);
infobox->setLayout(infolayout);
mainlayout->addWidget(infobox);

sizelayout->addWidget(width);
sizelayout->addWidget(new QLabel(" lignes"));
sizelayout->addWidget(length);
sizelayout->addWidget(new QLabel(" colonnes"));
sizelayout->addWidget(generate);
sizelayout->addWidget(new QLabel(" "));sizelayout->setStretch(5,400);

setlayout->addWidget(inradio);
setlayout->addWidget(wallradio);
setlayout->addWidget(outradio);
setlayout->addWidget(delradio);
setlayout->setStretch(3,50);

solvelayout->addWidget(seencheck);
solvelayout->addWidget(solveb);
solvelayout->addWidget(clearb);
solvelayout->addWidget(new QLabel(" "));solvelayout->setStretch(3,400);

maplayout->addWidget(map);

infolayout->addWidget(infolabel);


    //Scroller
mainwidget=new QWidget();
mainwidget->setLayout(mainlayout);
scroller = new QScrollArea(this);
scroller->setWidget(mainwidget);
scroller->resize(mainwidget->size()+QSize(20,20));
resize(mainwidget->size()+QSize(20,20));
scroller->setMinimumWidth(mainwidget->width()+20);
setMinimumWidth(mainwidget->width()+20);
scroller->setMaximumHeight(700);
setMaximumHeight(700);
scroller->setWidgetResizable(true);
scroller->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
scroller->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded);

    //Connection
QObject::connect(generate, SIGNAL(clicked()), map, SLOT(generate()));
QObject::connect(inradio, SIGNAL(clicked()), map, SLOT(changeColor()));
QObject::connect(wallradio, SIGNAL(clicked()), map, SLOT(changeColor()));
QObject::connect(outradio, SIGNAL(clicked()), map, SLOT(changeColor()));
QObject::connect(delradio, SIGNAL(clicked()), map, SLOT(changeColor()));
QObject::connect(solveb, SIGNAL(clicked()), this, SLOT(solve()));
QObject::connect(clearb, SIGNAL(clicked()), map, SLOT(clear()));

solver=new Solver(this,map);
info(to_string(size().width())+" ; "+to_string(mainwidget->width()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::info(string txt)
{
    infolabel->setText(QString::fromStdString(txt));
    infolabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    updateSize();

}

QColor MainWindow::color(){
    if(inradio->isChecked()) return Qt::blue;
    if(wallradio->isChecked()) return Qt::black;
    if(outradio->isChecked()) return Qt::red;
    if(delradio->isChecked()) return Qt::white;
    return Qt::white;
}

int MainWindow::mapLength(){
    int l=length->text().toInt();
    l=std::max(0,std::min(99,l));
    return l;
}

int MainWindow::mapWidth(){
    int w= width->text().toInt();
    w=std::max(0,std::min(99,w));
    return w;
}

bool MainWindow::isSeen(){
    return seencheck->isChecked();
}

void MainWindow::updateSize(){
    setMinimumWidth(mainwidget->minimumSizeHint().width() + scroller->verticalScrollBar()->width());
    update();
}

Solver * MainWindow::getSolver(){
    return solver;
}

void MainWindow::solve(){
    solver->solve();
}

void MainWindow::resizeEvent ( QResizeEvent * event ){
    scroller->resize(size());
}

