#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRUIT_NAME 20

typedef struct ListNode {
    char data[MAX_FRUIT_NAME];
    struct ListNode* link;
} ListNode;

ListNode* head = NULL; // ���� ���� ����Ʈ�� ��� ������
ListNode* deletedHead = NULL; // ������ ���� ����Ʈ�� ��� ������

// ����Ʈ�� �׸� ���
void print_list(ListNode* head) {
    if (head == NULL) return;

    ListNode* p = head->link;
    do {
        printf("%s->", p->data);
        p = p->link;
    } while (p != head->link);
}

// ����Ʈ�� �������� ��带 �߰�
ListNode* insert_last(ListNode* head, char* data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    strcpy(node->data, data);
    if (head == NULL) {
        head = node;
        node->link = head;
    }
    else {
        node->link = head->link;
        head->link = node;
        head = node;
    }
    return head;
}

// ����Ʈ�� ù ��°�� ��带 �߰�
ListNode* insert_first(ListNode* head, char* data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    strcpy(node->data, data);
    if (head == NULL) {
        head = node;
        node->link = head;
    }
    else {
        node->link = head->link;
        head->link = node;
    }
    return head;
}

// ����Ʈ���� ��带 ����
ListNode* delete_node(ListNode* head, char* data) {
    if (head == NULL) return NULL;

    ListNode* p = head;
    ListNode* prev = NULL;
    do {
        prev = p;
        p = p->link;
        if (strcmp(p->data, data) == 0) {
            prev->link = p->link;
            if (p == head) {
                if (head == head->link) {
                    head = NULL;
                }
                else {
                    head = prev;
                }
            }
            free(p);
            return head;
        }
    } while (p != head);
    return head;
}

// ���� ����Ʈ �ʱ�ȭ
void initFruits() {
    char* initFruits[] = {
        "Mango", "Orange", "Apple", "Grape", "Cherry",
        "Plum", "Guava", "Raspberry", "Banana", "Peach"
    };
    int n = sizeof(initFruits) / sizeof(initFruits[0]);
    for (int i = 0; i < n; i++) {
        head = insert_last(head, initFruits[i]);
    }
}

// ���� �߰� �Լ�
void addFruit(char* fruitName) {
    ListNode* p = head;
    if (head) {
        do {
            if (strcmp(p->data, fruitName) == 0) {
                printf("%s��(��) �̹� �����մϴ�.\n", fruitName);
                return;
            }
            p = p->link;
        } while (p != head);
    }
    head = insert_last(head, fruitName);
    printf("%s�� �߰��߽��ϴ�.\n", fruitName);
}

// ���� ���� �Լ�
void deleteFruit(char* fruitName) {
    ListNode* p = head;
    if (head) {
        do {
            if (strcmp(p->data, fruitName) == 0) {
                head = delete_node(head, fruitName);
                deletedHead = insert_last(deletedHead, fruitName);
                printf("%s�� �����߽��ϴ�.\n", fruitName);
                return;
            }
            p = p->link;
        } while (p != head);
    }
    printf("%s�� ã�� �� �����ϴ�.\n", fruitName);
}

int main() {
    int choice;
    char fruitName[MAX_FRUIT_NAME];

    initFruits();

    while (1) {
        printf("\n1. ���� �߰�\n2. ���� ����\n3. ������ ���� ��� ���\n4. ����\n����: ");
        scanf("%d", &choice);
        getchar(); // ���� ����

        switch (choice) {
        case 1:
            printf("�߰��� ���� �̸�: ");
            fgets(fruitName, MAX_FRUIT_NAME, stdin);
            fruitName[strcspn(fruitName, "\n")] = 0; // ���� ���� ����
            addFruit(fruitName);
            break;
        case 2:
            printf("������ ���� �̸�: ");
            fgets(fruitName, MAX_FRUIT_NAME, stdin);
            fruitName[strcspn(fruitName, "\n")] = 0; // ���� ���� ����
            deleteFruit(fruitName);
            break;
        case 3:
            print_list(deletedHead);
            break;
        case 4:
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }

    return 0;
}
