#ifndef OPTION_H
#define OPTION_H

typedef struct {
    char *nom;
    unsigned int index;
} Option;

Option* Option_creer(void);
void Option_supprimer(Option *option);

#endif
