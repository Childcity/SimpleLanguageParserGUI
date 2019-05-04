#ifndef MAIN_H
#define MAIN_H

#include <QDebug>

//#define DEBUGAST(msg) qDebug()<<__FILE__<<" ["<<__LINE__<<"]: "<<msg;
#define DEBUGAST(msg){}

//#define DEBUGTRE(msg) qDebug()<<__FILE__<<" ["<<__LINE__<<"]: "<<msg;
#define DEBUGTRE(msg){}

#define DEBUGM(msg) qDebug()<<__FILE__<<" ["<<__LINE__<<"]: "<<msg;

#define DEBUGSTCK(msg) qDebug()<<__FILE__<<" ["<<__LINE__<<"]: " <<msg <<"\n<<< STACK TRACE >>>"; \
for(const auto &it : stateStack) {                                                 \
    qDebug() <<it;                                          \
}

#define DEBUGSTATE(msg) qDebug()<<__FILE__<<" ["<<__LINE__<<"]: " <<msg <<"   " <<lexemeValue();

//#define DEBUGlex(msg) qDebug()<<__FILE__<<" ["<<__LINE__<<"]: "<<msg;
#define DEBUGlex(msg){}

//#define DEBUGSYNTX(msg) qDebug()<<__FILE__<<" ["<<__LINE__<<"]: "<<msg;
#define DEBUGSYNTX(msg){}

#define DEBUGEXE(msg) qDebug()<<__FILE__<<" ["<<__LINE__<<"]: "<<msg;
//#define DEBUGEXE(msg){}

#endif // MAIN_H
