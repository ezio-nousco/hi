#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLACK 1


typedef struct tag_node
{
   struct tag_node *parent;
   int data;
   struct tag_node *left;
   struct tag_node *right;
   short color; // defalut is Red
}node;

node* StartofData = NULL;

//Get GrnadParent & Uncle & siblingSer
node* grandparent(node * current);
node* uncle(node * current);
node* sibling(node* current);

//Rotate Function for Red & Black Tree Sustaining the Count of each Red and
//Black node to same Layer Destination
void rotate_left(node *p, node *g);
void rotate_right(node *p, node *g);
void rotate_left_all(node *n);
void rotated_right_all(node *n);
void rotate_left_delete(node *n);
void rotate_right_delete(node *n);

//Insert Function
node* InsertNode(int value);
//Modules For Insert Function
void insert_case1(node *n); // For Root Node
void insert_case2(node *n); // General
void insert_case3(node *n); // When Parent And Uncle is Red
void insert_case4(node *n); // Ready for case 5
void insert_case5(node *n); // changing Parent and Grand Parent

//Modules For Delete Function
void delete_one_child(node *n);
void delete_case1(node* n);
void delete_case2(node* n);
void delete_case3(node* n);
void delete_case4(node* n);
void delete_case5(node* n);
void delete_case6(node* n);

int is_leaf(node *n);
node* replace_node(node *n, node* child);

//Find data in R&B tree
node* SearchNode(int value);
void DeleteNode(int value);
void Dump(node* root);
void InsertTest();
void DeleteTest();

//Deallocate All Data
void DeallocateAll(node *start);

void K_Reg_13();
void K_Reg_15();
void K_Reg_17();
void K_Reg_18();

int main(int argc, char * argv[])
{
    int input;

    while(1)
    {
        printf("Insert Test : 1\n");
        printf("Delete Test : 2\n");
        printf("Exit : 3\n");
        printf("K_Reg_13 : 13\n");
        printf("K_Reg_15 : 15\n");
        printf("K_Reg_17 : 17\n");
        printf("K_Reg_18 : 18\n");
        printf("Please Input Number For Test : ");
        scanf("%d", &input);
       

        switch(input)
        {
            case 1:
                InsertTest();
                break;
            case 2:
                DeleteTest();
                break;
            case 13 :
                K_Reg_13();
                break;
            case 15 :
                K_Reg_15();
                break;
            case 17 :
                K_Reg_17();
                break;
            case 18 :
                K_Reg_18();
                break;
            case 3:
                printf("Bye\n");
                DeallocateAll(StartofData);
                exit(0);
                break;
            default :
                printf("Please Input Correct Value\n");
        }

    }



    DeallocateAll(StartofData);

    return 0;
}


node* grandparent(node *current)
{
    if((current != NULL) && (current->parent != NULL))
    {
        return current->parent->parent;
    }
    else
    {
        return NULL;
    }
}


node* uncle(node * current)
{
    node * g = grandparent(current);

    if(g == NULL)
        return NULL;

    if((current->parent == g->left))
    {
        return g->right;
    }
    else
    {
        return g->left;
    }
}

node* sibling(node* current)
{
    if(current == current->parent->left)
    {
        return current->parent->right;
    }
    else
    {
        return current->parent->left;
    }
}

void rotate_left(node *p, node *g)
{
    if ((p == NULL) || (g == NULL))
        return;


    node *n = p->right;
    node * saved_left = n->left;

    g->left = n;
    n->parent = g;
    n->left = p;
    p->parent = n;
    p->right = saved_left;

    if(saved_left != NULL)
    {
        saved_left->parent = p;
    }
}

void rotate_right_all(node *n)
{
    node * g = grandparent(n);
    node * saved = n->parent->right;

    if(g == NULL)
    {
        return ;
    }
    n->parent->right = g;

    if((g->parent != NULL) && (g == g->parent->left))
    {
       g->parent->left = n->parent;
       n->parent->parent = g->parent;
    }
    else if((g->parent != NULL) && (g == g->parent->right))
    {
        g->parent->right = n->parent;
        n->parent->parent = g->parent;
    }
    else
    {
        n->parent->parent = NULL;
        StartofData = n->parent;
    }
    g->parent = n->parent;
    g->left = saved;

    if(saved != NULL)
    {
        saved->parent = g;
    }

}

void rotate_left_delete(node *n)
{
    node *saved  = n->left;
    node *p = n->parent;

    if(p->parent == NULL)
    {
        n->parent = NULL;
        StartofData = n;
    }
    else
    {
		n->parent = p->parent;

		if(p == p->parent->left)
        {
            p->parent->left = n;
        }
        else if( p == p->parent->right)
        {
            p->parent->right =n;
        }
    }
	
    p->parent = n;
    n->left = p;
	p->right = saved;
	if (saved != NULL)
	{
		saved->parent = p;
		if (saved->left == NULL && saved->right == NULL &&
			saved->parent->color == RED && saved->color == BLACK)
		{
			saved->color = RED;
			saved->parent->color = BLACK;
		}
	}
    

	
}

void rotate_right_delete(node *n)
{
    node *saved = n->right;
    node *p = n->parent;

    if(p->parent == NULL)
    {
        n->parent = NULL;
        StartofData = n;
    }
    else
    {
		n->parent = p->parent;

		if(p == p->parent->left)
        {
            p->parent->left = n;
        }
        else if(p == p->parent->right)
        {
            p->parent->right = n;
        }
    }
	n->parent = p->parent;
    p->parent = n;
    n->right = p;
	p->left = saved;
	if (saved != NULL)
	{
		saved->parent = p;
		if (saved->left == NULL && saved->right == NULL &&
			saved->parent->color == RED && saved->color == BLACK)
		{
			saved->color = RED;
			saved->parent->color = BLACK;
		}
	}

	

	
}



void rotate_left_all(node *n)
{
    node *g = grandparent(n);
    node *saved = n->parent->left;

    if(g == NULL)
    {
        return;
    }
    n->parent->left = g;

    if((g->parent != NULL) && (g == g->parent->left))
    {
        g->parent->left = n->parent;
        n->parent->parent = g->parent;
    }
    else if((g->parent != NULL) && (g == g->parent->right))
    {
        g->parent->right = n->parent;
        n->parent->parent = g->parent;
    }
    else
    {
        n->parent->parent = NULL;
        StartofData = n->parent;
    }
    g->parent = n->parent;
    g->right = saved;

    if(saved != NULL)
    {
        saved->parent = g;
    }
}

void rotate_right(node *p, node *g)
{

    if ((p == NULL) || (g == NULL))
        return;

    node *n = p->left;
    node * saved_right = n->right;

    g->right = n;
    n->parent = g;
    n->right =p;
    p->parent = n;
    p->left = saved_right;

    if(saved_right != NULL)
    {
        saved_right->parent = p;
    }
}

node* InsertNode(int value)
{
    node * next;
    node * current;

    if(SearchNode(value) != NULL)
    {
        printf("Already Exist Value\n");
        return;
    }

    node * this = (node *)malloc(sizeof(node));
    this->data = value;
    this->color = RED;
    this->right = NULL;
    this->left = NULL;
    this->parent =NULL;


    if(StartofData != NULL)
    {
        for (current = StartofData;;current = next)
        {
            if(current->data > this->data)
            {
                next = current->left;

                if(next == NULL)
                {
                    current->left = this;
                    this->parent = current;
                    break;
                }
            }
            else
            {
                next = current->right;

                if(next == NULL)
                {
                   current->right = this;
                   this->parent = current;
                   break;
                }

            }
        }
    }
    else
    {
        StartofData = this;
    }

    insert_case1(this);
    return this;
}

node * SearchNode(int value)
{
    node* current;


    for(current = StartofData;;)
    {
        if(current == NULL)
        {
            return NULL;
        }

        if(current->data == value)
        {
            return current;
        }
        else
        {
           if(current->data > value)
           {
              current = current->left;
           }
           else
           {
              current = current->right;
           }
        }
    }

    return NULL;
}

void DeleteNode(int value)
{
    node* target = SearchNode(value);

    if(target == NULL)
    {
        printf("There is no data in Tree u want to delete\n");
        return;
    }
    delete_one_child(target);
}

// Module Start!
void insert_case1(node *n)
{

    if(n->parent == NULL)
    {
        n->color = BLACK;
    }
    else
    {
        insert_case2(n);
    }
}

void insert_case2(node *n)
{
    if(n->parent->color == BLACK)
    {
        return ;
    }
    else
    {
        insert_case3(n);
    }
}

void insert_case3(node *n)
{
    node *u = uncle(n), *g;

    if((u != NULL) && ( u->color == RED))
    {
        n->parent->color = BLACK;
        u-> color = BLACK;
        g = grandparent(n);
        g->color = RED;
        insert_case1(g);
    }
    else
    {
        insert_case4(n);
    }
}

void insert_case4(node *n)
{
    node *g = grandparent(n);
    if (g == NULL)
        return;

    if((n == n->parent->right) && (n->parent == g->left))
    {
        rotate_left(n->parent, g);
        n = n->left;
    }
    else if((n == n->parent->left) && (n->parent == g->right))
    {
        rotate_right(n->parent, g);
        n = n->right;
    }

    insert_case5(n);
}


void insert_case5(node *n)
{
    node *g = grandparent(n);
    if (g == NULL)
        return;

    n->parent->color = BLACK;
    g->color = RED;

    if((n->parent->left != NULL) && (n == n->parent->left))
    {
        rotate_right_all(n);
    }
    else if((n->parent->right != NULL) && (n == n->parent->right))
    {
        rotate_left_all(n);
    }
}

//Delete Module
void delete_one_child(node *n)
{

    if(n->left != NULL || n->right != NULL)
    {
        node *child = (is_leaf(n->right) == 1) ? n->right : n->left;
		/*
        if(n->parent != NULL)
        {
            if(n == n->parent->left)
            {
                n->parent->left = NULL;
            }
            else if(n == n->parent->right)
            {
                n->parent->right = NULL;
            }
        }
        */
        child = replace_node(n, child);
        if(n->color == BLACK)
        {
            if(child->color == RED)
            {
                child->color = BLACK;
            }
            else
            {
				delete_case1(child);
            }

        }
    }
    else
    {
        if(n->parent == NULL)
        {
            StartofData = NULL;
            free(n);
            return;
        }
        else
        {
            if(n->color = BLACK &&
                n->parent->color == RED)
            {
                node * s = sibling(n);
                n->parent->color = BLACK;

                if(s != NULL)
                {
                    s->color = RED;

                    if(s->left != NULL || s->right != NULL)
                    {
                        if(s == n->parent->right)
                        {
                            rotate_left_all(s->right);
                            if(s->right->color == RED)
                            {
                                s->right->color = BLACK;
                            }
                        }
                        else if(s == n->parent->left)
                        {
                            rotate_right_all(s->left);

                            if(s->left->color == RED)
                            {
                                s->left->color = BLACK;
                            }
                        }
                    }
                }

            }
			else
			{
				delete_case1(n);
			}
        }
   }







    if(n->left == NULL && n->right == NULL)
    {
		node *ts = sibling(n);

		if(n == n->parent->left)
        {
            n->parent->left = NULL;
        }
        else if(n == n->parent->right)
        {
            n->parent->right = NULL;
        }
    
		if (ts != NULL)
		{
			if (ts->left == NULL && ts->right == NULL && ts->color == BLACK)
			{
				ts->color = RED;
			}
		}
	}

    free(n);

}

void delete_case1(node* n)
{
    if(n->parent != NULL)
        delete_case2(n);

	if (n->left != NULL && n->right == NULL)
	{
		if (n->left->left == NULL && n->left->right == NULL)
		{
			if (n->left->color == BLACK)
			{
				n->left->color = RED;
			}
		}
	}
	else if (n->right != NULL && n->left == NULL)
	{
		if (n->right->left == NULL && n->right->left == NULL)
		{
			if (n->right->color == BLACK)
			{
				n->right->color = RED;
			}
		
		}
	}
	
}

void delete_case2(node* n)
{
   node *s = sibling(n);

   if(s != NULL)
   {
        if(s->color == RED)
        {
            n->parent->color = RED;
            s->color = BLACK;
            if(n == n->parent->left)
            {
                rotate_left_delete(s);
            }
            else
            {
				rotate_right_delete(s);
            }
        }
		else if (s->right != NULL || s->left != NULL)
        {
			if (n->left == NULL && n->right == NULL
				&& n->parent->left == n && ((s->right->color == RED && s->left == NULL) || (s->left->color == RED && s->right == NULL)))
			{
				if ((s->right->color == RED && s->left == NULL))
				{
					s->right->color = BLACK;
					
				}
				else if((s->left->color == RED && s->right == NULL))
				{
					rotate_right(s, s->parent);
					s->right->color = BLACK;

				}

				rotate_left_delete(s);

			}
			else if (n->left == NULL && n->right == NULL
				&& n->parent->right == n && ((s->right->color == RED && s->left == NULL) || (s->left->color == RED && s->right == NULL)))
			{
				if ((s->right->color == RED && s->left == NULL))
				{
					rotate_left(s, s->parent);
					s->left->color = BLACK;
				}
				else
				{
					s->left->color = BLACK;
				}
				rotate_right_delete(s);
			}
        }


   }
}

void delete_case3(node *n)
{
    node *s = sibling(n);

    if((s != NULL) && (s->left != NULL) && (s->right != NULL))
    {
        if((n->parent->color == BLACK) &&
           (s->color == BLACK) &&
           (s->left->color == BLACK) &&
           (s->right->color == BLACK))
        {
            s->color = RED;
            delete_case1(n->parent);
        }
        else
        {
            delete_case4(n);
        }
    }
}

void delete_case4(node *n)
{
    node *s = sibling(n);

    if((s != NULL) && (s->left != NULL) && (s->right != NULL))
    {
        if((n->parent->color == RED) &&
           (s->color == BLACK) &&
           (s->left->color == BLACK) &&
           (s->right->color == BLACK))
        {
            s->color = RED;
            n->parent->color = BLACK;
        }
    }
    else
    {
        delete_case5(n);
    }
}

void delete_case5(node *n)
{
    node* s = sibling(n);

    if((s != NULL) && (s->left != NULL) && (s->right != NULL))
    {
        if(s->color == BLACK)
        {
            if((n == n->parent->left) &&
               (s->right->color == BLACK) &&
               (s->left->color == RED))
            {
                s->color = RED;
                s->left->color = BLACK;
				rotate_right_delete(s->left);
            }
            else if((n == n->parent->right) &&
                    (s->left->color == BLACK) &&
                    (s->right->color == RED))
            {
                s->color = RED;
                s->right->color = BLACK;
				rotate_left_delete(s->right);
            }
        }

        delete_case6(n);
    }
}

void delete_case6(node* n)
{
    node* s = sibling(n);

    if((s != NULL) && (s->left != NULL) && (s->right != NULL))
    {
       s->color = n->parent->color;
       n->parent->color = BLACK;

       if(n == n->parent->left)
       {
            s->right->color = BLACK;
			rotate_left_delete(s);
       }
       else
       {
            s->left->color = BLACK;
			rotate_right_delete(s);
       }
    }
}


int is_leaf(node* n)
{
    if(n != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

node* replace_node(node *n, node* child)
{
    node *start;
    node *next;

    if(child == n->left)
    {
        for(start = child;; start=next)
        {
           if(start->right == NULL)
           {
              if((n->parent != NULL) &&(n == n->parent->left))
              {
                n->parent->left = start;
              }
              else if((n->parent != NULL) && (n == n->parent->right))
              {
                n->parent->right = start;
              }

              if(start != child)
              {
                start->parent->right = start->left;

                if(start->left !=NULL)
                {
                    start->left->parent = start->parent;
                }

                start->left = n->left;
                start->right = n->right;
                if(n->left != NULL)
                {
                    n->left->parent = start;
                }
                if(n->right != NULL)
                {
                    n->right->parent = start;
                }


              }
              else if(start == child)
              {
                start->right = n->right;

                if(n->right != NULL)
                    n->right->parent = start;
              }


              if(n->parent != NULL)
              {
                  start->parent = n->parent;
              }
              else if( n->parent == NULL)
              {
                start->parent = NULL;
                StartofData = start;
              }
              return start;
              break;
           }
           else
           {
             next = start->right;
           }
        }
    }
    else if(child == n->right)
    {
        for(start = child;; start = next)
        {
            if(start->left == NULL)
            {
                if((n->parent != NULL) && (n == n->parent->left))
                {
                    n->parent->left = start;
                }
                else if((n->parent != NULL) && (n == n->parent->right))
                {
                    n->parent->right = start;
                }
                if(start != child)
                {
                    start->parent->left = start->right;
                    if(start->right != NULL)
                    {
                        start->right->parent = start->parent;
                    }
                    start->left = n->left;
                    start->right = n->right;

                    if(n->left != NULL)
                    {
                        n->left->parent = start;
                    }
                    if(n->right != NULL)
                    {
                        n->right->parent = start;
                    }
                }
                else if(start == child)
                {
                    start->left = n->left;

                    if(n->left != NULL)
                        n->left->parent = start;
                }

                if(n->parent != NULL)
                {
                    start->parent = n->parent;
                }
                else if(n->parent == NULL)
                {
                   start->parent = NULL;
                   StartofData = start;
                }

                return start;
                break;
            }
            else
            {
                next = start->left;
            }
        }
    }
    return NULL;
}

void DeallocateAll(node *start)
{
    if(start == NULL)
        return;

    if(start->left != NULL)
    {
        DeallocateAll(start->left);
    }

    if(start->right != NULL)
    {
        DeallocateAll(start->right);
    }

    free(start);
    return;
}


void InsertTest()
{
    int i;

    for(i = 1; i < 10; i++)
    {
       InsertNode(i);
    }
    Dump(StartofData);

    if(StartofData->color != BLACK)
    {
        printf("Error\n");
    }

}

void Dump(node *root)
{
    int i;

    if(root == NULL)
    {
        return;
    }


    printf("Parent : %d || ", (root->parent == NULL)? -1 : root->parent->data);
    printf("Data : %d  || Color :  %s\n", root->data, (root->color)?
               "BLACK" : "RED");

    Dump(root->left);
    Dump(root->right);
}

void DeleteTest()
{
    int input;

    printf("Please Input Delete Number 1~100 : "  );
    scanf("%d", &input);
    

    if(!(input >0 && input < 101))
    {
       printf("Wrong Number : ");
       return;
    }

    DeleteNode(input);

    if(SearchNode(input) == NULL)
    {
        printf("Success!\n");
    }
    Dump(StartofData);

}

void K_Reg_13()
{
   int i;

   for(i = 0; i < 10; i++)
   {
        InsertNode(i);
   }

   DeleteNode(6);
   Dump(StartofData);
   DeallocateAll(StartofData);
   StartofData = NULL;

}

void K_Reg_15()
{
    int i;
    for(i = 0; i < 10; i++)
    {
        InsertNode(i);
    }

    DeleteNode(4);
    Dump(StartofData);
    DeallocateAll(StartofData);
    StartofData = NULL;
}

void K_Reg_17()
{
    int i;
    for(i = 0; i< 10; i++)
    {
        InsertNode(i);
    }
    DeleteNode(5);
    DeleteNode(6);
    for(i = 0; i < 10; i++)
    {
        InsertNode(i);
    }
    DeleteNode(5);
    DeleteNode(6);
    Dump(StartofData);
    DeallocateAll(StartofData);
    StartofData = NULL;
}

void K_Reg_18()
{
    int i;
    for(i = 0; i < 10; i++)
    {
        InsertNode(i);
    }
    DeleteNode(3);
    for(i = 0; i < 10; i++)
    {
        InsertNode(i);
    }
    DeleteNode(4);
    DeleteNode(5);
    DeleteNode(6);
    Dump(StartofData);
    DeallocateAll(StartofData);
    StartofData = NULL;
}
