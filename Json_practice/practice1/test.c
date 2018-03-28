#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leptjson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality,expect,actual,format) \
do{\
    test_count++;\
    if(equality){\
        test_pass++;\
    }else{\
        fprintf(stderr,"%s:%d: expect: "format"actual:"format"\n",\
        __FILE__,__LINE__,expect,actual);\
        main_ret = 1;\
    }\
}while(0)
#define TEST_ERROR(error,json)\
do{\
    lept_value value;\
    value.type = LEPT_FALSE;\
    EXPECT_EQ_INT(error,lept_parse(&value,json));\
    EXPECT_EQ_INT(LEPT_NULL,lept_get_type(&value));\
}while(0)



#define EXPECT_EQ_INT(expect,actual) EXPECT_EQ_BASE((expect)==(actual),expect,actual,"%d")
static void test_parse_null(){
    lept_value value;
    value.type = LEPT_TRUE;
    EXPECT_EQ_INT(LEPT_PARSE_OK,lept_parse(&value,"null"));
    EXPECT_EQ_INT(LEPT_NULL,lept_get_type(&value));
}
static void test_parse_true(){
    lept_value value;
    value.type = LEPT_TRUE;
    EXPECT_EQ_INT(LEPT_PARSE_OK,lept_parse(&value,"true"));
    EXPECT_EQ_INT(LEPT_TRUE,lept_get_type(&value));
}
static void test_parse_false(){
    lept_value value;
    value.type = LEPT_FALSE;
    EXPECT_EQ_INT(LEPT_PARSE_OK,lept_parse(&value,"false"));
    EXPECT_EQ_INT(LEPT_FALSE,lept_get_type(&value));
}
static void test_parse(){
    test_parse_null();
    test_parse_true();
    test_parse_false();
    // test_parse_();
    // test_parse_true();
}
static void test_parse_expect_value(){
    TEST_ERROR(LEPT_PARSE_EXPECT_VALUE,"");
    TEST_ERROR(LEPT_PARSE_EXPECT_VALUE," ");
}
int main(int argc,char** argv){
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n",test_pass,test_count,test_pass*100.0/test_count);

    return 0;
}