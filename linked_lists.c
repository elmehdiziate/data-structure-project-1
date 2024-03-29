#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct tag
{
    char ID[10];
    char name[80];
    char major[80];
    char class[80];
    struct tag *next;
} student_node;
int check(char *name)
{
    // in this function we check the class of the student return 0,1,2,3 if the class is available if not number 4 is returned
    if (strcmp(name, "Freshman") == 0)
    {
        return (0);
    }
    else if (strcmp(name, "Sophomore") == 0)
    {
        return (1);
    }
    else if (strcmp(name, "Junior") == 0)
    {
        return (2);
    }
    else if (strcmp(name, "Senior") == 0)
    {
        return (3);
    }
    else
    {
        return (4);
    }
}
student_node *create_fill_node(FILE *infp)
{
    // in this function we create a node usinf the file data
    student_node *new_node;
    new_node = (student_node *)malloc(sizeof(student_node));
    fgets(new_node->ID, 10, infp);
    fgets(new_node->name, 80, infp);
    fgets(new_node->major, 80, infp);
    fgets(new_node->class, 80, infp);
    new_node->class[strlen(new_node->class) - 1] = '\0';
    new_node->next = NULL;
    return (new_node);
}
void add_node_LL(student_node **p_head, student_node *ToAdd)
{
    // in this function we add the node to the linked list
    student_node *walker;
    if (*p_head == NULL)
    {
        *p_head = ToAdd;
    }
    else
    {
        walker = *p_head;
        while (walker->next != NULL)
            walker = walker->next;
        walker->next = ToAdd;
    }
}
void traverse(student_node *head)
{
    // this function is used to print the content of a linked list
    student_node *walker;
    printf("This is the content of the linked list:\n");
    walker = head;
    while (walker != NULL)
    {
        printf("\n%s\n%s\n%s\n%s\n", walker->ID, walker->name, walker->major, walker->class);
        walker = walker->next;
    }
}
void Load_File_content_to_the_array(FILE *infp, student_node **arr)
{
    // this function is used as the main function for creating a linked list by regrouping the add and check functions
    student_node *new_node;
    char line[50];
    fseek(infp, 0, 0);
    arr[0] = NULL;
    arr[1] = NULL;
    arr[2] = NULL;
    arr[3] = NULL;
    fgets(line, 50, infp);
    fgets(line, 50, infp);
    while (!feof(infp))
    {
        new_node = create_fill_node(infp);
        add_node_LL(&arr[check(new_node->class)], new_node);
        fgets(line, 50, infp);
    }
}
student_node *fill_new_student()
{
    // this function is used to fill the node of the new student we want to add
    char c;
    student_node *new_name;
    new_name = (student_node *)malloc(sizeof(student_node));
    scanf("%c", &c);
    printf("enter the ID:");
    gets(new_name->ID);
    strcat(new_name->ID, "\n");
    printf("enter the name:");
    gets(new_name->name);
    strcat(new_name->name, "\n");
    printf("enter the major:");
    gets(new_name->major);
    strcat(new_name->major, "\n");
    printf("enter the class(Freshman, Sophomore, Junior, Senior):");
    gets(new_name->class);
    new_name->next = NULL;
    return (new_name);
}
void add_new_node_LL(student_node **p_head, student_node *ToAdd)
{
    // this function is used to add the new student
    student_node *walker;
    walker = *p_head;
    if (strcmp(ToAdd->name, walker->name) < 0)
    {
        ToAdd->next = *p_head;
        *p_head = ToAdd;
    }
    else
    {
        while (walker->next != NULL)
        {
            if (strcmp(ToAdd->name, walker->next->name) < 0)
            {
                ToAdd->next = walker->next;
                walker->next = ToAdd;
                break;
            }
            walker = walker->next;
        }
    }
    if (walker->next == NULL)
    {
        walker->next = ToAdd;
    }
}
int search_Add_a_new_student(student_node **arr, student_node *new_student)
{
    // this function is used to check and add the new student depending on the class
    if (arr[check(new_student->class)] == NULL)
    {
        arr[check(new_student->class)] = new_student;
    }
    else
    {
        if (check(new_student->class) == 4)
        {
            return 0;
        }
        else
        {
            add_new_node_LL(&arr[check(new_student->class)], new_student);
            return 1;
        }
    }
}
student_node *delete(student_node *head, char *ID_delete)
{
    // this function is used to delete a student depending on the ID entered by the user
    student_node *walker1, *temp;
    walker1 = head;
    if (strcmp(walker1->ID, ID_delete) == 0)
    {
        head = walker1->next;
        free(walker1);
    }
    else
    {
        while (walker1->next != NULL)
        {
            if (strcmp(walker1->next->ID, ID_delete) == 0)
            {
                temp = walker1->next;
                walker1->next = temp->next;
                free(temp);
                break;
            }
            else
            {
                walker1 = walker1->next;
            }
        }
    }
    return (head);
}
void search_delete_node_ID(student_node **arr, char *ID_delete, int *tap)
{
    // this function is used to to search and delete the node of the ID entered by the user
    student_node *walker;
    for (int i = 0; i < 4; i++)
    {
        walker = arr[i];
        while (walker != NULL)
        {
            if (strcmp(walker->ID, ID_delete) == 0)
            {
                arr[i] = delete (arr[i], ID_delete);
                *tap = 1;
                break;
            }
            walker = walker->next;
        }
    }
}
void traverse_class(student_node **arr, char *class)
{
    // this function is used to traverse linked list of a class entered by the user
    if (check(class) == 4)
    {
        printf("the class is not available\n");
    }
    else
    {
        if (arr[check(class)] == NULL)
        {
            printf("the arr is empty");
        }
        else
        {
            traverse(arr[check(class)]);
        }
    }
}
void load(student_node *head, FILE *infp)
{
    // this function is used to load the data of a linked list to a file created
    student_node *walker;
    walker = head;
    while (walker != NULL)
    {
        fprintf(infp, "\n%s\n%s\n%s\n%s\n%s\n", walker->ID, walker->name, walker->major, walker->class, "-----------------------");
        walker = walker->next;
    }
}
void load_data_to_file(student_node **arr)
{
    // this function is used to load the whole linked lists on a file
    FILE *infp;
    infp = fopen("final_LL_Content.txt", "w");
    for (int i = 0; i < 4; i++)
    {
        load(arr[i], infp);
        free(arr[i]);
    }
    fclose(infp);
}
void load_data_to_screen(FILE *infp)
{
    // this function is used to print the content of a file to screen
    char line[50];
    fseek(infp, 0, 0);
    while (!feof(infp))
    {
        fgets(line, 50, infp);
        printf("%s", line);
    }
}
void menu(void)
{
    printf("\n\t\t----------------- Menu--------------------\n");
    printf("\n\t\t1. Load file content to screen \n");
    printf("\n\t\t2. Load File content to the array  \n");
    printf("\n\t\t3. Add a new student\n");
    printf("\n\t\t4. Remove a student\n");
    printf("\n\t\t5. Print Students of an Academic class\n");
    printf("\n\t\t6. QUIT\n");
    printf("\n\t\t------------------------------------------\n");
    printf("\n\t\tYour choice:");
}
int main(void)
{
    FILE *infp;
    char c;
    student_node *(arr[4]);
    int choice, flag = 0, tap = 0;
    student_node *new_student;
    char ID_delete[10], class[30];
    infp = fopen("List.txt", "r");
    if (infp == NULL)
    {
        printf("Error!");
    }
    else
    {
        do
        {
            menu();
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                load_data_to_screen(infp);
                break;
            case 2:
                Load_File_content_to_the_array(infp, arr);
                printf("file was loaded\n");
                flag = 1;
                break;
            case 3:
                if (flag == 0)
                {
                    printf("make sure to fill the array and the LL");
                }
                else
                {
                    new_student = fill_new_student();
                    if (search_Add_a_new_student(arr, new_student) == 0)
                    {
                        printf("the class is not available");
                    }
                    else
                    {
                        printf("the student was added");
                    }
                }
                break;
            case 4:
                if (flag == 0)
                {
                    printf("make sure to fill the array and the LL");
                }
                else
                {
                    scanf("%c", &c);
                    printf("enter the ID of the student you want to delete");
                    gets(ID_delete);
                    strcat(ID_delete, "\n");
                    search_delete_node_ID(arr, ID_delete, &tap);
                    if (tap == 0)
                    {
                        printf("the node was not deleted");
                    }
                    else
                    {
                        printf("the node was deleted\n");
                    }
                }
                break;
            case 5:
                if (flag == 0)
                {
                    printf("make sure to fill the LL");
                }
                else
                {
                    printf("enter the class you want to print: ");
                    scanf("%c", &c);
                    gets(class);
                    traverse_class(arr, class);
                }
                break;
            case 6:
                if (flag == 0)
                {
                    printf("make sure to fill the array");
                }
                else
                {
                    load_data_to_file(arr);
                }
                printf("done");
                break;
            default:
                printf("invalid choice!!!");
            }
        } while (choice != 6);
    }
    fclose(infp);
}
