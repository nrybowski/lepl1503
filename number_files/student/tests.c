#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

void error(int nb, int exp){
    char *template = "Your code doesn't work correctly. The expected result was %d, but you returned %d";
    char msg[strlen(template)];
    sprintf(msg, template, exp, nb);
    push_info_msg(msg);
}

void test1(){

    set_test_metadata("number_files", "Test pour le répertoire Documents", 1);

    // test de base minimaliste
    file_t a;
    a.folder = false;
    file_t b;
    b.folder = false;
    file_t c;
    c.folder = false;


    file_t Documents;
    Documents.folder = true;
    Documents.n_files = 3;
    Documents.files = (file_t*[]) {&a, &b, &c};

    int res;
    SANDBOX_BEGIN;
    res = get_number_of_files(&Documents);
    SANDBOX_END;

    CU_ASSERT_EQUAL(3,res);
    if (res != 3) error(res, 3);
}
    
void test2(){

    set_test_metadata("number_files", "Test pour le répertoire Downloads", 1);

    file_t d;
    d.folder = false;

    file_t y;
    y.folder = true;
    y.n_files = 0;
    y.files = NULL;

    file_t Downloads;
    Downloads.folder = true;
    Downloads.n_files = 2;
    Downloads.files = (file_t *[]) {&d, &y} ;

    int res;
    SANDBOX_BEGIN;
    res = get_number_of_files(&Downloads);
    SANDBOX_END;
    CU_ASSERT_EQUAL(1,res);
    if (res != 1) error(res, 1);
}

void test3(){

    set_test_metadata("number_files", "Test pour le répertoire y", 1);

    // test de base minimaliste
    file_t y;
    y.folder = true;
    y.n_files = 0;
    y.files = NULL;

    int res;
    SANDBOX_BEGIN;
    res = get_number_of_files(&y);
    SANDBOX_END;
    CU_ASSERT_EQUAL(0,res);
    if (res != 0) error(res, 0);
}

void test4(){

    set_test_metadata("number_files", "Test pour le répertoire Home", 1);
 
    file_t a;
    a.folder = false;
    file_t b;
    b.folder = false;
    file_t c;
    c.folder = false;


    file_t Documents;
    Documents.folder = true;
    Documents.n_files = 3;
    Documents.files = (file_t *[]) {&a, &b, &c};

    file_t d;
    d.folder = false;

    file_t y;
    y.folder = true;
    y.n_files = 0;
    y.files = NULL;

    file_t Downloads;
    Downloads.folder = true;
    Downloads.n_files = 2;
    Downloads.files = (file_t*[]) {&d, &y};

    file_t Home;
    Home.folder = true;
    Home.n_files = 2;
    Home.files = (file_t*[]) {&Documents, &Downloads};



    int res;
    SANDBOX_BEGIN;
    res = get_number_of_files(&Home);
    SANDBOX_END;
    CU_ASSERT_EQUAL(4,res);
    if (res != 4) error(res, 4);
    
}

void test5(){

    set_test_metadata("number_files", "Test pour un argument file == NULL", 1);

    file_t * file;
    file = NULL;
    int n_files;
    SANDBOX_BEGIN;
    n_files = get_number_of_files(file);
    SANDBOX_END;
    CU_ASSERT_EQUAL(n_files,-1);
    if (n_files != -1) push_info_msg("You should return -1 when file == NULL");
    
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5);
}
