#include <iostream>

using namespace std;

// 1.红黑树节点基类
//颜色标记
enum _Rb_tree_color { _S_red = false, _S_black = true};

struct _Rb_tree_node_base{
	//typedef 重命名
	typedef _Rb_tree_node_base* _Base_ptr;
	// 颜色
	_Rb_tree_color _M_color;
	// 指向父亲节点
	_Base_ptr _M_parent;
	// 指向左孩子节点
	_Base_ptr _M_left;
	// 指向右孩子节点
	_Base_ptr _M_right;
	// 求红黑树的最小节点
	static _Base_ptr _S_minimum( _Base_ptr __X ) _GLIBCXX_NOEXCEPT{
		while( __X->_M_left != 0){
			__X = __X->_M_left;
		}
		return __X;
	}
	// 求红黑树的最大节点
	static _Base_ptr _S_maximum( _Base_ptr __X ) _GLIBCXX_NOEXCEPT{
		while( __X->_M_right != 0){
			__X = __X->_M_right;
		}
		return __X;
	}
};

// 2.红黑树节点
template <typename _Val>
struct _Rb_tree_node : public _Rb_tree_node_base{
	typedef _Rb_tree_node<_Val> * _Link_type; //节点指针
	_Val _M_value_field; //节点数据域
	
};

// 3.红黑树迭代器
template <typename _Tp>
struct _Rb_tree_iterator{
	typedef _Tp value_type;
	typedef _Tp& reference;
	typedef _Tp* pointer;

	typedef bidirectional_iterator_tag iterator_category;
	typedef	ptrdiff_t difference_type;

	typedef _Rb_tree_node<_Tp> _Self;   // 红黑树节点
	typedef _Rb_tree_node_base::_Base_ptr _Base_ptr; //红黑树基类节点指针
	typedef _Rb_tree_node<_Tp>* _Link_type;	//红黑树节点的指针
	
	_Base_ptr _M_node; 


	// 重载获取数据
	reference operator*() const _GLIBCXX_NOEXCEPT{
		return *static_cast<_Link_type> (_M_node)->_M_valptr();
	}

	pointer operator->() const _GLIBCXX_NOEXCEPT{
		return static_cast<_Link_type> (_M_node)->_M_valptr();
	}

};



int main()
{


	return 0;
}
