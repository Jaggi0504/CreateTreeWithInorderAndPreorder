#include<bits/stdc++.h>
using namespace std;

template<typename T>
class BinaryTreeNode {
	public:
		T data;
		BinaryTreeNode *left;
		BinaryTreeNode *right;
		BinaryTreeNode(T data) {
			this->data = data;
			this->left = NULL;
			this->right = NULL;
		}
};

BinaryTreeNode<int> *takeInput() {
	int rootData;
	cout<<"Enter the root data: ";
	cin>>rootData;
	if(rootData == -1) {
		return NULL;
	}
	BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
	queue<BinaryTreeNode<int> *>pendingNodes;
	pendingNodes.push(root);
	while(pendingNodes.size() != 0) {
		BinaryTreeNode<int> *front = pendingNodes.front();
		pendingNodes.pop();
		int leftChildData;
		cout<<"Enter the left child of "<<front->data<<":";
		cin>>leftChildData;
		if(leftChildData != -1) {
			BinaryTreeNode<int> *child = new BinaryTreeNode<int>(leftChildData);
			front->left = child;
			pendingNodes.push(child);
		}
		int rightChildData;
		cout<<"Enter the right child of "<<front->data<<":";
		cin>>rightChildData;
		if(rightChildData != -1) {
			BinaryTreeNode<int> *child = new BinaryTreeNode<int>(rightChildData);
			front->right = child;
			pendingNodes.push(child);
		}
	}
	return root;
}

void print(BinaryTreeNode<int> *root) {
	if(root == NULL) {
		return ;
	}
	queue<BinaryTreeNode<int> *>ans;
	ans.push(root);
	ans.push(NULL);
	while(ans.size() != 0) {
		BinaryTreeNode<int> *front = ans.front();
		ans.pop();
		if(front == NULL) {
			if(ans.size() == 0) {
				break;
			}
			cout<<endl;
			ans.push(NULL);
			continue;
		}
		cout<<front->data<<" ";
		if(front->left) {
			ans.push(front->left);
		}
		if(front->right) {
			ans.push(front->right);
		}
	}
}

int main() {
	int preLength, inLength, inorder[100], preorder[100];
	cout<<endl;
	cout<<"Enter the inLength: ";
	cin>>inLength;
	cout<<"Enter the preLength: ";
	cin>>preLength;
	cout<<"Enter the nodes of inorder: ";
	for(int i=0;i<inLength;i++) {
		cin>>inorder[i];
	}
	cout<<"Enter the nodes of preorder: ";
	for(int i=0;i<preLength;i++) {
		cin>>preorder[i];
	}
	BinaryTreeNode<int> *root1 = buildTree(inorder, preorder, inLength, preLength);
	printNormal(root1);
	return 0;
}

BinaryTreeNode<int> *buildHelperTree(int *inorder, int *preorder, int inS, int inE, int preS, int preE) {
	if(inS > inE) {
		return NULL;
	}
	int rootData = preorder[preS];
	int rootIndex = -1;
	for(int i=inS;i<=inE;i++) {
		if(inorder[i] == rootData) {
			rootIndex = i;
			break;
		}
	}
	int lInS, lInE, lPreS, lPreE, rInS, rInE, rPreS, rPreE;
	lInS = inS;
	lInE = rootIndex - 1;
	rInS = rootIndex + 1;
	rInE = inE;
	lPreS = preS + 1;
	lPreE = lInE - lInS + lPreS;
	rPreS = lPreE + 1;
	rPreE = preE;
	BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
	root->left = buildHelperTree(inorder, preorder, lInS, lInE, lPreS, lPreE);
	root->right = buildHelperTree(inorder, preorder, rInS, rInE, rPreS, rPreE);
	return root;
}

BinaryTreeNode<int> *buildTree(int *inorder, int *preorder, int inLength, int preLength) {
	return buildHelperTree(inorder, preorder, 0, inLength-1, 0, preLength-1);
}
