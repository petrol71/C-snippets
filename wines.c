// Implement a winelist program in C that has following features:
// The user can add wines to be drinked
// The user can remove any wine from the list by checking it as drinked
// The user can print out the wines to be drinked onto the screen
// The winelist must not be static.
//
//  Created by Petri Ollonen on 02/11/2017.
//  Copyright © 2017 Petri Ollonen. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1
#define SIZE  64

typedef struct Node
{
    char *data;
    struct Node *next;
} Node;

/*Function prototypes*/
int stringInput(char buffer[]);
int insertNewNode(Node **head, char *p, int dataSize);
int deleteNode(Node **head, char wine[]);
void printWines(struct Node *head);

int main(void)
{
    /*Normally Names of the wines should fit in this size of an array*/
    char buf[SIZE];
    char userChoice;
    char *ptr;
    
    int dataArraySize = 0;
    int success = 0;
    
    struct Node *head = NULL;
    
    printf("This program lists wines to be drinked.\n");
    printf("\nValid user choices of action :\n");
    printf("\t\'a\' - Add a wine to be drinked\n");
    printf("\t\'d\' - Delete the drinked wine\n");
    printf("\t\'p\' - Print the list of wines to be drinked\n");
    printf("\t\'e\' - Exit the program\n");
    
    for(;;)
    {
        printf("\nPlease give your choice of action (\'a\', \'d\', \'p\' or \'e\'): ");
        userChoice = getchar();
        
        switch(userChoice)
        {
            case 'a':
                printf("\nEnter a name of the new Wine to be drinked: ");
                getchar();
                dataArraySize = stringInput(buf);
                ptr = &buf[0];
                success = insertNewNode(&head, ptr, dataArraySize);
                if(success == FALSE)
                {
                    printf("Something went wrong - new wine was not added due to memory allocation failure");
                    return -1;
                }
                memset(buf, 0, SIZE);
                break;
            case 'd':
                printf("\nEnter the drinked wine to be removed from the list: ");
                getchar();
                
                stringInput(buf);
                
                success = deleteNode(&head, buf);
                if(success == FALSE)
                    printf("\nThe given wine was not found from the list!\n");
                break;
            case 'p':
                if(head == NULL)
                    printf("The wine list is empty\n");
                else
                    printWines(head);
                getchar();
                break;
            case 'e':
                return 0;
            default:
                printf("\nNot a valid choice of action!");
                getchar();
                break;
        }
    }
}

int stringInput(char buffer[])
{
    int c;
    int i = 0;
    
    while((c = getchar()) != '\n' && (i < SIZE) && (c != EOF))
    {
        buffer[i] = c;
        i++;
    }
    buffer[i] = '\0';
    return i;
    
    //    printf("%s %d\n", buffer, (int)strlen(buffer));
}

int insertNewNode(Node **head, char *p, int dataSize)
{
    Node *newNode = (struct Node*) malloc(sizeof(struct Node));
    if(!newNode)
        return FALSE;
    
    newNode->data = (char*) malloc(sizeof(char) * dataSize+1);
    if(!(newNode->data))
        return FALSE;
    
    strcpy(newNode->data, p);
    newNode->next = *head;
    *head = newNode;
    
    return TRUE;
}

int deleteNode(Node **head, char wine[])
{
    Node *temp = *head;
    Node *prev = NULL;
    
    // If head node to be deleted
    if (temp != NULL && !strcmp(temp->data, wine))
    {
        *head = temp->next;   // Changed head
        free(temp);           // free old head
        return TRUE;
    }
    
    // Search for the key to be deleted, keep track
    while (temp != NULL && strcmp(temp->data, wine))
    {
        prev = temp;
        temp = temp->next;
    }
    
    // If key not present in linked list
    if (temp == NULL)
        return FALSE;
    
    // Unlink the node from linked list
    prev->next = temp->next;
    
    // Free memory
    free(temp->data);
    free(temp);
    
    return TRUE;
}

// This function prints contents of the linked list
void printWines(struct Node *p)
{
    printf("\nThe wines to be drinked:\n");
    while (p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }
}
