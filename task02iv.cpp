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
    int i, ok = 1;

    /* Write text file */
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

    /* Read text file */
    fp = fopen("donors.txt", "r");
    if (fp == NULL) {
        perror("donors.txt");
        return 1;
    }

    for (i = 0; i < 10; i++)
        fscanf(fp, "%d %29s %3s %d",
               &textRead[i].id, textRead[i].name,
               textRead[i].group, &textRead[i].age);
    fclose(fp);

    /* Write binary file */
    fp = fopen("donors.dat", "wb");
    if (fp == NULL) {
        perror("donors.dat");
        return 1;
    }

    fwrite(donors, sizeof(Donor), 10, fp);
    fclose(fp);

    /* Read binary file */
    fp = fopen("donors.dat", "rb");
    if (fp == NULL) {
        perror("donors.dat");
        return 1;
    }

    fread(binaryRead, sizeof(Donor), 10, fp);
    fclose(fp);

    /* Verify records */
    for (i = 0; i < 10; i++) {
        if (memcmp(&donors[i], &textRead[i], sizeof(Donor)) != 0 ||
            memcmp(&donors[i], &binaryRead[i], sizeof(Donor)) != 0) {
            ok = 0;
            break;
        }
    }

    if (ok)
        printf("Text and binary records verified successfully.\n");
    else
        printf("Data verification failed.\n");

    return 0;
}