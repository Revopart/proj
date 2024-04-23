#include <stdio.h>
#include <string.h>

#include "log_levels.h"
#include "logger.h"

int Original_key[64] = {0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1,
                        1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1,
                        1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1};

int Permutated_Choice1[56] = {57, 49, 41, 13, 25, 18, 9,  1,  58, 50, 42, 34, 26, 18, 10, 2,  59, 51, 43,
                              35, 27, 19, 11, 2,  60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7,  62, 54,
                              46, 38, 30, 12, 14, 6,  61, 53, 45, 37, 29, 21, 13, 5,  28, 20, 12, 4};

int Permutated_Choice2[48] = {14, 17, 12, 24, 1,  5,  3,  28, 15, 6,  21, 10, 23, 19, 12, 4,
                              26, 8,  16, 7,  27, 20, 13, 2,  41, 52, 31, 37, 47, 55, 30, 40,
                              51, 45, 13, 48, 47, 46, 39, 13, 34, 53, 46, 42, 50, 36, 29, 32};

int Iintial_Permutation[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
                               62, 54, 46, 38, 30, 24, 13, 6, 64, 56, 48, 40, 32, 24, 16, 8,
                               57, 49, 41, 33, 25, 17, 9,  2, 59, 51, 43, 35, 27, 19, 11, 3,
                               61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

int Final_Permutation[] = {40, 8, 48, 16, 56, 24, 63, 32, 39, 7, 47, 15, 55, 23, 63, 31,
                           38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
                           36, 4, 44, 12, 52, 20, 61, 28, 35, 3, 43, 11, 51, 19, 59, 27,
                           34, 2, 42, 10, 50, 18, 18, 26, 33, 1, 41, 9,  49, 17, 57, 25};

int P[] = {16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 13, 26, 5,  18, 31, 10,
           2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25};

int E[] = {32, 1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,  8,  9,  10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

int S1[4][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                 {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                 {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                 {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}};

int S2[4][16] = {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                 {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                 {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                 {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}};

int S3[4][16] = {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}};

int S4[4][16] = {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}};

int S5[4][16] = {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}};

int S6[4][16] = {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}};

int S7[4][16] = {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}};

int S8[4][16] = {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}};

int shifts_for_each_round[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
int _56bit_key[56];
int _48bit_key[17][48];
int text_to_bits[99999], bits_size = 0;
int Left32[17][32], Right32[17][32];
int EXPtext[48];
int XORtext[48];
int X[8][6];
int X2[32];
int R[32];
int chiper_text[64];
int encrypted_text[64];

int XOR(int a, int b) { return (a ^ b); }

void Dec_to_Binary(int n) {
    int binaryNum[1000];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--) {
        text_to_bits[bits_size++] = binaryNum[j];
    }
}

int F1(int i) {
    int r, c, b[6];
    for (int j = 0; j < 6; j++) b[j] = X[i][j];

    r = b[0] * 2 + b[5];
    c = 8 * b[1] + 4 * b[2] + 2 * b[3] + b[4];
    if (i == 0)
        return S1[r][c];
    else if (i == 1)
        return S2[r][c];
    else if (i == 2)
        return S3[r][c];
    else if (i == 3)
        return S4[r][c];
    else if (i == 4)
        return S5[r][c];
    else if (i == 5)
        return S6[r][c];
    else if (i == 6)
        return S7[r][c];
    else if (i == 7)
        return S8[r][c];
    return 0;
}

void PBox(int pos, int bit) {
    int i;
    for (i = 0; i < 32; i++)
        if (P[i] == pos + 1) break;
    R[i] = bit;
}

void ToBits(int value) {
    int k, j, m;
    static int i;
    if (i % 32 == 0) i = 0;
    for (j = 3; j >= 0; j--) {
        m = 1 << j;
        k = value & m;
        if (k == 0)
            X2[3 - j + i] = '0' - 48;
        else
            X2[3 - j + i] = '1' - 48;
    }
    i = i + 4;
}

void SBox(int XORtext[]) {
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 6; j++) X[i][j] = XORtext[k++];

    int value;
    for (int i = 0; i < 8; i++) {
        value = F1(i);
        ToBits(value);
    }
}

void expansion_function(int pos, int bit) {
    for (int i = 0; i < 48; i++)
        if (E[i] == pos + 1) EXPtext[i] = bit;
}

void cipher(int Round, int mode) {
    for (int i = 0; i < 32; i++) expansion_function(i, Right32[Round - 1][i]);

    for (int i = 0; i < 48; i++) {
        if (mode == 0)
            XORtext[i] = XOR(EXPtext[i], _48bit_key[Round][i]);
        else
            XORtext[i] = XOR(EXPtext[i], _48bit_key[17 - Round][i]);
    }

    SBox(XORtext);

    for (int i = 0; i < 32; i++) PBox(i, X2[i]);
    for (int i = 0; i < 32; i++) Right32[Round][i] = XOR(Left32[Round - 1][i], R[i]);
}

void finalPermutation(int pos, int bit) {
    int i;
    for (i = 0; i < 64; i++)
        if (Final_Permutation[i] == pos + 1) break;
    encrypted_text[i] = bit;
}

void Encrypt_each_64_bit(int plain_bits[], FILE *temp_f) {
    int IP_result[64];
    for (int i = 0; i < 64; i++) {
        IP_result[i] = plain_bits[Iintial_Permutation[i]];
    }
    for (int i = 0; i < 32; i++) Left32[0][i] = IP_result[i];
    for (int i = 32; i < 64; i++) Right32[0][i - 32] = IP_result[i];

    for (int k = 1; k < 17; k++) {
        cipher(k, 0);

        for (int i = 0; i < 32; i++) Left32[k][i] = Right32[k - 1][i];
    }

    for (int i = 0; i < 64; i++) {
        if (i < 32)
            chiper_text[i] = Right32[16][i];
        else
            chiper_text[i] = Left32[16][i - 32];
        finalPermutation(i, chiper_text[i]);
    }

    for (int i = 0; i < 64; i++) fputc((char)encrypted_text[i] - 'a', temp_f);
}

void convert_Text_to_bits(char *plain_text) {
    for (int i = 0; plain_text[i]; i++) {
        int asci = plain_text[i];
        Dec_to_Binary(asci);
    }
}

void key56to48(int round, int pos, int bit) {
    int i;
    for (i = 0; i < 56; i++)
        if (Permutated_Choice2[i] == pos + 1) break;
    _48bit_key[round][i] = bit;
}

void key64to56(int pos, int bit) {
    int i;
    for (i = 0; i < 56; i++)
        if (Permutated_Choice1[i] == pos + 1) break;
    _56bit_key[i] = bit;
}

void key64to48(int key[]) {
    int k, backup[17][2];
    int CD[17][56];
    int C[17][28], D[17][28];

    for (int i = 0; i < 64; i++) key64to56(i, key[i]);

    for (int i = 0; i < 56; i++)
        if (i < 28)
            C[0][i] = _56bit_key[i];
        else
            D[0][i - 28] = _56bit_key[i];

    for (int x = 1; x < 17; x++) {
        int shift = shifts_for_each_round[x - 1];

        for (int i = 0; i < shift; i++) backup[x - 1][i] = C[x - 1][i];
        for (int i = 0; i < (28 - shift); i++) C[x][i] = C[x - 1][i + shift];
        k = 0;
        for (int i = 28 - shift; i < 28; i++) C[x][i] = backup[x - 1][k++];

        for (int i = 0; i < shift; i++) backup[x - 1][i] = D[x - 1][i];
        for (int i = 0; i < (28 - shift); i++) D[x][i] = D[x - 1][i + shift];
        k = 0;
        for (int i = 28 - shift; i < 28; i++) D[x][i] = backup[x - 1][k++];
    }

    for (int j = 0; j < 17; j++) {
        for (int i = 0; i < 28; i++) CD[j][i] = C[j][i];
        for (int i = 28; i < 56; i++) CD[j][i] = D[j][i - 28];
    }

    for (int j = 1; j < 17; j++)
        for (int i = 0; i < 56; i++) key56to48(j, i, CD[j][i]);
}

void read_file(char *name, FILE *log_file) {
    FILE *f = NULL;

    char ch;
    f = fopen(name, "r");
    if (f != NULL) {
        if ((ch = fgetc(f)) != EOF) {
            printf("%c", ch);
            while (((ch = fgetc(f)) != EOF) && log_file != NULL) {
                printf("%c", ch);
            }
            printf("\n");
            char r[256] = "File read ";
            strcat(r, name);
#ifdef DOP
            logcat(log_file, r, "[info]");
#endif
        } else {
#ifdef DOP
            logcat(log_file, "file empty", "[error]");
#endif
            printf("n/a\n");
        }
    } else {
#ifdef DOP
        logcat(log_file, "file doesnt exist", "[error]");
#endif
        printf("n/a\n");
    }
    fclose(f);
}

void write_file(char *name, FILE *log_file) {
    FILE *f = NULL;
    char str[512];
    scanf("%s", str);
    f = fopen(name, "r");
    if (f != NULL && log_file != NULL) {
        f = fopen(name, "a");
        fputs(str, f);
        fclose(f);
        char r[256] = "File write ";
        strcat(r, name);
#ifdef DOP
        logcat(log_file, r, "[info]");
#endif
    } else {
#ifdef DOP
        logcat(log_file, "file doesnt exist", "[error]");
#endif
        printf("n/a\n");
    }
    read_file(name, log_file);
}

void encode(FILE *log_file) {
    int step;
#ifdef DOP
    logcat(log_file, "caesar encode", "[info]");
#endif
    if (scanf("%d", &step) == 1 && log_file != NULL) {
        if (step < 0) {
            step = step % 26 + 26;
        } else {
            step = step % 26;
        }
        char *files_list[4] = {"../src/ai_modules/m1.c", "../src/ai_modules/m2.c", "../src/ai_modules/m1.h",
                               "../src/ai_modules/m2.h"};
        for (int i = 0; i < 4; i++) {
            char *now = files_list[i];
            char *temp = "temp1.txt";
            char ch;
            if (strstr(now, ".c") != NULL) {
                FILE *temp_f, *now_f;
                temp_f = fopen(temp, "a");
                now_f = fopen(now, "r");
                while ((ch = fgetc(now_f)) != EOF) {
                    if (ch >= 'A' && ch <= 'Z') {
                        ch = (ch + step) - ('Z' + 1 - 'A') * ((ch + step - 1) / 'Z');
                    } else if (ch >= 'a' && ch <= 'z') {
                        ch = (ch + step) - ('z' + 1 - 'a') * ((ch + step - 1) / 'z');
                    }
                    putc(ch, temp_f);
                }
                fclose(now_f);
                fclose(temp_f);
                temp_f = fopen(temp, "r");
                now_f = fopen(now, "w");
                while ((ch = fgetc(temp_f)) != EOF) {
                    putc(ch, now_f);
                }
                fclose(now_f);
                fclose(temp_f);
                remove(temp);
            } else if (strstr(now, ".h") != NULL) {
                FILE *f;
                f = fopen(now, "w");
                fclose(f);
            }
        }

    } else {
        printf("n/a\n");
    }
}

void encode_dse(FILE *log_file) {
#ifdef DOP
    logcat(log_file, "dse encode", "[info]");
#endif
    char *files_list[4] = {"../src/ai_modules/m1.c", "../src/ai_modules/m2.c", "../src/ai_modules/m1.h",
                           "../src/ai_modules/m2.h"};
    for (int i = 0; i < 4; i++) {
        char *now = files_list[i];
        char *temp = "temp1.txt";
        char ch[50];
        char cha;
        if (strstr(now, ".c") != NULL && log_file != NULL) {
            FILE *temp_f, *now_f;
            temp_f = fopen(temp, "a");
            now_f = fopen(now, "r");
            while ((fgets(ch, 50, now_f)) != NULL) {
                convert_Text_to_bits(ch);
                key64to48(Original_key);
                int _64bit_sets = bits_size / 64;
                for (int i = 0; i <= _64bit_sets; i++) {
                    Encrypt_each_64_bit(text_to_bits + 64 * i, temp_f);
                }
            }
            fclose(now_f);
            fclose(temp_f);
            temp_f = fopen(temp, "r");
            now_f = fopen(now, "w");
            while ((cha = fgetc(temp_f)) != EOF) {
                putc(cha, now_f);
            }
            fclose(now_f);
            fclose(temp_f);
            remove(temp);
        } else if (strstr(now, ".h") != NULL) {
            FILE *f;
            f = fopen(now, "w");
            fclose(f);
        }
    }
}

int main() {
    int choise = 0;
    char name[255];
    FILE *log_file;
#ifdef DOP
    log_file = log_init("log.txt");
#endif

    while (choise != -1) {
        if (scanf("%d", &choise) == 1) {
            if (choise == 1) {
#ifndef DOP
                log_file = fopen(name, "r");
#endif
                scanf("%s", name);
                read_file(name, log_file);
            } else if (choise == 2) {
                write_file(name, log_file);
            } else if (choise == 3) {
                encode(log_file);
            } else if (choise == 4) {
                encode_dse(log_file);
            } else if (choise != -1) {
                printf("n/a\n");
            }
        } else {
            printf("n/a");
        }
    }
#ifdef DOP
    log_close(log_file);
#endif
    return 0;
}
