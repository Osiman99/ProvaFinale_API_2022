#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
	char *string;     
	struct node *right, *left, *next;
	char available;
} Node;

typedef struct lists {
    Node *available, *last_available, *not_available, *last_not_available;
    int number_available;
} Lists;

typedef enum {
    false, true
} bool;

void insertNode(Node *node, Node **root);
Node *delWord(Node *root, char word[], int len);
void printFilteredWords(Node *x);
void countWords(char string[], Lists *lists);
bool findNode(char string[], Node **root);
bool compareWord(char string[], char *change);
bool filterWord(Node *node);
int myStrcmp(const char* s1, const char* s2);
int readLine(char string[]);
Node* createNode(char string[]);
void printTree(Node *x);

int len;
char reference[20], *rightLetterAndPlace, *rightLetterWrongPlace, *wrongLetters, *letterOccurrence;
int *goodPosition, *halfGoodPosition, *minimumNumber, *perfectCount;

int main(){
    clock_t start, endo;
	double execution_time;
	start = clock();

    int attempts, count, end;
    int eof = 0;
    char first_match = '1';
    char start_program = '1';
    char string[20];
    Node *root = NULL;
    Node *node = NULL;
    Lists *lists;

    while (eof != EOF){
        if (start_program == '1'){                                                             //farlo in altro modo? solo se non passing upto18
            readLine(string);
            len = atoi(string);
            eof = readLine(string);

            rightLetterWrongPlace = malloc(sizeof(char) * len*len);
	        rightLetterAndPlace = malloc(sizeof(char) * (len+1));
	        minimumNumber = malloc(sizeof(int) * (len+1));
	        goodPosition = malloc(sizeof(int) * (len+1));
	        letterOccurrence = malloc(sizeof(char) * (len+1));
	        halfGoodPosition = malloc(sizeof(int) * len*len);
	        perfectCount = malloc(sizeof(int) * (len+1));
	        wrongLetters = malloc(sizeof(char) * 64);

            lists = malloc(sizeof(Lists));
            lists->not_available = NULL;
            lists->last_available = NULL;
            lists->last_not_available = NULL;
            lists->number_available = 0;

            while (string[0] != '+'){
                node = createNode(string);
                insertNode(node, &root);
                if (lists->last_available != NULL){
                    lists->last_available->next = node;
                }
                lists->number_available++;
                lists->last_available = node;
                eof = readLine(string);
            }

            lists->available = root;
            first_match = '1';
            start_program = '0';
        }
        if(string[1] == 'n'){
            end = 0;
            count = 0;
            if(first_match == '1'){                                           //conviene solo memset o anche for?
                memset(rightLetterAndPlace, '#', len+1);
			    memset(rightLetterWrongPlace, '#', len*len);
			    memset(wrongLetters, '#', 64);
			    memset(letterOccurrence, '#', len+1);
			    memset(minimumNumber, 0, (len+1)*4);
			    memset(perfectCount, 0, (len+1)*4);
            }else{
                Node *tmp;
			    tmp = lists->not_available;                 
			    while (tmp != NULL) {                
			    	tmp->available = 'v';            
			    	tmp = tmp->next;
                    lists->number_available++;                 
			    }                                    
                lists->last_available->next = lists->not_available;
                lists->last_available = lists->last_not_available;
                lists->last_not_available = NULL;
                lists->not_available = NULL;  
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

            eof = readLine(reference);
            readLine(string);
            attempts = atoi(string);
            eof = readLine(string);
            while (!end){
                if (string[0] == '+'){
                    if (string[1] == 'i'){
                        eof = readLine(string);
                        while(string[0] != '+'){
                            node = createNode(string);
                            insertNode(node, &root);
                            if (filterWord(node)){
                                lists->last_available->next = node;
                                lists->last_available = node;
                                lists->number_available++;
                            }else{
                                lists->last_not_available->next = node;            //bisognerebbe inizializzarlo a NULL (?)
                                lists->last_not_available = node;
                            }
                            eof = readLine(string);
                        }
                    }else{
                        printFilteredWords(root);
                    }
                }else{    
                    if(!findNode(string, &root)){
                        fputs("not_exists\n", stdout);
                    }else{
                        char change;
                        change = '0';
                        if (!compareWord(string, &change)){
                            if (change == '1'){
                                countWords(string, lists);
                            }
                            fprintf(stdout, "%d\n", lists->number_available);
                            count++;
                            if(count == attempts){
                                fputs("ko\n", stdout);
                                end = 1;
                            }
                        }else{
                            fputs("ok\n", stdout);
                            end = 1;
                        }
                    }
                }
                if(!end){
                    eof = readLine(string);
                }
            }
            if (first_match == '1'){
                first_match = '0';
            }
        }else{
            eof = readLine(string);
            while(string[0] != '+'){
                node = createNode(string);
                insertNode(node, &root);
                lists->last_available->next = node;
                lists->last_available = node;
                lists->number_available++;
                eof = readLine(string);
            }
        }
        eof = readLine(string);
    }
    endo = clock();
	execution_time = ((double)(endo - start))/CLOCKS_PER_SEC;
	//printf("time -> %f", execution_time);
    //printTree(root);
    return 0;
}

int readLine(char string[]){
    int i;
    char c;

    c = getchar_unlocked();
    for (i = 0; c != '\n' && c != EOF; i++){                //EOF pure, poi lo gestisco in main
        string[i] = c;
        c = getchar_unlocked();
    }
    string[i] = '\0';
    return c;
}

void printFilteredWords(Node *x){
    if (x != NULL){
        printFilteredWords(x->left);
        if (x->available != 'x'){
            fputs(x->string, stdout);
            fputs("\n", stdout);
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
	Node *node = malloc(sizeof(Node) + (sizeof(char) * (len+1)));
        
    node->right = NULL;
    node->left = NULL;
    node->next = NULL;
    node->available = 'v';
    node->string = (char *)&(node->string) + sizeof(Node);                        //indirizzo corretto???
    for (int i = 0; i < len; i++) {
        node->string[i] = string[i];
    }
    node->string[len] = '\0';
	return node;
}

void printTree(Node *x){
    if (x != NULL){
        printTree(x->left);
        fputs(x->string, stdout);
        fputs("\n", stdout);
        printTree(x->right);
    }
}

/*void freeWrongLetters(tree *letters, int k) {
	for (int i=0; i<k; i++){
		freeTree(letters[i]);
	}
}*/

void insertNode(Node *node, Node **root){
    Node *x, *y;
    int compare;
    
    y = NULL;
    x = *root;
    while (x != NULL){
        y = x;
        compare = myStrcmp(node->string, x->string);                    //provare a vedere se è più veloce questa strcmp
        if (compare < 0){
            x = x->left;
        }else{
            x = x->right;
        }

    }if (y == NULL){
        *root = node;
    }else if (compare < 0){
        y->left = node;
    }else {
        y->right = node;
    }
}

bool findNode(char string[], Node **root){
    Node *x;
    int compare;
    
    x = *root;
    while (x != NULL){
        compare = myStrcmp(string, x->string);                      //provare a vedere se è più veloce questa strcmp
        if (compare < 0){
            x = x->left;
        }else if (compare > 0){
            x = x->right;
        }else{
			return true;
        }
    }return false;
}

bool compareWord(char string[], char *change){
    int n_char_reference = 0;
    int n_char_right_reference = 0;
    int diff_cont = 0;
    int plus = 0;
    int j;
    char flag = '0';
    char result[len], x[len];
    memset(result, '0', len);
    result[len] = '\0';
    memset(x, 'v', len);
    
    for (int i = 0; i < len; i++) {
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
                for (j = 0; j < len; j++) {
                    if (flag == '0' && string[len-j-1] == string[i] && reference[len-j-1] != string[len-j-1] && x[len-j-1] != 'x'){              //potrei mettere if j>i al posto del flag
                        x[len-j-1] = 'x';
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
                            if (letterOccurrence[j] == string[i]){
                                break;
                            }
                        }if (letterOccurrence[j] == '#'){
                            letterOccurrence[j] = string[i];
                            perfectCount[j] = n_char_right_reference + diff_cont;
                            *change = '1';
                        }else{
                            if (perfectCount[j] == 0){
                                perfectCount[j] = n_char_right_reference + diff_cont;
                                minimumNumber[j] = 0;
                                *change = '1';
                            }
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

    if (plus == len) {
		return true;
    }

    fputs(result, stdout);
    fputs("\n", stdout);
    return false;

}

bool filterWord(Node *node){
    int sum = 0;

    for (int i = 0; rightLetterAndPlace[i] != '#'; i++){
        if(rightLetterAndPlace[i] != node->string[goodPosition[i]]){
            node->available = 'x';
            return false;
        }
    }
    for (int i = 0; rightLetterWrongPlace[i] != '#'; i++){
        if (rightLetterWrongPlace[i] == node->string[halfGoodPosition[i]]){
            node->available = 'x';
            return false;
        }
    }
    for (int i = 0; wrongLetters[i] != '#'; i++){
        for (int j = 0; j < len; j++){
            if(wrongLetters[i] == node->string[j]){
                node->available = 'x';
                return false;
            }
        }
    }
    for (int i = 0; letterOccurrence[i] != '#'; i++){
        if (minimumNumber[i] != 0){
            for (int j = 0; j < len; j++){
                if (letterOccurrence[i] == node->string[j]){
                    sum++;
                }
            }if (sum < minimumNumber[i]){
                node->available = 'x';
                return false;
            }
        }else{
            for (int j = 0; j < len; j++){
                if (letterOccurrence[i] == node->string[j]){
                    sum++;
                }
                if (sum > perfectCount[i]){
                    node->available = 'x';
                    return false;
                }
            }if (sum != perfectCount[i]){
                node->available = 'x';
                return false;
            }
        }
        sum = 0;
    }
    return true;
}

void countWords(char string[], Lists *lists){
    Node *current, *previous;
    char flag = '0';

    current = lists->available;
    previous = NULL;
    if (lists->not_available == NULL){
        flag = '1';
    }
    while (current != NULL){
        if(!filterWord(current)){
            if (previous == NULL){
                lists->available = current->next;
                if (flag == '1'){
                    current->next = lists->not_available;
                    lists->not_available = current;
                    flag = '0';
                }else{
                    current->next = lists->last_not_available->next;
                    lists->last_not_available->next = current;
                }
                lists->last_not_available = current;
                current = lists->available;
            }else{
                if (current == lists->last_available){
                    lists->last_available = previous;
                }
                previous->next = current->next;
                if (flag == '1'){
                    current->next = lists->not_available;
                    lists->not_available = current;
                    flag = '0';
                }else{
                    current->next = lists->last_not_available->next;
                    lists->last_not_available->next = current;
                }
                lists->last_not_available = current;
                current = previous->next;
            }lists->number_available--;
        }else{
            previous = current;
            current = current->next;
        }
    }
}



/*Node *delWord(Node *root, char word[], int len) {                         //dovrei ricambiare i nomi delle variabili all'interno di questa funzione e sistemare altre cose
	if (root == NULL) return root;

	int cmp = strcmpp(word, root->word);
	
	if (cmp < 0)
		root->left = delWord(root->left, word, k);
	else if (cmp > 0)
		root->right = delWord(root->right, word, k);

	else {
    	if (root->left == NULL) {
			node *temp = root->right;
			free(root->word);
			free(root);
			return temp;
		}else if (root->right == NULL) {
			node *temp = root->left;
			free(root->word);
			free(root);
			return temp;
		}
		node *temp = minValueNode(root->right);
    	//strcpy(root->word, temp->word);
		memcpy(root->word, temp->word, sizeof(char)*k+1);

		root->right = delWord(root->right, temp->word, k);
	}
	return root;
}*/

/*void freeWrongLetters(tree *letters, int k) {                        //vecchio approccio
	for (int i=0; i<k; i++){
		freeTree(letters[i]);
	}
}*/