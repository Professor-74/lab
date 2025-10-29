#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    int i, j, staddr1;
    char line[50], name1[50], staddr[200];

    fp = fopen("ab.txt", "r");
    if (fp == NULL)
    {
        printf("Error: cannot open file ab.txt\n");
        return 1;
    }

   
    fscanf(fp, "%s", line);

    
    for (i = 2, j = 0; line[i] != '^' && line[i] != '\0'; i++, j++)
    {
        name1[j] = line[i];
    }
    name1[j] = '\0';

    printf("Name of object program is %s\n", name1);


    while (!feof(fp))
    {
        fscanf(fp, "%s", line);


        if (line[0] == 'T')
        {

            for (i = 2, j = 0; line[i] != '^' && line[i] != '\0'; i++, j++)
            {
                staddr[j] = line[i];
            }
            staddr[j] = '\0';
            staddr1 = atoi(staddr);

          
            i = 12;

  
            while (line[i] != '$' && line[i] != '\0')
            {
                if (line[i] != '^')
                {
                    printf("00%d\t%c%c\n", staddr1, line[i], line[i + 1]);
                    staddr1++;
                    i += 2;
                }
                else
                {
                    i++;
                }
            }
        }

     
        if (line[0] == 'E')
        {
            fclose(fp);
            break;
        }
    }

    return 0;
}
