#include "Buffer.h"

Buffer::Buffer(void)
{
    for (int i =0 ;i<BUFFER_SIZE;i++)
    {
            _buffer[i]=0;
    }
    _textBegin = 0;
    _textEnd = BUFFER_SIZE;
    _bufferEnd = BUFFER_SIZE;
}

Buffer::~Buffer(void)
{
}

bool Buffer::fillBuffer (FILE* fin)
{
    if (!fin)
    {
        int count =0;
        while (!feof(fin) && count+_textBegin < _textEnd)
        {
                _buffer[_textBegin+count++]=fgetc(fin);
        }
        _textEnd =_textBegin+count;
        return true;
    }
    return false;
}

int Buffer::fillBuffer (Buffer buffer, int bytes)
{
    int i=0;
    while (this->_textBegin+i < this->_textEnd && i<bytes)
    {
            this->_buffer [i+this->_textBegin] = buffer._buffer[i+buffer._textBegin];
            i++;
    }
    return i;
}

bool Buffer::writeBuffer (char* filename)
{
    FILE* fout = fopen (filename, "w");
    if (!fout) return false;

    for (int i=0;i<_bufferEnd;i++)
    {
            fprintf (fout,"%c",_buffer[i]);
    }
    fclose (fout);
    return true;
}

void Buffer::writeTagNext(char *filename)
{
    if (filename!=NULL)
    {
        char tagBegin [] = "<A HREF=\"";
        char tagEnd [] ="\"> -> </A>";
        int pos = _bufferEnd-strlen(tagBegin)-strlen(tagEnd)-strlen(filename);
        for (int i=0;i<strlen(tagBegin);i++)
        {
            _buffer[pos+i]=tagBegin[i];
        }
        pos +=strlen(tagBegin);
        for (int i=0;i<strlen(filename);i++)
        {
            _buffer[pos+i]=filename[i];
        }
        pos+=strlen(filename);
        for (int i=0;i<strlen(tagEnd);i++)
        {
            _buffer[pos+i]=tagEnd[i];
        }
    }
}

void Buffer::writeTagPrev(char *filename)
{
    if (filename!=NULL)
    {
        char tagBegin [] = "<A HREF=\"";
        char tagEnd [] = "\"> <- </A>";
        for (int i=0;i<strlen(tagBegin);i++)
        {
            _buffer[_textBegin+i]=tagBegin[i];
        }
        _textBegin+=strlen(tagBegin);
        for (int i=0;i<strlen(filename);i++)
        {
            _buffer[_textBegin+i]=filename[i];
        }
        _textBegin+=strlen(filename);
        for (int i=0;i<strlen(tagEnd);i++)
        {
            _buffer [_textBegin+i]=tagEnd[i];
        }
        _textBegin+=strlen(tagEnd);


    }
}

void Buffer::writeTagTitle (char *title)
{
    if (title!=NULL)
    {
        char tagBegin [] = "<TITLE>";
        char tagEnd [] = "</TITLE>";
        for (int i=0;i<strlen(tagBegin);i++)
        {
            _buffer[_textBegin+i]=tagBegin[i];
        }
        _textBegin+=strlen(tagBegin);
        for (int i=0;i<strlen(title);i++)
        {
            _buffer[_textBegin+i]=title[i];
        }
        _textBegin+=strlen(title);
        for (int i=0;i<strlen(tagEnd);i++)
        {
            _buffer [_textBegin+i]=tagEnd[i];
        }
        _textBegin+=strlen(tagEnd);
    }
}

void Buffer::terminateBuffer (int pos)
{
    _buffer[pos]='\0';
    _bufferEnd=pos;
}

int Buffer::findLastPunctuationMark (int end=BUFFER_SIZE)
{
  int i=_textEnd;
  if (_textEnd>end)
  {
      i=end;
  }
  while (i!='.' || i!=',' || i!='!' || i!=':' || i!=';' || i!='?') i--;
  return i;
}

void Buffer::shiftLeft (int count)
{
    for (int i=0;i<_bufferEnd-count;i++)
        _buffer[i]=_buffer[i+count];
}

void Buffer::shiftRight (int count)
{

}


int Buffer::tellSize ()
{
    return _textEnd - _textBegin;
}
