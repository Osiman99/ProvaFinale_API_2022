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
void tryGuess(struct Node **root, char chosenWord[N], int n, int k);

int main() {
    int k, n;
    int bool = 0;
    char chosenWord[N];    //ottimizzare con addvocabulary?
    struct Node *root = NULL;

    scanf("%d", &k);
    /*for (int i = 0; i < N; i++) {
        getchar();
    }*/
    while (bool == 0) {
        bool = addVocabulary(&root);
    }
    printInOrder(root);
    scanf("%s\n%d", chosenWord, &n);
    tryGuess(&root, chosenWord, n, k);


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

void tryGuess(struct Node **root, char chosenWord[N], int n, int k){
    int cont = 0;
    int n_char_chosenWord = 0;
    int n_char_right_chosenWord = 0;
    char str[N], res[N];

    scanf("%s", str);
    while(cont < n){
        if (searchNode(root, str) != NULL){
            for (int i = 0; i < k; i++){
                if(str[i] == chosenWord[i]){
                    n_char_chosenWord++;
                    n_char_right_chosenWord++;
                    printf("%d +", k);
                }else{
                    for (int j = 1; j < k; j++) {
                        if(chosenWord[j] == str[i]){
                            n_char_chosenWord ++;
                        }if(chosenWord[j] == str[i] && chosenWord[j] == str[j]){
                            n_char_right_chosenWord++;
                        }
                    }
                }
            }
            cont++;
        }else{
            printf("not_exists");
        }
    }
}

