  /**--------------------------------------------------------**/
  /**       C o n v e r s i o n   Z vers C (Standard)        **/
  /**             Realisee par Pr D.E ZEGOUR                 **/
  /**             E S I - Alger                              **/
  /**             Copywrite 2014                             **/
  /**--------------------------------------------------------**/

  /*****************DDDDDDDDDDEBUT TP Z*********************/

   
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>

  typedef int bool ;
  typedef char * string255 ;
  typedef char * string2 ;

  #define True 1
  #define False 0

  /** Implementation **\: FICHIER **/

  /* Traitement des fichiers ouverts */

  struct _Noeud
    {
      FILE * Var_fich ;
      char * Nom_fich ;
      int Sauv_pos;
      struct _Noeud *Suiv ;
    } ;

  typedef struct _Noeud * _Ptr_Noeud;

  _Ptr_Noeud  _Pile_ouverts  = NULL;

  /* Teste si un fichier est ouvert */
  _Ptr_Noeud _Ouvert ( char * Fp)
    {
      _Ptr_Noeud P;
      bool Trouv ;
      P = _Pile_ouverts; Trouv = False ;
      while ((P != NULL) && ! Trouv )
        if ( strcmp(P->Nom_fich, Fp) == 0)
        Trouv = True;
        else P = P->Suiv;
      return P;
    }

  /* Ajouter un fichier ouvert */
  void _Empiler_ouvert ( char *Fp, FILE *Fl)
    {
      _Ptr_Noeud  P ;
      P = (_Ptr_Noeud) malloc( sizeof( struct _Noeud)) ;
      P->Nom_fich = Fp;
      P->Var_fich = Fl;
      P->Suiv = _Pile_ouverts;
      _Pile_ouverts = P;
    }

  /* Supprimer un fichier ouvert et rendre son nom*/
  char * _Depiler_ouvert ( FILE *Fl)
    {
      char * Fp = malloc (100);
      _Ptr_Noeud P,  Prec  ;
      P= _Pile_ouverts;
      Prec = NULL;
      while (P->Var_fich != Fl )
        { Prec = P ; P = P->Suiv ;}
      strcpy(Fp, P->Nom_fich);
      if (Prec != NULL)
        Prec->Suiv = P->Suiv;
      else _Pile_ouverts = P->Suiv;
      free (P);
      return Fp ;
    }


  /** Fichiers **/

  typedef char _Tx[255];
  /** Types des champs du bloc **/
  typedef string255 Typechamp1_s;
  typedef _Tx Typechamp1_s_Buf ;

  /** Type du bloc de donnees du fichier **/
  typedef struct
    {
      Typechamp1_s_Buf Champ1 ;
    }  Typestruct1_s_Buf;

  /** Type de la structure du bloc de donnees du fichier **/
  typedef struct
    {
      Typechamp1_s Champ1 ;
    }  Typestruct1_s_;

  typedef Typestruct1_s_  * Typestruct1_s ;

  typedef Typestruct1_s Typestr_Ts;
  typedef Typestruct1_s_ Type_Ts;


  Typechamp1_s Struct1_Ts ( Typestruct1_s Buf )
    {
      return Buf->Champ1;
    }

  /** Manipulation de la structure **/
  void Aff_struct1_Ts ( Typestruct1_s Buf, Typechamp1_s Val )
    {
     strcpy( Buf->Champ1 , Val );
    }

  /** Machine abstaite sur les fichiers **/

  void Ouvrir_s ( FILE **s , char *Fp , char * Mode )
    {
      _Ptr_Noeud P = _Ouvert(Fp);
      if ( P != NULL )
      /* Le fichier est deja ouvert */
        {
         P->Sauv_pos = ftell (P->Var_fich);
         fclose(P->Var_fich);
        }
      /* Le fichier est non ouvert */
      if ( strcmp(Mode,"A") == 0)
        *s = fopen(Fp, "r+b");
      else
        *s = fopen(Fp, "w+b");
      _Empiler_ouvert( Fp, *s);
    }

  void Fermer_s ( FILE * s )
    {
      char * Fp = malloc(100);
      _Ptr_Noeud P;
      strcpy(Fp, _Depiler_ouvert(s));
      fclose(s) ;
      /* Ya-til un fichier ouvert avec le m?me nom ?  */
      /* Si Oui, le Reouvrir a la position sauvegardee */
      P =  _Ouvert (Fp);
      if ( P != NULL)
      {
        s = fopen(P->Nom_fich, "r+b");
        fseek(s, P->Sauv_pos, 0);
      }
    }

  void Ecrireseq_s ( FILE * s, Typestruct1_s Buf  )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      for(J=0; J<= strlen(Buf->Champ1); ++J)
        Buffer.Champ1[J] = Buf->Champ1[J];
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Ecriredir_s ( FILE * s, Typestruct1_s Buf, int N )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      for(J=0; J<= strlen(Buf->Champ1); ++J)
        Buffer.Champ1[J] = Buf->Champ1[J];
      fseek(s, (long) (N-1)* sizeof(  Typestruct1_s_Buf), 0);
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Lireseq_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      if (fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s) != 0) {
      for(J=0; J<= strlen(Buffer.Champ1); ++J)
        Buf->Champ1[J] = Buffer.Champ1[J];
      }
    }

  void Liredir_s ( FILE * s, Typestruct1_s Buf, int N)
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      fseek(s, (long) (N-1)* sizeof( Typestruct1_s_Buf), 0 );
      fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s);
      for(J=0; J<= strlen(Buffer.Champ1); ++J)
        Buf->Champ1[J] = Buffer.Champ1[J];
    }

  void Rajouter_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      for(J=0; J<= strlen(Buf->Champ1); ++J)
        Buffer.Champ1[J] = Buf->Champ1[J];
      fseek(s, 0, 2); /* Fin du fichier */
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  bool Finfich_s (FILE * s)
    {
      long K = ftell(s);
      fseek(s, 0, 2); /* Fin du fichier */
      long K2 = ftell(s);   /* position a partir du debut */
      if  (K==K2)
        { fseek(s, K, 0); return 1;}
      else
        { fseek(s, K, 0); return 0;}
    }

  int Alloc_bloc_s (FILE * s)
    {
      long K;
      fseek(s, 0, 2); /* Fin du fichier */
      K = ftell(s);   /* position a partir du debut */
      K = K / sizeof (Typestruct1_s_Buf);
      K ++;
      return(K);
    }


  /** Implementation **\: ARBRE BINAIRE DE CHAINES DE CARACTERES**/

  /** Arbres de recherche binaire **/

  typedef string255 Typeelem_As   ;
  typedef struct Noeud_As * Pointeur_As ;

  struct Noeud_As
    {
      Typeelem_As  Val ;
      Pointeur_As Fg ;
      Pointeur_As Fd ;
      Pointeur_As Pere ;
     } ;

  Typeelem_As Info_As( Pointeur_As P )
    { return P->Val;   }

  Pointeur_As Fg_As( Pointeur_As P)
    { return P->Fg ; }

  Pointeur_As Fd_As( Pointeur_As P)
    { return P->Fd ; }

  Pointeur_As Pere_As( Pointeur_As P)
    { return P->Pere ; }

  void Aff_info_As ( Pointeur_As P, Typeelem_As Val)
    {
       strcpy( P->Val , Val );
    }

  void Aff_fg_As( Pointeur_As P, Pointeur_As Q)
    { P->Fg =  Q;  }

  void Aff_fd_As( Pointeur_As P, Pointeur_As Q)
    { P->Fd =  Q ; }

  void Aff_pere_As( Pointeur_As P, Pointeur_As Q)
    { P->Pere =  Q ; }

  void Creernoeud_As( Pointeur_As *P)
    {
      *P = (struct Noeud_As *) malloc( sizeof( struct Noeud_As))   ;
      (*P)->Val = malloc(255 * sizeof(string255));
      (*P)->Fg = NULL;
      (*P)->Fd = NULL;
      (*P)->Pere = NULL;
    }

  void Liberernoeud_As( Pointeur_As P)
    { free( P ) ; }


  /** Implementation **\: FILE DE ENTIERS**/
  /** Files d'attente **/

  typedef int Typeelem_Fi ;
  typedef  struct Filedattente_Fi * Pointeur_Fi ;
  typedef  struct Maillon_Fi * Ptliste_Fi ;

  struct Maillon_Fi
    {
      Typeelem_Fi Val ;
      Ptliste_Fi Suiv  ;
    };

  struct Filedattente_Fi
    {
      Ptliste_Fi Tete, Queue ;
    };

  void Creerfile_Fi ( Pointeur_Fi *Fil   )
    {
      *Fil = (struct Filedattente_Fi *) malloc( sizeof( struct Filedattente_Fi)) ;
      (*Fil)->Tete = NULL ;
      (*Fil)->Queue = NULL ;
    }

  bool Filevide_Fi (Pointeur_Fi Fil  )
    { return  Fil->Tete == NULL ;}

  void Enfiler_Fi ( Pointeur_Fi Fil , Typeelem_Fi Val   )
    {
      Ptliste_Fi Q;

      Q = (struct Maillon_Fi *) malloc( sizeof( struct Maillon_Fi))   ;
      Q->Val = Val ;
      Q->Suiv = NULL;
      if ( ! Filevide_Fi(Fil) )
        Fil->Queue->Suiv = Q ;
      else Fil->Tete = Q;
        Fil->Queue = Q;
    }

  void Defiler_Fi (Pointeur_Fi Fil, Typeelem_Fi *Val )
    {
      if (! Filevide_Fi(Fil) )
        {
          *Val = Fil->Tete->Val ;
          Fil->Tete =  Fil->Tete->Suiv;
        }
      else printf ("%s \n", "File d'attente vide");
    }


  /** Implementation **\: FILE DE ARBRES BINAIRES DE CHAINES DE CARACTERES**/
  /** Files d'attente **/

  typedef Pointeur_As Typeelem_FAs ;
  typedef  struct Filedattente_FAs * Pointeur_FAs ;
  typedef  struct Maillon_FAs * Ptliste_FAs ;

  struct Maillon_FAs
    {
      Typeelem_FAs Val ;
      Ptliste_FAs Suiv  ;
    };

  struct Filedattente_FAs
    {
      Ptliste_FAs Tete, Queue ;
    };

  void Creerfile_FAs ( Pointeur_FAs *Fil   )
    {
      *Fil = (struct Filedattente_FAs *) malloc( sizeof( struct Filedattente_FAs)) ;
      (*Fil)->Tete = NULL ;
      (*Fil)->Queue = NULL ;
    }

  bool Filevide_FAs (Pointeur_FAs Fil  )
    { return  Fil->Tete == NULL ;}

  void Enfiler_FAs ( Pointeur_FAs Fil , Typeelem_FAs Val   )
    {
      Ptliste_FAs Q;

      Q = (struct Maillon_FAs *) malloc( sizeof( struct Maillon_FAs))   ;
      Q->Val = Val ;
      Q->Suiv = NULL;
      if ( ! Filevide_FAs(Fil) )
        Fil->Queue->Suiv = Q ;
      else Fil->Tete = Q;
        Fil->Queue = Q;
    }

  void Defiler_FAs (Pointeur_FAs Fil, Typeelem_FAs *Val )
    {
      if (! Filevide_FAs(Fil) )
        {
          *Val = Fil->Tete->Val ;
          Fil->Tete =  Fil->Tete->Suiv;
        }
      else printf ("%s \n", "File d'attente vide");
    }

  /** Variables du programme principal **/
  FILE *F;
  Typestruct1_s S ;
  Pointeur_As Bst1=NULL;
  Pointeur_As Bst2=NULL;
  Pointeur_As Bst3=NULL;
  Pointeur_As Bst0=NULL;

  string2 X;
  string2 Y;
  string2 Z;
  int N;

  /** Fonctions standards **/

  int Aleanombre( int N )
    { return ( rand() % N ); }

  char  *Aleachaine ( int N )
    {
      int k;
      char  * Chaine = malloc(N+1);

      char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
      char Chr2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      for (k=0;k<N; k++)
        switch ( rand() % 2 ){
        case 0 :  *(Chaine+k) = Chr1[rand() % 26] ; break ;
        case 1 :  *(Chaine+k) = Chr2[rand() % 26] ; break ;
        }
      Chaine[k] =  '\0' ;

      return (Chaine);
    }

  char *Caract ( string255 Ch , int I )
    {
      char *s = malloc(2);
      s[0] = Ch[I-1];
      s[1] = '\0';
      return  s;
    }

  int Max (int a, int b)
    {
      if (a > b) return(a);
      else return(b);
    }


  /** Initialisation d'une structure **/
  void Init_struct_Ts ( Typestr_Ts S, Type_Ts S_ )
    {
      S->Champ1 = S_.Champ1 ;
    }


  /** Prototypes des fonctions **/

  void Menu (int N , Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z);
  void Generer_fichier (int Num);
  void Ecrire_fichier();
  void Insert_bst1 (Pointeur_As *Root , string2 *X , string2 *Y , string2 *Z);
  void Insert (Pointeur_As *Root , Pointeur_As *To_insert);
  void Retation (Pointeur_As *To_insert);
  void Insert_bst3 (Pointeur_As *Root , string2 *X , string2 *Y , string2 *Z);
  int  Depth_node (Pointeur_As *To_insert) ;
  void Insert_bst2 (Pointeur_As *Root , string2 *X , string2 *Y , string2 *Z);
  int  Conter_mot (Pointeur_As *Root , string2 *X , string2 *Y , string2 *Z) ;
  int  Depth (Pointeur_As *Root) ;
  void Inorder (Pointeur_As *Root);
  void Compter_niveau (Pointeur_As *Root , string2 *X , string2 *Y , string2 *Z);
  bool  Search_bst1 (Pointeur_As *Root , string255 *Ch , string2 *X , string2 *Y , string2 *Z,int *h) ;
  bool  Search_bst2 (Pointeur_As *Root , string255 *Ch , string2 *X , string2 *Y , string2 *Z,int *h) ;
  bool  Search_bst3 (Pointeur_As *Root , string255 *Ch , string2 *X , string2 *Y , string2 *Z,int *h) ;
  bool  Search (string255 *Word , Pointeur_As *Root1 , Pointeur_As *Root2 , Pointeur_As *Root3 , string2 *X , string2 *Y , string2 *Z,int *h) ;
  void Search_range (string255 *Word1 , string255 *Word2 , Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3,string2 *X , string2 *Y , string2 *Z);
  void Range_bst1 (Pointeur_As *Root , string255 *Word1 , string255 *Word2,string2 *X , string2 *Y , string2 *Z);
  void Range_bst3 (Pointeur_As *Root , string255 *Word1 , string255 *Word2,string2 *X , string2 *Y , string2 *Z);
  void Range_bst2 (Pointeur_As *Root , string255 *Word1 , string255 *Word2,string2 *X , string2 *Y , string2 *Z);
  bool  Search_bst0(Pointeur_As *Root , string255 *Ch , string2 *X , string2 *Y , string2 *Z,int *h);
  void Insert_bst0 (Pointeur_As *Root );
  void simulatio_search();
  void simulatio_range();
  void Search_range_s (string255 *Word1 , string255 *Word2 , Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3,int *h,string2 *X , string2 *Y , string2 *Z);
  void Range_bst1_s (Pointeur_As *Root , string255 *Word1 , string255 *Word2,int *h,string2 *X , string2 *Y , string2 *Z);
  void Range_bst2_s (Pointeur_As *Root , string255 *Word1 , string255 *Word2,int *h,string2 *X , string2 *Y , string2 *Z);
  void Range_bst3_s (Pointeur_As *Root , string255 *Word1 , string255 *Word2,int *h,string2 *X , string2 *Y , string2 *Z);
  void Range_bst0 (Pointeur_As *Root , string255 *Word1 , string255 *Word2,int *h);
   void Range_bst2_s2 (Pointeur_As *Root , string255 *Word1 , string255 *Word2,int *h,string2 *X , string2 *Y , string2 *Z);
  string255 word;
  string255 word1;
  string255 word2;




  /**************************************************************/
  /**************        MENU          ***************/
  /**************************************************************/
  void Menu (int N , Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      int Choix;
      string255 _Px1;
      string255 _Px2;
      string255 _Px3;
      string255 _Px4;
      string255 _Px5;
      string255 _Px6;
      string255 _Px7;
      string255 _Px8;
      string255 _Px9;
      int u;
      int sum;
      /** Corps du module **/
     _Px1 = malloc(255 * sizeof(char));
     _Px2 = malloc(255 * sizeof(char));
     _Px3 = malloc(255 * sizeof(char));
     _Px4 = malloc(255 * sizeof(char));
     _Px5 = malloc(255 * sizeof(char));
     _Px6 = malloc(255 * sizeof(char));
     _Px7 = malloc(255 * sizeof(char));
     _Px8 = malloc(255 * sizeof(char));
     _Px9 = malloc(255 * sizeof(char));
     Choix  =  - 1 ;
     while( Choix != 12) {
      system("cls"); // Effacer l'ecran a chaque affichage du menu
    printf("\n+-------------------------------------------------------+");
    printf("\n|                  \033[1;36mMENU PRINCIPAL\033[0m                       |");
    printf("\n+-------------------------------------------------------+");
    printf("\n|  1. Generer fichier                                   |");
    printf("\n|  2. Afficher le fichier                               |");
    printf("\n|  3. Creer les arbres                                  |");
    printf("\n|  4. Nombre des mots X/Y/Z                             |");
    printf("\n|  5. Profondeur des arbres (Depth)                     |");
    printf("\n|  6. Parcours Inorder (Inorder Traversal)              |");
    printf("\n|  7. Compte par niveau                                 |");
    printf("\n|  8. Recherche un mot (One Word Search)                |");
    printf("\n|  9. Recherche par plage (Range Search)                |");
    printf("\n| 10. Simulations (One Word)                            |");
    printf("\n| 11. Simulations (Range)                               |");
    printf("\n| 12. \033[1;31mQuitter\033[0m                                           |");
    printf("\n+-------------------------------------------------------+");
    printf("\n Entrez votre choix (1-12) : ");
       scanf ( " %d", &Choix ) ;

       system("cls");  // Effacer l'écran 

       if( Choix == 1) {
         Generer_fichier ( N ) ;
         printf("\n\033[1;32m---------------------------------\033[0m");
         printf("\n\033[1;32m|   FILE CREATED SUCCESSFULLY   |\033[0m");
         printf("\n\033[1;32m---------------------------------\033[0m");
         }
       else
         {
         if( Choix == 2) {
           Ecrire_fichier() ;
           }
         else
           {
           if( Choix == 3) {
             Insert_bst1 ( & *Bst1 , & *X , & *Y , & *Z ) ;
             Insert_bst2 ( & *Bst2 , & *X , & *Y , & *Z ) ;
             Insert_bst3 ( & *Bst3 , & *X , & *Y , & *Z ) ;
             printf("\n\033[1;32m-------------------------------------\033[0m");
             printf("\n\033[1;32m|   TREES BST1, BST2, BST3 CREATED  |\033[0m");
             printf("\n\033[1;32m|         \033[1;35mSUCCESSFULLY!\033[1;32m             |\033[0m");
             printf("\n\033[1;32m-------------------------------------\033[0m");
             }
           else
             {
             if( Choix == 4) {
              printf("\n\033[1;36m+-------------------------------+\033[0m");
              printf("\n\033[1;36m|\033[1;35m   WORDS STARTING WITH X/Y/Z   \033[1;36m|\033[0m");
              printf("\n\033[1;36m+-------------------------------+\033[0m");
              printf("\n\033[1;36m|\033[0m \033[1;33m   BST1\033[0m: %-6d               \033[1;36m|\033[0m", Conter_mot(&*Bst1, &*X, &*Y, &*Z));
              printf("\n\033[1;36m|\033[0m \033[1;33m   BST2\033[0m: %-6d               \033[1;36m|\033[0m", Conter_mot(&*Bst2, &*X, &*Y, &*Z));
              printf("\n\033[1;36m|\033[0m \033[1;33m   BST3\033[0m: %-6d               \033[1;36m|\033[0m", Conter_mot(&*Bst3, &*X, &*Y, &*Z));
              printf("\n\033[1;36m+-------------------------------+\033[0m");
               }
             else
               {
               if( Choix == 5) {
                  printf("\n\033[1;36m+---------------------+\033[0m");
                  printf("\n\033[1;36m|\033[1;35m      BST DEPTHS     \033[1;36m|\033[0m");
                  printf("\n\033[1;36m+---------------------+\033[0m");
                  printf("\n\033[1;36m|\033[0m \033[1;33m  BST1\033[0m: %-6d      \033[1;36m|\033[0m", Depth(&*Bst1));
                  printf("\n\033[1;36m|\033[0m \033[1;33m  BST2\033[0m: %-6d      \033[1;36m|\033[0m", Depth(&*Bst2));
                  printf("\n\033[1;36m|\033[0m \033[1;33m  BST3\033[0m: %-6d      \033[1;36m|\033[0m", Depth(&*Bst3));
                  printf("\n\033[1;36m+---------------------+\033[0m");
                 }
               else
                 {
                 if( Choix == 6) {
                  printf("\n\033[1;36m+-------------------------------------+\033[0m");
                  printf("\n\033[1;36m|\033[1;35m        INORDER TRAVERSAL        \033[1;36m|\033[0m");
                  printf("\n\033[1;36m+-------------------------------------+\033[0m");
                  printf("\n\033[1;36m|\033[0m \033[1;33mBST1\033[0m: ");
                  Inorder(&*Bst1); 
                  printf("\033[1;36m               |\033[0m");  
                  printf("\n\033[1;36m|\033[0m \033[1;33mBST2\033[0m: ");
                  Inorder(&*Bst2); 
                  printf("\033[1;36m               |\033[0m");
                  printf("\n\033[1;36m|\033[0m \033[1;33mBST3\033[0m: ");
                  Inorder(&*Bst3); 
                  printf("\033[1;36m               |\033[0m");
                  printf("\n\033[1;36m+-------------------------------------+\033[0m");
                   }
                 else
                   {
                   if( Choix == 7) {
                  printf("\n\033[1;36m+---------------------------------------------+\033[0m");
                  printf("\n\033[1;36m|\033[1;35m          WORD COUNT BY LEVEL           \033[1;36m|\033[0m");
                  printf("\n\033[1;36m+---------------------------------------------+\033[0m");
                  printf("\n\033[1;36m|\033[0m \033[1;33mBST1\033[0m: ");
                  Compter_niveau(&*Bst1, &*X, &*Y, &*Z);
                  printf("\033[1;36m                  |\033[0m");
                  printf("\n\033[1;36m|\033[0m \033[1;33mBST2\033[0m: ");
                  Compter_niveau(&*Bst2, &*X, &*Y, &*Z);
                  printf("\033[1;36m                  |\033[0m");
                  printf("\n\033[1;36m|\033[0m \033[1;33mBST3\033[0m: ");
                  Compter_niveau(&*Bst3, &*X, &*Y, &*Z);
                  printf("\033[1;36m                  |\033[0m");
                  printf("\n\033[1;36m+---------------------------------------------+\033[0m");
                     }
                   else
                     {
                     if( Choix == 8) {
                      printf("\n \033[1;36mEnter word to search: \033[0m");
                      word = malloc(255 * sizeof(char));
                      scanf("%s", word);
                      int found = Search(&word, &*Bst1, &*Bst2, &*Bst3, &*X, &*Y, &*Z,&u);
                      printf("Word '%s' %s found.\n", word, found ? "was" : "was not");
                       }
                     else
                       {
                       if( Choix == 9) {
                          printf("\n\033[1;36mEnter range [word1 word2]: \033[0m");
                          word1 = malloc(255 * sizeof(char));
                          word2 = malloc(255 * sizeof(char));        
                         scanf("%s %s", word1, word2);
                         Search_range(&word1, &word2, &*Bst1, &*Bst2, &*Bst3,&*X,&*Y,&*Z);
                         }
                       else
                         {
                          if(Choix==10){
                             printf("\n ENTER THE NUMBER OF SIMULATION :");
                             scanf("%d",&sum);
                             for(int v=1;v<=sum;v++){
                              printf("\n\n SUMULATION NUMBER : %d",v);
                              simulatio_search();
                             }
                          }else
                          {if(Choix==11){ 
                             printf("\n ENTER THE NUMBER OF SIMULATION :");
                             scanf("%d",&sum);
                             for(int v=1;v<=sum;v++){
                             printf("\n\n SUMULATION NUMBER : %d",v);
                             simulatio_range();
                             }
                          }else{
                         if( Choix == 12) {
                           printf ( " %s", "AU REVOIR!\n" ) ;
                         }
                        }
                         } ;
                        
                       } ;
                      
                     } ;
                    
                   } ;
                  
                 } ;
                
               } ;
              
             } ;
            
           } ;
          
         } ;
        
       } ;
     if (Choix != 12) {
            printf("\nAppuyez sur Enter pour continuer --> ");
            getchar(); 
            getchar(); 
        } 
 } ;
    
    }
  /**************************************************************/
  /***************FFFFFFFFFFONCTION POUR GENERER LE FICHIER***************/
  /**************************************************************/
  void Generer_fichier (int Num)
    {
      /** Variables locales **/
      int I;
      int J;
      string255 Mot;
      string255 _Sx;
      Type_Ts S_S;

      /** Corps du module **/
     Mot = malloc(255 * sizeof(char));
     _Sx = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "T.z" , "N" ) ;
     for( I  =  1 ;I <=  Num ; ++I){
       J  =  Aleanombre(10 ) ;
       if( I == 0) {
         strcpy (_Sx, "Y");
         strcpy (Mot,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
         }
       else
         {
         if( I == 0) {
           strcpy (_Sx, "Z");
           strcpy (Mot,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
           }
         else
           {
           if( I == 0) {
             strcpy (_Sx, "a");
             strcpy (Mot,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
             }
           else
             {
             strcpy (Mot,   Aleachaine(Aleanombre(5 ) + 3 )) ;
            
           } ;
          
         } ;
        
       } ;
       S_S.Champ1= malloc(255 * sizeof(char));
       strcpy(S_S.Champ1 , Mot) ;
       Init_struct_Ts ( S , S_S )  ;
       Ecrireseq_s ( F , S ) ;
      
     } ;
     Fermer_s ( F ) ;
    
    }
  /**************************************************************/
  /***************FFFFFFFFFFONCTION POUR AFFICHER LE FICHIER***************/
  /**************************************************************/
  void Ecrire_fichier()
    {
      /** Variables locales **/
      int I;

      /** Corps du module **/
     Ouvrir_s (&F , "T.z" , "A" ) ;
     I  =  0 ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       /** Ecriture d'une structure */
       printf ( " %s", S->Champ1 ) ;
       I  =  I + 1 ;
      
 } ;
     Fermer_s ( F ) ;
     printf ( " %s", "Compte = " );
     printf ( " %d", I ) ;
    
    }
  /**************************************************************/
  /***************FFFFFFFFFFFFFFONCTION POUR INSERTER BST1********************/
  /**************************************************************/
  void Insert_bst1 (Pointeur_As *Root , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As To_insert=NULL;
      string255 Str;
      string2 Ch;

      /** Corps du module **/
     Str = malloc(255 * sizeof(char));
     Ch = malloc(2 * sizeof(char));
     *Root  =  NULL ;
     Ouvrir_s (&F , "T.z" , "A" ) ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy (Str,   Struct1_Ts ( S  )) ;
       Creernoeud_As (& To_insert ) ;
       Aff_info_As ( To_insert , Str ) ;
       Insert ( & *Root , & To_insert ) ;
       strcpy (Ch,   Caract ( Str , 1 )) ;
       if( (strcmp( Ch, *X) == 0  ) || (strcmp( Ch, *Y) == 0  ) || (strcmp( Ch, *Z) == 0  )) {
         while( Pere_As ( To_insert ) != NULL) {
           Retation ( & To_insert ) ;
          
 } ;
         *Root  =  To_insert ;
        
       } ;
      
 } ;
     Fermer_s ( F ) ;
    
    }
  /**************************************************************/
  /***************FFFFFFFFFFFFFFONCTION POUR INSRTER DANS L'ARB***************/
  /**************************************************************/
  void Insert (Pointeur_As *Root , Pointeur_As *To_insert)
    {
      /** Variables locales **/
      Pointeur_As Save=NULL;

      /** Corps du module **/
     if( *Root == NULL) {
       *Root  =  *To_insert ;
       Aff_pere_As ( *To_insert , NULL ) ;
       }
     else
       {
       if(strcmp( Info_As ( *Root ), Info_As ( *To_insert )) < 0 ) {
         if( Fd_As ( *Root ) == NULL) {
           Aff_fd_As ( *Root , *To_insert ) ;
           Aff_pere_As ( *To_insert , *Root ) ;
           }
         else
           {
           Save  =  Fd_As ( *Root ) ;
           Insert ( & Save , & *To_insert ) ;
          
         } ;
         }
       else
         {
         if( Fg_As ( *Root ) == NULL) {
           Aff_fg_As ( *Root , *To_insert ) ;
           Aff_pere_As ( *To_insert , *Root ) ;
           }
         else
           {
           Save  =  Fg_As ( *Root ) ;
           Insert ( & Save , & *To_insert ) ;
          
         } ;
        
       } ;
      
     } ;
    
    }
  /**************************************************************/
  /***************FFFFFFFFFFFFFFONCTION POUR FAIRE UNE RETATION***************/
  /**************************************************************/
  void Retation (Pointeur_As *To_insert)
    {
      /** Variables locales **/
      Pointeur_As P=NULL;
      Pointeur_As Q=NULL;
      Pointeur_As Save=NULL;

      /** Corps du module **/
     P  =  Pere_As ( *To_insert ) ;
     Q  =  Pere_As ( P ) ;
     if( *To_insert == Fg_As ( P )) {
       Save  =  Fd_As ( *To_insert ) ;
       Aff_fd_As ( *To_insert , P ) ;
       Aff_fg_As ( P , Save ) ;
       if( Save != NULL) {
         Aff_pere_As ( Save , P ) ;
        
       } ;
       Aff_pere_As ( P , *To_insert ) ;
       Aff_pere_As ( *To_insert , Q ) ;
       if( Q != NULL) {
         if( P == Fd_As ( Q )) {
           Aff_fd_As ( Q , *To_insert ) ;
           }
         else
           {
           Aff_fg_As ( Q , *To_insert ) ;
          
         } ;
        
       } ;
       }
     else
       {
       Save  =  Fg_As ( *To_insert ) ;
       Aff_fg_As ( *To_insert , P ) ;
       Aff_fd_As ( P , Save ) ;
       if( Save != NULL) {
         Aff_pere_As ( Save , P ) ;
        
       } ;
       Aff_pere_As ( P , *To_insert ) ;
       Aff_pere_As ( *To_insert , Q ) ;
       if( Q != NULL) {
         if( P == Fd_As ( Q )) {
           Aff_fd_As ( Q , *To_insert ) ;
           }
         else
           {
           Aff_fg_As ( Q , *To_insert ) ;
          
         } ;
        
       } ;
      
     } ;
    
    }
  /**************************************************************/
  /***************FFFFFFFFFFFFFFONCTION POUR INSERTER BST3********************/
  /**************************************************************/
  void Insert_bst3 (Pointeur_As *Root , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As To_insert=NULL;
      string255 Str;
      string2 Ch;

      /** Corps du module **/
     Str = malloc(255 * sizeof(char));
     Ch = malloc(2 * sizeof(char));
     *Root  =  NULL ;
     Ouvrir_s (&F , "T.z" , "A" ) ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy (Str,   Struct1_Ts ( S  )) ;
       Creernoeud_As (& To_insert ) ;
       Aff_info_As ( To_insert , Str ) ;
       Insert ( & *Root , & To_insert ) ;
       strcpy (Ch,   Caract ( Str , 1 )) ;
       if( (strcmp( Ch, *X) != 0  ) && (strcmp( Ch, *Y) != 0  ) && (strcmp( Ch, *Z) != 0  )) {
         while( Pere_As ( To_insert ) != NULL) {
           Retation ( & To_insert ) ;
          
 } ;
         *Root  =  To_insert ;
        
       } ;
      
 } ;
     Fermer_s ( F ) ;
    
    }
  /**************************************************************/
  /***************FFFFFFFFFFFFFFONCTION POUR CALCULER LE DEPHT****************/
  /**************************************************************/
  int  Depth_node (Pointeur_As *To_insert) 
    {
      /** Variables locales **/
      int  Depth_node2 ;
      int Cpt;
      Pointeur_As P=NULL;

      /** Corps du module **/
     P  =  *To_insert ;
     Cpt  =  - 1 ;
     while( P != NULL) {
       P  =  Pere_As ( P ) ;
       Cpt  =  Cpt + 1 ;
      
 } ;
     Depth_node2  =  Cpt ;
    
     return Depth_node2 ;
    }
  /**************************************************************/
  /***************FFFFFFFFFFONCTION POUR INSERTER BST3********************/
  /**************************************************************/
  void Insert_bst2 (Pointeur_As *Root , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As To_insert=NULL;
      string255 Str;
      string2 Ch;
      int I;

      /** Corps du module **/
     Str = malloc(255 * sizeof(char));
     Ch = malloc(2 * sizeof(char));
     *Root  =  NULL ;
     Ouvrir_s (&F , "T.z" , "A" ) ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy (Str,   Struct1_Ts ( S  )) ;
       Creernoeud_As (& To_insert ) ;
       Aff_info_As ( To_insert , Str ) ;
       Insert ( & *Root , & To_insert ) ;
       strcpy (Ch,   Caract ( Str , 1 )) ;
       if( (strcmp( Ch, *X) == 0  ) || (strcmp( Ch, *Y) == 0  ) || (strcmp( Ch, *Z) == 0  )) {
         for( I  =  1 ;I <=  ( Depth_node ( & To_insert ) / 2 ) ; ++I){
           Retation ( & To_insert ) ;
          
         } ;
        
       } ;
       if( (strcmp( Ch, *X) > 0  ) && (strcmp( Ch, *Y) > 0  ) && (strcmp( Ch, *Z) > 0  )) {
         while( Pere_As ( To_insert ) != NULL) {
           Retation ( & To_insert ) ;
          
 } ;
         *Root  =  To_insert ;
        
       } ;
      
 } ;
     Fermer_s ( F ) ;
    
    }
  /**************************************************************/
  /***************FFFFFFFFFFONCTION POUR CALCULER LES MOTS****************/
  /**************************************************************/
  int  Conter_mot (Pointeur_As *Root , string2 *X , string2 *Y , string2 *Z) 
    {
      /** Variables locales **/
      int  Conter_mot2 ;
      int Cpt;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;
      Pointeur_As _Px3=NULL;
      Pointeur_As _Px4=NULL;

      /** Corps du module **/
     if( *Root == NULL) {
       Conter_mot2  =  0; }
     else
       {
       if( (strcmp( Caract ( Info_As ( *Root ) , 1 ), *X) == 0  ) || (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Y) == 0  ) || (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Z) == 0  )) {
         _Px1 =  Fd_As ( *Root ) ;
         _Px2 =  Fg_As ( *Root ) ;
         Cpt  =  Conter_mot ( &_Px1, & *X , & *Y , & *Z ) + Conter_mot ( &_Px2, & *X , & *Y , & *Z ) + 1 ;
         }
       else
         {
         _Px3 =  Fd_As ( *Root ) ;
         _Px4 =  Fg_As ( *Root ) ;
         Cpt  =  Conter_mot ( &_Px3, & *X , & *Y , & *Z ) + Conter_mot ( &_Px4, & *X , & *Y , & *Z ) ;
        
       } ;
       Conter_mot2  =  Cpt ;
      
     } ;
    
     return Conter_mot2 ;
    }
  /**************************************************************/
  /***************FFFFFFFONCTION POUR CALCULER le depht****************/
  /**************************************************************/
  int  Depth (Pointeur_As *Root) 
    {
      /** Variables locales **/
      int  Depth2 ;
      int Prf;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( *Root == NULL) {
       Depth2  =  - 1 ;
       }
     else
       {
       _Px1 =  Fd_As ( *Root ) ;
       _Px2 =  Fg_As ( *Root ) ;
       Depth2  =  Max ( Depth ( &_Px1) , Depth ( &_Px2) ) + 1 ;
      
     } ;
    
     return Depth2 ;
    }
  /**************************************************************/
  /***************FFFFFFONCTION POUR INORDER TRAVERSAL****************/
  /**************************************************************/
  void Inorder (Pointeur_As *Root)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( *Root != NULL) {
       _Px1 =  Fg_As ( *Root ) ;
       Inorder ( &_Px1) ;
       printf ( " %s", Info_As(*Root) ) ;
       _Px2 =  Fd_As ( *Root ) ;
       Inorder ( &_Px2) ;
      
     } ;
    
    }
  /**************************************************************/
  /***************FFFFFFONCTION POUR CONTER PAR NIVEAU****************/
  /**************************************************************/
  void Compter_niveau (Pointeur_As *Root , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      if (*Root!=NULL){
      Pointeur_As P=NULL;
      Pointeur_Fi Queue1=NULL;
      Pointeur_FAs Queue2=NULL;
      int Prev;
      int Cpt;
      int Val;

      /** Corps du module **/
     Prev  =  0 ;
     Cpt  =  0 ;
     Creerfile_Fi (& Queue1 ) ;
     Creerfile_FAs (& Queue2 ) ;
     Enfiler_FAs ( Queue2 , *Root ) ;
     Enfiler_Fi ( Queue1 , 0 ) ;
     while( ! Filevide_FAs ( Queue2 )) {
       Defiler_FAs ( Queue2 , &P ) ;
       Defiler_Fi ( Queue1 , &Val ) ;
       if( Val > Prev) {
        printf ( "\nLEVEL  %d : %d",Prev, Cpt ) ;
         Prev  =  Prev + 1 ;
         Cpt  =  0 ;
        
       } ;
       if( (strcmp( Caract ( Info_As ( P ) , 1 ), *X) == 0  ) || (strcmp( Caract ( Info_As ( P ) , 1 ), *Y) == 0  ) || (strcmp( Caract ( Info_As ( P ) , 1 ), *Z) == 0  )) {
         Cpt  =  Cpt + 1 ;
        
       } ;
       if( Fg_As ( P ) != NULL) {
         Enfiler_FAs ( Queue2 , Fg_As ( P ) ) ;
         Enfiler_Fi ( Queue1 , Val + 1 ) ;
        
       } ;
       if( Fd_As ( P ) != NULL) {
         Enfiler_FAs ( Queue2 , Fd_As ( P ) ) ;
         Enfiler_Fi ( Queue1 , Val + 1 ) ;
        
       } ;
      
 } ;
     printf ( "\nLEVEL %d :  %d",Prev, Cpt ) ;
    }
    }
  /**************************************************************/
  /***************  FONCTION POUR chercher bst1  ****************/
  /**************************************************************/
  bool  Search_bst1 (Pointeur_As *Root , string255 *Ch , string2 *X , string2 *Y , string2 *Z,int *h) 
    {
      /** Variables locales **/
      bool  Search_bst12 ;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root == NULL )) {
       Search_bst12  =  False ;
       }
     else
       {
       (*h)++;
       if( (strcmp( Caract ( Info_As ( *Root ) , 1 ), *X) != 0  ) && (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Y) != 0  ) && (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Z) != 0  )) {
         Search_bst12  =  False ;
         }
       else
         {
         if( (strcmp( *Ch, Info_As ( *Root )) == 0  )) {
           Search_bst12  =  True ;
           }
         else
           {
           if( (strcmp( *Ch, Info_As ( *Root )) < 0  )) {
             _Px1 =  Fg_As ( *Root ) ;
             Search_bst12  =  Search_bst1 ( &_Px1, & *Ch , & *X , & *Y , & *Z, & *h ) ;
             }
           else
             {
             _Px2 =  Fd_As ( *Root ) ;
             Search_bst12  =  Search_bst1 ( &_Px2, & *Ch , & *X , & *Y , & *Z , & *h) ;
            
           } ;
          
         } ;
        
       } ;
      
     } ;
    
     return Search_bst12 ;
    }
  /**************************************************************/
  /***************       FONCTION POUR chercher bst2  ****************/
  /**************************************************************/
 bool  Search_bst2(Pointeur_As *Root , string255 *Ch , string2 *X , string2 *Y , string2 *Z,int *h)
    {
      /** Variables locales **/
      bool  Search_bst22 ;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root == NULL )) {
       Search_bst22  =  False ;
       }
     else
       {
        (*h)++;
       if( (strcmp( Caract ( Info_As ( *Root ) , 1 ), *X) < 0  ) && (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Y) < 0  ) && (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Z) < 0  )) {
         Search_bst22  =  False ;
         }
         else{
        if( (strcmp( *Ch, Info_As ( *Root )) == 0  )) {
         Search_bst22  =  True ;
         }
       else
         {
         if( (strcmp( *Ch, Info_As ( *Root )) < 0  )) {
           _Px1 =  Fg_As ( *Root ) ;
           Search_bst22  =  Search_bst2 ( &_Px1, & *Ch , & *X , & *Y , & *Z , & *h) ;
           }
         else
           {
           _Px2 =  Fd_As ( *Root ) ;
           Search_bst22  =  Search_bst2 ( &_Px2, & *Ch , & *X , & *Y , & *Z ,& *h) ;
          
         } ;
        
       } ;
      
     } ;
     };
     return Search_bst22 ;
    }
  /**************************************************************/
  /***************       FONCTION POUR chercher bst3  ****************/
  /**************************************************************/
  bool  Search_bst3 (Pointeur_As *Root , string255 *Ch , string2 *X , string2 *Y , string2 *Z, int *h) 
    {
      /** Variables locales **/
      bool  Search_bst32 ;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root == NULL )) {
       Search_bst32  =  False ;
       }
     else
       {
        (*h)++;
       if( (strcmp( Caract ( Info_As ( *Root ) , 1 ), *X) == 0  ) || (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Y) == 0  ) || (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Z) == 0  )) {
         Search_bst32  =  False ;
         }
       else
         {
         if( (strcmp( *Ch, Info_As ( *Root )) == 0  )) {
           Search_bst32  =  True ;
           }
         else
           {
           if( (strcmp( *Ch, Info_As ( *Root )) < 0  )) {
             _Px1 =  Fg_As ( *Root ) ;
             Search_bst32  =  Search_bst3 ( &_Px1, & *Ch , & *X , & *Y , & *Z ,& *h) ;
             }
           else
             {
             _Px2 =  Fd_As ( *Root ) ;
             Search_bst32  =  Search_bst3 ( &_Px2, & *Ch , & *X , & *Y , & *Z,& *h ) ;
            
           } ;
          
         } ;
        
       } ;
      
     } ;
    
     return Search_bst32 ;
    }
  /**************************************************************/
  /***************         FONCTION POUR chercher     ****************/
  /**************************************************************/
 
    bool  Search (string255 *Word , Pointeur_As *Root1 , Pointeur_As *Root2 , Pointeur_As *Root3 , string2 *X , string2 *Y , string2 *Z, int *h) 
    {
      /** Variables locales **/
      bool  Search2 ;
      (*h)=0;
      /** Corps du module **/
     if( (strcmp( Caract ( *Word , 1 ), *X) == 0  ) || (strcmp( Caract ( *Word , 1 ), *Y) == 0  ) || (strcmp( Caract ( *Word , 1 ), *Z) == 0  )) {
       Search2  =  Search_bst1 ( & *Root1 , & *Word , & *X , & *Y , & *Z, & *h ) ;
       }
     else
       {
       if( (strcmp( Caract ( *Word , 1 ), *X) > 0  ) || (strcmp( Caract ( *Word , 1 ), *Y) > 0  ) || (strcmp( Caract ( *Word , 1 ), *Z) > 0  )) {
         Search2  =  Search_bst2 ( & *Root2 , & *Word , & *X , & *Y , & *Z, & *h ) ;
         }
       else
         {
         Search2  =  Search_bst3 ( & *Root3 , & *Word , & *X , & *Y , & *Z ,& *h) ;
        
       } ;
      
     } ;
    
     return Search2 ;
    }
  /**************************************************************/
  /************   FONCTION POUR chercher in a range  **************/
  /**************************************************************/
  void Search_range (string255 *Word1 , string255 *Word2 , Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3,string2 *X , string2 *Y , string2 *Z)
    {

      /** Corps du module **/
     if( ( (strcmp( Caract ( *Word1 , 1 ), *X) == 0  ) || (strcmp( Caract ( *Word1 , 1 ), *Y) == 0  ) || (strcmp( Caract ( *Word1 , 1 ), *Z) == 0  ) ) && ( (strcmp( Caract ( *Word2 , 1 ), *X) == 0  ) || (strcmp( Caract ( *Word2 , 1 ), *Y) == 0  ) || (strcmp( Caract ( *Word2 , 1 ), *Z) == 0  ) )) {
       Range_bst1 ( & *Bst1 , & *Word1 , & *Word2,&*X,&*Y,&*Z ) ;
       }
     else
       {
       if( ( (strcmp( Caract ( *Word1 , 1 ), *X) > 0  ) && (strcmp( Caract ( *Word1 , 1 ), *Y) > 0  ) && (strcmp( Caract ( *Word1 , 1 ), *Z) > 0  ) ) || ( (strcmp( Caract ( *Word2 , 1 ), *X) < 0  ) && (strcmp( Caract ( *Word2 , 1 ), *Y) < 0  ) && (strcmp( Caract ( *Word2 , 1 ), *Z) < 0  ) )) {
         Range_bst3 ( & *Bst3 , & *Word1 , & *Word2 ,&*X,&*Y,&*Z) ;
         }
       else
         {
         Range_bst2 ( & *Bst2 , & *Word1 , & *Word2,&*X,&*Y,&*Z ) ;
        
       } ;
      
     } ;
    
    }
  /**************************************************************/
  /************   FONCTION POUR chercher a range bst1**************/
  /**************************************************************/
  void Range_bst1 (Pointeur_As *Root , string255 *Word1 , string255 *Word2,string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root != NULL )) {
       if( ( (strcmp( Caract ( Info_As ( *Root ) , 1 ), *X) == 0  ) || (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Y) == 0  ) || (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Z) == 0  ) )) {
         if( (strcmp( Info_As ( *Root ), *Word1) > 0  )) {
           _Px1 =  Fg_As ( *Root ) ;
           Range_bst1 ( &_Px1, & *Word1 , & *Word2 ,&*X,&*Y,&*Z) ;
          
         } ;
         if( (strcmp( Info_As ( *Root ), *Word1) >= 0  ) && (strcmp( Info_As ( *Root ), *Word2) <= 0  )) {
           printf ( " %s", Info_As(*Root) ) ;
          
         } ;
         if( (strcmp( Info_As ( *Root ), *Word2) < 0  )) {
           _Px2 =  Fd_As ( *Root ) ;
           Range_bst1 ( &_Px2, & *Word1 , & *Word2,&*X,&*Y,&*Z ) ;
          
         } ;
        
       } ;
      
     } ;
    
    }
  /**************************************************************/
  /************   FONCTION POUR chercher a range bst1**************/
  /**************************************************************/
  void Range_bst3 (Pointeur_As *Root , string255 *Word1 , string255 *Word2,string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root != NULL )) {
       if( ( (strcmp( Caract ( Info_As ( *Root ) , 1 ), *X) != 0  ) && (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Y) != 0  ) && (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Z) != 0  ) )) {
         if( (strcmp( Info_As ( *Root ), *Word1) > 0  )) {
           _Px1 =  Fg_As ( *Root ) ;
           Range_bst3 ( &_Px1, & *Word1 , & *Word2,&*X,&*Y,&*Z ) ;
          
         } ;
         if( (strcmp( Info_As ( *Root ), *Word1) >= 0  ) && (strcmp( Info_As ( *Root ), *Word2) <= 0  )) {
           printf ( " %s", Info_As(*Root) );
         } ;
         if( (strcmp( Info_As ( *Root ), *Word2) < 0  )) {
           _Px2 =  Fd_As ( *Root ) ;
           Range_bst3 ( &_Px2, & *Word1 , & *Word2 ,&*X,&*Y,&*Z) ;
          
         } ;
        
       } ;
      
     } ;
    
    }
  /**************************************************************/
  /************   FONCTION POUR chercher a range bst1**************/
  /**************************************************************/
  void Range_bst2 (Pointeur_As *Root , string255 *Word1 , string255 *Word2,string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root != NULL )) {
       if( (strcmp( Info_As ( *Root ), *Word1) > 0  )) {
         _Px1 =  Fg_As ( *Root ) ;
         Range_bst2 ( &_Px1, & *Word1 , & *Word2,&*X,&*Y,&*Z ) ;
        
       } ;
       if( (strcmp( Info_As ( *Root ), *Word1) >= 0  ) && (strcmp( Info_As ( *Root ), *Word2) <= 0  )) {
         printf ( " %s", Info_As(*Root) );
       } ;
       if( (strcmp( Info_As ( *Root ), *Word2) < 0  )) {
         _Px2 =  Fd_As ( *Root ) ;
         Range_bst2 ( &_Px2, & *Word1 , & *Word2,&*X,&*Y,&*Z ) ;
        
       } ;
      
     } ;
    
    }
 
    void Insert_bst0 (Pointeur_As *Root )
    {
      /** Variables locales **/
      Pointeur_As To_insert=NULL;
      string255 Str;
      string2 Ch;

      /** Corps du module **/
     Str = malloc(255 * sizeof(char));
     Ch = malloc(2 * sizeof(char));
     *Root  =  NULL ;
     Ouvrir_s (&F , "T.z" , "A" ) ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy (Str,   Struct1_Ts ( S  )) ;
       Creernoeud_As (& To_insert ) ;
       Aff_info_As ( To_insert , Str ) ;
       Insert ( & *Root , & To_insert ) ;
       } ;
      Fermer_s ( F ) ; 
 } ;

 void Generer_fichier2 (int Num)
    {
      /** Variables locales **/
      int I;
      int J;
      string255 Mot;
      string255 _Sx;
      Type_Ts S_S;

      /** Corps du module **/
     Mot = malloc(255 * sizeof(char));
     _Sx = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F2.z" , "N" ) ;
     for( I  =  1 ;I <=  Num ; ++I){
       J  =  Aleanombre(10 ) ;
       if( I == 0) {
         strcpy (_Sx, "Y");
         strcpy (Mot,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
         }
       else
         {
         if( I == 0) {
           strcpy (_Sx, "Z");
           strcpy (Mot,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
           }
         else
           {
           if( I == 0) {
             strcpy (_Sx, "a");
             strcpy (Mot,  strcat(_Sx, Aleachaine(Aleanombre(5 ) + 3 ))) ;
             }
           else
             {
             strcpy (Mot,   Aleachaine(Aleanombre(5 ) + 3 )) ;
            
           } ;
          
         } ;
        
       } ;
       S_S.Champ1= malloc(255 * sizeof(char));
       strcpy(S_S.Champ1 , Mot) ;
       Init_struct_Ts ( S , S_S )  ;
       Ecrireseq_s ( F , S ) ;
      
     } ;
     Fermer_s ( F ) ;
    
    }

bool  Search_bst0(Pointeur_As *Root , string255 *Ch , string2 *X , string2 *Y , string2 *Z,int *h)
    {
      /** Variables locales **/
      bool  Search_bst22 ;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root == NULL )) {
       Search_bst22  =  False ;
       }
     else
       {
        (*h)++;
       if( (strcmp( *Ch, Info_As ( *Root )) == 0  )) {
         Search_bst22  =  True ;
         }
       else
         {
         if( (strcmp( *Ch, Info_As ( *Root )) < 0  )) {
           _Px1 =  Fg_As ( *Root ) ;
           Search_bst22  =  Search_bst0 ( &_Px1, & *Ch , & *X , & *Y , & *Z , & *h) ;
           }
         else
           {
           _Px2 =  Fd_As ( *Root ) ;
           Search_bst22  =  Search_bst0 ( &_Px2, & *Ch , & *X , & *Y , & *Z ,& *h) ;
          
         } ;
        
       } ;
      
     } ;
    
     return Search_bst22 ;
    }
     void Search_range_s (string255 *Word1 , string255 *Word2 , Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3,int *h,string2 *X , string2 *Y , string2 *Z)
    {
      /** Corps du module **/
     if( ( (strcmp( Caract ( *Word1 , 1 ), *X) == 0  ) || (strcmp( Caract ( *Word1 , 1 ), *Y) == 0  ) || (strcmp( Caract ( *Word1 , 1 ), *Z) == 0  ) ) && ( (strcmp( Caract ( *Word2 , 1 ), *X) == 0  ) || (strcmp( Caract ( *Word2 , 1 ), *Y) == 0  ) || (strcmp( Caract ( *Word2 , 1 ), *Z) == 0  ) )) {
       Range_bst1_s ( & *Bst1 , & *Word1 , & *Word2,& *h , & *X , & *Y , & *Z ) ;
       }
     else
       {
       if ( (strcmp( Caract ( *Word1 , 1 ), *X) < 0  ) && (strcmp( Caract ( *Word1 , 1 ), *Y) < 0  ) && (strcmp( Caract ( *Word1 , 1 ), *Z) < 0  ) ) {
         Range_bst3_s ( & *Bst3 , & *Word1 , & *Word2 ,& *h, & *X , & *Y , & *Z ) ;
         }
       else
         {
          if ( (strcmp( Caract ( *Word2 , 1 ), *X) > 0  ) && (strcmp( Caract ( *Word2 , 1 ), *Y) > 0  ) && (strcmp( Caract ( *Word2 , 1 ), *Z) > 0  ) ){
              Range_bst2_s2 ( & *Bst2 , & *Word1 , & *Word2 ,& *h, & *X , & *Y , & *Z ) ;
          }
          else{
         Range_bst2_s ( & *Bst2 , & *Word1 , & *Word2 ,& *h, & *X , & *Y , & *Z ) ;
          }
       } ;
      
     } ;
    }
    
  /**************************************************************/
  /************   FONCTION POUR chercher a range bst1**************/
  /**************************************************************/
  void Range_bst1_s (Pointeur_As *Root , string255 *Word1 , string255 *Word2,int *h,string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root != NULL )) {
      (*h)++;
       if( ( (strcmp( Caract ( Info_As ( *Root ) , 1 ), *X) == 0  ) || (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Y) == 0  ) || (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Z) == 0  ) )) {
         if( (strcmp( Info_As ( *Root ), *Word1) > 0  )) {
           _Px1 =  Fg_As ( *Root ) ;
           Range_bst1_s ( &_Px1, & *Word1 , & *Word2 ,& *h, & *X , & *Y , & *Z ) ;
         } ;       
         if( (strcmp( Info_As ( *Root ), *Word2) < 0  )) {
           _Px2 =  Fd_As ( *Root ) ;
           Range_bst1_s ( &_Px2, & *Word1 , & *Word2 ,& *h, & *X , & *Y , & *Z ) ;
          
         } ;
        
       } ;
     } ;
    
    }
  /**************************************************************/
  /************   FONCTION POUR chercher a range bst1**************/
  /**************************************************************/
  void Range_bst3_s (Pointeur_As *Root , string255 *Word1 , string255 *Word2,int *h,string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root != NULL )) {
      (*h)++;
       if( ( (strcmp( Caract ( Info_As ( *Root ) , 1 ), *X) != 0  ) && (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Y) != 0  ) && (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Z) != 0  ) )) {
         if( (strcmp( Info_As ( *Root ), *Word1) > 0  )) {
           _Px1 =  Fg_As ( *Root ) ;
           Range_bst3_s ( &_Px1, & *Word1 , & *Word2,& *h, & *X , & *Y , & *Z  ) ;
          
         } ;
         
         if( (strcmp( Info_As ( *Root ), *Word2) < 0  )) {
           _Px2 =  Fd_As ( *Root ) ;
           Range_bst3_s ( &_Px2, & *Word1 , & *Word2,& *h , & *X , & *Y , & *Z ) ;
         } ;
        
       } ;
     } ;
    
    }
  /**************************************************************/
  /************   FONCTION POUR chercher a range bst1**************/
  /**************************************************************/
  void Range_bst2_s (Pointeur_As *Root , string255 *Word1 , string255 *Word2,int *h,string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root != NULL )) {
      (*h)++;
       if( (strcmp( Info_As ( *Root ), *Word1) > 0  )) {
         _Px1 =  Fg_As ( *Root ) ;
         Range_bst2_s ( &_Px1, & *Word1 , & *Word2,& *h, & *X , & *Y , & *Z  ) ;
       } ;
       
       if( (strcmp( Info_As ( *Root ), *Word2) < 0  )) {
         _Px2 =  Fd_As ( *Root ) ;
         Range_bst2_s (&_Px2 , & *Word1 , & *Word2,& *h , & *X , & *Y , & *Z ) ;
       } ;
     } ;
    
    }
    void Range_bst2_s2 (Pointeur_As *Root , string255 *Word1 , string255 *Word2,int *h,string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root != NULL )) {
      if( (strcmp( Caract ( Info_As ( *Root ) , 1 ), *X) >= 0  ) || (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Y) >= 0  ) || (strcmp( Caract ( Info_As ( *Root ) , 1 ), *Z) >= 0  )) {
       (*h)++;
        if( (strcmp( Info_As ( *Root ), *Word1) > 0  )) {
         _Px1 =  Fg_As ( *Root ) ;
         Range_bst2_s2 ( &_Px1, & *Word1 , & *Word2,& *h, & *X , & *Y , & *Z  ) ;
       } ;
       
       if( (strcmp( Info_As ( *Root ), *Word2) < 0  )) {
         _Px2 =  Fd_As ( *Root ) ;
         Range_bst2_s2 (&_Px2 , & *Word1 , & *Word2,& *h , & *X , & *Y , & *Z ) ;
       } ;
     } ;
     }
    }

    void Range_bst0 (Pointeur_As *Root , string255 *Word1 , string255 *Word2,int *h)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Root != NULL )) {
      (*h)++;
       if( (strcmp( Info_As ( *Root ), *Word1) > 0  )) {
         _Px1 =  Fg_As ( *Root ) ;
         Range_bst0 ( &_Px1, & *Word1 , & *Word2,& *h ) ;        
       } ;
       
       if( (strcmp( Info_As ( *Root ), *Word2) < 0  )) {
         _Px2 =  Fd_As ( *Root ) ;
         Range_bst0 ( &_Px2, & *Word1 , & *Word2,& *h ) ;
        
       } ;
     } ;
    }
  void simulatio_search(){
    int k =10000;
    int cpt=0;
    string255 Str;
    Str = malloc(255 * sizeof(char));
    int nombre_found=0;
    int nombre_not_found=0;
    int operation_found=0;
    int operation_not_found=0;
    int nombre_found0=0;
    int nombre_not_found0=0;
    int operation_found0=0;
    int operation_not_found0=0;
    int trouve;
    int nbr_xyz=0;
    int nbr_greater= 0;
    int nbr_less=0;
    Generer_fichier (k);
    Insert_bst1 ( & Bst1 , & X , & Y , & Z ) ;
    Insert_bst2 ( & Bst2 , & X , & Y , & Z ) ;
    Insert_bst3 ( & Bst3 , & X , & Y , & Z ) ;
    Insert_bst0 ( & Bst0 );
    Generer_fichier2(k);
     Ouvrir_s (&F , "F2.z" , "A" ) ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy (Str,   Struct1_Ts ( S  )) ;
        if ( (strcmp( Caract ( Str , 1 ), X) == 0  ) || (strcmp( Caract ( Str, 1 ), Y) == 0  ) || (strcmp( Caract ( Str , 1 ), Z) == 0  ) ) {
          nbr_xyz++;
        }
        if ( (strcmp( Caract ( Str , 1 ), X) > 0  ) && (strcmp( Caract ( Str, 1 ), Y) > 0  ) && (strcmp( Caract ( Str , 1 ), Z) > 0  ) ) {
          nbr_greater++;
        }
         if ( (strcmp( Caract ( Str , 1 ), X) < 0  ) && (strcmp( Caract ( Str, 1 ), Y) < 0  ) && (strcmp( Caract ( Str , 1 ), Z) < 0  ) ) {
          nbr_less++;
        }
       cpt=0;
       trouve = Search(&Str, &Bst1, &Bst2, &Bst3, &X, &Y, &Z,&cpt);
      if (trouve==0){
        nombre_not_found++;
        operation_not_found+=cpt;
      }else{
        nombre_found++;
        operation_found+=cpt;
      }
      cpt=0;
       trouve = Search_bst0(&Bst0 ,  & Str , & X , & Y , & Z , &cpt);
      if (trouve==0){
        nombre_not_found0++;
        operation_not_found0+=cpt;
      }else{
        nombre_found0++;
        operation_found0+=cpt;
      }
       } ;
      Fermer_s ( F ) ;
      printf("\n+----------------------------+-------------------+-------------------+");
      printf("\n|           INFO             |   TRIPLET (BST)   |      BST0         |");
      printf("\n+----------------------------+-------------------+-------------------+");
      printf("\n| Words found                | %17d | %17d |", nombre_found, nombre_found0);
      printf("\n| Words not found            | %17d | %17d |", nombre_not_found, nombre_not_found0);
      printf("\n| Operations for found words | %17d | %17d |", operation_found, operation_found0);
      printf("\n| Operations for not found   | %17d | %17d |", operation_not_found, operation_not_found0);
      printf("\n+----------------------------+-------------------+-------------------+");
      printf("\n| Additional Statistics      |                                       |");
      printf("\n+----------------------------+---------------------------------------+");
      printf("\n| Words starting with x,y,z  | %17d                     |", nbr_xyz);
      printf("\n| Words > x,y,z              | %17d                     |", nbr_greater);
      printf("\n| Words < x,y,z              | %17d                     |", nbr_less);
      printf("\n+----------------------------+---------------------------------------+");
  }

  void simulatio_range(){
    int k =10000;
    int cpt=0;
    string255 Str,Str1;
    Str = malloc(255 * sizeof(char));
    Str1 = malloc(255 * sizeof(char));
   int nombre_triplet=0;
   int nombre_bst0=0;
    Generer_fichier (k);
    Insert_bst1 ( & Bst1 , & X , & Y , & Z ) ;
    Insert_bst2 ( & Bst2 , & X , & Y , & Z ) ;
    Insert_bst3 ( & Bst3 , & X , & Y , & Z ) ;
    Insert_bst0 ( & Bst0 );
    Generer_fichier2(k);
     Ouvrir_s (&F , "F2.z" , "A" ) ;
     while( ! Finfich_s ( F )) {
       Lireseq_s ( F , S ) ;
       strcpy (Str,   Struct1_Ts ( S  )) ;
      Lireseq_s ( F , S ) ;
       strcpy (Str1,   Struct1_Ts ( S  )) ;
        cpt=0;
       
     if (strcmp(  Str , Str1) < 0){
        Range_bst0(& Bst0 , & Str , & Str1 ,& cpt);
        nombre_bst0+=cpt;
      }else{
        Range_bst0(& Bst0 , & Str1 , & Str ,& cpt);
        nombre_bst0+=cpt;
      }
       
       cpt=0;
      if (strcmp(  Str , Str1) < 0){
        Search_range_s(&Str,&Str1,&Bst1, &Bst2, &Bst3,&cpt, & X , & Y , & Z );
        nombre_triplet+=cpt;
      }else{
        Search_range_s(&Str1,&Str,&Bst1, &Bst2, &Bst3,&cpt, & X , & Y , & Z );
        nombre_triplet+=cpt;
      }
      } ;
     
      Fermer_s ( F ) ;
      printf("\n+----------------------+-------------------+-------------------+");
      printf("\n|        INFO          |  TRIPLET (BST)    |       BST0        |");
      printf("\n+----------------------+-------------------+-------------------+");
      printf("\n| Number of nodes      | %17d | %17d |", nombre_triplet, nombre_bst0);
      printf("\n+----------------------+-------------------+-------------------+");

  }


  int main(int argc, char *argv[])
    {
     srand(time(NULL));
     S = malloc(sizeof(Typestruct1_s));
     S->Champ1 = malloc(255 * sizeof(char));
     X = malloc(2 * sizeof(char));
     Y = malloc(2 * sizeof(char));
     Z = malloc(2 * sizeof(char));
     strcpy (X,   "Y") ;
     strcpy (Y,   "Z") ;
     strcpy (Z,   "a") ;
     Bst1  =  NULL ;
     Bst2  =  NULL ;
     Bst3  =  NULL ;
     N  =  101 ;
     Menu (  N , & Bst1 , & Bst2 , & Bst3 , & X , & Y , & Z ) ;
    
   
      system("PAUSE");
      return 0;
    }