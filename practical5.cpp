Question 5: Construct an expression tree from the given prefix expression eg. +--
a*bc/def and traverse it using postorder traversal(non 
2 recursive) and then delete the entire tree.
3
4
5 #include <iostream>
6 #include <stack>
7 using namespace std;
8
9 // Node structure for expression tree
10 struct Node {
11 string data;
12 Node* left;
13 Node* right;
14
15 Node(string value) : data(value), left(nullptr), right(nullptr) {}
16 };
17
18 // Function to check if a character is an operand
19 bool isOperand(char c) {
20 return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
21 }
22
23 // Function to construct an expression tree from prefix expression
24 Node* constructExpressionTree(string prefixExpression) {
25 stack<Node*> st;
26
27 int length = prefixExpression.length();
28
29 // Traverse the prefix expression in reverse order
30 for (int i = length - 1; i >= 0; i--) {
31 char ch = prefixExpression[i];
32
33 // If the character is an operand, create a new node and push it to the
stack
34 if (isOperand(ch)) {
35 string operand(1, ch);
36 st.push(new Node(operand));
37 } else {
38 // If the character is an operator, pop two nodes from the stack,
39 // create a new node with the operator as the data, and push it back to
the stack
40 Node* operand1 = st.top();
41 st.pop();
42 Node* operand2 = st.top();
43 st.pop();
44
45 string op(1, ch);
46 string expression = operand1->data + operand2->data + op;
47
48 Node* operatorNode = new Node(expression);
49 operatorNode->left = operand1;
50 operatorNode->right = operand2;
51
52 st.push(operatorNode);
53 }
54 }
55
56 // The top of the stack will be the root of the expression tree
57 return st.top();
58 }
59
60 // Function to perform postorder traversal (non-recursive) on the expression tree
61 void postorderTraversal(Node* root) {
62 if (root == nullptr)
63 return;
File: /home/shrikant/Desktop/Shrikant/5 Page 2 of 2
64
65 stack<Node*> st;
66 Node* current = root;
67 Node* lastVisited = nullptr;
68
69 while (current || !st.empty()) {
70 if (current) {
71 st.push(current);
72 current = current->left;
73 } else {
74 Node* topNode = st.top();
75 if (topNode->right && topNode->right != lastVisited) {
76 current = topNode->right;
77 } else {
78 cout << topNode->data << " ";
79 lastVisited = topNode;
80 st.pop();
81 }
82 }
83 }
84 }
85
86 // Function to delete the entire expression tree
87 void deleteExpressionTree(Node* root) {
88 if (root == nullptr)
89 return;
90
91 deleteExpressionTree(root->left);
92 deleteExpressionTree(root->right);
93
94 delete root;
95 }
96
97 int main() {
98 string prefixExpression;
99 cout << "Enter the prefix expression: ";
100 cin >> prefixExpression;
101
102 Node* root = constructExpressionTree(prefixExpression);
103
104 cout << "Postorder Traversal: ";
105 postorderTraversal(root);
106 cout << endl;
107
108 deleteExpressionTree(root);
109
110 return 0;
111 }