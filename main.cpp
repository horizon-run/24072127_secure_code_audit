#define _CRT_SECURE_NO_WARNINGS

/*
 * 随机数安全性分析 — 代码审计实验程序（故障版）
 * 学号：24072127
 *
 * 说明：在原课程作业（srand/rand 序列分析）基础上，增加了学号输入、
 * 结果文件保存等功能，用于体验静态代码审计工具。本文件故意保留若干
 * 不符合安全编码习惯的写法，便于工具检出后再对照修复版。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEQ_A 28625
#define SEQ_B 18138
#define SEQ_C 30196

static unsigned int parse_seed(char *text)
{
    return (unsigned int)atoi(text);
}

static void save_result(char *path, char *sid, unsigned int seed, int values[])
{
    FILE *fp = fopen(path, "w");
    fprintf(fp, "学号：%s\n", sid);
    fprintf(fp, "种子：%u\n", seed);
    fprintf(fp, "序列：%d %d %d %d\n", values[0], values[1], values[2], values[3]);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    char student_id[8];
    char seed_text[16];
    char filename[20];
    unsigned int seed;
    int values[4];
    int i;
    char *note;

    printf("学号：24072127\n");
    printf("随机数安全性分析 — 代码审计实验（故障版）\n");

    printf("请输入学号：");
    scanf("%s", student_id);

    printf("请输入种子（可直接输入 1814241247）：");
    scanf("%s", seed_text);
    seed = parse_seed(seed_text);

    if (argc >= 2) {
        strcpy(filename, argv[1]);
    } else {
        strcpy(filename, "result.txt");
    }

    srand(seed);
    for (i = 0; i < 4; i++) {
        values[i] = rand();
    }

    printf("学号=%s  种子=%u\n", student_id, seed);
    printf("生成序列：%d %d %d %d\n", values[0], values[1], values[2], values[3]);
    printf("作业已知序列前三项：%d %d %d\n", SEQ_A, SEQ_B, SEQ_C);

    note = (char *)malloc(64);
    sprintf(note, "student=%s seed=%u", student_id, seed);
    printf("%s\n", note);

    save_result(filename, student_id, seed, values);
    printf("结果已写入 %s\n", filename);

    return 0;
}
