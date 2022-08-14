#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 1024

struct Node{
    char str[N];
    struct Node *right;
    struct Node *left;
    struct Node *p;
};

struct Node *searchNode(struct Node **root, char str[N]);
void insert(struct Node **root, struct Node *node);
void printInOrder(struct Node *root);
int addVocabulary(struct Node **root);
void tryGuess(struct Node **root, const char chosen_word[N], int n, int k);

int main() {
    int k, n;
    int bool = 0;
    char chosen_word[N];    //ottimizzare con addvocabulary?
    struct Node *root = NULL;

    scanf("%d", &k);
    /*for (int i = 0; i < N; i++) {
        getchar();
    }*/
    while (bool == 0) {
        bool = addVocabulary(&root);
    }
    printInOrder(root);
    scanf("%s\n%d", chosen_word, &n);
    tryGuess(&root, chosen_word, n, k);


    return 0;

}

struct Node *searchNode(struct Node **root, char str[N]) {
    if (*root == NULL || strcmp(str, (*root)->str) == 0) {
        return *root;
    }
    if (strcmp(str, (*root)->str) < 0) {
        return searchNode(&((*root)->left), str);
    } else {
        return searchNode(&((*root)->right), str);
    }
}

void insert(struct Node **root, struct Node *node){
    struct Node *x, *y;
    y = NULL;
    x = *root;

    while (x != NULL){
        y = x;
        if (strcmp(node->str, x->str) < 0){
            x = x->left;
        }else{
            x = x->right;
        }
    }node->p = y;
    if (y == NULL){
        *root = node;
    }else if (strcmp(node->str, y->str) < 0){
        y->left = node;
    }else{
        y->right = node;
    }
}

void printInOrder(struct Node *root){
    if (root != NULL){
        printInOrder(root->left);
        printf("%s\n", root->str);
        printInOrder(root->right);
    }
}

int addVocabulary(struct Node **root){
    char str[N];

    scanf("%s", str);
    if (strcmp(str,"+nuova_partita") == 0){
        return 1;
    }
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    strcpy(new_node->str, str);
    insert(root, new_node);
    return 0;
}

void tryGuess(struct Node **root, const char chosen_word[N], int n, int k){   //const?
    int cont = 0;
    int n_char_chosen_word = 0;
    int n_char_right_chosen_word = 0;
    int diff_cont = 0;
    char res[N];
    char str[N];

    while(cont < n){
        scanf("%s", str);
        if (searchNode(root, str) != NULL){
            for (int i = 0; i < k; i++) {
                if (str[i] == chosen_word[i]) {
                    res[i] = '+';
                } else {
                    for (int j = 0; j < k; j++) {
                        if (chosen_word[j] == str[i]) {
                            n_char_chosen_word++;
                            if (chosen_word[j] == str[j]) {
                                n_char_right_chosen_word++;
                            }
                        }
                    }
                    for (int j = 0; j < i; j++) {
                        if (str[j] == str[i] && str[j] != chosen_word[j]) {
                            diff_cont++;
                        }
                    }
                    if (diff_cont >= (n_char_chosen_word - n_char_right_chosen_word)) {
                        res[i] = '/';
                    } else {
                        res[i] = '|';
                    }
                    n_char_chosen_word = 0;
                    n_char_right_chosen_word = 0;
                    diff_cont = 0;
                }
            }
            printf("%s\n", res);
            cont++;
        }else{
            printf("not_exists\n");
        }
    }
}

