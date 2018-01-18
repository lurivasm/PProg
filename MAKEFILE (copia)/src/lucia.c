#include "lucia.h"



int main_lucia(Interface *i){

  int quit,res = 1,lucia = 0,javiti = 0;
	char** board;
	int sizeb[2],points[30];
  int *p = (int*)malloc(sizeof(int)*2);


 /*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("olympics",sizeb);


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

  board = create_map("room",sizeb);
  set_board(i,board,sizeb[0],sizeb[1]);
  set_player(i,'J',6,40);
  draw_board(i,1);

  sprintf(points,"Your points %d",javiti);
  win_write_line_at(s,4,4,points);
  sprintf(points,"Lucia's points %d",lucia);
  win_write_line_at(s,5,4,points);

  win_write_line_at(t,4,4,"A: So, let's begin with the 2017 alcoholympics final!");
  usleep(4000000);
  win_write_line_at(t,5,4,"A: Our two finalists are Javiti and Lucia");
  usleep(3000000);
  win_write_line_at(t,6,4,"A: So please both of you go to the beer table to start with the first task");
  usleep(4000000);
  draw_text(i,1);
  win_write_line_at(t,4,4,"L: Aim goin tu wuin, aim an expert in drinkin");
  usleep(2000000);
  win_write_line_at(s,7,4,"Get to the beer table");

while(1){
  quit = _read_key();
  if(quit == 'q') break;
  move(i,-quit);
  p = player_get_position(i);
  if(p[0] == 7 && p[1] == 16){
    res = beer(i);
    break;
  }
}
if(res == 0) lucia++;
if(res == 1) javiti++;

draw_text(i,1);
draw_score(i,1);

sprintf(points,"Your points %d",javiti);
win_write_line_at(s,4,4,points);
sprintf(points,"Lucia's points %d",lucia);
win_write_line_at(s,5,4,points);

set_board(i,board,sizeb[0],sizeb[1]);
set_player(i,'J',7,16);
draw_board(i,1);

win_write_line_at(t,4,4,"A: That was great.Now, let's head to the second task ");
usleep(4000000);
win_write_line_at(t,5,4,"A: Please go to the card table");
usleep(2000000);
win_write_line_at(s,7,4,"Get to the card table");


while(1){
  quit = _read_key();
  if(quit == 'q') break;
  move(i,-quit);
  p = player_get_position(i);
  if(p[0] == 13 &&( p[1] == 39 || p[1] == 40)){
    res = cards(i);
    break;
  }
}
if(res == 0) lucia++;
if(res == 1) javiti++;

draw_text(i,1);
draw_score(i,1);

sprintf(points,"Your points %d",javiti);
win_write_line_at(s,4,4,points);
sprintf(points,"Lucia's points %d",lucia);
win_write_line_at(s,5,4,points);

set_board(i,board,sizeb[0],sizeb[1]);
set_player(i,'J',13,39);
draw_board(i,1);

usleep(3000000);
win_write_line_at(t,4,4,"A: So, I know I said that there are 3 tasks, but we don't have more ideas ");
usleep(3000000);
sprintf(points,"A: The final result is javiti = %d points and lucia = %d points",javiti,lucia);
win_write_line_at(t,5,4,points);
usleep(3000000);
if(javiti > lucia){
  win_write_line_at(t,6,4,"A: Javiti wins!");
  free(p);
  usleep(3000000);
  return 1;
}
if(javiti < lucia){
  win_write_line_at(t,6,4,"A: Lucía wins!");
  free(p);
  usleep(3000000);
  return 0;
}
if(javiti == lucia){
  win_write_line_at(t,6,4,"A: It's a draw! What a pity we don't have more tasks...");
  free(p);
  usleep(3000000);
  return 2;
}



}


void drink_beer(sc_rectangle *b, int r,int c){
  win_write_line_at(b,r,c,"|                |");
  return;
}



int lose ;

void lucia_beer(void *b){
  int r = 7;
  lose = 0;
  while(r < 18 ){
    usleep(2500000);
    drink_beer(b,r,60);
    r++;
  }

   lose = 1;
}

int beer(Interface *i){

  char** board;
  int sizeb[2];
  int drink,cont = 0,r = 7,d = 15;
  pthread_t pth;

  board = create_map("beer",sizeb);
  set_player(i,' ',0,0);
  set_board(i,board,sizeb[0],sizeb[1]);

  draw_board(i,1);
  draw_score(i,1);
  draw_text(i,1);

  sc_rectangle *t,*s,*b;
  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

  win_write_line_at(t,4,4,"A: Okay,in this first task, the one who finishes the beer first is the winner");
  usleep(3000000);
  win_write_line_at(s,4,4,"Press the space bar ");
  win_write_line_at(s,5,4,"repeatedly to drink");
  usleep(5000000);
  win_write_line_at(t,5,4,"So this begins in 3");
  usleep(1000000);
  win_write_line_at(t,5,24,"2");
  usleep(1000000);
  win_write_line_at(t,5,26,"1");
  usleep(3000000);
  win_write_line_at(t,5,28,"GO!");

  pthread_create(&pth, NULL, lucia_beer,(void*)(b));
  char p[30];
  while(r < 18 && lose == 0){
    drink = _read_key();
    if(drink == 'q') return 1;
    if(drink == 32) cont++;
    if(cont == d ){
      drink_beer(b,r,18);
      r++;
      d+=15;
    }
  }
    pthread_cancel(pth);


    draw_text(i,1);
    if(lose == 0){
       win_write_line_at(t,4,4,"YOU WIN");
       usleep(3000000);
       return 1;
     }
     if(lose == 1){
       win_write_line_at(t,4,4,"YOU LOOSE");
       usleep(3000000);
       return 0;
     }

  return 1;
}

draw_cards(sc_rectangle *b,int r, int c,int value){
  if(value == 1){
    win_write_line_at(b,r,c," ___________ ");
    r++;
    win_write_line_at(b,r,c,"|           |");
    r++;
    win_write_line_at(b,r,c,"|   ___     |");
    r++;
    win_write_line_at(b,r,c,"|  |_  |    |");
    r++;
    win_write_line_at(b,r,c,"|    | |    |");
    r++;
    win_write_line_at(b,r,c,"|    | |    |");
    r++;
    win_write_line_at(b,r,c,"|   _| |_   |");
    r++;
    win_write_line_at(b,r,c,"|  |_____|  |");
    r++;
    win_write_line_at(b,r,c,"|___________|");
    r++;

  }
  if(value == 2){
    win_write_line_at(b,r,c," ___________ ");
    r++;
    win_write_line_at(b,r,c,"|           |");
    r++;
    win_write_line_at(b,r,c,"|  ________ |");
    r++;
    win_write_line_at(b,r,c,"| |______  ||");
    r++;
    win_write_line_at(b,r,c,"|  ______| ||");
    r++;
    win_write_line_at(b,r,c,"| |  ______||");
    r++;
    win_write_line_at(b,r,c,"| | |______ |");
    r++;
    win_write_line_at(b,r,c,"| |________ |");
    r++;
    win_write_line_at(b,r,c,"|___________|");
    r++;

    }

    if(value == 3){
        win_write_line_at(b,r,c," ___________ ");
        r++;
        win_write_line_at(b,r,c,"|           |");
        r++;
        win_write_line_at(b,r,c,"|  ________ |");
        r++;
        win_write_line_at(b,r,c,"| |______  ||");
        r++;
        win_write_line_at(b,r,c,"|  ______| ||");
        r++;
        win_write_line_at(b,r,c,"| |______  ||");
        r++;
        win_write_line_at(b,r,c,"|  ______| ||");
        r++;
        win_write_line_at(b,r,c,"| |________||");
        r++;
        win_write_line_at(b,r,c,"|___________|");
        r++;

      }

      if(value == 4){
          win_write_line_at(b,r,c," ___________ ");
          r++;
          win_write_line_at(b,r,c,"|           |");
          r++;
          win_write_line_at(b,r,c,"| __    __  |");
          r++;
          win_write_line_at(b,r,c,"||  |  |  | |");
          r++;
          win_write_line_at(b,r,c,"||  |__|  | |");
          r++;
          win_write_line_at(b,r,c,"||_____   | |");
          r++;
          win_write_line_at(b,r,c,"|      |  | |");
          r++;
          win_write_line_at(b,r,c,"|      |__| |");
          r++;
          win_write_line_at(b,r,c,"|___________|");
          r++;

        }

        if(value == 5){
            win_write_line_at(b,r,c," ___________ ");
            r++;
            win_write_line_at(b,r,c,"|           |");
            r++;
            win_write_line_at(b,r,c,"|  ________ |");
            r++;
            win_write_line_at(b,r,c,"| |  ______||");
            r++;
            win_write_line_at(b,r,c,"| | |______ |");
            r++;
            win_write_line_at(b,r,c,"| |______  ||");
            r++;
            win_write_line_at(b,r,c,"|  ______| ||");
            r++;
            win_write_line_at(b,r,c,"| |________||");
            r++;
            win_write_line_at(b,r,c,"|___________|");
            r++;

          }

          if(value == 6){
              win_write_line_at(b,r,c," ___________ ");
              r++;
              win_write_line_at(b,r,c,"|           |");
              r++;
              win_write_line_at(b,r,c,"|  _______  |");
              r++;
              win_write_line_at(b,r,c,"| |   ____| |");
              r++;
              win_write_line_at(b,r,c,"| |  |____  |");
              r++;
              win_write_line_at(b,r,c,"| |   __  | |");
              r++;
              win_write_line_at(b,r,c,"| |  |__| | |");
              r++;
              win_write_line_at(b,r,c,"| |_______| |");
              r++;
              win_write_line_at(b,r,c,"|___________|");
              r++;

            }

            if(value == 7){
                win_write_line_at(b,r,c," ___________ ");
                r++;
                win_write_line_at(b,r,c,"|           |");
                r++;
                win_write_line_at(b,r,c,"|  ______   |");
                r++;
                win_write_line_at(b,r,c,"| |____  |  |");
                r++;
                win_write_line_at(b,r,c,"|      | |  |");
                r++;
                win_write_line_at(b,r,c,"|      | |  |");
                r++;
                win_write_line_at(b,r,c,"|      | |  |");
                r++;
                win_write_line_at(b,r,c,"|      |_|  |");
                r++;
                win_write_line_at(b,r,c,"|___________|");
                r++;

              }

              if(value == 8){
                  win_write_line_at(b,r,c," ___________ ");
                  r++;
                  win_write_line_at(b,r,c,"|           |");
                  r++;
                  win_write_line_at(b,r,c,"|  _______  |");
                  r++;
                  win_write_line_at(b,r,c,"| |  ___  | |");
                  r++;
                  win_write_line_at(b,r,c,"| | |___| | |");
                  r++;
                  win_write_line_at(b,r,c,"| |  ___  | |");
                  r++;
                  win_write_line_at(b,r,c,"| | |___| | |");
                  r++;
                  win_write_line_at(b,r,c,"| |_______| |");
                  r++;
                  win_write_line_at(b,r,c,"|___________|");
                  r++;

                }

                if(value == 9){
                    win_write_line_at(b,r,c," ___________ ");
                    r++;
                    win_write_line_at(b,r,c,"|           |");
                    r++;
                    win_write_line_at(b,r,c,"|  ______   |");
                    r++;
                    win_write_line_at(b,r,c,"| | __   |  |");
                    r++;
                    win_write_line_at(b,r,c,"| ||__|  |  |");
                    r++;
                    win_write_line_at(b,r,c,"| |___   |  |");
                    r++;
                    win_write_line_at(b,r,c,"|     |  |  |");
                    r++;
                    win_write_line_at(b,r,c,"|     |__|  |");
                    r++;
                    win_write_line_at(b,r,c,"|___________|");
                    r++;

                  }

                  if(value == 10){
                      win_write_line_at(b,r,c," ___________ ");
                      r++;
                      win_write_line_at(b,r,c,"|           |");
                      r++;
                      win_write_line_at(b,r,c,"| _   _____ |");
                      r++;
                      win_write_line_at(b,r,c,"|| | |  _  ||");
                      r++;
                      win_write_line_at(b,r,c,"|| | | | | ||");
                      r++;
                      win_write_line_at(b,r,c,"|| | | | | ||");
                      r++;
                      win_write_line_at(b,r,c,"|| | | |_| ||");
                      r++;
                      win_write_line_at(b,r,c,"||_| |_____||");
                      r++;
                      win_write_line_at(b,r,c,"|___________|");
                      r++;

                    }

}



int cards(Interface *i){
  char** board;
  int sizeb[2];
  int lu=0,jav=0,cc = 0,next,win;
  char points[30];

  board = create_map("cards",sizeb);
  set_player(i,' ',0,0);
  set_board(i,board,sizeb[0],sizeb[1]);

  draw_board(i,1);
  draw_score(i,1);
  draw_text(i,1);

  sc_rectangle *t,*s,*b;
  t = get_text(i);
  s = get_score(i);
  b = get_board(i);

  win_write_line_at(t,4,4,"A: So,in this card game, each turn you'll be given a first card");
  usleep(5000000);
  win_write_line_at(t,5,4,"A: This card will have a value from 1 to 10");
  usleep(5000000);
  win_write_line_at(t,6,4,"A: The card deck has 52 cards, 4 of each number except of the 10.");
  usleep(5000000);
  win_write_line_at(t,7,4,"A: There are 16 cards with value 10");
  usleep(5000000);
  draw_text(i,1);
  win_write_line_at(t,4,4,"A: After you recieve your card,you will have to say if the next card in ");
  win_write_line_at(t,5,4,"A: the deck is lower or bigger than your card");
  usleep(5000000);
  win_write_line_at(t,6,4,"A: When you make your choice, you'll be given a second card(the next deck card)");
  usleep(5000000);
  draw_text(i,1);
  win_write_line_at(t,4,4,"A: If your answer is correct, you get one point.");
  win_write_line_at(t,5,4,"A: If it's not, you loose one point(unless you have 0)");
  usleep(5000000);
  win_write_line_at(t,6,4,"A: The first one who gets to 5 points win");
  usleep(4000000);
  win_write_line_at(t,7,4,"A: So, Javiti,you start!");

  sprintf(points,"Javiti: %d",jav);
  win_write_line_at(s,4,4,points);
  sprintf(points,"Lucia: %d",lu);
  win_write_line_at(s,5,4,points);


  Deck* d;
  d = create_deck();
  d = set_deck(d);
  d = shuffle(d);

  while(jav < 5 && lu < 5 ){
    draw_text(i,1);
    win_write_line_at(t,4,4,"Here's your first card!");
    draw_cards(b,7,14,card_get_value(deck_get_card(d,cc)));
    cc++;
    usleep(2000000);
    while(1){
      win_write_line_at(t,5,4,"The next card is lower or bigger? [l/b]: ");
      next = _read_key();
      if(next == 'q') return 1;
      if(next != 'l' && next!= 'b') continue;
      break;
    }
    draw_text(i,1);
    win_write_line_at(t,4,4,"Let's see the next card and check your answer");
    next1:usleep(3000000);
    draw_cards(b,7,60,card_get_value(deck_get_card(d,cc)));
    if(card_get_value(deck_get_card(d,cc)) > card_get_value(deck_get_card(d,cc-1)) && next == 'b') win =1;
    if(card_get_value(deck_get_card(d,cc)) > card_get_value(deck_get_card(d,cc-1)) && next == 'l') win =0;
    if(card_get_value(deck_get_card(d,cc)) < card_get_value(deck_get_card(d,cc-1)) && next == 'b') win =0;
    if(card_get_value(deck_get_card(d,cc)) < card_get_value(deck_get_card(d,cc-1)) && next == 'l') win =1;
    if(card_get_value(deck_get_card(d,cc)) == card_get_value(deck_get_card(d,cc-1)) ) {
      win_write_line_at(t,5,4,"Oh, it has the same value. Let's check the next card");
      cc++;
      usleep(3000000);
      draw_text(i,1);
      goto next1;
    }
    cc++;
    if(win == 1){
      win_write_line_at(t,5,4,"Your answer is correct! A point for you!");
      jav++;
    }
    if(win == 0){
      win_write_line_at(t,5,4,"Your answer is incorrect! You loose one point");
      if(jav != 0) jav--;
    }
    sprintf(points,"Javiti: %d",jav);
    win_write_line_at(s,4,4,points);

    if(jav == 5){
      win_write_line_at(t,6,4,"YOU WIN!");
      usleep(3000000);
      return 1;
    };
    usleep(5000000);
    draw_board(i,1);
    draw_text(i,1);
    win_write_line_at(t,4,4,"Okay, now is Lucia's turn");
    usleep(2000000);
    draw_text(i,1);
    win_write_line_at(t,4,4,"Here's your first card!");
    draw_cards(b,7,14,card_get_value(deck_get_card(d,cc)));
    cc++;
    usleep(2000000);
    win_write_line_at(t,5,4,"The next card is lower or bigger? [l/b]: ");
    usleep(3000000);

    if(card_get_value(deck_get_card(d,cc-1)) < 7){
      win_write_line_at(t,5,45,"b");
      next = 'b';
    }
    if(card_get_value(deck_get_card(d,cc-1)) >= 7){
      win_write_line_at(t,5,45,"l");
      next = 'l';
    }
    usleep(2000000);
    draw_text(i,1);
    win_write_line_at(t,4,4,"Let's see the next card and check your answer");
    next2:usleep(2000000);
    draw_cards(b,7,60,card_get_value(deck_get_card(d,cc)));
    if(card_get_value(deck_get_card(d,cc)) > card_get_value(deck_get_card(d,cc-1)) && next == 'b') win =1;
    if(card_get_value(deck_get_card(d,cc)) > card_get_value(deck_get_card(d,cc-1)) && next == 'l') win =0;
    if(card_get_value(deck_get_card(d,cc)) < card_get_value(deck_get_card(d,cc-1)) && next == 'b') win =0;
    if(card_get_value(deck_get_card(d,cc)) < card_get_value(deck_get_card(d,cc-1)) && next == 'l') win =1;
    if(card_get_value(deck_get_card(d,cc)) == card_get_value(deck_get_card(d,cc-1)) ) {
      win_write_line_at(t,5,4,"Oh, it has the same value. Let's check the next card");
      cc++;
      usleep(3000000);
      draw_text(i,1);
      goto next2;
    }
    cc++;

    if(win == 1){
      win_write_line_at(t,5,4,"Your answer is correct! A point for you!");
      lu++;
    }
    if(win == 0){
      win_write_line_at(t,5,4,"Your answer is incorrect! You loose one point");
      if(lu != 0) lu--;
    }
    sprintf(points,"Lucia: %d",lu);
    win_write_line_at(s,5,4,points);
    if(lu == 5) break;
    win_write_line_at(t,6,4,"Javiti's turn!");
    usleep(3000000);
    draw_board(i,1);
  }

  win_write_line_at(t,6,4,"LUCIA WINS!");
  usleep(3000000);
  return 0;


}
