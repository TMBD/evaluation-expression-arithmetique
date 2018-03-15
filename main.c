#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
    Declaration de la constante qui définit
    la taille maximale de la chaine que l'utilisateur
    pourra entrer.
*/
#define N 100

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
//////////// DECLARATION DES FONCTIONS UTILISEES ///////////
////////////////////////////////////////////////////////////

/*
    -> DECLARATION DE LA FONCTION @lire_utile(char* str) :
    @lire_utile() permet de lire convenablement la chaine
    entrèe par l'utilisateur caratère par caractère
    jusqu'à ce qu'il rencontre le caractère '='
    en reiterant toujours l'appel de @getchar().
*/
void lire_utile(char* str);




/*
    -> DECLARATION DE LA FONCTION @expression() :
    Cette fonction permet non seulement de reconnaitre une expression
    mais aussi de renvoyer sa valeur au cas echéan.
    C'est le point d'entré et de sortie de notre algorithme BNF.
    Du fait de la manière dont une expression est constituèe,
    on trouve en son sein l'appel des fonctions @terme(), @operateur_additif() et la fonction @expression() elle même.
*/
int expression();



/*
    -> DECLARATION DE LA FONCTION @terme() :
    Cette fonction permet non seulement de reconnaitre un terme
    mais aussi de renvoyer sa valeur au cas echéan.
    Elle est utilisée par la fonction @expression pour verifier
    (éventuellement evaluer) qu'un de ces membres est bien un terme.
    Du fait de la manière dont un terme est constituè,
    on trouve en son sein l'appel des fonctions @facteur(), @operateur_multiplicatif() et la fonction @terme() elle même.
*/
int terme();



/*
    -> DECLARATION DE LA FONCTION @facteur()
    Cette fonction permet non seulement de reconnaitre un facteur
    mais auusi de renvoyer sa valeur au cas echéan.
    Utilisé par la fonction @terme() pour verifier qu'il est bien constitué de facteur,
    cette fonction est principalement caracterisée de l'appel de la fonction @nombre() et @expression()
    pour verifier que nous sommes bien dans le cas d'une expression se trouvant entre parentese
    si la fonction @nombre() n'affirme pas le cas echean.
*/
int facteur();



/*
    -> DECLARATION DE LA FONCTION @nombre() :
    Cette fonction permet de verifier si un ensembre de caractère est bien un nombre
    et de renvoyer sa valeur au cas echéan.
    Elle est utilisée par la fonction @facteur() pour verifier
    qu'un facteur est bien un nombre.
    Cette fonction appel principalement la fonction @chiffre()
*/
int nombre();



/*
    -> DECLARATION DE LA FONCTION @chiffre() :
    Elle est utilisée pour verifier si effectivement nous avons un chiffre.
    Elle renvoie la @true si c'est cas et @false au cas non echéan.
    Elle est utilisée par la fonction @nombre() pour vérifier
    que ce dernier est bien constitué de chiffres.
    Elle se contante juste comparer la valeur de la variable @calu avec un ensemble de valeur
    et de revoyer @true s'il y a au mois une correspondance ou @false sinon
*/
int chiffre();




/*
    -> DECLARATION DE LA FONCTION @operateur_additif() :
    Cette fonction permet de verifier si un caractere est bien
    un operateur-additif (un '+' ou un '-').
    Elle renvoi le carractere correspondant si celui la est egale
    à l'un de ces deux operateur-additif ou la constante @INVALID_CHAR sinon.
    Elle est utilisée uniquement par la fonction @expression() pour verifier
    que ces differantes termes sont bien separés par un des operateur-additif
*/
char operateur_additif();




/*
    -> DECLARATION DE LA FONCTION @operateur_multiplicatif() :
    Cette fonction permet de verifier si un caractere est bien
    un operateur-multiplicatif (un '*' ou un '/').
    Elle renvoi le carractere correspondant si celui la est egale
    à l'un de ces deux operateur-multiplicatif ou la constante @INVALID_CHAR sinon.
    Elle est utilisée uniquement par la fonction @terme() pour verifier
    que ces differantes facteurs sont bien separés par un des operateur-multiplicatif
*/
char operateur_multiplicatif();


/*
    -> DECLARATION DE LA FONCTION @car_suivant() :
    Cette fonction permet tout simplement d'aller au caractere suivant
    de la chaine de l'expression que nous sommmes entrain d'analyser.
    Elle renvoie @true si l'avancé s'est bien passer ou @false sinon (si nous sommes à la fin de la chaine).
*/
int car_suivant();


/*
    -> DECLARATION DE LA FONCTION @fin_expression() :
    Cette fonction est utilisée pour savoir si nous sommes à la fin de l'expression.
    Elle revoie @true si c'est le cas ou @false sinon
*/
int fin_expression();



/*
    -> DECLARATION DE LA FONCTION @enlever_blanc() :
    Elle permet de sauter les espaces blancs jusqu'à ce qu'on trouve
    un caractère graphique ou qu'on atteigne la fin de la chaine.
    Elle utilise pricipalement la fonction @car_suivant().
    Elle n'a pas de valeur de retour.
*/
void enlever_blanc();



/*
    -> DECLARATION DE LA FONCTION @parentese_ouvrante() :
    Cette fonction permet de verifier si un caractere est bien
    une parentèse ouvrante.
    Elle revoie @true si c'est le cas ou @false sinon
    Elle est uniquement utilisée par la fonction @facteur()
    pour savoir si celui-ci ne commance pas par une parentèse ouvrante
    au cas où l'appel de la fonction nombre ne donne pas une valeur concluante.
*/
int parentese_ouvrante();



/*
    -> DECLARATION DE LA FONCTION @parentese_fermante() :
    Cette fonction permet de verifier si un caractere est bien
    une parentèse fermante.
    Elle revoie @true si c'est le cas ou @false sinon
    Elle est uniquement utilisée par la fonction @facteur()
    pour savoir si celui-ci se termine par une parentèse fermante
    au cas où elle a commencé par une parentèse ouvrante.
*/
int parentese_fermante();

////////////////////////////////////////////////////////////
//////////// DEFINITIONS DES VARIABLES GLOBALES ////////////
////////////////////////////////////////////////////////////


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


////////////////////////////////////////////////////////////
//////////////// DEFINITIONS DES FONCTIONS /////////////////
////////////////////////////////////////////////////////////


/*
    -> DEFINITION DE LA FONCTION @main() :
    Etant le point d'entrée de notre programme,
    c'est dans cette fonction que nous initialiserons
    tous les variables qui en ont besoin.
    Aussi c'est à partire de cette fonction que nous appelerons
    la fonction @lire_utile() qui se chargera de demander à l'utilisateur
    d'entrer la chaine puis de la lire convenablement.
    Enfin cette fonction se chargera aussi d'afficher le resultat du programme.
*/
int main()
{

    label : printf("Entrer l'expression!\n");
    taille = 0;
    strncpy(expression_arith, "", N);
    indice_calu = 0;
    arret = false;
    lire_utile(expression_arith);

    if(!strcmp(expression_arith, ".")) {
        printf("Au revoir...");
        exit(EXIT_SUCCESS);
    }

    int exp = expression();
    if(arret || indice_calu < taille) printf("arret : CECI N'EST PAS UNE EXPRESSION !!!!!!\n");
    else printf("CECI EST UNE EXPRESSION CORRECTE\n");
    printf("sa valeur est : %d\n",exp);
    printf("______________________________________\n");
    printf("expression_arith : %s\n",expression_arith);
    printf("taille : %d\n",taille);
    printf("calu : %c\n",calu);
    printf("indice_calu : %d\n",indice_calu);
    printf("______________________________________\n\n");
    goto label;
}


/*
    -> Definition de la fonction @lire_utile() :

*/
void lire_utile(char* str){
    char c;

    int i = 0;
    while(i<N){
        c = getchar();

        if(c == '='){
            getchar(); //Ce getchar() est juste pour eliminer le caractere "à la ligne ou retour chariot" que l'utilisateur a teper pour que je puisse faire le traitement
            break;
        }
        str[i] = c;
        i++;
    }
    taille = i;
    calu = str[0];
}


int expression(){
    enlever_blanc(); //a tester au cas ou ce truc present ne marche pas
    int val;
    val = terme();
    if(arret) return val;
    int val_retour_expression;
    enlever_blanc();
    char operation = operateur_additif();
    if(operation != INVALID_CHAR){
        if(car_suivant()){
            enlever_blanc();
            val_retour_expression = expression();
            if(arret){
                return val_retour_expression;
            }else{
                if(operation == ADD)
                    return val + val_retour_expression;
                else return val - val_retour_expression;
            }
        }else{
            arret = true;
            //return INVALID_EXP;
        }
    }else {
        if(taille == 1 && val == INVALID_INT) arret = true;  //Ceci gère le cas où nous avons un seul caractere mais que ce caractère ne soit pas valide
    }
    return val;
}


int terme(){

    int val = facteur(); //Nous appelons la fonction facteur qui se chage de verifier/retouner la valeur de facteur
    if(arret) return val; //Si nous n'avons pas de facteur alors on arrete tout et on retoune les valeurs appropiees sans affectuer les actions suivantes
    int val_retour_terme; //Variable permettant de contenir la valeur de retour de la fonction terme (i.e. l'appel recursif)
    enlever_blanc(); //Nous enlevons les caracteres blancs eventuels qui se trouvent avant l'operateur
    char operation = operateur_multiplicatif(); //Une fois que nous avon la valeur d'un facteur, nous varifions que le caractere suivant est un operateur
    if(operation != INVALID_CHAR){ //Si nous avons bien un operateur valide
        if(car_suivant()){ //alors on passe au caractere suivant
            enlever_blanc(); //Si nosu avons un caractere multiplicatif et que nous avons passé au caractere suivant, nous enlevons encore les caracteres blancs eventuels
            val_retour_terme = terme();  //Nous recuperons la valeur retounée par l'appel de la fonction recursive de terme() pour la mettre dans val_retour_terme
            if(arret){ //Avant de continuer nous verifions si val_retour_terme a une valeur incorrecte
                return val_retour_terme; //si c'est le cas on retoune la valeur appropriée
            }else { //Sinon on effectue le calcul necessaire en fonction de l'operation (multiplication ou division)
                if(operation == MULT)
                    return val*val_retour_terme;
                else return val/val_retour_terme;
            }
        }else{
            arret = true;
            //return INVALID_EXP; //l'operation multiplicatif est le dernier element de l'expression
        }
    }//Si nous avons la valeur d'un facteur et que le caractere suivant n'est pas un operateur multiplicatif alors on retourne simplement la valeur du facteur (voir en bas de la fonction)
    return val;

}


int facteur(){
    int val;
    val = nombre();

    if(val == INVALID_INT){ //Nous verifions si la veleur retourne par nombre n'est pas un nombre
        if(parentese_ouvrante()){ //si c'est le cas nous verifions aussi qu'il s'agit d'une parentese ouvrante
            //parentese_non_fermee++;
            if(car_suivant()){ //si c'est une parentese ouvrante on decale la valeur de calu
                enlever_blanc(); //On eleves les eventuelles espaces blancs qui se trouvent juste apres la parentese ouvrante
                val = expression(); //puis on verifie si le contenu des parenteses est bien une expression
                if(!arret){ //si le contenu est bien une expression alors la parentese doit eter bien fermée
                    if(parentese_fermante()){ //Si effectivement la parentese à ete fermée
                        car_suivant();  //alors nous passons au caractere suivant
                    }else{
                        arret = true; //Sinon c'est qu'il y a probleme et que l'expression est invalide
                        //return INVALID_EXP; //Sinon c'est qu'il y a probleme et que l'expression est invalide
                    }
                }
            }else{
                arret = true;
                //return INVALID_EXP; //si nous avons une parentese ouvrante juste avant la fin de l'expression cela veux tout siplement dire que l'expression n'est pas valide
            }
        }else arret = true; //A VERIFIER!!!!!!!!!!!!!!!
    }

    /*if(parentese_non_fermee > 0){
        if(parentese_fermante()){
            parentese_non_fermee--;
            car_suivant();
        }
    }*/

    return val;
}

int nombre(){
    int val, n;
    char str_calu[1]; //Nous definissons un string pour nous permettre de convertir calu en int (;car la convertion ne s'applique pas au char)
    if(chiffre()){ //On teste si la valeur courante de calu est un chiffre
        str_calu[0] = calu; //Affectation de la valeur de calu au string pour la convertion
        n = atoi(str_calu); //Convertion de str_calu i.e. calu
        bool suivant = car_suivant(); //si c'est un chiffre, on lit la valeur suivante de l'expression_arith
        if(suivant){ //si on est pas a la fin de l'expression_arith
            val = nombre(); //nous faisson un appel recursif de nombre
            if(val != INVALID_INT){ // et on verifie si la valeur est un nombre ou pas (i.e si c'est bien un chiffre)
                int puissance = 1;  //pour permettre d'avoir le nombre correspondant
                                    //en prenant en compte les valeures precedantes revoyées par nombre
                do{
                    puissance*=10;
                }while(puissance <= val);

                val = n*puissance + val;
                return val;
            } // si val == INVALID_INT pas grave nous avons un return plus bas qui se charge de retouner la bonne valeur
        } // si suivant == false pas grave nous avons un return plus bas qui se charge de retouner la bonne valeur
        return n;

    }else return INVALID_INT;


}

char operateur_additif(){
    if(calu == ADD) return ADD;
    else if(calu == MOINS) return MOINS;
    return INVALID_CHAR;
}

char operateur_multiplicatif(){
    if(calu == MULT) return MULT;
    else if(calu == DIV) return DIV;
    return INVALID_CHAR;
}

int chiffre(){
    if(calu == CHIFFRES[0] ||
       calu == CHIFFRES[1] ||
       calu == CHIFFRES[2] ||
       calu == CHIFFRES[3] ||
       calu == CHIFFRES[4] ||
       calu == CHIFFRES[5] ||
       calu == CHIFFRES[6] ||
       calu == CHIFFRES[7] ||
       calu == CHIFFRES[8] ||
       calu == CHIFFRES[9]   ) return true;
    return false;
}

int car_suivant(){
    if(indice_calu < taille){
        calu = expression_arith[++indice_calu];
        return true;
    }else return false;
}

int fin_expression(){
    if(indice_calu >= taille) return true;
    return false;
}
void enlever_blanc(){
    while(calu == BLANC_CHARS[0] ||
          calu == BLANC_CHARS[1] ||
          calu == BLANC_CHARS[2] ||
          calu == BLANC_CHARS[3] )
    {
        if(!fin_expression())
            car_suivant();
            else break;
    }
}

int parentese_ouvrante(){
    return calu == '(';
}

int parentese_fermante(){
    return calu == ')';
}
