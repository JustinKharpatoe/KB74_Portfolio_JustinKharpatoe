#include "evidence.h"

evidence::evidence(QString name, int smileIndex):name(name),index(smileIndex), values(0), oper(0)
{

}

void evidence::setName(QString nam)
{
    name=nam;
}

void evidence::setvalues(QVector<float> val)
{
   values= val;
}

void evidence::setop(int op)
{
    oper = op;
}

int evidence::getIndex()
{
    return index;
}

QVector<float> evidence::getvalues()
{
    return values;
}

int evidence::getValuesSize()
{
    return values.size();
}

float evidence::getOnevalue(int post)
{
    return values[post];
}

int evidence::getop()
{
    return oper;
}

QString evidence::getName()
{
    return name;
}

//bool evidence::operator()(evidence *lhs, evidence *rhs)
//{
//    return (*lhs).getop() < (*rhs).getop();
//}

//bool evidence::operator<(evidence &R)
//{
// return this->getop()< R.getop();

//}



