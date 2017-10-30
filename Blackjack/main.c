

#include "deck.h"
#include <unistd.h>


int main(int argc, char** argv) {

    Deck *d;
    char card[1],round[1],ace[2];
    int croupier=0,asv,points=0,cc;
    d = create_deck();
    if (!d) return 0;
    d = set_deck(d);
    if (!d) return 0;

    printf("Let's start playing\n");

    while(1){
        d = shuffle(d);
        cc = 0;
        if (!d) return 0;
        points=0;
        while(1){
           printf("Your card is  ");
           print_card(deck_get_card(d,cc),stdout);
           if(card_get_value(deck_get_card(d,cc))==1){
               printf("You want it to value 1 or 11?: ");
               fgets(ace,10,stdin);
               asv = atoi(ace);
               points += asv;
           }
           else{
               points+=card_get_value(deck_get_card(d,cc));
           }

           printf("You have %d points. ",points);
           if(points > 21){
             printf("You exceed 21!You lost!\n" );
             cc++;
             break;
           }
           while(1){
             printf("Do you want a new card?[Y/N] :");
             fgets(card,10,stdin);
             if(*card == 'N'){
               printf("You stand with %d points\n",points);
               break;
             }
             if(*card != 'N' && *card != 'Y') continue;
             else break;
           }
           cc++;
           if(*card == 'N') break;
         }

         if(points <=21){
           printf("Now is Santi's turn. ");
          croupier=0;
          while(croupier<17){

             usleep(5000000);

             printf("Santi's card is ");
             print_card(deck_get_card(d,cc),stdout);
             if(card_get_value(deck_get_card(d,cc)) == 1){
               srand(rand());
               if(rand()%4 == 0){
                 printf(" Real Value 11\n");
                 croupier+=(card_get_value(deck_get_card(d,cc)) + 10);
               }
               else printf("Real Value 1\n");
             }
              croupier += card_get_value(deck_get_card(d,cc));
              printf("Total: %d\n",croupier);
              cc++;
            }

             usleep(3000000);

          if(croupier > 21){
              printf("Santi exceed 21!You won!\n");
          }
          else if(croupier > points){
            printf("Santi stands with %d points\n",croupier);
            usleep(3000000);
            printf("Santi has %d points and you have %d.You lost\n",croupier,points);
          }
          else if(croupier == points){
              printf("Santi stands with %d points\n",croupier);
              usleep(3000000);
              printf("You and Santi have the same points(%d).It's a draw.Let's play again\n",points);
              continue;
          }
          else{
            printf("Santi stands with %d points\n",croupier);
            usleep(3000000);
            printf("Santi has %d points and you have %d.You won!\n",croupier,points);
          }
        }
        usleep(3000000);
        while(1){
          printf("Do you want to play again?[Y/N]: ");
          fgets(round,10,stdin);
          if(*round != 'Y' && *round != 'N') continue;
          break;
        }
        if(*round == 'Y') continue;
        else break;
    }
    printf("Thanks for playing\n");
    return 1;
  }
