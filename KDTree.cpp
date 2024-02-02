#include "KDTree.h"

TreeNode::TreeNode(Node<Store>* data,int depth, TreeNode* parent , TreeNode* left , TreeNode* right) {
	this->right = right;
	this->parent = parent;
	this->left = left;
	this->data = data;
	this->depth = depth;
	this->h = 0;
}

KDTree::KDTree()=default;

void KDTree::BFSPrint() {
	int nodes_in_same_height = 1;
	int nodes_in_next_same_height = 0;
	Queue<TreeNode*> nodes;
	TreeNode* prev_parent = nullptr;
	if (root != nullptr)
		nodes.push(root);
	while (!nodes.empty()) {
		TreeNode* node = nodes.front();
		nodes.pop();

		if (node->left) {
			nodes.push(node->left);
			nodes_in_next_same_height++;
		}
		if (node->right) {
			nodes.push(node->right);
			nodes_in_next_same_height++;
		}
		if (prev_parent != node->parent) {


			cout << node->parent->data->get_data().get_individualName() << "[" << node->parent->data->get_data().get_x() << "," << node->parent->data->get_data().get_y() << "]" << ':';

			prev_parent = node->parent;
		}
		cout << node->data->get_data().get_individualName() <<"[" << node->data->get_data().get_x()<<","<< node->data->get_data().get_y() <<"]" << ' ';
		nodes_in_same_height--;
		if (!nodes_in_same_height) {

			nodes_in_same_height = nodes_in_next_same_height;
			nodes_in_next_same_height = 0;
			prev_parent = node->parent;
			cout << endl;
		}
	}

}
void KDTree::push(Node<Store>* data) {
	size++;
	if (!this->root) {
		this->root = new TreeNode(data,0);
		return;
	}
	try {
		recursivePush(this->root, data, 0);
	}
	catch (const char* err) {
		if (string(err) == "tree not balanced") {
			Vector<Node<Store>*> vec;
			this->AddAll(vec,this->root);
			this->clear();
			this->construct(vec.get_arr(), vec.getSize());
			vec.clear();

		}
		else {
			throw err;
		}
	}
}
void KDTree::recursivePush(TreeNode* curr, Node<Store>* data, int depth) {
	
	if (!(depth % 2)) {//x 
		if (data->get_data().get_x() >= curr->data->get_data().get_x()) {
			if (curr->right == nullptr) {
				if (curr->data->get_data().get_x() == data->get_data().get_x() && curr->data->get_data().get_y() == data->get_data().get_y()) {
					throw "there is another store with this coordineence";
				}
				curr->right = new TreeNode(data,depth+1, curr);
				if (!fix_up_h(curr->right)) {
					throw "tree not balanced";

				}
				
			}
			else {
				recursivePush(curr->right, data, depth + 1);

			}
		}
		else {
			if (curr->left == nullptr) {
				curr->left = new TreeNode(data,depth+1, curr);
				if (!fix_up_h(curr->left)) {
					throw "tree not balanced";

				}

				
			}
			else {
				recursivePush(curr->left, data, depth + 1);

			}
		}
	}
	else {//y
		if (data->get_data().get_y() >= curr->data->get_data().get_y()) {
			if (curr->right == nullptr) {
				if (curr->data->get_data().get_x() == data->get_data().get_x() && curr->data->get_data().get_y() == data->get_data().get_y()) {
					throw "there is another store with this coordineence";
				}
				curr->right = new TreeNode(data,depth+1, curr);
				if (!fix_up_h(curr->right)) {
					throw "tree not balanced";

				}

			}
			else {
				recursivePush(curr->right, data, depth + 1);

			}
		}
		else {
			if (curr->left == nullptr) {
				
				curr->left = new TreeNode(data,depth+1, curr);
				if (!fix_up_h(curr->left)) {
					throw "tree not balanced";

				}

				
			}
			else {
				recursivePush(curr->left, data, depth + 1);
			}
		}

	}

}

TreeNode* KDTree::find(TreeNode* curr, int x, int  y, int depth) {
	if (!curr) {
		return nullptr;
	}
	int curr_x = curr->data->get_data().get_x();
	int curr_y = curr->data->get_data().get_y();
	if (curr_x == x && curr_y == y)
		return curr;
	if (!curr) {
		return nullptr;
	}

	if (!(depth % 2)) {//x
		if (curr_x <= x) {
			return find(curr->right, x, y, depth + 1);
		}
		else {
			return find(curr->left, x, y, depth + 1);

		}
	}
	else{
		if (curr_y <= y) {
			return find(curr->right, x, y, depth + 1);
		}
		else {
			return find(curr->left, x, y, depth + 1);

		}
	}
}

Node<Store>* KDTree::deleteByCoo(int x, int y) {
	TreeNode* target = find(this->root, x, y, 0);
	if (target == nullptr)
		throw "no such node with this coordinence";
	
	Node<Store>* result = target->data;
	if (result->get_data().get_is_original())
		throw "the store is the main branch";
	try {
		deleteByAdr(target);
	}
	catch(const char* err){
		if (string(err) == "tree not balanced") {
			Vector<Node<Store>*> vec;
			this->AddAll(vec, this->root);
			this->clear();
			this->construct(vec.get_arr(), vec.getSize());
			vec.clear();

		}
	}
	size--;

	return result;
}
void KDTree::deleteByAdr(TreeNode* node) {
	if (node->left == nullptr && node->right == nullptr) {//the node is a leaf
		TreeNode* parent = node->parent;
		if (!node->parent) {//node is root
			delete this->root;
			this->root = nullptr;
		}
		else {//node is not root
			if (node == node->parent->right)
				node->parent->right = nullptr;
			else
				node->parent->left = nullptr;

			delete node;
		}
		if (!fix_up_h(parent)) {
			throw "tree not balanced";
		}
	}
	else if(node->right) {//it has a right node
		TreeNode* minimum = findSmallest(node->right, node->depth % 2);
		node->data = minimum->data;//just two pointers being equal
		deleteByAdr(minimum);
	}
	else {
		TreeNode* minimum = findSmallest(node->left, node->depth % 2);
		node->data = minimum->data;//just two pointers being equal
		deleteByAdr(minimum);
		node->right = node->left;
		node->left = nullptr;
	}

}
TreeNode* KDTree::minNode(TreeNode* node1, TreeNode* node2,int dim) {
	if (!node1) {
		return node2;
	}
	else if (!node2) {
		return node1;
	}
	if (!dim) {
		if (node2==nullptr||node1->data->get_data().get_x() < node2->data->get_data().get_x()) {
			return node1;
		}
		else {
			return node2;
		}
	}
	else {
		if (node2 == nullptr || node1->data->get_data().get_y() < node2->data->get_data().get_y()) {
			return node1;
		}
		else {
			return node2;
		}

	}
}
TreeNode* KDTree::minNode(TreeNode* node1, TreeNode* node2, TreeNode* node3, int dim) {
	return minNode(minNode(node1, node2,dim), node3,dim);
}

TreeNode* KDTree::findSmallest(TreeNode* curr, int dim) {
	if (!curr)
		return nullptr;
	if (curr->depth % 2 == dim) {
		if (curr->left == nullptr)
			return curr;
		return findSmallest(curr->left, dim);

	}
	return minNode(curr, findSmallest(curr->left, dim), findSmallest(curr->right, dim),dim);

}
void KDTree::searchNeighborhood(Neighborhood neighborhood) {
	_searchNeighborhood(this->root, neighborhood);

}
void KDTree::_searchNeighborhood(TreeNode* curr, Neighborhood neighborhood) {
	if (curr == nullptr)
		return;
	int curr_x = curr->data->get_data().get_x();
	int curr_y = curr->data->get_data().get_y();
	auto coo = neighborhood.getCoo();
	if ((curr_x <= coo.first.second && curr_x >= coo.first.first) && ((curr_y <= coo.second.second && curr_y >= coo.second.first))) {
		cout << curr->data->get_data() << endl;
	}
	if (!(curr->depth % 2)) {
		if (curr_x <= coo.first.first) {
			_searchNeighborhood(curr->right, neighborhood);
		}
		else if (curr_x > coo.first.second) {
			_searchNeighborhood(curr->left, neighborhood);

		}
		else {
			_searchNeighborhood(curr->right, neighborhood);
			_searchNeighborhood(curr->left, neighborhood);

		}

		
	}
	else {
		if (curr_y <= coo.second.first) {
			_searchNeighborhood(curr->right, neighborhood);
		}
		else if (curr_y > coo.second.second) {
			_searchNeighborhood(curr->left, neighborhood);

		}
		else {
			_searchNeighborhood(curr->right, neighborhood);
			_searchNeighborhood(curr->left, neighborhood);

		}


	}
	
}
Node<Store>* KDTree::findTheClosestPoint(int x, int y) {
	//we keep the x^2+y^2 in the int;
	Pair<TreeNode*, float> target = { nullptr,0 };
	if (!this->root)
		throw "there isn't any node in tree";

	_findTheClosestPoint(this->root, target, x, y);
	return target.first->data;

}
void KDTree::_findTheClosestPoint(TreeNode* curr, Pair<TreeNode*, float>& target ,int x, int y) {
	float dist = distPower2(curr, x, y);	
	if (!target.first || dist < target.second) {
		target = { curr,dist };
	}
	if (!curr->left && !curr->right) {
		return;
	}

	if (!(curr->depth)) {
		
		if (curr->data->get_data().get_x() <=x) {
			if (curr->right) {
				_findTheClosestPoint(curr->right, target, x, y);
			}
			if (curr->left && (x-curr->data->get_data().get_x()) * (x - curr->data->get_data().get_x()) <target.second) {
				_findTheClosestPoint(curr->left, target, x, y);
				
			}
		}
		else {
			if (curr->left) {
				_findTheClosestPoint(curr->left, target, x, y);
			}
			if (curr->right && (x - curr->data->get_data().get_x()) * (x - curr->data->get_data().get_x()) < target.second) {
				_findTheClosestPoint(curr->right, target, x, y);

			}


		}
		
	}
	else {
		if (curr->data->get_data().get_y() <= y) {
			if (curr->right) {
				_findTheClosestPoint(curr->right, target, x, y);
			}
			if (curr->left && (y - curr->data->get_data().get_y()) * (y - curr->data->get_data().get_y()) < target.second) {
				_findTheClosestPoint(curr->left, target, x, y);

			}
		}
		else {
			if (curr->left) {
				_findTheClosestPoint(curr->left, target, x, y);
			}
			if (curr->right && (y - curr->data->get_data().get_y()) * (y - curr->data->get_data().get_y()) < target.second) {
				_findTheClosestPoint(curr->right, target, x, y);

			}


		}

	}
}
void KDTree::printAllNodesInRange( int x, int y, float R) {
	if (!this->root)
		return;

	_printAllNodesInRange(this->root, R * R, x, y);
	
}
void KDTree::_printAllNodesInRange(TreeNode* curr, float R2, int x, int y) {
	float dist = distPower2(curr, x, y);
	if (dist <= R2) {
		cout << curr->data->get_data()<<endl;
	}
	if (!curr->left && !curr->right) {
		return;
	}

	if (!(curr->depth)) {

		if (curr->data->get_data().get_x() <= x) {
			if (curr->right) {
				_printAllNodesInRange(curr->right,R2, x, y);
			}
			if (curr->left && (x - curr->data->get_data().get_x()) * (x - curr->data->get_data().get_x()) < R2) {
				_printAllNodesInRange(curr->left, R2, x, y);

			}
		}
		else {
			if (curr->left) {
				_printAllNodesInRange(curr->left, R2, x, y);
			}
			if (curr->right && (x - curr->data->get_data().get_x()) * (x - curr->data->get_data().get_x()) < R2) {
				_printAllNodesInRange(curr->right, R2, x, y);

			}


		}

	}
	else {
		if (curr->data->get_data().get_y() <= y) {
			if (curr->right) {
				_printAllNodesInRange(curr->right, R2, x, y);
			}
			if (curr->left && (y - curr->data->get_data().get_y()) * (y - curr->data->get_data().get_y()) < R2) {
				_printAllNodesInRange(curr->left, R2, x, y);

			}
		}
		else {
			if (curr->left) {
				_printAllNodesInRange(curr->left, R2, x, y);
			}
			if (curr->right && (y - curr->data->get_data().get_y()) * (y - curr->data->get_data().get_y()) < R2) {
				_printAllNodesInRange(curr->right, R2, x, y);

			}


		}

	}

}

float KDTree::distPower2(TreeNode* node1,int x,int y) {
	int diff_x = node1->data->get_data().get_x() - x;
	int diff_y = node1->data->get_data().get_y() - y;
	return diff_x * diff_x + diff_y * diff_y;//I didnt use the pow function to be safe in case the compiler is changed

}
void KDTree::clear() {
	_clear(this->root);
}
void KDTree::_clear(TreeNode* node){
	if (!node)
		return;
	if (node->right) {
		_clear(node->right);
	}
	if (node->left) {
		_clear(node->left);
	}
	if (node->right) {
		delete node->right;
	}
	if (node->left) {
		delete node->left;
	}
	if (node && node == this->root) {
		delete node;
		this->root = nullptr;
	}

}
void KDTree::construct(Node<Store>** arr,int size) {
	this->root=_construct( 0, arr,size);


}

TreeNode* KDTree::_construct( int depth, Node<Store>** arr,int size) {
	if (size<=0) {
		return nullptr;
	}
	if (!(depth % 2)) {
		mergeSort(arr, size, [](Node<Store>* node) {return node->get_data().get_x(); });
	}else{
		mergeSort(arr, size, [](Node<Store>* node) {return node->get_data().get_y(); });
	}

	int median = size / 2;
	TreeNode* node = new TreeNode(arr[median], depth, nullptr);
	node->right = _construct(depth + 1, arr + median+1, size-median-1);
	node->left= _construct(depth + 1, arr, median);
	
	if(node->right)
		node->right->parent = node;
	if(node->left)
		node->left->parent = node;
	return node;

	

	
	
}

bool KDTree :: fix_up_h(TreeNode* problem_node) {
	if (!problem_node) {
		true;
	}
	TreeNode* parent = problem_node;
	while (parent) {
		int h = -1;
		if (parent->right) {
			h = parent->right->h;
			
		}
		if (parent->left && parent->left->h > h) {
			h = parent->left->h;
		}
		parent->h = h+1;
		//check
		if (parent->right && parent->left) {
			if (abs(parent->right->h - parent->left->h) > 1) {
				return false;
			}
		}
		else if (parent->right && !parent->left) {
			if (parent->right->h > 0) {
				return false;
			}
		}
		else if (parent->left && !parent->right) {
			if (parent->left->h > 0) {
				return false;
			}
		}
		parent = parent->parent;

	}
	return true;
}
void KDTree::AddAll(Vector < Node<Store>*>& vec,TreeNode* curr) {
	if (!curr) {
		return;


	}
	vec.push(curr->data);
	AddAll(vec,curr->right);
	AddAll(vec, curr->left);

}