
//Inclusion du fichier contenant la declaration des fonctions utilisées
#include "declarations_fonctions.h"

//Inclusion du fichier contenant les variables globales utilisées
#include "globals.h"





////////////////////////////////////////////////////////////
//////////////// DEFINITIONS DES FONCTIONS /////////////////
////////////////////////////////////////////////////////////



/*
    DEFINITION DE LA FONCTION @lire_utile() :
    - Cette fonction permet de reiterer l'appel de @getchar() jusqu'à ce qu'on optient
        un caractère '=' (qui marque la fin du saisi)
        ou que nous atteignons la taille limite du tableau.

*/
void lire_utile(char* str){
    char c;

    int i = 0;
    while(i<N){
        c = getchar();

        if(c == '='){
            getchar(); //Ce getchar() est juste pour eliminer le caractere "à la ligne ou retour chariot" que l'utilisateur a teper pour que nous puissions faire le traitement
            break;
        }
        str[i] = c;
        i++;
    }
    taille = i;
    calu = str[0];
}



/*
    DEFINITION DE LA FONCTION @expression :
    - Avant de commncer quoique ce soit d'autre on elève
        les éventuels blancs qui peuvent se trouver devant l'expression.
    - Ensuite on appel la fonction @terme() en stockant sa valeur de retour dans une variable @val.


    - Avant de continuer nous testons si nous devons arreter l'execution
        par biais de la variable @arret et si nous devons nous arreter,
        nous renvoyons tous simplement la valeur de @val sinon on continu l'execution.
    - En suite nous déclarons une variable @val_retour_expression permettant
        de contenir la valeur de retour de la fonction @expression() (i.e. l'appel recursif).
    - Nous enlovons les eventuelle espaces blancs qui peuvent se trouver devant l'operateur
        avant d'appeler la fonction @operateur_additif() pour verifier si nous avons bien
        un operateur additif.
        - Si nous avons bien un operateur additif alors nous passons au caractère suivant
            - Nous enlevons les éventuels espaces blancs se trouvant après le caractère additif
            - puis on verifie si le membre gauche de l'addition est bien une expression aussi
                en affectant sa valeur de retour à la variable @val_retour_expression.
            - Nous verifions ensuite avant de continuer si nous ne devons
                pas nous arreter en evaluant le contenu de @arret
                -Si nous devons nous arreter alors on renvoi la valeur de @val_retour_expression
                -Sinon Nous effectuons la l'addition avec l'operateur
                    aproprié en fonction de la valeur de operation.
        - Sinon (si nous n'avons pas un operateur additif)
            - On verifier qu'on ne se trouve pas dans le cas d'un seul caractère qui soit invalide.
            - Et si c'est le cas alors on arret l'execution en affectant à la variable @arret la valeur @true.
            - Sinon on retoune tout simplement la valeur de @val.
*/

int expression(){
    enlever_blanc();                            //nous enlevons les espaces blancs car meme si nous en avons ici, l'expression peut etre correcte
    int val;
    val = terme();                              // appel de la fonction terme
    if(arret) return val;
    int val_retour_expression;
    enlever_blanc();                            ////Nous enlevons les caracteres blancs eventuels qui se trouvent avant l'operateur
    char operation = operateur_additif();
    if(operation != INVALID_CHAR){
        if(car_suivant()){
            enlever_blanc();                    ////Nous enlevons les caracteres blancs eventuels qui se trouvent après l'operateur
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
        }
    }else {
        if(taille == 1 && val == INVALID_INT) arret = true;  //Ceci gère le cas où nous avons un seul caractere mais que ce caractère ne soit pas valide
    }
    return val;
}

/*
    DEFINITION DE LA FONCTION @terme() :
    - Dans cette fonction nous appelons d'abord la fonction @facteur()
        et stockons le resultat dans une variable @val.
    - Avant de continuer nous testons si nous devons arreter l'execution
        par biais de la variable @arret et si nous devons nous arreter,
        nous renvoyons tous simplement la valeur de @val sinon on continu l'execution.
    - En suite nous déclarons une variable @val_retour_terme permettant
        de contenir la valeur de retour de la fonction @terme() (i.e. l'appel recursif).
    - Nous enlovons les eventuelle espaces blancs qui peuvent se trouver devant l'operateur
        avant d'appeler la fonction @operateur_multiplicatif pour verifier si nous avons bien
        un operateur multiplicatif.
        - Si nous avons bien un operateur multiplicatif alors nous passons au caractère suivant
            - Nous enlevons les éventuels espaces blancs se trouvant après le caractère multiplicatif
            - puis on verifie si le membre gauche de la multiplication est bien un terme
                en affectant sa valeur de retour à la variable @val_retour_terme.
            - Nous verifions ensuite avant de continuer si nous ne devons
                pas nous arreter en evaluant le contenu de @arret
                -Si nous devons nous arreter alors on renvoi la valeur de @val_retour_terme
                -Sinon Nous effectuons la multiplication avec l'operateur
                    aproprié en fonction de la valeur de operation.
        - Sinon (si nous n'avons pas un operateur multiplicatif)
            on retoune tout simplement la valeur de @val.
*/
int terme(){
    //Nous appelons la fonction facteur qui se chage de verifier/retouner la valeur de facteur
    int val = facteur();
    //Si nous n'avons pas de facteur alors on arrete tout et on retoune les valeurs appropiees sans affectuer les actions suivantes
    if(arret) return val;
    //Variable permettant de contenir la valeur de retour de la fonction terme (i.e. l'appel recursif)
    int val_retour_terme;
    //Nous enlevons les caracteres blancs eventuels qui se trouvent avant l'operateur
    enlever_blanc();
    //Une fois que nous avon la valeur d'un facteur, nous varifions que le caractere suivant est un operateur
    char operation = operateur_multiplicatif();
    //Si nous avons bien un operateur valide
    if(operation != INVALID_CHAR){
        //alors on passe au caractere suivant
        if(car_suivant()){
            //Si nosu avons un caractere multiplicatif et que nous avons passé au caractere suivant, nous enlevons encore les caracteres blancs eventuels
            enlever_blanc();
            //Nous recuperons la valeur retounée par l'appel de la fonction recursive de terme() pour la mettre dans val_retour_terme
            val_retour_terme = terme();
            if(arret){ //Avant de continuer nous verifions si val_retour_terme a une valeur incorrecte
                return val_retour_terme; //si c'est le cas on retoune la valeur appropriée
            //Sinon on effectue le calcul necessaire en fonction de l'operation (multiplication ou division)
            }else {
                if(operation == MULT)
                    return val*val_retour_terme;
                else return val/val_retour_terme;
            }
        }else{
            arret = true;
        }
    }//Si nous avons la valeur d'un facteur et que le caractere suivant n'est pas un operateur multiplicatif alors on retourne simplement la valeur du facteur (voir en bas de la fonction)
    return val;
}


/*
    DEFINITION DE LA FONCTION @facteur() :
    - Dans cette fonction nous appellons d'abord la fonction @nombre()
        stockons sa valeur de retour dans une variable @val.
    - Nous vérifions si @val est entier.
    - Si @val n'est pas un nombre valide alors
        - nous verifions si c'est parce que nous avons une parentèse ouvrante
        - Si nous avons avons une eparentèse ouvrante alors
            - Nous verifions si ce qui s'y trouve est une expression
                en affectant la valeur de retour à @val.
            - Avant de continuer nous testons si l'expression peut toujour etre correcte.
            - Si elle peut toujours etre correcte alors
            - On verifie si la parentèse precedement ouverte a été fermée.
            - Si elle a été fermé,on passe au caractère suivant
            - Sinon nous arretons l'analyse.
        - Sinon On affecte à @arret true pour terminer l'analyse
            car facteur dois forcement etre un nombre
            ou une expresession entre parentèse.
    - Sinon on retourne la valeur de @val.
*/
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
        }else arret = true; //Un facteur doit etre soit un nombre ou une expression entre parentèse. Donc si ce n'est ni l'un, ni l'autre nous pouvons affirmer que l'expression est donc erronée
    }

    return val;
}

/*
    DEINITION DE LA FONCTION @nombre :
    - Dans cette fonction nous definisson d'abord
    - @val qui contiendra la valeur du nombre en question,
    - @n qui contiendra les differentes chiffres revoyés par la fonction chiffre,
    - et @str_calu  qui est une chaine de caractère qui sera utilisée
        juste pour pouvoir convertir @calu en entier au cas ou il s'agit d'un chiffre.
    - Nous testons ensuite la valeur de retour de la fonction chiffre en l'appellant.
        pour savoir si la valeur courante de calu est bien un chiffre.
    - Si c'est le cas, alors
        - On converti @calu en entier puis on passe au caractère suivant;
        - Si nous sommes à la fin de la chaine alors on retourne la valeur du chiffre @n
        - Sinon on appelle encore nombre en stockant sa valeur de retour dans @val.
        - Ensuite on verifie si la valeur de @val est bien un nombre un nombre valide;
        - Si c'est la cas alors nous placons n au debut du nombre
            par le biais d'une boucle while avec des puissanecs de 10.
    - Sinon nous renvoyons la valeur @INVALID_INT pour dire que ceci n'est pas un nombre
*/
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


/*
    - DEFINITION DE FONCTION @operateur_additif()
*/
char operateur_additif(){
    if(calu == ADD) return ADD;
    else if(calu == MOINS) return MOINS;
    return INVALID_CHAR;
}


/*
    - DEFINITION DE FONCTION @operateur_multiplicatif()
*/
char operateur_multiplicatif(){
    if(calu == MULT) return MULT;
    else if(calu == DIV) return DIV;
    return INVALID_CHAR;
}


/*
    - DEFINITION DE FONCTION @chiffre()
*/
bool chiffre(){
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


/*
    - DEFINITION DE FONCTION @car_suivant()
*/
bool car_suivant(){
    if(indice_calu < taille){
        calu = expression_arith[++indice_calu];
        return true;
    }else return false;
}


/*
    - DEFINITION DE FONCTION @fin_expression()
*/
bool fin_expression(){
    if(indice_calu >= taille) return true;
    return false;
}


/*
    - DEFINITION DE FONCTION @enlever_blanc()
*/
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


/*
    - DEFINITION DE FONCTION @parentese_ouvrante()
*/
bool parentese_ouvrante(){
    return calu == '(';
}


/*
    - DEFINITION DE FONCTION @parentese_fermante()
*/
bool parentese_fermante(){
    return calu == ')';
}

