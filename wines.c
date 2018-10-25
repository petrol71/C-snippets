// Implement a winelist program in C that has following features:
// The user can add wines to be drinked
// The user can remove any wine from the list by checking it as drinked
// The user can print out the wines to be drinked onto the screen
// The winelist must not be static.
//
//  Created by Petri Ollonen on 02/11/2017.
//  Copyright © 2017 Petri Ollonen. All rights reserved.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define FALSE 0
#define TRUE  1
#define SIZE  32+1

typedef struct Node
{
    char *data;
    struct Node *next;
} Node;

/*Function prototypes*/
int fileCheck(const char *fileName);
size_t stringInput(char *buffer);
int insertNewNode(Node **head, char *buffer, size_t dataSize);
int deleteNode(Node **head, char *wine);
void deleteList(Node *head);
void printWines(Node *head);

int main(void)
{
    char buf[SIZE];
    char userChoice;
    char *fName = "winelist.txt";
    
    int success = 0;
    
    size_t dataArraySize = 0;
    
    Node *head = NULL;
    Node *ptr = NULL; 
    
    FILE *f;
    
    printf("This program lists wines to be drinked.\n");
    printf("\nValid user choices of action :\n");
    printf("\t\'a\' - Add a wine to be drinked\n");
    printf("\t\'d\' - Delete the drinked wine\n");
    printf("\t\'p\' - Print the list of wines to be drinked\n");
    printf("\t\'e\' - Exit the program\n");
    
    if(fileCheck(fName))
    {
        f = fopen("winelist.txt", "r");
        printf("\nThe wines to be drinked:\n");
        while(fgets(buf, SIZE, f) != NULL)
        {
            printf("%s", buf);
            dataArraySize = strlen(buf);
            success = insertNewNode(&head, buf, dataArraySize);
            if(success == FALSE)
            {
                printf("Something went wrong - new wine was not added due to memory allocation failure");
                deleteList(head);
                fclose(f);

                return -1;
            }
        }
        fclose(f);
    }

    for(;;)
    {
        printf("\nPlease give your choice of action (\'a\', \'d\', \'p\' or \'e\'): ");
        userChoice = getchar();
        while (getchar() != '\n');
        
        switch(userChoice)
        {
            case 'a':
                printf("\nEnter a name of the new Wine to be drinked:\n");
                dataArraySize = stringInput(buf);
                success = insertNewNode(&head, buf, dataArraySize);
                if(success == FALSE)
                {
                    printf("Something went wrong - new wine was not added due to memory allocation failure");
                    deleteList(head);
                    return -1;
                }
                f = fopen("winelist.txt", "a");
                fprintf(f, "%s", buf);
                fclose(f);
                break;
            case 'd':
                printf("\nEnter the drinked wine to be removed from the list:\n");
                dataArraySize = stringInput(buf);
                success = deleteNode(&head, buf);
                if(success)
                {
                    ptr = head;
                    f = fopen("winelist.txt", "w");
                    while (ptr != NULL)
                    {
                        fprintf(f, "%s", ptr->data);
                        ptr = ptr->next;
                    }
                    fclose(f);
                }
                else
                    printf("\nThe wine was not found from the list!\n");
                break;
            case 'p':
                if(head == NULL)
                    printf("The wine list is empty\n");
                else
                    printWines(head);
                break;
            case 'e':
                deleteList(head);
                return 0;
            default:
                printf("\nNot a valid choice of action!\n");
                while (getchar() != '\n')
                    ;
                break;
        }
    }
}

int fileCheck(const char *fileName)
{
    int file;

    if(!access(fileName, F_OK ))
        file = TRUE;
    else
    {
        printf("\nThe wine list is empty\n");
        file = FALSE;
    }

    return file;
}

size_t stringInput(char *buffer)
{
    size_t arraySize;

    fgets(buffer, SIZE, stdin);
    while (getchar() != '\n')
        ;
    arraySize = strlen(buffer);
    if(arraySize == SIZE-1)
        buffer[SIZE-2] = '\n';

    return arraySize;
}

int insertNewNode(Node **head, char *buffer, size_t dataSize)
{
    char *ptr = buffer;

    Node *newNode = (Node *) malloc(sizeof(Node));
    if(!newNode)
        return FALSE;
    
    newNode->data = (char *) malloc(sizeof(char) * dataSize + 1);
    if(!(newNode->data))
        return FALSE;
    
    strcpy(newNode->data, ptr);
    newNode->next = *head;
    *head = newNode;
    
    return TRUE;
}

int deleteNode(Node **head, char *wine)
{
    Node *temp = *head;
    Node *prev = NULL;
    
    // If first node to be deleted
    if (temp != NULL && (strcmp(temp->data, wine) == 0))
    {
        *head = temp->next;
        free(temp->data);
        free(temp);
        
        return TRUE;
    }
    
    // Search for the node to be deleted keeping track
    while (temp != NULL && !(strcmp(temp->data, wine) == 0))
    {
        prev = temp;
        temp = temp->next;
    }
    
    // If node not present in linked list
    if (temp == NULL)
        return FALSE;
    
    // Unlink the node from linked list
    prev->next = temp->next;
    
    // Free memory
    free(temp->data);
    free(temp);
    
    return TRUE;
}

void deleteList(Node *head)
{
    Node *ptr = head;
    Node *tmp;

    while (ptr != NULL)
    {
        tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
    head = NULL;
}

// This function prints contents of the linked list
void printWines(Node *p)
{
    printf("\nThe wines to be drinked:\n");
    while (p != NULL)
    {
        printf("%s", p->data);
        p = p->next;
    }
}