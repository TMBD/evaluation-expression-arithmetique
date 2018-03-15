#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Inclusion du fichier contenant la fonction qui se charge de la pr�sentation du programme
#include "presentation.h"

//Inclusion du fichier contenant les d�finitions des fonctions utilis�es
#include "definitions_fonctions.h"




////////////////////////////////////////////////////////////
//////////////// PRESENTATION DU PRGRAMME //////////////////
////////////////////////////////////////////////////////////

/*
@autors     :   Thierno Mamadou Boye DIALLO
                Cod� K�b�
                Moustapha L�
                Saliou SENE

@date       :   15/03/2018

Comments    :   Ce programme permet d'analyser et d'�valuer une expression arithm�tique donn�e par l'utilisateur.
                Il utilise une methode qui consiste � lire l'expression saisie par l'utilisateur caract�re par caract�re
                et du d�but vers la fin.
                L'agorithme utilise principalement la grammaire BNF(Backus-Naur Form) ou grammaire non contextuelle.
*/






////////////////////////////////////////////////////////////
//////////// DEFINITIONS DE LA FONCTION @main() ////////////
////////////////////////////////////////////////////////////


/*
    -> DEFINITION DE LA FONCTION @main() :
    Etant le point d'entr�e de notre programme,
    c'est dans cette fonction que nous initialiserons
    tous les variables qui en ont besoin.
    Aussi c'est � partire de cette fonction que nous appelerons
    la fonction @lire_utile() qui se chargera de lire convenablement
    la chaine entr�e par l'utilisateur.
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

