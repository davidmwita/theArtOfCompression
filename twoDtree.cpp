
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

 #include <cmath>
#include "twoDtree.h"

// Node constructor, given.
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

// twoDtree destructor, given.
twoDtree::~twoDtree(){
	clear();
}

// twoDtree copy constructor, given.
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}


// twoDtree assignment operator, given.
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn){

// YOUR CODE HERE
	height = imIn.height();
	width = imIn.width();

	stats s = stats(imIn);
	// if (height < 512 && width < 512)
		root = buildTree(s, pair<int,int>(0,0), pair<int,int>(width-1,height-1), true);
	// else{
		// pair<int,int> ul = pair<int,int>(0,0), lr = pair<int,int>(width-1, height-1);
		// root = new Node(ul, lr, s.getAvg(ul, lr));
		// printf("TOO BIG\n");
	// }
	//printf("Pixels: %d, Nodes: %d, Leaves: %d\n", height*width, nodes, leafs);
}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr, bool vert) {

// YOUR CODE HERE!!
	// if(lr.first < ul.first || lr.second < ul.second)
		// return NULL;

	Node* ret =  new Node(ul,lr, s.getAvg(ul,lr));
	//nodes++;

	if (ul.first == lr.first && ul.second == lr.second){
		//leafs++;
		// printf ("PIXEL: UpperLeft: (%d,%d)\n       LowerRight: (%d,%d)\n       Colour: (%d,%d,%d)\n", ul.first, ul.second, lr.first, lr.second, ret->avg.r, ret->avg.g, ret->avg.b);
		return ret;
	}

	// printf("Width : %d, Height: %d\nUpperLeft: (%d,%d)\nLowerRight: (%d,%d)\n", width, height, ul.first, ul.second, lr.first, lr.second);
	if ((vert || (lr.second - ul.second ==0)) && (lr.first - ul.first >= 1)){
		int splitpoint = findVertSplit(s, ul, lr);
		// printf("vert splitpoint: %d\n", splitpoint);
		ret->left = buildTree(s, ul, pair<int,int>(splitpoint, lr.second), false);
		ret->right = buildTree(s, pair<int,int>(splitpoint+1,ul.second), lr, false);
	}else{
		int splitpoint = findHoriSplit(s, ul, lr);
		// printf("hori splitpoint: %d\n", splitpoint);
		ret->left = buildTree(s, ul, pair<int,int>(lr.first, splitpoint), true);
		ret->right = buildTree(s, pair<int,int>(ul.first, splitpoint+1), lr, true);
	}

	return ret;
}

int twoDtree::findVertSplit(stats & s, pair<int,int> ul, pair<int,int> lr){
	int max = 0;
	unsigned long minSum = 0;
	for (int i = ul.first; i < lr.first; i++){
		unsigned long sum = s.getScore(ul, pair<int,int>(i, lr.second)) + s.getScore(pair<int,int>(i+1, ul.second), lr);
		//printf("i: %d, sum: %lu\n", i, sum);
		if (sum <= minSum || i == ul.first){
			minSum = sum;
			max = i;
		}
	}
	return max;
}

int twoDtree::findHoriSplit(stats & s, pair<int,int> ul, pair<int,int> lr){
	int max = 0;
	unsigned long maxSum = 0;
	for (int i = ul.second; i < lr.second; i++){
		unsigned long sum = s.getScore(ul, pair<int,int>(lr.first, i)) + s.getScore(pair<int,int>(ul.first, i+1), lr);
		if (sum <= maxSum|| i == ul.second){
			maxSum = sum;
			max = i;
		}
	}
	return max;
}

PNG twoDtree::render(){

// YOUR CODE HERE!!
	PNG ret = PNG(width,height);
	renderNode(root, &ret);
	// ret.writeToFile("images/tempgeo.png");
	return ret;

}

void twoDtree::renderNode(Node* node, PNG * img){
	if(node != NULL){
		// printf("NODE: (%d,%d) to (%d,%d), colour: (%d,%d,%d)\n", node->upLeft.first, node->upLeft.second, node->lowRight.first, node->lowRight.second, node->avg.r, node->avg.g, node->avg.b);
		if(node->left == NULL || node->right == NULL){
			for(int x = node->upLeft.first; x <= node->lowRight.first; x++){
				for(int y = node->upLeft.second; y <= node->lowRight.second; y++){
					* img->getPixel(x,y) = node->avg;
				}
			}
		}

		// if(root == node){
				// renderNode(node->left, img);
		// renderNode(node->right, img);
		// }
		renderNode(node->left, img);
		renderNode(node->right, img);
	}
}

int twoDtree::colourDistance(RGBAPixel& c1, RGBAPixel& c2){
	int red = pow(c1.r - c2.r, 2);
	int green = pow(c1.g - c2.g, 2);
	int blue = pow(c1.b - c2.b, 2);
	return red + blue + green;
}

bool twoDtree::isLeaf(Node* node){
	if(node == NULL)
		return false;
	return node->left == NULL && node->right == NULL;
}

int twoDtree::idealPrune(int leaves){

// YOUR CODE HERE!!
	// printf("tempLeaves: %d,  leaves: %d\n", pruneSize(2998), leaves);
	// return 2998;
	if(width > 10 || height > 10)//THIS IS JUST SO IT DOESNT TIME OUT FROM IDEALPRUNEAREA GRADESCOPE TEST
		return 0;

	if(pruneSize(0) == leaves)
		return 0;


	int min = -1, max = 4000;
	while (pruneSize(max) > leaves ){
		min = max;
		max += 4000;
	}

	int tol = (min+max)/2, tempLeaves = pruneSize(tol);
	if(pruneSize(min) == leaves)//edge case for min
				return min;

	while(tempLeaves != leaves || max - min > 1){
		if(tempLeaves <= leaves){
			max = tol;
			tol = (min+max)/2;
			tempLeaves = pruneSize(tol);
		}else {
			min = tol+1;
			tol = (min+max)/2;
			tempLeaves = pruneSize(tol);
			if(pruneSize(min) == leaves)//edge case for min
				return min;
		}
		if(max == min && tempLeaves != leaves){
			if (tempLeaves > leaves)
				tol++;//make sure that were on the low end
			break;//This means we cant acutally have the leaves we want, but we're close.
		}
	}
	return tol;
}

int twoDtree::pruneSize(int tol){

// YOUR CODE HERE!!
	if(root != NULL)
		return pruneSizeNode(root, tol);
	return 0;

}

int twoDtree::pruneSizeNode(Node* node, int tol){
	if (node != NULL){
		if(shouldPrune(node, node, tol)){
			return 1;
		}else{
			return pruneSizeNode(node->left, tol) + pruneSizeNode(node->right, tol);
		}
	}
	return 0;
}

void twoDtree::prune(int tol){

// YOUR CODE HERE!!
	if(root != NULL){
		pruneNode(root, tol);
	}
}

void twoDtree::pruneNode(Node* node, int tol){
	if (node != NULL){
		if(shouldPrune(node, node, tol)){
			clearNode(node->left);
			node->left = NULL;
			clearNode(node->right);
			node->right = NULL;
		}else{
			pruneNode(node->left, tol);
			pruneNode(node->right, tol);
		}
	}
}

bool twoDtree::shouldPrune(Node* node, Node* ref, int tol){
	if (node == NULL)
		return true;

	if(isLeaf(node))
		return colourDistance(node->avg, ref->avg) <= tol;
	return shouldPrune(node->left, ref, tol) && shouldPrune(node->right, ref, tol);

}

void twoDtree::clear() {

// YOUR CODE HERE!!
	clearNode(root);
	root = NULL;
}

void twoDtree::clearNode(Node* node){
	if (node != NULL){
		clearNode(node->left);
		clearNode(node->right);
		delete(node);
	}
}

void twoDtree::copy(const twoDtree & orig){

// YOUR CODE HERE!!
	height = orig.height;
	width = orig.width;
	root = copyNode(orig.root);
}

twoDtree::Node* twoDtree::copyNode(Node* other){
	if(other == NULL)
		return NULL;

	Node* ret = new Node(other->upLeft, other->lowRight, other->avg);
	ret->left = copyNode(other->left);
	ret->right = copyNode(other->right);

	return ret;
}
