#include <stdio.h>

typedef struct {
    int group_code;
    int units;
} Stock;

/* Updates one record directly in the binary file. */
int update_units(FILE *fp, int index, int units)
{
    Stock s;

    if (fp == NULL || index < 0)
        return 0;

    /* Move to the required record */
    if (fseek(fp, (long)index * sizeof(Stock), SEEK_SET) != 0)
        return 0;

    /* Read the existing record */
    if (fread(&s, sizeof(Stock), 1, fp) != 1)
        return 0;

    /* Change the units */
    s.units = units;

    /* Move back to the same record */
    if (fseek(fp, -(long)sizeof(Stock), SEEK_CUR) != 0)
        return 0;

    /* Write the updated record */
    if (fwrite(&s, sizeof(Stock), 1, fp) != 1)
        return 0;

    return 1;
}

int main(void)
{
    FILE *fp = tmpfile();

    if (fp == NULL) {
        perror("tmpfile");
        return 1;
    }

    Stock initial[5] = {
        {1, 40}, {2, 25}, {3, 12},
        {4, 8}, {5, 30}
    };

    if (fwrite(initial, sizeof(Stock), 5, fp) != 5) {
        perror("fwrite");
        fclose(fp);
        return 1;
    }

    printf("update record 3: %s\n",
           update_units(fp, 3, 20) ? "done" : "failed");

    printf("update record 9: %s\n",
           update_units(fp, 9, 20) ? "done" : "failed");

    rewind(fp);

    Stock s;
    while (fread(&s, sizeof s, 1, fp) == 1)
        printf("%d:%d ", s.group_code, s.units);

    printf("\n");
    fclose(fp);

    return 0;
}