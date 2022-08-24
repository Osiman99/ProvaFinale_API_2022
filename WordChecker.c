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
void insertNode(struct Node **root, struct Node *node);
void printInOrder(struct Node *root);
void addVocabulary(struct Node **root, struct Node **rootF, int *start_flag);
void tryGuess(struct Node **root, struct Node **rootF, const char chosen_word[N], int n, int k, int *start_flag);
void insertStart(struct Node **root, struct Node **rootF, char chosenWord[N], int *start_flag);
struct Node *minimumNode(struct Node **node);
struct Node *successorNode(struct Node **node);
void deleteNode(struct Node **rootF, struct Node **node);
void filter(struct Node **rootF, int k, char res[N], char str_guess[N]);
void printFiltered();

int main() {
    int k, n, *start_flag;
    char chosen_word[N];    //ottimizzare con addvocabulary?
    struct Node *root = NULL;
    struct Node *rootF = NULL;

    *start_flag = 1;
    scanf("%d", &k);
    addVocabulary(&root, &rootF, start_flag);
    //printInOrder(root);
    //printInOrder(rootF);
    while (1 == 1) {                                         //while feof
        scanf("%s\n%d", chosen_word, &n);
        tryGuess(&root, &rootF, chosen_word, n, k, start_flag);
        insertStart(&root, &rootF, chosen_word, start_flag);   //uso la chosen_word come str temporanea
    }


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

void insertNode(struct Node **root, struct Node *node){
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

void addVocabulary(struct Node **root, struct Node **rootF, int *start_flag){
    char str[N];

    do{
        scanf("%s", str);
        if (strcmp(str,"+nuova_partita") == 0 || strcmp(str, "+inserisci_fine") == 0){
            return;
        }
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
        strcpy(new_node->str, str);
        insertNode(root, new_node);
        if (*start_flag == 1){
            struct Node *new_nodeF = (struct Node *) malloc(sizeof(struct Node));
            strcpy(new_nodeF->str, str);
            insertNode(rootF, new_nodeF);
        }//else
    }while(strcmp(str, "+nuova_partita") != 0 || strcmp(str, "+inserisci_fine") != 0);
    *start_flag = 0;
}

void tryGuess(struct Node **root, struct Node **rootF, const char chosen_word[N], int n, int k, int *start_flag) {   //const?
    int cont = 0;
    int n_char_chosen_word = 0;
    int n_char_right_chosen_word = 0;
    int diff_cont = 0;
    char res[N], str[N];

    res[k] = '\0';
    while (cont < n) {
        scanf("%s", str);
        if (strcmp(str, "+inserisci_inizio") == 0) {
            addVocabulary(root, rootF, start_flag);
        }else if (strcmp(str, "+stampa_filtrate") == 0){
            printFiltered();
        }else if (searchNode(root, str) != NULL) {
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
            for (int i = 0; i < k; i++){
                if (res[i] != '+'){
                    printf("%s\n", res);
                    cont++;
                    break;
                }if (i == k-1){
                    printf("ok\n");
                    return;
                }
            }
            //filter(rootF, k, res, str);
        } else {
            printf("not_exists\n");
        }
    }
    printf("ko\n");
}

void insertStart(struct Node **root, struct Node **rootF, char str[N], int *start_flag){
    scanf("%s", str);
    if (strcmp(str, "+inserisci_inizio") == 0) {
        addVocabulary(root, rootF, start_flag);
        scanf("%s", str);
    }
}

void filter(struct Node **rootF, int k, char res[N], char str_guess[N]){
    struct Node **node = rootF;
    struct Node **node_temp;
    int n_same_char_str_guess = 0;
    int n_same_char_str_node = 0;

    *node = minimumNode(node);
    for (int i = 0; i < k; i++){
        if (res[i] == '+') {
            for (int j = 0; j < k/* cambiare k con numero nodi albero*/; j++){
                if ((**node).str[i] != str_guess[i]) {
                    *node_temp = *node;
                    *node = successorNode(node);
                    deleteNode(rootF, node_temp);
                }
            }
        }else{                                                                       //array con lettere già viste (es. 'a' che ha / (//////))?
            for (int j = 0; j < k; j++){
                if (str_guess[i] == str_guess[j] && res[j] != '/') {
                    n_same_char_str_guess++;
                }
            }for (int j = 0; j < k/* cambiare k con numero nodi albero*/; j++){
                for (int l = 0; l < k; l++){
                    if ((**node).str[l] == str_guess[i]) {
                        n_same_char_str_node++;
                    }
                }if (res[i] == '/'){
                    if (n_same_char_str_node != n_same_char_str_guess){
                        *node_temp = *node;
                        *node = successorNode(node);
                        deleteNode(rootF, node_temp);
                    }
                }else if (res[i] == '|'){
                    if (n_same_char_str_node < n_same_char_str_guess){
                        *node_temp = *node;
                        *node = successorNode(node);
                        deleteNode(rootF, node_temp);
                    }
                }
                n_same_char_str_guess = 0;
                n_same_char_str_node = 0;
            }
        }node = rootF;
        *node = minimumNode(node);
    }
}

struct Node *minimumNode(struct Node **node){
    while ((**node).left != NULL){
        *node = (**node).left;
    }return *node;
}

struct Node *successorNode(struct Node **node){
    struct Node **successor;

    if ((**node).right != NULL){
        return minimumNode(&((**node).right));
    }*successor = (**node).p;
    while (*successor != NULL && *node == (**successor).right){
        *node = *successor;
        *successor = (**successor).p;
    }return *successor;

}

void deleteNode(struct Node **rootF, struct Node **node){
    struct Node *x, *y;

    if ((**node).left == NULL || (**node).right == NULL) {y = *node;}
    else {y = successorNode(node);}

    if (y->left != NULL) {x = y->left;}
    else {x = y->right;}

    if (x != NULL) {x->p = y->p;}

    if (y->p == NULL) {*rootF = x;}
    else if (y == (y->p)->left) {(y->p)->left = x;}
    else {(y->p)->right = x;}

    if (y != *node){
        strcpy((**node).str, y->str);
    }
    free(y);
}

void printFiltered(){

}