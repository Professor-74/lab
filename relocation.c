#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 int main()
{
	FILE *fp1, *fp2;
	int i, j, hexaddr, start_hexaddr;
	char line[50], addr[10];
	fp1 = fopen("inputr.txt", "r");
	printf("Enter the actual starting address:");
	scanf("%x", &start_hexaddr );
	
	do{
		fscanf(fp1, "%s", line);
		if (line[0]=='T')
		{
			for(i=1, j=0; i<7; i++, j++)
			{
				addr[j] = line[i];
				}
				addr[j]='\0';
				
				
				fp2 = fopen("tempR.txt", "r+");						// for just extracting the hexa number 
				fprintf(fp2, "%s", addr);
				rewind(fp2);
				fscanf(fp2, "%x", &hexaddr);
				fclose(fp2);                                                 
				
				i=9;
				
				while (line[i]!='\0')
				{
					printf("%x \t %c%c\n", hexaddr+start_hexaddr, line[i], line[i+1]);
					hexaddr++;
					i=i+2;
					}            
				                        
			}
		} while (!feof(fp1));
		fclose(fp1);
		
		return 0;
	}
