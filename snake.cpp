#include "snake.h"



Serpent::Serpent()
{
}
 
Serpent::Serpent(RGBmatrixPanel* matrix){
    // assign the matrix to a variable here?
    __matrix = matrix;
}

Serpent::~Serpent()
{
}

void Serpent::snake_intialization(mysnake * snake) {
	int k;
	for (k = 0; k < ((ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 4); k++) {
		snake[k].srow = 0;
		snake[k].scolumn = 0;
		snake[k].direction = 0;
	}
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3].srow = 5;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3].scolumn = 5;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3].direction = right;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 2].srow = 5;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 2].scolumn = 4;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 2].direction = right;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 1].srow = 5;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 1].scolumn = 3;
	snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 1].direction = right;
    new_direction = right;
}

void Serpent::clear_matrix() {
    __matrix->fillScreen(0);
}

void Serpent::create_border() {
    __matrix->drawRect(0, 0, ledmatrix_width*2, ledmatrix_length*2, __matrix->Color333(255, 0, 0));
	__matrix->drawRect(1, 1, ledmatrix_width*2-1, ledmatrix_length*2-1, __matrix->Color333(255, 0, 0));
}

void Serpent::light_bit(int row, int column, int color) {
    //light bit
    
    int r = 0;
    int g = 0;
    int b = 0;
    
    switch (color){
        case 0:
            r = 0;
            g = 255;
            b = 50;
            break;
        case 1:
            r = 0;
            g = 255;
            b = 0;
            break;
        case 2:
            r = 255;
            g = 150;
            b = 0;
            break;
            
    }
	
	int X = row * 2;
	int Y = column * 2;
	
	
	__matrix->drawPixel(X       , Y      , __matrix->Color333(r, g, b));
	__matrix->drawPixel(X + 1   , Y      , __matrix->Color333(r, g, b));
	__matrix->drawPixel(X       , Y + 1  , __matrix->Color333(r, g, b));
	__matrix->drawPixel(X + 1   , Y + 1  , __matrix->Color333(r, g, b));
	
}

void Serpent::update_body(mysnake *snake, int length) {
	int i;
	for (i = (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3 - length + 1; i < (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3; i++){
    	switch (snake[i + 1].direction) {
    		case 1:
    			++(snake[i].scolumn);
    			break;
    		case 2:
    			--(snake[i].scolumn);
    			break;
    		case 3:
    			++(snake[i].srow);
    			break;
    		case 4:
    			--(snake[i].srow);
    			break;
    	}
	}
}

void Serpent::show_body(mysnake * snake, int length) {
	int i;
	for (i = (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3 - length + 1; i < (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3; i++) {
		light_bit(snake[i].srow, snake[i].scolumn);
	}
}

void Serpent::adapt_body(mysnake * snake, int length) {
	int i;
	for (i = (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3 - length + 1; i < (ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3; i++) {
		snake[i].direction = snake[i + 1].direction;
	}
}

void Serpent::change_direction(mysnake *snakehead) {
	switch (snakehead -> direction) {
    	case up:
    	{
    		if (new_direction == 1) {
    			snakehead -> direction = right;
    			break;
    		}
    		if (new_direction == 2) {
    			snakehead -> direction = left;
    			break;
    		}
    	}
    	break;
    	case down:
    	{
    		if (new_direction == 1) {
    			snakehead -> direction = right;
    			break;
    		}
    		if (new_direction == 2) {
    			snakehead -> direction = left;
    			break;
    		}
    	}
    	break;
    	case right:
    	{
    		if (new_direction == 3) {
    			snakehead -> direction = up;
    			break;
    		}
    		if (new_direction == 4) {
    			snakehead -> direction = down;
    			break;
    		}
    	}
    	break;
    	case left:
    	{
    		if (new_direction == 3) {
    			snakehead -> direction = up;
    			break;
    		}
    		if (new_direction == 4) {
    			snakehead -> direction = down;
    			break;
    		}
    	}
    	break;
	}
}

void Serpent::happy_meal(mysnake *listhead) {
	mysnake *temp;
	temp = listhead - 1;

	switch (listhead->direction) {
    	case 1:
        	{
        		temp->srow = listhead->srow;
        		temp->scolumn = (listhead->scolumn) - 1;
        	} //right
        break;
    	case 2:
        	{
        		temp->srow = listhead->srow;
        		temp->scolumn = (listhead->scolumn) + 1;
        	} //left
        break;
    	case 3:
        	{
        		temp->srow = (listhead->srow) - 1;
        		temp->scolumn = listhead->scolumn;
        	} //down
        break;
    	case 4:
        	{
        		temp->srow = (listhead->srow) + 1;
        		temp->scolumn = listhead->scolumn;
        	}; //up
        break;
	}
	temp->direction = listhead->direction;

}

void Serpent::renew_apple(food * applepointer, mysnake * listhead) {
  applepointer->row = random(1, ledmatrix_width - 1);
  applepointer->column = random(1, ledmatrix_length - 1);
}

bool Serpent::check_collision(food* applepointer, mysnake* listhead) {
	mysnake* temp;
	temp = listhead;
	while (temp -> direction != 0) {
		if ((applepointer -> row == temp -> srow) && (applepointer -> column == temp -> scolumn)) {
			return 1;
		}
		--temp;
	}
	return 0;
}

void Serpent::update_head(mysnake* snakehead) {
	switch (snakehead -> direction) {
    	case 1:
    		++(snakehead -> scolumn); //right
    	break;
    	case 2:
    		--(snakehead -> scolumn); //left
    	break;
    	case 3:
    		++(snakehead -> srow); //down
    	break;
    	case 4:
    		--(snakehead -> srow); //up
    	break;
	}
}

bool Serpent::body_crash(mysnake* listhead) {
	mysnake* temp;
	temp = listhead - 1;
	while (temp -> direction != 0) {
		if ((listhead -> srow == temp -> srow) && (listhead -> scolumn == temp -> scolumn))
			return 1;
		--temp;
	}
	return 0;
}

void Serpent::clear(mysnake * snake) {
	int k;
	for (k = 0; k < ((ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 4); k++) {
		snake[k].srow = 0;
		snake[k].scolumn = 0;
		snake[k].direction = 0;
	}
}