#include <iostream>

#include "ZigZag/Object.hpp"
#include "ZigZag/BaseOperator.hpp"

#include "DataSource.hpp"


int main()
{


    ZigZag::Object obj1(nullptr, "aaa");
    ZigZag::Object obj3(&obj1, "b2  ");
    ZigZag::Object obj4(&obj1, "b2  ");
    ZigZag::Object obj2(&obj1, "b#2 3 ");
    ZigZag::Object obj5(&obj1, "b2  3");
    ZigZag::Object obj6(&obj1, "b2  2");
    ZigZag::Object obj7(&obj1, "b2  1");
    ZigZag::Object obj8(&obj1, "");
    ZigZag::Object obj9(&obj1, "1");
    ZigZag::Object obj10(&obj1, " 1  ");

    ZigZag::BaseOperator op1(&obj1, "op1");
    ZigZag::BaseDataSource* data1 = new ZigZag::BaseDataSource(&op1, "data1");
    ZigZag::BaseDataSource* data2 = new ZigZag::BaseDataSource(&op1, "data2");
    ZigZag::BaseDataSource* data3 = new ZigZag::BaseDataSource(&op1, "data3");

    ZigZag::BaseOperator op2(nullptr, "op2");
    ZigZag::BaseDataInput* input1 = new ZigZag::BaseDataInput(&op2, "inout1");

    //ZigZagOutput<BaseDataSource, BaseDataInput>*, ZigZagInput<BaseDataInput, BaseDataSource>*
    //connect(static_cast<ZigZagOutput<BaseDataSource, BaseDataInput>*>(data1), static_cast<ZigZagInput<BaseDataInput, BaseDataSource>*>(input1));
    ZigZag::connect(data3, input1);
    ZigZag::disconnect(data3, input1);

    int intData = 400;
    DataSource<int> ds(&op2, "haai", &intData);

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
    Object obj2(" b ", &obj1);
    Object obj4(" b   1", &obj1);
    Object obj6(" b", &obj1);
    Object obj5(" ", &obj1);*/

    return 0;
}
