#define IO_LINE_LENGTH 10
#define IO_LINE_INTERVAL_MAX 40
#define IO_LINE_NUM_MAX 10
#define BLOCK_GAP_X 90
#define BLOCK_GAP_Y 60
#define BLOCK_EDGE 50
#define TEXT_X 6
#define TEXT_Y 14
#define MAX_BLOCK_NUM 55


void scaler(float);
int line_interval(int);
void draw_block(int,int,int*,int);
void draw_connection(int,int,int,int,int);
void display_all_block(int,int);

