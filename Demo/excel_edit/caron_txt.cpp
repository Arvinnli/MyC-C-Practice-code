#include <stdio.h>
// #include <String>
#include <iostream>
#include <string.h>

#ifdef __DEBUG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...) 
#endif





int flag = 0;
struct Csv{
    char spc_id[20];
    char bzid[20];
    char bzurl[128];
    char state[20];
    char headline[796];
    char owner[20];
    char contacter[20];
};
int get_txt(const char* s){
	int ret;
	
	for(int i=0;s[i];i++){
		if(s[i]=='.'){
			if(!strncmp(&s[i+1],"txt",3)){
				return i+1;
			}
		}
	}
	return -1;
}
int Csv_get(const char* s,char* d){
    int i,j;
    if(s==NULL||d==NULL||s[0]==0){
        return -1;
    }
    for(i=0;s[i]=='|';i++);
        LOG("%d\n",__LINE__);
    for(j=0;(s[i+j]!='|')&&(s[i+j]!=0);j++){
        LOG("%d\n",__LINE__);
        d[j]=s[i+j];
        LOG("%d\n",__LINE__);

        if(flag){
            putchar(d[j]);
        }
    }
    d[j] = 0;
    return i+j;
}
int main(int argc,char** argv){

    Csv tmp;
    char buf[128]={0};
    char r_buf[1024];
    // char w_buf[1024];
    if(argc<2){
        std::cout << "missing parameters." << std::endl;
        return 0;
    }
    int a=3,b=2,c=1;
    a=1+(b=c=4);
    
    FILE* fp = fopen(argv[1],"r");
    sprintf(buf,"_n%s",argv[1]);
        
	int n = get_txt(buf);
	buf[n++] = 'c';
	buf[n++] = 's';
	buf[n++] = 'v';
    FILE* fp_n = fopen(buf,"w");
    fgets(r_buf,1023,fp);
    for(int i=0;r_buf[i];i++){
        if(r_buf[i]=='|'){
            r_buf[i] = ',';
        }
    }
    fputs(r_buf,fp_n);
    // printf("%s",r_buf);
    while(!feof(fp)){
        int i,j,k;

        memset(r_buf,0,sizeof(buf));
        memset(&tmp,0,sizeof(buf));
        // memset(w_buf,0,sizeof(buf));
        fgets((char*)&r_buf,1023,fp);
        


        LOG("%d\n",__LINE__);
        int n = Csv_get(r_buf,tmp.spc_id);
        LOG("%d\n",__LINE__);
        if(n==-1){
            goto __END;
        }
        // printf("%s\n",tmp.spc_id);


        n += Csv_get((char*)&r_buf[n],tmp.bzid);
        // printf("%s\n",tmp.bzid);
        
        // flag = 1;
        n += Csv_get((char*)&r_buf[n],tmp.state);
        // printf("%s\n",tmp.state);
        // std::cout << std::endl;
        flag = 0;

        n += Csv_get((char*)&r_buf[n],tmp.headline);
        // printf("%s\n",tmp.headline);
        
        n += Csv_get((char*)&r_buf[n],tmp.owner);
        // printf("%s\n",tmp.owner);
        
        n += Csv_get((char*)&r_buf[n],tmp.contacter);
        // printf("%s\n",tmp.contacter);
        
        sprintf(tmp.bzurl,"=HYPERLINK(\"\"http://bugzilla.unisoc.com/bugzilla/show_bug.cgi?id=%s\"\",\"\"%s\"\")",tmp.bzid,tmp.bzid);
        for(int i=0;tmp.contacter[i];i++){
            if(tmp.contacter[i]=='?'||tmp.contacter[i]=='\n'){
                tmp.contacter[i]=0;
            }
        }
        
        fprintf(fp_n,"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"",tmp.spc_id,tmp.bzurl,tmp.state,tmp.headline,tmp.owner,tmp.contacter);
        fprintf(fp_n,"\n");
        // printf("%s%s%s%s%s",tmp.spc_id,tmp.bzid,tmp.headline,tmp.owner,tmp.contacter);

        // for(j=0;r_buf[i+j]!=',';j++){
        //     tmp.bzid[j] = r_buf[i+j];
        // }
        // for(k=0;r_buf[i+j+k];k++){
        //     tmp.rest[k] = r_buf[i+j+k];
        // }
                            
        // fprintf(fp_n,"%s,%s%s",tmp.spc_id,tmp.bzurl,tmp.rest);
        //std::cout << __LINE__ << std::endl;

    }
__END:
    fclose(fp_n);
    fclose(fp);

    return 0;
}