#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
	char * word;     
	struct node *right, *left;
	int available;
} Node;

void insertNode(Node *node);
void printTree(Node *x);
int find(char string[]);
int compare(char string[]);

int k;
char reference[10];
Node *root;

int main(){
    //int first_turn = 1;
    //int quit = 0;
    int end = 0;
    int count = 0;
    int attempts;
    char string[10];
    Node *node = NULL;

    fscanf(stdin, "%d", &k);
    fscanf(stdin, "%s", string);
    while (string[0] != '+'){
        node = malloc(sizeof(Node) + (sizeof(char) * (k+1)));
        
        node->right = NULL;
        node->left = NULL;
        node->available = 1;
        node->word = (char *)&(node->word) + sizeof(Node);
        for (int i = 0; i < k; i++) {
            node->word[i] = string[i];
        }
        node->word[k] = '\0';
        
        insertNode(node);
        fscanf(stdin, "%s", string);
        
        //fprintf(stdout, "%s\n", string);
    }

    while (1){
        if(string[1] == 'n'){
            fscanf(stdin, "%s", reference);
            fscanf(stdin, "%d", &attempts);
            fscanf(stdin, "%s", string);
            while (!end){
                if (string[0] == '+'){
                    if (string[1] == 'i'){
                        fscanf(stdin, "%s", string);
                        while(string[0] != '+'){
                            node = malloc(sizeof(Node) + (sizeof(char) * (k+1)));
                            node->right = NULL;
                            node->left = NULL;
                            node->available = 1;
                            node->word = (char *)&(node->word) + sizeof(Node);
                            for (int i = 0; i < k; i++) {
                                node->word[i] = string[i];
                            }
                            node->word[k] = '\0';
                            insertNode(node);
                            //filter();
                            fscanf(stdin, "%s", string);
                        }
                    }else{
                        //stampa_filtrate
                    }
                }else{    
                    if(!find(string)){
                        fprintf(stdout, "not_exists\n");
                    }else{
                        if (!compare(string)){
                            //count();
                            count++;
                            if(count == attempts){
                                fprintf(stdout, "ko\n");
                                end = 1;
                            }
                        }else{
                            fprintf(stdout, "ok\n");
                            end = 1;
                        }
                    }
                }
                if(!end){
                    fscanf(stdin, "%s", string);
                }
            }
        }else{
            fscanf(stdin, "%s", string);
            while(string[0] != '+'){
                node = malloc(sizeof(Node) + (sizeof(char) * (k+1)));
        
                node->right = NULL;
                node->left = NULL;
                node->available = 1;
                node->word = (char *)&(node->word) + sizeof(Node);
                for (int i = 0; i < k; i++) {
                    node->word[i] = string[i];
                }
                node->word[k] = '\0';
                insertNode(node);
                fscanf(stdin, "%s", string);
            }
        }fscanf(stdin, "%s", string);
    }

    //printTree(root);


    return 0;
}

void printTree(Node *x){
    if (x != NULL){
        printTree(x->left);
        fprintf(stdout, "%s\n", x->word);
        printTree(x->right);
    }
}

void insertNode(Node *node){
    Node *x, *y;
    int i;
    char l_r ='n';
    
    y = NULL;
    x = root;
    while (x != NULL){
        y = x;
        for (i = 0; i < k; i++){
            if (node->word[i] > x->word[i]){
                l_r = 'r';
                break;
            }else if (node->word[i] < x->word[i]){
                l_r = 'l';
                break;
            }
        }
        if (l_r == 'r'){
            x = x->right;
        }else {
            x = x->left;
        }
    }if (y == NULL){
        root = node;
    }else if (l_r == 'r'){
        y->right = node;
    }else {
        y->left = node;
    }
}

int find(char string[]){
    Node *x;
    int i;
    char l_r ='n';
    
    x = root;
    while (x != NULL){
        for (i = 0; i < k; i++){
            if (node->word[i] > x->word[i]){
                l_r = 'r';
                break;
            }else if (node->word[i] < x->word[i]){
                l_r = 'l';
                break;
            }
        }
        if (i == k){
            return 1;
        }

        if (l_r == 'r'){
            x = x->right;
        }else {
            x = x->left;
        }
    }return 0;
}

int compare(char string[]){
    int plus = 0;
    char result[k];
    
    for (int i = 0; i < k; i++) {
        if (result[i] != '+'){
            if (string[i] == reference[i] ) {
                result[i] = '+';
                plus++;
            } else {
                for (int j = 0; j < k; j++) {
                    if (reference[j] == string[i]) {         //potrei mette && j != i
                        n_char_reference++;
                        if (reference[j] == string[j]) {
                            if(j > i){
                                result[j] = '+';
                                plus++;                      //mezzo inutile (è più per precisione, da eliminare in caso di non passing upto18)
                            }
                            n_char_right_reference++;
                        }
                    }
                    if (j < i && result[j] == '|' && string[j] == string[i]) {
                        diff_cont++;
                    }
                }
                if (diff_cont >= (n_char_reference - n_char_right_reference)) {
                    result[i] = '/';
                } else {
                    result[i] = '|';
                }
                n_char_reference = 0;
                n_char_right_reference = 0;
                diff_cont = 0;
            }
        }
    }

    if (plus == k) {
		return 1;
    } return 0;

}