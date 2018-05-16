//chinese codec : GBK

#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include <string.h>
#include <strings.h>
char int2hex(int n);
int getCurcwd(char* src_buf,int src_size,char* dest_buf,int dest_size);
 
int main(){
    
    char buf[128] = {0};
    char str[40] = {0};
    char tmp[128] = {0};
    char ch;
    size_t count;
    int ret ;
    char* ptr = _getcwd(buf,sizeof(buf));//��ȡ��ǰ·��
    FILE* fp_src,*fp_dest;
    
    if(ptr!=buf){
        printf("_getcwd failed!\n");
        exit(1);
    }
    ret = getCurcwd(buf,sizeof(buf),str,sizeof(str));//��ȡ��ǰ���ļ��й�����
    if(ret){
        printf("getCurcwd failed");
        exit(1);
    }
    // system("del sprd_macro.txt");
    // printf("buf:%s\n",buf);
    // ret = strstr(buf,"\\lib\\");//��ȡMS_code·�� ret��MS_code��ʼ ret = \lib\...
    // printf("strstr:%s\n",ret);
    sprintf(ptr,"\\build\\%s_builddir\\tmp\\sprd_macro.tmp",str);//���̶�Ӧ��buildĿ¼,ǿ�ƴ�retλ�ÿ�ʼ�޸�·��
    // printf("buf:%s\n",buf); 
    
    fp_src = fopen(buf,"r");
    fp_dest = fopen("sprd_macro.txt","w");
    if(fp_src==NULL||fp_dest==NULL){
        if(fp_src!=NULL){
            fclose(fp_src);
        }
        if(fp_dest!=NULL){
            fclose(fp_dest);
        }
        exit(1);
    }
    
    while(count = fread(&ch,1,1,fp_src)){
        fwrite(&ch,1,1,fp_dest);
    }
    fclose(fp_src);
    fclose(fp_dest);

    return 0;
}

int getCurcwd(char* src_buf,int src_size,char* dest_buf,int dest_size){
    int ret,i,flag,tmp;
    
    if(src_buf==NULL||src_size==0||dest_buf==NULL||dest_size==0){
        return -1;
    }
    for(i=0;src_buf[i];i++){
        if(src_buf[i]=='\\'){
            flag = i;
        }
    }
    ++flag;
    
    
    tmp = i - flag;
    if(i>src_size||tmp>dest_size){
        return -1;
    }
    for(i=0;i<tmp;i++){
        dest_buf[i] = src_buf[i+flag];
    }
    return 0;
}


char int2hex(int n){
    char a[]="0123456789ABCDEF";
    printf("addr:%p \t\n",&a[n]);
    return a[n];
}