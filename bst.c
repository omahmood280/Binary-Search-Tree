#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int value;
        struct _Node *left_child;
    struct _Node *right_child;

}Node; //This structure can now be referred to as just 'Node'

Node * addNode(Node * root, int value){ //adds a node to the tree
  
  Node *new = malloc(sizeof(Node)); // To later create the node that is to be returned
  
  Node*curr=root; //rather then changing the actual root contents in the while loop, this creates a pointer to work with instead
  
  Node*prev=NULL; // the return Node, which stays 1 step behind curr  throughout the loop so it can assign the node to be added as the child of another node

  //iteration is used over recursion as the Node to be inserted must also be returned
  
  while(curr!=NULL){ //this loop is to traverse to the Node's rightful position to be inserted in the tree
        if(value > curr->value){
            prev=curr;
	    curr = curr->right_child;
    }
        else if(value < curr->value){
            prev=curr;
    curr =  curr->left_child;
    }
    }
  // node position found
  
  if(prev==NULL){ //if parent node of the node is NULL (only happens when a new tree is created) 
            Node*new=malloc(sizeof(Node));
    new->value = value;
    new->left_child=NULL;
    new->right_child=NULL;
    prev = new;
    return prev;
    }
    
  if(prev->value > value){ //if the parent node is greater then the node to be inserted, it will become the parent's left child
        
            new->value = value;
    new->left_child=NULL;
    new->right_child=NULL;
        prev->left_child = new;
        return prev->left_child;
    }
  else if(prev->value < value){ //if the parent node is smaller then the node to be inserted, it will become the parent's right child
            new->value = value;
    new->left_child=NULL;
    new->right_child=NULL;
    
        prev->right_child = new;
        return prev->right_child;
    }
       else{
	 return NULL; 
       }
    
}

Node * removeNode(Node * root, int value){ //deletes a node from the tree
    
  if (root == NULL){ 
        return NULL;
    }

  //recursively goes down the tree until the node to be deleted is found (when root->value == value)
     else if(value > root->value){
      root->right_child =  removeNode(root->right_child, value); 
    }
        else if(value < root->value){
     root->left_child =  removeNode(root->left_child, value);
    }
    else{

      //position found

      
        //case no child.
        
        if(root->left_child == NULL && root->right_child ==NULL){
            free(root);
            return NULL;
        }
        
        // case 1 child
        
        
        
        if(root->left_child == NULL){
            Node *temp = root->right_child;
            free(root);
return temp;
}
        
        else if(root->right_child==NULL){
            Node *temp = root->left_child;
            free(root);
return temp;
}

        // case 2 children
        
        else{
	  //finds the left most child of the right subtree replace the to be deleted node
            Node *temp = root->right_child;
            while(temp->left_child != NULL){
                temp = temp->left_child;
            }
            root->value = temp->value; //copies the value of the left most child into the Node that is to be deleted
	    
	    root->right_child = removeNode(root->right_child, temp->value); //finds and deletes the child that just been copied  as it's value has been moved to another position in the tree, if it also has 2 children, this process is repeated
            
        }
        }
        return root;
    }

void displaySubtree(Node * N){ //displays an entire subtree in ascending order
  if (N != NULL){ 
 
    displaySubtree(N->left_child); //priority is always going as far left as possible, until the last left node is found
      printf("%d\n", N->value); //when a NULL value is returned it goes back in the call stack to the last node and prints it's value 
      displaySubtree(N->right_child);//right child is the last priority so it is checked and printed last, the function goes to find the left most child of this child
	
    }
}

int numberLeaves(Node * N){ //finds the number of leaves

    if(N==NULL){
        return 0;
    }

if(N->left_child == NULL && N->right_child == NULL){
  return 1; //if a leaf node is found
}
else {
  return numberLeaves(N->left_child) + numberLeaves(N->right_child); // recursive addition function which goes through every value in the tree and checks if it is a leaf node, if it is, 1 is to be added
}
}

Node * removeSubtree(Node * root, int value){ //removes sub tree
  if(root == NULL){
    return NULL;
  }
  
  if(value == root->value){ //if subtree value is found, time get to deleting it
    
    removeSubtree(root->left_child, value); // keeps going left till it returns a NULL value, in which case it goes back in the call stack to it's parent
    
    removeSubtree(root->right_child, value); // the parents node goes down to it's left most value in it's right subtree
    
    free(root); // when both the left and right child nodes have returned NULL, the node is now deleted
  }
 
  else if(value > root->value){ //recursively traverses the tree until the sub tree value to be deleted  is found
    root->right_child =  removeSubtree(root->right_child, value);
  }
  else if (value < root->value){
   root->left_child =  removeSubtree(root->left_child, value);
  }

  
    return NULL;
  

    
}

int nodeDepth (Node * R, Node * N){ //finds the depth of Node N from root R

    if(R==NULL || N == NULL)

      { 
        return -1; //-1 is returned if the node doesn't not exist 
    
    }

    else if(R->value == N->value){
      return 0; // when the target node is found, 0 is returned as there is already a '1 +' in the return statement when it goes back up the callstack, the line for it's parent to itself is already accounted for
    }
    else if (R->value < N->value){ // traverses the tree until it finds the target node, 1 is added each time it traverses as it has dropped a level in the tree each time  
     return  1 + nodeDepth(R->right_child, N); 
    }
    else{
       return  1 +  nodeDepth(R->left_child, N);
    }
}


