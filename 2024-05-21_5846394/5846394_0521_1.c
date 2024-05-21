#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRUIT_NAME 20

typedef struct ListNode {
    char data[MAX_FRUIT_NAME];
    struct ListNode* link;
} ListNode;

ListNode* head = NULL; // 원형 연결 리스트의 헤드 포인터
ListNode* deletedHead = NULL; // 삭제된 과일 리스트의 헤드 포인터

// 리스트의 항목 출력
void print_list(ListNode* head) {
    if (head == NULL) return;

    ListNode* p = head->link;
    do {
        printf("%s->", p->data);
        p = p->link;
    } while (p != head->link);
}

// 리스트에 마지막에 노드를 추가
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

// 리스트에 첫 번째에 노드를 추가
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

// 리스트에서 노드를 삭제
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

// 과일 리스트 초기화
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

// 과일 추가 함수
void addFruit(char* fruitName) {
    ListNode* p = head;
    if (head) {
        do {
            if (strcmp(p->data, fruitName) == 0) {
                printf("%s는(은) 이미 존재합니다.\n", fruitName);
                return;
            }
            p = p->link;
        } while (p != head);
    }
    head = insert_last(head, fruitName);
    printf("%s를 추가했습니다.\n", fruitName);
}

// 과일 삭제 함수
void deleteFruit(char* fruitName) {
    ListNode* p = head;
    if (head) {
        do {
            if (strcmp(p->data, fruitName) == 0) {
                head = delete_node(head, fruitName);
                deletedHead = insert_last(deletedHead, fruitName);
                printf("%s를 삭제했습니다.\n", fruitName);
                return;
            }
            p = p->link;
        } while (p != head);
    }
    printf("%s를 찾을 수 없습니다.\n", fruitName);
}

int main() {
    int choice;
    char fruitName[MAX_FRUIT_NAME];

    initFruits();

    while (1) {
        printf("\n1. 과일 추가\n2. 과일 삭제\n3. 삭제된 과일 목록 출력\n4. 종료\n선택: ");
        scanf("%d", &choice);
        getchar(); // 버퍼 비우기

        switch (choice) {
        case 1:
            printf("추가할 과일 이름: ");
            fgets(fruitName, MAX_FRUIT_NAME, stdin);
            fruitName[strcspn(fruitName, "\n")] = 0; // 개행 문자 제거
            addFruit(fruitName);
            break;
        case 2:
            printf("삭제할 과일 이름: ");
            fgets(fruitName, MAX_FRUIT_NAME, stdin);
            fruitName[strcspn(fruitName, "\n")] = 0; // 개행 문자 제거
            deleteFruit(fruitName);
            break;
        case 3:
            print_list(deletedHead);
            break;
        case 4:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다.\n");
        }
    }

    return 0;
}
