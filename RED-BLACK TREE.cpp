#include <bits/stdc++.h>

using namespace std;

/* 노드의 색깔을 표시하기 위한 열거형 함수 */
enum Color {
    RED,
    BLACK,
};

/* 함수 선언부 [모든 함수는 여기서 찾기] */
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
    int id; // 필드 ID
    string name; // 필드 이름
    int size; // 필드 용량
    double price; // 필드 가격
    int color; // 노드의 색깔
    Node* left, * right, * parent; // 노드의 부모와 자기 자식의 정보

    Node(int id, string name, int size, int price) {
        this->id = id;
        this->name = name;
        this->size = size;
        this->price = price;

        color = RED; /* 레드 블랙트리의 규칙에 따라 삽입할때는 항상 RED */

        parent = NULL;
        right = NULL;
        left = NULL;
    }
}; Node* root; // 루트 노드를 생성

/* 현재 노드의 색깔이 어떤 것인지 find */
int FindColor(Node* node) {

    /* NULL 노드일 경우 BLACK 반환 */
    if (node == NULL)
        return BLACK;

    return node->color;
}

/* 노드의 색깔을 칠하기 */
void SetColor(Node* node, int color) {
    if (node == NULL)
        return;

    node->color = color;
}

/* 노드의 깊이를 확인하는 함수 */
int Get_Height(Node* node) {
    Node* ptr = root;
    int height = 0; // 노드의 깊이를 저장하는 변수

    /* 루트 노드부터 시작해서 leaf노드를 만날때까지 반복 */
    while (ptr != NULL) {
        if (ptr->id == node->id) { // 현재 노드와 찾고자 하는 노드가 일치할때 height 리턴
            return height;
        }
        else if (ptr->id > node->id) { // 노드의 크기가 작으면 왼쪽으로 이동하고 깊이 ++
            height++;
            ptr = ptr->left;
        }
        else { // 노드의 크기가 크면 오른쪽으로 이동하고 깊이 ++
            height++;
            ptr = ptr->right;
        }
    }
}

/* 입력받은 값이 중복인지 아닌지 체크하는 함수*/
int Duplicate_check(Node* node) {
    Node* ptr = root;
    int height = 0;

    if (root == NULL) {
        return 0;
    }

    /* O(logN) 만큼 노드를 돌면서 중복된 값이 있는지 체크 */
    while (ptr != NULL) {
        if (ptr->id == node->id) {
            cout << height << endl; // 중복된 값을 발견하면 깊이를 출력 후 1을 리턴
            return 1;
        }
        else if (ptr->id > node->id) { // 현재 id값이 작다면 왼쪽으로 이동하여 Search
            height++;
            ptr = ptr->left;
        }
        else { // 현재 id값이 크다면 오른쪽으로 이동하여 Search
            height++;
            ptr = ptr->right;
        }
    }
}

/* 삽입 부분 */
Node* insertRBT(Node* root, Node* node) {
    /* 부모면 부모를 반환 */
    if (root == NULL) { return node; }

    /* 현재 노드의 값보다 부모노드의 값이 더 크면 왼쪽으로 이동 */
    if (node->id < root->id) {
        root->left = insertRBT(root->left, node);
        root->left->parent = root;
    }
    /* 아니고 부모보다 크다면 오른쪽으로 이동 */
    else {
        root->right = insertRBT(root->right, node);
        root->right->parent = root;
    }
    return root;
}

/* 입력받은 노드 삽입 함수 */
void insertNode(int id, string name, int size, int price) {
    Node* node = new Node(id, name, size, price);

    if (Duplicate_check(node) == 1) { // 값이 중복되었다면 함수 종료
        return;
    }
    else {
        root = insertRBT(root, node); /* FixRBTree를 통해 레드블랙트리 조건에 맞게 수정 */
        
        FixRBTree(node);
        
        
        /*preorderBST(root);*/

        cout << Get_Height(node) << endl; /* Fix 수행후 현재노드의 깊이를 탐색 */
    }
}

/* 찾고자 하는 노드를 검색하는 함수 */
void Search_Application(int id) {
    Node* ptr = root;

    /* 부모 노드부터 시작해서 leaf 노드 만날때까지 반복 */
    while (ptr != NULL) {
        if (ptr->id == id) { // 찾았으면 깊이, 필드명, 용량, 가격 출력
            cout << Get_Height(ptr) << ' ' << ptr->name << ' ' << ptr->size << ' ' << ptr->price << endl;
            return;
        }
        else if (ptr->id > id) { // 왼쪽으로 서치
            ptr = ptr->left;
        }
        else { // 오른쪽으로 서치
            ptr = ptr->right;
        }
    }
    /* 찾는 값이 없을 경우 NULL 출력 후 종료 */
    cout << "NULL" << endl;
}

/* Fix 하는 함수 */
/*
1) 부모노드가 빨간색이고, 삼촌노드도 빨간색일경우
2) 부모노드가 빨간색이고, 삼촌노드가 검은색이고, 현재 노드가 우측일경우
3) 부모노드가 빨간색이고, 삼촌노드가 검은색이고, 현재 노드가 좌측일경우

제가 작성한 코드에는 총 4가지의 경우의 수가 있습니다.

IF{
    1) 조부모 - 부모 는 오른쪽 방향이지만, 자식은 왼쪽 방향일 경우
    2) 조부모 - 부모 - 자식이 모두 오른쪽 방향일 경우
}
ELSE{
    3) 조부모 - 부모는 왼쪽방향이지만, 자식은 오른쪽 방향일 경우
    4) 조부모 - 부모 - 자식이 모두 왼쪽 방향 
}
마지막에는 root에 노드를 항상 BLACK으로 처리
*/

void FixRBTree(Node* node) {
    /* Restruct 와 Recolor를 체크해주기 위해 조상노드와 부모노드를 생성하여 체크 */
    Node* grandparent = NULL;
    Node* parent = NULL;

    /* 루트노드가 아니고, 현재 노드가 빨강이고 내 부모도 빨강일때 계속 Restruct 또는 Recolor 수행 */
    while (node != root && FindColor(node) == RED && FindColor(node->parent) == RED) {

        parent = node->parent; // 내 노드의 부모노드 저장
        grandparent = parent->parent; // 부모노드의 조상노드 저장

        // 조부모의 오른쪽 자식이 부모노드를 가리킬경우
        if (grandparent->right == parent) {

            Node* left_parent_slibing = grandparent->left; // 부모노드의 형제노드의 값을 저장

            /********** 삼촌노드가 BLACK일 경우 RESTURCT 실행 **********/

            if (FindColor(left_parent_slibing) == BLACK) { // 삼촌노드가 BLACK일 경우 RESTRUCT 수행
                
                /* CASE 1 [ 조부모 - 부모 는 오른쪽 방향이지만, 자식은 왼쪽 방향일 경우 ]*/
                if (parent->left == node) {

                    if (grandparent->parent == NULL) { // 조부모의 부모의 노드가 NULL일 경우 (* 즉, 존재하지 않을경우)
                        root = node;    // 루트를 자식노드로 설정
                        node->parent = NULL;    // 루트가 된 자식노드의 부모를 NULL로 만든다 (* ROOT는 부모가 존재하지 않으므로)
                    }
                    else if (grandparent == grandparent->parent->left) {    // 조부모의 부모가 존재할 경우 -> 조부모의 부모의 왼쪽 자식이 조부모일 경우 체크
                        grandparent->parent->left = node;   // 조부모의 부모의 왼쪽 자식을 자식노드로 설정
                        node->parent = grandparent->parent; // 자식노드가 가리키는 부모를 조부모의 부모노드로 설정 한다.
                    }
                    else if (grandparent == grandparent->parent->right) {   // 조부모의 부모가 존재할 경우 -> 조부모의 부모의 오른쪽 자식이 조부모일 경우 체크
                        grandparent->parent->right = node;  // 조부모의 부모의 오른쪽 자식을 자식노드로 설정
                        node->parent = grandparent->parent; // 자식노드가 가리키는 부모를 조부모의 부모노드로 설정 한다.
                    }

                    parent->left = node->right; // 부모의 왼쪽자식을 자식의 오른쪽 노드로 설정
                    if (parent->left != NULL)   // 만약 방금 삽입한 부모의 왼쪽 노드가 NULL이 아니라면, 부모의 왼쪽 노드와 부모를 연결시킴
                        parent->left->parent = parent;

                    grandparent->right = node->left;    // 조부모의 오른쪽자식을 자식의 왼쪽 노드로 설정
                    if (grandparent->right != NULL) // 만약 방금 삽입한 조부모의 오른쪽 노드가 NULL이 아니라면, 부모의 오른쪽 노드와 부모를 연결시킴
                        grandparent->right->parent = grandparent;

                    /* 배치가 완료된 자식 노드 두개를 부모노드에 연결시키는 과정 [ 자식 -> 부모 ]*/
                    parent->parent = node;  // 부모가 가리키는 부모를 자식노드로 설정
                    grandparent->parent = node; // 조부모가 가리키는 부모를 자식노드로 설정

                    /* 배치가 완료된 자식노드 두개를 부모 노드에 연결시키는 과정 [ 부모 -> 자식 ]*/
                    node->left = grandparent;   // 자식노드(부모노드)의 왼쪽 자식노드를 조부모로 설정
                    node->right = parent;   // 자식노드(부모노드)의 오른쪽 자식노드를 부모로 설정

                    swap(node->color, grandparent->color); // 자식노드를 BLACK으로, 조부모노드를 RED로 설정
                }
                /* CASE 2 [ 조부모 - 부모 - 자식이 모두 오른쪽 방향일 경우 ] */
                else {

                    if (grandparent->parent == NULL) {  // 조부모의 부모의 노드가 NULL일 경우 (* 즉, 존재하지 않을 경우) 
                        root = parent;  // 루트를 자식노드로 설정
                        parent->parent = NULL;  // 루트가 된 자식노드의 부모를 NULL로 만든다. (* ROOT는 부모가 존재하지 않으므로)
                    }
                    else if (grandparent == grandparent->parent->left) {    // 조부모의 부모가 존재할 경우 -> 조부모의 부모의 왼쪽 자식이 조부모일 경우 체크
                        grandparent->parent->left = parent; // 조부모의 부모의 왼쪽 자식을 부모노드로 설정
                        parent->parent = grandparent->parent;   // 부모가 가리키는 부모를 조부모노드로 설정
                    }
                    else if (grandparent == grandparent->parent->right) {   // 조부모의 부모가 존재할 경우 -> 조부모의 부모의 오른쪽 자식이 조부모일 경우 체크
                        grandparent->parent->right = parent;    // 조부모의 부모의 오른쪽 자식을 부모노드로 설정
                        parent->parent = grandparent->parent;   // 부모가 가리키는 부모를 조부모노드로 설정
                    }

                    grandparent->right = parent->left;  // 조부모의 오른쪽 자식을 부모의 왼쪽 자식으로 설정
                    if (grandparent->right != NULL) // 만약 방금 삽입한 조부모의 오른쪽 노드가 NULL이 아니라면, 조부모의 오른쪽 노드와 조부모를 연결시킴
                        grandparent->right->parent = grandparent;

                    parent->left = grandparent;    // 부모의 왼쪽 자식노드를 조부모노드로 설정
                    grandparent->parent = parent;   // 조부모노드가 가리키는 부모를 부모노드로 설정

                    swap(parent->color, grandparent->color); // 부모노드를 BLACK으로, 조부모노드를 RED로 설정
                }

            }
            /********** 삼촌노드가 RED일 경우 Recoloring 실행 **********/
            else if (FindColor(left_parent_slibing) == RED)
            {
                SetColor(parent, BLACK);    // 부모노드의 색을 BLACK
                SetColor(left_parent_slibing, BLACK);   // 형제노드의 색을 BLACK
                SetColor(grandparent, RED); // 조부모노드의 색을 RED
                node = grandparent; /* 다시 조상노드부터 DOUBLE RED를 체크 */
            }
        }

        // 조부모의 왼쪽 자식이 부모노드 노드를 가리킬경우
        else if (grandparent->left == parent) {

            Node* right_parent_slibing = grandparent->right; // 부모노드의 형제노드의 값을 저장


            /********** 삼촌노드가 BLACK일 경우 RESTURCT 실행 **********/

            if (FindColor(right_parent_slibing) == BLACK) { // 삼촌노드가 BLACK일 경우 RESTRUCT 수행

                /* CASE 3 [ 조부모 - 부모는 왼쪽방향이지만, 자식은 오른쪽 방향일 경우 ] */
                if (parent->right == node) {

                    if (grandparent->parent == NULL) {  // 조부모의 부모의 노드가 NULL일 경우 (* 즉, 존재하지 않을경우)
                        root = node;    // 루트를 자식노드로 설정
                        node->parent = NULL;    // 루트가 된 자식노드의 부모를 NULL로 만든다. (* ROOT는 부모가 존재하지 않으므로)
                    }
                    else if (grandparent == grandparent->parent->left) {    // 조부모의 부모의 왼쪽 자식을 자식노드로 설정
                        grandparent->parent->left = node;   // 조부모의 부모의 왼쪽 자식을 자식노드로 설정
                        node->parent = grandparent->parent; // 자식노드가 가리키는 부모를 조부모의 부모노드로 설정 한다.
                    }
                    else if (grandparent == grandparent->parent->right) {   // 조부모의 부모가 존재할 경우 -> 조부모의 부모의 오른쪽 자식이 조부모일 경우 체크
                        grandparent->parent->right = node;  // 조부모의 부모의 오른쪽 자식을 자식노드로 설정
                        node->parent = grandparent->parent; // 자식노드가 가리키는 부모를 조부모의 부모노드로 설정 하낟.
                    }

                    parent->right = node->left; // 부모의 오른쪽자식을 자식의 왼쪽 노드로 설정
                    if (parent->right != NULL)  // 만약 방금 삽입한 부모의 왼쪽 노드가 NULL이 아니라면, 부모의 오른쪽 노드와 부모를 연결시킴
                        parent->right->parent = parent;

                    grandparent->left = node->right;    // 조부모의 왼쪽자식을 자식의 왼쪽 노드로 설정
                    if (grandparent->left != NULL)  // 만약 방금 삽입한 조부모의 오른쪽 노드가 NULL이 아니라면, 부모의 오른쪽 노드와 부모를 연결시킴
                        grandparent->left->parent = grandparent;

                    /* 배치가 완료된 자식 노드 두개를 부모노드에 연결시키는 과정 [ 자식 -> 부모 ] */
                    parent->parent = node;  // 부모가 가리키는 부모를 자식노드로 설정
                    grandparent->parent = node; // 조부모가 가리키는 부모를 자식노드로 설정

                    /* 배치가 완료된 자식 노드 두개를 부모노드에 연결시키는 과정 [ 부모 -> 자식 ] */
                    node->left = parent;    // 자식노드(부모노드)의 왼쪽 자식노드를 조부모로 설정
                    node->right = grandparent;  // 자식노드(부모노드)의 오른쪽 자식노드를 부모로 설정

                    swap(node->color, grandparent->color);  // 자식노드를 BLACK으로, 조부모노드를 RED로 설정
                }
                /* CASE 4 [ 조부모 - 부모 - 자식이 모두 왼쪽 방향  ] */
                else {

                    if (grandparent->parent == NULL) {  // 조부모의 부모의 노드가 NULL일 경우 (* 즉, 존재하지 않을 경우)
                        root = parent;  // 루트를 자식노드로 설정
                        parent->parent = NULL;  // 루트가 된 자식노드의 부모를 NULL로 만든다. (* ROOT는 부모가 존재하지 않으므로)
                    }
                    else if (grandparent == grandparent->parent->left) {    // 조부모의 부모가 존재할 경우 -> 조부모의 부모의 왼쪽 자식이 조부모일 경우 체크
                        grandparent->parent->left = parent; // 조부모의 부모의 왼쪽 자식을 부모노드로 설정
                        parent->parent = grandparent->parent;   // 부모가 가리키는 부모를 조부모노드로 설정
                    }
                    else if (grandparent == grandparent->parent->right) {   // 조부모의 부모가 존재할 경우 -> 조부모의 부모의 오른쪽 자식이 조부모일 경우 체크
                        grandparent->parent->right = parent;    // 조부모의 부모의 오른쪽 자식을 부모노드로 설정
                        parent->parent = grandparent->parent;   // 부모가 가리키는 부모를 조부모노드로 설정
                    }
                    

                    grandparent->left = parent->right;  // 조부모의 왼쪽 자식을 부모의 오른쪽 자식으로 설정
                    if (grandparent->left != NULL)  // 만약 방금 삽입한 조부모의 왼쪽 노드가 NULL이 아니라면, 조부모의 왼쪽 노드와 조부모를 연결시킴
                        grandparent->left->parent = grandparent;

                    parent->right = grandparent;    // 부모의 오른쪽 자식노드를 조부모노드로 설정
                    grandparent->parent = parent;   // 조부모노드가 가리키는 부모를 부모노드로 설정

                    swap(parent->color, grandparent->color); // 부모노드를 BLACK으로, 조부모노드를 RED로 설정

                }
            }
            /********** 삼촌노드가 RED일 경우 Recoloring 실행 **********/
            else if (FindColor(right_parent_slibing) == RED) // 레드라면 Recoloring 수행
            {
                SetColor(parent, BLACK);    // 부모노드의 색을 BLACK
                SetColor(right_parent_slibing, BLACK);   // 형제노드의 색을 BLACK
                SetColor(grandparent, RED); // 조부모노드의 색을 RED
                node = grandparent; /* 다시 조상노드부터 DOUBLE RED를 체크 */
            }
        }
    }
    /* 레드블랙 트리 1조건 : 루트는 항상 BLACK이어야 하므로 */
    SetColor(root, BLACK);
}

/* 입력된 값을 Update 하기 위한 함수 */
void Updata_Application(int id, string name, int size, int price) {
    Node* ptr = root;
    int height = 0; // 깊이를 출력하기 위한 변수

    while (ptr != NULL) {
        if (ptr->id == id) { // 값을 찾았다면 ID,NAME,SIZE,PRICE 수정
            ptr->name = name;
            ptr->size = size;
            ptr->price = price;
            //cout << ptr->id << ' ' << ptr->name << ' ' << ptr->size << ' ' << ptr->price << endl;
            cout << height << endl;
            return;
        }
        else if (ptr->id > id) { // 노드의 값이 작다면 왼쪽으로 이동
            ptr = ptr->left;
            height++;
        }
        else { // 크다면 오른쪽으로 이동
            height++;
            ptr = ptr->right;
        }
    }
    /* 업데이트 할 값이 없다면 NULL 출력 */
    cout << "NULL" << endl;
}

/* A ~ B 의 지정된 범위를 P 의 할인 값으로 적용하는 함수 */
void Sale_ApplicationRBT(Node* node, int first, int last, int percent) {
    if (node == NULL)
        return;

    if (first <= node->id && last >= node->id) { // FIRST ~ LAST 범위 안에 포함된다면 할인율을 적용한 값으로 수정
        node->price = trunc(node->price * ((100 - percent) / double(100)));
    }

    /* 전위순회로 모든 노드를 돌면서 재귀함수 반복 */
    /* 최악의 경우 O(n)
    범위의 값이 루트 기준으로 양방향인 오른쪽과 왼쪽이 될 경우가 있을 수 있으므로 모든 노드를 순회해야 할인율 적용이 가능하다 [ 개인적인 의견 optimal 하지 않음 ]
    */
    Sale_ApplicationRBT(node->left, first, last, percent);
    Sale_ApplicationRBT(node->right, first, last, percent);
}

void Sale_Application(int first, int last, int percent) {
    Sale_ApplicationRBT(root, first, last, percent); // 재귀 함수를 사용하기 위해 호출
}


int main() {
    root = NULL;

    int T; // 테스트 케이스 수
    cin >> T;

    char C; // 실행할 함수를 입력할 값

    int id; // 필드 ID
    string name; // 필드명
    int size; // 필드 용량
    int price; // 필드 가격

    while (T--) {
        cin >> C;

        if (C == 'I') { // 삽입 명령어
            cin >> id >> name >> size >> price;
            insertNode(id, name, size, price);
        }
        else if (C == 'F') { // 검색 명령어
            cin >> id;
            Search_Application(id);
        }
        else if (C == 'R') { // 수정 명령어
            cin >> id >> name >> size >> price;
            Updata_Application(id, name, size, price);
        }
        else if (C == 'D') { // 할인율 반영 명령어
            int range_first, range_last, discount_rate;
            cin >> range_first >> range_last >> discount_rate;
            Sale_Application(range_first, range_last, discount_rate);
        }
        else
            break;
    }
    return 0;
}