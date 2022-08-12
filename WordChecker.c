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

struct Node *searchNode(struct Node *root, char str[N]);

int main() {
    int k;
    scanf("%d", &k);

    return 0;
}

struct Node *searchNode(struct Node *root, char str[N]){
    if (root == NULL || strcmp(str, root->str) == 0){
        return root;
    }
    if (strcmp(str, root->str) < 0){
        return searchNode(root->left, str);
    }else{
        return searchNode(root->right, str);
    }
}

