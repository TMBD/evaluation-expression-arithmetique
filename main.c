#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 100

int expression();
int terme();
int facteur();
int nombre();
int chiffre();
char operateur_additif();
char operateur_multiplicatif();
int car_suivant();
int fin_expression();
void enlever_blanc();
int parentese_ouvrante();
int parentese_fermante();


const char  CHIFFRES[10] = {'0','1','2','3','4','5','6','7','8','9'},
            ADD = '+',
            MOINS = '-',

            MULT = '*',
            DIV = '/',

            INVALID_CHAR = 'x',
            BLANC_CHARS[4] = {9, 10, 13, 32};
const int INVALID_INT = -1, INVALID_EXP = -5;
char expression_arith[N] = "", calu;
int taille = 0, indice_calu = 0;
bool arret = false;
//int parentese_non_fermee = 0;


int main()
{
    printf("Entrer l'expression!\n");
    lire_utile(expression_arith);
    //printf("expression_arith : %s\n",expression_arith);


    //TEST DE LA FONCTION NOMBRE()
    /*int nb = nombre();
    if(nb == INVALID_INT) printf("CECI N'EST PAS UN NOMBRE !!!!!!\n");
    printf("______________________________________\n");
    printf("nombre : %d\n",nb);
    printf("calu : %c\n",calu);
    printf("indice_calu : %d\n",indice_calu);
    printf("______________________________________\n\n");
    */

    //TESTE DE LA FONCTION FACTEUR
    /*int fact = facteur();

    if(fact == INVALID_INT) printf("CECI N'EST PAS UN FACTEUR !!!!!!\n");
    else if(fact == INVALID_EXP) printf("CECI N'EST PAS UNE EXPRESSION\n");
    else printf("CECI EST UN FACTEUR\n");
    printf("______________________________________\n");
    printf("facteur : %d\n",fact);
    printf("calu : %c\n",calu);
    printf("indice_calu : %d\n",indice_calu);
    printf("______________________________________\n\n");
    */

    //TEST DE LA FONCTION TERME
    /*int t = terme();

    if(t == INVALID_INT) printf("CECI N'EST PAS UN TERME !!!!!!\n");
    else if(t == INVALID_EXP) printf("CECI N'EST PAS UNE EXPRESSION\n");
    else printf("CECI EST UN TERME\n");
    printf("______________________________________\n");
    printf("terme = %d\n",t);
    printf("calu : %c\n",calu);
    printf("indice_calu : %d\n",indice_calu);
    printf("______________________________________\n\n");
    */

    //TEST DE LA FONCTION EXPRESSION

    int exp = expression();
    if(arret || indice_calu < taille) printf("arret : CECI N'EST PAS UNE EXPRESSION !!!!!!\n");
    //if(exp == INVALID_INT) printf("INVALID_INT...\n");
    //else if(exp == INVALID_EXP) printf("INVALID_EXP...\n");
    else printf("CECI EST UNE EXPRESSION CORRECTE\n");
    printf("______________________________________\n");
    printf("expression = %d\n",exp);
    printf("calu : %c\n",calu);
    printf("indice_calu : %d\n",indice_calu);
    printf("______________________________________\n\n");
}


void lire_utile(char* str){
    char c;

    int i = 0;
    while(true){
        c = getchar();

        if(c == '=') break;

        str[i] = c;
        i++;
    }
    taille = i-1;
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
        }
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
