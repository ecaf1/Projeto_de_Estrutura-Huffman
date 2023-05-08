//gcc -I .  test_estrutura.c tree.c queue.c -o teste_estrutura -lcunit

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "tree.h"
#include "queue.h"
void test_creat_node(void){
    Tree* node = creat_node('A', 10);
    CU_ASSERT(node != NULL);
    CU_ASSERT_EQUAL(node->character, 'A');
    CU_ASSERT_EQUAL(node->frequency, 10);
    CU_ASSERT(node->next == NULL);
    CU_ASSERT(node->left == NULL);
    CU_ASSERT(node->right == NULL);
}

void test_write_Tree(void){
    FILE *header = fopen("test_header.txt", "w");
    int size = 0;
    Tree *root = creat_node('A', 10);
    root->left = creat_node('B', 5);
    root->right = creat_node('C', 3);
    write_Tree(root, &size, header);
    fclose(header);
    CU_ASSERT_EQUAL(size, 3);
    header = fopen("test_header.txt", "r");
    char c;
    fscanf(header, "%c", &c);
    CU_ASSERT_EQUAL(c, 'A');
    fscanf(header, "%c", &c);
    CU_ASSERT_EQUAL(c, 'B');
    fscanf(header, "%c", &c);
    CU_ASSERT_EQUAL(c, 'C');
    fclose(header);
}

void test_dequeue(void){
    priority_queue *pq = creat_priority_queue();
    Tree* node1 = creat_node('A', 10);
    Tree* node2 = creat_node('B', 5);
    enqueue(node1, pq);
    enqueue(node2, pq);
    Tree* dequeued_node = dequeue(pq);
    CU_ASSERT_EQUAL(dequeued_node->character, 'B');
    CU_ASSERT_EQUAL(dequeued_node->frequency, 5);
    dequeued_node = dequeue(pq);
    CU_ASSERT_EQUAL(dequeued_node->character, 'A');
    CU_ASSERT_EQUAL(dequeued_node->frequency, 10);
    dequeued_node = dequeue(pq);
    CU_ASSERT(dequeued_node == NULL);
}

void test_creat_priority_queue(void){
    priority_queue *pq = creat_priority_queue();
    CU_ASSERT(pq != NULL);
    CU_ASSERT(pq->head == NULL);
}

void test_enqueue(void){
    priority_queue *pq = creat_priority_queue();
    Tree* node1 = creat_node('A', 10);
    Tree* node2 = creat_node('B', 5);
    Tree* node3 = creat_node('C', 15);
    enqueue(node1, pq);
    enqueue(node2, pq);
    enqueue(node3, pq);
    CU_ASSERT_EQUAL(pq->head->character, 'B');
    CU_ASSERT_EQUAL(pq->head->frequency, 5);
    CU_ASSERT_EQUAL(pq->head->next->character, 'A');
    CU_ASSERT_EQUAL(pq->head->next->frequency, 10);
    CU_ASSERT_EQUAL(pq->head->next->next->character, 'C');
    CU_ASSERT_EQUAL(pq->head->next->next->frequency, 15);
}

int main(){
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes das funções da árvore Huffman", 0, 0);
    CU_add_test(suite, "Teste da função creat_node", test_creat_node);
    CU_add_test(suite, "Teste da função write_Tree", test_write_Tree);
    CU_add_test(suite, "Teste da função dequeue", test_dequeue);
    CU_add_test(suite, "Teste da função creat_priority_queue", test_creat_priority_queue);
    CU_add_test(suite, "Teste da função test_enqueue", test_enqueue);
    CU_add_test(suite, "Teste da função creat", test_creat_priority_queue);

    // CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    return 0;
}