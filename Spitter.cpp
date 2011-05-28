#include "Splitter.h"
#include <cstring>
#include <cstdlib>
#include "Buffer.h"
#define DIR_SEP '/'

Splitter::Splitter (Args *args)
{
    _isErrors = false;
    _chapterSign = new char [strlen (args->chapterSign_)];
    if ( args->chapterSign_!=NULL)
    {
        strcpy (_chapterSign,args->chapterSign_);
    }
    else
    {
        _chapterSign = NULL;
        _isErrors = true;
    }

    _filename = new char [strlen (args->filename_)];
    if (args->filename_!=NULL)
    {
        strcpy (_filename,args->filename_);
    }
    else
    {
        _filename = NULL;
        _isErrors = true;
    }

    _sourceFile = fopen (_filename,"r");
    if (!_sourceFile)
    {
        _isErrors = true;
    }
    else
    {
        fseek (_sourceFile,0,SEEK_END);
        _filesize = ftell (_sourceFile);
        rewind (_sourceFile);
    }

    _outputPath = new char [strlen(args->outputPath_)];
    if (args->outputPath_!=NULL)
    {
        strcpy (_outputPath,args->outputPath_);
    }
    else
    {
        _isErrors=true;
    }

    _currentPiece = 0;
    _currentTitle = NULL;

    if (_isErrors)
    {
        printf ("ERR_INIT: There were some errors while init\n");
        freeAll ();
    }

}

void Splitter::freeAll ()
{
    delete [] _chapterSign;
    delete [] _filename;
    delete [] _outputPath;
    delete [] _currentTitle;
    fclose (_sourceFile);
}

void Splitter::findChapter ()
{
    fpos_t file_pos;
    fgetpos (_sourceFile,&file_pos);

    char* buff = new char [BUFFER_SIZE];
    for (int i=0;i<BUFFER_SIZE;i++)
    {
        buff[i]=fgetc(_sourceFile);
    }

    char* where = strstr (buff,_chapterSign);
    int len=0;
    if (where !=NULL)
    {
        while (where[len++]!='\n');

        delete [] _currentTitle;
        _currentTitle = new char [len];
        for (int i=0;i<len;i++)
        {
            _currentTitle[i]= where[i];
        }
    }

    delete [] buff;
}

bool Splitter::Split ()
{
    while (!feof (_sourceFile))
    {
        int diff = _filesize-ftell(_sourceFile);
        Buffer frstBuffer ;
        frstBuffer.fillBuffer (_sourceFile);
        findChapter ();
        char* prevFile = NULL;
        char* nextFile = NULL;
        char* curFile = numToString (_currentPiece);
        if (_currentPiece!=0)
        {
            prevFile = numToString (_currentPiece-1);
        }

        if (diff>BUFFER_SIZE)
        {
            nextFile = numToString (_currentPiece+1);
        }

        Buffer scndBuffer;
        scndBuffer.writeTagPrev (prevFile);
        scndBuffer.writeTagTitle (_currentTitle);
        scndBuffer.writeTagNext (nextFile);

        delete [] nextFile;
        delete [] prevFile;

        int mark = frstBuffer.findLastPunctuationMark (scndBuffer.tellSize ());
        scndBuffer.fillBuffer (frstBuffer, mark);

        scndBuffer.writeBuffer (curFile);
        delete [] curFile;
    }
}

char* Splitter::numToString (int x)
{
    char* res = new char [NUMSIZE];
    for (int i=0;i<NUMSIZE;i++)
    {
        res[i]='0';
    }

    int i=0;
    while (x!=0)
    {
        res[NUMSIZE-1-i]=x%10+'0';
        x/=10;
        i++;
    }
    return res;
}
