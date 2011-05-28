#pragma once

#include <fstream>
#include <iostream>
#include <cstring>


#define BUFFER_SIZE 4096
#define LOGFILE "splitlog.log"
#define NUMSIZE 8

using namespace std;

struct Args
{
    char* chapterSign_;
    char* filename_;
    char* outputPath_;        

};

class Splitter
{

    char* _chapterSign;
    char* _filename;
    char* _outputPath;
    char* _currentTitle;

    int _filesize;
    int _currentPiece;

    FILE* _sourceFile;

    bool _isErrors;

    Splitter ();
    void freeAll ();
    void findChapter ();
    char* numToString (int x);
public:
    Splitter (Args* args);

    bool Split ();

    ~Splitter ();




};
