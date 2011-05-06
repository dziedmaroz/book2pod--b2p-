#pragma once
#include <iostream>
 

using namespace std;
class PodExceptions
{
	char* text_;
public:
	PodExceptions(char* text);
    void print (ostream& out);
	~PodExceptions(void);
	
};
