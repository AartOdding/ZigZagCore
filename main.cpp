#include <iostream>

#include "ZigZagObject.hpp"
#include "BaseOperator.hpp"
#include "ZigZagParentChild.hpp"
#include "ZigZagInputOutput.hpp"



int main()
{
    std::cout << "Hello World!" << std::endl;

    ZigZagObject obj1(nullptr, "aaa");
    ZigZagObject obj3(&obj1, "b2  ");
    ZigZagObject obj4(&obj1, "b2  ");
    ZigZagObject obj2(&obj1, "b#2 3 ");
    ZigZagObject obj5(&obj1, "b2  3");
    ZigZagObject obj6(&obj1, "b2  2");
    ZigZagObject obj7(&obj1, "b2  1");
    ZigZagObject obj8(&obj1, "");
    ZigZagObject obj9(&obj1, "1");
    ZigZagObject obj10(&obj1, " 1  ");

    BaseOperator op1(&obj1, "op1");
    BaseDataSource* data1 = new BaseDataSource(&op1, "data1");
    BaseDataSource* data2 = new BaseDataSource(&op1, "data2");
    BaseDataSource* data3 = new BaseDataSource(&op1, "data3");

    BaseOperator op2(nullptr, "op2");
    BaseDataInput* input1 = new BaseDataInput(&op2, "inout1");

    //ZigZagOutput<BaseDataSource, BaseDataInput>*, ZigZagInput<BaseDataInput, BaseDataSource>*
    //connect(static_cast<ZigZagOutput<BaseDataSource, BaseDataInput>*>(data1), static_cast<ZigZagInput<BaseDataInput, BaseDataSource>*>(input1));
    connect(data3, input1);
    disconnect(data3, input1);

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

    return 0;
}
