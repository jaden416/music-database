#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define SIZE 30

// structs
typedef struct {

  int id;
  char title[30];
  char artist[30];
  int date;
  double rating;

} albums_t;

struct database {
  int choice;
  albums_t album[30]; // this database will store the struct array within it
};

// functions
int databaseProgram(struct database database);
void displayOptions();
void displayAlbums(struct database database);
void addAlbum(struct database *
                  database); // passing by reference so it wont make a mere copy
// of the database and change absolutely nothing
void deleteAlbum(struct database *database);
void searchAlbum(struct database database);
void printAlbums(struct database *database);
int main(void) {

  struct database database;
  // filling the database with empty values that will be altered later
  for (int i = 0; i < SIZE; ++i) {
    database.album[i].id = -1;
    strncpy(database.album[i].title, "-1", 30);
    strncpy(database.album[i].artist, "-1", 20);
    database.album[i].date = -1;
    database.album[i].rating = -1;
  }

  int dataB = databaseProgram(database);

  return 0;
}

int databaseProgram(struct database database) {

  printf("Welcome to the Album Database!\n\n");
  // hardcoding the first six albums in the database
  for (int i = 0; i < 1; ++i) {
    database.album[i].id = i;
    printf("Insert album title: ");
    fgets(database.album[i].title, sizeof(database.album[i].title), stdin);

    printf("Insert album artist: ");
    fgets(database.album[i].artist, sizeof(database.album[i].artist), stdin);
    
      printf("Insert album date: ");
    while(scanf("%d", &database.album[i].date) != 1){
      printf("Invalid input. Try again.\n");
      printf("Insert album date: ");
      scanf("%d", &database.album[i].date);
      fgetc(stdin); //prevents the loop by clearing the input stream
    }

    printf("Insert album rating: ");
    while(scanf("%lf", &database.album[i].rating) != 1){
      printf("Invalid input. Try again.\n");
      printf("Insert album rating: ");
      scanf("%lf", &database.album[i].rating);
      fgetc(stdin);
    }
  }

  // initiating program

  while (database.choice != 5) {
    printf("------------------------\n");
    displayOptions();
    scanf("%d", &database.choice);
    switch (database.choice) {
    case 1:
      addAlbum(&database);
      break;
    case 2:
      deleteAlbum(&database);
      break;
    case 3:
      searchAlbum(database);
      break;
    case 4:
      displayAlbums(database);
      break;
    case 5:
      database.choice = 5;
      printf("Exited program. Here is your album spreadsheet!\n");
      // printing records on records.txt
      printAlbums(&database);
      break;

    default:
      printf("Invalid option. Try again.\n");
      break;
    }
  }

  
  return 1;
}

void displayOptions() {
  printf("Here are your options.\n");
  printf("1. Add a new album.\n");
  printf("2. Delete an album.\n");
  printf("3. Search an album.\n");
  printf("4. Display all your albums.\n");
  printf("5. Exit.\n");
  printf("Enter option: ");
}

void displayAlbums(struct database database) {
  int i = 0;
  while (database.album[i].id != -1) {
    printf("------------------------\n");
    printf("Album title:        %s", database.album[i].title);
    printf("Album artist:       %s", database.album[i].artist);
    printf("Album date:         %d\n", database.album[i].date);
    printf("Album rating:       %.2lf\n", database.album[i].rating);
    i++;
  }
}

void addAlbum(struct database *database) {
  for (int i = 0; i < SIZE; ++i) {
    if (database->album[i].id == -1) {

      database->album[i].id = i; // making the id value valid

      printf("Insert album title: ");
      fgetc(stdin);
      fgets(database->album[i].title, sizeof(database->album[i].title), stdin);

      printf("Insert album artist: ");
      fgets(database->album[i].artist, sizeof(database->album[i].artist),
            stdin);

      printf("Insert album date: ");
      scanf("%d", &database->album[i].date);

      printf("Insert album rating: ");
      scanf("%lf", &database->album[i].rating);
      break; // only iterates once
    }
  }
}

void deleteAlbum(struct database *database) {
  char deleteThis[30];

  printf("What album do you want to delete?\nEnter the album title: ");
  fgetc(stdin);
  fgets(deleteThis, sizeof(deleteThis), stdin);

  for (int i = 0; i < SIZE; ++i) {
    if (strcmp(database->album[i].title, deleteThis) == 0) {
      database->album[i].id = -1;
      strncpy(database->album[i].title, "-1", 30);
      strncpy(database->album[i].artist, "-1", 20);
      database->album[i].date = -1;
      database->album[i].rating = -1;
    }
  }

  // moving the deleted values to the back of the array
  int tempId;
  char tempTitle[30];
  char tempArtist[30];
  int tempDate;
  float tempRating;
  for (int i = 0; i < SIZE; ++i) {

    if (database->album[i].id == -1) {
      // storing the data attributes
      tempId = database->album[i].id;
      strncpy(tempTitle, database->album[i].title, 30);
      strncpy(tempArtist, database->album[i].artist, 30);
      tempDate = database->album[i].date;
      tempRating = database->album[i].rating;

      // replacing the deleted data attributes with next data attributes
      database->album[i].id = database->album[i + 1].id;
      strncpy(database->album[i].title, database->album[i + 1].title, 30);
      strncpy(database->album[i].artist, database->album[i + 1].artist, 30);
      database->album[i].date = database->album[i + 1].date;
      database->album[i].rating = database->album[i + 1].rating;

      database->album[i + 1].id = tempId;
      strncpy(tempTitle, database->album[i + 1].title, 30);
      strncpy(tempArtist, database->album[i + 1].artist, 30);
      database->album[i + 1].date = tempDate;
      database->album[i + 1].rating = tempRating;
    }
  }
}
void searchAlbum(struct database database) {
  char searchThis[30];

  printf("What album do you want to search?\nEnter the album title: ");
  fgetc(stdin);
  fgets(searchThis, sizeof(searchThis), stdin);

  
  for (int i = 0; i < SIZE; ++i) {
    if (strcmp(database.album[i].title, searchThis) == 0) {
      printf("Album is in the database!\n");
      printf("------------------------\n");
      printf("Album title:        %s", database.album[i].title);
      printf("Album artist:       %s", database.album[i].artist);
      printf("Album date:         %d\n", database.album[i].date);
      printf("Album rating:       %.2lf\n", database.album[i].rating);
      
      if (strcmp(database.album[i].title, searchThis) == 0)
      break; //stops the loop after finding the  album
    }
        if ( i >= SIZE-1 && strcmp(database.album[i].title, searchThis) != 0)//if the loop has finished and the last album in the list is not in the search then..
      printf("Album not found!\n");
  }


}

void printAlbums(struct database *database) {
  FILE *ptr;
  ptr = fopen("Records.txt", "w");
  int i = 0;
  fprintf(ptr, "Album Database Records\n");
  while (database->album[i].id != -1) {
    fprintf(ptr, "------------------------\n");
    fprintf(ptr, "Album title:        %s", database->album[i].title);
    fprintf(ptr, "Album artist:       %s", database->album[i].artist);
    fprintf(ptr, "Album date:         %d\n", database->album[i].date);
    fprintf(ptr, "Album rating:       %.2lf\n", database->album[i].rating);
    i++;
  }

  fclose(ptr);
}