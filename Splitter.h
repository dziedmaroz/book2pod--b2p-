#pragma once

#include <fstream>
#include <iostream>
#define FILESIZE 4096
#define LOGFILE "splitlog.log"

using namespace std;

struct Args
{
    char* chapterSign_;
    char* filename_;
    char* outputPath_;
    bool verbose_;
    char* outLog_;
};

class Splitter
{

	char* title_;
	char* chapterSign_;
	int maxPieces_;
	char* filename_;
	char* outputPath_;
    int filesize_;
        bool verbose_;
        bool verbScreen_;
        ostream log_;

        Splitter(void);
        int getFileSize (char* filename);
public:
        Splitter (char* filename,bool verbose, char* logOutput="", char* outputPath ="", char* chaterSign="√À¿¬¿") ;
        Splitter& operator= (Splitter& orig);
    bool Split ();
        ~Splitter(void);



};
