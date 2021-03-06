

#include "blackjack.h"


int draw_card(sc_rectangle* b,int row ,int column ,char *value){
  if(!b) return 0;
  char aux[10];


  win_write_line_at(b,row,column," __ ");
  if(strcmp(value,"10")==0) sprintf(aux,"|%s|",value);
  else sprintf(aux,"|%s |",value);

  win_write_line_at(b,row+1,column,aux);
  win_write_line_at(b,row+2,column,"|__|");
  return 1;
}

int  main_Blackjack(Interface *i,World *w){


	int quit,res;
	char** board;

	int sizeb[2],mode;


 /*We create the maps for the board,score and text and set them on the interface*/
	board = create_map("portada",sizeb);


	set_board(i,board,sizeb[0],sizeb[1]);

	draw_board(i,1);

	draw_score(i,1);

	draw_text(i,1);



	sc_rectangle* t;
 	t = get_text(i);
 	if(!t) return;

	win_write_line_at(t,4,4,"Press the space bar to continue");




	while(1){
	quit = _read_key();
	/*pressing q it exits*/
	if (quit == 'q')  return;
	/*if you press the space bar,you move foward*/
	if(quit == 32) break;
	}
/*we create the new map,and draw it in board*/
	board = create_map("sala",sizeb);
	set_board(i,board,sizeb[0],sizeb[1]);
	draw_board(i,1);
	draw_text(i,1);
/*The player chooses the game mode*/
	while(1){
		win_write_line_at(t,4,4,"Press e for the easy mode or h for the hard mode");
		mode = _read_key();
		if(mode != 'e' && mode != 'h') continue;
		break;
}
/*depending on the game mode,we call a different function*/
if(mode == 'e') res = Blackjack(i,w);
if(mode == 'h') res = Blackjack_hard(i,w);

return res;
}


int Blackjack_hard(Interface *i,World *w) {

    Deck *d;
    char p[3],aux[512],c[3];
    int croupier=0,points=0,cc,card,smoke,round,ace,column,prob,javiti = 0,santi = 0;   /* cc is used to count the cards*/
    d = create_deck();
    if (!d) return 0;
    d = set_deck(d);
    if (!d) return 0;
    srand(time(NULL));

    Player *p;
    p = get_player(w);

    sc_rectangle *t,*s,*b;
    t = get_text(i);
    s = get_score(i);
    b = get_board(i);
    draw_text(i,1);
    win_write_line_at(t,5,4,"The one who wins 3 rounds is the final winner");
    usleep(2000000);
    win_write_line_at(t,4,4,"Let's start playing");

    win_write_line_at(s,4,4,"Your points :");
    win_write_line_at(s,6,4,"Santi's points :");





    usleep(2000000);

    while(1){
        draw_board(i,1);
        points=0;
        sprintf(p,"%d",points);
        win_write_line_at(s,4,18,p);
        d = shuffle(d);
        cc = 0;
        if (!d) return 0;
        points=0;
        column =12 ;

        while(1){
           draw_text(i,1);
           win_write_line_at(t,4,4,"Your card is  ");
           print_card(deck_get_card(d,cc),stdout);
           sprintf(c,"%d",card_get_value(deck_get_card(d,cc)));
           column+=6;
           draw_card(b,16,column,c);
          if(card_get_value(deck_get_card(d,cc))==1){
               while(1){

               win_write_line_at(t,5,4,"You want it to value 11?[y/n]: ");
               ace = _read_key();
               if(ace != 'y' && ace !='n') continue;
               if(ace =='y'){
                 points+=11;
                 break;
               }
               else{
                 points+=1;
                 break;
               }

             }
             draw_text(i,1);
           }
           else{
               points+=card_get_value(deck_get_card(d,cc));
               usleep(2000000);

           }




            sprintf(p,"%d",points);
            win_write_line_at(s,4,18,p);


           if(points > 21){
             _move_to(t,5,4);
             printf("You exceed 21!You lost this round!\n" );
             cc++;
             santi++;
             break;
           }

           while(1){
             _move_to(t,5,4);
             printf("Do you want a new card?[y/n] :");
             card = _read_key();

             if(card == 'n'){
               _move_to(t,6,4);
               printf("You stand with %d points\n",points);
               break;
             }

             if(card != 'n' && card != 'y' && card != 'q') continue;
             if(card == 'q') return 0;
             else break;
           }
           cc++;
           if(card == 'n') break;
         }

         if(points <=21){

           draw_text(i,1);
           win_write_line_at(t,4,4,"Now is Santi's turn. ");


           if(rand()%10 == 0){
             _move_to(t,5,4);
             printf("But Santi wants to smoke first.");
             while(1){
               _move_to(t,6,4);
               printf("Do you want to smoke with him?[y/n]: ");
               smoke = _read_key();
               if(smoke != 'y' && smoke != 'n') continue;
               break;
             }
             if(smoke == 'y'){
               win_write_line_at(t,7,4,"Your alcohol level decreases because of the cigarette! Now let's play");
               modify_alcohol(p,-10);
             }
             else{

               win_write_line_at(t,7,4,"Now let's play\n");
             }
           }

          croupier=0;
          column = 22;
          prob = 0;
          while(croupier<21){

             usleep(2000000);

             draw_text(i,1);
             _move_to(t,4,4);
             printf("Santi's card is ");
             print_card(deck_get_card(d,cc),stdout);
             sprintf(c,"%d",card_get_value(deck_get_card(d,cc)));
             column += 6;
             draw_card(b,9,column,c);
             if(card_get_value(deck_get_card(d,cc)) == 1){
               if(rand()%(2+prob) == 0){
                 _move_to(t,5,4);
                 printf(" Real Value 11");
                 croupier+=(card_get_value(deck_get_card(d,cc)) + 10);
               }
               else{
                  _move_to(t,5,4);
                  printf("Real Value 1");
                }
             }
              croupier += card_get_value(deck_get_card(d,cc));
              sprintf(p,"%d",croupier);
              win_write_line_at(s,6,21,p);
              cc++;
              if(croupier == 16 && rand()%2 == 0){
                deck_card_swap(d,cc,deck_find_card_value(d,5,cc));
              }
              if(croupier == 17 && rand()%2 == 0){
                deck_card_swap(d,cc,deck_find_card_value(d,4,cc));
              }
              if(croupier == 18 && rand()%2 == 0){
                deck_card_swap(d,cc,deck_find_card_value(d,3,cc));
              }
              if(croupier == 19 && rand()%2 == 0){
                deck_card_swap(d,cc,deck_find_card_value(d,2,cc));
              }
              if(croupier == 20 && rand()%2 == 0){
                deck_card_swap(d,cc,deck_find_card_value(d,1,cc));
                prob = 2;
              }

            }

             usleep(3000000);

          if(croupier > 21){
              win_write_line_at(t,5,4,"Santi exceed 21!You won this round!");
              javiti++;
          }
          else if(croupier > points){
            sprintf(aux,"Santi stands with %d points",croupier);
            win_write_line_at(t,5,4,aux);
            usleep(3000000);
            sprintf(aux,"Santi has %d points and you have %d.You lost this round!",croupier,points);
            win_write_line_at(t,6,4,aux);
            santi++;
          }
          else if(croupier == points){
              sprintf(aux,"Santi stands with %d points",croupier);
              win_write_line_at(t,5,4,aux);
              usleep(3000000);
              sprintf(aux,"You and Santi have the same points(%d).It's a draw.Let's play this round again",points);
              win_write_line_at(t,5,4,aux);

              draw_score(i,1);
              win_write_line_at(s,4,4,"Your points :");
              win_write_line_at(s,6,4,"Santi's points :");
              continue;
          }
          else if (points > croupier){
            sprintf(aux,"Santi stands with %d points",croupier);
            win_write_line_at(t,5,4,aux);
            usleep(3000000);
            sprintf(aux,"Santi has %d points and you have %d.You won this round!",croupier,points);
            javiti++;
            win_write_line_at(t,6,4,aux);
          }
        }
        usleep(3000000);
        if(javiti == 3 || santi == 3) break;
    }

    if(javiti > santi) {
      win_write_line_at(t,4,4,"YOU WON");
      delete_deck(d);
      draw_text(i,1);
      _move_to(t,5,4);
      printf("Thanks for playing!");
      usleep(3000000);
      return 4;
    }
    if(javiti < santi) {
      win_write_line_at(t,4,4,"YOU LOOSE");
      delete_deck(d);
      draw_text(i,1);
      _move_to(t,5,4);
      printf("Thanks for playing!");
      usleep(3000000);
      return 3;
    }

  }







  int Blackjack(Interface *i,World *w){
    Deck *d;
    char p[3],aux[512],c[3];
    int croupier=0,points=0,cc,card,smoke,round,ace,column,javiti = 0,santi = 0;   /* cc is used to count the cards*/
    d = create_deck();
    if (!d) return 0;
    d = set_deck(d);
    if (!d) return 0;
    srand(time(NULL));

    Player *p;
    p = get_player(w);

    sc_rectangle *t,*s,*b;
    t = get_text(i);
    s = get_score(i);
    b = get_board(i);
    draw_text(i,1);
    win_write_line_at(t,5,4,"The one who wins 3 rounds is the final winner");
    usleep(2000000);
    win_write_line_at(t,4,4,"Let's start playing");

    win_write_line_at(s,4,4,"Your points :");
    win_write_line_at(s,6,4,"Santi's points :");






    usleep(2000000);

    while(1){
        draw_board(i,1);
        points=0;
        sprintf(p,"%d",points);
        win_write_line_at(s,4,18,p);
        d = shuffle(d);
        cc = 0;
        if (!d) return 0;
        points=0;
        column =12 ;



        while(1){
           draw_text(i,1);
           win_write_line_at(t,4,4,"Your card is  ");
           print_card(deck_get_card(d,cc),stdout);
           sprintf(c,"%d",card_get_value(deck_get_card(d,cc)));
           column+=6;
           draw_card(b,16,column,c);
          if(card_get_value(deck_get_card(d,cc))==1){
               while(1){

               win_write_line_at(t,5,4,"You want it to value 11?[y/n]: ");
               ace = _read_key();
               if(ace != 'y' && ace !='n') continue;
               if(ace =='y'){
                 points+=11;
                 break;
               }
               else{
                 points+=1;
                 break;
               }

             }
             draw_text(i,1);
           }
           else{
               points+=card_get_value(deck_get_card(d,cc));
               usleep(2000000);

           }




            sprintf(p,"%d",points);
            win_write_line_at(s,4,18,p);


           if(points > 21){
             _move_to(t,5,4);
             printf("You exceed 21!You lost this round!\n" );
             santi++;
             cc++;
             break;
           }

           while(1){
             _move_to(t,5,4);
             printf("Do you want a new card?[y/n] :");
             card = _read_key();

             if(card == 'n'){
               _move_to(t,6,4);
               printf("You stand with %d points\n",points);
               break;
             }

             if(card != 'n' && card != 'y' && card != 'q') continue;
             if(card == 'q') return 0;
             else break;
           }
           cc++;
           if(card == 'n') break;
         }

         if(points <=21){

           draw_text(i,1);
           win_write_line_at(t,4,4,"Now is Santi's turn. ");


           if(rand()%10 ==0){
             _move_to(t,5,4);
             printf("But Santi wants to smoke first.");
             while(1){
               _move_to(t,6,4);
               printf("Do you want to smoke with him?[y/n]: ");
               smoke = _read_key();
               if(smoke != 'y' && smoke != 'n') continue;
               break;
             }
             if(smoke == 'y'){
               win_write_line_at(t,7,4,"Your alcohol level decreases because of the cigarette! Now let's play");
               modify_alcohol(p,-10);
             }
             else{

               win_write_line_at(t,7,4,"Now let's play\n");
             }
           }

          croupier=0;
          column = 22;
          while(croupier<17){

             usleep(2000000);

             draw_text(i,1);
             _move_to(t,4,4);
             printf("Santi's card is ");
             print_card(deck_get_card(d,cc),stdout);
             sprintf(c,"%d",card_get_value(deck_get_card(d,cc)));
             column += 6;
             draw_card(b,9,column,c);
             if(card_get_value(deck_get_card(d,cc)) == 1){
               if(rand()%2 == 0){
                 _move_to(t,5,4);
                 printf(" Real Value 11");
                 croupier+=(card_get_value(deck_get_card(d,cc)) + 10);
               }
               else{
                  _move_to(t,5,4);
                  printf("Real Value 1");
                }
             }
              croupier += card_get_value(deck_get_card(d,cc));
              sprintf(p,"%d",croupier);
              win_write_line_at(s,6,21,p);
              cc++;
            }

             usleep(3000000);

          if(croupier > 21){
              win_write_line_at(t,5,4,"Santi exceed 21!You won this round!");
              javiti++;
          }
          else if(croupier > points){
            sprintf(aux,"Santi stands with %d points",croupier);
            win_write_line_at(t,5,4,aux);
            usleep(3000000);
            sprintf(aux,"Santi has %d points and you have %d.You lost this round!",croupier,points);
            santi++;
            win_write_line_at(t,6,4,aux);
          }
          else if(croupier == points){
              sprintf(aux,"Santi stands with %d points",croupier);
              win_write_line_at(t,5,4,aux);
              usleep(3000000);
              sprintf(aux,"You and Santi have the same points(%d).It's a draw.Let's play  this round again",points);
              win_write_line_at(t,5,4,aux);

              draw_score(i,1);
              win_write_line_at(s,4,4,"Your points :");
              win_write_line_at(s,6,4,"Santi's points :");
              continue;
          }
          else if (points > croupier){
            sprintf(aux,"Santi stands with %d points",croupier);
            win_write_line_at(t,5,4,aux);
            usleep(3000000);
            sprintf(aux,"Santi has %d points and you have %d.You won this round!",croupier,points);
            javiti++;
            win_write_line_at(t,6,4,aux);
          }
        }
        usleep(3000000);
        if(javiti == 3 || santi == 3) break;
        draw_text(i,1);
        win_write_line_at(t,4,4,"Let's head to the next round");
        usleep(3000000);
    }

    if(javiti > santi) {
      win_write_line_at(t,4,4,"YOU WON");
      delete_deck(d);
      draw_text(i,1);
      _move_to(t,5,4);
      printf("Thanks for playing!");
      usleep(3000000);
      return 1;
    }
    if(javiti < santi) {
      win_write_line_at(t,4,4,"YOU LOOSE");
      delete_deck(d);
      draw_text(i,1);
      _move_to(t,5,4);
      printf("Thanks for playing!");
      usleep(3000000);
      return 0;
    }

  }
