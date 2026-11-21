#include <stdio.h>
#include <string.h>

int main(void)
{
    char name1[20];
    char name2[20];

    
    printf("Enter donor name for scanf: ");

  
       
    if (scanf("%19s", name1) != 1)
    {
        printf("Input error\n");
        return 1;
    }

    printf("Name using scanf: %s\n", name1);

    
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }

    printf("Enter donor name for fgets: ");

    if (fgets(name2, sizeof(name2), stdin) == NULL)
    {
        printf("Input error\n");
        return 1;
    }

    if (strchr(name2, '\n') == NULL)
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        printf("Name is too long and was truncated.\n");
    }

    name2[strcspn(name2, "\n")] = '\0';

    printf("Name using fgets: %s\n", name2);

    return 0;
}