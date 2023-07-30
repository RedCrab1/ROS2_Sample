#include "common/common.h"
#include <iostream>
using namespace std;

CommonLib::CommonLib()
{
	cout << "construct.."<<endl;
}

CommonLib::~CommonLib()
{
}

void CommonLib::Publish()
{
	cout << "this is common package func.."<< endl;
}

