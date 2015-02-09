#include "solver.h"

using namespace std;

Solver::Solver(MainWindow *parentwindow, MapStar *parentmap)
{
    window=parentwindow;
    map=parentmap;
    length=0;
    width=0;
    in.setX(-1);
    out.setX(-1);
}

Solver::~Solver(){

}

void Solver::setPoint(QPoint pos,QColor c){
    int v=0;
    if(c==Qt::blue)v=1;
    if(c==Qt::red)v=-1;
    if(c==Qt::black)v=2;
    if(pos.x()<length && pos.x()>=0 && pos.y()<width && pos.y()>=0) mat[pos.y()][pos.x()]=v;
}

QPoint Solver::entry(){
    return in;
}

QPoint Solver::exit(){
    return out;
}

void Solver::setEntry(QPoint pos){
    in=pos;
}

void Solver::setExit(QPoint pos){
    out=pos;
}

void Solver::generateMat(int l, int w){
    mat.clear();
    vector<int> row(l,0);
    for(int i=0;i<w;i++) mat.push_back(row);
    length=l;
    width=w;
    in.setX(-1);
    out.setX(-1);
}

string Solver::matToString(){
    string s;s+=to_string(width)+" x "+to_string(length)+"\n";
    for(int i=0;i<width;i++){
        for(int j=0;j<length;j++){
            s+=to_string(mat[i][j])+" ; ";
        }
        s+=" \n";
    }
    s+="Entrée :("+to_string(in.x())+","+to_string(in.y())+") \n";
    s+="Sortie :("+to_string(out.x())+","+to_string(out.y())+") \n";
    return s;
}

int Solver::getWidth(){
    return width;
}

int Solver::getLength(){
    return length;
}

void Solver::solve(){
    if(in.x()>=0 && out.x()>=0){
    //initialisation
    process.clear();cost.clear();ecost.clear();back.clear();todo.clear();
    vector<int> row(length,0);vector<int> rowm(length,-1);vector<QPoint> rowp(length,QPoint(-1,0));
    for(int i=0;i<width;i++) {process.push_back(row);cost.push_back(rowm);ecost.push_back(row);back.push_back(rowp);}
    cost[in.y()][in.x()]=0;
    ecost[in.y()][in.x()]=dist(in,out);
    insert(in);
    bool found=false;
    QPoint p;
    list<QPoint> succ;
    map->clearColor(length,width);

    while(!found && !todo.empty()){
        p=todo.front();todo.pop_front();
        process[p.y()][p.x()]=2;
        if(p==out) found=true;
        else{
            succ.push_back(p+QPoint(1,0)); succ.push_back(p+QPoint(0,1)); succ.push_back(p+QPoint(-1,0)); succ.push_back(p+QPoint(0,-1));
            for (list<QPoint>::const_iterator q = succ.begin(); q != succ.end(); ++q){
                if(adm(*q) && process[q->y()][q->x()]==0 && mat[q->y()][q->x()]!=2 ){
                    if(cost[q->y()][q->x()]==-1 || cost[q->y()][q->x()]>cost[p.y()][p.x()]+1){
                        cost[q->y()][q->x()]=cost[p.y()][p.x()]+1;
                        ecost[q->y()][q->x()]=cost[q->y()][q->x()]+dist(*q,out);
                        back[q->y()][q->x()]=p;
                        process[q->y()][q->x()]=1;
                        insert(*q);
                        if(window->isSeen()) {map->pixel(*q,Qt::yellow);window->update();}
                    }
                }
            } succ.clear();
        }
    }

    if(found) {
        window->info("Chemin trouvé");
        QPoint pp(out);pp=back[pp.y()][pp.x()];
        while(pp!=in){
            map->pixel(pp,Qt::green);
            pp=back[pp.y()][pp.x()];
        }
        map->pixel(out,Qt::red);
    }
    else {window->info("Impossible de joindre l'entrée à la sortie");}


}
    else {window->info("L'éntrée/sortie n'a pas été placée !");}

    /* //insert function test, put generate before clearing matrixes
      generateMat(4,4);
    ecost[0][1]=1;ecost[1][2]=2;ecost[2][3]=3;
    insert(QPoint(3,2));insert(QPoint(1,0));insert(QPoint(2,1));
    string s="";
    for (list<QPoint>::const_iterator i = todo.begin(); i != todo.end(); ++i){
        s+="("+to_string(i->y())+","+to_string(i->x())+") ";
    }
    window->info(s);*/
}

void Solver::insert(QPoint pos){
    if(todo.empty()) {todo.push_back(pos);return;}
    for (list<QPoint>::const_iterator i = todo.begin(); i != todo.end(); ++i){
        if(ecost[pos.y()][pos.x()]<ecost[i->y()][i->x()]){todo.insert(i,pos);return;}
    }
    todo.push_back(pos);return;
}

int Solver::dist(QPoint p,QPoint q){
    return abs(p.x()-q.x())+abs(p.y()-q.y());
}

bool Solver::adm(QPoint q){
    return (q.x()>=0 && q.y()>=0 && q.x()<length && q.y()<width);
}
