
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

/********************************************************************************************************/

typedef struct Logement { // structure pour un logement
    int id_logement;
    char type[10];  // "studio", "f2", "f3", "f4"
    float superficie;
    char quartier[50];
    float distance;
    float loyer;
    bool etat ;// ocuppe ou non true if occupe
    struct Logement *suivant; // pointeur pour LLC
} Logement;

/********************************************************************************************************/

typedef struct Locataire {// structure pour un locataire
    int id_locataire;
    char nom[20];
    char prenom[20];
    char telephone[15];
    struct Locataire *suivant; // pointeur pour LLC
} Locataire;

/********************************************************************************************************/

typedef struct Location {// structure pour une location
    int id_location;
    int id_locataire;
    int id_logement;
    int date_debut; // AAAAMMJJ
    int date_fin;   // AAAAMMJJ
    struct Location *suivant;
} Location;

/********************************************************************************************************/

float calculer_loyer(char type[], float superficie) {// fonction pour calculer le loyer
    float LB, SM;
    if (strcmp(type, "studio") == 0) { LB = 15000; SM = 20; }
    else if (strcmp(type, "f2") == 0) { LB = 20000; SM = 45; }
    else if (strcmp(type, "f3") == 0) { LB = 30000; SM = 65; }
    else if (strcmp(type, "f4") == 0) { LB = 45000; SM = 85; }
    // on compare le type par (studio f2 f3 f4) pour initialiser LB et SM
    else { return -1; } // le type doit etre bien ecrit si non loyer = -1
    return (LB + (superficie - SM) * 800);
}

/********************************************************************************************************/

// gerer les logements :

//ajouter un logement au fichier des logements
void logement_fichier(Logement *nouveau){
    FILE *file = fopen("logement_fichier.txt", "a");//pointer pour le fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");//afficher en cas de l'erreur
    }
    //remplir une ligne du fichier avec les info du logement
    fprintf(file,"%d %s %.2f %s %.2f %.2f %d\n",nouveau->id_logement, nouveau->type, nouveau->superficie,
                                         nouveau->quartier, nouveau->distance, nouveau->loyer, nouveau->etat);
    fclose(file)  ; //fermer le fichier                     
 }

 /********************************************************************************************************/

//ajouter un logement au fichier des logements archive
void logement_archive(Logement *nouveau){
    FILE *file = fopen("logement_archive.txt", "a");//pointer du fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");//en cas d'ereur
    }
   //Ajouter une ligne des infos d'un logement suprime au fichier archive
    fprintf(file,"%d %s %.2f %s %.2f %.2f %d\n",nouveau->id_logement, nouveau->type, nouveau->superficie,
                                         nouveau->quartier, nouveau->distance, nouveau->loyer, nouveau->etat);
    fclose(file) ;  //fermer le fichier                    
 }
 
 /********************************************************************************************************/
 // ce module est pour suprimer une informatoin du fichier apres etre suprimer dans la liste
void suprimer_logement_fichier(Logement *nouveau){
    FILE *file = fopen("logement_fichier.txt", "w");//pointer pour le fichier en mode w pour effacer le contenu initial 
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");// si il y a une erreur
    }

 while(nouveau!=NULL){//remplir le fichier a paritr du cintenu de la liste donc le logement suprime ne sera pas ajouter au fichier
    fprintf(file,"%d %s %.2f %s %.2f %.2f %d\n",nouveau->id_logement, nouveau->type, nouveau->superficie,
                                         nouveau->quartier, nouveau->distance, nouveau->loyer, nouveau->etat); 
    nouveau=nouveau->suivant;
 } 

 fclose(file)  ;     //fermer le fichier              
}
 /********************************************************************************************************/

//ajouter un locataire au fichier des locataires
 void locataire_fichier(Locataire *nouveau){
    FILE *file = fopen("locataire_fichier.txt", "a");//pointer pour un fichier
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");//cas d'erreur
    }
    //remplir le fichier
     fprintf(file, "%d %s %s %s\n",nouveau->id_locataire, nouveau->nom, nouveau->prenom, nouveau->telephone);
     fclose(file);//fermer le fichier
 }

 /********************************************************************************************************/
//ajouter un locataire au fichier des locataires archive
 void locataire_archive(Locataire *nouveau){
    FILE *file = fopen("locataire_archive.txt", "a");//pointer pour le fichier
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");//cas d'erreur
    }
    //remplir le fichier
     fprintf(file, "%d %s %s %s\n",nouveau->id_locataire, nouveau->nom, nouveau->prenom, nouveau->telephone);
     fclose(file);//fermer le fichier
 }

 /********************************************************************************************************/
 // ce module est pour suprimer une informatoin du fichier apres etre suprimer dans la liste
void suprimer_locataire_file(Locataire *nouveau){
    FILE *file = fopen("locataire_fichier.txt", "w");//pointer pour le fichier en mode w
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");//cas d'erreur
    }
 while(nouveau!=NULL){//remplir le fichier de nouveau sans ajouter le locatair suprime
    fprintf(file, "%d %s %s %s\n",nouveau->id_locataire, nouveau->nom, nouveau->prenom, nouveau->telephone);
    nouveau=nouveau->suivant;
 } 
 fclose(file)  ; //fermer le fichier                  
}

 /********************************************************************************************************/
//ajouter une location au fichier des locations
 void location_fichier(Location *nouveau){
    FILE *file = fopen("location_fichier.txt", "a");//pointer pour le fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");//cas d'erreur
    }
    //remplir le fichier
    fprintf(file,"%d %d %d %d %d\n",nouveau->id_location, nouveau->id_locataire, nouveau->id_logement, 
                                nouveau->date_debut,nouveau->date_fin);
 
      fclose(file);//fermer le fichier
 }

 /********************************************************************************************************/

 //ajouter une location au fichier des locations archive
 void location_archive(Location *nouveau){
    FILE *file = fopen("location_archive.txt", "a");//pointer de fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");//erreur
    }

    //remlir le fichier
    fprintf(file,"%d %d %d %d %d\n",nouveau->id_location, nouveau->id_locataire, nouveau->id_logement, 
                                nouveau->date_debut,nouveau->date_fin);
 fclose(file);//fermer le fichier
 }

  /********************************************************************************************************/
 // ce module est pour suprimer une informatoin du fichier apres etre suprimer dans la liste
void suprimer_location_file(Location *nouveau){
    FILE *file = fopen("location_fichier.txt", "w");//pointer de fichier en mode w
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");//erreur
    }
 while(nouveau!=NULL){
    //remplir le fichier a zero
    fprintf(file,"%d %d %d %d %d\n",nouveau->id_location, nouveau->id_locataire, nouveau->id_logement, 
        nouveau->date_debut,nouveau->date_fin);
    nouveau=nouveau->suivant;
 } 
 fclose(file)  ; //fermer le fichier                  
}

 /********************************************************************************************************/

 void ajouter_logement(Logement **liste) {
    Logement *nouveau = (Logement*) malloc(sizeof(Logement));//allouer une case memoire
    if (nouveau==NULL) {
        printf("Erreur\n"); // verification si allouer a ete bien utilise (LLC)
    }
    int id;  
    bool id_existe; // pour la verification de l'existance de id
    do {
        id_existe = false; // initializer a false 
        printf("Entrez l'id du logement : ");
        scanf("%d", &id);
        // verifier si id existe deja
        Logement *temp = *liste;
        while (temp != NULL) {
            if (temp->id_logement == id) {
                id_existe = true;
                printf("id %d est deja utilise , veuillez entrer un autre id \n", id);
                break;
            }
            temp = temp->suivant;
        }
    } while (id_existe); // repeter jusqu'a un id unique entre

    nouveau->id_logement = id;

    printf("Entrez le type de logement (studio, f2, f3, f4 NO UPPERCASE LETTERS) : ");
    scanf("%s", nouveau->type);
    printf("Entrez la superficie en m2 : ");
    scanf("%f", &nouveau->superficie);
    printf("Entrez le quartier : ");
    scanf("%s", nouveau->quartier);
    printf("Entrez la distance jusqu'a la commune : ");
    scanf("%f", &nouveau->distance);
    nouveau->etat = false; // initialiser l'etat
    nouveau->loyer = calculer_loyer(nouveau->type, nouveau->superficie); // Calculer le loyer
    nouveau->suivant = *liste;
    *liste = nouveau;

    printf("Logement ajoute avec succes, Loyer = %.2f DA\n", nouveau->loyer);
    logement_fichier(*liste); // ajouter au fichier
}
 

/********************************************************************************************************/

void supprimer_logement(Logement **liste, Logement **archive, int id) {// 2 - supprimer un logement et l'archiver
    Logement *temp = *liste, *prev = NULL;//initialiser le curent et le previous pointers
    while (temp != NULL && temp->id_logement != id) {//chercher le logement a suprimer
        prev = temp;
        temp = temp->suivant;
    }
    if (temp == NULL) {//cas en trouve pas
        printf("Logement non trouve \n");
        return;
    }
    // retirer de la liste principale
    if (prev == NULL) *liste = temp->suivant;
    else prev->suivant = temp->suivant;
    // ajouter à la liste archive
    temp->suivant = *archive;
    *archive = temp;
    printf(" Logement id :  %d supprime et archive \n", id);
    logement_archive(*archive);//ajouter au liste des archive
    suprimer_logement_fichier(*liste);//suprimer du list des logements
}

/********************************************************************************************************/

void afficher_logement(Logement *liste){//afficher un logement
    Logement *temp=liste;
    printf("\n*********************************************************************************************************************\n");
    printf("ID: %d |TYPE: %s |SUPEFICIE: %.2f m2|QUARTIER: %s|DISTANCE : %.2f km|LOYER: %.2f DA| ",
        temp->id_logement, temp->type, temp->superficie,
        temp->quartier, temp->distance, temp->loyer);
        if (temp->etat ==true)printf("le logement est occupe");
        else printf("le logement est libre");     
}
/********************************************************************************************************/

void afficher_par_id(Logement *liste,int id){//afficher par id 
    Logement *temp=liste;
    while(temp!=NULL){
        if (temp->id_logement==id){afficher_logement(temp);
          break;//on sort si on trouve le logement
        }
        temp=temp->suivant;//le suivant pointer
    }
}

/********************************************************************************************************/

void afficher_logements(Logement *liste) {// 3 - afficher les logements
    printf("\n liste des logements :");
    int cpt=0;
    while (liste != NULL) {//afficher les logement jusque a la fin
       afficher_logement(liste);
        liste = liste->suivant; // l'affichage des logements a partir de la liste
        cpt++; 
    }
    printf("\n***********************************************************************************************************************\n");
    printf("\nLe nombre est : %d \n ",cpt);

}

/********************************************************************************************************/

void supprimer_type_logement(Logement **liste, Logement **archive, char type[]) {// 4 - supprimer un type de logement :
    Logement *temp = *liste, *prev = NULL;
    bool found = false; // Pour verifier si au moins un logement a ete supprime
    while (temp != NULL) {
        if (strcmp(temp->type, type) == 0) {
            Logement *a_supprimer = temp;
            found = true; // un logement du type specifie a ete trouve

            if (prev == NULL) {
                *liste = temp->suivant; // suppression en tete de liste
            } else {
                prev->suivant = temp->suivant;
            }

            temp = temp->suivant; // passer au suivant avant de supprimer l'actuel
            // ajouter a la liste archive
            a_supprimer->suivant = *archive;
            *archive = a_supprimer;
            logement_archive(*archive);// a chaque fois on ajoute au fichier de larchive
            printf("logement de type %s supprime et archive \n", type);
        } else {//on passe au suivant
            prev = temp;
            temp = temp->suivant;
        }
    }
    if (found==false) {//en cas il ya aucan logement
        printf("aucun logement du type %s trouve \n", type);
    }
    suprimer_logement_fichier(*liste);//actiualiser le fichier
}

/********************************************************************************************************/

// gerer les locataires
void ajouter_locataire(Locataire **liste) {
    Locataire *nouveau = (Locataire*) malloc(sizeof(Locataire));
    if (nouveau==NULL) {
        printf("Erreur\n"); //verification si allouer a ete bien utilise 
    }
    int id;
    bool id_existe; // pour la verification de l'existance de id
    do {
        id_existe = false; // initializer a false 
        printf("Entrez l'id du locataire : ");
        scanf("%d", &id);
        // verifier si l'id existe deja
        Locataire *temp = *liste;
        while (temp != NULL) {
            if (temp->id_locataire == id) {
                id_existe = true;
                printf("id %d est deja utilise, Veuillez entrer un autre id\n", id);
                break;
            }
            temp = temp->suivant;
        }
    } while (id_existe); // repeter jusqu'un id unique entre

    nouveau->id_locataire = id;
    printf("Entrez le nom : ");
    scanf("%s", nouveau->nom);
    printf("Entrez le prenom : ");
    scanf("%s", nouveau->prenom);
    printf("Entrez le telephone : ");
    scanf("%s", nouveau->telephone);
    nouveau->suivant = *liste;
    *liste = nouveau;

    printf("Locataire ajoute avec succes\n");
    locataire_fichier(*liste); // Ajouter au fichier
}

/********************************************************************************************************/

void supprimer_locataire(Locataire **liste, Locataire **archive, int id) {// 2 - supprimer un locataire et l'archiver :
    Locataire *temp = *liste, *prev = NULL;
    while (temp != NULL && temp->id_locataire != id) {//chercher le locataire a suprimer
        prev = temp;
        temp = temp->suivant;
    }
    if (temp == NULL) {
        printf("Locataire non trouve !\n"); // cas de saisir un id invalide
        return;
    }
 // retirer de la liste principale
    if (prev == NULL) *liste = temp->suivant;
    else prev->suivant = temp->suivant;

    // ajouter à l'archive
    temp->suivant = *archive;
    *archive = temp;
     printf("Locataire id : %d supprime et archive \n", id);

     locataire_archive(*archive);//ajouter au archive
     suprimer_locataire_file(*liste);//suprimer du fichier des locataires
}/********************************************************************************************************/

// gerer les locations :
void changer_letat(Logement *liste ,int id,bool state){// acceder a un logement avec l'id pour changer l'etat
    Logement *temp=liste;
    while(temp!=NULL){
        if (temp->id_logement==id){temp->etat=state;//changer l'etat
            break;
        }
        else temp=temp->suivant;
    }
}

/********************************************************************************************************/

void ajouter_location(Location **liste,Logement *logements) {// 1 - ajouter une location
    Location *nouvelle = (Location*) malloc(sizeof(Location));//alouer une case memoire
    if (nouvelle==NULL) {
        printf("erreur d'allocation memoire !\n");
    }
    //remplir les informations
    printf("Entrez l'ID de la location : ");
    scanf("%d", &nouvelle->id_location);
    printf("Entrez l'ID du locataire : ");
    scanf("%d", &nouvelle->id_locataire);
    printf("Entrez l'ID du logement : ");
    scanf("%d", &nouvelle->id_logement);
    printf("Entrez la date de debut (AAAAMMJJ) : ");
    scanf("%d", &nouvelle->date_debut);
    printf("Entrez la date de fin (AAAAMMJJ) : ");
    scanf("%d", &nouvelle->date_fin);
    changer_letat(logements ,nouvelle->id_logement ,true);
    nouvelle->suivant = *liste;
    *liste = nouvelle;

    printf("Location ajoutee avec succes !\n");
    location_fichier(*liste);//ajouter au fichier
    suprimer_logement_fichier(logements);//pour changer l'etat
}/********************************************************************************************************/

void supprimer_location(Location **liste, Location **archive, int id,Logement *logements) {// 2 - supprimer_location
    Location *temp = *liste, *prev = NULL;

    while (temp != NULL && temp->id_location != id) {//chercher la location a suprimer
        prev = temp;
        temp = temp->suivant;
    }

    if (temp == NULL) {//cas non  trouve
        printf("Location non trouee !\n");
        return;
    }

    if (prev == NULL) *liste = temp->suivant;
    else prev->suivant = temp->suivant;

    temp->suivant = *archive;
    *archive = temp;
    changer_letat(logements ,temp->id_logement ,false);//changer l'etat a libre
    printf("Location id :  %d supprimee et archivee !\n", id);
    location_archive(*archive);//ajouter au fichier archive 
    suprimer_location_file(*liste);//suprimer du fichier des locations
    suprimer_logement_fichier(logements);//pour changer l'etat

}

/********************************************************************************************************/

void afficher_occupe(Logement *liste){//afficher les logements occupes
    Logement *temp=liste;
    int cpt=0; 
    while(temp!=NULL){
        if(temp->etat==true){
            afficher_logement(temp);//afficher le logement en cas occupe
            cpt++;//incrementer le compteur
        }
        temp=temp->suivant;
    }
    if (cpt==0)printf("Il ne y a pas des logements occupe");
}

/********************************************************************************************************/

void afficher_libre(Location *list,Logement *liste){// affichet les logements libres a un moment donnee
   int date;
    printf("\n enter the date (AAAAMMJJ) :");
    scanf("%d",&date);
    Logement *save= liste;
    while(liste!=NULL){
        if(liste->etat==false)afficher_logement(liste);//afficher les logement libre du debut
        liste=liste->suivant;
    }
    while(list!=NULL){//afficher les logement occupe mais seront liber au moment donnee
        //comparer la date
        if (list->date_fin<date)afficher_par_id(save,list->id_logement);
        list=list->suivant;
    }
}

/********************************************************************************************************/

void afficher_locataire(Locataire *locataire){//afficher un locataire
    printf("***************************************************************************\n");
    printf("ID Locataire: %d | Nom: %s | Prenom: %s | Telephone: %s\n", 
        locataire->id_locataire, locataire->nom, locataire->prenom, locataire->telephone);
}

/********************************************************************************************************/

void afficher_locataires(Locataire *liste){
    int cpt =0 ;
    while(liste!=NULL){//afficher les locataires
        afficher_locataire(liste);
        liste=liste->suivant;
        cpt++;
    }
    printf("\nLe nombre est : %d \n",cpt);
}

/********************************************************************************************************/

void afficher_locataires_superficie(Location *locations, Logement *logements, Locataire *locataires) {
    printf("\nLocataires occupant un logement avec une superficie superieure a la moyenne :\n");
    Location *loc = locations;
    while (loc != NULL) {
        Logement *log = logements;
        while (log != NULL) {
            if (log->id_logement == loc->id_logement) {
                float moyenne; //chercher le type
                if (strcmp(log->type, "studio") == 0) moyenne = 20;
                else if (strcmp(log->type, "f2") == 0) moyenne = 45;
                else if (strcmp(log->type, "f3") == 0) moyenne = 65;
                else if (strcmp(log->type, "f4") == 0) moyenne = 85;
                else continue; 
                if (log->superficie > moyenne) {
                    Locataire *locataire = locataires;
                    while (locataire != NULL) {
                        if (locataire->id_locataire == loc->id_locataire) {
                            afficher_locataire(locataire);//afficher le locataire
                        }
                        locataire = locataire->suivant;
                    }
                }
            }
            log = log->suivant;
        }
        loc = loc->suivant;
    }
}

/********************************************************************************************************/
//this module give as the type when we give it an id 1 for studio 2 for f2 3and4 for f3 and f4
int the_type( Logement *log,int id){
    int result=0;
    while(log!=NULL){
       if (log->id_logement==id){//on compare pour savoir le type
        if (strcmp(log->type, "studio") == 0)result=1;
        if (strcmp(log->type, "f2") == 0) result=2;
        if (strcmp(log->type, "f3") == 0) result=3;
        if (strcmp(log->type, "f4") == 0) result=4;
       }
       log=log->suivant;
    }
    return result;//donner le resultat qui sera le type 1 for studio 2 for f2 3and4 for f3 and f4
   }
   
   /********************************************************************************************************/
//this module split a type of logement from the main list
 void location_type(Location **location,Location **kind,int type,Logement *logements){
    Location *prev=NULL;
    Location *save=*location;
     while(save!=NULL){ 
        if(the_type(logements,save->id_logement)==type){//comparer le type
          if(prev==NULL){//cas la tete du liste est du type
           *location=save->suivant;
           save->suivant=*kind;
           //on prend la node a l'autre liste
           *kind=save;
           save=*location;
          }
          else{//cas au melieu ou fin
             prev->suivant=save->suivant;
             save->suivant=*kind;
            //on prend la node a l'autre liste
             *kind=save;
             save=prev->suivant;
          }
         }
         else{//si c'est pas le type
              prev=save;
              save=save->suivant;
         }
     }
    }
    
/********************************************************************************************************/

// THIS MODULE GIVES YOU THE RENT USING THE ID 
int rent(struct Logement *log,int id){
    int result=0;
    while(log!=NULL){
       if (log->id_logement==id){//compare the id
         result=log->loyer;
          break;//sortir de la loop
       }
       log=log->suivant;
    }
    return result;
 }

/********************************************************************************************************/
//this module give us the pointer and the previous pointer of the highest rent in the list
void highest_rent(Location *list,Location **prec,Location **proch,Logement *log){
      Location  *prev=NULL;
      int save=0;
    while(list!=NULL){
         if (rent(log,list->id_logement)>save){//comparer le loyer
          save=rent(log,list->id_logement);
          *prec=prev;//save the pointers
          *proch=list;
         }
         prev=list;
         list=list->suivant;
      }
   }

/********************************************************************************************************/
//this module sort location list bu rent
void sort_location(Location **list,Logement *log){
    Location *prec=NULL;//initialiser les pointer
    Location *proch=NULL;
    Location *save=NULL;//pour la new liste
    while(*list!=NULL){
       highest_rent(*list,&prec,&proch,log);//prendre le plus grand
       if(prec==NULL){//cas tete de la liste
          *list=proch->suivant;
          proch->suivant=save;
          save=proch;//la metre dans la new liste
       }
       else{
          prec->suivant=proch->suivant;
          proch->suivant=save;
          save=proch;//la metre dans la new liste
       }
    }
    *list=save;
}
 
/********************************************************************************************************/
//ce module pour fusionner des sortesd lists
void merge_location(Location **list, Location **other, Logement *log) {
    Location *result = NULL;  // tete de la merged liste une new liste
    Location *last = NULL;   //fin de la merged liste  
    while (*list != NULL && *other != NULL) {
        Location *save = NULL;
        if (rent(log, (*list)->id_logement)<rent(log,(*other)->id_logement)) {//comparer le loyer
         save = *list;
        *list = (*list)->suivant;  
        } 
        else {//on prend la plus petite dans la nouvele list
         save = *other;
         *other = (*other)->suivant;  
        }
        if (result == NULL) {
         //la rendre la tete
         result = save;
        } 
        else {
         //l'ajouter a la liste 
         last->suivant = save;
        }
        last = save;  
    }
    //quand une liste est finie
    if (*other==NULL) {//si other est finie
       if (result==NULL) {
        //rendre la tete
        result = *list;
       } 
       else {
         //ajouter a la liste
         last->suivant = *list;
        }
    }   
    if (*list==NULL) {//si list est finie
     if (result == NULL) {
         //ajouter a la tete
         result = *other;
        } else {
            //l'ajouter a la liste
           last->suivant = *other;
        }
    }
    *list = result;//pour rendre le resultat
}

/********************************************************************************************************/

void afficher_location(Location *list){//afficher les locations
    int cpt = 0;
    while(list!=NULL){
     printf("\n**************************************************************************************");
     printf("\nId location : %d \nId logement : %d\nId locataire :%d\nDate de debut : %d\nDate de fin :%d\n",
        list->id_location,list->id_logement,list->id_locataire,list->date_debut,list->date_fin);
     list=list->suivant;//la suivante location
     cpt++;
    }
    printf("**************************************************************************************\n");
    printf("Le nombre est : %d \n",cpt);
 }

 /********************************************************************************************************/

//rempir la liste des logements depuit le fichier
void file_logement(Logement **list) {
    FILE *file = fopen("logement_fichier.txt", "r");//pointeur vers le fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");//error
    }
    while (!feof(file)) {//jusque la fin du fichier
        Logement *nouveau = (Logement*) malloc(sizeof(Logement));//allouer une memoire
        if (nouveau==NULL) {
            printf("Erreur d'allocation mémoire\n");
            fclose(file); // fermer le fichier
        }
        // remplir la liste depuis le fichier
        int result = fscanf(file, "%d %s %f %s %f %f %d",
                            &nouveau->id_logement, nouveau->type, &nouveau->superficie,
                            nouveau->quartier, &nouveau->distance, &nouveau->loyer, &nouveau->etat);

        if(!feof(file)){//fin du fichier est sortir
        // ajouter la node au debut de la liste
        nouveau->suivant = *list;
        *list = nouveau;
        }
    }

    fclose(file);//fermer le fichier
}

/********************************************************************************************************/

//rempir la liste des logements archive depuit le fichier
void archive_logement(Logement **list) {
    FILE *file = fopen("logement_archive.txt", "r");//pointeur du  fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");//error
    }
    while (!feof(file)) { //jusque la fin du fichier
        Logement *nouveau = (Logement*) malloc(sizeof(Logement));//allouer la memoire
        if (nouveau==NULL) {
            printf("Erreur d'allocation mémoire\n");
            fclose(file); // fermer le fichier 
        }

        // lire data depuis le fichier
        int result = fscanf(file, "%d %s %f %s %f %f %d",
                            &nouveau->id_logement, nouveau->type, &nouveau->superficie,
                            nouveau->quartier, &nouveau->distance, &nouveau->loyer, &nouveau->etat);

        if (!feof(file)) {
        // ajouter la node au debut de la liste
        nouveau->suivant = *list;
        *list = nouveau;
        }
    }

    fclose(file);//fermer le fichier
}
 
/********************************************************************************************************/

//rempir la liste des locataires depuit le fichier
void file_locataire(Locataire **list) {
    FILE *file = fopen("locataire_fichier.txt", "r");//pointeur vers fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");
    }
    while (!feof(file)) { //jusque la fin du fichier
        Locataire *nouveau = (Locataire*) malloc(sizeof(Locataire));//allouer memoire
        if (nouveau==NULL) {
            printf("Erreur d'allocation mémoire\n");
            fclose(file); //fermer le fichier 
        }

        // lire data depuis le fichier
        int result = fscanf(file, "%d %s %s %s",
                            &nouveau->id_locataire, nouveau->nom, nouveau->prenom, nouveau->telephone);

        if (!feof(file)) {
        // ajouter la node au debut de la liste
        nouveau->suivant = *list;
        *list = nouveau;
        }
    }

    fclose(file);//fermer le fichier
}

/********************************************************************************************************/

//rempir la liste des locataires archive depuit le fichier
void archive_locataire(Locataire **list) {
    FILE *file = fopen("locataire_archive.txt", "r");//pointeur vers fichier
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");//error
    }

    while (!feof(file)) { //jusque la fin du fichier
        Locataire *nouveau = (Locataire*) malloc(sizeof(Locataire));//allouer
        if (nouveau==NULL) {
            printf("Erreur d'allocation mémoire\n");
            fclose(file); // fermer le fichier
        }

         // lire data depuis le fichier
        int result = fscanf(file, "%d %s %s %s",
                            &nouveau->id_locataire, nouveau->nom, nouveau->prenom, nouveau->telephone);

        if (!feof(file)) {
        // ajouter la node au debut de la liste
        nouveau->suivant = *list;
        *list = nouveau;
        }
    }

    fclose(file);//fermer le fichier
}

/********************************************************************************************************/

//rempir la liste des locations depuit le fichier
void file_location(Location **list) {
    FILE *file = fopen("location_fichier.txt", "r"); 
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");
    }

    while (!feof(file)) { //jusque la fin du fichier
        Location *nouveau = (Location*) malloc(sizeof(Location));
        if (nouveau==NULL) {
            printf("Erreur d'allocation mémoire\n");
            fclose(file); // Close the file 
        }

         // lire data depuis le fichier
        int result = fscanf(file, "%d %d %d %d %d",
                            &nouveau->id_location, &nouveau->id_locataire, &nouveau->id_logement,
                            &nouveau->date_debut, &nouveau->date_fin);

        if (!feof(file)) {
        // ajouter la node au debut de la liste
        nouveau->suivant = *list;
        *list = nouveau;
        }
    }

    fclose(file);
}
 
/********************************************************************************************************/

//rempir la liste des locations archive depuit le fichier
void archive_location(Location **list) {
    FILE *file = fopen("location_archive.txt", "r"); //pointer of file
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier");
        return;
    }
    while (!feof(file)) {//jusque la fin du fichier
        Location *nouveau = (Location*) malloc(sizeof(Location));//allouer
        if (nouveau==NULL) {
            printf("Erreur d'allocation mémoire\n");
            fclose(file); // fermer le  fichier
        }

        // lire data depuis le fichier
        int result = fscanf(file, "%d %d %d %d %d",
                            &nouveau->id_location, &nouveau->id_locataire, &nouveau->id_logement,
                            &nouveau->date_debut, &nouveau->date_fin);
       
        if (!feof(file)) {
        // ajouter la node au debut de la liste
        nouveau->suivant = *list;
        *list = nouveau;
        }
    }

    fclose(file);//fermer le fichier
}
 
/********************************************************************************************************/

//cree les fichiers si ils n'existe pas
void create_file(){
    //ouvrir les fichiers en mode a pour conserver le contenue
    FILE *log_file=fopen("logement_fichier.txt","a");
    FILE *log_archive=fopen("logement_archive.txt","a");
    FILE *loc_file=fopen("locataire_fichier.txt","a");
    FILE *loc_archive=fopen("locataire_archive.txt","a");
    FILE *location_file=fopen("location_fichier.txt","a");
    FILE *location_archive=fopen("location_archive.txt","a");
    // Check if all files were opened successfully
    if (log_file == NULL || log_archive == NULL || loc_file == NULL ||
        loc_archive == NULL || location_file == NULL || location_archive == NULL) {
        printf("Erreur d'ouverture des fichiers");
        // Close any files that were successfully opened
        if (log_file) fclose(log_file);
        if (log_archive) fclose(log_archive);
        if (loc_file) fclose(loc_file);
        if (loc_archive) fclose(loc_archive);
        if (location_file) fclose(location_file);
        if (location_archive) fclose(location_archive);
        }
    fclose(log_file);
    fclose(log_archive);
    fclose(loc_file);
    fclose(loc_archive);
    fclose(location_file);
    fclose(location_archive);
 }

 /********************************************************************************************************/

// give the logement with the shotest distance
void highest_distance(Logement *log,Logement **prec,Logement **proch){
    Logement *prev=NULL;
    int save=-1;
    while(log!=NULL){
       if(log->distance>save){
         save=log->distance;//saving the shortest distance
          *prec=prev;
          *proch=log;//saving the pointers
         }
         prev=log;
         log=log->suivant;
      }
 }

 /********************************************************************************************************/

 void sort_par_distance(Logement **list){//this module trie les liste par distance
    Logement *prev=NULL;//pointers to save the logement with highest distance
    Logement *proch=NULL;
    Logement*save=NULL;
  while(*list!=NULL){
    highest_distance(*list,&prev,&proch);
    if(prev==NULL){//cas dans la tete
       *list=proch->suivant;
       proch->suivant=save;
       save=proch;
    }//la metre dans une autre liste
    else{//cas en melieu ou la fin
       prev->suivant=proch->suivant;
       proch->suivant=save;
       save=proch;
    }
  }
  *list=save;//rendre la liste
 }

 /********************************************************************************************************/

 void proche_commune(Logement **log){//module pour avoire le logement le plus proche
    int cpt=0;
    printf("\n entre le nombre de logement a afficher :");
    scanf("%d",&cpt);
    Logement *save=*log;
    sort_par_distance(&save);//on trie la liste
   *log=save;
    while(*log!=NULL && cpt>0){
       afficher_logement(save);//on affiche les n proche logements
       cpt--;
       save=save->suivant;
    }
 }

 /********************************************************************************************************/
 
 void highest_loyer(Logement *log,Logement **prec,Logement **proch){//avoir le logeemnt avec le plus grand loyer
    Logement *prev=NULL;
    int save=-1;
    while(log!=NULL){
       if(log->loyer>save){//comparer le loyer
        save=log->loyer;
          *prec=prev;//save the pointers
          *proch=log;
         }
         prev=log;
         log=log->suivant;
      }
 }

 /********************************************************************************************************/

 void sort_par_loyer(Logement **list){// trierla liste par loyer
    Logement *prev=NULL;
    Logement *proch=NULL;//pointers pour save le mplus grand
    Logement*save=NULL;
  while(*list!=NULL){
    highest_loyer(*list,&prev,&proch);
    if(prev==NULL){//cas dans la tete
       *list=proch->suivant;
       proch->suivant=save;
       save=proch;
    }//changer la liste
    else{//cas en melieu
       prev->suivant=proch->suivant;
       proch->suivant=save;
       save=proch;
    }
  }
  *list=save;//rendre le liste
 }

 /********************************************************************************************************/

 void minimal_loyer(Logement **log){//afficher les n minimal loyer 
    int cpt=0;
    printf("\n entre le nombre de logement a afficher :");
    scanf("%d",&cpt);
    Logement *save=*log;
    sort_par_loyer(&save);//trier la liste par loyer
   *log=save;
    while(save!=NULL && cpt>0){
       afficher_logement(save);//afficher les logements
       cpt--;
       save=save->suivant;
    }
    
 }

 /********************************************************************************************************/
// fonction pour extraire la date de la format aaaammjj
int extract_year(int date) {
    return date / 10000; 
}

/********************************************************************************************************/
// fonction pour compter les logements loues par quartier pour une annee
void count_logements_by_quartier_and_year(Logement *logements, Logement *archive_logements, Location *locations, Location *archive_locations, int year) {
    Logement *log = logements;
    Location *loc = locations;
    int count_by_quartier[100] = {0}; // tableau pour stoquer nombre par quartier 
    char quartiers[100][50]; // 2d tab pour les noms des quartiers
    int quartier_count = 0; // nombre des quartiers

    // check active logements et locations
    while (log != NULL) {
        Location *temp = locations;
        while (temp != NULL) {
            if (temp->id_logement == log->id_logement && extract_year(temp->date_debut) == year) {
               // check si le quartier est deja dans la liste
                bool found = false;
                for (int i = 0; i < quartier_count; i++) {
                    if (strcmp(quartiers[i], log->quartier) == 0) {
                        count_by_quartier[i]++;
                        found = true;
                        break;
                    }
                }
                if (found==false) {
                    strcpy(quartiers[quartier_count], log->quartier);
                    count_by_quartier[quartier_count]++;
                    quartier_count++;
                }
                break;
            }
            temp = temp->suivant;
        }
        log = log->suivant;
    }

    // check  logements et locations archivees
    log = archive_logements;
    while (log != NULL) {
        Location *temp = archive_locations;
        while (temp != NULL) {
            if (temp->id_logement==log->id_logement && extract_year(temp->date_debut) == year) {
                // check si le quartier est deja dans la liste
                bool found = false;
                for (int i = 0; i < quartier_count; i++) {
                    if (strcmp(quartiers[i], log->quartier) == 0) {
                        count_by_quartier[i]++;
                        found = true;
                        break;
                    }
                }
                if (found==false) {
                    strcpy(quartiers[quartier_count], log->quartier);
                    count_by_quartier[quartier_count]++;
                    quartier_count++;
                }
                break;
            }
            temp = temp->suivant;
        }
        log = log->suivant;
    }
    //results
    printf("\nLogements loues en %d, classes par quartier:\n", year);
    for (int i = 0; i < quartier_count; i++) {
        printf("Quartier: %s | Nombre de logements loues: %d\n", quartiers[i], count_by_quartier[i]);
    }
}

/********************************************************************************************************/

void count_locations_by_type_and_year(Location *locations, Location *archive_locations, Logement *logements, Logement *archive_logements, int year) {
    Location *loc = locations;
    int studio_count = 0, f2_count = 0, f3_count = 0, f4_count = 0;

    // check active locations et logements
    while (loc != NULL) {
        if (extract_year(loc->date_debut) == year) {
            Logement *log = logements;
            while (log != NULL) {
                if (log->id_logement == loc->id_logement) {
                    if (strcmp(log->type, "studio") == 0) studio_count++;
                    else if (strcmp(log->type, "f2") == 0) f2_count++;
                    else if (strcmp(log->type, "f3") == 0) f3_count++;
                    else if (strcmp(log->type, "f4") == 0) f4_count++;
                    break;
                }
                log = log->suivant;
            }
        }
        loc = loc->suivant;
    }

    // check archived locations and logements
    loc = archive_locations;
    while (loc != NULL) {
        if (extract_year(loc->date_debut) == year) {
            Logement *log = archive_logements;
            while (log != NULL) {
                if (log->id_logement == loc->id_logement) {
                    if (strcmp(log->type, "studio") == 0) studio_count++;
                    else if (strcmp(log->type, "f2") == 0) f2_count++;
                    else if (strcmp(log->type, "f3") == 0) f3_count++;
                    else if (strcmp(log->type, "f4") == 0) f4_count++;
                    break;
                }
                log = log->suivant;
            }
        }
        loc = loc->suivant;
    }

    // results
    printf("\nTotal des locations par type en %d:\n", year);
    printf("Studio: %d\n", studio_count);
    printf("F2: %d\n", f2_count);
    printf("F3: %d\n", f3_count);
    printf("F4: %d\n", f4_count);
}

/********************************************************************************************************/
//constuire le menu
void menu_logements(Logement **logements, Logement **archive_logements) {//les applications sur les logements
    int choix, id;
    char type_logement[10];

    do {
        system("cls");
        printf("\n=== GESTION DES LOGEMENTS ===\n");
        printf("1. Ajouter un logement\n");
        printf("2. Supprimer un logement\n");
        printf("3. Supprimer un type de logement\n");
        printf("4. Afficher les logements\n");
        printf("5. Retour au menu principal\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        system("cls");

        switch (choix) {
            case 1:
                ajouter_logement(logements);//pour ajouter un logement
                break;
            case 2:
                printf("Entrez l'ID du logement a supprimer : ");//pour suprimer avec l'id
                scanf("%d", &id);
                supprimer_logement(logements, archive_logements, id);
                break;
            case 3:
                printf("Entrez le type de logement a supprimer (studio, f2, f3, f4) : ");
                scanf("%s", type_logement);//pour suprimer les logements d'un type
                supprimer_type_logement(logements, archive_logements, type_logement);
                break;
            case 4:
                afficher_logements(*logements);//pour afficher les logements
                break;
            case 5://to return to the main menu
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }

        if (choix != 5) {
            printf("\nAppuyez sur Enter pour continuer --> ");
            getchar(); 
            getchar(); 
        }

    } while (choix != 5);
}

/********************************************************************************************************/
//constuire le menu
void menu_locataires(Locataire **locataires, Locataire **archive_locataires) {
    int choix, id;

    do {
        system("cls");
        printf("\n=== GESTION DES LOCATAIRES ===\n");
        printf("1. Ajouter un locataire\n");
        printf("2. Supprimer un locataire\n");
        printf("3. Afficher les locataires\n");
        printf("4. Retour au menu principal\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        system("cls");

        switch (choix) {
            case 1:
                ajouter_locataire(locataires);//ajouter un locataire
                break;
            case 2:
                printf("Entrez l'ID du locataire a supprimer : ");//suprimer par l'id
                scanf("%d", &id);
                supprimer_locataire(locataires, archive_locataires, id);
                break;
            case 3:
                afficher_locataires(*locataires);//afficher les locataires
                break;
            case 4:
                break;//sortir au lenu principal
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }
        if (choix != 4) {
            printf("\nAppuyez sur Enter pour continuer --> ");
            getchar(); 
            getchar(); 
        }
    } while (choix != 4);
}

/********************************************************************************************************/
//consuiure le menu
void menu_locations(Location **locations, Location **archive_locations, Logement *logements,Locataire **locataires) {
    int choix, id;

    do {
        system("cls");
        printf("\n=== GESTION DES LOCATIONS ===\n");
        printf("1. Ajouter une location\n");
        printf("2. Supprimer une location\n");
        printf("3. Afficher les logements occupes\n");
        printf("4. Afficher les logements libres a une date\n");
        printf("5. Afficher les locataires occupant un logement de meme type avec superficie moyenne\n");
        printf("6. Afficher toutes les locations\n");
        printf("7. Retour au menu principal\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        system("cls");

        switch (choix) {
            case 1:
                ajouter_location(locations, logements);//ajouter une location
                break;
            case 2:
                printf("Entrez l'ID de la location a supprimer : ");//suprimer une location par id
                scanf("%d", &id);
                supprimer_location(locations, archive_locations, id, logements);
                break;
            case 3:
                afficher_occupe(logements);//afficher les logements occupe
                break;
            case 4:
                afficher_libre(*locations, logements);//afficher les logements libre a une date
                break;
            case 5:
                afficher_locataires_superficie(*locations, logements, *locataires);
                break;
            case 6:  
                //afficher le resultat
                afficher_location(*locations);
                break;  
            case 7:
                break;//sortir au menu principal
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }

        if (choix != 7) {
            printf("\nAppuyez sur Enter pour continuer --> ");
            getchar(); 
            getchar(); 
        }

    } while (choix != 7);
}

/********************************************************************************************************/
//constuire le menu
void fusion_et_tris(Location **locations, Location **studio, Location **f2, Location **f3, Location **f4, Logement *logements) {
    int choix;

    do {
        system("cls");
        printf("\n=== FUSION ET TRIS ===\n");
        printf("1. Separer les locations par type\n");
        printf("2. Trier les locations\n");
        printf("3. Fusionner les locations\n");
        printf("4. Afficher toutes les locations\n");
        printf("5. Retour au menu principal\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        system("cls");

        switch (choix) {
            case 1:
                location_type(locations, studio, 1, logements); // Liste des studios costuire le liste du type syudio
                location_type(locations, f2, 2, logements);    // Liste des F2 liste du type F2
                location_type(locations, f3, 3, logements);    // Liste des F3 constuire la liste du type F3
                location_type(locations, f4, 4, logements);    // Liste des F4 constuire la liste du type F4
                printf("Studios :\n");
                afficher_location(*studio);//afficher la liste du studio
                printf("F2 :\n");
                afficher_location(*f2);//afficher la liste du f3
                printf("F3 :\n");
                afficher_location(*f3);//affiche la liste du F3
                printf("F4 :\n");
                afficher_location(*f4);//afficher la liste du f4
                break;
            case 2:
                //trier les liste des studio f2 f3 f4
                sort_location(studio, logements);
                sort_location(f2, logements);
                sort_location(f3, logements);
                sort_location(f4, logements);
                //afficher les resultats
                printf("Studios :\n");
                afficher_location(*studio);
                printf("f2 :\n");
                afficher_location(*f2);
                printf("f3 :\n");
                afficher_location(*f3);
                printf("f4 :\n");
                afficher_location(*f4);
                printf("Listes triEes avec succes.\n");
                break;
            case 3:
               //fusionner leslistes dans la liste principale
                merge_location(locations, studio, logements);
                merge_location(locations, f2, logements);
                merge_location(locations, f3, logements);
                merge_location(locations, f4, logements);
                printf("Listes fusionnees avec succes.\n");
                break;
            case 4:
            //afficher le resultat
                afficher_location(*locations);
                break;
            case 5:
            //sortir au menu principal
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }

        if (choix != 5) {
            printf("\nAppuyez sur Enter pour continuer --> ");
            getchar(); 
            getchar(); 
        }

    } while (choix != 5);
}

/********************************************************************************************************/
//constuire le menu
void recherche(Logement **logements) {
    int choix;

    do {
        system("cls");
        printf("\n=== RECHERCHE ===\n");
        printf("1. Rechercher les logements proches d'une commune\n");
        printf("2. Rechercher les logements avec loyer minimal\n");
        printf("3. Retour au menu principal\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        system("cls");

        switch (choix) {
            case 1:
                proche_commune(logements);//afficher les n proche commune
                break;
            case 2:
                minimal_loyer(logements);//afficher les n minimal loyer
                break;
            case 3:
                break; // sortir au menu pricipal
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }

        if (choix != 3) {
            printf("\nAppuyez sur Enter pour continuer --> ");
            getchar(); 
            getchar(); 
        }

    } while (choix != 3);
}

/********************************************************************************************************/
//constuire le menu
void historique(Logement **logements, Logement **archive_logements, Location **locations, Location **archive_locations,Locataire *archive_lovataire) {
    int choix, year;

    do {
        system("cls");
        printf("\n=== HISTORIQUE ===\n");
        printf("1. Consulter l'historique des logements par annee\n");
        printf("2. Consulter l'historique des locations par annee\n");
        printf("3. Afficher l'archive des logements\n");
        printf("4. Afficher l'archive des locataires\n");
        printf("5. Afficher l'archive des locations\n");
        printf("6. Retour au menu principal\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        system("cls");

        switch (choix) {
            case 1:
                printf("Entrez l'annee (AAAA) : ");
                scanf("%d", &year);
                count_logements_by_quartier_and_year(*logements, *archive_logements, *locations, *archive_locations, year);
                break;
            case 2:
                printf("Entrez l'annee (AAAA) : ");
                scanf("%d", &year);
                count_locations_by_type_and_year(*locations, *archive_locations, *logements, *archive_logements, year);
                break;
            case 3:
                afficher_logements(*archive_logements);
                break; // Retour au menu principal
            case 4:
                afficher_locataires(archive_lovataire);
                break;
            case 5 :
                afficher_location(*archive_locations);
                break;   
            case 6 :
                break;    
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }
        if (choix != 6) {
            printf("\nAppuyez sur Enter pour continuer --> ");
            getchar(); 
            getchar(); 
        }
    } while (choix != 6);
}

/********************************************************************************************************/

void menu() {
    // initialisation des listes
    Logement *logements = NULL;
    Logement *archive_logements = NULL;
    Locataire *locataires = NULL;
    Locataire *archive_locataires = NULL;
    Location *locations = NULL;
    Location *archive_locations = NULL;
    Location *studio = NULL;
    Location *f2 = NULL;
    Location *f3 = NULL;
    Location *f4 = NULL;

    int choix, id, year;
    char type_logement[10];

    // Chargement des données depuis les fichiers
    create_file();
    file_logement(&logements);
    archive_logement(&archive_logements);
    file_locataire(&locataires);
    archive_locataire(&archive_locataires);
    file_location(&locations);
    archive_location(&archive_locations);

    do {
        system("cls"); // Effacer l'ecran a chaque affichage du menu
        printf("\n----- MENU PRINCIPAL -----\n");
        printf("1. Gestion des logements\n");
        printf("2. Gestion des locataires\n");
        printf("3. Gestion des locations\n");
        printf("4. Fusion et tris\n");
        printf("5. Recherche\n");
        printf("6. Historique\n");
        printf("7. Quitter\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        system("cls");  // Effacer l'écran 

        switch (choix) {
            case 1:
                menu_logements(&logements,&archive_logements);//gestion de logement fonction
                break;
            case 2:
                menu_locataires(&locataires,&archive_locataires);//gestion de locataire fonction
                break;
            case 3:
                menu_locations(&locations,&archive_locations, logements,&locataires);//gestion de location fonction
                break;
            case 4:
                fusion_et_tris(&locations,&studio, &f2, &f3, &f4, logements);//les tris et fusion
                break;
            case 5:
                recherche(&logements);//chercher les proche commune et minimal loyer
                break;
            case 6:
                historique(&logements, &archive_logements, &locations, &archive_locations,archive_locataires);//consulter l'hstorique
                break;
            case 7:
                printf("Au revoir !\n");//fin du programe
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }
        
        if (choix != 7) {
            printf("\nAppuyez sur Enter pour continuer --> ");
            getchar(); 
            getchar(); 
        }

    } while (choix != 7);
}

/********************************************************************************************************/

