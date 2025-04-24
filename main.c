#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NAME_LENGTH 50

// Structure qui représente un objet dans le jeu
typedef struct Object {
    char name[MAX_NAME_LENGTH];
    char description[100];
    int value;
} Object;
Object OBJET_VIDE = {"VIDE", "cette emplacement de l inventaire est vide", 0};
// Structure qui représente un objet dans le jeu
typedef struct Porte {
    char name[MAX_NAME_LENGTH];
    char description[100];
    int clef;
} Porte;
Porte PORTE_VIDE = {"VIDE", "cette emplacement de porte est vide", 0};
typedef struct entitee {
    char name[MAX_NAME_LENGTH];
    char description[100];
    int health;
    int statue;
    int id;
} PNJ;
PNJ PNJ_VIDE = {"VIDE", "cette emplacement de PNJ est vide", 0, 0};
typedef struct Dialogue {
    char texte[500];
    int choix;
    int ordre;
} Dialogue;
typedef struct Reponse {
    char rep[100];
    int ordre;
    int id;
} Reponse;
// Structure qui représente un lieu du jeu
typedef struct Location {
    char name[MAX_NAME_LENGTH];
    char description[150];
    int numero;
    Object inventory[10];
    Porte portes[10];
    PNJ entities[10];
} Location;
typedef struct Character {
    char name[MAX_NAME_LENGTH];
    int health;
    Object inventory[5]; // Inventaire contenant jusqu'à 5 objets
    Location *current_location;
} C;

void afficher_objects(Object **objects, int *size) {
    if (*size == 0) {
        printf("Erreur aucun objet.\n\n");
        return;
    }
    printf("\nListe des objets :\n");
    for (int i = 0; i < *size; i++) {
        printf("Objet %d : %s\n", i + 1, (*objects)[i].name);
        printf("Description : %s\n", (*objects)[i].description);
        printf("Valeur : %d\n\n", (*objects)[i].value);
    }
}
void afficher_portes(Porte **portes, int *size) {
    if (*size == 0) {
        printf("Erreur aucunne porte.\n\n");
        return;
    }
    printf("\nListe des portes :\n");
    for (int i = 0; i < *size; i++) {
        printf("Porte %d : %s\n", i + 1, (*portes)[i].name);
        printf("Description : %s\n", (*portes)[i].description);
        printf("Clef : %d\n\n", (*portes)[i].clef);
    }
}
void afficher_pnj(PNJ **pnj, int *size) {
    if (*size == 0) {
        printf("Erreur aucune entitee.\n\n");
        return;
    }
    printf("\nListe des entitees :\n");
    for (int i = 0; i < *size; i++) {
        printf("entitee %d : %s\n", i + 1, (*pnj)[i].name);
        printf("Description : %s\n", (*pnj)[i].description);
        printf("Point de vie : %d\n", (*pnj)[i].health);
        printf("Statue : %d\n", (*pnj)[i].statue);
        printf("id : %d\n\n", (*pnj)[i].id);
    }
}
void afficher_Location(Location **Locations, int *start, int *size) {
    if (*size == 0) {
        printf("Erreur aucun lieu.\n\n");
        return;
    }
    printf("\nListe des Lieux :\n");
    for (int i = *start; i <= *size; i++) {
        printf("lieu %d : %s\n", i, (*Locations)[i-1].name);
        printf("Description : %s\n", (*Locations)[i-1].description);
        printf("numero : %d\n", (*Locations)[i-1].numero);
        printf("objets du lieu :\n");
        for (int j = 0; j < 10; j++) {
            printf("%d. %s \n", j+1, (*Locations)[i-1].inventory[j].name);
        }
        printf("portes du lieu :\n");
        for (int j = 0; j < 10; j++) {
            printf("%d. %s \n", j+1, (*Locations)[i-1].portes[j].name);
        }
        printf("entitees du lieu :\n");
        for (int j = 0; j < 10; j++) {
            printf("%d. %s \n", j+1, (*Locations)[i-1].entities[j].name);
        }
    }
}
void afficherCharacter(C **Characters,int *start, int *size) {
    if (*size == 0) {
        printf("Erreur aucun personnage.\n\n");
        return;
    }
    for (int i = *start; i <= *size; i++) {
        printf("personnage %d : %s\n", i, (*Characters)[i-1].name);
        printf("PV : %d\n", (*Characters)[i-1].health);
        printf("inventaire : \n");
        for (int j = 0; j < 5; j++) {
            printf("%d. %s \n", j+1, (*Characters)[i-1].inventory[j].name);
        }
        printf("lieu : %s\n\n", (*Characters)[i-1].current_location->name);
    }
}
void afficher_dialogue(Dialogue **dia, int *size) {
    if (*size == 0) {
        printf("Erreur aucun dialogue.\n\n");
        return;
    }
    printf("\nListe des dialogues :\n");
    for (int i = 0; i < *size; i++) {
        printf("texte %d : %s\n", i + 1, (*dia)[i].texte);
        printf("choix : %d\n", (*dia)[i].choix);
        printf("ordre : %d\n\n", (*dia)[i].ordre);
    }
}
void afficher_reponse(Reponse **rep, int *size) {
    if (*size == 0) {
        printf("Erreur aucun reponse.\n\n");
        return;
    }
    printf("\nListe des reponses :\n");
    for (int i = 0; i < *size; i++) {
        printf("reponse %d : %s\n", i + 1, (*rep)[i].rep);
        printf("ordre : %d\n", (*rep)[i].ordre);
        printf("id : %d\n\n", (*rep)[i].id);
    }
}
void tout_afficher(C **Characters, int *persosize, Object **objects, int *objsize, Location **locations, int *lieusize, PNJ **pnj, int *pnjsize, Porte **portes, int *portesize, Dialogue **dia, int *diasize, Reponse **rep, int *repsize) {
    int start=1;
    afficher_Location(locations, &start, lieusize);
    afficherCharacter(Characters, &start, persosize);
    afficher_objects(objects, objsize);
    afficher_portes(portes, portesize);
    afficher_pnj(pnj, pnjsize);
    afficher_dialogue(dia, diasize);
    afficher_reponse(rep, repsize);
}

void addObject(Object **array, int *size, int *capacity, char *name, char *desc, int value) {
    if (*size >= *capacity) {
        *capacity *= 2;  // Double la capacité
        Object *temp = realloc(*array, *capacity * sizeof(Object));
        if (temp == NULL) {
            printf("Erreur de reallocation memoire.\n");
            free(*array);  // Libère la mémoire précédemment allouée
            exit(1);
        }
        *array = temp;  // Met à jour l'array avec la nouvelle allocation
    }

    // Ajout de l'objet
    strncpy((*array)[*size].name, name, sizeof((*array)[*size].name) - 1);
    (*array)[*size].name[sizeof((*array)[*size].name) - 1] = '\0';  // Assure-toi que la chaîne est terminée par '\0'

    strncpy((*array)[*size].description, desc, sizeof((*array)[*size].description) - 1);
    (*array)[*size].description[sizeof((*array)[*size].description) - 1] = '\0';  // Pareil pour la description

    (*array)[*size].value = value;
    (*size)++;
}
void ajouter_objects(Object **objects, int *size, int *capacity) {
    Object obj;  // On utilise directement un objet

    printf("\nEntrez le nom de l'objet : ");
    fgets(obj.name, sizeof(obj.name), stdin);
    obj.name[strcspn(obj.name, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez la description de l'objet : ");
    fgets(obj.description, sizeof(obj.description), stdin);
    obj.description[strcspn(obj.description, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez la valeur de l'objet : ");
    scanf("%d", &obj.value);
    getchar();  // Consomme le '\n' restant après scanf

    addObject(objects, size, capacity, obj.name, obj.description, obj.value);
    afficher_objects(objects, size);
}
void addPorte(Porte **array, int *size, int *capacity, char *name, char *desc, int clef) {
    if (*size >= *capacity) {
        *capacity *= 2;  // Double la capacité
        *array = realloc(*array, *capacity * sizeof(Porte));
        if (*array == NULL) {
            printf("Erreur de reallocation memoire.\n");
            exit(1);
        }
    }

    // Ajout de l'objet
    strcpy((*array)[*size].name, name);
    strcpy((*array)[*size].description, desc);
    (*array)[*size].clef = clef;
    (*size)++;
}
void ajouter_portes(Porte **porte, int *size, int *capacity) {
    Porte portes;  // On utilise directement un objet

    printf("\nEntrez le nom de la porte : ");
    fgets(portes.name, sizeof(portes.name), stdin);
    portes.name[strcspn(portes.name, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez la description de la porte : ");
    fgets(portes.description, sizeof(portes.description), stdin);
    portes.description[strcspn(portes.description, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez le numero de clef de la porte : ");
    scanf("%d", &portes.clef);
    getchar();  // Consomme le '\n' restant après scanf

    addPorte(porte, size, capacity, portes.name, portes.description, portes.clef);
    afficher_portes(porte, size);
}
void addPNJ(PNJ **array, int *size, int *capacity, char *name, char *desc, int hp, int statue, int id) {
    if (*size >= *capacity) {
        *capacity *= 2;  // Double la capacité
        *array = realloc(*array, *capacity * sizeof(PNJ));
        if (*array == NULL) {
            printf("Erreur de reallocation memoire.\n");
            exit(1);
        }
    }

    // Ajout de l'objet
    strcpy((*array)[*size].name, name);
    strcpy((*array)[*size].description, desc);
    (*array)[*size].health = hp;
    (*array)[*size].statue = statue;
    (*array)[*size].id = id;
    (*size)++;
}
void ajouter_PNJ(PNJ **entitee, int *size, int *capacity) {
    PNJ pnj;  // On utilise directement un objet

    printf("\nEntrez le nom de l entitee : ");
    fgets(pnj.name, sizeof(pnj.name), stdin);
    pnj.name[strcspn(pnj.name, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez la description de l entitee : ");
    fgets(pnj.description, sizeof(pnj.description), stdin);
    pnj.description[strcspn(pnj.description, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez le nombre de point de vie de l entitee : ");
    scanf("%d", &pnj.health);
    getchar();  // Consomme le '\n' restant après scanf

    printf("Entrez le statue de l entitee : ");
    scanf("%d", &pnj.statue);
    getchar();  // Consomme le '\n' restant après scanf

    printf("Entrez l id de l entitee : ");
    scanf("%d", &pnj.id);
    getchar();  // Consomme le '\n' restant après scanf

    addPNJ(entitee, size, capacity, pnj.name, pnj.description, pnj.health, pnj.statue, pnj.id);
    afficher_pnj(entitee, size);
}
void addLieu(Location **array, int *size, int *capacity, char *name, char *desc, int *id) {
    if (*size >= *capacity) {
        *capacity *= 2;  // Double la capacité
        *array = realloc(*array, *capacity * sizeof(Location));
        if (*array == NULL) {
            printf("Erreur de reallocation memoire.\n");
            exit(1);
        }
    }
    // Ajout de l'objet
    Location *new_lieu = &(*array)[*size];
    strcpy(new_lieu->name, name);
    strcpy(new_lieu->description, desc);
    new_lieu->numero = id;
    for (int i = 0; i < 10; i++) {
        new_lieu->inventory[i] = OBJET_VIDE;
        new_lieu->portes[i] = PORTE_VIDE;
        new_lieu->entities[i] = PNJ_VIDE;
    }

    (*size)++;
}
void ajouter_lieu(Location **Locations, int *size, int *capacity) {
    Location lieu;

    printf("\nEntrez le nom du lieu : ");
    fgets(lieu.name, sizeof(lieu.name), stdin);
    lieu.name[strcspn(lieu.name, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez la description du lieu : ");
    fgets(lieu.description, sizeof(lieu.description), stdin);
    lieu.description[strcspn(lieu.description, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez le numero du lieu : ");
    scanf("%d", &lieu.numero);
    getchar();  // Consomme le '\n' restant après scanf

    addLieu(Locations, size, capacity, lieu.name, lieu.description, lieu.numero);
    int start = 1;
    afficher_Location(Locations, &start, size);
}
void addCharacter(C **array, int *size, int *capacity, char *name, int hp, Location *Location) {
    if (*size >= *capacity) {
        *capacity *= 2;  // Double la capacité
        *array = realloc(*array, *capacity * sizeof(C));
        if (*array == NULL) {
            printf("Erreur de reallocation memoire.\n");
            exit(1);
        }
    }

    C *new_char = &(*array)[*size];
    strcpy(new_char->name, name);
    new_char->health = hp;
    for (int i = 0; i < 5; i++) {
        new_char->inventory[i] = OBJET_VIDE;
    }
    new_char->current_location = Location;
    (*size)++;
}
void ajouter_Character(C **Characters, int *size, int *capacity, Location *available_locations, int location_count) {
    C perso;
    int location_choice;
    int INVENTORY_SIZE=5;

    if (location_count == 0) {
        printf("Erreur aucun lieu.\n\n");
        return;
    }

    printf("\nEntrez le nom du Character : ");
    fgets(perso.name, sizeof(perso.name), stdin);
    perso.name[strcspn(perso.name, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez la bare de vie du Character : ");
    scanf("%d", &perso.health);
    getchar();  // Consomme le '\n' restant après scanf


    printf("Choisissez un lieu de départ, \nEntrer le numero correspondant :\n");
    for (int i = 0; i < location_count; ++i) {
        printf("%d. %s\n", i + 1, available_locations[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &location_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (location_choice < 1 || location_choice > location_count) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    perso.current_location = &available_locations[location_choice - 1];

    addCharacter(Characters, size, capacity, perso.name, perso.health, perso.current_location);
    int start = 1;
    afficherCharacter(Characters, &start, size);
}
void addDialogue(Dialogue **array, int *size, int *capacity, char *texte, int choix, int ordre) {
    if (*size >= *capacity) {
        *capacity *= 2;  // Double la capacité
        *array = realloc(*array, *capacity * sizeof(Dialogue));
        if (*array == NULL) {
            printf("Erreur de reallocation memoire.\n");
            exit(1);
        }
    }

    // Ajout du dialogue
    strcpy((*array)[*size].texte, texte);
    (*array)[*size].choix = choix;
    (*array)[*size].ordre = ordre;
    (*size)++;
}
void addReponse(Reponse **array, int *size, int *capacity, char *repTexte, int ordre, int id) {
    if (*size >= *capacity) {
        *capacity *= 2;
        *array = realloc(*array, *capacity * sizeof(Reponse));
        if (*array == NULL) {
            printf("Erreur de reallocation memoire.\n");
            exit(1);
        }
    }

    // Ajout des données
    strcpy((*array)[*size].rep, repTexte);
    (*array)[*size].ordre = ordre;
    (*array)[*size].id = id;
    (*size)++;
}
void creer_dialogue(Dialogue **dialogue, int *diasize, int *diacapacity, Reponse **reponses, int *repsize, int *repcapacity, int *id) {
    Reponse rep;
    Dialogue dia;
    printf("Taper le texte de l entitee : ");
    fgets(dia.texte, sizeof(dia.texte), stdin);
    dia.texte[strcspn(dia.texte, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez le nombre de choix de reponse possible, \nTaper 0 pour cloturer le dialogue : ");
    scanf("%d", &dia.choix);
    getchar();  // Consomme le '\n' restant après scanf

    dia.ordre = *id;
    //appelle de la fonction de creation de Dialogue
    addDialogue(dialogue, diasize, diacapacity, dia.texte, dia.choix, dia.ordre);
    for (int i = 0; i < dia.choix; i++) {
        printf("Taper le texte de la reponse %d : ", i+1);
        fgets(rep.rep, sizeof(rep.rep), stdin);
        rep.rep[strcspn(rep.rep, "\n")] = '\0';  // Supprime le retour à la ligne
        rep.ordre=dia.ordre;
        (*id)++;
        rep.id = *id;
        //appelle de la fonction de creation de Reponse
        addReponse(reponses, repsize, repcapacity, rep.rep, rep.ordre, rep.id);
        creer_dialogue(dialogue, diasize, diacapacity, reponses, repsize, repcapacity, id);
    }
}
void initDialogue(PNJ **pnj, int *pnjsize, Dialogue **dialogue, int *diasize, int *diacapacity, Reponse **reponses, int *repsize, int *repcapacity) {
    int entitee_choice;
    printf("Choisissez une entitee, \nEntrer le numero correspondant :\n");
    for (int i = 0; i < *pnjsize; ++i) {
        printf("%d. %s\n", i + 1, (*pnj)[i].name);
    }
    printf("Votre choix : ");
    scanf("%d", &entitee_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (entitee_choice < 1 || entitee_choice > *pnjsize) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int id = (*pnj)[entitee_choice - 1].id;
    creer_dialogue(dialogue, diasize, diacapacity, reponses, repsize, repcapacity, &id);
}

void deplacement(int *persosize, int *lieusize, Location *available_locations, C *available_personnage) {
    int location_choice;
    int personnage_choice;
    if (*persosize == 0) {
        printf("Erreur aucun personnage.\n\n");
        return;
    }
    if (*lieusize <= 1) {
        printf("Erreur, il y a 1 ou aucun lieu.\n\n");
        return;
    }
    if (*persosize > 1) {
        printf("Choisissez un personnage, \nEntrer le numero correspondant :\n");
        for (int i = 0; i < *persosize; ++i) {
            printf("%d. %s\n", i + 1, available_personnage[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &personnage_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (personnage_choice < 1 || personnage_choice > *persosize) {
            printf("Choix invalide, annulation.\n");
            return;
        }
    }   else {personnage_choice=1;}

        printf("Choisissez un lieu, \nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieusize; ++i) {
            printf("%d. %s\n", i + 1, available_locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &location_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (location_choice < 1 || location_choice > *lieusize) {
            printf("Choix invalide, annulation.\n");
            return;
    }
    available_personnage[personnage_choice - 1].current_location = &available_locations[location_choice - 1];
    int start = 1;
    afficherCharacter(&available_personnage, &start, persosize);
}
void ajObject(C *characters, int *persosize, Object *objects, int *objsize) {
    int personnage_choice;
    int object_choice;
    if (*persosize == 0) {
        printf("Erreur aucun personnage.\n\n");
        return;
    }
    if (*objsize < 1) {
        printf("Erreur, il y a aucun objet.\n\n");
        return;
    }
    if (*persosize > 1) {
        printf("Choisissez un personnage, \nEntrer le numero correspondant :\n");
        for (int i = 0; i < *persosize; ++i) {
            printf("%d. %s\n", i + 1, characters[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &personnage_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (personnage_choice < 1 || personnage_choice > *persosize) {
            printf("Choix invalide, annulation.\n");
            return;
        }
    }else {personnage_choice=1;}

    afficherCharacter(&characters, &personnage_choice, &personnage_choice);

    printf("Choisissez un objet, \nEntrer le numero correspondant :\n");
    for (int i = 0; i < *objsize; ++i) {
        printf("%d. %s\n", i + 1, objects[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &object_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (object_choice < 1 || object_choice > *objsize) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index = personnage_choice - 1;
    int placed = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp(characters[index].inventory[i].name, "VIDE") == 0) {
            characters[index].inventory[i] = objects[object_choice - 1];
            placed = 1;
            break;
        }
    }

    if (!placed) {
        printf("Inventaire plein, impossible d'ajouter un objet.\n");
        return;
    }
    afficherCharacter(&characters, &personnage_choice, &personnage_choice);
}
void ajObject_lieu(Location *locations, int *lieusize, Object *objects, int *objsize) {
    int lieu_choice;
    int object_choice;
    if (*lieusize == 0) {
        printf("Erreur aucun lieu\n\n");
        return;
    }
    if (*objsize < 1) {
        printf("Erreur, il y a aucun objet\n\n");
        return;
    }
    if (*lieusize > 1) {
        printf("Choisissez un lieu, \nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieusize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieusize) {
            printf("Choix invalide, annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez un objet, \nEntrer le numero correspondant :\n");
    for (int i = 0; i < *objsize; ++i) {
        printf("%d. %s\n", i + 1, objects[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &object_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (object_choice < 1 || object_choice > *objsize) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index = lieu_choice - 1;
    int placed = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp(locations[index].inventory[i].name, "VIDE") == 0) {
            locations[index].inventory[i] = objects[object_choice - 1];
            placed = 1;
            break;
        }
    }

    if (!placed) {
        printf("lieu plein, impossible d'ajouter un objet.\n");
        return;
    }
    afficher_Location(&locations, &lieu_choice, &lieu_choice);
}
void ajPorte_lieu(Location *locations, int *lieusize, Porte *portes, int *portesize) {
    int lieu_choice;
    int porte_choice;
    if (*lieusize == 0) {
        printf("Erreur aucun lieu\n\n");
        return;
    }
    if (*portesize < 1) {
        printf("Erreur, il y a aucune porte\n\n");
        return;
    }
    if (*lieusize > 1) {
        printf("Choisissez un lieu, \nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieusize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieusize) {
            printf("Choix invalide, annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez une porte, \nEntrer le numero correspondant :\n");
    for (int i = 0; i < *portesize; ++i) {
        printf("%d. %s\n", i + 1, portes[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &porte_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (porte_choice < 1 || porte_choice > *portesize) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index = lieu_choice - 1;
    int placed = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp(locations[index].portes[i].name, "VIDE") == 0) {
            locations[index].portes[i] = portes[porte_choice - 1];
            placed = 1;
            break;
        }
    }

    if (!placed) {
        printf("Lieu plein, impossible d'ajouter une porte.\n");
        return;
    }
    afficher_Location(&locations, &lieu_choice, &lieu_choice);
}
void ajPNJ_lieu(Location *locations, int *lieusize, PNJ *pnj, int *pnjsize) {
    int lieu_choice;
    int entitee_choice;
    if (*lieusize == 0) {
        printf("Erreur aucun lieu\n\n");
        return;
    }
    if (*pnjsize < 1) {
        printf("Erreur, il y a aucune entitee\n\n");
        return;
    }
    if (*lieusize > 1) {
        printf("Choisissez un lieu, \nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieusize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieusize) {
            printf("Choix invalide, annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez une entitee, \nEntrer le numero correspondant :\n");
    for (int i = 0; i < *pnjsize; ++i) {
        printf("%d. %s\n", i + 1, pnj[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &entitee_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (entitee_choice < 1 || entitee_choice > *pnjsize) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index = lieu_choice - 1;
    int placed = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp(locations[index].entities[i].name, "VIDE") == 0) {
            locations[index].entities[i] = pnj[entitee_choice - 1];
            placed = 1;
            break;
        }
    }

    if (!placed) {
        printf("Lieu plein, impossible d'ajouter une entitee.\n");
        return;
    }
    afficher_Location(&locations, &lieu_choice, &lieu_choice);
}
void suprObject(C *characters, int *persosize, Object *objects, int *objsize) {
    int personnage_choice;
    int object_choice;
    if (*persosize == 0) {
        printf("Erreur aucun personnage\n\n");
        return;
    }
    if (*objsize < 1) {
        printf("Erreur, il y a aucun objet\n\n");
        return;
    }
    if (*persosize > 1) {
        printf("Choisissez un personnage, \nEntrer le numero correspondant :\n");
        for (int i = 0; i < *persosize; ++i) {
            printf("%d. %s\n", i + 1, characters[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &personnage_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (personnage_choice < 1 || personnage_choice > *persosize) {
            printf("Choix invalide, annulation.\n");
            return;
        }
    }else {personnage_choice=1;}

    afficherCharacter(&characters, &personnage_choice, &personnage_choice);

    printf("Choisissez un objet, \nEntrer le numero correspondant :\n");
    for (int i = 0; i < *objsize; ++i) {
        printf("%d. %s\n", i + 1, objects[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &object_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (object_choice < 1 || object_choice > *objsize) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index = personnage_choice - 1;
    int placed = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp(characters[index].inventory[i].name, objects[object_choice - 1].name) == 0) {
            characters[index].inventory[i] = OBJET_VIDE;
            placed = 1;
            break;
        }
    }

    if (!placed) {
        printf("Objet introuvable.\n");
        return;
    }
    afficherCharacter(&characters, &personnage_choice, &personnage_choice);
}
void suprObject_lieu(Location *locations, int *lieuosize, Object *objects, int *objsize) {
    int lieu_choice;
    int object_choice;
    if (*lieuosize == 0) {
        printf("Erreur aucun lieu.\n\n");
        return;
    }
    if (*objsize < 1) {
        printf("Erreur, il y a aucun objet.\n\n");
        return;
    }
    if (*lieuosize > 1) {
        printf("Choisissez un lieu, \nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieuosize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieuosize) {
            printf("Choix invalide, annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez un objet, \nEntrer le numero correspondant :\n");
    for (int i = 0; i < *objsize; ++i) {
        printf("%d. %s\n", i + 1, objects[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &object_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (object_choice < 1 || object_choice > *objsize) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index = lieu_choice - 1;
    int placed = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp(locations[index].inventory[i].name, objects[object_choice - 1].name) == 0) {
            locations[index].inventory[i] = OBJET_VIDE;
            placed = 1;
            break;
        }
    }

    if (!placed) {
        printf("Objet introuvable.\n");
        return;
    }
    afficher_Location(&locations, &lieu_choice, &lieu_choice);
}
void suprPorte_lieu(Location *locations, int *lieuosize, Porte *portes, int *portesize) {
    int lieu_choice;
    int porte_choice;
    if (*lieuosize == 0) {
        printf("Erreur aucun lieu.\n\n");
        return;
    }
    if (*portesize < 1) {
        printf("Erreur, il y a aucune porte.\n\n");
        return;
    }
    if (*lieuosize > 1) {
        printf("Choisissez un lieu, \nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieuosize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieuosize) {
            printf("Choix invalide, annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez une porte, \nEntrer le numero correspondant :\n");
    for (int i = 0; i < *portesize; ++i) {
        printf("%d. %s\n", i + 1, portes[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &porte_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (porte_choice < 1 || porte_choice > *portesize) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index = lieu_choice - 1;
    int placed = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp(locations[index].portes[i].name, portes[porte_choice - 1].name) == 0) {
            locations[index].portes[i] = PORTE_VIDE;
            placed = 1;
            break;
        }
    }

    if (!placed) {
        printf("porte introuvable.\n");
        return;
    }
    afficher_Location(&locations, &lieu_choice, &lieu_choice);
}
void suprPNJ_lieu(Location *locations, int *lieuosize, PNJ *pnj, int *pnjsize) {
    int lieu_choice;
    int PNJ_choice;
    if (*lieuosize == 0) {
        printf("Erreur aucun lieu.\n\n");
        return;
    }
    if (*pnjsize < 1) {
        printf("Erreur, il y a aucune entitee.\n\n");
        return;
    }
    if (*lieuosize > 1) {
        printf("Choisissez un lieu, \nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieuosize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieuosize) {
            printf("Choix invalide, annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez une entitee, \nEntrer le numero correspondant :\n");
    for (int i = 0; i < *pnjsize; ++i) {
        printf("%d. %s\n", i + 1, pnj[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &PNJ_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (PNJ_choice < 1 || PNJ_choice > *pnjsize) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index = lieu_choice - 1;
    int placed = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp(locations[index].entities[i].name, pnj[PNJ_choice - 1].name) == 0) {
            locations[index].entities[i] = PNJ_VIDE;
            placed = 1;
            break;
        }
    }

    if (!placed) {
        printf("Porte introuvable.\n");
        return;
    }
    afficher_Location(&locations, &lieu_choice, &lieu_choice);
}

void sauvegarderJeu(const char *nomFichier, Object *objects, int objsize, int objcapacity, Location *locations, int lieusize, int lieucapacity, C *Characters, int persosize, int persocapacity, Porte *portes, int portesize, int portecapacity, PNJ *pnj, int pnjsize, int pnjcapacity, Dialogue *dia, int diasize, int diacapacity, Reponse *rep, int repsize, int repcapacity) {
    FILE *f = fopen(nomFichier, "w");
    if (!f) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Sauvegarder les objets
    fprintf(f, "%d\n", objsize);
    fprintf(f, "%d\n", objcapacity);
    for (int i = 0; i < objsize; i++) {
        fprintf(f, "%s\n", objects[i].name);  // Nom de l'objet sur une ligne
        fprintf(f, "%d\n", objects[i].value); // Valeur sur une ligne
        fprintf(f, "%s\n", objects[i].description); // Description sur une ligne
    }
    // Sauvegarder les portes
    fprintf(f, "%d\n", portesize);
    fprintf(f, "%d\n", portecapacity);
    for (int i = 0; i < portesize; i++) {
        fprintf(f, "%s\n", portes[i].name);  // Nom de l'objet sur une ligne
        fprintf(f, "%s\n", portes[i].description); // Description sur une ligne
        fprintf(f, "%d\n", portes[i].clef); // clef sur une ligne
    }
    // Sauvegarder les PNJ
    fprintf(f, "%d\n", pnjsize);
    fprintf(f, "%d\n", pnjcapacity);
    for (int i = 0; i < pnjsize; i++) {
        fprintf(f, "%s\n", pnj[i].name);  // Nom de l'objet sur une ligne
        fprintf(f, "%s\n", pnj[i].description); // Description sur une ligne
        fprintf(f, "%d\n", pnj[i].health); // hp sur une ligne
        fprintf(f, "%d\n", pnj[i].statue); // statue sur une ligne
        fprintf(f, "%d\n", pnj[i].id); // id sur une ligne
    }
    // Sauvegarder les dialogue
    fprintf(f, "%d\n", diasize);
    fprintf(f, "%d\n", diacapacity);
    for (int i = 0; i < diasize; i++) {
        fprintf(f, "%s\n", dia[i].texte);  // texte sur une ligne
        fprintf(f, "%d\n", dia[i].choix); // choix sur une ligne
        fprintf(f, "%d\n", dia[i].ordre); // ordre sur une ligne
    }
    // Sauvegarder les reponse
    fprintf(f, "%d\n", repsize);
    fprintf(f, "%d\n", repcapacity);
    for (int i = 0; i < repsize; i++) {
        fprintf(f, "%s\n", rep[i].rep);  // reponse sur une ligne
        fprintf(f, "%d\n", rep[i].ordre); // ordre sur une ligne
        fprintf(f, "%d\n", rep[i].id); // id sur une ligne
    }
    // Sauvegarder les lieux
    fprintf(f, "%d\n", lieusize);
    fprintf(f, "%d\n", lieucapacity);
    for (int i = 0; i < lieusize; i++) {
        fprintf(f, "%s\n", locations[i].name);
        fprintf(f, "%s\n", locations[i].description);
        fprintf(f, "%d\n", locations[i].numero);
        for (int j = 0; j < 10; j++) {
            fprintf(f, "%s\n", locations[i].inventory[j].name); // Chaque objet de l'inventaire sur une ligne
            fprintf(f, "%s\n", locations[i].inventory[j].description);
            fprintf(f, "%d\n", locations[i].inventory[j].value);
        }
        for (int j = 0; j < 10; j++) {
            fprintf(f, "%s\n", locations[i].portes[j].name); // Chaque porte de l'inventaire sur 3 ligne
            fprintf(f, "%s\n", locations[i].portes[j].description);
            fprintf(f, "%d\n", locations[i].portes[j].clef);
        }
        for (int j = 0; j < 10; j++) {
            fprintf(f, "%s\n", locations[i].entities[j].name); // Chaque entitee de l'inventaire sur une ligne
            fprintf(f, "%s\n", locations[i].entities[j].description);
            fprintf(f, "%d\n", locations[i].entities[j].health);
            fprintf(f, "%d\n", locations[i].entities[j].statue);
            fprintf(f, "%d\n", locations[i].entities[j].id);
        }
    }

    // Sauvegarder les personnages
    fprintf(f, "%d\n", persosize);
    fprintf(f, "%d\n", persocapacity);
    for (int i = 0; i < persosize; i++) {
        fprintf(f, "%s\n", Characters[i].name);
        fprintf(f, "%d\n", Characters[i].health);
        fprintf(f, "%s\n", Characters[i].current_location->name);
        for (int j = 0; j < 5; j++) {
            fprintf(f, "%s\n", Characters[i].inventory[j].name); // Chaque objet de l'inventaire sur une ligne
            fprintf(f, "%s\n", Characters[i].inventory[j].description);
            fprintf(f, "%d\n", Characters[i].inventory[j].value);
        }
    }
    fclose(f);
    printf("Jeu sauvegarde avec succes dans %s.\n", nomFichier);
}
void chargerJeu(const char *nomFichier, Object **objects, int *objsize, int *objcapacity, Location **locations, int *lieusize, int *lieucapacity, C **Characters, int *persosize, int *persocapacity, Porte **portes, int *portesize, int *portecapacity, PNJ **pnj, int *pnjsize, int *pnjcapacity, Dialogue **dia, int *diasize, int *diacapacity, Reponse **rep, int *repsize, int *repcapacity) {

    FILE *f = fopen(nomFichier, "r");
    if (!f) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    // Charger les objets
    fscanf(f, "%d\n", objsize);
    fscanf(f, "%d\n", objcapacity);
    *objects = malloc(*objcapacity * sizeof(Object));
    for (int i = 0; i < *objsize; i++) {
        fscanf(f, "%[^\n]\n", (*objects)[i].name);  // Lire le nom de l'objet
        fscanf(f, "%d\n", &(*objects)[i].value); // Lire la valeur
        fscanf(f, "%[^\n]\n", (*objects)[i].description);  // Lire la description
    }
    // Charger les portes
    fscanf(f, "%d\n", portesize);
    fscanf(f, "%d\n", portecapacity);
    *portes = malloc(*portecapacity * sizeof(Porte));
    for (int i = 0; i < *portesize; i++) {
        fscanf(f, "%[^\n]\n", (*portes)[i].name);  // Lire le nom de l'objet
        fscanf(f, "%[^\n]\n", (*portes)[i].description);  // Lire la description
        fscanf(f, "%d\n", &(*portes)[i].clef); // Lire la clef
    }
    // Charger les PNJ
    fscanf(f, "%d\n", pnjsize);
    fscanf(f, "%d\n", pnjcapacity);
    *pnj = malloc(*pnjcapacity * sizeof(PNJ));
    for (int i = 0; i < *pnjsize; i++) {
        fscanf(f, "%[^\n]\n", (*pnj)[i].name);  // Lire le nom de l'entitee
        fscanf(f, "%[^\n]\n", (*pnj)[i].description);  // Lire la description
        fscanf(f, "%d\n", &(*pnj)[i].health); // Lire la vie
        fscanf(f, "%d\n", &(*pnj)[i].statue); // Lire le statue
        fscanf(f, "%d\n", &(*pnj)[i].id); // Lire l id
    }
    // Charger les Dialogue
    fscanf(f, "%d\n", diasize);
    fscanf(f, "%d\n", diacapacity);
    *dia = malloc(*diacapacity * sizeof(Dialogue));
    for (int i = 0; i < *diasize; i++) {
        fscanf(f, "%[^\n]\n", (*dia)[i].texte);  // Lire le texte
        fscanf(f, "%d\n", &(*dia)[i].choix); // Lire le choix
        fscanf(f, "%d\n", &(*dia)[i].ordre); // Lire l'ordre
    }
    // Charger les reponse
    fscanf(f, "%d\n", repsize);
    fscanf(f, "%d\n", repcapacity);
    *rep = malloc(*repcapacity * sizeof(Reponse));
    for (int i = 0; i < *repsize; i++) {
        fscanf(f, "%[^\n]\n", (*rep)[i].rep);  // Lire la reponse
        fscanf(f, "%d\n", &(*rep)[i].ordre); // Lire l'ordre
        fscanf(f, "%d\n", &(*rep)[i].id); // Lire l'id
    }
    // Charger les lieux
    fscanf(f, "%d\n", lieusize);
    fscanf(f, "%d\n", lieucapacity);
    *locations = malloc(*lieucapacity * sizeof(Location));
    for (int i = 0; i < *lieusize; i++) {
        fscanf(f, "%[^\n]\n", (*locations)[i].name);
        fscanf(f, "%[^\n]\n", (*locations)[i].description);
        fscanf(f, "%d\n", &(*locations)[i].numero);
        for (int j = 0; j < 10; j++) {
            fscanf(f, "%[^\n]\n", (*locations)[i].inventory[j].name);  // Lire chaque objet
            fscanf(f, "%[^\n]\n", (*locations)[i].inventory[j].description);
            fscanf(f, "%d\n", &(*locations)[i].inventory[j].value);
        }
        for (int j = 0; j < 10; j++) {
            fscanf(f, "%[^\n]\n", (*locations)[i].portes[j].name);  // Lire chaque porte
            fscanf(f, "%[^\n]\n", (*locations)[i].portes[j].description);
            fscanf(f, "%d\n", &(*locations)[i].portes[j].clef);
        }
        for (int j = 0; j < 10; j++) {
            fscanf(f, "%[^\n]\n", (*locations)[i].entities[j].name);// Lire chaque pnj
            fscanf(f, "%[^\n]\n", (*locations)[i].entities[j].description);
            fscanf(f, "%d\n", &(*locations)[i].entities[j].health);
            fscanf(f, "%d\n", &(*locations)[i].entities[j].statue);
            fscanf(f, "%d\n", &(*locations)[i].entities[j].id);
        }
    }

    // Charger les personnages
    fscanf(f, "%d\n", persosize);
    fscanf(f, "%d\n", persocapacity);
    *Characters = malloc(*persocapacity * sizeof(C));
    for (int i = 0; i < *persosize; i++) {
        fscanf(f, "%[^\n]\n", (*Characters)[i].name);
        fscanf(f, "%d\n", &(*Characters)[i].health);
        char locName[50];
        fscanf(f, "%[^\n]\n", locName);

        // Associer le pointeur de location
        for (int j = 0; j < *lieusize; j++) {
            if (strcmp(locName, (*locations)[j].name) == 0) {
                (*Characters)[i].current_location = &(*locations)[j];
                break;
            }
        }
        // Charger l'inventaire
        for (int j = 0; j < 5; j++) {
            fscanf(f, "%[^\n]\n", (*Characters)[i].inventory[j].name);  // Lire chaque objet
            fscanf(f, "%[^\n]\n", (*Characters)[i].inventory[j].description);
            fscanf(f, "%d\n", &(*Characters)[i].inventory[j].value);
        }
    }

    fclose(f);
    printf("Jeu charge avec succes depuis %s.\n", nomFichier);
}

void inventaire(C **Characters, int *perso) {
    printf("inventaire : \n");
    for (int j = 0; j < 5; j++) {
        printf("%d. %s \n", j+1, (*Characters)[*perso-1].inventory[j].name);
    }
}
void aller(Location **location, C **characters, int *perso , int *lieusize) {
    int location_choice;
    int id = (*characters)[*perso-1].current_location->numero;
    int correspondances[*lieusize]; // tableau temporaire pour index réels
    int nb_options = 0;
    printf("Vous ete a %s, \nchoisisser le numero corespondant a votre destination : \n", (*characters)[*perso-1].current_location->name);

    for (int i = 0; i < *lieusize; i++) {
        int diff = id - (*location)[i].numero;
        if (diff >= -1 && diff <= 1) {
            printf("%d. %s\n", nb_options + 1, (*location)[i].name);
            correspondances[nb_options] = i;
            nb_options++;
        }
    }
    printf("Votre choix : ");
    scanf("%d", &location_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (location_choice < 1 || location_choice > nb_options) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index_choisi = correspondances[location_choice - 1];
    (*characters)[*perso -1].current_location = &(*location)[index_choisi];
    afficherCharacter(characters,perso,perso);
}
void prendre(C **characters, int *perso) {
    int objet_choice;
    int correspondances[10]; // tableau temporaire pour index réels
    int nb_options = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp((*characters)[*perso - 1].current_location->inventory[i].name, "VIDE") != 0) {
            printf("%d. %s \n", nb_options + 1, (*characters)[*perso-1].current_location->inventory[i]);
            correspondances[nb_options] = i;
            nb_options++;
        }
    }
    if (nb_options == 0) {
        printf("Le lieu est vide imposible de prendre un objet.");
        return;
    }
    printf("Votre choix : ");
    scanf("%d", &objet_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (objet_choice < 1 || objet_choice > nb_options) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index_choisi = correspondances[objet_choice - 1];
    int placed = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp((*characters)[*perso - 1].inventory[i].name, "VIDE") == 0) {
            (*characters)[*perso - 1].inventory[i] = (*characters)[*perso - 1].current_location->inventory[index_choisi];
            placed = 1;
            break;
        }
    }
    if (!placed) {
        printf("Inventaire plein, impossible d'ajouter un objet.\n");
        return;
    }
    for (int i = 0; i < 10; i++) {
        if (strcmp((*characters)[*perso-1].current_location->inventory[i].name, (*characters)[*perso-1].current_location->inventory[index_choisi].name) == 0) {
            (*characters)[*perso-1].current_location->inventory[i] = OBJET_VIDE;
            break;
        }
    }
    inventaire(characters, perso);
}
void lacher(C **characters, int *perso) {
    int objet_choice;
    int correspondances[5]; // tableau temporaire pour index réels
    int nb_options = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp((*characters)[*perso - 1].inventory[i].name, "VIDE") != 0) {
            printf("%d. %s \n", nb_options + 1, (*characters)[*perso-1].inventory[i]);
            correspondances[nb_options] = i;
            nb_options++;
        }
    }
    if (nb_options == 0) {
        printf("Votre inventaire est vide imposible de lacher un objet.");
        return;
    }
    printf("Votre choix : ");
    scanf("%d", &objet_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (objet_choice < 1 || objet_choice > nb_options) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index_choisi = correspondances[objet_choice - 1];
    int placed = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp((*characters)[*perso - 1].current_location->inventory[i].name, "VIDE") == 0) {
            (*characters)[*perso - 1].current_location->inventory[i] = (*characters)[*perso - 1].inventory[index_choisi];
            placed = 1;
            break;
        }
    }
    if (!placed) {
        printf("Lieu plein, impossible de lacher un objet.\n");
        return;
    }
    for (int i = 0; i < 5; i++) {
        if (strcmp((*characters)[*perso-1].inventory[i].name, (*characters)[*perso-1].inventory[index_choisi].name) == 0) {
            (*characters)[*perso-1].inventory[i] = OBJET_VIDE;
            break;
        }
    }
    inventaire(characters, perso);
}
void examiner(C **characters, int *perso, Object **objets, int *objsize) {
    int objet_choice;
    int correspondances[5]; // tableau temporaire pour index réels
    int nb_options = 0;
    for (int i = 0; i < 5; i++) {
        if (strcmp((*characters)[*perso - 1].inventory[i].name, "VIDE") != 0) {
            printf("%d. %s \n", nb_options + 1, (*characters)[*perso-1].inventory[i]);
            correspondances[nb_options] = i;
            nb_options++;
        }
    }
    if (nb_options == 0) {
        printf("Votre inventaire est vide imposible d examiner un objet.");
        return;
    }
    printf("Votre choix : ");
    scanf("%d", &objet_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (objet_choice < 1 || objet_choice > nb_options) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index_choisi = correspondances[objet_choice - 1];
    char *desc = NULL;
    for (int i = 0; i < *objsize; i++) {
        if (strcmp((*characters)[*perso - 1].inventory[index_choisi].name, (*objets)[i].name) == 0) {
            desc = (*objets)[i].description;
            break; // une fois trouvé, inutile de continuer
        }
    }
    if (desc != NULL) {
        printf("La description de %s est : %s.\n\n", (*characters)[*perso - 1].inventory[index_choisi].name, desc);
    } else {
        printf("Objet non trouvé dans la liste des objets.\n\n");
    }
}
void examiner_lieu(C **characters,int *perso) {
    printf("Description du lieu : %s\n\n",(*characters)[*perso - 1].current_location->description);
}
void ouvrir(C **characters, int *perso, Location **lieu, int *lieusize , Porte **porte) {
    int porte_choice;
    int correspondances[10]; // lien entre option affichée et index réel
    int nb_options = 0;

    C *joueur = &(*characters)[*perso - 1];
    Location *lieu_actuel = joueur->current_location;

    // Liste les portes valides
    for (int i = 0; i < 10; i++) {
        if (strcmp(lieu_actuel->portes[i].name, "VIDE") != 0) {
            printf("%d. %s\n", nb_options + 1, lieu_actuel->portes[i].name);
            correspondances[nb_options] = i;
            nb_options++;
        }
    }

    if (nb_options == 0) {
        printf("Le lieu ne contient pas de porte.\n");
        return;
    }

    printf("Votre choix : ");
    scanf("%d", &porte_choice);
    while(getchar() != '\n'); // vider le buffer

    if (porte_choice < 1 || porte_choice > nb_options) {
        printf("Choix invalide, annulation.\n");
        return;
    }

    int index_choisi = correspondances[porte_choice - 1];
    Porte *p = &lieu_actuel->portes[index_choisi];
    // Vérifie si la clé est dans l'inventaire
    int clef_trouvee = 0;
    for (int i = 0; i < 5; i++) {
        if (joueur->inventory[i].value == p->clef) {
            clef_trouvee = 1;
            // Mise à jour de la destination
            for (int j = 0; j < *lieusize; j++) {
                if ((*lieu)[j].numero == p->clef) {
                    (*lieu)[j].numero = lieu_actuel->numero + 1;
                    printf("La porte %s est ouverte.\n", p->name);
                    printf("Vous pouvez maintenant aller dans un nouveau lieu avec la commande 'aller'.\n");
                    return;
                }
            }

            // Clé trouvée mais lieu non trouvé
            printf("Erreur, clef trouvée mais aucun lieu ne correspond.\n");
            return;
        }
    }

    // Si on arrive ici, c’est que la clé n’a pas été trouvée
    printf("Votre inventaire ne contient pas la clef de cette porte.\n");
}
void dialogue(int id, int *diasize, int *repsize, Reponse **rep, Dialogue **dia) {
    int reponse_choice;
    int correspondances[*repsize]; // tableau temporaire pour index réels
    int nb_options = 0;
    int placed=0;
    for (int i = 0; i < *diasize; i++) {
        if (id==(*dia)[i].ordre) {
            printf("%s\n", (*dia)[i].texte);
            placed=1;
            for (int j = 0; j < *repsize; j++) {
                if ((*rep)[j].ordre==(*dia)[i].ordre) {
                    printf("%d. %s\n", nb_options + 1, (*rep)[j].rep);
                    correspondances[nb_options] = j;
                    nb_options++;
                }
            }
            if (nb_options == 0) {
                printf("Fin de la conversation.\n");
                return;
            }
            break;
        }

    }
    if (placed == 0) {
        printf("Conversation terminer.\n");
        return;
        }

    printf("Votre choix : ");
    scanf("%d", &reponse_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (reponse_choice < 1 || reponse_choice > nb_options) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index_choisi = correspondances[reponse_choice - 1];
    dialogue((*rep)[index_choisi].id, diasize, repsize, rep, dia);
}
void parler(C **characters,int *perso, Reponse **rep, int *repsize, Dialogue **dia, int *diasize) {
    int entitee_choice;
    int correspondances[10]; // tableau temporaire pour index réels
    int nb_options = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp((*characters)[*perso - 1].current_location->entities[i].name, "VIDE") != 0) {
            printf("%d. %s \n", nb_options + 1, (*characters)[*perso-1].current_location->entities[i].name);
            correspondances[nb_options] = i;
            nb_options++;
        }
    }
    if (nb_options == 0) {
        printf("Le lieu ne contient pas d entitee.");
        return;
    }
    printf("Votre choix : ");
    scanf("%d", &entitee_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (entitee_choice < 1 || entitee_choice > nb_options) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index_choisi = correspondances[entitee_choice -1];
    dialogue((*characters)[*perso-1].current_location->entities[index_choisi].id, diasize, repsize, rep, dia);
}
void combat(C **characters, int *perso, int mob) {
    int arme_choice;
    int correspondances[10]; // tableau temporaire pour index réels
    int nb_options = 0;
    int vide = 0;
    int degat;
    int min;
    int max;

    for (int i = 0; i < 5; i++) {
        if (strcmp((*characters)[*perso - 1].inventory[i].name, "VIDE") != 0 && (((*characters)[*perso - 1].inventory[i].value)/1000000000)==1) {
            vide++;
        }
    }
    if (vide == 0) {
        min=6;
        max=12;
    }   else {
        printf("C est a vous d'attaquer,\navec quelle arme voulez vous attaquer ?\n");
        for (int i = 0; i < 10; i++) {
            if (strcmp((*characters)[*perso - 1].inventory[i].name, "VIDE") != 0 && (((*characters)[*perso - 1].inventory[i].value)/1000000000)==1) {
                printf("%d. %s \n", nb_options + 1, (*characters)[*perso-1].inventory[i].name);
                correspondances[nb_options] = i;
                nb_options++;
            }
        }
        printf("Votre choix : ");
        scanf("%d", &arme_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (arme_choice < 1 || arme_choice > nb_options) {
            printf("Choix invalide, annulation.\n");
            return;
        }
        int index_choisi = correspondances[arme_choice -1];
        min = (*characters)[*perso - 1].inventory[index_choisi].value/1000 % 1000;
        max = (*characters)[*perso - 1].inventory[index_choisi].value % 1000;
    }

    degat = rand() % (max - min + 1) + min;
    if (vide != 0) {
        int index_choisi = correspondances[arme_choice -1];
        if (rand() % 100 < (*characters)[*perso - 1].inventory[index_choisi].value/1000000 % 1000) {
            degat *= 2;
            printf("Vous avez fait un coup critique.\n");
        }
    }
    (*characters)[*perso - 1].current_location->entities[mob].health -= degat;
    printf("Votre adversaire prend %d degat, il a maintenant %d point de vie.\n\n", degat, (*characters)[*perso - 1].current_location->entities[mob].health);
    if ((*characters)[*perso - 1].current_location->entities[mob].health <= 0) {
        printf("Vous avez triompher de votre adversaire.\n\n");
        return;
    }
    min = (*characters)[*perso - 1].current_location->entities[mob].statue/1000 % 1000;
    max = (*characters)[*perso - 1].current_location->entities[mob].statue % 1000;
    degat = rand() % (max - min + 1) + min;
    if (rand() % 100 < (*characters)[*perso - 1].current_location->entities[mob].statue/1000000 % 1000) {
        degat *= 2;
        printf("Votre adversaire a fait un coup critique.\n");
    }

    (*characters)[*perso - 1].health -= degat;
    printf("Votre adversaire vous attaque, vous perder %d point de vie, il vous reste %d point de vie.\n\n", degat, (*characters)[*perso - 1].health);
    if ((*characters)[*perso - 1].health <= 0) {
        printf("GAME OVER\n\n");
        exit(0);
    }
    combat(characters, perso, mob);
}
void combatre(C **characters,int *perso) {
    int entitee_choice;
    int correspondances[10]; // tableau temporaire pour index réels
    int nb_options = 0;
    for (int i = 0; i < 10; i++) {
        if ((strcmp((*characters)[*perso - 1].current_location->entities[i].name, "VIDE") != 0 && (((*characters)[*perso - 1].current_location->entities[i].statue)/1000000000)==1) & (*characters)[*perso - 1].current_location->entities[i].health >= 0) {
            printf("%d. %s \n", nb_options + 1, (*characters)[*perso-1].current_location->entities[i].name);
            correspondances[nb_options] = i;
            nb_options++;
        }
    }
    if (nb_options == 0) {
        printf("Le lieu ne contient pas d ennemis.\n");
        return;
    }
    printf("Votre choix : ");
    scanf("%d", &entitee_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (entitee_choice < 1 || entitee_choice > nb_options) {
        printf("Choix invalide, annulation.\n");
        return;
    }
    int index_choisi = correspondances[entitee_choice -1];
    combat(characters, perso, index_choisi);
}


int main(void) {
    srand(time(NULL));
    char action[50];
    char rep[10];
    char nomFichier[100];
    int personnage_choice;
    int objSize = 0, objCapacity = 2;
    Object *objects = malloc(objCapacity * sizeof(Object));
    int porteSize = 0, porteCapacity = 2;
    Porte *portes = malloc(porteCapacity * sizeof(Porte));
    int pnjSize = 0, pnjCapacity = 2;
    PNJ *pnj = malloc(pnjCapacity * sizeof(PNJ));
    int diaSize = 0, diaCapacity = 2;
    Dialogue *dialogues = malloc(diaCapacity * sizeof(Dialogue));
    int repSize = 0, repCapacity = 2;
    Reponse *reponses = malloc(repCapacity * sizeof(Reponse));
    int lieuSize = 0, lieuCapacity = 2;
    Location *Locations = malloc(lieuCapacity * sizeof(Location));
    int persoSize = 0, persoCapacity = 2;
    C *Characters = malloc(persoCapacity * sizeof(C));

    printf("Pour passer en mode admin taper A, sinon taper play : ");
    fgets(rep, sizeof(rep), stdin);
    if (strcmp(rep, "A\n") == 0) {
        do {
            printf("A:/Entrez une action, \ntaper help pour plus d'information : ");
            fgets(action,sizeof(action), stdin);
            action[strcspn(action, "\n")] = '\0';
            if (strcmp(action, "help") == 0) {
                printf("Les commandes disonible sont :\ncreer_objet : Creation d un objet\ncreer_porte : Creation d une porte\ncreer_entitee : Creation d une entitee\ncreer_dialogue : creation d un dialogue\ncreer_lieu : creation d un lieu\ncreer_personnage : Creation d un personnage\ndeplacement : change le lieu d un personnage\naj_objet : ajoute un objet a l inventaire  d un personnage ou d un lieu\naj_porte : ajoute une porte a un lieu\naj_entitee : ajoute une entitee a un lieu\nsuppr_objet : suprime un objet de l inventaire d un personnage ou d un lieu\nsuppr_porte : suprime une porte d un lieu\nsuppr_entitee : suprime une entitee d un lieu\ntout_voir : affiche toutes les structures\nplay : lance la partie en tant que joueur\nsauvegarder : sauvegarde\ncharger : charge une sauvegarde\nDoc : ouvre la documentation\n\n");
            }
            else if (strcmp(action, "creer_objet") == 0) {
                ajouter_objects(&objects, &objSize, &objCapacity);
            }
            else if (strcmp(action, "creer_porte") == 0) {
                ajouter_portes(&portes, &porteSize, &porteCapacity);
            }
            else if (strcmp(action, "creer_entitee") == 0) {
                ajouter_PNJ(&pnj, &pnjSize, &pnjCapacity);
            }
            else if (strcmp(action, "creer_dialogue") == 0) {
                initDialogue(&pnj, &pnjSize, &dialogues, &diaSize, &diaCapacity, &reponses, &repSize, &repCapacity);
            }
            else if (strcmp(action, "creer_lieu") == 0) {
                ajouter_lieu(&Locations, &lieuSize, &lieuCapacity);
            }
            else if (strcmp(action, "creer_personnage") == 0) {
                ajouter_Character(&Characters, &persoSize, &persoCapacity, Locations, lieuSize);
            }
            else if (strcmp(action, "deplacement") == 0) {
                deplacement(&persoSize, &lieuSize, Locations, Characters);
            }
            else if (strcmp(action, "aj_objet") == 0) {
                char ajchoix[10];
                printf("Voulez vous ajouter un objet a un lieu(taper L) ou a  un personnage(taper P).");
                fgets(ajchoix,sizeof(ajchoix), stdin);
                ajchoix[strcspn(ajchoix, "\n")] = '\0';
                if (strcmp(ajchoix, "P") == 0) {
                    ajObject(Characters, &persoSize, objects, &objSize);
                }
                else if (strcmp(ajchoix, "L") == 0) {
                    ajObject_lieu(Locations, &lieuSize, objects, &objSize);
                }
            }
            else if (strcmp(action, "aj_porte") == 0) {
                ajPorte_lieu(Locations, &lieuSize, portes, &porteSize);
            }
            else if (strcmp(action, "aj_entitee") == 0) {
                ajPNJ_lieu(Locations, &lieuSize, pnj, &pnjSize);
            }
            else if (strcmp(action, "supr_objet") == 0) {
                char suprchoix[10];
                printf("Voulez vous suprimer un objet d un lieu(taper L) ou d un personnage(taper P).");
                fgets(suprchoix,sizeof(suprchoix), stdin);
                suprchoix[strcspn(suprchoix, "\n")] = '\0';
                if (strcmp(suprchoix, "P") == 0) {
                    suprObject(Characters, &persoSize, objects, &objSize);
                }
                else if (strcmp(suprchoix, "L") == 0) {
                    suprObject_lieu(Locations, &lieuSize, objects, &objSize);
                }
            }
            else if (strcmp(action, "supr_porte") == 0) {
                suprPorte_lieu(Locations, &lieuSize, portes, &porteSize);
            }
            else if (strcmp(action, "supr_entitee") == 0) {
                suprPNJ_lieu(Locations, &lieuSize, pnj, &pnjSize);
            }
            else if (strcmp(action, "tout_voir") == 0) {
                tout_afficher(&Characters, &persoSize, &objects, &objSize, &Locations, &lieuSize, &pnj, &pnjSize, &portes, &porteSize, &dialogues, &diaSize, &reponses, &repSize);
            }
            else if (strcmp(action, "sauvegarder") == 0) {
                printf("Entrez le nom du fichier de sauvegarde (ex: save.txt) : ");
                fgets(nomFichier, sizeof(nomFichier), stdin);
                nomFichier[strcspn(nomFichier, "\n")] = '\0';  // Supprime le \n
                sauvegarderJeu(nomFichier, objects, objSize, objCapacity, Locations, lieuSize, lieuCapacity, Characters, persoSize, persoCapacity, portes, porteSize, porteCapacity, pnj , pnjSize, pnjCapacity, dialogues, diaSize, diaCapacity, reponses, repSize, repCapacity);
            }
            else if (strcmp(action, "charger") == 0) {
                printf("Entrez le nom du fichier a charger (ex: save.txt) : ");
                fgets(nomFichier, sizeof(nomFichier), stdin);
                nomFichier[strcspn(nomFichier, "\n")] = '\0';
                chargerJeu(nomFichier, &objects, &objSize, &objCapacity, &Locations, &lieuSize, &lieuCapacity, &Characters, &persoSize, &persoCapacity, &portes, &porteSize, &porteCapacity, &pnj ,&pnjSize, &pnjCapacity, &dialogues, &diaSize, &diaCapacity, &reponses, &repSize, &repCapacity);
            }
            else if (strcmp(action, "Doc") == 0) {
                printf("Cette documentation a pour but d aider a creer une aventure.\n\n\n1. Le numero des lieux entree a la creation de ce dernier corespond a sont emplacement, \net determine les posiblitees de deplacement au sein des different lieux.\n(ex : si le lieu A a pour numero '1', \nalors lorsque le personnage si trouve il peut se rendre dans tout les lieux de numero 0, 1, 2.)\n\n ");
                printf("2. le systeme de porte fonctione avec les clef, le champ clef de la structure Porte doit etre\n egal a la valeur de l objet qui represente la clef de la porte\n et doit aussi etre egale au numero du lieu au quelle permet d acceder.\n(ex : si on a une porte a laquelle on donne la valeur 99, alors on donne a la valeur de l objet clef et au numero de la salle la valeur 99.)\n\n");
                printf("3. Le systeme de dialogue fonctionne avec les id des entitees que l on indique a la creation de l entitee.\nL id a sont importance car il determine le nombre de question/repnse au sein du dialogue de l entitee.\n(ex : si l entitee A a pour id 0, et l entitee B a 10, \nalors l entitee A poura avoir seulement 10 enchange question/reponse au sein de sont dialogue.)\nsi il y a plus d enchange question/reponse que la difference entre l id des entitees, \nalors le systme de dialogue ne fonctionera pas corectement.\n\n");
                printf("4. Le systeme de combat fonctione avec la valeur des objets et le statue des entitees.\nLa valeur de l objet determine sa puissance, pour etre considere comme une arme,\n un objet doit avoir une valeur de ce type'1010017026', idem pour le statue de l entitee.\n(ex : pour la valeur 1010017026, le premier chiffre determine que l objet est une arme, \ndoit valoir 1 si c est une arme et 0 sinon.\nPour les chiffre suivant on ne les ecrire que si c est une arme.\nDonc les trois chiffre suivant 010 determine le taux de coup critique soit dans l'example 10 pour cent.\nLes trois chiffres suivant 017 represante les degats minimum de l objet soit 17 dans l exemple.\nLes trois suivant et dernier chiffre represante le degats maximum de l objet soit dans l example 26.)\n\n");
                printf("Si tu charge la sauvegarde EcurLand.txt tu poura vivre une aventure au royaume des ecureuil.\n");
            }
        } while (strcmp(action, "play") != 0);

    }
    if (strcmp(rep, "play\n") == 0 || strcmp(action, "play") == 0) {
        if (persoSize == 0) {
            printf("Erreur aucun personnage.\n\n");
        }
        else {
            do {
                if (persoSize > 1) {
                    printf("Choisissez un personnage, \nEntrer le numero correspondant :\n");
                    for (int i = 0; i < persoSize; ++i) {
                        printf("%d. %s\n", i + 1, Characters[i].name);
                    }

                    printf("Votre choix : ");
                    scanf("%d", &personnage_choice);
                    while(getchar() != '\n'); // nettoyer le buffer

                    if (personnage_choice < 1 || personnage_choice > persoSize) {
                        printf("Choix invalide.\n\n");
                    }

                }   else {personnage_choice=1;}
            } while (personnage_choice < 1 || personnage_choice > persoSize);

                do {
                    printf("J:/Entrez une action, \ntaper help pour plus d'information : ");
                    fgets(action,sizeof(action), stdin);
                    action[strcspn(action, "\n")] = '\0';
                    if (strcmp(action, "help") == 0) {
                        printf("Les commandes disonible sont :\naller\nprendre\nlacher\ninventaire\nexaminer\nouvrir\ncombatre\nsauvegarder : sauvegarde la progression\nquit : quit la partie\n\n");
                    }
                    else if (strcmp(action, "inventaire") == 0) {
                        inventaire(&Characters, &personnage_choice);
                    }
                    else if (strcmp(action, "aller") == 0) {
                        aller(&Locations, &Characters, &personnage_choice, &lieuSize);
                    }
                    else if (strcmp(action, "ouvrir") == 0) {
                        ouvrir(&Characters, &personnage_choice, &Locations, &lieuSize, &portes);
                    }
                    else if (strcmp(action, "prendre") == 0) {
                        prendre(&Characters, &personnage_choice);
                    }
                    else if (strcmp(action, "lacher") == 0) {
                        lacher(&Characters, &personnage_choice);
                    }
                    else if (strcmp(action, "parler") == 0) {
                        parler(&Characters, &personnage_choice, &reponses, &repSize, &dialogues, &diaSize);
                    }
                    else if (strcmp(action, "combatre") == 0) {
                        combatre(&Characters, &personnage_choice);
                    }
                    else if (strcmp(action, "examiner") == 0) {
                        char exchoix[10];
                        printf("Voulez vous examiner le lieu(taper L) ou a un objet de votre inventaire(taper O).");
                        fgets(exchoix,sizeof(exchoix), stdin);
                        exchoix[strcspn(exchoix, "\n")] = '\0';
                        if (strcmp(exchoix, "O") == 0) {
                            examiner(&Characters, &personnage_choice, &objects, &objSize);
                        }
                        else if (strcmp(exchoix, "L") == 0) {
                            examiner_lieu(&Characters, &personnage_choice);
                        }
                    }
                    else if (strcmp(action, "sauvegarder") == 0) {
                        printf("Entrez le nom du fichier de sauvegarde (ex: save.txt) : ");
                        fgets(nomFichier, sizeof(nomFichier), stdin);
                        nomFichier[strcspn(nomFichier, "\n")] = '\0';  // Supprime le \n
                        sauvegarderJeu(nomFichier, objects, objSize, objCapacity, Locations, lieuSize, lieuCapacity, Characters, persoSize, persoCapacity, portes, porteSize, porteCapacity, pnj , pnjSize, pnjCapacity, dialogues, diaSize, diaCapacity, reponses, repSize, repCapacity);
                    }
                } while (strcmp(action, "quit") != 0);
            }
        }
    return 0;
}
