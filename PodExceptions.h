#pragma once
#include <iostream>
#include "PodExceptions.h"

using namespace std;
class PodExceptions
{
	char* text_;
	int code_;
public:
	PodExceptions(char* text);
    void print (ostream& out);
	~PodExceptions(void);
	
};
