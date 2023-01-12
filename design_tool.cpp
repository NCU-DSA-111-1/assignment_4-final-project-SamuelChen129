#include<stdio.h>
#include<stdlib.h>
#include"logic.h"
#include"design_tool.h"


void intro()
{
    printf("*******************************************************************************\n");
    printf("welcome for using logic_gate_ckt_simulator!\n");
    printf("u can compose the ckt u want with the basic gates and the blocks you created!\n");
    printf("and the ckt u make will be displayed in the other window!\n");
    printf("*******************************************************************************\n");
}

void what_to_do()
{
    printf("what do you want to do?\n");
    printf("if you want to add a block to ckt, enter 'a'\n");
    printf("if you want to make this ckt as a block, enter 'b'\n");
    printf("if you want to test the ckt, enter 't'\n");
    printf("if you want to save the ckt, enter 's'\n");
    printf("if you want to quit, enter 'q'\n");
}

void block_info(char** list,int num)
{
    printf("the list below are available gates and blocks \n");
    printf("please choose the type of block you now want to add:\n");
    for(int i=0;i<num;i++)
    {
        printf("| %d : %s ",i,list[i]);
    }
    printf("\n");
};

void update_type_list(char** list,int* num,char* add)//add new created block to the type list
{
    *num=*num+1;
    list[*num-1]=(char*)malloc(sizeof(char));
    list[*num-1]=add;
}

block* make_gate(int label,int type,bool v)
{
    block *new_gate;
    new_gate=(block*)malloc(sizeof(block));
    
    new_gate->type=type;
    new_gate->name=label;
    new_gate->out_num=1;
    if(type==3)
        new_gate->in_num=1;
    if(type>=4 && type<=9)
        new_gate->in_num=2;
    new_gate->value=0; 
    if(type==1)
        new_gate->value=v;
    new_gate->ready=false;
    new_gate->beside=NULL;

    block* input;
    input=(block*)malloc(sizeof(block));
    input->type=1;
    input->name=0;
    input->out_num=0;
    input->in_num=0;
    input->value=0;
    input->in_1=NULL;
    new_gate->in_1=input;

    block* tmp;
    tmp=input;
    for(int i=1;i<(new_gate->in_num);i++)
    {
        block* other_input;
        other_input=(block*)malloc(sizeof(block));
        other_input->type=1;
        other_input->name=0;
        other_input->out_num=0;
        other_input->in_num=0;
        other_input->value=0;
        other_input->in_1=NULL;
        tmp->beside = other_input;
        tmp = other_input;
    }
    tmp->beside=NULL;
    return new_gate;
}

void connect_to_input(block* b_target,block* b_new)
{
    block* in;
    block* tmp;
    block* tmp1;
    block* last_in;
    in=b_target;
    tmp1= (in->in_1);
    
    if(tmp1->type==1)
    {
        tmp=(in->in_1);
        (in->in_1) = b_new;
        (b_new->beside)=(tmp->beside);
        free(tmp);
    }
    if((tmp1->type)>1)
    {
        in=(in->in_1);
        while((in->type)!=1)
        {
            last_in = in;
            in = (in->beside) ;
        }
        tmp = in;
        (last_in->beside) = b_new;
        (b_new->beside)=(tmp->beside);
        free(tmp);
    }     
}

int max(int a[],int n)
{
    int max=0;
    for(int i=0;i<n;i++)
    {
        if(max<a[i])
            max=a[i];
    }
    return max;
}

int get_level(block* b)
{
    int input_level[b->in_num];
    int n=(b->in_num);
    block* tmp; 
    tmp=(b->in_1);
    bool is_level_0=true;
    for(int i=0;i<n;i++)
    {
        if( (tmp->type) > 2 && (tmp!=NULL) )
        {
            is_level_0=false;
            break;
        }
        tmp=(tmp->beside);
    }
    if(is_level_0)
        return 0;
    if(!is_level_0)
    {
        tmp=(b->in_1);
        for(int i=0;i<n;i++)
        {
            input_level[i]=get_level(tmp);
            tmp=(tmp->beside);
            if(tmp==NULL)
                break;
        }
        int gate_level=max(input_level,n)+1;
        return gate_level;
    }
}
void ask_for_test(block* ckt)
{
    printf("wanna test the output value?(y/n)");
    char y_n;
    scanf(" %c",&y_n);
    if(y_n=='y' or y_n=='Y')
    {
        get_value(ckt);
        printf("output : %d\n",ckt->value);
    }
}
void reset_ready(block* ckt)
{
    if(ckt==NULL || (ckt->type)<3)
        return;
    if((ckt->type)>=3)
        (ckt->ready)=false;
    reset_ready(ckt->in_1);
    reset_ready(ckt->beside);
}

void get_value(block* ckt_o)
{
    bool input[(ckt_o->in_num)];
    bool out=false;
    block* in;
    in = (ckt_o->in_1);
    for(int i=0;i<(ckt_o->in_num) && !(ckt_o->ready) ;i++)
    {
        if(in->type==1)
        {
            // connect input to the target logic gate
            printf("enter the input value : ");
            int t;
            scanf(" %d",&t);
            bool v;
            v=t;
            in->value=v;
        }
        else
            get_value(in);
        input[i] = (in->value);
        in = (in->beside);
    }

    if(!ckt_o->ready)
    {
        switch(ckt_o->type)
        {
            case 3:out=inv_gate(input[0]);break;
            case 4:out=and_gate(input[0],input[1]);break;
            case 5:out=or_gate(input[0],input[1]);break;
            case 6:out=nand_gate(input[0],input[1]);break;
            case 7:out=nor_gate(input[0],input[1]);break;
            case 8:out=xor_gate(input[0],input[1]);break;
            case 9:out=nxor_gate(input[0],input[1]);break;
            default: break;
        }
        ckt_o->value=out;
    }

    ckt_o->ready=true;

}

same_level_blocks* push(same_level_blocks* queue,int n)
{
    same_level_blocks* p;
    same_level_blocks* tmp;
    p=(same_level_blocks*)malloc(sizeof(same_level_blocks));
    p->label=n;
    p->next=queue;
    queue=p;
    return queue;
};

same_level_blocks* pop(same_level_blocks* queue,int* out)
{
    if(queue==NULL)
    {
        return queue;
    }
    same_level_blocks* tmp;
    tmp=queue;
    if(queue->next==NULL)
    {
        (*out)=(queue->label);
        queue=queue->next;
        free(tmp);
        return queue;
    }
    same_level_blocks* last_tmp;
    while((tmp->next)!=NULL)
    {
        last_tmp=tmp;
        tmp=tmp->next;
    }
    (*out)=(tmp->label);
    last_tmp->next = NULL;
    free(tmp);
    return queue;
}
void sort_to_same_level(block* list[],int *label,int max_level,same_level_blocks *level[])
{
    (*label)++;
    for(int i=1;i<(*label);i++)
    {
        int lvl;
        lvl=get_level(list[i]);
        level[lvl]=push(level[lvl],i);
    }
    /*for(int i=0;i<=max_level;i++)
    {
        same_level_blocks* show;
        show=level[i];
        printf("level %d : ",i);
        while(show!=NULL)
        {
            printf("%d ",show->label);
            show=(show->next);
        }
        printf("\n");
    }*/   
}




