#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    FILE *f1, *f2, *f3, *f4, *f5;
    char label[30], opcode[30], operand[30], opcode1[30], operand1[30];
    int locctr, x = 0, startadd, length;
    f1 = fopen("inputprgm.txt", "r");
    f2 = fopen("optab.txt", "r");
    f3 = fopen("pass1out.txt", "w");
    f4 = fopen("symtab.txt", "w");
    f5 = fopen("length.txt", "w");

    while (fscanf(f1, "%s %s %s", label, opcode, operand) != EOF) {
        if (strcmp(label, "**") == 0) {
            if (strcmp(opcode, "START") == 0) {
                fprintf(f3, "%s %s %s", label, opcode, operand);
                locctr = (int)strtol(operand, NULL, 16);
                startadd = locctr;
            }
            else if (strcmp(opcode, "END") == 0) {
                fprintf(f3, "\n%X %s %s %s", locctr, label, opcode, operand);
                length = locctr - startadd;
                fprintf(f5,"%X",length);
            }
            else {
                rewind(f2);
                x = 0;
                while (fscanf(f2, "%s%s", opcode1, operand1) != EOF) {
                    if (strcmp(opcode, opcode1) == 0) {
                        x = 1;
                    }
                }
                if (x == 1) {
                    fprintf(f3, "\n%X %s %s %s", locctr, label, opcode, operand);
                    locctr += 0x03;
                }
            }
        } 
        else {
            if (strcmp(opcode, "RESW") == 0) {
                fprintf(f3, "\n%X %s %s %s", locctr, label, opcode, operand);
                fprintf(f4, "%X %s\n", locctr, label);
                locctr += 0x03 * atoi(operand);
            } else if (strcmp(opcode, "WORD") == 0) {
                fprintf(f3, "\n%X %s %s %s", locctr, label, opcode, operand);
                fprintf(f4, "%X %s\n", locctr, label);
                locctr += 0x03;
            } else if (strcmp(opcode, "BYTE") == 0) {
                fprintf(f3, "\n%X %s %s %s", locctr, label, opcode, operand);
                fprintf(f4, "%X %s\n", locctr, label);
                locctr += 0x01;
            } else if (strcmp(opcode, "RESB") == 0) {
                fprintf(f3, "\n%X %s %s %s", locctr, label, opcode, operand);
                fprintf(f4, "%X %s\n", locctr, label);
                locctr += 0x01 * atoi(operand);
            }
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
}
