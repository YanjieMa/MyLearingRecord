#include <iostream>
#include <iomanip>
/* 红黑树 一种特殊的二叉查找树
 * 二叉查找树特点：任意一个节点的键值大于等于左孩子键值，小于等于右孩子键值
 * 红黑树特点:
 *			1.每个节点或者是红色，或者是黑色
 *			2.根节点是黑色
 *			3.每个为空的叶子结点是黑色
 *			4.如果一个节点是红色的，则他的子节点必须是黑色的
 *			5.从一个节点到该节点的子孙节点的所有路径上 包含相同数目的黑节点
 * */



using namespace std;

// 颜色定义
enum RBTColor {RED, BLACK};

//节点定义
template <class T>
class RBTNode{
	public:
		RBTColor color; // 颜色
		T key;          // 键值
		RBTNode *left;  // 左孩子
		RBTNode *right; // 右孩子
		RBTNode *parent;// 父节点
		RBTNode (T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r) :
			key(value),color(c),parent(p),left(l),right(r) {}	//构造函数
};

//红黑树定义
template <class T>
class RBTree{
private:
	RBTNode<T> *mRoot;		//根节点
public:
	RBTree();
	~RBTree();
	
	//前序遍历
	void preOrder();
	//中序遍历
	void inOrder();
	//后序遍历
	void postOrder();
	
	//查找键值为key的节点(递归实现)
	RBTNode<T>* search(T key);
	//查找键值为key的节点(非递归实现)
	RBTNode<T>* iteratorSearch(T key);
	//查找最小节点，返回最小节点的键值
	T minimum();
	//查找最大节点，返回最大节点的键值
	T maximum();

	//查找点x的后继节点
	RBTNode<T>* successor(RBTNode<T>* x);
	//查找点x的前驱节点
	RBTNode<T>* predecessor(RBTNode<T>* x);	
	
	//将key值插入到红黑树中
	void insert(T key);
	//删除节点(key为节点键值)
	void remove(T key);

	//销毁红黑树
	void destroy();

	//打印红黑树
	void print();
	
private:
	//前序遍历 红黑树
	void preOrder(RBTNode<T>* tree) const; //函数被const标记后不能修改成员数据
										   //函数被const标记后只能调用被const标志的函数
	//中序遍历 红黑树
	void inOrder(RBTNode<T>* tree) const;
	//后序遍历 红黑树
	void postOrder(RBTNode<T>* tree) const;

	//查找红黑树x中键值为key的节点(递归实现)
	RBTNode<T>* search(RBTNode<T>* x, T key) const;
	//查找红黑是x中键值为key的节点(非递归实现)
	RBTNode<T>* iteratorSearch(RBTNode<T>* x, T key) const;

	//查找最小节点
	RBTNode<T>* minimum(RBTNode<T>* tree);
	//查找最大节点
	RBTNode<T>* maximum(RBTNode<T>* tree);  		

	//左旋
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
	//右旋
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
	//插入函数
	void insert(RBTNode<T>* &root, RBTNode<T>* node);
	//插入修正函数
	void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
	//删除函数
	void remove(RBTNode<T>* &root, RBTNode<T>* node);
	//删除修正函数
	void removeFixUp(RBTNode<T>* &root,RBTNode<T>* node, RBTNode<T>* parent);
	
	//销毁红黑树
	void destroy(RBTNode<T>* &tree);
	//打印红黑树
	void print(RBTNode<T>* &tree, T key, int direction);
};

//构造函数
template <class T>
RBTree<T>::RBTree() : mRoot(NULL)
{
	mRoot = NULL;
}
//析构函数
template <class T>
RBTree<T>::~RBTree()
{
	destroy();
}
//前序遍历 红黑树
template< class T>
void RBTree<T>::preOrder(RBTNode<T>* tree) const
{
	if(tree != NULL){
		cout<< tree->key << " ";
		preOrder(tree->left);
		preOrder(tree->right);		
	}
}
//中序遍历 红黑树
template< class T>
void RBTree<T>::inOrder(RBTNode<T>* tree) const
{
	if(tree != NULL){
		inOrder(tree->left);
		cout << tree->key << " ";
		inOrder(tree->right);
	}
}
//后序遍历 红黑树
template<class T>
void RBTree<T>::postOrder(RBTNode<T>* tree) const
{
	if(tree != NULL){
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << " ";
	}
}

// 遍历红黑树 对外接口
template <class T>
void RBTree<T>::preOrder()
{
	preOrder(mRoot);
}
template<class T>
void RBTree<T>::inOrder()
{
	inOrder(mRoot);
}
template< class T>
void RBTree<T>::postOrder()
{
	postOrder(mRoot);
}

//查找红黑树x中 键值为key的节点 递归实现
template <class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* x, T key) const
{
	// 找到key值 或者 节点为NULL 时，返回
	if(x == NULL || x->key == key){
		return x;
	}
	if(key < x->key){
		return search(x->left,key);
	}else{
		return search(x->right,key);
	}
	return x;
}
//查找红黑树x中 键值为key的节点 非递归实现
template <class T>
RBTNode<T>* RBTree<T>::iteratorSearch(RBTNode<T>* x, T key) const
{
	while(x != NULL && x->key != key){
		if(key < x->key){
			x = x->left;
		}else{
			x = x->right;
		}
	}
	return x;
}

//查找key值节点 对外接口
template <class T>
RBTNode<T>* RBTree<T>::search(T key)
{
	search(mRoot, key);	
}
template<class T>
RBTNode<T>* RBTree<T>::iteratorSearch(T key)
{
	iteratorSearch(mRoot,key);
}


//查找最小节点
template<class T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* tree)
{
	if(tree == NULL){
		return NULL;
	}
	while(tree->left != NULL){
		tree = tree->left;
	}
	return tree;
}

template<class T>
T RBTree<T>::minimum()
{
	RBTNode<T> *p = minimum(mRoot);
	if(p != NULL)
		return p->key;
	return (T)NULL;
}

//查找最大节点
template <class T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* tree)
{
	if(tree == NULL)
		return NULL;

	while(tree->right != NULL)
		tree = tree->right;
	return tree;
}
template <class T>
T RBTree<T>::maximum()
{
	RBTNode<T>* p = maximum(mRoot);
	if(p != NULL)
		return p->key;
	return (T)NULL;
}

//查找节点x的后继节点 红黑树中数据值大于该节点 的 最小节点
template <class T>
RBTNode<T>* RBTree<T>::successor(RBTNode<T> *x)
{
	//如果x存在右孩子 则 x的后继节点为以其右孩子为根的子树的最小节点
	if(x->right != NULL)
		return minimum(x->right);

	//如果x没有右孩子, 则有两种可能
	//1.x是一个左孩子, 则他的后继节点为他的父节点
	//2.x是一个右孩子, 则x的后继节点为 x最低的父节点，并且该父节点要有左孩子
		//查找x的最低父节点,并且该父节点为左孩子	
	RBTNode<T>* p = x->parent;
	while(p != NULL && x == p->right){
		x = p;
		p = p->parent;
	} 
	return p;
}
//查找节点x的前驱节点 红黑树中数据值小于该节点的最小节点
template <class T>
RBTNode <T>* predecessor(RBTNode<T>* x)
{
	//如果x存在左孩子,则x的前驱节点为 以其左孩子为子树的最大节点
	if(x->left != NULL){
		return maximum(x->left);
	}	
	//如果x没有左孩子，则有两种可能
	//1.x是右孩子，他的前驱节点是他的父节点
	//2.x是左孩子，则x的最低父节点，且该父节点是右孩子 就是x的前驱节点
	RBTNode<T>* p = x->parent;
	while(p != NULL && p->left == x){
		x = p;
		p = p->parent;
	}
	return p;
}

/*
 * 左旋示意图(对节点x进行左旋)：
 **      px                              px
 **     /                               /
 **    x                               y                
 **   /  \      --(左旋)-->           / \                #
 **  lx   y                          x  ry     
 **     /   \                       /  \
 **    ly   ry                     lx  ly  
*/

//对红黑树的节点x进行左旋
template <class T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
{
	//获取x的右孩子为y
	RBTNode<T>* y = x->right;

	//将 y的左孩子 设为 x的右孩子
	//如果 y的左孩子非空 将 x设为 y的左孩子父亲
	x->right = y->left;
	if(y->left != NULL){
		y->left->parent = x;
	}
	//将 x的父亲 设为 y的父亲
	y->parent = x->parent;
	
	if(x->parent == NULL){
		root = y;	//如果 x的父亲 是空节点, 则 y为 根节点
	}else{
		if(x->parent->left == x){
			x->parent->left = y;	//如果x是他父亲的左孩子，将y设为 x父亲节点的左孩子
		}else{
			x->parent->right = y;	//如果x是他父亲的右孩子，将y设为 x父亲节点的右孩子
		}
	}
	//将 x 设为 y的左孩子
	y->left = x;
	//将 x的父节点 设为 y
	x->parent = y;		
}
/*
  * 右旋示意图(对节点y进行左旋)：
  *            py                               py
  *           /                                /
  *          y                                x                  
  *         /  \      --(右旋)-->            /  \                     #
  *        x   ry                           lx   y  
  *       / \                                   / \                 #
  *      lx  rx                                rx  ry
*/
//对红黑树的节点y进行右旋
template <class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
	//获取x的当前节点
	RBTNode<T>* x = y->left;
	
	//将 x的右孩子 设为 y的左孩子
	//如果x的右孩子不为空，将y设为x右孩子的父亲
	y->left = x->right;
	if(x->right != NULL){
		x->right->parent = y;
	}	
	//将y的父亲 设为 x的父亲
	x->parent = y->parent;
	if(y->parent == NULL){
		root = x; //如果y的父亲节点是空，则将x设为根节点
	}else{
		if(y == y->parent->right){
			y->parent->right = x;	//如果 y是他父亲节点的右孩子，将x设为y父节点的右孩子
		}else{
			y->parent->left = x; //y是他父亲节点的左孩子， 将x设为父亲节点的左孩子
		}
	}
	//将y设为x的右孩子
	x->right = y;
	//将y的父亲设为x
	y->parent= x;
}

//将节点插入到红黑树
template <class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* y = NULL;
	RBTNode<T>* x = root;

	//将红黑树当作一颗二叉查找树，将节点插入到二叉树
	while(x != NULL){
		y = x;
		if(node->key < x->key){
			x = x->left;
		}else{
			x = x->right;
		}
	}
	//找到最后的叶子节点，设置插入节点的父节点	
	node->parent = y;

	if(y != NULL){
		if(node->key < y->key){
			y->left = node;
		}else{
			y->right = node;
		}
	}else{
		root = node;
	}

	//设置节点的颜色为红色
	node->color = RED;

	//将他重新修正为一颗红黑树
	insertFixUp(root,node);	
}


//插入修正函数
template <class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root,RBTNode<T>* node)
{
	RBTNode<T> *parent, *gparent;
	
	//如果node节点的父节点存在 且 父节点颜色是红色
	while((parent = node->parent) && parent->color == RED){
		gparent = parent->parent;

		//如果父节点 是 祖父节点 的左孩子
		if(parent == gparent->left){
			//case1.叔叔节点是红色
			RBTNode<T>* uncle = parent->right;
			if(uncle && uncle->color == RED){
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				node = gparent;
				continue;
			}
			
			//case2.叔叔节点是黑色 且 当前节点是右孩子
			if(parent->right == node){
				RBTNode<T> *tmp;
				leftRotate(root,parent);
				tmp = parent;	//parent 和 node 互换
				parent = node;
				node = tmp;
			}else{
			//case3.叔叔节点是黑色 且 当前节点是左孩子
				parent->color = BLACK;
				gparent->color = RED;
				rightRotate(root,node);
			
			}
		//如果node的父节点 是 祖父节点的右孩子
		}else{
			//case1.叔叔节点是红色
			RBTNode<T>* uncle = gparent->left;
			if(uncle && uncle->color == RED){
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				node = gparent;
				continue;
			}
			//case2.叔叔节点是黑色 且 当前节点是左孩子
			if(parent->left == node){
				RBTNode<T>* tmp;
				rightRotate(root,node);
				tmp = parent;
				parent = node;
				node = tmp;
			//case3.叔叔节点是红色 且 当前节点是右孩子
			}else{
				parent->color = BLACK;
				gparent->color = RED;
				leftRotate(root,gparent);		
			}
		}
	}
	//将根节点设置为黑色
	root->color = BLACK;
}

template <class T>
void RBTree<T>::insert(T key)
{
	RBTNode<T>* z = NULL;
	if((z = new RBTNode<T>(key, BLACK, NULL, NULL, NULL)) == NULL){
		return;
	}
	
	insert(mRoot,z);
}

//删除节点 并返回被删除的节点
template <class T>
void RBTree<T>::remove(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T> *child, *parent;
	RBTColor color;
	
	//被删除的节点 左右孩子都不为空 的情况
	if((node->left != NULL) && (node->left) != NULL){
		//找到后继节点，用它取代被删节点的位置，然后再将被删节点删除掉
		RBTNode<T> *replace = node;

		//获取后继节点
		replace = replace->right;
		while(replace->left != NULL){
			replace = replace ->left;
		}
		//node节点不是根节点
		if(node->parent != NULL){
			if(node->parent->left = node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}else{
			root = replace;
		}

		
        child = replace->right;
        parent = rb_parent(replace);

        color = rb_color(replace);


        if (parent == node)
        {
            parent = replace;
        } 
        else
        {

            if (child)
                rb_set_parent(child, parent);
            parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            removeFixUp(root, child, parent);

        delete node;
        return ;


	}	
	//被删的节点为叶子节点
	if(node->left != NULL){
		child = node->left;
	}else{
		child = node->right;
	}
	parent = node->parent;
	color = node->color; //保存取代节点的颜色
	if(child)
		child->parent = parent;
	//node 节点不是根节点
	if(parent){
		if(parent->left == node){
			parent->left = child;
		}else{
			parent->right = child;
		}
	}else{
		root = child;
	}

	if(color = BLACK){
		removeFixUp(root,child,parent);
	}
	
	delete node;
}

template <class T>
void RBTree<T>::remove(T key)
{
	RBTNode<T> * node;

	if((node = search(mRoot,key) != NULL)){
		remove(mRoot, node);
	}	
}

// 红黑树 删除修正函数
template<class T> 
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T>* node,RBTNode<T>* parent)
{
	RBTNode<T> *other;

	
	while((!node || node->color == BLACK) && (node != root)){
		
		if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {  
                rb_set_black(other);
                rb_set_red(parent);
                leftRotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            { 
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rightRotate(root, other);
                    other = parent->right;
                }
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {  
                rb_set_black(other);
                rb_set_red(parent);
                rightRotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {  
                    rb_set_black(other->right);
                    rb_set_red(other);
                    leftRotate(root, other);
                    other = parent->left;
                }
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rightRotate(root, parent);
                node = root;
                break;
            }
		}	
	}	
	if(node)
		node->color = BLACK;
}


//销毁红黑树
template <class T>
void RBTree<T>::destroy(RBTNode<T>* &tree)
{
	if(tree == NULL){
		return ;
	}
	if(tree->left != NULL){
		return destroy(tree->left);
	}
	if(tree->right != NULL){
		return destroy(tree->right);
	}
	
	delete tree;
	tree = NULL;	
}

template <class T>
void RBTree<T>::destroy()
{
	destroy(mRoot);
}

//打印二叉查找树
template <class T>
void RBTree<T>::print(RBTNode<T>* &tree, T key, int direction)
{
	if(tree != NULL){
		if(direction == 0){//根节点
			cout << setw(2) << tree->key << "(B) is root" << endl;
		}else{
			cout << setw(2)<< tree->key << (tree->color == RED ? "(R)" : "(B)") << " is "<<setw(2)<< key <<"'s " << setw(12)<<(direction == 1 ? "right child":"left child") << endl;
		}
	
		print(tree->left,tree->key,-1);
		print(tree->right,tree->key,1);		
	}		 
}

template <class T>
void RBTree<T>::print()
{
	if(mRoot != NULL){
		print(mRoot,mRoot->key,0);
	}	
}


int main()
{
	int a[] = {10,20,30,40,50,60,70,80,90}	;
	
	RBTree<int>* tree = new RBTree<int>();

	for(int i=0; i<(sizeof(a)/sizeof(a[0])); i++){
		tree->insert(a[i]);
		cout << "添加节点 "<< a[i] << endl;

		cout << "树的详细信息" << endl;
		tree->print();
		cout << endl;
	}

	cout << "--------------" << endl;
	tree->postOrder();



	return 0;
}
