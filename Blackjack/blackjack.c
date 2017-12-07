

#include "blackjack.h"



int Blackjack(Interface *i) {

    Deck *d;
    char ace[2],p[3],aux[512];
    int croupier=0,asv,points=0,cc,card,smoke,round;   /*asv is used to choose the value of an ace. cc is used to count the cards*/
    d = create_deck();
    if (!d) return 0;
    d = set_deck(d);
    if (!d) return 0;
    srand(time(NULL));

    sc_rectangle *t,*s;
    t = get_text(i);
    s = get_score(i);
    win_write_line_at(t,4,4,"Let's start playing");

    win_write_line_at(s,4,4,"Your points :");
    win_write_line_at(s,6,4,"Santi's points :");


    usleep(2000000);

    while(1){
        points=0;
        sprintf(p,"%d",points);
        win_write_line_at(s,4,18,p);
        d = shuffle(d);
        cc = 0;
        if (!d) return 0;
        points=0;

        while(1){
           draw_text(i,1);
           win_write_line_at(t,4,4,"Your card is  ");
           print_card(deck_get_card(d,cc),stdout);
          if(card_get_value(deck_get_card(d,cc))==1){
              /* while(1){

               printf("You want it to value 1 or 11?: ");
               fgets(ace,10,stdin);
               asv = atoi(ace);
               if(asv != 1 && asv !=11) continue;
               points += asv;
               break;
             }*/
           }
           else{
               points+=card_get_value(deck_get_card(d,cc));

           }


            usleep(2000000);

            sprintf(p,"%d",points);
            win_write_line_at(s,4,18,p);

           if(points > 21){
             _move_to(t,5,4);
             printf("You exceed 21!You lost!\n" );
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
                _move_to(t,7,4);
               printf("Your alcohol level decreases because of the cigarette! Now let's play");
             }
             else{
                _move_to(t,7,4);
               printf("Now let's play\n");
             }
           }

          croupier=0;
          while(croupier<17){

             usleep(2000000);

             draw_text(i,1);
             _move_to(t,4,4);
             printf("Santi's card is ");
             print_card(deck_get_card(d,cc),stdout);
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
              win_write_line_at(t,5,4,"Santi exceed 21!You won!");
          }
          else if(croupier > points){
            sprintf(aux,"Santi stands with %d points",croupier);
            win_write_line_at(t,5,4,aux);
            usleep(3000000);
            sprintf(aux,"Santi has %d points and you have %d.You lost!",croupier,points);
            win_write_line_at(t,6,4,aux);
          }
          else if(croupier == points){
              sprintf(aux,"Santi stands with %d points",croupier);
              win_write_line_at(t,5,4,aux);
              usleep(3000000);
              sprintf(aux,"You and Santi have the same points(%d).It's a draw.Let's play again",points);
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
            sprintf(aux,"Santi has %d points and you have %d.You won!",croupier,points);
            win_write_line_at(t,6,4,aux);
          }
        }
        usleep(3000000);
        while(1){
          draw_text(i,1);
          _move_to(t,4,4);
          printf("Do you want to play again?[y/n]: ");
          round = _read_key();
          if(round != 'y' && round != 'n') continue;
          if(card == 'q') return 0;
          break;
        }
        if(round == 'y'){
          cc = 0;
          draw_score(i,1);
          win_write_line_at(s,4,4,"Your points :");
          win_write_line_at(s,6,4,"Santi's points :");
          continue;
        }
        else break;
    }
    delete_deck(d);
    draw_text(i,1);
    _move_to(t,4,4);
    printf("Thanks for playing!");
    return 1;
  }
