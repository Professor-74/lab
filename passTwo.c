#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *im = fopen("intermediate2.txt", "r");
    FILE *st = fopen("symtab2.txt", "r");
    FILE *op = fopen("optab2.txt", "r");
    FILE *out = fopen("output2.txt", "w");

    if (!im || !st || !op || !out) {
        printf("Error opening one or more files.\n");
        return 1;
    }

    char lbl[20], opc[20], opr[20], code[20], mnemonic[20], symLbl[20];
    char rec[80], obj[80], last[100];
    int loc, start = 0, len = 0, recStart, sym, found, i, progLen;

    fscanf(im, "%x %s %s %s", &loc, lbl, opc, opr);
    if (!strcmp(opc, "START"))
        start = strtol(opr, NULL, 16);

    // find last line to get program length
    while (fgets(last, 100, im))
        ; // read till end

    sscanf(last, "%x", &progLen);
    progLen -= start;

    rewind(im);
    fscanf(im, "%x %s %s %s", &loc, lbl, opc, opr);
    fprintf(out, "H^%-6s^%06X^%06X\n", lbl, start, progLen);

    recStart = start;
    rec[0] = '\0';

    fscanf(im, "%x %s %s %s", &loc, lbl, opc, opr);
    while (strcmp(opc, "END")) {
        obj[0] = '\0';
        found = 0;
        rewind(op);

        while (fscanf(op, "%s %s", code, mnemonic) != EOF) {
            if (!strcmp(opc, code)) {
                found = 1;
                rewind(st);
                while (fscanf(st, "%s %x", symLbl, &sym) != EOF) {
                    if (!strcmp(opr, symLbl)) {
                        sprintf(obj, "%s%04X", mnemonic, sym);
                        break;
                    }
                }
                break;
            }
        }

        if (!found) {
            if (!strcmp(opc, "WORD")) {
                sprintf(obj, "%06X", atoi(opr));
            } else if (!strcmp(opc, "BYTE")) {
                if (opr[0] == 'C') {
                    for (i = 2; i < strlen(opr) - 1; i++) {
                        char t[3];
                        sprintf(t, "%X", opr[i]);
                        strcat(obj, t);
                    }
                } else if (opr[0] == 'X') {
                    for (i = 2; i < strlen(opr) - 1; i++) {
                        char t[2] = {opr[i], 0};
                        strcat(obj, t);
                    }
                }
            }
        }

        if (strlen(obj)) {
            if (len + strlen(obj) > 60 || !strcmp(opc, "RESW") || !strcmp(opc, "RESB")) {
                if (len)
                    fprintf(out, "T^%06X^%02X%s\n", recStart, len / 2, rec);
                rec[0] = '\0';
                len = 0;
            }

            if (!len)
                recStart = loc;

            strcat(rec, "^");
            strcat(rec, obj);
            len += strlen(obj);
        } else if (!strcmp(opc, "RESW") || !strcmp(opc, "RESB")) {
            if (len)
                fprintf(out, "T^%06X^%02X%s\n", recStart, len / 2, rec);
            rec[0] = '\0';
            len = 0;
        }

        fscanf(im, "%x %s %s %s", &loc, lbl, opc, opr);
    }

    if (len)
        fprintf(out, "T^%06X^%02X%s\n", recStart, len / 2, rec);

    fprintf(out, "E^%06X\n", start);

    fclose(im);
    fclose(st);
    fclose(op);
    fclose(out);

    printf("Pass 2 completed. Object code in output2.txt\n");
    return 0;
}

