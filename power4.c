#include <stdio.h>
#include <stdlib.h>
#define LIGNES    6
#define COLS    7
#define FOUR    4

char scores[LIGNES][COLS];
char header[] = "  A   B   C   D   E   F   G  ";
char horbar[] = "|---|---|---|---|---|---|---|";
int bin = 0;
char disc = 'X';


void afficher();
void init_scores();
void test_scores();
void board();
void choose();
void fill_bin();

int check(char disc);

/* fonction main *************************************************************/

int main()
{

    int choice;
    afficher();
    scanf("%1d",&choice);



    switch(choice)
    {

    case 1 :

        init_scores();
        test_scores();
        board();


        while (1)
        {
            printf("Joueur %c, c'est votre tour!\n", disc);
            choose();
            printf("\n\n");
            board();
            if (check('X'))
            {
                printf("\n\nJoueur X a gagne !!\n\n");
                break;
            }
            if (check('O'))
            {
                printf("\n\nJoueur O a gagne!\n\n");
                break;
            }
        }



    case 2 :

        printf("PARTIE TESTEN COURS DE CONSTRUCTION !");
        break;
    case 3:
        printf("MERCI ET AU REVOIR !");
        break;

 default:
 printf("\nFAUX NUMERO REESSAIE\n\n");

 break;
    }




    return 0;
}

/* fonctions d'assistance **********************************************************/


void afficher()
{
    printf("BIENVENUE DANS LE JEU PUISSANCE 4 \n");
    printf("\n");
    printf("Choisissez une option :  \n");
    printf(" 1) JOUER \n");
    printf(" 2) MODE TEST \n");
    printf(" 3) QUITTER \n");



}


void init_scores()
{
    // initialiser le tableau:
    int i, j;

    for (i = 0; i < LIGNES; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            scores[i][j] = ' ';
        }
    }
}

void test_scores()
{

    int i, j;

    for (i = 0; i < LIGNES; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%c ", scores[i][j]);
        }
        printf("\n");
    }
}

void board()
{
    // imprimer le tableau et les scores selon le jeu en cours
    printf("%s\n", header);
    printf("%s\n", horbar);

    int i, j;

    for (i = 0; i < LIGNES; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("| %c ", scores[i][j]);
        }
        printf("|\n");
        printf("%s\n", horbar);
    }
}

void choose()
{
    // choisir A B C D E F G:
    char c;

    while (1)
    {
        printf("\n Choisissez un numero de colonne : ");
        scanf(" %c", &c);
        switch(c)
        {
        case 'A':
        case 'a':
            bin = 0;
            break;
        case 'B':
        case 'b':
            bin = 1;
            break;
        case 'C':
        case 'c':
            bin = 2;
            break;
        case 'D':
        case 'd':
            bin = 3;
            break;
        case 'E':
        case 'e':
            bin = 4;
            break;
        case 'F':
        case 'f':
            bin = 5;
            break;
        case 'G':
        case 'g':
            bin = 6;
            break;
        default:
            bin = 666;
            printf("\nFAUSSE LETTRE REESSAIE\n\n");
            board();
        }
        // sortir de la boucle si la bonne lettre a été choisie:
        if ((bin >= 0 && bin <= 6) && (scores[0][bin] == ' '))
        {
            fill_bin();
            disc = (disc == 'X') ? 'O' : 'X';
            break;
        }
    }
}

void fill_bin()
{
    // remplit le tableau en fonction de ce qui s'y trouve déjà :
    int level ;     /* niveau le plus bas ou bas du tableau */

    for (level = LIGNES-1; level >= 0; level--)
    {
        if (scores[level][bin] == ' ')
        {
            scores[level][bin] = disc;
            break;
        }
    }
}

int check(char disc)
{
    // recherche une rangée, une colonne ou une diagonale de 4 disques :


     /* vérifie les rangées de 4 disques
     chaque rangée a 4 façons différentes de connecter 4

    | X | X | X | X |   |   |   |
    |   | X | X | X | X |   |   |
    |   |   | X | X | X | X |   |
    |   |   |   | X | X | X | X |

     */

    int i, j, k;
    int count;
    int ways = 4;

    for (i = 0; i < LIGNES; ++i)
    {
        for (j = 0; j < ways; ++j)
        {
            count = 0;
            for (k = 0; k < FOUR; ++k)
            {
                if (scores[i][j + k] == disc) count++;
            }
            if (count == FOUR) return 1;
        }
    }


    /* vérifier les colonnes
     chaque colonne a 3 façons différentes de connecter 4

    | X |   |   |
    | X | X |   |
    | X | X | X |
    | X | X | X |
    |   | X | X |
    |   |   | X |

    */

    ways = 3;

    for (j = 0; j < COLS; ++j)
    {
        for (i = 0; i < ways; ++i)
        {
            count = 0;
            for (k = 0; k < FOUR; ++k)
            {
                if (scores[i + k][j] == disc) count++;
            }
            if (count == FOUR) return 1;
        }
    }

    /* vérifier les diagonales

      A B C D E F G
    0| | | | | | | |
    1| |\|\|\|\|\| |
    2| |\|\|\|\|\| |
    3| |\|\|\|\|\| |
    4| |\|\|\|\|\| |
    5| | | | | | | |

    */

    int ii, jj;
    for (i = 1; i < LIGNES-1; i++)
    {
        for (j = 1; j < COLS-1; j++)
        {

            /* diagonales inclinées vers la gauche */
            count = 0;
            // gauche-haut :
            for (ii = i, jj = j; (ii >= 0) || (jj >= 0); ii--, jj--)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;
                }
                else
                    break;
            }
            // vers la droite vers le bas :
            for (ii = i+1, jj = j+1; (ii <= LIGNES-1) || (jj <= COLS-1); ii++, jj++)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;
                }
                else
                    break;
            }

            /* diagonales inclinées vers la droite */
            count = 0;
            // gauche-bas :
            for (ii = i, jj = j; (ii <= LIGNES-1) || (jj >= 0); ii++, jj--)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;
                }
                else
                    break;
            }
            // vers la droite vers le haut :
            for (ii = i-1, jj = j+1; (ii >= 0) || (jj <= COLS-1); ii--, j++)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;
                }
                else
                    break;
            }

        }
    }

    return 0;
}



