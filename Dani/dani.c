#include "dani.h"

struct termios initial;

int tim = 100000;
int cont = 0,flag = 0;
int pos;


void laser(void *i){
  int r,c;
  sc_rectangle *b,*t;
  b = get_board(i);
  t = get_text(i);
  srand(time(NULL));

  while(cont < 200){
    r = 20;
    c = rand()% 38+ 25;  /*25 a 62 */
    win_write_char_at(b,20,c,'o');

    while(r != 1){

      win_write_char_at(b,r,c,' ');
      win_write_char_at(b,r-1,c,'o');
      win_write_char_at(b,r,c+1,' ');
      win_write_char_at(b,r,c-1,' ');
      win_write_char_at(b,r,c,' ');
      r--;


      usleep(tim);
    }
    if(pos == c) flag = 1;
    win_write_char_at(b,r,c,' ');
    cont++;

  }
  pthread_exit (NULL);
  return;
}


void main_dani(Interface *i){

	int quit,m,res;
  int *p;
  p = (int*)malloc(sizeof(int)*2);
	char** board;
	int sizeb[2];


 /*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("tiraficher",sizeb);


	set_board(i,board,sizeb[0],sizeb[1]);

	draw_board(i,1);

	draw_score(i,1);

	draw_text(i,1);


	sc_rectangle *t,*s;
 	t = get_text(i);
  s = get_score(i);
 	if(!t || !s) return;

	win_write_line_at(t,4,4,"Press the space bar to continue");




	while(1){
	quit = _read_key();
	/*pressing q it exits*/
	if (quit == 'q')   return;
	/*if you press the space bar,you move foward*/
	if(quit == 32) break;
	}

  draw_text(i,1);

  board = create_map("bar",sizeb);

  set_board(i,board,sizeb[0],sizeb[1]);
	set_player(i,'J',2,62);
	draw_board(i,1);

  win_write_line_at(t,4,4,"You are in the queue to enter a bar.");
  win_write_line_at(t,5,4,"There must be a way to enter avoiding the queue...");
  usleep(4000000);
  win_write_line_at(s,4,4,"Find a way to ");
  win_write_line_at(s,5,4,"enter the bar ");
  win_write_line_at(s,6,4,"and sit in front");
  win_write_line_at(s,7,4,"of the barman(S)");
  while(1){
		m = _read_key();
		/*pressing q it exits*/
		if (m == 'q')	break;

     move(i,-m);
     p = player_get_position(i);
     if(p[0] == 10 && p[1] == 21){
       break;
     }

   }
 draw_text(i,1);
 draw_score(i,1);
  if(m != 'q'){
  	 win_write_line_at(t,4,4,"You have a sit and look at the person at your right");
  	 win_write_line_at(t,5,4,"He suddenly looks at you and starts talking");
  	 usleep(4000000);
  	 draw_text(i,1);
  	 win_write_line_at(t,4,4,"D : Hey bb,you look amazing tonight.What are you doing in this bar?");
  	 usleep(4000000);
  	 win_write_line_at(t,5,4,"J : Eeh sorry,I think you're wrong,I'm a boy");
  	 usleep(4000000);
  	 win_write_line_at(t,6,4,"D : Hahahaha,you're funny,but I can clearly see that you're a girl");
  	 usleep(4000000);
  	 win_write_line_at(t,7,4,"J : No,I'm not");
  	 usleep(4000000);
  	 draw_text(i,1);
  	 win_write_line_at(t,4,4,"D : Look at the mirror right there");
  	 usleep(4000000);
  	 win_write_line_at(t,5,4,"J :WTF why would you put a mirror in the bar's counter? ");
  	 usleep(4000000);
  	 win_write_line_at(t,6,4,"D :That's because the barman loves to spend the day watching himself there");
  	 usleep(4000000);
  	 win_write_line_at(t,7,4,"Santini :Yes,I love that.");
  	 usleep(4000000);
  	 draw_text(i,1);
  	 win_write_line_at(t,4,4,"D : Well,look at the mirror please");
  	 usleep(4000000);
  	 win_write_line_at(t,5,4,"You look at it and you discover horrified that you are a GIRL!");
  	 usleep(4000000);
  	 win_write_line_at(t,6,4,"D : Well,let's stop making jokes.Do you wnat to dance with me? ( ͡° ͜ʖ ͡°) ");
  	 usleep(4000000);
   }
   while(1){
     win_write_line_at(t,7,4,"Press the space bar to start avoiding Dani's flirting chips");
        m = _read_key();
     /*pressing q it exits*/
      if (m == 'q')	break;
      if(m == 32){
  			draw_text(i,1);
        res = dani(i);
        break;
      }
   }

    board = create_map("bar2",sizeb);
    set_player(i,'J',10,21);
    set_board(i,board,sizeb[0],sizeb[1]);
    draw_board(i,1);
    draw_score(i,1);

    if(res == 0){
      win_write_line_at(t,4,4,"You couldn't escape and you end up dancing an drinking with Dani");
      usleep(3000000);
      win_write_line_at(t,5,4,"Bad news for your life bar...");
      usleep(3000000);
      return;
    }

    win_write_line_at(t,4,4,"You escape from Dani,but the main door is locked!");
    usleep(3000000);
    win_write_line_at(t,5,4,"S : Run,use the backdoor,it's in the top left corner of the bar!");
    usleep(2000000);
    draw_text(i,1);
    win_write_line_at(s,4,4,"Escape using ");
    win_write_line_at(s,5,4,"the backdoor ");

    while(1){
      m = _read_key();
      if (m == 'q')	break;
      move(i,-m);
      p = player_get_position(i);
      if((p[0] == 1 || p[0] == 2)  && p[1] == 3) break;
      if((p[0] == 18 || p[0] == 19 || p[0] == 20)  && p[1] == 3){

        win_write_line_at(t,4,4,"S : I said top left,you idiot!");
        usleep(200000);
        draw_text(i,1);
        continue;
      }

    }

   return;


}


int dani(Interface *i){
    char **board,p[3];
    int sizeb[2],m,again,lives;
    int *aux = (int*)malloc(sizeof(int)*2);
		pthread_t pth1,pth2,pth3,pth4,pth5;
    sc_rectangle *t,*s;
    t = get_text(i);
    s = get_score(i);

    play : board = create_map("esquivafichas",sizeb);
    set_board(i,board,sizeb[0],sizeb[1]);
  	set_player(i,'J',1,42);
  	draw_board(i,1);

    lives = 3;
    win_write_line_at(s,4,4,"Lives : ");
    sprintf(p,"%d",lives);
    win_write_line_at(s,4,12,p);

		pthread_create(&pth1, NULL, laser,(void*)(i));
		usleep(2000000);
		pthread_create(&pth2, NULL, laser,(void*)(i));
		usleep(2000000);
		pthread_create(&pth3, NULL, laser,(void*)(i));
    usleep(2000000);
		pthread_create(&pth4, NULL, laser,(void*)(i));
    usleep(2000000);
		pthread_create(&pth5, NULL, laser,(void*)(i));
		while(1){
      if(flag == 1) break;
			if(cont >=3 && cont < 20) tim = 100000;
			if(cont >= 20 && cont< 50) tim = 90000 ;
      if(cont >= 50 && cont< 100) tim = 70000 ;
      if(cont >= 100 && cont < 150 ) tim = 60000 ;
      if(cont >= 150) tim = 40000;
      if (cont > 200) break;
      m = _read_key();
			if(m == 'q') break;
			if(m == -NORTH || m == -SOUTH) continue;
			move(i,-m);
      aux = player_get_position(i);
      pos = aux[1];

      if(flag == 1){
        lives--;
        sprintf(p,"%d",lives);
        win_write_line_at(s,4,12,p);
        flag = 0;
      }
      if(lives == 0)break;

		}
    pthread_cancel(pth1);
    pthread_cancel(pth2);
    pthread_cancel(pth3);
    pthread_cancel(pth4);
    pthread_cancel(pth5);
    if (lives == 0){
      win_write_line_at(t,4,4,"YOU LOST!");

    }

    usleep(2000000);
    draw_text(i,1);
    while(1){
      win_write_line_at(t,4,4,"Do you want to play again?[y,n]: ");
      again = _read_key();
      if(again != 'y' && again != 'n') continue;
      if(again == 'y'){
        pthread_cancel(pth1);
        pthread_cancel(pth2);
        pthread_cancel(pth3);
        pthread_cancel(pth4);
        pthread_cancel(pth5);
        draw_text(i,1);
        goto play;
      }
      break;
    }
    draw_text(i,1);

    if(lives == 0) return 0;
    return 1;
  }
