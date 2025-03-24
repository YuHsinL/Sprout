#include "splendor.hpp"

extern Gem gameboard[BOARD_HEIGHT][BOARD_WIDTH];

void ai(Pos& pos1, Pos& pos2) {
  // TODO: Task 4.
  // You should remove the code below and determine the four values by yourself.
  
  //bomb gems
  for(int i=0; i<BOARD_HEIGHT; i++){
  	for(int j=0; j<BOARD_WIDTH; j++){
  	  if(gameboard[i][j].ability==ABI_BOMB){
  	  	if(i<=4){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i+1;
  	  	  pos2.y = j;
		}else if(i>=5){
		  pos1.x = i;
		  pos1.y = j;
		  pos2.x = i-1;
		  pos2.y = j;
		}else if(j<=4){
		  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i;
  	  	  pos2.y = j+1;
		}else if(j>=5){
		  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i;
  	  	  pos2.y = j-1;
		}
		return;
	  }
	}
  }
  //cross gems
  for(int i=1; i<BOARD_HEIGHT-1; i++){
  	for(int j=0; j<BOARD_WIDTH; j++){
  	  if(gameboard[i][j].ability==ABI_CROSS){
  	  	if(gameboard[i-1][j].type==gameboard[i+1][j].type && gameboard[i-1][j].type==gameboard[i][j+1].type){
  	  	  pos1.x = i;
  	  	  pos1.x = j;
  	  	  pos2.x = i;
  	  	  pos2.y = j+1;
	    }else if(gameboard[i-1][j].type==gameboard[i+1][j].type && gameboard[i-1][j].type==gameboard[i][j-1].type){
  	  	  pos1.x = i;
  	  	  pos1.x = j;
  	  	  pos2.x = i;
  	  	  pos2.y = j-1;
	    }
		return;
	  }
	}
  }
  for(int i=0; i<BOARD_HEIGHT; i++){
  	for(int j=1; j<BOARD_WIDTH-1; j++){
  	  if(gameboard[i][j].ability==ABI_CROSS){
  	    if(gameboard[i][j-1].type==gameboard[i][j+1].type && gameboard[i][j-1].type==gameboard[i+1][j].type){
  	  	  pos1.x = i;
  	  	  pos1.x = j;
  	  	  pos2.x = i+1;
  	  	  pos2.y = j;
	    }else if(gameboard[i][j-1].type==gameboard[i][j+1].type && gameboard[i][j-1].type==gameboard[i-1][j].type){
  	  	  pos1.x = i;
  	  	  pos1.x = j;
  	  	  pos2.x = i-1;
  	  	  pos2.y = j;
	    }
	  return;
      }
	}
  }
  //killsame gems
  int type_count[5]={0, 0, 0, 0, 0};
  int type_array[5]={1, 2, 3, 4, 5};
  for(int i=0; i<BOARD_HEIGHT; i++){
  	for(int j=0; j<BOARD_WIDTH; j++){
  	  if(gameboard[i][j].type==GEM_RUBY){
  	  	type_count[0]++;
	  }else if(gameboard[i][j].type==GEM_LAPIZ){
	  	type_count[1]++;
	  }else if(gameboard[i][j].type==GEM_EMERALD){
	  	type_count[2]++;
	  }else if(gameboard[i][j].type==GEM_AMBER){
	  	type_count[3]++;
	  }else if(gameboard[i][j].type==GEM_AMETHYST){
	  	type_count[4]++;
	  }
	}
  }
  for(int i=0; i<5-1; i++){
  	for(int j=1; j<5-i; j++){
  	  if(type_count[i]<type_count[i+1]){
  	  	int tmp_count, tmp_array;
  	  	tmp_count=type_count[i];
  	  	type_count[i]=type_count[i+1];
  	  	type_count[i+1]=tmp_count;
  	  	tmp_array=type_array[i];
  	  	type_array[i]=type_array[i+1];
  	  	type_array[i+1]=tmp_array;
	  }
	}
  }
  Pos tar_pos={0,0};
  for(int i=0; i<BOARD_HEIGHT; i++){
  	int max_type=5;
  	for(int j=0; j<BOARD_WIDTH; j++){
  	  if(gameboard[i][j].ability==ABI_KILLSAME){
  	  	if(check_inboard({i+1,j})){
  	  	  for(int k=0; k<5; k++){
  	  	  	if(gameboard[i+1][j].type==type_array[k] && max_type>k){
  	  	  	  max_type=k;
  	  	  	  tar_pos={i+1,j};
			}
		  }
		}
		if(check_inboard({i-1,j})){
  	  	  for(int k=0; k<5; k++){
  	  	  	if(gameboard[i-1][j].type==type_array[k] && max_type>k){
  	  	  	  max_type=k;
  	  	  	  tar_pos={i-1,j};
			}
		  }
		}
		if(check_inboard({i,j+1})){
  	  	  for(int k=0; k<5; k++){
  	  	  	if(gameboard[i][j+1].type==type_array[k] && max_type>k){
  	  	  	  max_type=k;
  	  	  	  tar_pos={i,j+1};
			}
		  }
		}
		if(check_inboard({i,j-1})){
  	  	  for(int k=0; k<5; k++){
  	  	  	if(gameboard[i][j-1].type==type_array[k] && max_type>k){
  	  	  	  max_type=k;
  	  	  	  tar_pos={i,j-1};
			}
		  }
		}
	    pos1.x = i;
	    pos1.y = j;
	    pos2.x = tar_pos.x;      
		pos2.y = tar_pos.y;
	    return;
	  }
	}
  }

  //find a five-same-gems line
  for(int i=2; i<BOARD_HEIGHT-2; i++){
  	for(int j=0; j<BOARD_WIDTH; j++){
  	  if(gameboard[i-2][j].type==gameboard[i-1][j].type && gameboard[i+2][j].type==gameboard[i+1][j].type){
  	  	if(gameboard[i-1][j].type==gameboard[i+1][j].type && gameboard[i-1][j].type==gameboard[i][j+1].type){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i;
  	  	  pos2.y = j+1;
		}else if(gameboard[i-1][j].type==gameboard[i+1][j].type && gameboard[i-1][j].type==gameboard[i][j-1].type){
		  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i;
  	  	  pos2.y = j+1;
		}
		return;
	  }
	}
  }
  for(int i=0; i<BOARD_HEIGHT; i++){
  	for(int j=2; j<BOARD_WIDTH-2; j++){
  	  if(gameboard[i][j-2].type==gameboard[i][j-1].type && gameboard[i][j+2].type==gameboard[i][j+1].type){
  	  	if(gameboard[i][j-1].type==gameboard[i][j+1].type && gameboard[i][j-1].type==gameboard[i+1][j].type){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i+1;
  	  	  pos2.y = j;
		}else if(gameboard[i][j-1].type==gameboard[i][j+1].type && gameboard[i][j-1].type==gameboard[i-1][j].type){
		  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i-1;
  	  	  pos2.y = j;
		}
		return;
	  }
	}
  }
  //find a four-gems-line
  for(int i=1; i<BOARD_HEIGHT-2; i++){
  	for(int j=0; j<BOARD_WIDTH; j++){
  	  if(gameboard[i-1][j].type==gameboard[i+1][j].type && gameboard[i+1][j].type==gameboard[i+2][j].type){
  	  	if(gameboard[i+1][j].type==gameboard[i][j+1].type){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i;
  	  	  pos2.y = j+1;
		}else if(gameboard[i+1][j].type==gameboard[i][j-1].type){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i;
  	  	  pos2.y = j-1;
		}
	  }
	}
  }
  for(int i=2; i<BOARD_HEIGHT-1; i++){
  	for(int j=0; j<BOARD_WIDTH; j++){
  	  if(gameboard[i-1][j].type==gameboard[i+1][j].type && gameboard[i-1][j].type==gameboard[i-2][j].type){
  	  	if(gameboard[i+1][j].type==gameboard[i][j+1].type){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i;
  	  	  pos2.y = j+1;
		}else if(gameboard[i+1][j].type==gameboard[i][j-1].type){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i;
  	  	  pos2.y = j-1;
		}
	  }
	}
  }
  for(int i=0; i<BOARD_HEIGHT; i++){
  	for(int j=1; j<BOARD_WIDTH-2; j++){
  	  if(gameboard[i][j-1].type==gameboard[i][j+1].type && gameboard[i][j+1].type==gameboard[i][j+2].type){
  	  	if(gameboard[i][j+1].type==gameboard[i+1][j].type){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i+1;
  	  	  pos2.y = j;
		}else if(gameboard[i][j+1].type==gameboard[i-1][j].type){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i-1;
  	  	  pos2.y = j;
		}
	  }
	}
  }
  for(int i=0; i<BOARD_HEIGHT; i++){
  	for(int j=2; j<BOARD_WIDTH-1; j++){
  	  if(gameboard[i][j-1].type==gameboard[i][j-2].type && gameboard[i][j-1].type==gameboard[i][j+1].type){
  	  	if(gameboard[i][j-1].type==gameboard[i+1][j].type){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i+1;
  	  	  pos2.y = j;
		}else if(gameboard[i][j-1].type==gameboard[i-1][j].type){
  	  	  pos1.x = i;
  	  	  pos1.y = j;
  	  	  pos2.x = i-1;
  	  	  pos2.y = j;
		}
	  }
	}
  }
  //find a three-gems-line
  for(int i=1; i<BOARD_HEIGHT-1; i++){
  	for(int j=0; j<BOARD_WIDTH; j++){
  	  if(gameboard[i-1][j].type==gameboard[i+1][j].type && gameboard[i-1][j].type==gameboard[i][j+1].type){
  	  	pos1.x = i;
  	  	pos1.x = j;
  	  	pos2.x = i;
  	  	pos2.y = j+1;
	  }else if(gameboard[i-1][j].type==gameboard[i+1][j].type && gameboard[i-1][j].type==gameboard[i][j-1].type){
  	  	pos1.x = i;
  	  	pos1.x = j;
  	  	pos2.x = i;
  	  	pos2.y = j-1;
	  }
	  return;
	}
  }
  for(int i=0; i<BOARD_HEIGHT; i++){
  	for(int j=1; j<BOARD_WIDTH-1; j++){
  	  if(gameboard[i][j-1].type==gameboard[i][j+1].type && gameboard[i][j-1].type==gameboard[i+1][j].type){
  	  	pos1.x = i;
  	  	pos1.x = j;
  	  	pos2.x = i+1;
  	  	pos2.y = j;
	  }else if(gameboard[i][j-1].type==gameboard[i][j+1].type && gameboard[i][j-1].type==gameboard[i-1][j].type){
  	  	pos1.x = i;
  	  	pos1.x = j;
  	  	pos2.x = i-1;
  	  	pos2.y = j;
	  }
	  return;
	}
  }
  return;
}

