1.2.cpp                                                                                             0000644 0000000 0000000 00000001755 12124243160 010563  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 1.2
 * Question:Write code to reverse a c-Style String,
 * (C-style means that "abcd" is represented as five characters,including the null character)
 * 反转字符串
 */
#include<iostream>
#include<string.h>
using namespace std;

/*
 * 两种考虑，如果可以使用strlen函数，则可以省略找最后一个字符的工作
 * 否则，需要自己写
 */
void solution(char * str){
    int len = strlen(str);
    int i = 0;
    char temp;
    while(i < len/2){
        temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
        i++;
    }
}

void solution2(char * str) {
    char * end = str;
    char temp;
    while(*end != '\0'){
        end ++;
    }
    end --;
    while(str < end){
        temp = *str;
        *str = *end;
        *end = temp;
        str++;
        end--;
    }
}

int main(){
    char s1[] = "hello world";
    char s2[] = "1234567890";
    solution(s1);
    solution2(s2);
    cout<<s1<<endl;
    cout<<s2<<endl;
    return 0;
}
                   1.3.cpp                                                                                             0000644 0000000 0000000 00000003001 12124243160 010546  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 1.3
 * Question:Design an algorithm and write code to remove the duplication characters in a string
 * without using any addtional buffer. NOTE:One or two addtional variables are fine.
 * An extra copy of the array is not.
 * FOLLOW UP
 * Write the test cases for this method.
 * 设计一个算法，用来移除一个字符串中重复的字符，并且不允许使用任何额外的空间（少量变量可以）
 * 不允许额外的拷贝
 * 接下来，为这个方法写一些测试用例
 */
#include<iostream>
#include<string.h>

using namespace std;
/*
 * 由于不允许使用额外空间，导致不能用1.1中类似的方法判断是否重复
 * 因此，采用遍历枚举的方式，方法如下：
 * 对于str[i]，枚举0～tail之间是否已存在该元素，其中0到tail之间字符不重复
 * 如果存在，则跳过，否则str[tail]更新为新元素str[i]
 */
void solution(char * str){
    if (str == NULL) return ;
    int len = strlen(str);
    int tail = 1;
    int j;
    for(int i=1;i<len;i++){
        for(j=0;j<tail;j++){
            if (str[i] == str[j]) break;
        }
        if(j == tail) {
            str[tail] = str[i];
            tail++;
        }
    }
    str[tail] = '\0';
}

/*
 * Test Cases:
 * 1. 不包含任何重复字符 abcd
 * 2. 所有的字符均重复 aaaa
 * 3. NULL
 * 4. 连续重复的字符串，如aaabbb
 * 5. 非连续重复的字符串 abcabcddeef
 */

int main(){
    char s [] = "abcdeagsdgabc";
    solution(s);
    cout<<s<<endl;
    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               1.4.cpp                                                                                             0000644 0000000 0000000 00000002751 12124243160 010562  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 1.4
 * Question: Write a method to decide if two strings are anagrams or not .
 * 判断两个字符串是否为易位够词，即排序之后相同的两个词
 * http://en.wikipedia.org/wiki/Anagram
 */

#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

/*
 * 通过抽象定义,直接對两个string进行排序，然后判断下就可以了
 * 时间复杂度O(nlogn)
 */

bool solution(char * s1, char * s2){
    sort(s1,s1+strlen(s1));
    sort(s2,s2+strlen(s2));
    int cmp = strcmp(s1,s2);
    if( cmp == 0) return true;
    return false;
}

/*
 * 由于方法1具有数据侵入性，即改遍了s1和s2中原有的数据位置，因此不是很好的解决办法。
 * 利用空间换时间，用char_count统计s1中每个字符出现的次数
 * 然后遍历s2中的每个字符，對char_count进行更新，即对应的char_count减1
 * 如果某个字符对应的char_count减为-1,则判定为false
 * 若字符数不相等也判定为false
 */

bool solution2(char * s1, char * s2){
    int char_count[256] = {0};
    int len1=0,len2=0;
    while(*s1 != '\0') {
        char_count[*s1] ++;
        s1++;
        len1++;
    }
    while(*s2 != '\0') {
        char_count[*s2] --;
        if(char_count[*s2] < 0) return false;
        s2++;
        len2++;
    }
    if(len1 != len2) return false;
    return true;
}

int main(){
    char s1 [] = "hello";
    char s2 [] = "lloeh";
    cout<<solution(s1,s2);
    cout<<solution2(s1,s2);
    return 0;
}
                       1.5.cpp                                                                                             0000644 0000000 0000000 00000003236 12124243161 010563  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 1.5
 * Question:Write a method to replace all spaces in a string with '%20'
 * 写一个方法用'%20'替换字符串中的所有空格
 */
#include<iostream>
#include<string.h>
using namespace std;

/*
 * 这应该算是比较典型的字符串移位的问题
 * 首先，如果我们知道了字符串中包含的space数量count，那么替换后的最终长度比原始长度增加了count*2
 * 在进行替换过程中，如果从头开始替换，势必在替换过程中，需要對后面的字符进行位置移动，显然这是开销很大的。
 * 由于我们已经知道了替换后的最终长度，那么便可以从后往前进行替换，这样不会對前面的字符产生影响。
 * 另外，由于字符串的最终长度增加了，那么在原有内存上进行操作，可能会造成字符串的访问越界。
 * 因此，最好的方法应该时新建一个string，再返回，这样的话，就无所谓替换的顺序了。
 */

void solution(char * str){
    //我们假设str申请的空间很大，不会产生越界问题
    int count = 0;
    int len = 0;
    char * pstr = str;
    while(*pstr != '\0'){
        if (*pstr == ' ') count++;
        len ++;
        pstr++;
    }
    int final_len = len + 2 * count;
    str[final_len] = '\0';
    int pos = final_len - 1;
    int j = len - 1;
    while(j>=0){
        if(str[j] != ' ') str[pos--] = str[j];
        else{
            str[pos - 2] = '%';
            str[pos - 1] = '2';
            str[pos] = '0';
            pos -=3;
        }
        j--;
    }
}

int main(){
    char str [100];
    strcpy(str," hello world python ");
    solution(str);
    cout<<str<<endl;
    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                  1.7.cpp                                                                                             0000644 0000000 0000000 00000002774 12124243161 010573  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Write an algorithm such that if an element in an M*N matrix is 0, its entire row and column is set to 0.
 * 写一个算法用于实现如果一个M*N的矩阵中某个元素为0.则将该行和该列所有元素设置为0
 */
#include<iostream>
using namespace std;

/*
 * 由于，不能在查找0的时候，进行相应行和列的更新0，因为这样会导致整个矩阵变为0矩阵了
 * 那么就需要记录每个0的位置，然后再统一进行行和列的0替换
 * 方法1：开两个数组row[i],column[j]，记录第i行与第j列是否为0
 * 方法2：建立一个struct，记录row 和 column，用链表形式记录，这样可以最小化存储空间
 * 方法3：num = row*MAXCOLUMN + column的方式进行0元素的位置存储
 */


void solution(int arr[][3], int maxcolumns, int maxrows) {
    bool * row = new bool[maxrows]; 
    bool * column = new bool[maxcolumns];
    for(int i=0;i<maxrows;i++){
        for(int j=0;j<maxcolumns;j++){
            if(arr[i][j] == 0){
                row[i] = true;
                column[i] = true;
            }
        }
    }
    for(int i=0;i<maxrows;i++){
        for(int j=0;j<maxcolumns;j++){
            if(row[i] | column[j]) arr[i][j] = 0;
        }
    }
}


int main(){
    int arr[3][3] = {{1,2,3},{4,0,6},{7,8,9}};
    solution(arr,3,3);
    int maxrows = 3;
    int maxcolumns = 3;
    for(int i=0;i<maxrows;i++){
        for(int j=0;j<maxcolumns;j++){
            cout<<arr[i][j]<<'\t';
        }
        cout<<endl;
    }
   
    return 0;
}
    1.8.cpp                                                                                             0000644 0000000 0000000 00000002476 12124243161 010573  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 1.8
 * Question:Assume you have a method isSubstring which checks if one word is substring of 
 * another. Given two strings s1 and s2, write code to check if s2 is a rotation of s1 using
 * only one call to isSubString(i.e."waterbottle" is a rotation of "erbottlewat")
 * 假设你有一个方法可以用来检测一个单词是否为一个另一个的子串。现在给你两个字符串并且只能进行一次substring的调用，判断s2是否为s1的转动形式。
 */

#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;


bool isSubstring(const char * s1, const char * s2){
    assert(s1 != NULL && s2 != NULL);
    return strstr(s1,s2) == NULL ? false : true;
}

/*
 * 首先应该检查s1与s2的长度，如果不想等，则直接判定为false
 * 对于字符串s1，s1s1则包含了s1转动后的所有形式，因此只要用isSubstring判断s2是否为s1s1的子串即可
 */

bool solution(const char * s1, const char * s2){
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if(len1 != len2) return false;
    char * temp = new char[len1*2];
    strcpy(temp,s1);
    strcpy(temp+len1,s1);
    bool res = isSubstring(temp,s2);
    delete [] temp;
    return res;
}
int main(){
    char s1 [] = "waterbottle";
    char s2 [] = "erbotdlewat";
    cout<<solution(s1,s2)<<endl;
}
                                                                                                                                                                                                  2.1.cpp                                                                                             0000644 0000000 0000000 00000002467 12124243161 010565  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 2.1
 * Question:Write code to remove duplicates from an unsorted linked list
 * FOLLOW UP
 * How would you solve this problem if a temporary buffer is not allowed?
 * 从一个无序的链表中移除重复的元素
 * 如果不允许使用额外的临时空间，该如何进行呢？
 */

#include<iostream>
#include<set>
using namespace std;

struct node{
    int value;
    node * next;
    node(int v){
        value = v;
    }
};

void printlink(node * head){
    while(head != NULL){
        cout<<head->value<<"\t";
        head = head->next;
    }
    cout<<endl;
}

node * solution(node * head){
    if (head == NULL) return NULL;
    set<int> valueset;
    node * pre = head;
    node * p = pre->next;
    while(p != NULL){
        if(valueset.count(p->value) == 0){
            valueset.insert(p->value);
            pre = p;
            p = p->next;
        }
        else{
            pre->next = p->next;
            p = p->next;
        }
    }
    return head;
}


int main()
{
    node * head = new node(2);
    node * p = head;
    int arr[] = {1,3,1,5,3,7,3,3,5,5,6,4,4,5,4};
    int length = sizeof(arr) / sizeof(int);
    for(int i=0; i<length ;i++){
        p->next = new node(arr[i]);
        p = p->next;
    }
    printlink(head);
    head = solution(head);
    printlink(head);
    return 0;
}
                                                                                                                                                                                                         2.2.cpp                                                                                             0000644 0000000 0000000 00000002345 12124243161 010561  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 2.2 
 * Question: Implement an algorithm to find nth to last element of a singly linked list.
 * 实现一个算法找到倒数第n个元素
 */

#include<iostream>
using namespace std;

struct node{
    int value;
    node * next;
    node(int v){
        value = v;
    }
};

void printlink(node * head){
    while(head != NULL){
        cout<<head->value<<"\t";
        head = head->next;
    }
    cout<<endl;
}

node * createTestLink(){
    node * head = new node(2);
    node * p = head;
    int arr[] = {1,3,1,5,3,7,3,3,5,5,6,4,4,5,4};
    int length = sizeof(arr) / sizeof(int);
    for(int i=0; i<length ;i++){
        p->next = new node(arr[i]);
        p = p->next;
    }
    return head;
}
/*
 * 设置两个节点指针，第一个先走n步，然后两个一起走，知道第一个到达终点后，第二个所指即为所求。
 */

node * solution(node * head, int n){
    node * pre = head;
    while(n>0){
        pre = pre->next;
        n--;
    }
    node * res = head;
    while(pre!=NULL){
        pre = pre->next;
        res = res->next;
    }
    return res;
} 

int main(){
    node * head = createTestLink();
    printlink(head);
    node * res = solution(head,2);
    cout<<res->value<<endl;
    return 0;
}
                                                                                                                                                                                                                                                                                           2.3.cpp                                                                                             0000644 0000000 0000000 00000003121 12124243161 010553  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 2.3
 * Question:Implement an algorithm to delete a node in the middle of single linked list, given only access to that node.
 * Example
 * Input:the node 'c' from the linked list a->b->c->d->e
 * Output:nothing is returned, but the new linked list looks like a->b->d->e
 * 实现一个算法实现删除一个单链表中间的某个节点，只可以访问待删除的节点。
 * PS:是中间，而不能是最后一个节点。因为，如果要删除的是最后一个节点，那么它的pre节点的next需要设置为NULL，
 * 而只通过待删除节点是找不到它的pre节点的。
 */

#include<iostream>
using namespace std;

struct node {
    char c;
    node * next;
    node (char _c){
        c = _c;
        next = NULL;
    }
};

void printlink(node * head){
    while(head!=NULL){
        cout<<head->c<<"\t";
        head = head->next;
    }
    cout<<endl;
}

/*
 * 这是个已经出烂了的题了，O(1)操作删除指定节点，其原理就是把该节点的下一个节点完全复制过来
 * 其实最终删除的是该节点的下一个节点的内存地址
 */

void solution_deletenode(node * deletenode){
    node * p = deletenode->next;
    deletenode->c = deletenode->next->c;
    deletenode->next = deletenode->next->next;
    delete p;
}

int main()
{
    node * head = new node('a');
    node * b = new node('b');
    node * c = new node('c');
    node * d = new node('d');
    node * e = new node('e');
    head->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    printlink(head);
    solution_deletenode(c);
    printlink(head);
    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                               2.4.cpp                                                                                             0000644 0000000 0000000 00000004401 12124243161 010556  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 2.4
 * Question:You have two numbers represented by linked list, where each node contains a single digit.
 * The digits are stored in reverse order, such that the 1's digit is at the head of the list. 
 * Write a function tha adds the two numbers and returns  the sum as a linked list.
 * Example:
 * Input:(3->1->5) + (5->9->2)
 * Output: 8->0->8
 * 用链表表示的数字（数位的顺序相反），写一个函数用来将两个数字相加求和后返回一个链表
 */

#include<iostream>
using namespace std;

struct node {
    short digit;
    node * next;
    node(short _digit){
        digit = _digit;
        next = NULL;
    }
};
node * constructLink(short s[], int len){
    node * head = new node(s[0]);
    node * p = head;
    for(int i=1; i<len; i++){
        head->next = new node(s[i]);
        head = head->next;
    }
    return p;
}

/*
 * 说白了，这题就是用链表结构实现高精度加法
 * 原来教科书上写的大多用的是数组的形式，这个只不过时变了个存储形式
 */
node * solution_add(node * l1, node * l2){
    node * res = new node(0);
    node * head = res;
    short mod_v=0, div_v=0;
    while(l1!=NULL && l2!=NULL){
        mod_v = (l1->digit + l2->digit + div_v) % 10;
        res->next = new node(mod_v);
        div_v = (l1->digit + l2->digit + div_v) / 10;
        res = res->next;
        l1 = l1->next;
        l2 = l2->next;
    }
    while(l1 != NULL){
        mod_v = (l1->digit + div_v) % 10;
        res->next = new node(mod_v);
        div_v = (l1->digit + div_v) / 10;
        res = res->next;
        l1 = l1->next;
    }
    while(l2 != NULL){
        mod_v = (l2->digit + div_v) % 10;
        res->next = new node(mod_v);
        div_v = (l2->digit + div_v) / 10;
        res = res->next;
        l2 = l2->next;
    }

    if(div_v > 0)
        res->next = new node(div_v);
    return head->next;
}

void printlink(node * head){
    while(head != NULL){
        cout<<head->digit<<"\t";
        head = head->next;
    }
    cout<<endl;
}

int main()
{
    short s1 [] = {1,1,1,1};
    short s2 [] = {9,9,9};
    node * l1 = constructLink(s1,sizeof(s1)/sizeof(short));
    node * l2 = constructLink(s2,sizeof(s2)/sizeof(short));
    node * res = solution_add(l1,l2);
    printlink(res);
    return 0;
}
                                                                                                                                                                                                                                                               2.5.cpp                                                                                             0000644 0000000 0000000 00000000571 12124243161 010563  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 2.5 
 * Question: Given a circular linked list, implement an algotithm 
 * which returns node at the beginning of the loop.
 * DEFINITION
 * Circular linked list: A(corrupt) linked list in which a node's next pointer points
 * to an earlier node, so as to make a loop in the linked list.
 */

#include<iostream>
using namespace std;

int main()
{
    return 0;
}
                                                                                                                                       3.5.cpp                                                                                             0000644 0000000 0000000 00000002355 12124243161 010566  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 3.5
 * Question:Implement a MyQueue class which implements a queue using two stacks.
 * 使用两个栈实现一个队列
 */

#include<iostream>
#include<stack>
using namespace std;

/*
 * 这个是很经典的问题了，不做解释了。
 */
class MyQueue{
    public :
        void push(int e) {
            a.push(e);
        }
        int front(){
            if(b.empty()){
                while(!a.empty()){
                    b.push(a.top());
                    a.pop();
                }
            }
            return b.top();
        }
        void pop(){
            if (b.empty()){
                while(!a.empty()){
                    b.push(a.top());
                    a.pop();
                }
            }
            b.pop();
        }
        bool empty(){
            return (a.empty() && b.empty());
        }
    private :
        stack<int> a,b;
};
int main(){
    int arr[] = {2,1,3,0,8,1,6,9,7};
    int length = sizeof(arr) / sizeof(int);
    MyQueue q;
    for(int i=0;i<length;i++){
        q.push(arr[i]);
    }
    cout<<q.front()<<endl;
    q.pop();
    for(int i=0;i<length;i++){
        q.push(arr[i]);
    }
    while(!q.empty()){
        cout<<q.front()<<endl;
        q.pop();
    }

    return 0;
}
                                                                                                                                                                                                                                                                                   3.6.cpp                                                                                             0000644 0000000 0000000 00000003442 12124243161 010565  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Write a program to sort a stack in ascending order. You should not make any assumptions about
 * how the stack is implemented.The following are the only functions that should be used to write
 * this program:push | pop | peek | isEmpty
 * 写程序实现對一个栈结构的排序。你不必假想这个栈是怎么实现的，你只允许使用栈的基本操作，比如push、pop、peek以及isEmpty
 */
#include<iostream>
#include<stack>
using namespace std;

/*
 * 我们假定题目中的升序是栈顶算起，即弹出的第一个元素应该最小。
 * 由于题目要求只允许使用栈的基本操作，于是，我们可以利用一个辅助栈b。
 * b存储的是有序的，从a中不断pop出元素item与b的top比较，如果改变了b的有序性，
 * 则将b中所有元素push到a中，然后将item push进b的栈底，最后再重复上诉过程。直到a为空为止。
 * 最后再将b中所有元素，push到a中，即完成了對a的排序。
 * 最坏的时间复杂度，为每次都会影响b的有序性，每次都会导致b中元素与a的交换，即为O（n*n）
 */

void stack_sort(stack<int> & a){
    stack<int> b;
    while(!a.empty()){
        int temp = a.top();
        a.pop();
        if (!b.empty() && b.top()>temp){
            while(!b.empty()){
                a.push(b.top());
                b.pop();
            }
        }
        b.push(temp);
    }
    while(!b.empty()) {
        a.push(b.top());
        b.pop();
    }
}
int main(){
    int arr [] = {2,1,3,0,8,1,6,9,7};
    stack<int> a;
    int length = sizeof(arr) / sizeof(int);
    for(int i=0;i<length;i++){
        a.push(arr[i]);
    }
    stack_sort(a);
    while(!a.empty()){
        cout<<a.top()<<endl;
        a.pop();
    }
    return 0;
}
                                                                                                                                                                                                                              3.6.cpp~                                                                                            0000644 0000000 0000000 00000001236 12124243162 010763  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   #include<iostream>
#include<stack>
using namespace std;

void stack_sort(int arr[], int length){
    stack<int> a, b;
    for(int i=0;i<length;i++){
        a.push(arr[i]);
    }
    while(!a.empty()){
        int temp = a.top();
        a.pop();
        if (!b.empty() && b.top()>temp){
            while(!b.empty()){
                a.push(b.top());
                b.pop();
            }
        }
        b.push(temp);
    }
    while(!b.empty()) {
        cout<<b.top()<<endl;
        b.pop();
    }
}
int main(){
    int arr [] = {2,1,3,0,8,1,6,9,7};
    int len = sizeof(arr) / sizeof(int);
    stack_sort(arr,len);
    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                  4.1.cpp                                                                                             0000644 0000000 0000000 00000003112 12124246223 010555  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 4.1
 * Implement a function to check if a tree is balanced. For the purposes of this question,
 * a balanced tree is defined to be a tree such that no two leaf nodes differ in distance
 * from the root by more than one.
 * 实现一个函数用于检查一棵树是否是平衡的。平衡的定义是，两个叶子节点的高度相差不超过1.
 */
#include<iostream>
#include<cmath>
using namespace std; 
struct node {
    int value;
    node * left;
    node * right;
    node(int v){
        value = v;
        left = NULL;
        right = NULL;
    }
};

node * buildtree(int arr[], int low, int high){
    if(low > high) return NULL;
    int mid = (low + high) / 2;
    node * n = new node(arr[mid]);
    n->left = buildtree(arr,low, mid-1);
    n->right = buildtree(arr,mid+1,high);
    return n;
}

void scantree(node * head){
    if(head == NULL) return;
    cout<<head->value<<endl;
    scantree(head->left);
    scantree(head->right);
}

/*
 * 递归求解每棵子树的高度，递归过程中进行平衡性的判断
 */

static bool isbalanced = true;
int checkBalanced(node * n){
    if (n == NULL) return 0;
    int lheight = checkBalanced(n->left);
    int rheight = checkBalanced(n->right);
    if (abs(lheight - rheight) > 1) isbalanced = false;
    return max(lheight,rheight) + 1;
}

bool isBalanced(node * head){
    isbalanced = true;
    checkBalanced(head);
    return isbalanced;
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    node * head = NULL;
    head = buildtree(arr,0,sizeof(arr)/sizeof(int) - 1);
    cout<<isBalanced(head)<<endl;
    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                      4.3.cpp                                                                                             0000644 0000000 0000000 00000001672 12124243162 010567  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Given a sorted (increasing order) array, write an algorithm to create a binary tree with minimal height.
 写一个算法由一个有序的数组创建一个具有最小高度的二叉树
 */

#include<iostream>
using namespace std;
struct node {
    int value;
    node * left;
    node * right;
    node(int v){
        value = v;
        left = NULL;
        right = NULL;
    }
};

node * buildtree(int arr[], int low, int high){
    if(low > high) return NULL;
    int mid = (low + high) / 2;
    node * n = new node(arr[mid]);
    n->left = buildtree(arr,low, mid-1);
    n->right = buildtree(arr,mid+1,high);
    return n;
}

void scantree(node * head){
    if(head == NULL) return;
    cout<<head->value<<endl;
    scantree(head->left);
    scantree(head->right);
}
/*
int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    node * head = NULL;
    head = buildtree(arr,0,sizeof(arr)/sizeof(int) - 1);
    scantree(head);
    return 0;
}*/
                                                                      4.6.cpp                                                                                             0000644 0000000 0000000 00000002533 12124253324 010570  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Design an algorithm and write code to find the first common ancestor of two nodes 
 * in a binary tree. Avoid storing additional nodes in a data structure. Note: This
 * is not necessarily a binary search tree.
 * 在一棵二叉树中找到两个节点的第一个公共祖先
 */

#include<iostream>
#include"buildtree.h"
using namespace std;

bool contains(treenode * tnode, treenode * node){
    if (tnode == NULL) return false;
    if (tnode == node) return true;
    return contains(tnode->left, node) || contains(tnode->right, node);
}

treenode * firstCommonAncestor(treenode * tnode, treenode * node1 , treenode * node2){
    bool l_node1 = contains(tnode->left,node1);
    bool r_node1 = contains(tnode->right,node1);
    bool l_node2 = contains(tnode->left,node2);
    bool r_node2 = contains(tnode->right,node2);
    if((l_node1 && r_node2) || (l_node2 && r_node1)) return tnode;
    if(l_node1 && l_node2) return firstCommonAncestor(tnode->left, node1, node2);
    if(r_node2 && r_node2) return firstCommonAncestor(tnode->right, node1, node2);
    return NULL;    
}

int main(){
    treenode * tnode = build_A_Test_Tree();
    cout<<treeheight(tnode)<<endl;
    treenode * ancestor = firstCommonAncestor(tnode, treenodelist[6], treenodelist[4]);
    if (ancestor == NULL) cout<<"Not find"<<endl;
    else cout<<ancestor->value<<endl;
    return 0;
}

                                                                                                                                                                     buildtree.h                                                                                         0000644 0000000 0000000 00000004351 12124247642 011713  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   #include<iostream>
#include<cmath>
using namespace std;
#ifndef BUILDTREE
#define BUILDTREE

struct treenode {
    int value ;
    treenode * left;
    treenode * right;
    treenode(int v){
        value = v;
        left = NULL;
        right = NULL;
    }
};


treenode * treenodelist [20];

treenode * build_A_Test_Tree(){
    int arr[][2] = {
        {1,2},
        {3,4},
        {5,-1},
        {6,7},
        {-1,-1},
        {8,9},
        {-1,-1},
        {10,11},
        {-1,-1},
        {12,13},
        {14,-1},
        {15,16},
        {-1,-1},
        {-1,-1},
        {-1,-1},
        {-1,-1},
        {-1,-1}
    };
    /*
     * The tree is for test. Like following:
     *                           0
     *                        /     \
     *                       1       2
     *                      / \     /   
     *                     3   4   5
     *                    / \     / \
     *                   6   7   8   9
     *                      / \     / \
     *                     10 11   12 13
     *                    /  /  \
     *                   14  15 16
     */
    int n_nodes = 17;
    for(int i=0; i<n_nodes; i++){
        treenodelist[i] = new treenode(i);
    }
    for(int i=0;i<n_nodes; i++){
        if(arr[i][0] != -1){
            treenodelist[i]->left = treenodelist[arr[i][0]];
        }else{
            treenodelist[i]->left = NULL;
        }
        if(arr[i][1] != -1){
            treenodelist[i]->right = treenodelist[arr[i][1]];
        }else{
            treenodelist[i]->right = NULL;
        }
   }
    return treenodelist[0];
}

void scanTree(treenode * tnode){
    if(tnode == NULL) return ;
    cout<<tnode->value<<endl;
    scanTree(tnode->left);
    scanTree(tnode->right);
}

void printTestTree(){
    for(int i=0;i<17;i++){
        cout<<treenodelist[i]->value<<"\t";
        if(treenodelist[i]->left != NULL) cout<<treenodelist[i]->left->value<<"\t";
        else cout<<"NULL\t";
        if(treenodelist[i]->right != NULL) cout<<treenodelist[i]->right->value<<"\t";
        else cout<<"NULL\t";
        cout<<endl;
    }
}


int treeheight(treenode * tnode){
    if (tnode == NULL) return 0;
    int l = treeheight(tnode->left);
    int r = treeheight(tnode->right);
    return max(l,r) + 1;
}

#endif
                                                                                                                                                                                                                                                                                       out                                                                                                 0000755 0000000 0000000 00000032711 12124253327 010316  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   ELF          >    `@     @       �!          @ 8 	 @         @       @ @     @ @     �      �                   8      8@     8@                                          @       @                               �      �`     �`     h      8                            `      `     �      �                   T      T@     T@     D       D              P�td   �      �@     �@     |       |              Q�td                                                  R�td   �      �`     �`                        /lib64/ld-linux-x86-64.so.2          GNU                       GNU z�j������j����   
                 
      !��	(E�L�C                        U                                                                    �                                                                e                      �                      _                      �      @@             3      @             K     ` `            libstdc++.so.6 __gmon_start__ _Jv_RegisterClasses _ZNSt8ios_base4InitD1Ev _ZSt4cout _ZNSolsEi _Znwm _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_ _ZNSolsEPFRSoS_E _ZNSt8ios_base4InitC1Ev libc.so.6 __cxa_atexit __libc_start_main GLIBC_2.2.5 GLIBCXX_3.4                                ui	   *                  t)�   6      �`                   ` `                     `                    `                    `                    `                     `                   ( `                   0 `                   8 `        
           @ `        	           H����   �j  ��  H����5*  �%,  @ �%*  h    ������%"  h   ������%  h   ������%  h   �����%
  h   �����%  h   �����%�  h   �����%�  h   �p����%�  h   �`���1�I��^H��H���PTI���@ H���@ H�ǣ@ �g������H��H�I  H��t��H��Ð������������UH��SH���=�   uK�` H��  H��` H��H��H9�s$fD  H��H��  ��` H�w  H9�r��c  H��[]�fff.�     H�=�   UH��t�    H��t]�` ��]Ð�UH��SH��   H��P���� @ �   H��H���H��E�   �E�    �+�   �����H�ËE��H���  �E�H�H�ŀ!` �E��E�;E�����u��E�    �   �E�H����P������t+�E�H�H�ŀ!` �U�Hcҋ��P���Hc�H�Հ!` H�P��E�H�H�ŀ!` H�@    �E�H����T������t+�E�H�H�ŀ!` �U�Hcҋ��T���Hc�H�Հ!` H�P��E�H�H�ŀ!` H�@    �E��E�;E������I���H�  H�Ĩ   []�UH��H��H�}�H�}� tAH�E�� �ƿ` ` �%����@@ H���x���H�E�H�@H������H�E�H�@H����������UH��H���E�    ��   �E�H�H�ŀ!` � �ƿ` ` �������@ H�������E�H�H�ŀ!` H�@H��t.�E�H�H�ŀ!` H�@� �ƿ` ` ������@ H����������@ �` ` �����E�H�H�ŀ!` H�@H��t.�E�H�H�ŀ!` H�@� �ƿ` ` �/�����@ H���r������@ �` ` �a����@@ �` ` �b����E��}�����������UH��H�� H�}�H�}� u�    �>H�E�H�@H��������E�H�E�H�@H��������E�H�U�H�E�H��H���  � ����UH��H��H�}�H�u�H�}� u�    �SH�E�H;E�u�   �BH�E�H�@H�U�H��H��������uH�E�H�@H�U�H��H��������t�   ��    ��UH��H��0H�}�H�u�H�U�H�E�H�@H�U�H��H���b����E�H�E�H�@H�U�H��H���H����E�H�E�H�@H�U�H��H���.����E�H�E�H�@H�U�H��H�������E��}� t�}� u�}� t�}� tH�E��W�}� t#�}� tH�E�H�@H�U�H�M�H��H���?����.�}� t#�}� tH�E�H�@H�U�H�M�H��H��������    ��UH��H������H�E�H�E�H���#����ƿ` ` �����@@ H���W���H��  H��  H�E�H��H������H�E�H�}� u��@ �` ` �����@@ H�������H�E�� �ƿ` ` �����@@ H��������    ��UH��H���}��u��}�u*�}���  u!� "` �t����@ �P ` � "` H���}�����UH����  �   ����]�UH��H�}��u�H�E��U�H�E�H�@    H�E�H�@    ]�UH��H�}�H�u�H�E��H�E�� 9�}H�E��H�E�]�H�l$�L�d$�H�-�  L�%�  L�l$�L�t$�L�|$�H�\$�H��8L)�A��I��H��I���s���H��t1�@ L��L��D��A��H��H9�u�H�\$H�l$L�d$L�l$ L�t$(L�|$0H��8��    �Ð�������������UH��SH��H�X  H���t��` D  H����H�H���u�H��[]Ð�H�������H���                                                       ����      ��������   	   ��������
      ��������         ����      ����������������������������������������	 NULL	 Not find    ;x      $����   �����   ����  A���$  G���D  ����d  ����  ����  �����  ����  �����   ,����  T���$  ����L         zR x�  $      �����    FJw� ?;*3$"       D   :���.    A�Ci   $   d   ����B   A�Cr�         �   ����W    A�CR     �   ���   A�C    �   ����Z    A�CU     �   5���s    A�Cn       �����    A�C�     ,  [����    A�C�     L  `���(    A�Cc      l  ����@    A�C{      �  ����    A�CP   $   �  (����    Q��_@����X      �  ����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           �@     ��������        ��������                                                  �@            �@            �`                   ���o    �@             @            �@     
       B                                          �`            �                            �@            �@            0       	              ���o    `@     ���o           ���o    B@                                                                                                              `                     �@     �@     �@     @     @     &@     6@     F@     V@                     GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3  .symtab .strtab .shstrtab .interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .text .fini .rodata .eh_frame_hdr .eh_frame .init_array .ctors .dtors .jcr .dynamic .got .got.plt .data .bss .comment                                                                                  8@     8                                    #             T@     T                                     1             t@     t      $                              D   ���o       �@     �      0                             N             �@     �      8                          V              @            B                             ^   ���o       B@     B                                  k   ���o       `@     `      @                            z             �@     �      0                            �             �@     �      �                           �             �@     �                                    �             �@     �      �                             �             `@     `      h                             �             �@     �                                    �             �@     �      �                               �             �@     �      |                              �             @           �                             �             �`     �                                    �             �`     �                                    �             `                                         �             `                                         �              `            �                           �             �`     �                                   �             �`     �      `                             �             H `     H                                     �             ` `     X       �                                   0               X       *                                                   �       
                                                   P)               2                 	                      `1      i                                                           8@                   T@                   t@                   �@                   �@                    @                   B@                   `@                  	 �@                  
 �@                   �@                   �@                   `@                   �@                   �@                   �@                   @                   �`                   �`                   `                   `                    `                   �`                   �`                   H `                   ` `                                        �@                 ��                     �`             *     `             8     `             E     �@             [     p!`            j     x!`            x      @                 ��                �      `             �      @             �     `             �     �@             �    ��                �      "`            �     E@     @           �@            $    �`             :     �`             K     �`             ^     `             g     H `             r                     �    �@            �    `@             �                      �                      �    �@     �       �  "  �@     .       �    �@                                  '                     F                     `     @             �                     �    �@            �    �!`     �       �    H `             �  "  �@     .           =@     s           �	@     W       3    ` `           J   P `             W   `             d    �@     �       t    �	@           �    D@     B      �    �
@     Z       �   ��X `             �  "  �@     (       �   ��("`             �                     �     @@             D   ��X `             K                     ^    �@     �       c    �@              call_gmon_start crtstuff.c __CTOR_LIST__ __DTOR_LIST__ __JCR_LIST__ __do_global_dtors_aux completed.6531 dtor_idx.6533 frame_dummy __CTOR_END__ __FRAME_END__ __JCR_END__ __do_global_ctors_aux 4.6.cpp _ZStL8__ioinit _Z41__static_initialization_and_destruction_0ii _GLOBAL__sub_I_treenodelist _GLOBAL_OFFSET_TABLE_ __init_array_end __init_array_start _DYNAMIC data_start _ZNSolsEi@@GLIBCXX_3.4 __libc_csu_fini _start __gmon_start__ _Jv_RegisterClasses _Z19firstCommonAncestorP8treenodeS0_S0_ _ZN8treenodeC2Ei _fini _ZNSt8ios_base4InitC1Ev@@GLIBCXX_3.4 __libc_start_main@@GLIBC_2.2.5 __cxa_atexit@@GLIBC_2.2.5 _ZNSt8ios_base4InitD1Ev@@GLIBCXX_3.4 _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@@GLIBCXX_3.4 _IO_stdin_used treenodelist __data_start _ZN8treenodeC1Ei _Z8containsP8treenodeS0_ _Z8scanTreeP8treenode _ZSt4cout@@GLIBCXX_3.4 __dso_handle __DTOR_END__ __libc_csu_init _Z13printTestTreev _Z17build_A_Test_Treev _Z10treeheightP8treenode __bss_start _ZSt3maxIiERKT_S2_S2_ _end _ZNSolsEPFRSoS_E@@GLIBCXX_3.4 _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@@GLIBCXX_3.4 _edata _Znwm@@GLIBCXX_3.4 main _init                                                        template.cpp                                                                                        0000644 0000000 0000000 00000000147 12124243162 012072  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 
 * Question:
 */

#include<iostream>
using namespace std;

int main()
{
    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                         template.cpp~                                                                                       0000644 0000000 0000000 00000000147 12124243162 012270  0                                                                                                    ustar   root                            root                                                                                                                                                                                                                   /*
 * Chapter 
 * Question:
 */

#include<iostream>
using namespace std;

int main()
{
    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         