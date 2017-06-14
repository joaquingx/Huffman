/* FEOF example */
#include <stdio.h>

int main(int argc , char * argv[])
{
  FILE * pFile;
  char buffer [100];
  pFile = fopen (argv[1] , "r");
  if (pFile == NULL) perror ("Error opening file");
  else
    {
      while ( ! feof (pFile) )
        {
          if ( fgets (buffer , 100 , pFile) == NULL ) break;
          for(int j = 0 ; buffer[j] != 0 ; ++j)
            {

              // cout << int(buffer[j]) << "\n" ;
              printf("%d ",int((unsigned char)buffer[j]));
            }
        }
      printf("\n");
      fclose (pFile);
    }
  return 0;
}
