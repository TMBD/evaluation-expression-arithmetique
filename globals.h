

////////////////////////////////////////////////////////////////////////////////////
//////////// DEFINITIONS/DECLARATIONS DES VARIABLES/CONSTANTES GLOBALES ////////////
////////////////////////////////////////////////////////////////////////////////////


/*
    Declaration de la constante qui définit
    la taille maximale de la chaine que l'utilisateur
    pourra entrer.
*/
#define N 100

/*

    ->  La variable @CHIFFRES
        utilisée par fonction @chiffre() permet de savoir
        si un caractère est un chiffre ou non.

    ->  La variable @INVALID_CHAR
        permet de savoir si nous avons bien un opérateur ou non.

    ->  La constante @INVALID_IND permet de dire qu'un caractère
        ou ensemble de caractère n'est pas un entier valide.

    ->  La constante @INVALID_EXP permet de dire qu'un caractère
        ou ensemble de caractère n'est pas une expression valide.

    ->  Le tableau de caractère @expression_arith contiendra
        la chaine (expression) que nous sommes entrain d'analyser.

    ->  La variable caractère @calu contiendra toujours
        le premier caractère de @expression_arith non encore examiné.

    ->  La variable @taille contiendra le nombre de caractère
        de notre expression (vu que la taille du tableau
        n'est pas forcement atteint).

    ->  @indice_calu est l'indice de la variable @calu
        dans le tableau @expression_arith.

    -> @arret est un booleen qui nous permet à tout instant
        de savoir si l'expression peut etre valide ou pas.
        Si elle peut etre valide elle contiendra la valeur @false
        dans quel cas nous continuons l'analyse de l'expression.
        Si elle ne peut plus etre valide peu importe le reste de la chaine
        alors elle vaudra true dans quelle cas nous arretons
        tout le treitement pour dire à l'utilisateur que
        l'expression n'est pas valide.
*/
const char  CHIFFRES[10] = {'0','1','2','3','4','5','6','7','8','9'},
            ADD = '+',
            MOINS = '-',

            MULT = '*',
            DIV = '/',

            INVALID_CHAR = 'x',

            BLANC_CHARS[4] = {9, 10, 13, 32};


const int INVALID_INT = -1, INVALID_EXP = -5;
char expression_arith[N], calu;
int taille, indice_calu;
bool arret;

