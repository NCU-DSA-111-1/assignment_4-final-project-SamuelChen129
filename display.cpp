#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include "display.h"

void scaler(float n)
{
    const float x=BLOCK_EDGE;
    line(0,0,0,x*n);
    line(0,0,x*n,0);
    line(0,x*n,x*n,x*n);
    line(x*n,0,x*n,x*n);
    char* text="1";
    outtextxy(x*n/2-3,x*n/2-7,text);
}

int line_interval(int n)
{
    if(n==1)
        return 0;
    else 
        return IO_LINE_INTERVAL_MAX/(n-1);
}

void draw_inv(int x1, int y1){

    line(x1  , y1 ,  x1  , y1+BLOCK_EDGE );
    line(x1  , y1 ,  x1 + (BLOCK_EDGE/2)*1.732 , y1+(BLOCK_EDGE/2));//3^0.5=1.732
    line(x1  , y1+BLOCK_EDGE ,  x1 + (BLOCK_EDGE/2)*1.732 , y1+(BLOCK_EDGE/2) );

    circle(x1 + BLOCK_EDGE, y1+(BLOCK_EDGE/2) , 5); 

    line(x1 , y1+BLOCK_EDGE/2  , x1-IO_LINE_LENGTH , y1+BLOCK_EDGE/2 );//input line
    // Close the initialized gdriver
} // end inverter

void draw_or(int x1, int y1){

    int n_in=2;
    int interval;
    interval=line_interval(n_in);
    int start_angle = 270 ;
    int end_angle = 90;

    int x_rad = BLOCK_EDGE;
    int y_rad = BLOCK_EDGE/2;

    ellipse(x1, y1+BLOCK_EDGE/2 , start_angle,end_angle, x_rad, y_rad);
    ellipse(x1, y1+BLOCK_EDGE/2 , start_angle,end_angle, x_rad/5, y_rad);
    

    int a=(BLOCK_EDGE-IO_LINE_INTERVAL_MAX)/2;
    
    for(int i=0;i<n_in;i++)
    {
        line(x1 , y1+ a + interval*i , x1-IO_LINE_LENGTH , y1+ a + interval*i );
    }//draw input line
    
} 

void draw_and(int x1, int y1){

    int n_in=2;
    int interval;
    interval=line_interval(n_in);
    int start_angle = 270 ;
    int end_angle = 90;
    int x_rad = BLOCK_EDGE/5;
    int y_rad = BLOCK_EDGE/2;

    ellipse(x1+BLOCK_EDGE*4/5, y1+BLOCK_EDGE/2, start_angle,end_angle, x_rad, y_rad);
    line(x1 , y1 , x1 +BLOCK_EDGE*4/5 , y1 );
    line(x1 , y1+BLOCK_EDGE , x1 +BLOCK_EDGE*4/5 , y1+BLOCK_EDGE );
    line(x1 , y1 , x1 , y1+BLOCK_EDGE );
    

    int a=(BLOCK_EDGE-IO_LINE_INTERVAL_MAX)/2;
    for(int i=0;i<n_in;i++)
    {
        line(x1 , y1+ a + interval*i , x1-IO_LINE_LENGTH , y1+ a + interval*i );
    }//draw input line

}// and gate end

void draw_nor(int x1, int y1){

    draw_or(x1,y1);
    circle(x1 + BLOCK_EDGE, y1+(BLOCK_EDGE/2) , 5); 

}// end nor gate

void draw_nand(int x1, int y1){

    draw_and(x1,y1);
    circle(x1 + BLOCK_EDGE, y1+(BLOCK_EDGE/2) , 5); 
}

void draw_xor(int x1, int y1){

    draw_or(x1,y1);

    int start_angle = 270 ;
    int end_angle = 90;
    int x_rad = BLOCK_EDGE;
    int y_rad = BLOCK_EDGE/2;
    ellipse(x1-x_rad/5, y1+BLOCK_EDGE/2 , start_angle,end_angle, x_rad/5, y_rad);
    
}

void draw_nxor(int x1, int y1){

    draw_xor(x1,y1);
    circle(x1 + BLOCK_EDGE, y1+(BLOCK_EDGE/2) , 5); 

}
void draw_block(int label,int level, int *seq, int type){
    int x;
    int y;//x is the left side, y is the up side of the block
    x=2*TEXT_X+IO_LINE_LENGTH;
    y=0;

    x=x+BLOCK_GAP_X*level;
    y=y+BLOCK_GAP_Y*level/2;
    
    y=y+BLOCK_GAP_Y*(*seq);

    (*seq)=(*seq)+1;

    char text[2];
    text[0]=(char)(label+48);
    text[1]='\0';
    outtextxy(x+BLOCK_EDGE/2-TEXT_X/2,y+BLOCK_EDGE/2-TEXT_Y/2,text);//label
    
    switch(type)
    {
        case 3:
            draw_inv(x,y);
            break;
        case 4:
            draw_and(x,y);
            break;
        case 5:
            draw_or(x,y);
            break;
        case 6:
            draw_nand(x,y);
            break;
        case 7:
            draw_nor(x,y);
            break;
        case 8:
            draw_xor(x,y);
            break;
        case 9:
            draw_nxor(x,y);
            break;
    }
}

void draw_connection(int level_d,int seq_d,int level_u,int seq_u,int input_n)
{
    int a=(BLOCK_EDGE-IO_LINE_INTERVAL_MAX)/2;
    int x_u=2*TEXT_X+IO_LINE_LENGTH            , y_u=a+IO_LINE_INTERVAL_MAX*input_n;
    int x_d=2*TEXT_X+IO_LINE_LENGTH+BLOCK_EDGE , y_d=BLOCK_EDGE/2;

    x_d=x_d+BLOCK_GAP_X*level_d;
    y_d=y_d+BLOCK_GAP_Y*level_d/2; 
    x_u=x_u+BLOCK_GAP_X*level_u;
    y_u=y_u+BLOCK_GAP_Y*level_u/2;  

    y_d=y_d+BLOCK_GAP_Y*seq_d;
    y_u=y_u+BLOCK_GAP_Y*seq_u;

    int mx;
    float k;
    k=1-0.5/(level_u-level_d);
    mx=x_d+(x_u-x_d)*k;
    line(x_d,y_d,mx,y_d);
    line(mx,y_d,mx,y_u);
    line(mx,y_u,x_u,y_u);
}
void display_all_block(int x, int y){
   
   int t;
   
   scaler(1);
   
   scanf("%d",&t);
   cleardevice();
   draw_inv(x,y);

   scanf("%d",&t);//pause on the image
   cleardevice();//clean the last image
   draw_and(x,y);//update the image

   scanf("%d",&t);
   cleardevice();
   draw_or(x,y);

   scanf("%d",&t);
   cleardevice();
   draw_nor(x,y);

   scanf("%d",&t);
   cleardevice();
   draw_nand(x,y);

   scanf("%d",&t);
   cleardevice();
   draw_xor(x,y);

   scanf("%d",&t);
   cleardevice();
   draw_nxor(x,y);

   scanf("%d",&t);

   closegraph();
}


