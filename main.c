#include <stdio.h>
#include <stdlib.h>
#include <mmcobj.h>
#include <math.h>


int chunk;

struct n{
    int data;
    int height;
    struct n * left;
    struct n * right;
}*root = NULL;

typedef struct n node;

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void reverse(int arr[], int low, int high)
{
    if (low < high)
    {
        int temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;

        reverse(arr, low + 1, high - 1);
    }
}
int NodeHeight(struct n *tree){

    int hl,hr;
    hl =tree && tree->left ? tree->left->height:0;
    hr =tree && tree->right ? tree->right->height:0;

    return hl>hr?hl+1:hr+1;
}
int BalanceFactor(struct n* tree){
    int hl,hr;
    hl =tree && tree->left ? tree->left->height:0;
    hr =tree && tree->right ? tree->right->height:0;

    return hl-hr;
}
struct n * LLRotation (struct n *p){
    struct n * pl= p->left;
    struct n * plr =pl->right;

    pl->right = p;
    p->left = plr;
    p->height= NodeHeight(p);
    pl->height= NodeHeight(pl);

    if (root == p )
        root = pl;

    return pl;

}
struct n * LRRotation(struct n *p)
{
    struct n *pl=p->left;
    struct n *plr=pl->right;

    pl->right=plr->left;
    p->left=plr->right;

    plr->left=pl;
    plr->right=p;

    pl->height=NodeHeight(pl);
    p->height=NodeHeight(p);
    plr->height=NodeHeight(plr);

    if(root==p)
        root=plr;
    return plr;
}


node * BuildTree (node *tree , int x) {
    if (tree == NULL) {
        node *root = (node *) malloc(sizeof(node));
        root->left = NULL;
        root->right = NULL;
        root->data = x;
        root->height = 1;
        return root;
    }

    if (tree->data < x) {
        tree->right = BuildTree(tree->right, x);
    } else if (tree->data > x) {
        tree->left = BuildTree(tree->left, x);
    }
    tree->height = NodeHeight(tree);
    if (BalanceFactor(tree) == 2 && BalanceFactor(tree->left) == 1) {
        return LLRotation(tree);
}
    else if (BalanceFactor(tree) == 2 && BalanceFactor(tree->left) == -1) {
        return LRRotation(tree);
    }

    return tree;
}
void search(node * tree){
    if (tree == NULL){
        return;
    }
    search(tree->left);
    printf( " %d",tree->data);
    search(tree->right);


}

    int main() {
    double power = 0.33;
    double depthlevel=0;
    int i=0;
        int counter = 0;
        int num=0;
        FILE *fp = fopen("input.txt", "r");
        while(fscanf(fp, "%d", &num) == 1){
            counter++;
            if (num<0){
                printf("Numbers in tree can't be negative!");
            }
        }
        rewind(fp);
        int list[counter];
        if (counter<16){
            printf("Array length can't be smaller than 16!");
        }
        while(fscanf(fp, "%d", &num) == 1){

            list[i]=num;
            i++;
        }

       insertionSort(list,counter);
        reverse(list,0,counter-1);
        for (int j = 0; j <counter ; ++j) {
           printf(" %d",list[j]);

        }
        //depthlevel = 3 * (floor(log2(counter)/2));


        node * tree = NULL;
        for (int j = 0; j <counter ; ++j) {
            tree = BuildTree(tree,list[j]);
        }


        printf("\nDepth level of BST is %d",tree->height );

        search(tree);
        return 0;
    }
