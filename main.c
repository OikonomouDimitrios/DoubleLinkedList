#include <stdio.h>
#include <malloc.h>


typedef struct record *Record;
struct record {
    int am;
    double grade;
    Record next;
    Record previous;
};
Record head, tail, temp, aux;


char handleInput(char input);

void printRecords(Record h);

void insertRecord(Record *h);

void deleteRecord(Record *h);


int main(void) {
    head = NULL;
    int num1 = 0;
    char input;
    printf("\nselect action: ");
    printf("\ngive i/d/p for insert,delete,print: ");
    fflush(stdin);
    input = getchar();

    while (input != 'q') {
        handleInput(input);
        printf("\nselect action: ");
        printf("\ngive i/d/p for insert,delete,print: ");
        fflush(stdin);
        input = getchar();
    }

    printf("");
    return 0;
}

char handleInput(char input) {
    if (input == 'i') {
        insertRecord(&head);
    } else if (input == 'p') {
        printRecords(head);
    } else if (input == 'q') {
        printf("\nexiting program!");
    } else if (input == 'd') {
        deleteRecord(&head);
    } else {
        printf("\ninvalid input!");
    }
    return input;
}

void insertRecord(Record *h) {
    Record te, a;
    int am;
    double grade;
    te = (Record) malloc(sizeof(struct record));
    printf("give me an AM");
    scanf("%d", &am);
    printf("give me a grade");
    scanf("%lf", &grade);
    te->am = am;
    te->grade = grade;
    te->previous = NULL;
    te->next = NULL;
    if (*h == NULL) {
        *h = te;
    } else {
        if ((*h)->next == NULL) {
            if (te->am > (*h)->am) {
                //next of head point to te
                (*h)->next = te;
                //previous of te points to head
                te->previous = *h;
            } else {
                //te->am is less than head's am so we swap
                te->next = (*h);
                (*h)->previous = te;
                *h = te;
            }
        } else {
            a = *h;
            while (a->next != NULL && a->next->am < te->am) {
                a = a->next;
            }
            if (a->next == NULL) {
                a->next = te;
                te->previous = a;
            } else {
                te->next = a->next;
                a->next->previous = te;
                a->next = te;
                te->previous = a;
            }
        }
    }
}


void printRecords(Record h) {
    Record a;
    a = h;
    while (a != NULL) {
        printf("\nAM is : %d, grade is %lf", a->am, a->grade);
        a = a->next;
    }
}

void deleteRecord(Record *h) {
    Record a;
    int am;
    printf("give me an AM to delete");
    scanf("%d", &am);
    if (*h == NULL) {
        printf("\nlist is empty!");
    } else {
        if ((*h)->next == NULL) {
            printf("\n list has one element");
        }
        if ((*h)->am == am) {
            a = *h;
            *h = (*h)->next;
            free(a);
            if (*h == NULL) {
                printf("\n list is now empty");
            } else {
                (*h)->previous = NULL;
            }
        } else {
            a = *h;
            while (a->next != NULL && a->next->am != am) {
                a = a->next;
            }
            if (a->next == NULL) {
                printf("\n record not found");
            } else {
                temp = a->next;
                a->next = temp->next;
                if (temp->next != NULL) {
                    temp->next->previous = a;
                }
                free(temp);
            }
        }
    }
}


