#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    char opcode[20], operand[20], symbol[20], label[20], code[20], mnemonic[25], character, add[20], objectcode[20];
    int flag, flag1, locctr, loc;
    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("pass1out.txt", "r");
    fp2 = fopen("pass2out.txt", "w");
    fp3 = fopen("optab.txt", "r");
    fp4 = fopen("symtab.txt", "r");
    
    fscanf(fp1, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        locctr = (int)strtol(operand, NULL, 16);
        fprintf(fp2, "%s\t%s\t%s\n", label, opcode);
        fscanf(fp1, "%X %s %s %s", &locctr, label, opcode, operand);
    }

    while (strcmp(opcode, "END") != 0) {
        flag = 0;
        rewind(fp3);
        fscanf(fp3, "%s %s", code, mnemonic);

        while (strcmp(code, "END") != 0) {
            if ((strcmp(opcode, code) == 0) && (strcmp(mnemonic, "*") != 0)) {
                flag = 1;
                break;
            }
            fscanf(fp3, "%s %s", code, mnemonic);
        }

        if (flag == 1) {
            flag1 = 0;
            rewind(fp4);

            while (fscanf(fp4, "%X %s", &loc, symbol) != EOF) {
                if (strcmp(symbol, operand) == 0) {
                    flag1 = 1;
                    break;
                }
            }

            if (flag1 == 1) {
                sprintf(add, "%04X", loc);
                strcpy(objectcode, strcat(mnemonic, add));
            } else {
                strcpy(objectcode, "0000");
            }
        } 
        else if (strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "WORD") == 0) {
            if (operand[0] == 'C') {
                character = operand[2];
                sprintf(objectcode, "%06X", character);
            } 
            else if (operand[0] == 'X') {
                strncpy(objectcode, operand + 2, strlen(operand) - 3);
                objectcode[strlen(operand) - 3] = '\0';
            } 
            else {
                sprintf(objectcode, "%06X", atoi(operand));
            }
        } 
        else {
            strcpy(objectcode, "");
        }

        fprintf(fp2, "%s\t%s\t%s\t%04X\t%s\n", label, opcode, operand, locctr, objectcode);
        fscanf(fp1, "%X %s %s %s", &locctr, label, opcode, operand);
    }

    fprintf(fp2, "%s\t%s\t%s\t%04X\n", label, opcode, operand, locctr);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}