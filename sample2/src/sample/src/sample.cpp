#include "sample/sample.h"
#include <iostream>

using namespace std;

Sample::Sample()
{
	lib_ = make_shared<CommonLib>();
}

Sample::~Sample()
{
}

void Sample::Publish()
{
	lib_->Publish();
}

int main(int argc, char ** argv)
{
  
  Sample sample;
  sample.Publish();

  return 0;
}
