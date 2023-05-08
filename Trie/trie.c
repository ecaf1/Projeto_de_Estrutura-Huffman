#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 256

typedef struct trienode
{
    struct trienode *children[ALPHABET_SIZE];
    bool terminal;
} trienode;

trienode *createnode()
{
    trienode *newnode = (trienode*)malloc(sizeof *newnode);

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        newnode->children[i] = NULL;
    }
    newnode->terminal = false;
    return newnode;
}

bool trieinsert(trienode **root, char *signedtext)
{
    if (*root == NULL)
    {
        *root = createnode();
    }

    unsigned char *text = (unsigned char *)signedtext;
    trienode *tmp = *root;
    int lenght = strlen(signedtext);

    for (int i = 0; i < lenght; i++)
    {
        if (tmp->children[text[i]] == NULL)
        {
            tmp->children[text[i]] = createnode();
        }

        tmp = tmp->children[text[i]];
    }
    
    if (tmp->terminal)
    {
        return false;
    }
    else
    {
        tmp->terminal = true;
        return true;
    }
}

void print_trie_rec(trienode *node, unsigned char *prefix, int lenght)
{   
    unsigned char newprefix[lenght+2];
    memcpy(newprefix,prefix,lenght);
    newprefix[lenght+1] = 0;

    if (node->terminal)
    {
        printf("WORD IS: %s\n", prefix);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(node->children[i] != NULL)
        {
            newprefix[lenght] = i;
            print_trie_rec(node->children[i], newprefix, lenght+1);
        }
    }
    
}

void print_trie(trienode * root)
{
    if(root == NULL)
    {
        printf("TRIE EMPTY\n");
        return;
    }
    print_trie_rec(root, NULL, 0);
}

bool search_trie(trienode * root, char *signedtext)
{
    unsigned char *text = (unsigned char *) signedtext;
    int lenght = strlen(signedtext);
    trienode * tmp = root;

    for (int i = 0; i < lenght; i++)
    {
        if (tmp->children[text[i]] == NULL)
        {
            return false;
        }
        tmp = tmp->children[text[i]];
    }
    return tmp->terminal;
}

bool node_has_children(trienode * node)
{
    if (node == NULL) return false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            // tem pelo menos um filho
            return true;
        }
    }

    return false;
    
}

trienode * delete_string_rec(trienode * node, unsigned char * text, bool * deleted)
{
    if(node == NULL) return node;

    if (*text == '\0')
    {
        if (node->terminal)
        {
            node->terminal = false;
            *deleted = true;

            if (node_has_children(node) == false)
            {
                free(node);
                node = NULL;
            }
        }

        return node;
    }

    node->children[text[0]] = delete_string_rec(node->children[text[0]], text+1, deleted);

    if (*deleted && node_has_children(node) == false && node->terminal == false)
    {
        free(node);
        node = NULL;
    }
    return node;
}

bool delete_string (trienode **root, char *signedtext)
{
    unsigned char *text = (unsigned char *) signedtext;
    bool result = false;

    if (*root == NULL) return false;

    *root = delete_string_rec(*root, text, &result);
    return result;     











}  

int main()
{
    trienode * root = NULL;

    trieinsert(&root, "GATO");
    trieinsert(&root, "SAPATO");
    trieinsert(&root, "RATO");
    trieinsert(&root, "CHATO");
    trieinsert(&root, "MATO");

    print_trie(root);
    printf("\n");

    printf("Buscando GATO: %d\n", search_trie(root, "GATO"));
    printf("Buscando SAPATO: %d\n", search_trie(root, "SAPATO"));
    printf("Buscando GATINHO: %d\n", search_trie(root, "GATINHO"));
    printf("\n");

    delete_string(&root, "CHATO");
    delete_string(&root, "MATO");

    print_trie(root);
}