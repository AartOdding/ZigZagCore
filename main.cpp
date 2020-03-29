#include <iostream>

#include "ZigZagObject.hpp"
#include "BaseOperator.hpp"

using namespace std;



int main()
{
    cout << "Hello World!" << endl;

    ZigZagObject obj1("aaa");
    ZigZagObject obj3("b2  ", &obj1);
    ZigZagObject obj4("b2  ", &obj1);
    ZigZagObject obj2("b#2 3 ", &obj1);
    ZigZagObject obj5("b2  3", &obj1);
    ZigZagObject obj6("b2  2", &obj1);
    ZigZagObject obj7("b2  1", &obj1);
    ZigZagObject obj8("", &obj1);
    ZigZagObject obj9("1", &obj1);
    ZigZagObject obj10(" 1  ", &obj1);

    BaseOperator op1("op1");
    BaseDataSource* data1 = new BaseDataSource(&op1, "data1");
    BaseDataSource* data2 = new BaseDataSource(&op1, "data2");
    BaseDataSource* data3 = new BaseDataSource(&op1, "data3");

    BaseOperator op2(nullptr, "op2");

    std::cout << "op1:\n";

    for (auto d : op1.getDataSources())
    {
        std::cout << d->getFullName() << std::endl;
    }

    std::cout << "op2:\n";

    for (auto d : op2.getDataSources())
    {
        std::cout << d->getFullName() << std::endl;
    }

    std::cout << "...:\n";

    data2->setParent(&op2);

    for (auto d : op1.getDataSources())
    {
        std::cout << d->getFullName() << std::endl;
    }

    std::cout << "op2:\n";

    for (auto d : op2.getDataSources())
    {
        std::cout << d->getFullName() << std::endl;
    }
    /*
    ZigZagObject obj2(" b ", &obj1);
    ZigZagObject obj4(" b   1", &obj1);
    ZigZagObject obj6(" b", &obj1);
    ZigZagObject obj5(" ", &obj1);*/

    cout << "Hello World!" << endl;
    cout << "Hello World!" << endl;
    cout << "Hello World!" << endl;
    cout << "Hello World!" << endl;
    return 0;
}
