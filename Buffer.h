#pragma once

#define BUFFER_SIZE 4096


#include <stdio.h>
#include <iostream>
#include <cstring>

class Buffer
{
	char _buffer [BUFFER_SIZE];
	int _bufferEnd;
	int _textBegin;
	int _textEnd;
public:
	Buffer(void);

	bool fillBuffer (FILE* fin);
	int fillBuffer (Buffer buff, int bytes);

	void writeTagPrev (char* filename);
	void writeTagNext (char* filename);
	void writeTagTitle(char* title);

	bool writeBuffer (char* filename);
	void terminateBuffer (int pos);
	void shiftLeft (int count);
	void shiftRight (int count);
	int findLastPunctuationMark (int);
	int tellSize ();

	~Buffer(void);
};
