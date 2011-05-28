#include "main.h"

/*
  -o Output path
  -c Chapter sign

 */

int main (int argc, char** argv)
{
    Args* args = parseArgumets (argc,argv);
    destroyArgs (args);
    return 0;
}

Args* parseArgumets (int argc, char **argv)
{
   Args* args = new Args;
   args->chapterSign_=NULL;
   args->filename_=NULL;
   args->outputPath_=NULL;

   for (int i=0;i<argc;i++)
   {
       if (argv[i][0]=='-')
       {
           switch (argv[i][1])
           {
                case 'o':
                   {
                        if (i+1>=argc)
                        {
                            printf ("ERR_ARG_PARSE: Have you forgot some options?",argv[i]);
                            destroyArgs (args);
                            exit (100);
                        }
                        args->outputPath_= new char [strlen (argv[i+1])];
                        strcpy(args->outputPath_,argv[i+1]);
                        i++;
                        break;
                   }
                case 'c':
                   {
                        if (i+1>=argc)
                        {
                            printf ("ERR_ARG_PARSE: Have you forgot some options?",argv[i]);
                            destroyArgs (args);
                            exit (100);
                        }
                        args->chapterSign_ = new char [strlen(argv[i+1])];
                        strcpy(args->chapterSign_,argv[i+1]);
                        i++;
                        break;
                   }
           default:
                {
                        printf ("ERR_ARG_PARSE: Can't parse option '%s'\n",argv[i]);

                        exit (100);
                }
           }
       }
   }

   args->filename_ = new char [strlen(argv[argc-1])];
   strcpy(args->filename_,argv[argc-1]);
   return args;
}



void destroyArgs (Args *args)
{
    delete [] args->chapterSign_;
    delete [] args->filename_;
    delete [] args->outputPath_;
    delete args;
}
