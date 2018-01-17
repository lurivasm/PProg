#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#define ERR -1
#define OK (!(ERR))
typedef struct _player Player;

Player* create_player();
/*Create a new player*/
void delete_player(Player* pl);
/*Delete a current player*/
int modify_alcohol(Player* pl,int mod);
/*Increase or decrease the alcohol parameter*/
int get_alcohol(Player* pl);
/*returns the actual value of alcohol*/
int is_dead(Player* pl);
/*Informs about player's life (-1=Dead,0=Alive)*/

#endif
