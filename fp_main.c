#include<stdio.h>
#include<stdlib.h>
#include "fp_tree_gen.c"
#include <math.h>
int top=-1;
int *stack;
int *set;
int tree_top=0;

int check_stack(int x)
{
        int i;
        if(top==-1)
          return 0;

        for(i=0;i<=top;i++)
        {
                if(stack[i]==x)
                  return 1;
        }
        return 0;
}
void print(list *itemSet,int val)
{
        int i;
        printf("Transaction items sorted as per decreasing order of support value \n");
        printf("tid\tSupport\n");
        for(i=0;i<val;i++)
        {
                printf("%d\t%d\n",itemSet[i].tid,itemSet[i].support);
        
        }
    
}
void swap(list *itemSet,int i,int j)
{

        int temp=itemSet[i].tid;
        int temp1=itemSet[i].support;
        
        itemSet[i].tid=itemSet[j].tid;
        itemSet[i].support=itemSet[j].support;

        itemSet[j].tid=temp;
        itemSet[j].support=temp1;
        

}
void sort(list *itemSet,int val)
{
        int i,j;
        for(i=0;i<val;i++)
        {
                for(j=i+1;j<val;j++)
                {
                        if(itemSet[i].support<itemSet[j].support)
                        {
                                swap(itemSet,i,j);
                        
                        }
                
                }
        
        }

}
/*void print_pattern_frequent(tnode *ptr,tnode *root,tnode *parent,int x)
{
        
        if(ptr!=root && ptr!=parent)
        {
                if(ptr->parent==root)
                   glob_count+=x;       
                   
                   
                print_pattern_frequent(ptr->parent,root,parent,x);
                 
                //if(ptr->parent!=root)
       //         ptr->val_occur+=x;
                
               
        
        }
        
        

}*/

void print_pattern_base(tnode *ptr,tnode *root,int x,int val)
{
        if(ptr!=root)
        {
               if(val!=ptr->id && check_stack(ptr->id)==0)
               {
                 ++top;
                 stack[top]=ptr->id;               
                // printf("ok,%d,%d",ptr->id,top);
               }
                print_pattern_base(ptr->parent,root,x,val);
                //if(ptr->parent!=root)
                ptr->val_occur+=x;
                
                printf("\tI%d",ptr->id);
                
               
        
        }
        
        

}


int check_set(int val)
{
        int i;
        for(i=0;i<=tree_top;i++)
        {
                if(set[i]==val)
                  return 1;
        
        }
        return 0;
}
int find_freq(tnode *ptr,tnode *root)
{
        int count=0,counter=ptr->count;
        
        
        while(ptr!=root && count<=tree_top)
        {
               
               if(check_set(ptr->id)==1)
               {
                  //printf("\tI%d,%d",ptr->id,set[count]);          
                  count++;
                  
               
               }
               ptr=ptr->parent; 
                
               
        
        }
        if(count>tree_top)
           return counter;     
        else
           return 0;   
         

}

void conditional_pattern_base(list *itemSet,tnode *root,int uniq_trans,int threshold){

        tnode *ptr,*ptr1;
        int i,count,j,counter=0,glob_count=0;
        
        for(i=uniq_trans-1;i>0;i--)
        {
               
                count=1;
        
                ptr=itemSet[i].ptr;
                top=-1;
                while(ptr!=NULL)
                {
                        ptr=ptr->horizontal;
                        if(ptr!=NULL)
                                count++;             
                }
                //printf("%d\n",threshold);
                if(count>=threshold)
                {
                        printf("\nGenerating conditional pattern base \n");
                        ptr=itemSet[i].ptr;
                        do
                        {
                              if(ptr->parent!=root)
                              {
                                printf("< ");
                                print_pattern_base(ptr,root,ptr->count,ptr->id);
                                printf(": %d > , ",ptr->count);
                              }
                              ptr=ptr->horizontal;
                        
                        }while(ptr);
                        
                        printf("\nFrequent patterns generated\n");
                      
 
                        
                        set[0]=itemSet[i].ptr->id;
                        
                        for(counter = 0; counter < (pow(2,top+1)); counter++)
                        {
                             tree_top=0;
                              for(j = 0; j <=top; j++)
                              {
          /* Check if jth bit in the counter is set
             If set then pront jth element from set */
                                  if(counter & (1<<j))
                                     set[++tree_top]=stack[j]; //      printf("%d", stack[j]);
                              }


                              //printf("\n");
                              ptr=itemSet[i].ptr;
                              while(ptr!=NULL)
                              {
                                  glob_count+=find_freq(ptr,root);
                                  //printf("gc=%d  ",glob_count);
                                  ptr=ptr->horizontal;
                              }
                              
                              if(glob_count>=threshold && tree_top>0)
                              {
                                         for(j=0;j<=tree_top;j++)
                                          printf("I%d\t",set[j]);
                                         printf(":%d",glob_count); 
                                         printf("\n");
                              }
                              glob_count=0;
                              

                        }  
                         
/*                        ptr=itemSet[i].ptr;
                        ptr1=ptr->parent;
                        while(ptr1!=root)
                        {
                          do
                          {
                              
                              
                              
                                print_pattern_frequent(ptr,ptr1,root,ptr->count);
                                
                              
                              ptr=ptr->horizontal;
                        
                          }while(ptr);
                          printf("id:%d,%d\n",ptr1->id,glob_count);
                          if(glob_count>=threshold)
                          {
                               // push_stack(ptr1);
                                
                                printf(" (%d,%d) , ",itemSet[i].ptr->id,ptr1->id);
                          }
                          glob_count=0;
                          ptr=itemSet[i].ptr;
                          ptr1=ptr1->parent;
                          
                       }*/
                        
                }
                
                
                printf("\n");
        }                




}

int main(int argc,char *argv[])
{
        FILE *fp1=fopen(argv[1],"r");
        list *itemSet;
        tnode *root;
        char currentchar;
        int num_transaction,currentItem;
        
        int uniq_trans,i,j;
        int threshold=atoi(argv[2]);
        fscanf( fp1, "%d %d", &num_transaction, &uniq_trans);
        
        root=makenode(uniq_trans,-1);
        
        stack=(int*)malloc(uniq_trans*sizeof(int));
        set=(int*)malloc(uniq_trans*sizeof(int));
        itemSet=(list*)malloc(uniq_trans*sizeof(list));
        
        for(i=0;i<uniq_trans;i++)
        {
                itemSet[i].support=0;
                itemSet[i].ptr=NULL;

                
        }

        while( (fscanf(fp1,"%d", &currentItem))!=EOF )
        {
                
              
              itemSet[currentItem-1].support++; //increment current item's support count
              itemSet[currentItem-1].tid=currentItem;  
              fscanf(fp1,"%c", &currentchar);
            
        }

        sort(itemSet,uniq_trans);
        print(itemSet,uniq_trans);
        fclose(fp1);
        root=fp_tree_gen(root,itemSet,uniq_trans,argv[1]);
        printf("\nTree generated : \n");
        print_tree(root,uniq_trans);    
        
        
       
        
        conditional_pattern_base(itemSet,root,uniq_trans,threshold);
       
        
                
}
