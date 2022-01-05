# RED-BLACK_TREE

### 1. 개요
+ 레드 블랙 트리를 통해 자료의 삽입과, 삭제, 검색을 수행 할 때  일정한 처리 속도를 보장한다.
+ 개발 환경 - C, C++ 개발 환경 / Windows 10 64 bits, Visual Studio 2019
  - 대학 과제로 만든 RED-BLACK TREE 라서 여러 기능이 추가되어 있을 수 있습니다.

### 정의된 기능

``` C++
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
```
<HR>

### FUNCTION

> 현재 색깔을 얻는 함수
```C++
  int FindColor(Node* node) {

      /* NULL 노드일 경우 BLACK 반환 */
      if (node == NULL)
          return BLACK;

      return node->color;
  }
  ```
  > 노드의 색깔을 칠하는 함수
  ``` C++
  void SetColor(Node* node, int color) {
      if (node == NULL)
          return;

      node->color = color;
  }
```
> 노드의 깊이를 확인하는 함수
``` C++
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
```
> 입력받은 값이 중복인지 체크하는 함수
``` C++
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
```
> 삽입 부분
``` C++
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
```
> 입혁받은 노드 삽입 함수
``` C++
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
```
> 노드를 검색하는 함수
``` C++
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
```
> 삽입되어 있는 값의 내용을 수정하는 함수
``` C++
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
```
> FIX 하는 함수
``` C++
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
```

<HR>

### 사용방법
  
![제목 없음](https://user-images.githubusercontent.com/93738662/148175173-64305a02-19d3-4897-9928-cad181caaac5.png)

1. 처음은 TEST CASE 수를 입력 받는다
2. 그 후 I를 통해 노드를 입력받아 트리를 만든다.

### 명령어

+ F ID
  - FIND 기능
+ R ID NAME SIZE PRICE
  - UPDATE 기능
+ D RANGE1 RANGE2 PERCENT
  - 범위A ~ 범위B의 노드들의 가격 할인율은 변경한다

<HR>

### 평가 및 개선 방향

+ 구현한 알고리즘의 장점으로는 자료를 삽입, 검색, 삭제 할 때 최악의 경우에도 일정한 시간을 보장하는 것과 몇 개의 조건에 따라 균형 있게 만들어지기 때문에 무너지지 않는 장점이 있는 것 같다. 또한 노드의 색깔로 인한 구분으로 인하여 사용하자가 보다 트리의 구조를 설명할 때 이해하기 편하다는 장점도 있는 것 같다.
+ 단점으로는 범위가 주어진 노드를 수정할시 최악의 경우 O(logN)이 아닌 O(N)이 걸린다는 단점이 있었고, 또 다른 하나는 깊이를 탐색할 때 깊이를 탐색하는 함수를 또 다시 호출하는 문제점이 있었다. 이럴 경우 탐색이 끝난 후에 깊이를 출력하기 위하여 다시 탐색을 해야 한다는 단점이 존재하였다.

+ 향후 추후 개선방향으로는 범위가 주어진 노드에 대해 O(N)보다 더 작은 수행시간이 가능한지에 대한 알고리즘을 분석해보고, 깊이를 탐색할 때 현재 함수 내 에서 깊이탐색 함수를 호출하여 실행하는 것이 아닌 탐색하면서 깊이의 값을 저장하면서 마지막에 출력하는 방식의 코드로 수정해야 한다고 생각한다.
