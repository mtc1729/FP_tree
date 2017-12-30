#include "tree_struct.h"
int search(int id,list *itemset,int uniq_trans)
{
     int i;
     for(i=0;i<uniq_trans;i++)
     {
        if(itemset[i].tid==id)
        {
        
                return i;
        }
     
     }

}

void clear(int *tid,int uniq_trans)
{
        int i;
        for(i=0;i<uniq_trans;i++)
        {
                tid[i]=-1;
        
        }       

}     
        
tnode *fp_create(tnode *root,int *tid,int uniq_val,list *itemset)
{

        tnode *ptr=root,*ptr1;
        int flag=0,i;
        for(i=0;i<uniq_val;i++)
        {
                
                if(tid[i]!=-1)
                {
                         //printf("dfjwrg");
//                         printf("tid_act : %d\n",tid[i]);
                         if(ptr->children[tid[i]-1]==NULL)
                         {
                           //   printf("tid : %d\n",tid[i]);
                                
                                ptr->children[tid[i]-1]=makenode(uniq_val,tid[i]);
                                ptr->children[tid[i]-1]->parent=ptr;
                                if(itemset[i].ptr==NULL){
                        
                                  itemset[i].ptr=ptr->children[tid[i]-1];                                  
                                  
                                }
                                else
                                {
                                     ptr1=itemset[i].ptr;
                                     while(ptr1->horizontal!=NULL)
                                        ptr1=ptr1->horizontal;
                                        
                                     ptr1->horizontal=ptr->children[tid[i]-1];   
                                
                                }
                                
                                
                         
                         }
                         else
                         {
                                ptr->children[tid[i]-1]->count++;
                         
                         }
                         ptr=ptr->children[tid[i]-1];
                         
                
                }
        
        }
        return root;

}

void print_tree(tnode *root, int uniq_val)
{
        int i;
        if(root!=NULL)
        {
                for(i=0;i<uniq_val;i++)
                {
                        if(root->children[i]!=NULL)
                         {
                                if(root->children[i]->parent->id==-1)
                                
                                        printf("Node : %d < support : %d , parent : null > ----> \t",root->children[i]->id,root->children[i]->count);
                                else        
                                        printf("Node : %d < support : %d , parent : %d > ----> \t",root->children[i]->id,root->children[i]->count,root->children[i]->parent->id);
                                print_tree(root->children[i], uniq_val);
                                
                                
                                printf("\n");
                                
                        
                        }
                       
                                
                }       

        }
       

}

tnode *fp_tree_gen(tnode *root,list *itemset,int uniq_trans,char *file_name)
{
        
        int n,k,x;
        char id,i;
        int id_val;        
        FILE *fp1=fopen(file_name,"r");
       
        int *tid=(int*)malloc(uniq_trans*sizeof(int));
                     
        fscanf(fp1,"%d %d\n",&n,&k);
        clear(tid,uniq_trans);
        

       
        while(fscanf(fp1,"%d%c",&id_val,&id)!=EOF)
        {
                      

                         
                          x=search(id_val,itemset,uniq_trans);
                          tid[x]=id_val;
                          
                               
               // printf("tid:%c,%d\n",id,id);
                if(id==';')
                {
                  //     printf("tid_enter:%d\n",id);
                        root=fp_create(root,tid,uniq_trans,itemset);
                        clear(tid,uniq_trans);
                        
                        
                }
                
             
        }
        fclose(fp1);   

        return root;

}

