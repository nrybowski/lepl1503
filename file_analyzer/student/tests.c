#include <stdlib.h>
#include <string.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

#define SIZE 700

int numberOfOutputs = 10;
struct FilesStream * HEAD;

int init();
int clean();

// Fonctions utiles pour la générations de fichiers


struct FilesStream * generateFile(char * inp_filename, char * inp_extension, int inp_size){
    // On genère un "struct FilesStream" avec:
    //  1) filename   = inp_filename
    //  2) extension  = inp_extension
    //  3) size       = inp_size

    struct FilesStream *FS = malloc(sizeof(struct FilesStream));
    if (!FS) return NULL;

    char *filename = (char*) calloc(strlen(inp_filename)+1, sizeof(char));

    if (!filename){
        free(FS);
        return NULL;
    } 

    char *extension = (char*) calloc(strlen(inp_extension)+1, sizeof(char));
    int  size = inp_size;

    if (!extension){
        free(FS);
        free(filename);
        return NULL;
    } 

    strcpy(filename, inp_filename);
    strcpy(extension, inp_extension);

    FS->filename = filename;
    FS->extension = extension;
    FS->size = size;
    FS->next = NULL;

    return FS;

}

void setNext(struct FilesStream * parent, struct FilesStream * child){
    // On définit le next du "parent" à "child"
    parent->next = child;
}

struct FilesStream * exploreXStep(struct FilesStream * StartingPosition, int steps){
    // On se déplace de "steps" steps depuis la "StartingPosition"

    struct FilesStream *explorer = StartingPosition;

    int i = 0;

    while (explorer != NULL && i < steps){
      i++;
      explorer = explorer->next;
    }

    return explorer;

}

void str_fs_help(struct FilesStream *fs, char *buffer){
    if (!fs) return;
    char *template = "%s.%s (size = %d)";
    char *comma = fs->next ? ", " : "";
    char temp[strlen(template) + 50];
    sprintf(temp, template, fs->filename, fs->extension, fs->size);
    strcat(buffer, temp);
    strcat(buffer, comma);
    str_fs_help(fs->next, buffer);
}

char *str_fs(struct FilesStream *fs){
    char *buffer = malloc(2*SIZE);
    strcpy(buffer, "[");
    str_fs_help(fs, buffer);
    strcat(buffer, "]");
    return buffer;
}

void str_out_help(struct Output *o, char *buffer, int count){
    if (count >= numberOfOutputs) return;
    if (o && o->extension){
        char *template = "\"%d .%s files of size = %d\"";
        char *comma = count < numberOfOutputs - 1 ? ", " : "";
        char temp[strlen(template) + 20];
        sprintf(temp, template, o->number, o->extension, o->totalSize);
        strcat(buffer, temp);
        strcat(buffer, comma);
        return str_out_help(o+1, buffer, count+1);
    }
    if (o && !o->extension){
        return;
    }
    strcat(buffer, "NULL");
    return str_out_help(o+1, buffer, count+1);
}

char *str_out(struct Output *o){
    char *buffer = malloc(SIZE);
    strcpy(buffer, "[");
    str_out_help(o, buffer, 0);
    strcat(buffer, "]");
    return buffer;
}

void error(struct Output *ret, struct FilesStream *fs){
    char *template = "Wrong return value. For information, your function returned %s when FS = %s";
    char *fs_str = str_fs(fs);
    char *ret_str = str_out(ret);
    char msg[strlen(template) + 3*SIZE];
    sprintf(msg, template, ret_str, fs_str);
    push_info_msg(msg);
    free(ret_str);
    free(fs_str);
    free(ret);
    clean();
}




// Tests

void test_emptyList(){

    set_test_metadata("file-analyzer", "Pas de fichier", 1);

    init();

    struct Output *results = NULL;

    SANDBOX_BEGIN;
    results = fileAnalyzer(exploreXStep(HEAD, 17));
    SANDBOX_END;

    for (size_t i = 0; i < numberOfOutputs; i++){
        struct Output *extensionFound = results + i;
        if (extensionFound == NULL) return error(results, exploreXStep(HEAD, 17));
        CU_ASSERT_EQUAL(extensionFound->extension, NULL);
        CU_ASSERT_EQUAL(extensionFound->number, 0);
        CU_ASSERT_EQUAL(extensionFound->totalSize, 0);
        if (extensionFound->extension != NULL || extensionFound->number != 0 || extensionFound->totalSize != 0) return error(results, exploreXStep(HEAD, 17));
    }

    free(results);

    clean();
}

void test_linkedlist(){

    set_test_metadata("file-analyzer", "Plusieurs fichiers liés", 1);

    init();

    struct Output *results = NULL;
    SANDBOX_BEGIN;
    results = fileAnalyzer(exploreXStep(HEAD, 13));
    SANDBOX_END;

    

    // png | 1 | 1954
    if (results == NULL) return error(results, exploreXStep(HEAD, 13));
    CU_ASSERT_EQUAL(strcmp(results->extension, "png"), 0);
    CU_ASSERT_EQUAL(results->number, 1);
    CU_ASSERT_EQUAL(results->totalSize, 1954);
    if (strcmp(results->extension, "png") != 0 || results->number != 1 || results->totalSize != 1954) return error(results, exploreXStep(HEAD, 13));

    // zip | 1 | 1530
    if (results+1 == NULL) return error(results, exploreXStep(HEAD, 13));
    CU_ASSERT_EQUAL(strcmp((results + 1)->extension, "zip"), 0);
    CU_ASSERT_EQUAL((results + 1)->number, 1);
    CU_ASSERT_EQUAL((results + 1)->totalSize, 1530);
    if (strcmp((results + 1)->extension, "zip") != 0 || (results + 1)->number != 1 || (results + 1)->totalSize != 1530) return error(results, exploreXStep(HEAD, 13));

    // mp4 | 1 | 1563015
    if (results+2 == NULL) return error(results, exploreXStep(HEAD, 13));
    CU_ASSERT_EQUAL(strcmp((results + 2)->extension, "mp4"), 0);
    CU_ASSERT_EQUAL((results + 2)->number, 1);
    CU_ASSERT_EQUAL((results + 2)->totalSize, 1563015);
    if (strcmp((results + 2)->extension, "mp4") != 0 || (results + 2)->number != 1 || (results + 2)->totalSize != 1563015) return error(results, exploreXStep(HEAD, 13));

    // c | 1 | 753
    if (results+3 == NULL) return error(results, exploreXStep(HEAD, 13));
    CU_ASSERT_EQUAL(strcmp((results + 3)->extension, "c"), 0);
    CU_ASSERT_EQUAL((results + 3)->number, 1);
    CU_ASSERT_EQUAL((results + 3)->totalSize, 753);
    if (strcmp((results + 3)->extension, "c") != 0 || (results + 3)->number != 1 || (results + 3)->totalSize != 753) return error(results, exploreXStep(HEAD, 13));

    for (size_t i = 4; i < numberOfOutputs; i++){
        struct Output *extensionFound = results + i;
        if (extensionFound == NULL) return error(results, exploreXStep(HEAD, 13));
        CU_ASSERT_EQUAL(extensionFound->extension, NULL);
        CU_ASSERT_EQUAL(extensionFound->number, 0);
        CU_ASSERT_EQUAL(extensionFound->totalSize, 0);
        if (extensionFound->extension != NULL || extensionFound->number != 0 || extensionFound->totalSize != 0) return error(results, exploreXStep(HEAD, 13));
    }

    free(results);

    clean();

}

void test_multipleFilesPerExtension(){

    set_test_metadata("file-analyzer", "Plusieurs fichiers par extension", 1);

    init();

    struct Output *results = NULL;
    SANDBOX_BEGIN;
    results = fileAnalyzer(exploreXStep(HEAD, 9));
    SANDBOX_END;

    // mp4 | 2 | 2359368
    if (results == NULL) return error(results, exploreXStep(HEAD, 9));
    CU_ASSERT_EQUAL(strcmp((results + 0)->extension, "mp4"), 0);
    CU_ASSERT_EQUAL((results + 0)->number, 2);
    CU_ASSERT_EQUAL((results + 0)->totalSize, 2359368);
    if (strcmp((results + 0)->extension, "mp4") != 0 || (results + 0)->number != 2 || (results + 0)->totalSize != 2359368) return error(results, exploreXStep(HEAD, 9));

    // png | 3 | 6036
    if (results+1 == NULL) return error(results, exploreXStep(HEAD, 9));
    CU_ASSERT_EQUAL(strcmp((results + 1)->extension, "png"), 0);
    CU_ASSERT_EQUAL((results + 1)->number, 3);
    CU_ASSERT_EQUAL((results + 1)->totalSize, 6036);
    if (strcmp((results + 1)->extension, "png") != 0 || (results + 1)->number != 3 || (results + 1)->totalSize != 6036) return error(results, exploreXStep(HEAD, 9));

    // zip | 2 | 16390
    if (results+2 == NULL) return error(results, exploreXStep(HEAD, 9));
    CU_ASSERT_EQUAL(strcmp((results + 2)->extension, "zip"), 0);
    CU_ASSERT_EQUAL((results + 2)->number, 2);
    CU_ASSERT_EQUAL((results + 2)->totalSize, 16390);
    if (strcmp((results + 2)->extension, "zip") != 0 || (results + 2)->number != 2 || (results + 2)->totalSize != 16390) return error(results, exploreXStep(HEAD, 9));

    // c | 1 | 753
    if (results+3 == NULL) return error(results, exploreXStep(HEAD, 9));
    CU_ASSERT_EQUAL(strcmp((results + 3)->extension, "c"), 0);
    CU_ASSERT_EQUAL((results + 3)->number, 1);
    CU_ASSERT_EQUAL((results + 3)->totalSize, 753);
    if (strcmp((results + 3)->extension, "c") != 0 || (results + 3)->number != 1 || (results + 3)->totalSize != 753) return error(results, exploreXStep(HEAD, 9));

    for (size_t i = 4; i < numberOfOutputs; i++){
        struct Output *extensionFound = results + i;
        if (extensionFound == NULL) return error(results, exploreXStep(HEAD, 9));
        CU_ASSERT_EQUAL(extensionFound->extension, NULL);
        CU_ASSERT_EQUAL(extensionFound->number, 0);
        CU_ASSERT_EQUAL(extensionFound->totalSize, 0);
        if (extensionFound->extension != NULL || extensionFound->number != 0 || extensionFound->totalSize != 0) return error(results, exploreXStep(HEAD, 9));
    }

    free(results);

    clean();
    
}

void test_lotOfExtensionsLotOfFiles(){

    set_test_metadata("file-analyzer", "Beaucoup de fichiers par extension", 1);

    init();

    struct Output *results = NULL;
    SANDBOX_BEGIN;
    results = fileAnalyzer(HEAD);
    SANDBOX_END;

    // png | 4 | 9596
    if (results == NULL) return error(results, HEAD);
    CU_ASSERT_EQUAL(strcmp((results + 0)->extension, "png"), 0);
    CU_ASSERT_EQUAL((results + 0)->number, 4);
    CU_ASSERT_EQUAL((results + 0)->totalSize, 9596);
    if (strcmp((results + 0)->extension, "png") != 0 || (results + 0)->number != 4 || (results + 0)->totalSize != 9596) return error(results, HEAD);

    // exe | 1 | 56
    if (results+1 == NULL) return error(results, HEAD);
    CU_ASSERT_EQUAL(strcmp((results + 1)->extension, "exe"), 0);
    CU_ASSERT_EQUAL((results + 1)->number, 1);
    CU_ASSERT_EQUAL((results + 1)->totalSize, 56);
    if (strcmp((results + 1)->extension, "exe") != 0 || (results + 1)->number != 1 || (results + 1)->totalSize != 56) return error(results, HEAD);

    // world | 1 | 15603
    if (results+2 == NULL) return error(results, HEAD);
    CU_ASSERT_EQUAL(strcmp((results + 2)->extension, "world"), 0);
    CU_ASSERT_EQUAL((results + 2)->number, 1);
    CU_ASSERT_EQUAL((results + 2)->totalSize, 15603);
    if (strcmp((results + 2)->extension, "world") != 0 || (results + 2)->number != 1 || (results + 2)->totalSize != 15603) return error(results, HEAD);

    // c | 2 | 1406
    if (results+3 == NULL) return error(results, HEAD);
    CU_ASSERT_EQUAL(strcmp((results + 3)->extension, "c"), 0);
    CU_ASSERT_EQUAL((results + 3)->number, 2);
    CU_ASSERT_EQUAL((results + 3)->totalSize, 1406);
    if (strcmp((results + 3)->extension, "c") != 0 || (results + 3)->number != 2 || (results + 3)->totalSize != 1406) return error(results, HEAD);

    // jpeg | 1 | 1630
    if (results+4 == NULL) return error(results, HEAD);
    CU_ASSERT_EQUAL(strcmp((results + 4)->extension, "jpeg"), 0);
    CU_ASSERT_EQUAL((results + 4)->number, 1);
    CU_ASSERT_EQUAL((results + 4)->totalSize, 1630);
    if (strcmp((results + 4)->extension, "jpeg") != 0 || (results + 4)->number != 1 || (results + 4)->totalSize != 1630) return error(results, HEAD);

    // mail | 1 | 896
    if (results+5 == NULL) return error(results, HEAD);
    CU_ASSERT_EQUAL(strcmp((results + 5)->extension, "mail"), 0);
    CU_ASSERT_EQUAL((results + 5)->number, 1);
    CU_ASSERT_EQUAL((results + 5)->totalSize, 896);
    if (strcmp((results + 5)->extension, "mail") != 0 || (results + 5)->number != 1 || (results + 5)->totalSize != 896) return error(results, HEAD);

    // zip | 3 | 95355
    if (results+6 == NULL) return error(results, HEAD);
    CU_ASSERT_EQUAL(strcmp((results + 6)->extension, "zip"), 0);
    CU_ASSERT_EQUAL((results + 6)->number, 3);
    CU_ASSERT_EQUAL((results + 6)->totalSize, 95355);
    if (strcmp((results + 6)->extension, "zip") != 0 || (results + 6)->number != 3 || (results + 6)->totalSize != 95355) return error(results, HEAD);

    // jpg | 1 | 4563
    if (results+7 == NULL) return error(results, HEAD);
    CU_ASSERT_EQUAL(strcmp((results + 7)->extension, "jpg"), 0);
    CU_ASSERT_EQUAL((results + 7)->number, 1);
    CU_ASSERT_EQUAL((results + 7)->totalSize, 4563);
    if (strcmp((results + 7)->extension, "jpg") != 0 || (results + 7)->number != 1 || (results + 7)->totalSize != 4563) return error(results, HEAD);

    // msi | 1 | 17862
    if (results+8 == NULL) return error(results, HEAD);
    CU_ASSERT_EQUAL(strcmp((results + 8)->extension, "msi"), 0);
    CU_ASSERT_EQUAL((results + 8)->number, 1);
    CU_ASSERT_EQUAL((results + 8)->totalSize, 17862);
    if (strcmp((results + 8)->extension, "msi") != 0 || (results + 8)->number != 1 || (results + 8)->totalSize != 17862) return error(results, HEAD);

    // mp4 | 2 | 2359368
    if (results+9 == NULL) return error(results, HEAD);
    CU_ASSERT_EQUAL(strcmp((results + 9)->extension, "mp4"), 0);
    CU_ASSERT_EQUAL((results + 9)->number, 2);
    CU_ASSERT_EQUAL((results + 9)->totalSize, 2359368);
    if (strcmp((results + 9)->extension, "mp4") != 0 || (results + 9)->number != 2 || (results + 9)->totalSize != 2359368) return error(results, HEAD);

    free(results);

    clean();
    
}


// initialisation: à utiliser si vous devez faire des mallocs ou
// des fichiers utilisés par tous les tests
int init(void) {

  // On crée les fichiers
  struct FilesStream *FS1 = generateFile("image_001", "png", 3560);
  struct FilesStream *FS2 = generateFile("Postman", "exe", 56);
  struct FilesStream *FS3 = generateFile("save", "world", 15603);
  struct FilesStream *FS4 = generateFile("programme", "c", 653);
  struct FilesStream *FS5 = generateFile("logo", "jpeg", 1630);
  struct FilesStream *FS6 = generateFile("email02", "mail", 896);
  struct FilesStream *FS7 = generateFile("projet5", "zip", 78965);
  struct FilesStream *FS8 = generateFile("image8", "jpg", 4563);
  struct FilesStream *FS9 = generateFile("installer_v6", "msi", 17862);
  struct FilesStream *FS10 = generateFile("film05", "mp4", 796353);
  struct FilesStream *FS11 = generateFile("image_002", "png", 1546);
  struct FilesStream *FS12 = generateFile("projet2", "zip", 14860);
  struct FilesStream *FS13 = generateFile("image_003", "png", 2536);

  struct FilesStream *FS14 = generateFile("image_004", "png", 1954);
  struct FilesStream *FS15 = generateFile("exo8", "zip", 1530);
  struct FilesStream *FS16 = generateFile("starwars3", "mp4", 1563015);
  struct FilesStream *FS17 = generateFile("main", "c", 753);

  if (
    FS1==NULL || FS2==NULL || FS3==NULL ||
    FS4==NULL || FS5==NULL || FS6==NULL ||
    FS7==NULL || FS8==NULL || FS9==NULL ||
    FS10==NULL || FS11==NULL || FS12==NULL ||
    FS13==NULL || FS14==NULL || FS15==NULL ||
    FS16==NULL || FS17==NULL
  ) {
    return -1;
  }

  // On link les fichiers ensemble
  setNext(FS16, FS17);
  setNext(FS15, FS16);
  setNext(FS14, FS15);
  setNext(FS13, FS14);
  setNext(FS12, FS13);
  setNext(FS11, FS12);
  setNext(FS10, FS11);
  setNext(FS9, FS10);
  setNext(FS8, FS9);
  setNext(FS7, FS8);
  setNext(FS6, FS7);
  setNext(FS5, FS6);
  setNext(FS4, FS5);
  setNext(FS3, FS4);
  setNext(FS2, FS3);
  setNext(FS1, FS2);

  // On définit la HEAD globale a FS1
  HEAD = FS1;

  return 0; // réussite, -1 pour échec
}
// initialisation: à utiliser si vous devez libérer des ressources
// créées par init
int clean(void) {
  struct FilesStream *explorer = HEAD;
  struct FilesStream *save = NULL;

  while (explorer != NULL){

    save = explorer->next;
    free(explorer->filename);
    free(explorer->extension);
    free(explorer);
    explorer = save;

  }

  return 0; // réussite, -1 pour échec
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test_emptyList, test_linkedlist, test_multipleFilesPerExtension, test_lotOfExtensionsLotOfFiles);
}
