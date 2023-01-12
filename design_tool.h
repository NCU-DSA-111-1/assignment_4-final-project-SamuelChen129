
typedef struct block_t
{
    int type;
    int name;
    int out_num;
    int in_num;
    bool value;
    bool ready;
    block_t *in_1;
    block_t *beside;
}block;

typedef struct same_level_blocks_t
{
    int label;
    same_level_blocks_t* next;

}same_level_blocks;

void intro();

void block_info(char** ,int );

void update_type_list(char**,int* ,char* );

block* make_gate(int,int,bool);

int get_level(block*);

void connect_to_input(block*,block*);

void ask_for_test(block*);

void reset_ready(block*);

void get_value(block*);

void what_to_do();

same_level_blocks* pop(same_level_blocks*,int*);

void sort_to_same_level(block*[],int*,int,same_level_blocks*[]);

