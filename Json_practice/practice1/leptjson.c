#include "leptjson.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
typedef struct{
    const char* json;
}lept_context;


static void lept_parse_whitespace(lept_context* context);
static int lept_parse_value(lept_context* context,lept_value* value);
//json-text = ws value ws
//
int lept_parse(lept_value* value,const char* json){
    lept_context context;
    int ret;
    assert(value!=NULL);
    context.json = json;
    // value->type = LEPT_NULL;
    lept_parse_whitespace(&context);
    ret = lept_parse_value(&context,value);
    if(ret==LEPT_PARSE_OK){
        lept_parse_whitespace(&context);
        if(*context.json != 0){
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return ret;
}
lept_type lept_get_type(const lept_value* v){
    return v->type;
}
#define EXPECT(c,ch) do{assert(*c->json==(ch));c->json++;}while(0)

static void lept_parse_whitespace(lept_context* context){
    const char* p = context->json;
    while(*p==' '||*p=='\t'||*p=='\n'||*p=='\r'){
        p++;
    }
    context->json = p;
    
}
static int lept_parse_null(lept_context* context,lept_value* value){
    EXPECT(context,'n');
    if(context->json[0]!='u'||context->json[1]!='l'||context->json[2]!='l'){
        return LEPT_PARSE_INVALID_VALUE;
    }
    context->json+=3;
    value->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}
static int lept_parse_true(lept_context* context,lept_value* value){
    EXPECT(context,'t');
    if(strncmp(context->json,"rue",3)){
        return LEPT_PARSE_INVALID_VALUE;
    }
    context->json+=3;
    value->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}
static int lept_parse_false(lept_context* context,lept_value* value){
    EXPECT(context,'f');
    if(strncmp(context->json,"alse",4)){
        return LEPT_PARSE_INVALID_VALUE;
    }
    context->json += 4;
    value->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}
static int lept_parse_literal(lept_context* context,lept_value* value,const char* str,const lept_type type){
    // EXPECT(context,str[0]);  
    assert((context->json[0])==str[0]);
    if(strncmp(context->json,str,strlen(str))){
        return LEPT_PARSE_INVALID_VALUE;
    }
    context->json+=strlen(str);
    value->type = type;
    return LEPT_PARSE_OK;
}
static int lept_parse_value(lept_context* context,lept_value* value){
    // printf("json:%s\n",context->json);
    char* str;
    lept_type type;
    switch(*context->json){
        case 'n':str = "null";type = LEPT_NULL;break;
        case 't':str = "true";type = LEPT_TRUE;break;
        case 'f':str = "false";type = LEPT_FALSE;break;         
        case '\0':return LEPT_PARSE_EXPECT_VALUE;        
        default:goto defau1t;
        defau1t:return LEPT_PARSE_INVALID_VALUE;//It's just a joke;
    }
    return lept_parse_literal(context,value,str,type);
}