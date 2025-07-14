
  /*****************DDDDDDDDDDEBUT TP Z*********************/
   SOIT
       F UN FICHIER DE ( CHAINES ) BUFFER S ;
       Generer_fichier , Ecrire_fichier DES ACTION ;
       Bst1 , Bst2 , Bst3 : ARB DE CHAINE ;
       Insert , Retation , Insert_bst1 UNE ACTION ;
       Insert_bst3 , Insert_bst2 DES ACTION ;
       Depth_node , Conter_mot , Depth UNE FONCTION ( ENTIER ) ;
       X , Y , Z DES CAR ;
       Inorder , Compter_niveau , Search_range , Range_bst1 , Range_bst2 , Range_bst3,Range_bst22 UNE ACTION ;
       Search_bst1 , Search_bst2 , Search_bst3 , Search UNE FONCTION ( BOOLEEN ) ;
       N UN ENTIER ;
       Menu UNE ACTION ;
       cher ,cw1 ,cw2 une chaine ;
   DEBUT
       X := 'Y' ;
       Y := 'Z' ;
       Z := 'a' ;
       Bst1 := NIL ;
       Bst2 := NIL ;
       Bst3 := NIL ;
       N := 101 ;
       APPEL Menu ( N , Bst1 , Bst2 , Bst3 , X , Y , Z ) ;
   FIN
  /**************************************************************/
  /**************        MENU          ***************/
  /**************************************************************/
   ACTION Menu ( N , Bst1 , Bst2 , Bst3 , X , Y , Z )
   SOIENT
       Choix UN ENTIER ;
       Bst1 , Bst2 , Bst3 DES ARB DE CHAINE ;
       X , Y , Z DES CAR ;
       N UN ENTIER ;
   DEBUT
       Choix := - 1 ;
       TANTQUE Choix # 10
           ECRIRE ( '----- MENU PRINCIPAL -----' ) ;
           ECRIRE ( '1. GENERER FICHIER' ) ;
           ECRIRE ( '2. AFFICHER LE FICHIER' ) ;
           ECRIRE ( '3. CREER LES ARBRES' ) ;
           ECRIRE ( '4. NOMBRE DES MOTS X/Y/Z ' ) ;
           ECRIRE ( '5. DEPTH DES ARBRES' ) ;
           ECRIRE ( '6. INORDER TRAVERSAL' ) ;
           ECRIRE ( '7. COMPTE PAR NIVEAU' ) ;
           ECRIRE ( '8. ONE WORD SEARCH' ) ;
           ECRIRE ( '9. RANGE search' ) ;
           ECRIRE ( '10. Quitter' ) ;
           ECRIRE ( 'ENTRER VOTRE CHOIX' ) ;
           LIRE ( Choix ) ;
           SI Choix = 1
               APPEL Generer_fichier ( N ) ;
           SINON
               SI Choix = 2
                   APPEL Ecrire_fichier ;
               SINON
                   SI Choix = 3
                       APPEL Insert_bst1 ( Bst1 , X , Y , Z ) ;
                       APPEL Insert_bst2 ( Bst2 , X , Y , Z ) ;
                       APPEL Insert_bst3 ( Bst3 , X , Y , Z ) ;
                   SINON
                       SI Choix = 4
                           ECRIRE('BST1 :');
                           ECRIRE ( Conter_mot ( Bst1 , X , Y , Z ) ) ;
                           ECRIRE ('BST2 :');
                           ECRIRE ( Conter_mot ( Bst2 , X , Y , Z ) ) ;
                           ECRIRE ('BST3 :');
                           ECRIRE ( Conter_mot ( Bst3 , X , Y , Z ) ) ;
                       SINON
                           SI Choix = 5
                               ECRIRE ('BST1 :');
                               ECRIRE ( Depth ( Bst1 ) ) ;
                               ECRIRE ('BST2 :');
                               ECRIRE ( Depth ( Bst2 ) ) ;
                               ECRIRE ('BST3 :');
                               ECRIRE ( Depth ( Bst3 ) ) ;
                           SINON
                               SI Choix = 6
                                   ECRIRE ('BST1 :');
                                   APPEL Inorder ( Bst1 ) ;
                                   ECRIRE ( 'BST2 :' ) ;
                                   APPEL Inorder ( Bst2 ) ;
                                   ECRIRE ( 'BST3 :' ) ;
                                   APPEL Inorder ( Bst3 ) ;
                               SINON
                                   SI Choix = 7
                                       ECRIRE ('BST1 : ');
                                       APPEL Compter_niveau ( Bst1 , X , Y , Z ) ;
                                       ECRIRE ( 'BST2 :' ) ;
                                       APPEL Compter_niveau ( Bst2 , X , Y , Z ) ;
                                       ECRIRE ( 'BST3 :' ) ;
                                       APPEL Compter_niveau ( Bst3 , X , Y , Z ) ;
                                   SINON
                                       SI Choix = 8
                                           ECRIRE ('ENTRER LE MOT A CHERCHER :');
                                           lire(cher);

                                           ECRIRE ( Search ( cher , Bst1 , Bst2 , Bst3 , X , Y , Z ) ) ;
                                       SINON
                                           SI Choix = 9
                                               ECRIRE('ENTRER LE MOT 1 :');
                                               lire(cw1);
                                               ECRIRE('ENTRER LE MOT 2 : ');
                                               lire (cw2);
                                               APPEL Search_range ( cw1 , cw2 , Bst1 , Bst2 , Bst3 ) ;
                                           SINON
                                               SI Choix = 10
                                                   ECRIRE ( 'AU REVOIR!' ) ;
                                               FSI ;
                                           FSI ;
                                       FSI ;
                                   FSI ;
                               FSI ;
                           FSI ;
                       FSI ;
                   FSI ;
               FSI ;
           FSI ;
       FTQ ;
   FIN
  /**************************************************************/
  /***************FFFFFFFFFFONCTION POUR GENERER LE FICHIER***************/
  /**************************************************************/
   ACTION Generer_fichier ( Num )
   SOIENT
       I , J , Num : ENTIER ;
       Mot : CHAINE ;
   DEBUT
       OUVRIR ( F , 'T.z' , 'N' ) ;
       POUR I := 1 , Num
           J := ALEANOMBRE ( 10 ) ;
           SI I = 0
               Mot := 'Y' + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
           SINON
               SI I = 0
                   Mot := 'Z' + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
               SINON
                   SI I = 0
                       Mot := 'a' + ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
                   SINON
                       Mot := ALEACHAINE ( ALEANOMBRE ( 5 ) + 3 ) ;
                   FSI ;
               FSI ;
           FSI ;
           INIT_STRUCT ( S , [ Mot ] ) ;
           ECRIRESEQ ( F , S ) ;
       FPOUR ;
       FERMER ( F ) ;
   FIN
  /**************************************************************/
  /***************FFFFFFFFFFONCTION POUR AFFICHER LE FICHIER***************/
  /**************************************************************/
   ACTION Ecrire_fichier
   SOIENT
       I UN ENTIER ;
   DEBUT
       OUVRIR ( F , 'T.z' , 'A' ) ;
       I := 0 ;
       TQ NON FINFICH ( F )
           LIRESEQ ( F , S ) ;
           ECRIRE ( S ) ;
           I := I + 1 ;
       FTQ ;
       FERMER ( F ) ;
       ECRIRE ( 'Compte = ' , I ) ;
   FIN
  /**************************************************************/
  /***************FFFFFFFFFFFFFFONCTION POUR INSERTER BST1********************/
  /**************************************************************/
   ACTION Insert_bst1 ( Root , X , Y , Z )
   SOIENT
       Root , To_insert UN ARB DE CHAINE ;
       Str UNE CHAINE ;
       Ch , X , Y , Z DES CAR ;
   DEBUT
       Root := NIL ;
       OUVRIR ( F , 'T.z' , 'A' ) ;
       TQ NON FINFICH ( F )
           LIRESEQ ( F , S ) ;
           Str := STRUCT ( S , 1 ) ;
           CREERNOEUD ( To_insert ) ;
           AFF_INFO ( To_insert , Str ) ;
           APPEL Insert ( Root , To_insert ) ;
           Ch := CARACT ( Str , 1 ) ;
           SI ( Ch = X ) OU ( Ch = Y ) OU ( Ch = Z )
               TANTQUE PERE ( To_insert ) # NIL
                   APPEL Retation ( To_insert ) ;
               FTQ ;
               Root := To_insert ;
           FSI ;
       FTQ ;
       FERMER ( F ) ;
   FIN
  /**************************************************************/
  /***************FFFFFFFFFFFFFFONCTION POUR INSRTER DANS L'ARB***************/
  /**************************************************************/
   ACTION Insert ( Root , To_insert )
   SOIENT
       Root , To_insert , Save UN ARB DE CHAINE ;
   DEBUT
       SI Root = NIL
           Root := To_insert ;
           AFF_PERE ( To_insert , NIL ) ;
       SINON
           SI INFO ( Root ) < INFO ( To_insert )
               SI FD ( Root ) = NIL
                   AFF_FD ( Root , To_insert ) ;
                   AFF_PERE ( To_insert , Root ) ;
               SINON
                   Save := FD ( Root ) ;
                   APPEL Insert ( Save , To_insert ) ;
               FSI ;
           SINON
               SI FG ( Root ) = NIL
                   AFF_FG ( Root , To_insert ) ;
                   AFF_PERE ( To_insert , Root ) ;
               SINON
                   Save := FG ( Root ) ;
                   APPEL Insert ( Save , To_insert ) ;
               FSI ;
           FSI ;
       FSI ;
   FIN
  /**************************************************************/
  /***************FFFFFFFFFFFFFFONCTION POUR FAIRE UNE RETATION***************/
  /**************************************************************/
   ACTION Retation ( To_insert )
   SOIENT
       To_insert , P , Q , Save UN ARB DE CHAINE ;
   DEBUT
       P := PERE ( To_insert ) ;
       Q := PERE ( P ) ;
       SI To_insert = FG ( P )
           Save := FD ( To_insert ) ;
           AFF_FD ( To_insert , P ) ;
           AFF_FG ( P , Save ) ;
           SI Save # NIL
               AFF_PERE ( Save , P ) ;
           FSI ;
           AFF_PERE ( P , To_insert ) ;
           AFF_PERE ( To_insert , Q ) ;
           SI Q # NIL
               SI P = FD ( Q )
                   AFF_FD ( Q , To_insert ) ;
               SINON
                   AFF_FG ( Q , To_insert ) ;
               FSI ;
           FSI ;
       SINON
           Save := FG ( To_insert ) ;
           AFF_FG ( To_insert , P ) ;
           AFF_FD ( P , Save ) ;
           SI Save # NIL
               AFF_PERE ( Save , P ) ;
           FSI ;
           AFF_PERE ( P , To_insert ) ;
           AFF_PERE ( To_insert , Q ) ;
           SI Q # NIL
               SI P = FD ( Q )
                   AFF_FD ( Q , To_insert ) ;
               SINON
                   AFF_FG ( Q , To_insert ) ;
               FSI ;
           FSI ;
       FSI ;
   FIN
  /**************************************************************/
  /***************FFFFFFFFFFFFFFONCTION POUR INSERTER BST3********************/
  /**************************************************************/
   ACTION Insert_bst3 ( Root , X , Y , Z )
   SOIENT
       Root , To_insert UN ARB DE CHAINE ;
       Str UNE CHAINE ;
       Ch , X , Y , Z DES CAR ;
   DEBUT
       Root := NIL ;
       OUVRIR ( F , 'T.z' , 'A' ) ;
       TQ NON FINFICH ( F )
           LIRESEQ ( F , S ) ;
           Str := STRUCT ( S , 1 ) ;
           CREERNOEUD ( To_insert ) ;
           AFF_INFO ( To_insert , Str ) ;
           APPEL Insert ( Root , To_insert ) ;
           Ch := CARACT ( Str , 1 ) ;
           SI ( Ch # X ) ET ( Ch # Y ) ET ( Ch # Z )
               TANTQUE PERE ( To_insert ) # NIL
                   APPEL Retation ( To_insert ) ;
               FTQ ;
               Root := To_insert ;
           FSI ;
       FTQ ;
       FERMER ( F ) ;
   FIN
  /**************************************************************/
  /***************FFFFFFFFFFFFFFONCTION POUR CALCULER LE DEPHT****************/
  /**************************************************************/
   FONCTION Depth_node ( To_insert ) : ENTIER
   SOIENT
       Cpt UN ENTIER ;
       P UN ARB DE CHAINE ;
       To_insert : ARB DE CHAINE ;
   DEBUT
       P := To_insert ;
       Cpt := - 1 ;
       TANTQUE P # NIL
           P := PERE ( P ) ;
           Cpt := Cpt + 1 ;
       FTQ ;
       Depth_node := Cpt ;
   FIN
  /**************************************************************/
  /***************FFFFFFFFFFONCTION POUR INSERTER BST3********************/
  /**************************************************************/
   ACTION Insert_bst2 ( Root , X , Y , Z )
   SOIENT
       Root , To_insert UN ARB DE CHAINE ;
       Str UNE CHAINE ;
       Ch , X , Y , Z DES CAR ;
       I UN ENTIER ;
   DEBUT
       Root := NIL ;
       OUVRIR ( F , 'T.z' , 'A' ) ;
       TQ NON FINFICH ( F )
           LIRESEQ ( F , S ) ;
           Str := STRUCT ( S , 1 ) ;
           CREERNOEUD ( To_insert ) ;
           AFF_INFO ( To_insert , Str ) ;
           APPEL Insert ( Root , To_insert ) ;
           Ch := CARACT ( Str , 1 ) ;
           SI ( Ch = X ) OU ( Ch = Y ) OU ( Ch = Z )
               POUR I := 1 , ( Depth_node ( To_insert ) / 2 )
                   APPEL Retation ( To_insert ) ;
               FPOUR ;
           FSI ;
           si  ( Ch > X   ) et ( Ch > Y)    et ( Ch > Z  )
               TANTQUE PERE ( To_insert ) # NIL
                    APPEL Retation ( To_insert ) ;
               ftq ;
               Root  :=  To_insert ;

           fsi ;

       FTQ ;
       FERMER ( F ) ;
   FIN
  /**************************************************************/
  /***************FFFFFFFFFFONCTION POUR CALCULER LES MOTS****************/
  /**************************************************************/
   FONCTION Conter_mot ( Root , X , Y , Z ) : ENTIER
   SOIENT
       Root UN ARB DE CHAINE ;
       Cpt UN ENTIER ;
       X , Y , Z DES CAR ;
   DEBUT
       SI Root = NIL
           Conter_mot := 0
       SINON
           SI ( CARACT ( INFO ( Root ) , 1 ) = X ) OU ( CARACT ( INFO ( Root ) , 1 ) = Y ) OU ( CARACT ( INFO ( Root )
           , 1 ) = Z )
               Cpt := Conter_mot ( FD ( Root ) , X , Y , Z ) + Conter_mot ( FG ( Root ) , X , Y , Z ) + 1 ;
           SINON
               Cpt := Conter_mot ( FD ( Root ) , X , Y , Z ) + Conter_mot ( FG ( Root ) , X , Y , Z ) ;
           FSI ;
           Conter_mot := Cpt ;
       FSI ;
   FIN
  /**************************************************************/
  /***************FFFFFFFONCTION POUR CALCULER le depht****************/
  /**************************************************************/
   FONCTION Depth ( Root ) : ENTIER
   SOIENT
       Root UN ARB DE CHAINE ;
       Prf UN ENTIER ;
   DEBUT
       SI Root = NIL
           Depth := - 1 ;
       SINON
           Depth := MAX ( Depth ( FD ( Root ) ) , Depth ( FG ( Root ) ) ) + 1 ;
       FSI ;
   FIN
  /**************************************************************/
  /***************FFFFFFONCTION POUR INORDER TRAVERSAL****************/
  /**************************************************************/
   ACTION Inorder ( Root )
   SOIENT
       Root UN ARB DE CHAINE ;
   DEBUT
       SI Root # NIL
           APPEL Inorder ( FG ( Root ) ) ;
           ECRIRE ( INFO ( Root ) ) ;
           APPEL Inorder ( FD ( Root ) ) ;
       FSI ;
   FIN
  /**************************************************************/
  /***************FFFFFFONCTION POUR CONTER PAR NIVEAU****************/
  /**************************************************************/
   ACTION Compter_niveau ( Root , X , Y , Z )
   SOIENT
       Root , P UN ARB DE CHAINE ;
       Queue1 UNE FILE DE ENTIER ;
       Queue2 UNE FILE DE ARB DE CHAINE ;
       Prev UN ENTIER ;
       Cpt , Val UN ENTIER ;
       X , Y , Z DES CAR ;
   DEBUT
       si Root<>nil
       Prev := 0 ;
       Cpt := 0 ;
       CREERFILE ( Queue1 ) ;
       CREERFILE ( Queue2 ) ;
       ENFILER ( Queue2 , Root ) ;
       ENFILER ( Queue1 , 0 ) ;
       TANTQUE NON FILEVIDE ( Queue2 )
           DEFILER ( Queue2 , P ) ;
           DEFILER ( Queue1 , Val ) ;
           SI Val > Prev
               ECRIRE('LEVEL NUMBER ',Prev,':');
               Prev := Prev + 1 ;
               ECRIRE ( Cpt ) ;
               Cpt := 0 ;
           FSI ;
           SI ( CARACT ( INFO ( P ) , 1 ) = X ) OU ( CARACT ( INFO ( P ) , 1 ) = Y ) OU ( CARACT ( INFO ( P ) , 1 ) =
           Z )
               Cpt := Cpt + 1 ;
           FSI ;
           SI FG ( P ) # NIL
               ENFILER ( Queue2 , FG ( P ) ) ;
               ENFILER ( Queue1 , Val + 1 ) ;
           FSI ;
           SI FD ( P ) # NIL
               ENFILER ( Queue2 , FD ( P ) ) ;
               ENFILER ( Queue1 , Val + 1 ) ;
           FSI ;
       FTQ ;
       ECRIRE('LEVEL NUMBER ',Prev,':');
       ECRIRE ( Cpt ) ;
       fsi;
   FIN
  /**************************************************************/
  /***************       FONCTION POUR chercher bst1  ****************/
  /**************************************************************/
   FONCTION Search_bst1 ( Root , Ch , X , Y , Z ) : BOOLEEN
   SOIENT
       Root UN ARB DE CHAINE ;
       Ch UNE CHAINE ;
       X , Y , Z DES CAR ;
   DEBUT
       SI ( Root = NIL )
           Search_bst1 := FAUX ;
       SINON
           SI ( CARACT ( INFO ( Root ) , 1 ) # X ) ET ( CARACT ( INFO ( Root ) , 1 ) # Y ) ET ( CARACT ( INFO ( Root )
           , 1 ) # Z )
               Search_bst1 := FAUX ;
           SINON
               SI ( Ch = INFO ( Root ) )
                   Search_bst1 := VRAI ;
               SINON
                   SI ( Ch < INFO ( Root ) )
                       Search_bst1 := Search_bst1 ( FG ( Root ) , Ch , X , Y , Z ) ;
                   SINON
                       Search_bst1 := Search_bst1 ( FD ( Root ) , Ch , X , Y , Z ) ;
                   FSI ;
               FSI ;
           FSI ;
       FSI ;
   FIN
  /**************************************************************/
  /***************       FONCTION POUR chercher bst2  ****************/
  /**************************************************************/
   FONCTION Search_bst2 ( Root , Ch , X , Y , Z ) : BOOLEEN
   SOIENT
       Root UN ARB DE CHAINE ;
       Ch UN CHAINE ;
       X , Y , Z DES CAR ;
   DEBUT
       SI ( Root = NIL )
           Search_bst2 := FAUX ;
       SINON
           si (  Caract ( Info( Root ) , 1 )< X   ) et ( Caract ( Info ( Root ) , 1 )< Y  )
             et ( Caract ( Info ( Root ) , 1 )< Z   )
            Search_bst2  :=  Faux ;
         sinon
           SI ( Ch = INFO ( Root ) )
               Search_bst2 := VRAI ;
           SINON
               SI ( Ch < INFO ( Root ) )
                   Search_bst2 := Search_bst2 ( FG ( Root ) , Ch , X , Y , Z ) ;
               SINON
                   Search_bst2 := Search_bst2 ( FD ( Root ) , Ch , X , Y , Z ) ;
               FSI ;
           FSI ;
         FSI ;
       FSI;
   FIN
  /**************************************************************/
  /***************       FONCTION POUR chercher bst3  ****************/
  /**************************************************************/
   FONCTION Search_bst3 ( Root , Ch , X , Y , Z ) : BOOLEEN
   SOIENT
       Root UN ARB DE CHAINE ;
       Ch UN CHAINE ;
       X , Y , Z DES CAR ;
   DEBUT
       SI ( Root = NIL )
           Search_bst3 := FAUX ;
       SINON
           SI ( CARACT ( INFO ( Root ) , 1 ) = X ) OU ( CARACT ( INFO ( Root ) , 1 ) = Y ) OU ( CARACT ( INFO ( Root )
           , 1 ) = Z )
               Search_bst3 := FAUX ;
           SINON
               SI ( Ch = INFO ( Root ) )
                   Search_bst3 := VRAI ;
               SINON
                   SI ( Ch < INFO ( Root ) )
                       Search_bst3 := Search_bst3 ( FG ( Root ) , Ch , X , Y , Z ) ;
                   SINON
                       Search_bst3 := Search_bst3 ( FD ( Root ) , Ch , X , Y , Z ) ;
                   FSI ;
               FSI ;
           FSI ;
       FSI ;
   FIN
  /**************************************************************/
  /***************         FONCTION POUR chercher     ****************/
  /**************************************************************/
   FONCTION Search ( Word , Root1 , Root2 , Root3 , X , Y , Z ) : BOOLEEN
   SOIENT
       Word UNE CHAINE ;
       Root1 , Root2 , Root3 UNE ARB DE CHAINE ;
       X , Y , Z DES CAR ;
   DEBUT
       SI ( CARACT ( Word , 1 ) = X ) OU ( CARACT ( Word , 1 ) = Y ) OU ( CARACT ( Word , 1 ) = Z )
           Search := Search_bst1 ( Root1 , Word , X , Y , Z ) ;
       SINON
           SI ( CARACT ( Word , 1 ) > X ) OU ( CARACT ( Word , 1 ) > Y ) OU ( CARACT ( Word , 1 ) > Z )
               Search := Search_bst2 ( Root2 , Word , X , Y , Z ) ;
           SINON
               Search := Search_bst3 ( Root3 , Word , X , Y , Z ) ;
           FSI ;
       FSI ;
   FIN
  /**************************************************************/
  /************   FONCTION POUR chercher in a range  **************/
  /**************************************************************/
   ACTION Search_range ( Word1 , Word2 , Bst1 , Bst2 , Bst3 )
   SOIENT
       Bst1 , Bst2 , Bst3 UN ARB DE CHAINE ;
       Word1 , Word2 DES CHAINE ;
   DEBUT
       SI ( ( CARACT ( Word1 , 1 ) = X ) OU ( CARACT ( Word1 , 1 ) = Y ) OU ( CARACT ( Word1 , 1 ) = Z ) ) ET ( (
       CARACT ( Word2 , 1 ) = X ) OU ( CARACT ( Word2 , 1 ) = Y ) OU ( CARACT ( Word2 , 1 ) = Z ) )
           APPEL Range_bst1 ( Bst1 , Word1 , Word2 ) ;
       SINON
           SI ( (  CARACT ( Word2 , 1 ) < X ) ET ( CARACT ( Word2 , 1 ) < Y ) et ( CARACT ( Word2 , 1 ) < Z ) )
               APPEL Range_bst3 ( Bst3 , Word1 , Word2 ) ;
           SINON
               si ( (CARACT ( Word1 , 1 ) > X ) ET ( CARACT ( Word1 , 1 ) > Y ) ET ( CARACT ( Word1 , 1 ) > Z ) )
                 APPEL Range_bst22( Bst2 , Word1 , Word2);
               sinon
                 APPEL Range_bst2 ( Bst2 , Word1 , Word2 ) ;
               fsi;
           FSI ;
       FSI ;
   FIN
  /**************************************************************/
  /************   FONCTION POUR chercher a range bst1**************/
  /**************************************************************/
   ACTION Range_bst1 ( Root , Word1 , Word2 )
   SOIENT
       Root UN ARB DE CHAINE ;
       Word1 , Word2 DES CHAINE ;
   DEBUT
       SI ( Root # NIL )
           SI ( ( CARACT ( INFO ( Root ) , 1 ) = X ) OU ( CARACT ( INFO ( Root ) , 1 ) = Y ) OU ( CARACT ( INFO ( Root
           ) , 1 ) = Z ) )
               SI ( INFO ( Root ) > Word1 )
                   APPEL Range_bst1 ( FG ( Root ) , Word1 , Word2 ) ;
               FSI ;
               SI ( INFO ( Root ) >= Word1 ) ET ( INFO ( Root ) <= Word2 )
                   ECRIRE ( INFO ( Root ) ) ;
               FSI ;
               SI ( INFO ( Root ) < Word2 )
                   APPEL Range_bst1 ( FD ( Root ) , Word1 , Word2 ) ;
               FSI ;
           FSI ;
       FSI ;
   FIN
  /**************************************************************/
  /************   FONCTION POUR chercher a range bst1**************/
  /**************************************************************/
   ACTION Range_bst3 ( Root , Word1 , Word2 )
   SOIENT
       Root UN ARB DE CHAINE ;
       Word1 , Word2 DES CHAINE ;
   DEBUT
       SI ( Root # NIL )
           SI ( ( CARACT ( INFO ( Root ) , 1 ) # X ) ET ( CARACT ( INFO ( Root ) , 1 ) # Y ) ET ( CARACT ( INFO ( Root
           ) , 1 ) # Z ) )
               SI ( INFO ( Root ) > Word1 )
                   APPEL Range_bst3 ( FG ( Root ) , Word1 , Word2 ) ;
               FSI ;
               SI ( INFO ( Root ) >= Word1 ) ET ( INFO ( Root ) <= Word2 )
                   ECRIRE ( INFO ( Root ) )
               FSI ;
               SI ( INFO ( Root ) < Word2 )
                   APPEL Range_bst3 ( FD ( Root ) , Word1 , Word2 ) ;
               FSI ;
           FSI ;
       FSI ;
   FIN
  /**************************************************************/
  /************   FONCTION POUR chercher a range bst2**************/
  /**************************************************************/
   ACTION Range_bst2 ( Root , Word1 , Word2 )
   SOIENT
       Root UN ARB DE CHAINE ;
       Word1 , Word2 DES CHAINE ;
   DEBUT
       SI ( Root # NIL )
           SI ( INFO ( Root ) > Word1 )
               APPEL Range_bst2 ( FG ( Root ) , Word1 , Word2 ) ;
           FSI ;
           SI ( INFO ( Root ) >= Word1 ) ET ( INFO ( Root ) <= Word2 )
               ECRIRE ( INFO ( Root ) )
           FSI ;
           SI ( INFO ( Root ) < Word2 )
               APPEL Range_bst2 ( FD ( Root ) , Word1 , Word2 ) ;
           FSI ;
       FSI ;
   FIN
   /**************************************************************/
  /************   FONCTION POUR chercher a range bst2**************/
  /**************************************************************/
   ACTION Range_bst22 ( Root , Word1 , Word2 )
   SOIENT
       Root UN ARB DE CHAINE ;
       Word1 , Word2 DES CHAINE ;
   DEBUT
       SI ( Root # NIL )
       si ( (CARACT ( INFO ( Root ) , 1 ) >= X ) ou ( CARACT ( INFO ( Root ) , 1 ) >= Y ) ou ( CARACT ( INFO ( Root
           ) , 1 ) >= Z ) )
           SI ( INFO ( Root ) > Word1 )
               APPEL Range_bst22 ( FG ( Root ) , Word1 , Word2 ) ;
           FSI ;
           SI ( INFO ( Root ) >= Word1 ) ET ( INFO ( Root ) <= Word2 )
               ECRIRE ( INFO ( Root ) )
           FSI ;
           SI ( INFO ( Root ) < Word2 )
               APPEL Range_bst22 ( FD ( Root ) , Word1 , Word2 ) ;
           FSI ;
       FSI ;
       fsi;
   FIN
