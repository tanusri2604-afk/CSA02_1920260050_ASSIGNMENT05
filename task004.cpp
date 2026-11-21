#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    char group[4];
    int age;
} Donor;

/* Add a donor using dynamic memory allocation */
int add_donor(Donor **list, int *count, int *capacity,
              Donor newDonor)
{
    if (*count == *capacity) {
        int newCapacity = (*capacity == 0) ? 2 : (*capacity * 2);

        Donor *temp = realloc(*list,newCapacity * sizeof(Donor));

        if (temp == NULL) {
            return 0;
        }

        *list = temp;
        *capacity = newCapacity;
    }

    (*list)[*count] = newDonor;
    (*count)++;

    return 1;
}

int main(void)
{
    Donor *list = NULL;
    int count = 0, capacity = 0;
    FILE *fp;
    Donor d;

    fp = fopen("donors.txt", "r");

    if (fp == NULL) {
        perror("donors.txt");
        return 1;
    }

    while (fscanf(fp, "%d %29s %3s %d",
                  &d.id, d.name, d.group, &d.age) == 4) {

        if (!add_donor(&list, &count, &capacity, d)) {
            printf("Memory allocation failed.\n");
            fclose(fp);
            free(list);
            return 1;
        }
    }

    fclose(fp);

    printf("Total donors loaded: %d\n", count);
    printf("Allocated capacity: %d\n", capacity);

    printf("\nDonor Details:\n");

    for (int i = 0; i < count; i++) {
        printf("%d %s %s %d\n",
               list[i].id,
               list[i].name,
               list[i].group,
               list[i].age);
    }

    free(list);
    list = NULL;

    return 0;
}