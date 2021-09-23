#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>

class TestClass
{
public:
    TestClass();
public:
    signals:
        void TestSignal();
public slots:
         void TestSlot();
};

#endif // TESTCLASS_H
