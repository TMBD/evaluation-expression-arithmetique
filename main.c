#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Inclusion du fichier contenant la fonction qui se charge de la présentation du programme
#include "presentation.h"

//Inclusion du fichier contenant les définitions des fonctions utilisées
#include "definitions_fonctions.h"




////////////////////////////////////////////////////////////
//////////////// PRESENTATION DU PRGRAMME //////////////////
////////////////////////////////////////////////////////////

/*
@autors     :   Thierno Mamadou Boye DIALLO
                Codé Kébé
                Moustapha LÔ
                Saliou SENE

@date       :   15/03/2018

Comments    :   Ce programme permet d'analyser et d'évaluer une expression arithmétique donnée par l'utilisateur.
                Il utilise une methode qui consiste à lire l'expression saisie par l'utilisateur caractère par caractère
                et du début vers la fin.
                L'agorithme utilise principalement la grammaire BNF(Backus-Naur Form) ou grammaire non contextuelle.
*/






////////////////////////////////////////////////////////////
//////////// DEFINITIONS DE LA FONCTION @main() ////////////
////////////////////////////////////////////////////////////


/*
    -> DEFINITION DE LA FONCTION @main() :
    Etant le point d'entrée de notre programme,
    c'est dans cette fonction que nous initialiserons
    tous les variables qui en ont besoin.
    Aussi c'est à partire de cette fonction que nous appelerons
    la fonction @lire_utile() qui se chargera de lire convenablement
    la chaine entrèe par l'utilisateur.
    Enfin cette fonction se chargera aussi d'afficher le resultat du programme.
*/

void main()
{
    presenter();

    label : printf("=> A toi : ");

    taille = 0;
    strncpy(expression_arith, "", N);
    indice_calu = 0;
    arret = false;

    lire_utile(expression_arith);

    if(!strcmp(expression_arith, ".")){
        printf("\n");
        printf("Au revoir...");
        printf("\n\n");
        getchar();
        exit(EXIT_SUCCESS);
    }

    int exp = expression();

    if(arret || indice_calu < taille){
        printf("La syntaxe de l'expression est erronees\n");
    }
    else {
        printf("La syntaxe de l'expression est correcte\n");
        printf("sa valeur est : %d\n",exp);
    }

    printf("__________________________________\n");
    printf("\n\n");

    goto label;
}

