#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
} PNJ;
PNJ PNJ_VIDE = {"VIDE", "cette emplacement de PNJ est vide", 0, 0};
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
        printf("Erreur aucun object\n\n");
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
        printf("Erreur aucunne porte\n\n");
        return;
    }
    printf("\nListe des portes :\n");
    for (int i = 0; i < *size; i++) {
        printf("Objet %d : %s\n", i + 1, (*portes)[i].name);
        printf("Description : %s\n", (*portes)[i].description);
        printf("Valeur : %d\n\n", (*portes)[i].clef);
    }
}
void afficher_pnj(PNJ **pnj, int *size) {
    if (*size == 0) {
        printf("Erreur aucun pnj\n\n");
        return;
    }
    printf("\nListe des entitees :\n");
    for (int i = 0; i < *size; i++) {
        printf("Objet %d : %s\n", i + 1, (*pnj)[i].name);
        printf("Description : %s\n", (*pnj)[i].description);
        printf("Point de vie : %d\n", (*pnj)[i].health);
        printf("Statue : %d\n\n", (*pnj)[i].statue);
    }
}
void afficher_Location(Location **Locations, int *start, int *size) {
    if (*size == 0) {
        printf("Erreur aucun lieu\n\n");
        return;
    }
    printf("\nListe des Lieu :\n");
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
        printf("Erreur aucun personnage\n\n");
        return;
    }
    for (int i = *start; i <= *size; i++) {
        printf("personnage %d : %s\n", i, (*Characters)[i-1].name);
        printf("PV : %d\n", (*Characters)[i-1].health);
        printf("inventaire : \n");
        for (int j = 0; j < 5; j++) {
            printf("%d. %s \n", j+1, (*Characters)[i-1].inventory[j].name);
        }
        printf("Lieu : %s\n\n", (*Characters)[i-1].current_location->name);
    }
}
void addObject(Object **array, int *size, int *capacity, char *name, char *desc, int value) {
    if (*size >= *capacity) {
        *capacity *= 2;  // Double la capacité
        *array = realloc(*array, *capacity * sizeof(Object));
        if (*array == NULL) {
            printf("Erreur de réallocation mémoire !\n");
            exit(1);
        }
    }

    // Ajout de l'objet
    strcpy((*array)[*size].name, name);
    strcpy((*array)[*size].description, desc);
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
            printf("Erreur de réallocation mémoire !\n");
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
void addPNJ(PNJ **array, int *size, int *capacity, char *name, char *desc, int hp, int statue) {
    if (*size >= *capacity) {
        *capacity *= 2;  // Double la capacité
        *array = realloc(*array, *capacity * sizeof(PNJ));
        if (*array == NULL) {
            printf("Erreur de réallocation mémoire !\n");
            exit(1);
        }
    }

    // Ajout de l'objet
    strcpy((*array)[*size].name, name);
    strcpy((*array)[*size].description, desc);
    (*array)[*size].health = hp;
    (*array)[*size].statue = statue;
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

    addPNJ(entitee, size, capacity, pnj.name, pnj.description, pnj.health, pnj.statue);
    afficher_pnj(entitee, size);
}
void addLieu(Location **array, int *size, int *capacity, char *name, char *desc, int *id) {
    if (*size >= *capacity) {
        *capacity *= 2;  // Double la capacité
        *array = realloc(*array, *capacity * sizeof(Location));
        if (*array == NULL) {
            printf("Erreur de réallocation mémoire !\n");
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
            printf("Erreur de réallocation mémoire !\n");
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
        printf("Erreur aucun lieu\n\n");
        return;
    }

    printf("\nEntrez le nom du Character : ");
    fgets(perso.name, sizeof(perso.name), stdin);
    perso.name[strcspn(perso.name, "\n")] = '\0';  // Supprime le retour à la ligne

    printf("Entrez la bare de vie du Character : ");
    scanf("%d", &perso.health);
    getchar();  // Consomme le '\n' restant après scanf


    printf("Choisissez un lieu de départ :\nEntrer le numero correspondant :\n");
    for (int i = 0; i < location_count; ++i) {
        printf("%d. %s\n", i + 1, available_locations[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &location_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (location_choice < 1 || location_choice > location_count) {
        printf("Choix invalide. Annulation.\n");
        return;
    }
    perso.current_location = &available_locations[location_choice - 1];

    addCharacter(Characters, size, capacity, perso.name, perso.health, perso.current_location);
    int start = 1;
    afficherCharacter(Characters, &start, size);
}
void deplacement(int *persosize, int *lieusize, Location *available_locations, C *available_personnage) {
    int location_choice;
    int personnage_choice;
    if (*persosize == 0) {
        printf("Erreur aucun personnage\n\n");
        return;
    }
    if (*lieusize <= 1) {
        printf("Erreur, il y a 1 ou aucun lieu\n\n");
        return;
    }
    if (*persosize > 1) {
        printf("Choisissez un personnage :\nEntrer le numero correspondant :\n");
        for (int i = 0; i < *persosize; ++i) {
            printf("%d. %s\n", i + 1, available_personnage[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &personnage_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (personnage_choice < 1 || personnage_choice > *persosize) {
            printf("Choix invalide. Annulation.\n");
            return;
        }
    }   else {personnage_choice=1;}

        printf("Choisissez un lieu\nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieusize; ++i) {
            printf("%d. %s\n", i + 1, available_locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &location_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (location_choice < 1 || location_choice > *lieusize) {
            printf("Choix invalide. Annulation.\n");
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
        printf("Erreur aucun personnage\n\n");
        return;
    }
    if (*objsize < 1) {
        printf("Erreur, il y a aucun objet\n\n");
        return;
    }
    if (*persosize > 1) {
        printf("Choisissez un personnage :\nEntrer le numero correspondant :\n");
        for (int i = 0; i < *persosize; ++i) {
            printf("%d. %s\n", i + 1, characters[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &personnage_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (personnage_choice < 1 || personnage_choice > *persosize) {
            printf("Choix invalide. Annulation.\n");
            return;
        }
    }else {personnage_choice=1;}

    afficherCharacter(&characters, &personnage_choice, &personnage_choice);

    printf("Choisissez un objet\nEntrer le numero correspondant :\n");
    for (int i = 0; i < *objsize; ++i) {
        printf("%d. %s\n", i + 1, objects[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &object_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (object_choice < 1 || object_choice > *objsize) {
        printf("Choix invalide. Annulation.\n");
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
        printf("Choisissez un lieu :\nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieusize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieusize) {
            printf("Choix invalide. Annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez un objet\nEntrer le numero correspondant :\n");
    for (int i = 0; i < *objsize; ++i) {
        printf("%d. %s\n", i + 1, objects[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &object_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (object_choice < 1 || object_choice > *objsize) {
        printf("Choix invalide. Annulation.\n");
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
        printf("Choisissez un lieu :\nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieusize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieusize) {
            printf("Choix invalide. Annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez une porte\nEntrer le numero correspondant :\n");
    for (int i = 0; i < *portesize; ++i) {
        printf("%d. %s\n", i + 1, portes[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &porte_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (porte_choice < 1 || porte_choice > *portesize) {
        printf("Choix invalide. Annulation.\n");
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
        printf("lieu plein, impossible d'ajouter une porte.\n");
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
        printf("Choisissez un lieu :\nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieusize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieusize) {
            printf("Choix invalide. Annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez une entitee\nEntrer le numero correspondant :\n");
    for (int i = 0; i < *pnjsize; ++i) {
        printf("%d. %s\n", i + 1, pnj[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &entitee_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (entitee_choice < 1 || entitee_choice > *pnjsize) {
        printf("Choix invalide. Annulation.\n");
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
        printf("lieu plein, impossible d'ajouter une entitee.\n");
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
        printf("Choisissez un personnage :\nEntrer le numero correspondant :\n");
        for (int i = 0; i < *persosize; ++i) {
            printf("%d. %s\n", i + 1, characters[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &personnage_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (personnage_choice < 1 || personnage_choice > *persosize) {
            printf("Choix invalide. Annulation.\n");
            return;
        }
    }else {personnage_choice=1;}

    afficherCharacter(&characters, &personnage_choice, &personnage_choice);

    printf("Choisissez un objet\nEntrer le numero correspondant :\n");
    for (int i = 0; i < *objsize; ++i) {
        printf("%d. %s\n", i + 1, objects[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &object_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (object_choice < 1 || object_choice > *objsize) {
        printf("Choix invalide. Annulation.\n");
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
        printf("objet introuvable.\n");
        return;
    }
    afficherCharacter(&characters, &personnage_choice, &personnage_choice);
}
void suprObject_lieu(Location *locations, int *lieuosize, Object *objects, int *objsize) {
    int lieu_choice;
    int object_choice;
    if (*lieuosize == 0) {
        printf("Erreur aucun lieu\n\n");
        return;
    }
    if (*objsize < 1) {
        printf("Erreur, il y a aucun objet\n\n");
        return;
    }
    if (*lieuosize > 1) {
        printf("Choisissez un lieu :\nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieuosize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieuosize) {
            printf("Choix invalide. Annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez un objet\nEntrer le numero correspondant :\n");
    for (int i = 0; i < *objsize; ++i) {
        printf("%d. %s\n", i + 1, objects[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &object_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (object_choice < 1 || object_choice > *objsize) {
        printf("Choix invalide. Annulation.\n");
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
        printf("objet introuvable.\n");
        return;
    }
    afficher_Location(&locations, &lieu_choice, &lieu_choice);
}
void suprPorte_lieu(Location *locations, int *lieuosize, Porte *portes, int *portesize) {
    int lieu_choice;
    int porte_choice;
    if (*lieuosize == 0) {
        printf("Erreur aucun lieu\n\n");
        return;
    }
    if (*portesize < 1) {
        printf("Erreur, il y a aucune porte\n\n");
        return;
    }
    if (*lieuosize > 1) {
        printf("Choisissez un lieu :\nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieuosize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieuosize) {
            printf("Choix invalide. Annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez une porte\nEntrer le numero correspondant :\n");
    for (int i = 0; i < *portesize; ++i) {
        printf("%d. %s\n", i + 1, portes[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &porte_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (porte_choice < 1 || porte_choice > *portesize) {
        printf("Choix invalide. Annulation.\n");
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
        printf("Erreur aucun lieu\n\n");
        return;
    }
    if (*pnjsize < 1) {
        printf("Erreur, il y a aucune entitee\n\n");
        return;
    }
    if (*lieuosize > 1) {
        printf("Choisissez un lieu :\nEntrer le numero correspondant :\n");
        for (int i = 0; i < *lieuosize; ++i) {
            printf("%d. %s\n", i + 1, locations[i].name);
        }

        printf("Votre choix : ");
        scanf("%d", &lieu_choice);
        while(getchar() != '\n'); // nettoyer le buffer

        if (lieu_choice < 1 || lieu_choice > *lieuosize) {
            printf("Choix invalide. Annulation.\n");
            return;
        }
    }else {lieu_choice=1;}

    afficher_Location(&locations, &lieu_choice, &lieu_choice);

    printf("Choisissez une entitee\nEntrer le numero correspondant :\n");
    for (int i = 0; i < *pnjsize; ++i) {
        printf("%d. %s\n", i + 1, pnj[i].name);
    }

    printf("Votre choix : ");
    scanf("%d", &PNJ_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (PNJ_choice < 1 || PNJ_choice > *pnjsize) {
        printf("Choix invalide. Annulation.\n");
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
        printf("porte introuvable.\n");
        return;
    }
    afficher_Location(&locations, &lieu_choice, &lieu_choice);
}
void sauvegarderJeu(const char *nomFichier, Object *objects, int objsize, Location *locations, int lieusize, C *Characters, int persosize, Porte *portes, int portesize, PNJ *pnj, int pnjsize) {
    FILE *f = fopen(nomFichier, "w");
    if (!f) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Sauvegarder les objets
    fprintf(f, "%d\n", objsize);
    for (int i = 0; i < objsize; i++) {
        fprintf(f, "%s\n", objects[i].name);  // Nom de l'objet sur une ligne
        fprintf(f, "%d\n", objects[i].value); // Valeur sur une ligne
        fprintf(f, "%s\n", objects[i].description); // Description sur une ligne
    }
    // Sauvegarder les portes
    fprintf(f, "%d\n", portesize);
    for (int i = 0; i < portesize; i++) {
        fprintf(f, "%s\n", portes[i].name);  // Nom de l'objet sur une ligne
        fprintf(f, "%d\n", portes[i].clef); // clef sur une ligne
        fprintf(f, "%s\n", portes[i].description); // Description sur une ligne
    }
    // Sauvegarder les PNJ
    fprintf(f, "%d\n", pnjsize);
    for (int i = 0; i < pnjsize; i++) {
        fprintf(f, "%s\n", pnj[i].name);  // Nom de l'objet sur une ligne
        fprintf(f, "%s\n", pnj[i].description); // Description sur une ligne
        fprintf(f, "%d\n", pnj[i].health); // hp sur une ligne
        fprintf(f, "%d\n", pnj[i].statue); // statue sur une ligne
    }

    // Sauvegarder les lieux
    fprintf(f, "%d\n", lieusize);
    for (int i = 0; i < lieusize; i++) {
        fprintf(f, "%s\n", locations[i].name);
        fprintf(f, "%s\n", locations[i].description);
        fprintf(f, "%d\n", locations[i].numero);
        for (int j = 0; j < 10; j++) {
            fprintf(f, "%s\n", locations[i].inventory[j].name); // Chaque objet de l'inventaire sur une ligne
        }
        for (int j = 0; j < 10; j++) {
            fprintf(f, "%s\n", locations[i].portes[j].name); // Chaque objet de l'inventaire sur une ligne
        }
        for (int j = 0; j < 10; j++) {
            fprintf(f, "%s\n", locations[i].entities[j].name); // Chaque objet de l'inventaire sur une ligne
        }
    }

    // Sauvegarder les personnages
    fprintf(f, "%d\n", persosize);
    for (int i = 0; i < persosize; i++) {
        fprintf(f, "%s\n", Characters[i].name);
        fprintf(f, "%d\n", Characters[i].health);
        fprintf(f, "%s\n", Characters[i].current_location->name);
        for (int j = 0; j < 5; j++) {
            fprintf(f, "%s\n", Characters[i].inventory[j].name); // Chaque objet de l'inventaire sur une ligne
        }
    }
    fclose(f);
    printf("Jeu sauvegardé avec succès dans %s\n", nomFichier);
}
void chargerJeu(const char *nomFichier, Object **objects, int *objsize, Location **locations, int *lieusize, C **Characters, int *persosize, Porte **portes, int *portesize, PNJ **pnj, int *pnjsize) {

    FILE *f = fopen(nomFichier, "r");
    if (!f) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    // Charger les objets
    fscanf(f, "%d\n", objsize);
    *objects = malloc(*objsize * sizeof(Object));
    for (int i = 0; i < *objsize; i++) {
        fscanf(f, "%[^\n]\n", (*objects)[i].name);  // Lire le nom de l'objet
        fscanf(f, "%d\n", &(*objects)[i].value); // Lire la valeur
        fscanf(f, "%[^\n]\n", (*objects)[i].description);  // Lire la description
    }
    // Charger les portes
    fscanf(f, "%d\n", portesize);
    *portes = malloc(*portesize * sizeof(Porte));
    for (int i = 0; i < *portesize; i++) {
        fscanf(f, "%[^\n]\n", (*portes)[i].name);  // Lire le nom de l'objet
        fscanf(f, "%d\n", &(*portes)[i].clef); // Lire la clef
        fscanf(f, "%[^\n]\n", (*portes)[i].description);  // Lire la description
    }
    // Charger les PNJ
    fscanf(f, "%d\n", pnjsize);
    *pnj = malloc(*pnjsize * sizeof(PNJ));
    for (int i = 0; i < *objsize; i++) {
        fscanf(f, "%[^\n]\n", (*pnj)[i].name);  // Lire le nom de l'objet
        fscanf(f, "%[^\n]\n", (*pnj)[i].description);  // Lire la description
        fscanf(f, "%d\n", &(*pnj)[i].health); // Lire la valeur
        fscanf(f, "%d\n", &(*pnj)[i].statue); // Lire la valeur
    }

    // Charger les lieux
    fscanf(f, "%d\n", lieusize);
    *locations = malloc(*lieusize * sizeof(Location));
    for (int i = 0; i < *lieusize; i++) {
        fscanf(f, "%[^\n]\n", (*locations)[i].name);
        fscanf(f, "%[^\n]\n", (*locations)[i].description);
        fscanf(f, "%d\n", &(*locations)[i].numero);
        for (int j = 0; j < 10; j++) {
            fscanf(f, "%[^\n]\n", (*locations)[i].inventory[j].name);  // Lire chaque objet
        }
        for (int j = 0; j < 10; j++) {
            fscanf(f, "%[^\n]\n", (*locations)[i].portes[j].name);  // Lire chaque porte
        }
        for (int j = 0; j < 10; j++) {
            fscanf(f, "%[^\n]\n", (*locations)[i].entities[j].name);  // Lire chaque pnj
        }
    }
    // Charger les personnages
    fscanf(f, "%d\n", persosize);
    *Characters = malloc(*persosize * sizeof(C));
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
        }
    }

    fclose(f);
    printf("Jeu charge avec succes depuis %s\n", nomFichier);
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
    printf("vous ete a %s\nchoisisser le numero corespondant a votre destination :\n", (*characters)[*perso-1].current_location->name);

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
        printf("Choix invalide. Annulation.\n");
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
        printf("le lieu est vide imposible de prendre un objet ");
        return;
    }
    printf("Votre choix : ");
    scanf("%d", &objet_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (objet_choice < 1 || objet_choice > nb_options) {
        printf("Choix invalide. Annulation.\n");
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
        printf("votre inventaire est vide imposible de lacher un objet ");
        return;
    }
    printf("Votre choix : ");
    scanf("%d", &objet_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (objet_choice < 1 || objet_choice > nb_options) {
        printf("Choix invalide. Annulation.\n");
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
        printf("lieu plein, impossible de lacher un objet.\n");
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
        printf("votre inventaire est vide imposible d examiner un objet ");
        return;
    }
    printf("Votre choix : ");
    scanf("%d", &objet_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (objet_choice < 1 || objet_choice > nb_options) {
        printf("Choix invalide. Annulation.\n");
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
        printf("La description de %s est : %s\n\n", (*characters)[*perso - 1].inventory[index_choisi].name, desc);
    } else {
        printf("Objet non trouvé dans la liste des objets.\n\n");
    }
}
void examiner_lieu(C **characters,int *perso) {
    printf("description du lieu : %s\n\n",(*characters)[*perso - 1].current_location->description);
}
void ouvrir(C **characters, int *perso, Location **lieu, int *lieusize , Porte **porte) {
    int porte_choice;
    int correspondances[10]; // tableau temporaire pour index réels
    int nb_options = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp((*characters)[*perso - 1].current_location->portes[i].name, "VIDE") != 0) {
            printf("%d. %s \n", nb_options + 1, (*characters)[*perso-1].current_location->portes[i]);
            correspondances[nb_options] = i;
            nb_options++;
        }
    }
    if (nb_options == 0) {
        printf("le lieu ne contient pas de porte");
        return;
    }
    printf("Votre choix : ");
    scanf("%d", &porte_choice);
    while(getchar() != '\n'); // nettoyer le buffer

    if (porte_choice < 1 || porte_choice > nb_options) {
        printf("Choix invalide. Annulation.\n");
        return;
    }
    int index_choisi = correspondances[porte_choice - 1];
    int placed = 0;
    for (int i = 0; i < 5; i++) {
        if (((*characters)[*perso - 1].current_location->portes[index_choisi].clef)==((*characters)[*perso - 1].inventory[i].value)) {
            for (int j = 0; j < *lieusize; j++) {
                if ((*lieu)[j].numero==((*characters)[*perso - 1].current_location->portes[index_choisi].clef)) {
                    (*lieu)[j].numero=((*characters)[*perso - 1].current_location->numero)+1;
                    placed = 1;
                    break;
                }
            }
        }
    }
    if (!placed) {
        printf("Votre inventaire ne contient pas la clef de cette porte.\n");
        return;
    }
    printf("La porte %s est ouverte\nvous pouver a present vous rendre dans un nouveaux lieu avec la commande aller\n", (*porte)[index_choisi].name);
}

int main(void) {
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
    int lieuSize = 0, lieuCapacity = 2;
    Location *Locations = malloc(lieuCapacity * sizeof(Location));
    int persoSize = 0, persoCapacity = 2;
    C *Characters = malloc(persoCapacity * sizeof(C));

    printf("pour passer en mode admin taper A, sinon taper play : ");
    fgets(rep, sizeof(rep), stdin);
    if (strcmp(rep, "A\n") == 0) {
        do {
            printf("A:/Entrez une action,\ntaper help pour plus d'information : ");
            fgets(action,sizeof(action), stdin);
            action[strcspn(action, "\n")] = '\0';
            if (strcmp(action, "help") == 0) {
                printf("les commandes disonible sont :\ncreer_objet : Creation d un objet\ncreer_porte : Creation d une porte\ncreer_entitee : Creation d une entitee\ncreer_lieu : creation d un lieu\ncreer_personnage : Creation d un personnage\ndeplacement : change le lieu d un personnage\naj_objet : ajoute un objet a l inventaire  d un personnage ou d un lieu\naj_porte : ajoute une porte a un lieu\naj_entitee : ajoute une entitee a un lieu\nsuppr_objet : suprime un objet de l inventaire d un personnage ou d un lieu\nsuppr_porte : suprime une porte d un lieu\nsuppr_entitee : suprime une entitee d un lieu\nplay : lance la partie en tant que joueur\nsauvegarder : sauvegarde\ncharger : charge une sauvegarde\n\n");
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
                printf("voulez vous ajouter un objet a un lieu(taper L) ou a  un personnage(taper P)");
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
                printf("voulez vous suprimer un objet d un lieu(taper L) ou d un personnage(taper P)");
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
            else if (strcmp(action, "sauvegarder") == 0) {
                printf("Entrez le nom du fichier de sauvegarde (ex: save.txt) : ");
                fgets(nomFichier, sizeof(nomFichier), stdin);
                nomFichier[strcspn(nomFichier, "\n")] = '\0';  // Supprime le \n
                sauvegarderJeu(nomFichier, objects, objSize, Locations, lieuSize, Characters, persoSize, portes, porteSize, pnj ,pnjSize);
            }
            else if (strcmp(action, "charger") == 0) {
                printf("Entrez le nom du fichier à charger : ");
                fgets(nomFichier, sizeof(nomFichier), stdin);
                nomFichier[strcspn(nomFichier, "\n")] = '\0';
                chargerJeu(nomFichier, &objects, &objSize, &Locations, &lieuSize, &Characters, &persoSize, &portes, &porteSize, &pnj ,&pnjSize);
            }
        } while (strcmp(action, "play") != 0);

    }
    if (strcmp(rep, "play\n") == 0 || strcmp(action, "play") == 0) {
        if (persoSize == 0) {
            printf("Erreur aucun personnage\n\n");
        }
        else {
            do {
                if (persoSize > 1) {
                    printf("Choisissez un personnage :\nEntrer le numero correspondant :\n");
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
                    printf("J:/Entrez une action,\ntaper help pour plus d'information : ");
                    fgets(action,sizeof(action), stdin);
                    action[strcspn(action, "\n")] = '\0';
                    if (strcmp(action, "help") == 0) {
                        printf("les commandes disonible sont :\naller\nprendre\nlacher\ninventaire\nexaminer\nsauvegarder : sauvegarde la progression\nquit : quit la partie\n\n");
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
                    else if (strcmp(action, "examiner") == 0) {
                        char exchoix[10];
                        printf("voulez vous examiner le lieu(taper L) ou a un objet de votre inventaire(taper O)");
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
                        sauvegarderJeu(nomFichier, objects, objSize, Locations, lieuSize, Characters, persoSize, portes, porteSize, pnj ,pnjSize);
                    }
                } while (strcmp(action, "quit") != 0);
            }
        }
    return 0;
}
