#include<stdlib.h>
#include"admin.h"
#include<math.h>

const int account_len=3;//工号长度 ps:如果数字长度超过len会自动加长
int worker_number=1;
bool worker_number_flag[101]={0};
void worker_account_init(){
    worker* cur=worker_list->next;
    int tmp=0,account;
    while(cur!=NULL){
        account=atoi(cur->zhanghao);
        if(account>pow(10,account_len-1)){
            if(account>tmp){
                tmp=account;
            }
        }
        else{
            worker_number_flag[account]=1;
        }
        cur=cur->next;
    }
    worker_number=tmp+1;
    return;
}

char* worker_account_creat(int len,int number){
    char* number_char=(char*)malloc(sizeof(char)*10);
    sprintf(number_char,"%d",number);
    int numberlen=strlen(number_char);
    if(len-numberlen<0){
        return strdup(number_char);
    }
    else{
        char* account=(char*)malloc(sizeof(char)*(len+1));
        memset(account,'0',len-strlen(number_char));
        account[len-strlen(number_char)]='\0';
        strcat(account,number_char);
        return account;
    }
}
//worker operations
bool exsit_worker(char* account){
    bool flag=0;
    worker* cur=worker_list->next;
    if(*account=='\0'){
        return 0;
    }
    while(cur!=NULL){
        if(strcmp(cur->zhanghao,account)==0){
            flag=1;
            break;
        }
        cur=cur->next;
    }
    return flag;
}

void view_all_worker(){
    worker* cur=worker_list->next;
    if(cur==NULL){
        printf("no worker\n");
        return;
    }
    while(cur!=NULL){
        printf("name:%s\n",cur->name);
        printf("account:%s\n",cur->zhanghao);
        printf("password:%s\n",cur->mima);
        cur=cur->next;
    }
    return;
}

void find_worker(char* account){
    worker* cur=worker_list;
    while(cur!=NULL){
        if(strcmp(cur->zhanghao,account)==0){
            printf("name:%s\n",cur->name);
            printf("account:%s\n",cur->zhanghao);
            printf("password:%s\n",cur->mima);
            return;
        }
        cur=cur->next;
    }
    printf("no such worker\n");
    return;
    
}

void add_worker(char* name,char* password){
    worker* cur=worker_list->next;
    worker* new_worker = (worker*)malloc(sizeof(worker));
    new_worker->name = strdup(name);
    new_worker->zhanghao = worker_account_creat(account_len,worker_number);
    new_worker->mima = strdup(password);
    new_worker->next = NULL;
    printf("worker added. account:%s\n",new_worker->zhanghao);
    worker_number++;
    if(worker_list->next==NULL){
        worker_list->next = new_worker;
        return;
    }
    else{
        while(cur->next!=NULL){
            cur=cur->next;
        }
        cur->next = new_worker;
    }
    return;
}

void delete_worker(char* account){
    worker* cur=worker_list->next;
    int flag=0;
    if(cur==NULL||exsit_worker(account)==0){
        printf("no such worker\n");
        return;
    }
    else{
        worker* pre=worker_list;
        while(cur!=NULL){
            if(strcmp(cur->zhanghao,account)==0){
                if(cur->next==NULL){
                    pre->next=NULL;
                    free(cur);
                    flag=1;
                    break;
                }
                else{
                    pre->next = cur->next;
                    free(cur);
                    flag=1;
                    break;
                }
            }
            cur=cur->next;
            pre=pre->next;
        }
    }
    return;
}

//user operations

bool exsit_user(char* id){
    bool flag=0;
    user* cur=user_list->next;
    if(*id=='\0'){
        return 0;
    }
    while(cur!=NULL){
        char id_str[20];
        sprintf(id_str, "%d", cur->id);
        if(strcmp(id_str, id)==0){
            flag=1;
            break;
        }
        cur=cur->next;
    }
    return flag;
}

void find_user(char* id){
    user* cur=user_list->next;
    if(cur==NULL||exsit_user(id)==0){
        printf("no such user\n");
        return;
    }
    while(cur!=NULL){
        char id_str[20];
        sprintf(id_str, "%d", cur->id);
        if(strcmp(id_str, id)==0){
            printf("name:%s\n",cur->name);
            printf("id:%s\n",cur->id);
            printf("tel:%s\n",cur->tel);
            break;
        }
        cur=cur->next;
    }
}

void view_all_user(){
    user* cur=user_list->next;
    if(cur==NULL){
        printf("no user\n");
        return;
    }
    while(cur!=NULL){
        printf("name:%s\n",cur->name);
        printf("id:%s\n",cur->id);
        printf("tel:%s\n",cur->tel);
        cur=cur->next;
    }
    return;
}

//packege_in operations

//daishou_package operations
bool exsit_daishou_package(char* code){
    bool flag=0;
    package_in* cur=daishou_package->next;
    while(cur!=NULL){
        if(strcmp(cur->code,code)==0){
            flag=1;
            break;
        }
        cur=cur->next;
    }
    return flag;
}

void find_daishou_package(){
    package_in* cur=daishou_package->next;
    while(cur!=NULL){
        printf("name:%s\n",cur->name);
        printf("tel:%s\n",cur->tel);
        printf("code:%s\n",cur->code);
        printf("out_address:%s\n",cur->out_address);
        printf("in_address:%s\n",cur->in_address);
        printf("state:%d\n",cur->state);
        printf("id:%s\n",cur->id);
        printf("company:%s\n",cur->company);
        printf("time:%ld\n",cur->time);
        cur=cur->next;
    }
    return;
}

void view_all_daishou_package(){
    package_in* cur=daishou_package->next;
    if(cur==NULL){
        printf("no daishou_package\n");
        return;
    }
    while(cur!=NULL){
        printf("name:%s\n",cur->name);
        printf("tel:%s\n",cur->tel);
        printf("code:%s\n",cur->code);
        printf("out_address:%s\n",cur->out_address);
        printf("in_address:%s\n",cur->in_address);
        printf("state:%d\n",cur->state);
        printf("id:%s\n",cur->id);
        printf("company:%s\n",cur->company);
        printf("time:%ld\n",cur->time);
        cur=cur->next;
    }
    return;
}

//nuw_package operations
bool exsit_nuw_package(char* code){
    bool flag=0;
    package_in* cur=nuw_package->next;
    while(cur!=NULL){
        if(strcmp(cur->code,code)==0){
            flag=1;
            break;
        }
        cur=cur->next;
    }
    return flag;
}

void find_nuw_package(){
    package_in* cur=nuw_package->next;
    while(cur!=NULL){
        printf("name:%s\n",cur->name);
        printf("tel:%s\n",cur->tel);
        printf("code:%s\n",cur->code);
        printf("out_address:%s\n",cur->out_address);
        printf("in_address:%s\n",cur->in_address);
        printf("state:%d\n",cur->state);
        printf("id:%s\n",cur->id);
        printf("company:%s\n",cur->company);
        printf("time:%ld\n",cur->time);
        cur=cur->next;
    }
    return;
}

void view_all_nuw_package(){
    package_in* cur=nuw_package->next;
    if(cur==NULL){
        printf("no nuw_package\n");
        return;
    }
    while(cur!=NULL){
        printf("name:%s\n",cur->name);
        printf("tel:%s\n",cur->tel);
        printf("code:%s\n",cur->code);
        printf("out_address:%s\n",cur->out_address);
        printf("in_address:%s\n",cur->in_address);
        printf("state:%d\n",cur->state);
        printf("id:%s\n",cur->id);
        printf("company:%s\n",cur->company);
        printf("time:%ld\n",cur->time);
        cur=cur->next;
    }
    return;
}

//rukou_package operations
bool exsit_ruku_package(char* code){
    bool flag=0;
    package_in* cur=ruku_package->next;
    while(cur!=NULL){
        if(strcmp(cur->code,code)==0){
            flag=1;
            break;
        }
        cur=cur->next;
    }
    return flag;
}

void find_ruku_package(char* code){
    package_in* cur=ruku_package->next;
    while(cur!=NULL){
        if(strcmp(cur->code,code)==0){
            printf("name:%s\n",cur->name);
            printf("tel:%s\n",cur->tel);
            printf("code:%s\n",cur->code);
            printf("out_address:%s\n",cur->out_address);
            printf("in_address:%s\n",cur->in_address);
            printf("state:%d\n",cur->state);
            printf("id:%s\n",cur->id);
            printf("company:%s\n",cur->company);
            printf("time:%ld\n",cur->time);
            break;
        }
        cur=cur->next;
    }
    return;
}

void view_all_ruku_package(){
    package_in* cur=ruku_package->next;
    if(cur==NULL){
        printf("no ruku_package\n");
        return;
    }
    while(cur!=NULL){
        printf("name:%s\n",cur->name);
        printf("tel:%s\n",cur->tel);
        printf("code:%s\n",cur->code);
        printf("out_address:%s\n",cur->out_address);
        printf("in_address:%s\n",cur->in_address);
        printf("state:%d\n",cur->state);
        printf("id:%s\n",cur->id);
        printf("company:%s\n",cur->company);
        printf("time:%ld\n",cur->time);
        cur=cur->next;
    }
    return;
}
