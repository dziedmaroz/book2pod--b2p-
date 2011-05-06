#include "PodExceptions.h"
#include <cstring>




PodExceptions::PodExceptions(char* text)
{
	text_= new char [strlen(text)];
	strcpy(text_,text);
}

void PodExceptions::print (ostream& out)
{
	out<<text_<<endl;
}

PodExceptions::~PodExceptions(void)
{
	delete [] text_;
}
