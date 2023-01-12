#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>

bool nor_gate(bool line_1, bool line_2 ){
    return !(line_1 | line_2);
} 

bool nand_gate(bool line_1, bool line_2 ){
   return !(line_1 & line_2);
} 

bool inv_gate(bool line_1 ){
    return !(line_1);
} 

bool and_gate(bool line_1, bool line_2 ){
    return line_1 & line_2;
}

bool or_gate(bool line_1, bool line_2 ){
    return line_1 | line_2;
}

bool xor_gate(bool line_1, bool line_2 ){
    return line_1 ^ line_2; 
} // end xor Gate

bool nxor_gate(bool line_1, bool line_2 ){
    return !(line_1 ^ line_2);
} // end Nxor Gate