
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

typedef struct _Data* nd_ptr;

// Data structure Define
typedef struct _Data
{
    int tag;
    char date[11];
    char pee_paid[5];
    char name[20];
    int age;
    char organization[50];
    char job[20];
    nd_ptr next;
} Data;

// This function opens file and returns file pointer
FILE* open_file(const char* address, const char* mode)
{
    FILE* fp = fopen(address, mode);

    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    return fp;
}

// This function splits raw data into data structure
void split_data(char raw_data[MAX][1000], Data data[MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        int count = 0;
        char* token = strtok(raw_data[i], "/");
        char tokens[7][100] = {
            0,
        };

        while (count < 7)
        {
            strcpy(tokens[count], token);
            token = strtok(NULL, "/");
            count++;
        }

        data[i].tag = atoi(tokens[0]);
        strcpy(data[i].date, tokens[1]);
        strcpy(data[i].pee_paid, tokens[2]);
        strcpy(data[i].name, tokens[3]);
        data[i].age = atoi(tokens[4]);
        strcpy(data[i].organization, tokens[5]);
        strcpy(data[i].job, tokens[6]);
    }
}

// This function sorts data by age using bubble sort
void sort_data(Data data[MAX])
{
    Data temp;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX - i - 1; j++)
        {
            if (data[j].age > data[j + 1].age)
            {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

// This function creates a linked list from sorted data
Data* linked_list(Data data[MAX])
{
    Data* dummy_head = (Data*)malloc(sizeof(Data));
    if (dummy_head == NULL)
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    dummy_head->next = NULL;
    Data* current = dummy_head;

    for (int i = 0; i < MAX; i++)
    {
        Data* new_node = (Data*)malloc(sizeof(Data));
        if (new_node == NULL)
        {
            printf("Memory allocation error\n");
            exit(1);
        }

        *new_node = data[i];
        new_node->next = NULL;

        current->next = new_node;
        current = new_node;
    }

    return dummy_head->next; // Skip the dummy head when returning the actual head
}

void print_linked_list(Data* head)
{
    Data* ptr = head;  // Start from the dummy head

    while (ptr != NULL)
    {
        printf("%d/%s/%s/%s/%d/%s/%s\n", ptr->tag, ptr->date, ptr->pee_paid, ptr->name, ptr->age, ptr->organization, ptr->job);

        // Move to the next node
        ptr = ptr->next;
    }
}

void free_linked_list(Data* head)
{
    Data* ptr = head;  // Start from the dummy head

    while (ptr != NULL)
    {
        Data* temp = ptr;
        // Move to the next node
        ptr = ptr->next;

        // Free the current node
        free(temp);
    }
}

int main()
{
    char raw_data[30][1000];
    Data data[MAX];
    FILE* fp = open_file("C:/data/registration_data.txt", "r");
    FILE* sorted_fp = open_file("C:/data/sorted_data.txt", "w");

    // Read data from file
    for (int i = 0; i < MAX; i++)
        fgets(raw_data[i], 1000, fp);

    split_data(raw_data, data);
    sort_data(data);

    // Write data to file
    for (int i = 0; i < MAX; i++)
        fprintf(sorted_fp, "%d/%s/%s/%s/%d/%s/%s", data[i].tag, data[i].date, data[i].pee_paid, data[i].name, data[i].age, data[i].organization, data[i].job);

    Data* head_linked_list = linked_list(data);

    // Print the linked list
    printf("[Linked List Printing]\n\n");
    print_linked_list(head_linked_list);

    // Free memory used by linked list
    free_linked_list(head_linked_list);

    fclose(fp);
    fclose(sorted_fp);

    return 0;
}
