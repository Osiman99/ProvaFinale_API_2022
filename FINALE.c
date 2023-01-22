#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
	char * string;     
	struct node *right, *left, *next;
	char available;
} Node;

void insertNode(Node *node);
void printFilteredWords(Node *x);
void countWords(char string[]);
int findNode(char string[]);
int compareWord(char string[], char *change);
int filterWord(Node *node);
int myStrcmp(const char* s1, const char* s2);
Node* createNode(char string[]);
//void printTree(Node *x);

int k, number_available;
Node *root, *last_not_available, *available;
Node *not_available = NULL;
Node *last_available = NULL;
char reference[10], *rightLetterAndPlace, *rightLetterWrongPlace, *wrongLetters, *letterOccurrence;
int *goodPosition, *halfGoodPosition, *minimumNumber, *perfectCount;

int main(){
    int attempts, count, end;
    char first_match = '1';
    char string[10];
    Node *node = NULL;

    fscanf(stdin, "%d\n%s", &k, string);

    rightLetterWrongPlace = malloc(sizeof(char) * k*k);
	rightLetterAndPlace = malloc(sizeof(char) * (k+1));
	minimumNumber = malloc(sizeof(int) * (k+1));
	goodPosition = malloc(sizeof(int) * (k+1));
	letterOccurrence = malloc(sizeof(char) * (k+1));
	halfGoodPosition = malloc(sizeof(int) * k*k);
	perfectCount = malloc(sizeof(int) * (k+1));
	wrongLetters = malloc(sizeof(char) * 64);

    while (string[0] != '+'){
        node = createNode(string);
        insertNode(node);
        if (last_available != NULL){
            last_available->next = node;
        }
        last_available = node;
        fscanf(stdin, "%s", string);
    }

    available = root;
    first_match = '1';

    while (1){
        if(string[1] == 'n'){
            end = 0;
            count = 0;
            if(first_match == '1'){
                memset(rightLetterAndPlace, '#', k+1);
			    memset(rightLetterWrongPlace, '#', k*k);
			    memset(wrongLetters, '#', 64);
			    memset(letterOccurrence, '#', k+1);
			    memset(minimumNumber, 0, (k+1)*4);
			    memset(perfectCount, 0, (k+1)*4);
            }else{
                Node *tmp;
			    tmp = not_available;                 
			    while (tmp != NULL) {                
			    	tmp->available = 'v';            
			    	tmp = tmp->next;                 
			    }                                    
                last_available->next = not_available;
                last_available = last_not_available; 
                not_available = NULL;  
                for(int i = 0; rightLetterAndPlace[i] != '#'; i++){
                    rightLetterAndPlace[i] = '#';
                }
                for(int i = 0; rightLetterWrongPlace[i] != '#'; i++){
                    rightLetterWrongPlace[i] = '#';
                }
                for(int i = 0; wrongLetters[i] != '#'; i++){
                    wrongLetters[i] = '#';
                }
                for(int i = 0; letterOccurrence[i] != '#'; i++){
                    minimumNumber[i] = 0;
                }
                for(int i = 0; letterOccurrence[i] != '#'; i++){
                    perfectCount[i] = 0;
                }
                for(int i = 0; letterOccurrence[i] != '#'; i++){
                    letterOccurrence[i] = '#';
                }
            }

            fscanf(stdin, "%s\n%d\n%s", reference, &attempts, string);
            while (!end){
                if (string[0] == '+'){
                    if (string[1] == 'i'){
                        fscanf(stdin, "%s", string);
                        while(string[0] != '+'){
                            node = createNode(string);
                            insertNode(node);
                            if (filterWord(node)){
                                last_available->next = node;
                                last_available = node;
                                number_available++;
                            }else{
                                node->next = last_not_available->next;
                                last_not_available->next = node;
                            }
                            fscanf(stdin, "%s", string);
                        }
                    }else{
                        printFilteredWords(root);
                    }
                }else{    
                    if(!findNode(string)){
                        fprintf(stdout, "not_exists\n");
                    }else{
                        char change;
                        change = '0';
                        if (!compareWord(string, &change)){
                            if (change == '1'){
                                countWords(string);
                            }
                            fprintf(stdout, "%d\n", number_available);
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
                node = createNode(string);
                insertNode(node);
                last_available->next = node;
                last_available = node;
                fscanf(stdin, "%s", string);
            }
        }
        if (first_match == '1'){
            first_match = '0';
        }
        fscanf(stdin, "%s", string);
    }
    //printTree(root);
    return 0;
}

void printFilteredWords(Node *x){
    if (x != NULL){
        printFilteredWords(x->left);
        if (x->available != 'x'){
            fprintf(stdout, "%s\n", x->string);
        }
        printFilteredWords(x->right);
    }
}

int myStrcmp(const char* s1, const char* s2){
	while (*s1 && (*s1==*s2))
	s1++,s2++;
	return *(const unsigned char*)s1 -*(const unsigned char*)s2;
}

Node* createNode(char string[]){
	Node *node = malloc(sizeof(Node) + (sizeof(char) * (k+1)));
        
    node->right = NULL;
    node->left = NULL;
    node->string = (char *)&(node->string) + sizeof(Node);
    for (int i = 0; i < k; i++) {
        node->string[i] = string[i];
    }
    node->string[k] = '\0';
	return node;
}
/*void printTree(Node *x){
    if (x != NULL){
        printTree(x->left);
        fprintf(stdout, "%s\n", x->string);
        printTree(x->right);
    }
}*/

void insertNode(Node *node){
    Node *x, *y;
    int compare;
    
    y = NULL;
    x = root;
    while (x != NULL){
        y = x;
        compare = myStrcmp(node->string, x->string);
        if (compare < 0){
            x = x->left;
        }else{
            x = x->right;
        }

    }if (y == NULL){
        root = node;
    }else if (compare < 0){
        y->left = node;
    }else {
        y->right = node;
    }
}

int findNode(char string[]){
    Node *x;
    int compare;
    
    x = root;
    while (x != NULL){
        compare = myStrcmp(string, x->string);
        if (compare < 0){
            x = x->left;
        }else if (compare > 0){
            x = x->right;
        }else{
			return 1;
        }
    }return 0;
}

int compareWord(char string[], char *change){
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
                    *change = '1';
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
                            *change = '1';
                        }else{
                            perfectCount[j] = n_char_right_reference + diff_cont;
                            minimumNumber[j] = 0;
                            *change = '1';
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
                            *change = '1';
                        }else{
                            if (minimumNumber[j] != 0 && minimumNumber[j] < n_char_right_reference + diff_cont + 1){
                                minimumNumber[j] = n_char_right_reference + diff_cont + 1;
                                *change = '1';
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
                        *change = '1';
                    }
                }else{
                    for (j = 0; rightLetterWrongPlace[j] != '#'; j++){
                        if (rightLetterWrongPlace[j] == string[i] && halfGoodPosition[j] == i){
                            break;
                        }
                    }if (rightLetterWrongPlace[j] == '#'){
                        rightLetterWrongPlace[j] = string[i];
                        halfGoodPosition[j] = i;
                        *change = '1';
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
                *change = '1';
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

int filterWord(Node *node){
    int sum = 0;

    for (int i = 0; rightLetterAndPlace[i] != '#'; i++){
        if(rightLetterAndPlace[i] != node->string[goodPosition[i]]){
            node->available = 'x';
            return 0;
        }
    }
    for (int i = 0; rightLetterWrongPlace[i] != '#'; i++){
        if (rightLetterWrongPlace[i] == node->string[halfGoodPosition[i]]){
            node->available = 'x';
            return 0;
        }
    }
    for (int i = 0; wrongLetters[i] != '#'; i++){
        for (int j = 0; j < k; j++){
            if(wrongLetters[i] == node->string[j]){
                node->available = 'x';
                return 0;
            }
        }
    }
    for (int i = 0; letterOccurrence[i] != '#'; i++){
        if (minimumNumber[i] != 0){
            for (int j = 0; j < k; j++){
                if (letterOccurrence[i] == node->string[j]){
                    sum++;
                }
            }if (sum < minimumNumber[i]){
                node->available = 'x';
                return 0;
            }
        }else{
            for (int j = 0; j < k; j++){
                if (letterOccurrence[i] == node->string[j]){
                    sum++;
                }
                if (sum > perfectCount[i]){
                    node->available = 'x';
                    return 0;
                }
            }if (sum != perfectCount[i]){
                node->available = 'x';
                return 0;
            }
        }
        sum = 0;
    }
    return 1;
}

void countWords(char string[]){
    Node *current, *previous;
    char flag = '0';

    number_available = 0;
    current = available;
    previous = NULL;
    if (not_available == NULL){
        flag = '1';
    }
    while (current != NULL){
        if(!filterWord(current)){
            if (previous == NULL){
                available = current->next;
                if (flag == '1'){
                    current->next = not_available;
                    not_available = current;
                    flag = '0';
                }else{
                    current->next = last_not_available->next;
                    last_not_available->next = current;
                }
                last_not_available = current;
                current = available;
            }else{
                if (current == last_available){
                    last_available = previous;
                }
                previous->next = current->next;
                if (flag == '1'){
                    current->next = not_available;
                    not_available = current;
                    flag = '0';
                }else{
                    current->next = last_not_available->next;
                    last_not_available->next = current;
                }
                last_not_available = current;
                current = previous->next;
            }
        }else{
            number_available++;
            previous = current;
            current = current->next;
        }
    }
}