#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char title[100];
    char Author[100];
    char ISBN[20];
    int qnty;
}book ;

bool handleError(char *input, int valtyp)
{
    switch (valtyp)
    {
        case 1:
        {
            for(int i = 0; input[i] != '\0'; i++)
            {
                if(!isalpha(input[i])&&!isspace(input[i])&&!isalnum(input[i])&&input[i] !='-' )
                {
                    printf("Name. Please enter a valid name containing only alphabetic or alphanumeric characters, spaces, or hyphens:\n");
                    return true;
                }
            }
            return false;
        }
        case 2:
        {
             for(int i = 0; input[i] != '\0'; i++)
             {
                if(!isalpha(input[i])&&!isspace(input[i])&&(input[i]) != '.' &&input[i] !='-' )
                {
                    printf("Author's name. Please enter a valid name containing only alphabetic  characters, spaces, hyphens or dots:\n");
                    return true;
                }
             }
             return false;
        }
        case 3:
        {
            for(int i = 0; input[i] != '\0'; i++)
             {
                if (!isalnum(input[i]) && input[i] != '-')
                {
                    printf("ISBN Number. Please enter a valid ISNB containing only alphanumerics and hyphens :\n");
                    return true;
                }
             }
             return false;
        }
        case 4:
        {
            int quantity;
            if (sscanf(input, "%d", &quantity) == 1 && quantity >= 0) {
                return true;
            } else {
                printf("Invalid quantity. Please enter a non-negative quantity:\n");
                return false;
            }
        }
        default:
        {
            printf("Unknown validation error.\n");
            return false;
        }
    }

}
void addbook(book library[], int *nobk) 
{
    book data;
    int num;
    printf("please enter the number of books you want to entered :\n");
    scanf("%d",&num);
    getchar();
    char input[100];
    for(int i = 0; i < num ; i++)
    {
        printf("Please enter the name of the book you want to add:\n");
        do {
             fgets(input, sizeof(input), stdin);
        } while (handleError(input, 1));
        strcpy(data.title, input);
        memset(input, '\0', sizeof(input));

        printf("Please enter the author of the book you just added:\n");
        do {
             fgets(input, sizeof(input), stdin);
        } while (handleError(input, 2));
        strcpy(data.Author, input);
        memset(input, '\0', sizeof(input));

        printf("Please enter the ISBN code of the book you entered above:\n");
        do{
             fgets(input, sizeof(input), stdin);
        }while(handleError(input,3));
        strcpy(data.ISBN,input);
        memset(input, '\0', sizeof(input));

        printf("Please enter the quantity:\n");
        do{
            scanf("%s",input);
        }while(handleError(input,4));
        sscanf(input, "%d", &data.qnty);

        (*nobk)++;
    }
}
void removebook(book library[], int *nobk)
{
    book data;
    char input[100];
    printf("Please enter the name or Author's name or ISBN of the book you want to remove \n");
    scanf("%s",input);
    int delindex = -1;
    for (int i = 0; i < *nobk; i++)
    {
        if(strcasecmp(input,library[i].title) == 0 ||strcasecmp(input,library[i].Author) == 0 ||strcasecmp(input,library[i].ISBN) == 0 )
        {
            delindex = i;
        }
    }
    if (delindex != -1){
        for (int i = delindex; i < *nobk - 1; i++)
        {
            library[i] = library[i+1];
        }
        (*nobk)--;
        printf("The book has been removed successfully.\n");
    }
    else
    {
        printf("The book was not found in the library.\n");
    }
}

void searchbook(book library[], int *nobk)
{
    char input[100];
    int found = 0;

    do {
        printf("Please enter the name or Author's name or ISBN of the book you want to search:\n");
        scanf("%s", input);

        if (input[0] == '\0' || strcasecmp(input, "exit") == 0) 
        {
            break;
        }

        for (int i = 0; i < *nobk; i++)
        {
            if (strcasecmp(input, library[i].title) == 0) {
                printf("You have searched book title: \n", input);
                printf("Author's name: %s\n", library[i].Author);
                printf("ISBN: %s\n", library[i].ISBN);
                printf("No. of books: %d\n", library[i].qnty);
                found = 1;
                break;
            } else if (strcasecmp(input, library[i].Author) == 0)
            {
                printf("You have searched Author's name: %s\n", input);
                printf("Book's name: %s\n", library[i].title);
                printf("ISBN: %s\n", library[i].ISBN);
                printf("No. of books: %d\n", library[i].qnty);
                found = 1;
                break;
            } else if (strcasecmp(input, library[i].ISBN) == 0)
            {
                printf("You have searched ISBN: %s\n", input);
                printf("Author's name: %s\n", library[i].Author);
                printf("Book's name: %s\n", library[i].title);
                printf("No. of books: %d\n", library[i].qnty);
                found = 1;
                break;
            }
            else if(strcasecmp(input,"exit") == 0)
            {
                break;
            }
        }

        if (found == 0 )
        {
            printf("Sorry, the book with the given title, author's name, or ISBN was not found.If you want to exit please type (exit)\n");
        }
    } while (found == 0);
}
void displaybooks(book library[],int *nobk)
{
    printf("All the books now will be listed below with all the details");
    for(int i = 0; i < *nobk; i++)
    {
        printf("%d. %s\n",i,library[i].title);
        printf("    Author's name : %s\n",library[i].Author);
        printf("    ISBN : %s\n",library[i].ISBN);
        printf("    Quantity of books : %d\n",library[i].qnty);
    }
}
void saveLibrary(book library[], int *nobk)
{
    FILE *p;
    p = fopen("rec.txt","w");
    if (p == NULL) 
    {
        printf("Unable to create or open file.\n");
        return;
    }
    for (int i = 0; i < *nobk; i++) 
    {
        fprintf(p, "%s\n", library[i].title);
        fprintf(p, "%s\n", library[i].Author);
        fprintf(p, "%s\n", library[i].ISBN);
        fprintf(p, "%d\n", library[i].qnty);
    }
    fclose(p);
}
void loadLibrary( book library[], int *nobk)
{
    FILE *p;
    book data;
    p = fopen("rec.txt","r");
    if(p == NULL)
    {
        printf("Error, file cannot be opened \n");
        return;
    }
    *nobk = 0;
    while(!feof(p))
    {
        fscanf(p, "%s\n", data.title);
        fscanf(p, "%s\n", data.Author);
        fscanf(p, "%s\n", data.ISBN);
        fscanf(p, "%d\n", &data.qnty);
        (*nobk)++;
    }
    fclose(p);

}

int main()
{
    int nobk;
    book library[100];
    int chc;
    char c;

    loadLibrary(library, &nobk);
    do {
        printf("Library Management System\n");
        printf("1. Add Book\n");
        printf("2. Remove A Certain Book Book\n");
        printf("3. Search For A Specific Book\n");
        printf("4. Display All Books\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &chc);
        getchar();
         switch (chc)
        {
            case 1:
                addbook(library, &nobk);
                break;
            case 2:
                removebook(library, &nobk);
                break;
            case 3:
                searchbook(library, &nobk);
                break;
            case 4:
                displaybooks(library, &nobk);
                break;
            case 0:
                printf("Exiting... do you want to save (Y/N)\n");
                scanf("%c", &c);
                if (c == 'y' || c == 'Y')
                {
                    saveLibrary(library, &nobk);
                }
                printf("Thanks for using our Library Management System.\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (chc != 0);

    return 0;
}

