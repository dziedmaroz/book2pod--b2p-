#ifndef BUFFER_H
#define BUFFER_H

#include "PodExceptions.h"
#include <cstring>
#include <stdio.h>

#define BUFF_SIZE 4096
#define SCREEN_SIZE 4097
class Buffer
{
    char buffer_ [BUFF_SIZE];
    int textBeg_;
    int textEnd_;
    int bufferEnd_;
    int inFileSize_;




    bool writeTagPrev (char* filename);
    bool writeTagNext (char* filename);
    bool writeTagTitle (char* title);
    bool shiftTextEndLeft (int count);
    int getDiff (FILE* file);
public:
    Buffer(int inFileSize);   
    bool prepareBuffer (char* nxtFilename, char* prevFilename, char* title);
    bool fillBuffer (FILE* fin);
    void terminateBuffer (int pos);
    bool writeBuffer (char* foutName);
    void writeStat (FILE* fout);
    ~Buffer (){};
};

#endif // BUFFER_H
