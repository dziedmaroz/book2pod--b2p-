#include "Buffer.h"

#include <cstdlib>

Buffer::Buffer ()
{
    textBeg_=0;
    textEnd_=BUFF_SIZE-1;
    bufferEnd_=BUFF_SIZE-1;

}
bool Buffer::writeTagTitle (char *title)
{
    if (title!=NULL)
    {
        char tagBeg [] = "<TITLE>";
        char tagEnd [] = "</TITLE>";

        for (int i=0;i<strlen(tagBeg);i++)
        {
            buffer_[textBeg_++]=tagBeg[i];
            if (textBeg_>textEnd_) return false;
        }
        for (int i=0;i<strlen(title);i++)
        {
            buffer_[textBeg_++]=title[i];
            if (textBeg_>textEnd_) return false;
        }
        for (int i=0;i<strlen(tagEnd);i++)
        {
            buffer_[textBeg_++]=tagEnd[i];
            if (textBeg_>textEnd_) return false;
        }
    }
    return true;
}

bool Buffer::writeTagPrev (char *filename)
{
    if (filename!=NULL)
    {
        char tagBeg [] = "<A HREF=\"";
        char tagEnd [] = "\"> <- </A>";

        for (int i=0;i<strlen(tagBeg);i++)
        {
            buffer_[textBeg_++]=tagBeg[i];
            if (textBeg_>textEnd_) return false;
        }
        for (int i=0;i<strlen(filename);i++)
        {
            buffer_[textBeg_++]=filename[i];
            if (textBeg_>textEnd_) return false;
        }
        for (int i=0;i<strlen(tagEnd);i++)
        {
            buffer_[textBeg_++]=tagEnd[i];
            if (textBeg_>textEnd_) return false;
        }
    }
   return true;
}

bool Buffer::writeTagNext (char *filename)
{
    if (filename!=NULL)
    {
        char tagBeg [] = "<A HREF=\"";
        char tagEnd [] = "\"> -> </A>";
        textEnd_=BUFF_SIZE-1;

        for(int i=strlen(tagEnd);i>0;i--)
        {
            buffer_[textEnd_]=tagEnd[i-1];
            textEnd_--;
            if (textBeg_>textEnd_) return false;
        }

        for (int i=strlen(filename);i>0;i--)
        {
            buffer_[textEnd_--]=filename[i-1];
            if (textBeg_>textEnd_) return false;
        }

        for (int i=strlen(tagBeg);i>0;i--)
        {
            buffer_[textEnd_--]=tagBeg[i-1];
            if (textBeg_>textEnd_) return false;
        }
        if ((textEnd_-textBeg_)%2 !=0 )
        {
            for (int i=textEnd_;i<BUFF_SIZE;i++)
                buffer_[i-1]=buffer_[i];
            textEnd_--;
            buffer_[BUFF_SIZE-1]='\0';
        }
    }
    return true;
}

bool Buffer::writeBuffer (char *foutName)
{
    FILE* fout = fopen (foutName,"w");
    if (!fout) return false;
    int i=0;
    while (buffer_[i]!='\0' && i<BUFF_SIZE)
        fprintf (fout,"%c",buffer_[i++]);
    fclose (fout);
    return true;
}

bool Buffer::fillBuffer (FILE *fin)
{

     for (int i=textBeg_;i<textEnd_-1;i++)
     {
         buffer_[i]=fgetc(fin);
     }      
     for (int i=SCREEN_SIZE;i<textEnd_;i++)
     {
         if (buffer_[i]!=' ')
         {
             for (int j=i;j>i-SCREEN_SIZE;j--)
                 if (buffer_[j]==' ')
                 {
                     buffer_[j]='\n';
                     break;
                 }
         }
         else
         {
             buffer_[i]='\n';
         }
     }
     for (int i=0;i<bufferEnd_;i++)
         if (buffer_[i]=='\0') buffer_[i]=' ';
     return true;
}

void Buffer::terminateBuffer (int pos)
{
    buffer_[pos]='\0';
    bufferEnd_=pos;
}

bool Buffer::prepareBuffer (char *nxtFilename, char *prevFilename, char *title)
{
    if (writeTagTitle (title))
    {
        if (writeTagPrev (prevFilename))
        {
            if (writeTagNext (nxtFilename))
            {
                if ((textEnd_-textBeg_)%4 !=0)
                {
                    {
                        shiftTextEndLeft ((textEnd_-textBeg_)%4+1);
                    }
                }
            }
        }
    }
    return false;
}

bool Buffer::shiftTextEndLeft (int count)
{
    for (int i=textEnd_;i<BUFF_SIZE;i++)
    {
        buffer_[i-count]=buffer_[i];
    }
    textEnd_-=count;
    terminateBuffer (BUFF_SIZE-count);    
    return textEnd_>textBeg_;
}
