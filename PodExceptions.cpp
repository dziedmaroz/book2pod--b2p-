#include "PodExceptions.h"
#include <cstring>




PodExceptions::PodExceptions(int code,char* text)
{
	text_= new char [strlen(text)];
	strcpy(text_,text);
	code_=code;
}

void PodExceptions::print (ostream& out)
{
	out<<code_<<":"<<text_<<endl;
}

PodExceptions::~PodExceptions(void)
{
	delete [] text_;
}
