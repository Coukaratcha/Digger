#include "../include/Item.h"

Item* Item_initialiser(void)
{
   Item* item=(Item*)malloc(sizeof(Item*));
   int i;
   for(i=0;i<4;i++)
   {
      item->table[i]=0;
   }
   return item;
}

void Item_ajouter(Item *item, TypeItem type)
{
    switch(type)
    {
    case 0:
        item->table[0]++;
        break;
    case 1:
        item->table[1]++;
        break;
    case 2:
        item->table[2]++;
        break;
    case 3:
        item->table[0]++;
        break;
    default:
        break;
    }
}

void Item_enlever(Item *item, TypeItem type)
{
    switch(type)
    {
    case 0:
        if(item->table[0]!=0) item->table[0]--;
        break;
    case 1:
        if(item->table[1]!=0) item->table[1]--;
        break;
    case 2:
        if(item->table[2]!=0) item->table[2]--;
        break;
    case 3:
        if(item->table[3]!=0) item->table[0]--;
        break;
    default:
        break;
    }
}

void Item_faireEffet(TypeItem type)
{
    switch(type)
    {
    case 0:
        ///////////// effet de force ///////////////////
        break;
    case 1:
        //////////// effet de flashback ///////////
        break;
    case 2:
        //////////// effet de keyswitch /////////////
        break;
    case 3:
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
