#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE*in = fopen("input.txt", "r"), *op= fopen("optab.txt", "r"), *st = fopen("symtab.txt", "w"), *im= fopen("intermediate.txt", "w");
	char lbl[20], opc[20], opr[20], c[20], m[20];
	int lc = 0, start=0;
	
	fscanf(in, "%s %s %s", lbl, opc, opr);
	if(!strcmp(opc, "START"))
		{
			start= atoi(opr); lc = start;
			fprintf(im, "%d\t%s\t%s\t%s\n", lc, lbl, opc, opr);
			fscanf(in, "%s %s %s", lbl, opc, opr);
			}
			
			while(strcmp(opc, "END"))
			{
				fprintf(im, "%d\t%s\t%s\t%s\n", lc, lbl, opc, opr);
				if (strcmp(lbl, "**")) fprintf (st, "%s\t%d\n", lbl, lc);
				int f=0; rewind(op);
				while (fscanf(op, "%s %s",c,m ) != EOF) if (!strcmp(opc, c)){lc+=3; f=1;break;}
				
				if(!f)
				{
					if(!strcmp(opc, "WORD")) lc+=3;
					else if (!strcmp(opc, "RESW")) lc+=3*atoi(opr);
					else if (!strcmp(opc, "RESB")) lc+=atoi(opr);
					else if (!strcmp(opc, "BYTE")) lc+=(opr[0]=='C')?strlen(opr)-3: (strlen(opr)-2)/2;
					else printf("Invalid opcode: %s\n", opc);
					}
				fscanf(in, "%s %s %s", lbl, opc, opr);
				}
				fprintf(im, "%d\t%s\t%s\t%s\t\n", lc, lbl, opc, opr);
				printf("Program length= %d\n", lc-start);
				fclose(in);fclose(op);fclose(st);fclose(im);
	}
