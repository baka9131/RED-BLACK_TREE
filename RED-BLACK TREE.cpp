#include <bits/stdc++.h>

using namespace std;

/* ����� ������ ǥ���ϱ� ���� ������ �Լ� */
enum Color {
    RED,
    BLACK,
};

/* �Լ� ����� [��� �Լ��� ���⼭ ã��] */
/**************************************/
struct Node;

int FindColor(Node*);
void SetColor(Node*, int);

void insertNode(int, string, int, int);
Node* insertRBT(Node*, Node*);
int Duplicate_check(Node*);

void FixRBTree(Node*);

void Search_Application(int);

int Get_Height(Node*);

void Updata_Application(int, string, int, int);

void preorderBST(Node*);

void Sale_ApplicationRBT(Node*, int, int, int);
void Sale_Application(int, int, int);
/**************************************/

struct Node {
    int id; // �ʵ� ID
    string name; // �ʵ� �̸�
    int size; // �ʵ� �뷮
    double price; // �ʵ� ����
    int color; // ����� ����
    Node* left, * right, * parent; // ����� �θ�� �ڱ� �ڽ��� ����

    Node(int id, string name, int size, int price) {
        this->id = id;
        this->name = name;
        this->size = size;
        this->price = price;

        color = RED; /* ���� ��Ʈ���� ��Ģ�� ���� �����Ҷ��� �׻� RED */

        parent = NULL;
        right = NULL;
        left = NULL;
    }
}; Node* root; // ��Ʈ ��带 ����

/* ���� ����� ������ � ������ find */
int FindColor(Node* node) {

    /* NULL ����� ��� BLACK ��ȯ */
    if (node == NULL)
        return BLACK;

    return node->color;
}

/* ����� ������ ĥ�ϱ� */
void SetColor(Node* node, int color) {
    if (node == NULL)
        return;

    node->color = color;
}

/* ����� ���̸� Ȯ���ϴ� �Լ� */
int Get_Height(Node* node) {
    Node* ptr = root;
    int height = 0; // ����� ���̸� �����ϴ� ����

    /* ��Ʈ ������ �����ؼ� leaf��带 ���������� �ݺ� */
    while (ptr != NULL) {
        if (ptr->id == node->id) { // ���� ���� ã���� �ϴ� ��尡 ��ġ�Ҷ� height ����
            return height;
        }
        else if (ptr->id > node->id) { // ����� ũ�Ⱑ ������ �������� �̵��ϰ� ���� ++
            height++;
            ptr = ptr->left;
        }
        else { // ����� ũ�Ⱑ ũ�� ���������� �̵��ϰ� ���� ++
            height++;
            ptr = ptr->right;
        }
    }
}

/* �Է¹��� ���� �ߺ����� �ƴ��� üũ�ϴ� �Լ�*/
int Duplicate_check(Node* node) {
    Node* ptr = root;
    int height = 0;

    if (root == NULL) {
        return 0;
    }

    /* O(logN) ��ŭ ��带 ���鼭 �ߺ��� ���� �ִ��� üũ */
    while (ptr != NULL) {
        if (ptr->id == node->id) {
            cout << height << endl; // �ߺ��� ���� �߰��ϸ� ���̸� ��� �� 1�� ����
            return 1;
        }
        else if (ptr->id > node->id) { // ���� id���� �۴ٸ� �������� �̵��Ͽ� Search
            height++;
            ptr = ptr->left;
        }
        else { // ���� id���� ũ�ٸ� ���������� �̵��Ͽ� Search
            height++;
            ptr = ptr->right;
        }
    }
}

/* ���� �κ� */
Node* insertRBT(Node* root, Node* node) {
    /* �θ�� �θ� ��ȯ */
    if (root == NULL) { return node; }

    /* ���� ����� ������ �θ����� ���� �� ũ�� �������� �̵� */
    if (node->id < root->id) {
        root->left = insertRBT(root->left, node);
        root->left->parent = root;
    }
    /* �ƴϰ� �θ𺸴� ũ�ٸ� ���������� �̵� */
    else {
        root->right = insertRBT(root->right, node);
        root->right->parent = root;
    }
    return root;
}

/* �Է¹��� ��� ���� �Լ� */
void insertNode(int id, string name, int size, int price) {
    Node* node = new Node(id, name, size, price);

    if (Duplicate_check(node) == 1) { // ���� �ߺ��Ǿ��ٸ� �Լ� ����
        return;
    }
    else {
        root = insertRBT(root, node); /* FixRBTree�� ���� �����Ʈ�� ���ǿ� �°� ���� */
        
        FixRBTree(node);
        
        
        /*preorderBST(root);*/

        cout << Get_Height(node) << endl; /* Fix ������ �������� ���̸� Ž�� */
    }
}

/* ã���� �ϴ� ��带 �˻��ϴ� �Լ� */
void Search_Application(int id) {
    Node* ptr = root;

    /* �θ� ������ �����ؼ� leaf ��� ���������� �ݺ� */
    while (ptr != NULL) {
        if (ptr->id == id) { // ã������ ����, �ʵ��, �뷮, ���� ���
            cout << Get_Height(ptr) << ' ' << ptr->name << ' ' << ptr->size << ' ' << ptr->price << endl;
            return;
        }
        else if (ptr->id > id) { // �������� ��ġ
            ptr = ptr->left;
        }
        else { // ���������� ��ġ
            ptr = ptr->right;
        }
    }
    /* ã�� ���� ���� ��� NULL ��� �� ���� */
    cout << "NULL" << endl;
}

/* Fix �ϴ� �Լ� */
/*
1) �θ��尡 �������̰�, ���̳�嵵 �������ϰ��
2) �θ��尡 �������̰�, ���̳�尡 �������̰�, ���� ��尡 �����ϰ��
3) �θ��尡 �������̰�, ���̳�尡 �������̰�, ���� ��尡 �����ϰ��

���� �ۼ��� �ڵ忡�� �� 4������ ����� ���� �ֽ��ϴ�.

IF{
    1) ���θ� - �θ� �� ������ ����������, �ڽ��� ���� ������ ���
    2) ���θ� - �θ� - �ڽ��� ��� ������ ������ ���
}
ELSE{
    3) ���θ� - �θ�� ���ʹ���������, �ڽ��� ������ ������ ���
    4) ���θ� - �θ� - �ڽ��� ��� ���� ���� 
}
���������� root�� ��带 �׻� BLACK���� ó��
*/

void FixRBTree(Node* node) {
    /* Restruct �� Recolor�� üũ���ֱ� ���� ������� �θ��带 �����Ͽ� üũ */
    Node* grandparent = NULL;
    Node* parent = NULL;

    /* ��Ʈ��尡 �ƴϰ�, ���� ��尡 �����̰� �� �θ� �����϶� ��� Restruct �Ǵ� Recolor ���� */
    while (node != root && FindColor(node) == RED && FindColor(node->parent) == RED) {

        parent = node->parent; // �� ����� �θ��� ����
        grandparent = parent->parent; // �θ����� ������ ����

        // ���θ��� ������ �ڽ��� �θ��带 ����ų���
        if (grandparent->right == parent) {

            Node* left_parent_slibing = grandparent->left; // �θ����� ��������� ���� ����

            /********** ���̳�尡 BLACK�� ��� RESTURCT ���� **********/

            if (FindColor(left_parent_slibing) == BLACK) { // ���̳�尡 BLACK�� ��� RESTRUCT ����
                
                /* CASE 1 [ ���θ� - �θ� �� ������ ����������, �ڽ��� ���� ������ ��� ]*/
                if (parent->left == node) {

                    if (grandparent->parent == NULL) { // ���θ��� �θ��� ��尡 NULL�� ��� (* ��, �������� �������)
                        root = node;    // ��Ʈ�� �ڽĳ��� ����
                        node->parent = NULL;    // ��Ʈ�� �� �ڽĳ���� �θ� NULL�� ����� (* ROOT�� �θ� �������� �����Ƿ�)
                    }
                    else if (grandparent == grandparent->parent->left) {    // ���θ��� �θ� ������ ��� -> ���θ��� �θ��� ���� �ڽ��� ���θ��� ��� üũ
                        grandparent->parent->left = node;   // ���θ��� �θ��� ���� �ڽ��� �ڽĳ��� ����
                        node->parent = grandparent->parent; // �ڽĳ�尡 ����Ű�� �θ� ���θ��� �θ���� ���� �Ѵ�.
                    }
                    else if (grandparent == grandparent->parent->right) {   // ���θ��� �θ� ������ ��� -> ���θ��� �θ��� ������ �ڽ��� ���θ��� ��� üũ
                        grandparent->parent->right = node;  // ���θ��� �θ��� ������ �ڽ��� �ڽĳ��� ����
                        node->parent = grandparent->parent; // �ڽĳ�尡 ����Ű�� �θ� ���θ��� �θ���� ���� �Ѵ�.
                    }

                    parent->left = node->right; // �θ��� �����ڽ��� �ڽ��� ������ ���� ����
                    if (parent->left != NULL)   // ���� ��� ������ �θ��� ���� ��尡 NULL�� �ƴ϶��, �θ��� ���� ���� �θ� �����Ŵ
                        parent->left->parent = parent;

                    grandparent->right = node->left;    // ���θ��� �������ڽ��� �ڽ��� ���� ���� ����
                    if (grandparent->right != NULL) // ���� ��� ������ ���θ��� ������ ��尡 NULL�� �ƴ϶��, �θ��� ������ ���� �θ� �����Ŵ
                        grandparent->right->parent = grandparent;

                    /* ��ġ�� �Ϸ�� �ڽ� ��� �ΰ��� �θ��忡 �����Ű�� ���� [ �ڽ� -> �θ� ]*/
                    parent->parent = node;  // �θ� ����Ű�� �θ� �ڽĳ��� ����
                    grandparent->parent = node; // ���θ� ����Ű�� �θ� �ڽĳ��� ����

                    /* ��ġ�� �Ϸ�� �ڽĳ�� �ΰ��� �θ� ��忡 �����Ű�� ���� [ �θ� -> �ڽ� ]*/
                    node->left = grandparent;   // �ڽĳ��(�θ���)�� ���� �ڽĳ�带 ���θ�� ����
                    node->right = parent;   // �ڽĳ��(�θ���)�� ������ �ڽĳ�带 �θ�� ����

                    swap(node->color, grandparent->color); // �ڽĳ�带 BLACK����, ���θ��带 RED�� ����
                }
                /* CASE 2 [ ���θ� - �θ� - �ڽ��� ��� ������ ������ ��� ] */
                else {

                    if (grandparent->parent == NULL) {  // ���θ��� �θ��� ��尡 NULL�� ��� (* ��, �������� ���� ���) 
                        root = parent;  // ��Ʈ�� �ڽĳ��� ����
                        parent->parent = NULL;  // ��Ʈ�� �� �ڽĳ���� �θ� NULL�� �����. (* ROOT�� �θ� �������� �����Ƿ�)
                    }
                    else if (grandparent == grandparent->parent->left) {    // ���θ��� �θ� ������ ��� -> ���θ��� �θ��� ���� �ڽ��� ���θ��� ��� üũ
                        grandparent->parent->left = parent; // ���θ��� �θ��� ���� �ڽ��� �θ���� ����
                        parent->parent = grandparent->parent;   // �θ� ����Ű�� �θ� ���θ���� ����
                    }
                    else if (grandparent == grandparent->parent->right) {   // ���θ��� �θ� ������ ��� -> ���θ��� �θ��� ������ �ڽ��� ���θ��� ��� üũ
                        grandparent->parent->right = parent;    // ���θ��� �θ��� ������ �ڽ��� �θ���� ����
                        parent->parent = grandparent->parent;   // �θ� ����Ű�� �θ� ���θ���� ����
                    }

                    grandparent->right = parent->left;  // ���θ��� ������ �ڽ��� �θ��� ���� �ڽ����� ����
                    if (grandparent->right != NULL) // ���� ��� ������ ���θ��� ������ ��尡 NULL�� �ƴ϶��, ���θ��� ������ ���� ���θ� �����Ŵ
                        grandparent->right->parent = grandparent;

                    parent->left = grandparent;    // �θ��� ���� �ڽĳ�带 ���θ���� ����
                    grandparent->parent = parent;   // ���θ��尡 ����Ű�� �θ� �θ���� ����

                    swap(parent->color, grandparent->color); // �θ��带 BLACK����, ���θ��带 RED�� ����
                }

            }
            /********** ���̳�尡 RED�� ��� Recoloring ���� **********/
            else if (FindColor(left_parent_slibing) == RED)
            {
                SetColor(parent, BLACK);    // �θ����� ���� BLACK
                SetColor(left_parent_slibing, BLACK);   // ��������� ���� BLACK
                SetColor(grandparent, RED); // ���θ����� ���� RED
                node = grandparent; /* �ٽ� ��������� DOUBLE RED�� üũ */
            }
        }

        // ���θ��� ���� �ڽ��� �θ��� ��带 ����ų���
        else if (grandparent->left == parent) {

            Node* right_parent_slibing = grandparent->right; // �θ����� ��������� ���� ����


            /********** ���̳�尡 BLACK�� ��� RESTURCT ���� **********/

            if (FindColor(right_parent_slibing) == BLACK) { // ���̳�尡 BLACK�� ��� RESTRUCT ����

                /* CASE 3 [ ���θ� - �θ�� ���ʹ���������, �ڽ��� ������ ������ ��� ] */
                if (parent->right == node) {

                    if (grandparent->parent == NULL) {  // ���θ��� �θ��� ��尡 NULL�� ��� (* ��, �������� �������)
                        root = node;    // ��Ʈ�� �ڽĳ��� ����
                        node->parent = NULL;    // ��Ʈ�� �� �ڽĳ���� �θ� NULL�� �����. (* ROOT�� �θ� �������� �����Ƿ�)
                    }
                    else if (grandparent == grandparent->parent->left) {    // ���θ��� �θ��� ���� �ڽ��� �ڽĳ��� ����
                        grandparent->parent->left = node;   // ���θ��� �θ��� ���� �ڽ��� �ڽĳ��� ����
                        node->parent = grandparent->parent; // �ڽĳ�尡 ����Ű�� �θ� ���θ��� �θ���� ���� �Ѵ�.
                    }
                    else if (grandparent == grandparent->parent->right) {   // ���θ��� �θ� ������ ��� -> ���θ��� �θ��� ������ �ڽ��� ���θ��� ��� üũ
                        grandparent->parent->right = node;  // ���θ��� �θ��� ������ �ڽ��� �ڽĳ��� ����
                        node->parent = grandparent->parent; // �ڽĳ�尡 ����Ű�� �θ� ���θ��� �θ���� ���� �ϳ�.
                    }

                    parent->right = node->left; // �θ��� �������ڽ��� �ڽ��� ���� ���� ����
                    if (parent->right != NULL)  // ���� ��� ������ �θ��� ���� ��尡 NULL�� �ƴ϶��, �θ��� ������ ���� �θ� �����Ŵ
                        parent->right->parent = parent;

                    grandparent->left = node->right;    // ���θ��� �����ڽ��� �ڽ��� ���� ���� ����
                    if (grandparent->left != NULL)  // ���� ��� ������ ���θ��� ������ ��尡 NULL�� �ƴ϶��, �θ��� ������ ���� �θ� �����Ŵ
                        grandparent->left->parent = grandparent;

                    /* ��ġ�� �Ϸ�� �ڽ� ��� �ΰ��� �θ��忡 �����Ű�� ���� [ �ڽ� -> �θ� ] */
                    parent->parent = node;  // �θ� ����Ű�� �θ� �ڽĳ��� ����
                    grandparent->parent = node; // ���θ� ����Ű�� �θ� �ڽĳ��� ����

                    /* ��ġ�� �Ϸ�� �ڽ� ��� �ΰ��� �θ��忡 �����Ű�� ���� [ �θ� -> �ڽ� ] */
                    node->left = parent;    // �ڽĳ��(�θ���)�� ���� �ڽĳ�带 ���θ�� ����
                    node->right = grandparent;  // �ڽĳ��(�θ���)�� ������ �ڽĳ�带 �θ�� ����

                    swap(node->color, grandparent->color);  // �ڽĳ�带 BLACK����, ���θ��带 RED�� ����
                }
                /* CASE 4 [ ���θ� - �θ� - �ڽ��� ��� ���� ����  ] */
                else {

                    if (grandparent->parent == NULL) {  // ���θ��� �θ��� ��尡 NULL�� ��� (* ��, �������� ���� ���)
                        root = parent;  // ��Ʈ�� �ڽĳ��� ����
                        parent->parent = NULL;  // ��Ʈ�� �� �ڽĳ���� �θ� NULL�� �����. (* ROOT�� �θ� �������� �����Ƿ�)
                    }
                    else if (grandparent == grandparent->parent->left) {    // ���θ��� �θ� ������ ��� -> ���θ��� �θ��� ���� �ڽ��� ���θ��� ��� üũ
                        grandparent->parent->left = parent; // ���θ��� �θ��� ���� �ڽ��� �θ���� ����
                        parent->parent = grandparent->parent;   // �θ� ����Ű�� �θ� ���θ���� ����
                    }
                    else if (grandparent == grandparent->parent->right) {   // ���θ��� �θ� ������ ��� -> ���θ��� �θ��� ������ �ڽ��� ���θ��� ��� üũ
                        grandparent->parent->right = parent;    // ���θ��� �θ��� ������ �ڽ��� �θ���� ����
                        parent->parent = grandparent->parent;   // �θ� ����Ű�� �θ� ���θ���� ����
                    }
                    

                    grandparent->left = parent->right;  // ���θ��� ���� �ڽ��� �θ��� ������ �ڽ����� ����
                    if (grandparent->left != NULL)  // ���� ��� ������ ���θ��� ���� ��尡 NULL�� �ƴ϶��, ���θ��� ���� ���� ���θ� �����Ŵ
                        grandparent->left->parent = grandparent;

                    parent->right = grandparent;    // �θ��� ������ �ڽĳ�带 ���θ���� ����
                    grandparent->parent = parent;   // ���θ��尡 ����Ű�� �θ� �θ���� ����

                    swap(parent->color, grandparent->color); // �θ��带 BLACK����, ���θ��带 RED�� ����

                }
            }
            /********** ���̳�尡 RED�� ��� Recoloring ���� **********/
            else if (FindColor(right_parent_slibing) == RED) // ������ Recoloring ����
            {
                SetColor(parent, BLACK);    // �θ����� ���� BLACK
                SetColor(right_parent_slibing, BLACK);   // ��������� ���� BLACK
                SetColor(grandparent, RED); // ���θ����� ���� RED
                node = grandparent; /* �ٽ� ��������� DOUBLE RED�� üũ */
            }
        }
    }
    /* ����� Ʈ�� 1���� : ��Ʈ�� �׻� BLACK�̾�� �ϹǷ� */
    SetColor(root, BLACK);
}

/* �Էµ� ���� Update �ϱ� ���� �Լ� */
void Updata_Application(int id, string name, int size, int price) {
    Node* ptr = root;
    int height = 0; // ���̸� ����ϱ� ���� ����

    while (ptr != NULL) {
        if (ptr->id == id) { // ���� ã�Ҵٸ� ID,NAME,SIZE,PRICE ����
            ptr->name = name;
            ptr->size = size;
            ptr->price = price;
            //cout << ptr->id << ' ' << ptr->name << ' ' << ptr->size << ' ' << ptr->price << endl;
            cout << height << endl;
            return;
        }
        else if (ptr->id > id) { // ����� ���� �۴ٸ� �������� �̵�
            ptr = ptr->left;
            height++;
        }
        else { // ũ�ٸ� ���������� �̵�
            height++;
            ptr = ptr->right;
        }
    }
    /* ������Ʈ �� ���� ���ٸ� NULL ��� */
    cout << "NULL" << endl;
}

/* A ~ B �� ������ ������ P �� ���� ������ �����ϴ� �Լ� */
void Sale_ApplicationRBT(Node* node, int first, int last, int percent) {
    if (node == NULL)
        return;

    if (first <= node->id && last >= node->id) { // FIRST ~ LAST ���� �ȿ� ���Եȴٸ� �������� ������ ������ ����
        node->price = trunc(node->price * ((100 - percent) / double(100)));
    }

    /* ������ȸ�� ��� ��带 ���鼭 ����Լ� �ݺ� */
    /* �־��� ��� O(n)
    ������ ���� ��Ʈ �������� ������� �����ʰ� ������ �� ��찡 ���� �� �����Ƿ� ��� ��带 ��ȸ�ؾ� ������ ������ �����ϴ� [ �������� �ǰ� optimal ���� ���� ]
    */
    Sale_ApplicationRBT(node->left, first, last, percent);
    Sale_ApplicationRBT(node->right, first, last, percent);
}

void Sale_Application(int first, int last, int percent) {
    Sale_ApplicationRBT(root, first, last, percent); // ��� �Լ��� ����ϱ� ���� ȣ��
}


int main() {
    root = NULL;

    int T; // �׽�Ʈ ���̽� ��
    cin >> T;

    char C; // ������ �Լ��� �Է��� ��

    int id; // �ʵ� ID
    string name; // �ʵ��
    int size; // �ʵ� �뷮
    int price; // �ʵ� ����

    while (T--) {
        cin >> C;

        if (C == 'I') { // ���� ��ɾ�
            cin >> id >> name >> size >> price;
            insertNode(id, name, size, price);
        }
        else if (C == 'F') { // �˻� ��ɾ�
            cin >> id;
            Search_Application(id);
        }
        else if (C == 'R') { // ���� ��ɾ�
            cin >> id >> name >> size >> price;
            Updata_Application(id, name, size, price);
        }
        else if (C == 'D') { // ������ �ݿ� ��ɾ�
            int range_first, range_last, discount_rate;
            cin >> range_first >> range_last >> discount_rate;
            Sale_Application(range_first, range_last, discount_rate);
        }
        else
            break;
    }
    return 0;
}