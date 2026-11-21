#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int valid_group(char group[])
{
    char *groups[] =
    {
        "A+", "A-", "B+", "B-",
        "AB+", "AB-", "O+", "O-"
    };

    for (int i = 0; i < 8; i++)
    {
        if (strcmp(group, groups[i]) == 0)
            return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error: No command entered.\n");
        printf("Usage: ./B2 find O+\n");
        return 1;
    }

    if (strcmp(argv[1], "find") == 0)
    {
        if (argc != 3)
        {
            printf("Error: Incorrect number of arguments.\n");
            return 1;
        }

        if (!valid_group(argv[2]))
        {
            printf("Error: Invalid blood group.\n");
            return 1;
        }

        printf("Searching donors with blood group %s\n",
               argv[2]);
    }
    else
    {
        printf("Error: Unknown command.\n");
        return 1;
    }

    return 0;
}