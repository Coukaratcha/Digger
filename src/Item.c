#include "../include/Item.h"

Item* Item_initialiser(void)
{
   Item* item=(Item*)malloc(sizeof(Item));
   item->table[FORCE]=0;
   item->table[FLASHBACK]=0;
   item->table[KEYSWITCH]=0;
   item->table[ROCK]=0;
   return item;
}

void Item_ajouter(Item *item, TypeItem type)
{
    switch(type)
    {
    case FORCE:
        item->table[FORCE]++;
        break;
    case FLASHBACK:
        item->table[FLASHBACK]++;
        break;
    case KEYSWITCH:
        item->table[KEYSWITCH]++;
        break;
    case ROCK:
        item->table[ROCK]++;
        break;
    default:
        break;
    }
}

void Item_enlever(Item *item, TypeItem type)
{
    switch(type)
    {
    case FORCE:
        if(item->table[FORCE]!=0) item->table[FORCE]--;
        break;
    case FLASHBACK:
        if(item->table[FLASHBACK]!=0) item->table[FLASHBACK]--;
        break;
    case KEYSWITCH:
        if(item->table[KEYSWITCH]!=0) item->table[KEYSWITCH]--;
        break;
    case ROCK:
        if(item->table[ROCK]!=0) item->table[ROCK]--;
        break;
    default:
        break;
    }
}

void Item_faireEffet(TypeItem type)
{
    switch(type)
    {
    case FORCE:
        ///////////// effet de force ///////////////////
        break;
    case FLASHBACK:
        //////////// effet de flashback ///////////
        break;
    case KEYSWITCH:
        //////////// effet de keyswitch /////////////
        break;
    case ROCK:
        //////////// effet de rock ///////////////
        break;
    default:
        break;
    }
}

void Item_utiliser(Item *item, TypeItem type)
{
    Item_enlever(item,type);
    Item_faireEffet(type);
}
