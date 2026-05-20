#include <iostream>

using namespace std;

class List; // 前向引用声明

class Node
{
    int info; // 数据域
    Node *link;
    // 指针域，尖括号中是参数名表，类模板实例化为类
public:
    Node();                    // 生成头结点的构造函数
    Node(const int &data);     // 生成一般结点的构造函数
    void InsertAfter(Node *p); // 在当前结点后插入一个结点
    Node *RemoveAfter();       // 删除当前结点的后继结点
    friend class List;
    // 以List为友元类，List可直接访问Node的私有函数
};
Node::Node()
{
    link = NULL;
}
Node::Node(const int &data)
{
    info = data;
    link = NULL;
}
void Node::InsertAfter(Node *p)
{
    p->link = link; // 把p连接到后面节点
    link = p;       // 把p放到当前节点后面
}
Node *Node::RemoveAfter()
{
    Node *tempP = link; // 留住这个节点返回，未真正删除
    if (link == NULL)
        tempP = NULL; // 已在链尾,后面无结点
    else
        link = tempP->link; // 跨过一个后面的节点
    return tempP;
}

class List
{
private:
    Node *head, *tail;

public:
    List();
    ~List();
    void MakeEmpty();           // 清空链表，只余表头结点
    int Find(int data);         // 搜索数据域与data相同的结点，返回
    int Length();               // 计算单链表长度
    void PrintList();           // 打印链表的数据域
    void InsertFront(int data); // 可用来向前生成链表
    void InsertRear(int data);  // 可用来向后生成链表
    void InsertOrder(int data); // 按升序生成链表
    Node *CreatNode(int data);  // 创建结点(孤立结点)
    void DeleteNode(int index); // 删除指定结点
};

List::List()
{
    head = tail = new Node();
}

List::~List()
{
    MakeEmpty();
    delete head;
}

void List::MakeEmpty()
{
    Node *tempP;
    while (head->link != nullptr) {
        tempP = head->link;
        head->link = tempP->link;
        // 把头结点后的第一个结点从链中脱离
        delete tempP;
    } // 删除(释放)脱离下来的结点
    tail = head;
} // 表头指针与表尾指针均指向表头结点，表示空链

int List::Find(int data)
{
    int idx = 1;
    Node *tempP = head->link;
    // 防止跳过尾节点和空链表崩溃
    while (tempP != nullptr && tempP->info != data) {
        tempP = tempP->link;
        idx++;
    }
    return (tempP == nullptr) ? -1 : idx;
}

int List::Length()
{
    int len = 0;
    Node *tempP = head->link;
    while (tempP != nullptr) {
        tempP = tempP->link;
        len++;
    }
    return len;
}

void List::PrintList()
{ // 显示链表
    Node *tempP = head->link;
    while (tempP != NULL) {
        cout << tempP->info << '\t';
        tempP = tempP->link;
    }
    cout << endl;
}

Node *List::CreatNode(int data)
{
    Node *tempP = new Node(data);
    return tempP;
}
void List::InsertFront(int data)
{
    Node *p = new Node(data);
    p->link = head->link;
    head->link = p;
    if (tail == head)
        tail = p;
}
void List::InsertRear(int data)
{
    Node *p = new Node(data);
    p->link = tail->link;
    tail->link = p;
    tail = p;
}

void List::InsertOrder(int data)
{
    Node *p = new Node(data);
    Node *tempP = head;
    while (tempP->link != nullptr && tempP->link->info < data) {
        tempP = tempP->link;
    }
    p->link = tempP->link;
    tempP->link = p;
    if (tempP == tail)
        tail = p;
}

void List::DeleteNode(int index)
{
    if (index < 1)
        return; // 非法索引直接返回
    Node *tempP = head;
    int counter = index - 1;

    // 确保 tempP 停在待删节点的前驱
    while (tempP->link != nullptr && counter > 0) {
        tempP = tempP->link;
        counter--;
    }

    if (tempP->link == nullptr)
        return; // 索引超出链表长度，安全退出

    if (tempP->link == tail)
        tail = tempP; // 更新尾指针
    Node *p = tempP->RemoveAfter();
    delete p;
}

int main()
{
    cout << "Input list: " << endl;
    List forwardList{};
    List backwardList{};
    int arr[16] = {0};
    for (int i = 0; i < 16; i++) {
        int n;
        if (!(cin >> n))
            break;
        arr[i] = n;
        forwardList.InsertFront(n);
        backwardList.InsertRear(n);
    }

    cout << "The forward list: ";
    forwardList.PrintList();
    cout << "The backward list: ";
    backwardList.PrintList();

    cout << "Input the number to delete: ";
    int target;
    cin >> target;

    int idx1 = forwardList.Find(target);
    int idx2 = backwardList.Find(target);
    if (idx1 == -1) {
        cout << "This number does not exist in the list." << endl;
    } else {
        // 先找位置，再按位置删除
        forwardList.DeleteNode(idx1);
        backwardList.DeleteNode(idx2);

        cout << "The forward list after deleting " << target << " : ";
        forwardList.PrintList();
        cout << "The backward list after deleting " << target << " : ";
        backwardList.PrintList();
    }

    forwardList.MakeEmpty();
    backwardList.MakeEmpty();
    for (int i = 0; i < 16; i++) {
        forwardList.InsertOrder(arr[i]);
    }

    cout << "The Ascending order list: ";
    forwardList.PrintList();
    return 0;
}