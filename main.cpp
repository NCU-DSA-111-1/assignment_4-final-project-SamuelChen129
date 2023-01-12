#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include"logic.h"
#include"design_tool.h"
#include"display.h"

void test_block(block* b)
{
    printf("type : %d\n",b->type);
    printf("name : %d\n",b->name);
    printf("out_num : %d\n",b->out_num);
    printf("in_num : %d\n",b->in_num);
    block* input1;
    input1=b;
    input1=(input1->in_1);
    if(input1!=NULL)
        printf("input1 : %d\n",input1->type);
    else
        printf("input1 is NULL\n");
                
    block* input2;
    input2=b;
    input2=(input1->beside);
    if(input2!=NULL)
        printf("input2 : %d\n",input2->type);
    else
        printf("input2 is NULL\n");
    printf("\n");
}
void draw_all_connect(block* ckt,int sequence[])
{
    if(ckt->type==1 || ckt==NULL)
    {    return;}
    int level_u,seq_u;
    int level_d0,seq_d0;
    block* in0;
    int level_d1,seq_d1;
    block* in1;
    
    in0=(ckt->in_1);

    if(ckt->type>3)
    {in1=(in0->beside);}

    level_u=get_level(ckt);
    level_d0=get_level(in0);

    if(ckt->type>3)
    {level_d1=get_level(in1);}

    seq_u=sequence[ckt->name];
    seq_d0=sequence[in0->name];

    if(ckt->type>3)
    {seq_d1=sequence[in1->name];}

    if(in0->type>2)
    {draw_connection(level_d0,seq_d0,level_u,seq_u,0);}

    if(in1->type>2 && ckt->type>3)
    {draw_connection(level_d1,seq_d1,level_u,seq_u,1);}

    draw_all_connect(in0,sequence);

    if(ckt->type>3)
    {draw_all_connect(in1,sequence);}

}
void draw_ckt(block* block_list[],same_level_blocks* level[],int max,int sequence[])
{
    if(max<0)
        return;
    int seq=0;
    while(level[max]!=NULL)
    {
        int get=0;
        level[max]=pop(level[max],&get);
        sequence[get]=seq;
        draw_block(get,max,&seq,block_list[get]->type);
    }
    draw_ckt(block_list,level,max-1,sequence);
}



int main()
{
    intro();
    char **type_list;
    type_list=(char**)malloc(sizeof(char*));
    int n=10;
    int *type_num;
    *type_num=n;
    for(int i=0;i<n;i++)
    {
        type_list[i]=(char*)malloc(sizeof(char));
    }  
    char basic[10][10]={"empty","input","output","inv","and","or","nand","nor","xor","nxor"};   
    for(int i=0;i<n;i++)
    {
        type_list[i]=basic[i];
    }  
    block *block_list[MAX_BLOCK_NUM];
    block *new_block;
    int output[10];
    char sel;
    int label=1;
    int level=0;
    int new_gate_type;
    initwindow(1000,600,"display");
    while(1)
    {
        what_to_do();
        scanf(" %c",&sel);
        if(sel=='q')
        {
            printf("GOOD BYE!");
            break;
        }
        if(sel=='a')
        {
            block_info(type_list,*type_num);
            scanf(" %d",&new_gate_type);
            new_block=make_gate(label,new_gate_type,0);
            block_list[label]=new_block;

            while(label>1)
            {
                printf("which block do you want the output connect to?");
                int n;
                scanf(" %d",&n);
                connect_to_input(block_list[n],block_list[label]);
                printf("any else?(y/n)");
                char y_n;
                scanf(" %c",&y_n);
                if(y_n=='n' || y_n=='N')
                    break;
            }

            int max_level;
            max_level=get_level(block_list[1]);
            printf("max level = %d\n",max_level);
            same_level_blocks* level[max_level+1];
            for(int i=0;i<=max_level;i++)
                level[i]=NULL;
            sort_to_same_level(block_list,&label,max_level,level);//label also increase here

            cleardevice();
            int sequence[MAX_BLOCK_NUM];
            draw_ckt(block_list,level,max_level,sequence);
            draw_all_connect(block_list[1],sequence);
            //test_block(block_list[1]);
        }
        if(sel=='b')
        {
            printf("make block\n");
        }
        if(sel=='t')
        {   
            ask_for_test(block_list[1]);
            reset_ready(block_list[1]);
        }
        if(sel=='s')
        {
            
            printf("ckt saved!\n");
        }
        printf("\n\n");
    }
}