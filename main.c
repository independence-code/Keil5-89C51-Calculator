#include <REGX52.H>
#include <delay.h>
#include <keyscan.h>   
#include <LCD1602.h>    
#include <matrix.h>

#define MAX_INPUT_LEN 16

// ??????
unsigned char get_key() {
    unsigned char key_num = matrixkey();
    switch(key_num) {
        case 1:  return '1';
        case 2:  return '2';
        case 3:  return '3';
        case 4:  return '4';
        case 5:  return '5';
        case 6:  return '6';
        case 7:  return '7';
        case 8:  return '8';
        case 9:  return '9';
        case 10: return '0';
        case 11: return '(';
        case 12: return ')';
        case 13: return '.';
        case 14: return '=';
        case 15: return 'd';  // ??
        case 16: return 'C';  // ??(?'A'??????'C')
        case 17: return '+';
        case 18: return '-';
        case 19: return '*';
        case 20: return '/';
        default: return 0xFF;
    }
}

void main() {
    unsigned char input[MAX_INPUT_LEN] = {0};  // ?????
    unsigned char pos = 0;                     // ??????
    float result;
    unsigned char key_val;
    unsigned char result_str[16];              // ????????

    LCD_Init();
    LCD_Clear();

    while (1) {
        key_val = get_key();
        
        if (key_val != 0xFF) {
            delay(20);  // ????

            /*----- ????? -----*/
            if (key_val == 'C') {  // ????
                pos = 0;
                input[0] = '\0';
                LCD_Clear();
            }
            else if (key_val == 'd' && pos > 0) {  // ????
                input[--pos] = '\0';
                LCD_ShowString(1, 1, "                "); // ?????
                LCD_ShowString(1, 1, input);             // ??????
            }
            else if (key_val == '=') {  // ????
                if (pos > 0) {
                    result = jisuan(input);
                    float2char(result, result_str, sizeof(result_str));
                    LCD_ShowString(2, 1, "                "); // ?????
                    LCD_ShowString(2, 1, result_str);         // ????
                }
            }
            /*----- ?????? -----*/
            else if (pos < MAX_INPUT_LEN-1) {  
                input[pos++] = key_val;
                input[pos] = '\0';
                LCD_ShowChar(1, pos, key_val);  // ???????
            }

            while (matrixkey() != 0);  // ??????
            delay(20);                // ????
        }
    }
}