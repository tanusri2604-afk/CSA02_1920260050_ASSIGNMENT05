#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    char group[4];
    int age;
} Donor;

int main(void)
{
    Donor donors[10] = {
        {1001, "Arun", "O+", 25},
        {1002, "Bala", "A+", 30},
        {1003, "Charan", "B+", 28},
        {1004, "Divya", "AB+", 22},
        {1005, "Ezhil", "O-", 35},
        {1006, "Farah", "A-", 26},
        {1007, "Gokul", "B-", 31},
        {1008, "Hari", "AB-", 24},
        {1009, "Indu", "O+", 29},
        {1010, "Jaya", "A+", 27}
    };

    Donor textRead[10], binaryRead[10];
    FILE *fp;
    int i, valid = 1;

    fp = fopen("donors.txt", "w");
    if (fp == NULL) {
        perror("donors.txt");
        return 1;
    }

    for (i = 0; i < 10; i++)
        fprintf(fp, "%d %s %s %d\n",
                donors[i].id, donors[i].name,
                donors[i].group, donors[i].age);
    fclose(fp);

    fp = fopen("donors.txt", "r");
    if (fp == NULL) {
        perror("donors.txt");
        return 1;
    }

    for (i = 0; i < 10; i++) {
        if (fscanf(fp, "%d %29s %3s %d",
                   &textRead[i].id, textRead[i].name,
                   textRead[i].group, &textRead[i].age) != 4) {
            valid = 0;
            break;
        }
    }
    fclose(fp);

    fp = fopen("donors.dat", "wb");
    if (fp == NULL) {
        perror("donors.dat");
        return 1;
    }

    if (fwrite(donors, sizeof(Donor), 10, fp) != 10)
        valid = 0;
    fclose(fp);

    fp = fopen("donors.dat", "rb");
    if (fp == NULL) {
        perror("donors.dat");
        return 1;
    }

    if (fread(binaryRead, sizeof(Donor), 10, fp) != 10)
        valid = 0;
    fclose(fp);

    for (i = 0; i < 10 && valid; i++) {
        if (donors[i].id != textRead[i].id ||
            strcmp(donors[i].name, textRead[i].name) != 0 ||
            strcmp(donors[i].group, textRead[i].group) != 0 ||
            donors[i].age != textRead[i].age ||
            donors[i].id != binaryRead[i].id ||
            strcmp(donors[i].name, binaryRead[i].name) != 0 ||
            strcmp(donors[i].group, binaryRead[i].group) != 0 ||
            donors[i].age != binaryRead[i].age) {
            valid = 0;
        }
    }

    if (valid)
        printf("Text and binary records verified successfully.\n");
    else
        printf("Data verification failed.\n");

    return 0;
}