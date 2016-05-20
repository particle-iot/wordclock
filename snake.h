#ifndef SNAKE_H_
#define SNAKE_H_

// This #include statement was automatically added by the Particle IDE.
#include "RGBmatrixPanel/RGBmatrixPanel.h"

#include "application.h"


#define ledmatrix_length 16
#define ledmatrix_width 16
#define game_speed 200

/*----------------definitions------------------*/
// #define data    porta.b2
// #define latch   porta.b1
// #define clk     porta.b0
// #define a1      porta.B3
// #define a2      porta.b4
// #define a3      porta.b5
#define right 1
#define left 2
#define down 3
#define up 4
// #define uppin 0
// #define leftpin 1
// #define rightpin 2
// #define downpin 3

/*----------------definitions------------------*/


/*----------------structures------------------*/
typedef struct snakebit {
	char srow;
	char scolumn;
	char direction;
} mysnake;

typedef struct food {
	char row;
	char column;
} food;
/*----------------structures------------------*/

#pragma once
class Serpent
{
    
    RGBmatrixPanel* __matrix;
    int new_direction = 0;
    
public:
	Serpent();
	Serpent(RGBmatrixPanel* matrix);
	virtual ~Serpent();


    void set_new_direction(int val){
		this->new_direction = val;
	}
	int get_new_direction(){
		return this->new_direction;
	}
    

	void
	    snake_intialization(mysnake* snake),
		clear_matrix(),
		create_border(),
		light_bit(int row, int column, int color = 0),
		update_body(mysnake* snake, int length),
		show_body(mysnake* temp, int length),
		adapt_body(mysnake* snake, int length),
		change_direction(mysnake* snakehead),
		happy_meal(mysnake* listhead),
		renew_apple(food* applepointer, mysnake* listhead),
		update_head(mysnake* snakehead),
		clear(mysnake* snake);
		
	
		
	bool
	    check_collision(food* applepointer, mysnake* listhead),
	    body_crash(mysnake* listhead);
		
		/*
		write_byte(char serial),
		write_byte(char serial),
		gameover(char* patt1, char* patt2, char* patt3, char* patt4),
		print1(char* patt1, char* patt2, char* patt3, char* patt4),
		print2(char* patt1, char* patt2, char* patt3, char* patt4),
		display(char* patt1, char* patt2, char* patt3, char* patt4),
		initialization(void);

	char
		zone_detect(char row, char column),
	

*/
};



#endif /* SNAKE_H_ */
