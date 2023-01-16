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
Node *root;
char reference[10], *rightLetterAndPlace, *rightLetterWrongPlace, *wrongLetters, *letterOccurrence;
int *goodPosition, *halfGoodPosition, *minimumNumber, *perfectCount;

int main(){
    int first_match = 1;
    //int quit = 0;
    int end = 0;
    int count = 0;
    int attempts;
    char string[10];
    Node *node = NULL;

    fscanf(stdin, "%d", &k);

    rightLetterWrongPlace = malloc(sizeof(char) * k*k);
	rightLetterAndPlace = malloc(sizeof(char) * (k+1));
	minimumNumber = malloc(sizeof(int) * (k+1));
	goodPosition = malloc(sizeof(int) * (k+1));
	letterOccurrence = malloc(sizeof(char) * (k+1));
	halfGoodPosition = malloc(sizeof(int) * k*k);
	perfectCount = malloc(sizeof(int) * (k+1));
	wrongLetters = malloc(sizeof(char) * 64);

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
            if(first_match){
                memset(rightLetterAndPlace, '#', k+1);
			    memset(rightLetterWrongPlace, '#', k*k);
			    memset(wrongLetters, '#', 64);
			    memset(letterOccurrence, '#', k+1);
			    memset(minimumNumber, 0, (k+1)*4);
			    memset(perfectCount, 0, (k+1)*4);
            }else{
                for(int i = 0; rightLetterAndPlace[i] != '#'; i++){
                    rightLetterAndPlace[i] == '#';
                }
                for(int i = 0; rightLetterWrongPlace[i] != '#'; i++){
                    rightLetterWrongPlace[i] == '#';
                }
                for(int i = 0; wrongLetters[i] != '#'; i++){
                    wrongLetters[i] == '#';
                }
                for(int i = 0; letterOccurrence[i] != '#'; i++){
                    minimumNumber[i] == 0;
                }
                for(int i = 0; letterOccurrence[i] != '#'; i++){
                    perfectCount[i] == 0;
                }
                for(int i = 0; letterOccurrence[i] != '#'; i++){
                    letterOccurrence[i] == '#';
                }
            }

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
        }
        if (first_match){
            first_match = 0;
        }
        fscanf(stdin, "%s", string);
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
            if (string[i] > x->word[i]){
                l_r = 'r';
                break;
            }else if (string[i] < x->word[i]){
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
    int n_char_reference = 0;
    int n_char_right_reference = 0;
    int diff_cont = 0;
    int plus = 0;
    int j;
    char flag = '0';
    char result[k], x[k];
    
    for (int i = 0; i < k; i++) {
        if (result[i] != '+'){
            if (string[i] == reference[i] ) {
                result[i] = '+';
                plus++;
                for (j = 0; rightLetterAndPlace[j] != '#'; j++){
                    if (rightLetterAndPlace[j] == string[i] && goodPosition[j] == i){
                        break;
                    }
                }if (rightLetterAndPlace[j] == '#'){
                    rightLetterAndPlace[j] = string[i];
                    goodPosition[j] = i;
                }
            } else {
                for (j = 0; j < k; j++) {
                    if (flag == '0' && string[k-j-1] == string[i] && reference[k-j-1] != string[k-j-1] && x[k-j-1] != 'x'){              //potrei mettere if j>i al posto del flag
                        x[k-j-1] = 'x';
                        flag = '1';
                    }
                    if (reference[j] == string[i]) {         //potrei mettere && j != i??
                        n_char_reference++;
                        if (reference[j] == string[j]) {        //forse potrei mettere if (result[j] == '+')????
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
                    if (n_char_reference != 0 && x[i] == 'x'){
                        for (j = 0; letterOccurrence[j] != '#'; j++){
                            if (letterOccurrence[j] == string[i] && perfectCount[j] == 0){
                                break;
                            }
                        }if (letterOccurrence[j] == '#'){
                            letterOccurrence[j] = string[i];
                            perfectCount[j] = n_char_right_reference + diff_cont;
                        }else{
                            perfectCount[j] = n_char_right_reference + diff_cont;
                            minimumNumber[j] = 0;
                        }
                    }
                } else {
                    result[i] = '|';
                    if (x[i] == 'x'){
                        for (j = 0; letterOccurrence[j] != '#'; j++){
                            if (letterOccurrence[j] == string[i]){
                                    break;
                            }
                        }if (letterOccurrence[j] == '#'){
                            letterOccurrence[j] = string[i];
                            minimumNumber[j] = n_char_right_reference + diff_cont + 1;
                        }else{
                            if (minimumNumber[j] != 0 && minimumNumber[j] < n_char_right_reference + diff_cont + 1){
                                minimumNumber[j] = n_char_right_reference + diff_cont + 1;
                            }
                        }
                    }  
                }

                if (n_char_reference == 0){
                    for (j = 0; wrongLetters[j] != '#'; j++){
                        if (wrongLetters[j] == string[i]){
                            break;
                        }
                    }if (wrongLetters[j] == '#'){
                        wrongLetters[j] = string[i];
                    }
                }else{
                    for (j = 0; rightLetterWrongPlace[j] != '#'; j++){
                        if (rightLetterWrongPlace[j] == string[i] && halfGoodPosition[j] == i){
                            break;
                        }
                    }if (rightLetterWrongPlace[j] == '#'){
                        rightLetterWrongPlace[j] = string[i];
                        halfGoodPosition[j] = i;
                    }
                }
                n_char_reference = 0;
                n_char_right_reference = 0;
                diff_cont = 0;
                flag = '0';
            }
        }else{
            for (j = 0; rightLetterAndPlace[j] != '#'; j++){
                if (rightLetterAndPlace[j] == string[i] && goodPosition[j] == i){
                    break;
                }
            }if (rightLetterAndPlace[j] == '#'){
                rightLetterAndPlace[j] = string[i];
                goodPosition[j] = i;
            }
        }
    }

    if (plus == k) {
		return 1;
    }

    result[k] = '\0';
    fprintf(stdout, "%s\n", result);
    return 0;

}