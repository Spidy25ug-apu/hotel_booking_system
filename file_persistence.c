

#include <stdio.h>
#include <stdlib.h>
#include "room.h"


// Load rooms from file
void load_rooms_from_file(RoomList *list)
{
    FILE *fp = fopen("rooms.dat", "rb");

    if (fp == NULL)
    {
        return;
    }

    Room tempRoom;

    while (fread(&tempRoom, sizeof(Room), 1, fp) == 1)
    {
        Node *newNode = malloc(sizeof(Node));

        if (newNode == NULL)
        {
            fclose(fp);
            return;
        }

        newNode->data = tempRoom;
        newNode->next = NULL;

        if (list->head == NULL)
        {
            list->head = newNode;
        }
        else
        {
            Node *temp = list->head;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = newNode;
        }

        list->total_rooms++;
    }

    fclose(fp);
}


//  Save rooms to file
void save_rooms_to_file(RoomList *list)
{
    FILE *fp = fopen("rooms.dat", "wb");

    if (fp == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    Node *temp = list->head;

    while (temp != NULL)
    {
        if (fwrite(&temp->data, sizeof(Room), 1, fp) != 1)
        {
            printf("Error saving room data.\n");
            fclose(fp);
            return;
        }

        temp = temp->next;
    }

    fclose(fp);

    // Free linked list nodes
    temp = list->head;

    while (temp != NULL)
    {
        Node *nextNode = temp->next;

        free(temp);

        temp = nextNode;
    }

    list->head = NULL;
    list->total_rooms = 0;
}
