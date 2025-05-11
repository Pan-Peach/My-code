//logic.c
#include"item.h"
#include"user_fun.h"
#include"login.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>


int get_line_number(char * filename){
    int n=0;
    FILE *f;
    f = fopen(filename,"r");
    char a;
    while((a = fgetc(f))!=EOF){
        if (a=='\n'){n++;}
    }
    fclose(f);
    return n;
}

void show_options(){
    system("clear");
    printf("*********************************\n");
    printf("*         驿站管理系统          *\n");
    printf("*1.我是用户                     *\n");
    printf("*2.我是员工                     *\n");
    printf("*3.我是管理员                   *\n");
    printf("*0.退出系统                     *\n");
    printf("*********************************\n");
}

void show_login_user(){
    system("clear");
    printf("*********************************\n");
    printf("*             用户登录          *\n");
    printf("*1.登录                         *\n");
    printf("*2.注册                         *\n");
    printf("*********************************\n");
}

void show_login_worker(){
    system("clear");
    printf("*********************************\n");
    printf("*             员工登录           *\n");
    printf("*********************************\n");
    printf("输入q退出\n");
}

void show_login_admin(){
    system("clear");
    printf("*********************************\n");
    printf("*             管理员             *\n");
    printf("*********************************\n");
    printf("输入q退出\n");
}

user * bulid_user(){
    int line_number=0;
    line_number = get_line_number("user_data.txt");
    FILE *file;
    user *head,*tmp,*p,*returan_list;
    head = tmp = p = NULL;
    returan_list = (user*)malloc(sizeof(user));
    returan_list->next = NULL;

    file = fopen("user_data.txt","r");
    if (file){
        while(line_number){
            tmp = (user*)malloc(sizeof(user));
            tmp->name = (char*)malloc(sizeof(char));
            tmp->zhanghao = (char*)malloc(sizeof(char));
            tmp->mima = (char*)malloc(sizeof(char));
            tmp->tel = (char*)malloc(sizeof(char));
            fscanf(file,"%s%s%s%d%d%d%s",tmp->name,tmp->zhanghao,tmp->mima
                ,&tmp->id,&tmp->num_ji,&tmp->num_qu,tmp->tel);
	        tmp->next = NULL;
            p = head;
            if (head){
                while(p->next){
                    p = p->next;
                }
                p->next = tmp;
            }
            else{
                head = tmp;
                p = head;
            }
            line_number--;
        }        
    }
    fclose(file);
    returan_list->next = head;
    return returan_list;
}

worker * bulid_worker(){
    int line_number=0;
    line_number = get_line_number("worker_data.txt");
    FILE *file;
    worker *head,*tmp,*p,*return_list;
    head = tmp = p =NULL;
    return_list->next = NULL;

    file = fopen("worker_data.txt","r");
    if (file){
        while(line_number){
            tmp = (worker*)malloc(sizeof(worker));
            tmp->name = (char*)malloc(sizeof(char));
            tmp->zhanghao = (char*)malloc(sizeof(char));
            tmp->mima = (char*)malloc(sizeof(char));
            fscanf(file,"%s%s%s",
            tmp->name,tmp->zhanghao,tmp->mima);
            tmp->next = NULL;
            p = head;
            if (head){
                while(p->next){
                    p = p->next;
                }
                p->next = tmp;
            }
            else{
                head = tmp;
                p = head;
            }
            line_number--;
        }        
    }
    fclose(file);
    return_list->next = head;
    return return_list;
}

admin * bulid_admin(){
    admin* tmp = (admin*)malloc(sizeof(admin));
    tmp->zhanghao = "admin";
    tmp->mima = "password";
    return tmp;
}

package_in * bulid_package_in(){
    int line_number=0,index=0,i=0;
    char * code_;
    code_ = (char*)malloc(sizeof(code));
    line_number = get_line_number("package_in_data.txt");
    FILE *file;
    package_in *head,*tmp,*p,*returan_list;
    head = tmp = p = NULL;
    returan_list = (package_in*)malloc(sizeof(package_in));
    returan_list->next = NULL;

    file = fopen("package_in_data.txt","r");
    if (file){
        while(line_number){
            tmp = (package_in*)malloc(sizeof(package_in));
            tmp->name = (char*)malloc(sizeof(char));
            tmp->tel = (char*)malloc(sizeof(char));
            tmp->code = (char*)malloc(sizeof(char));
            tmp->id  = (char*)malloc(sizeof(char));
            tmp->company = (char*)malloc(sizeof(char));
            tmp->next = NULL;
            fscanf(file,"%f%f%s%s%s%d%d%d%s%s%ld",&tmp->weight,&tmp->volume
                    ,tmp->name,tmp->tel,tmp->code,&tmp->out_address,&tmp->in_address
                    ,&tmp->state,tmp->id,tmp->company,&tmp->time);
            strcpy(code_,tmp->code);
            for(i=0;i<strlen(code_)-1;i++){code_[i]=code_[i+1];}
            code_[strlen(code_)-1]='\0';
            index = atoi(code_);
            code[tmp->code[0]-65][index]=1;
            p = head;
            if (head){
                while(p->next){
                    p = p->next;
                }
                p->next = tmp;
            }
            else{
                head = tmp;
                p = head;
            }
            line_number--;
        }        
    }
    fclose(file);
    returan_list->next = head;
    return returan_list;
}

package_in * build_package_daishou(){
    int line_number=0;
    line_number = get_line_number("package_daishou_data.txt");
    FILE *file;
    package_in *head,*tmp,*p,*returan_list;
    head = tmp = p = NULL;
    returan_list = (package_in*)malloc(sizeof(package_in));
    returan_list->next = NULL;

    file = fopen("package_daishou_data.txt","r");
    if (file){
        while(line_number){
            tmp = (package_in*)malloc(sizeof(package_in));
            tmp->name = (char*)malloc(sizeof(char));
            tmp->tel = (char*)malloc(sizeof(char));
            tmp->code = (char*)malloc(sizeof(char));
            tmp->id  = (char*)malloc(sizeof(char));
            tmp->company = (char*)malloc(sizeof(char));
            tmp->next = NULL;
            fscanf(file,"%f%f%s%s%s%d%d%d%s%s%ld",&tmp->weight,&tmp->volume
                    ,tmp->name,tmp->tel,tmp->code,&tmp->out_address,&tmp->in_address
                    ,&tmp->state,tmp->id,tmp->company,&tmp->time);
            p = head;
            if (head){
                while(p->next){
                    p = p->next;
                }
                p->next = tmp;
            }
            else{
                head = tmp;
                p = head;
            }
            line_number--;
        }        
    }
    fclose(file);
    returan_list->next = head;
    return returan_list;
}

package_out * bulid_package_out(){
    int line_number=0;
    line_number = get_line_number("package_out_data.txt");
    FILE *file;
    package_out *head,*tmp,*p,*returan_list;
    head = tmp = p = NULL;
    returan_list = (package_out*)malloc(sizeof(package_out));
    returan_list->next = NULL;

    file = fopen("package_out_data.txt","r");
    if (file){
        while(line_number){
            tmp = (package_out*)malloc(sizeof(package_out));
            tmp->name = (char*)malloc(sizeof(char));
            tmp->shoujianren_tel = (char*)malloc(sizeof(char));
            tmp->jijianren_tel = (char*)malloc(sizeof(char));
            tmp->out_name = (char*)malloc(sizeof(char));
            tmp->in_name = (char*)malloc(sizeof(char));
            tmp->id = (char*)malloc(sizeof(char));
            tmp->company = (char*)malloc(sizeof(char));
            tmp->next = NULL;

            fscanf(file,"%f%f%s%s%s%d%d%s%s%d%d%s%s%d",&tmp->weight,&tmp->volume
                    ,tmp->name,tmp->shoujianren_tel,tmp->jijianren_tel,&tmp->out_address
                    ,&tmp->in_address,tmp->out_name,tmp->in_name,&tmp->cost,&tmp->state
                    ,tmp->id,tmp->company,&tmp->hurry_ornot);

            p = head;
            if (head){
                while(p->next){
                    p = p->next;
                }
                p->next = tmp;
            }
            else{
                head = tmp;
                p = head;
            }
            line_number--;
        }        
    }
    fclose(file);
    returan_list->next = head;
    return returan_list;
}


int match_user_account_password(){
    user *p;
    p = (user*)malloc(sizeof(user));
    p = user_list->next;
    int c1=1,c2=1,i=0;
    while(p){
        c1=c2=1;
        if(strlen(p->zhanghao)==strlen(user_input->zhanghao)){
            if (strlen(p->mima)==strlen(user_input->mima)){
                for(i=0;i<strlen(p->zhanghao);){
                    if (p->zhanghao[i]!=user_input->zhanghao[i]){
                        c1=0;break;
                    }
                    i++;
                }
                for(i=0;i<strlen(p->mima);){
                    if (p->mima[i]!=user_input->mima[i]){
                        c2=0;break;
                    }
                    i++;
                }
                if(c1&&c2){
                    user_input = p;
                    free(p);
                    return 1;}
            }
        }
        p = p->next;
    }
    free(p);
    return 0;
}

int match_worker_account_password(){
    worker *p;
    p = (worker*)malloc(sizeof(worker));
    p = worker_list->next;
    int c1=1,c2=1,i=0;
    while(p){
        c1=c2=1;
        if(strlen(p->zhanghao)==strlen(worker_input->zhanghao)){
            if (strlen(p->mima)==strlen(worker_input->mima)){
                for(i=0;i<strlen(p->zhanghao);){
                    if (p->zhanghao[i]!=worker_input->zhanghao[i]){
                        c1=0;break;
                    }
                    i++;
                }
                for(i=0;i<strlen(p->mima);){
                    if (p->mima[i]!=worker_input->mima[i]){
                        c2=0;break;
                    }
                    i++;
                }
                if(c1&&c2){
                    worker_input = p;
                    free(p);
                    return 1;}
            }
        }
        p = p->next;
    }
    free(p);
    return 0;
}

int match_admin_account_password(){
    int c1=1,c2=1,i=0;
    if(strlen(admin_input->zhanghao)==strlen(admin_list->zhanghao)){
        if(strlen(admin_input->mima)==strlen(admin_list->mima)){
            for(i=0;i<strlen(admin_list->zhanghao);){
                if(admin_input->zhanghao[i]!=admin_list->zhanghao[i]){c1=0;break;}
            }
            for(i=0;i<strlen(admin_list->mima);){
                if(admin_input->mima[i]!=admin_list->mima[i]){c2=0;break;}
            }
            if(c1&&c2){return 1;}
        }
    }
    return 0;
}

void login_user(){
    while(1){
        input_user_account_password();
        if ((strlen(user_input->zhanghao)==1)&&(user_input->zhanghao[0]=='q')){running=0;return;}
        if (match_user_account_password(user_list)){
            printf("登录成功\n");
            running = 0;
            sleep(2);
            break;
        }
        else{
            printf("账号或密码错误\n");
            sleep(2);
            show_login_user();
        }
    }
    }

void signup_user(){
    if(input_sign_up_user()){
        save_user_data();
        printf("注册成功\n");
        user_list = bulid_user();
        sleep(2);
    }
}


void input_user_account_password(){
    user_input = (user*)malloc(sizeof(user));
    user_input->zhanghao = (char*)malloc(sizeof(char));
    user_input->mima = (char*)malloc(sizeof(char));
    printf("请输入账号(输入q退出):");
    scanf("%s",user_input->zhanghao);
    fflush(stdin);
    if ((strlen(user_input->zhanghao)!=1)&&(user_input->zhanghao[0]!='q')){
        printf("请输入密码:");
        scanf("%s",user_input->mima);
        fflush(stdin);
    }
    else{user_input->name=NULL;}
}

void input_worker_account_password(){
    worker_input = (worker*)malloc(sizeof(worker));
    worker_input->zhanghao = (char*)malloc(sizeof(char));
    worker_input->mima = (char*)malloc(sizeof(char));
    printf("请输入工号:");
    scanf("%s",worker_input->zhanghao);
    fflush(stdin);
    if ((strlen(worker_input->zhanghao)!=1)&&(worker_input->zhanghao[0]!='q')){
        printf("请输入密码:");
        scanf("%s",worker_input->mima);
        fflush(stdin);
    }
    else{
        running = 0;
    }
}

void input_admin_account_password(){
    admin_input = (admin*)malloc(sizeof(admin));
    admin_input->zhanghao = (char*)malloc(sizeof(char));
    admin_input->mima = (char*)malloc(sizeof(char));
    printf("请输入账号:");
    scanf("%s",admin_input->zhanghao);
    fflush(stdin);
    printf("请输入密码:");
    scanf("%s",admin_input->mima);
    fflush(stdin);
}

int input_sign_up_user(){
    user_input = (user*)malloc(sizeof(user));
    user_input->name = (char*)malloc(sizeof(char));
    user_input->zhanghao = (char*)malloc(sizeof(char));
    user_input->mima = (char*)malloc(sizeof(char));
    user_input->tel = (char*)malloc(sizeof(char));
    user_input->num_ji = user_input->num_qu = 0;
    user_input->star_level = 1;
    user_input->next = NULL;


    system("clear");
    printf("请输入用户名:");
    scanf("%s",user_input->name);
    fflush(stdin);
    printf("请输入注册账号:");
    scanf("%s",user_input->zhanghao);
    fflush(stdin);
    printf("请输入在注册密码:");
    scanf("%s",user_input->mima);
    fflush(stdin);
    if(match_user_account_password(user_list)){
        printf("该账号密码已在已经注册过 请转至登陆\n");
        sleep(2);
        mode_login = '0';
        return 0;
    }

    printf("请输入手机号码:");
    scanf("%s",user_input->tel);
    user_input->id = get_line_number("user_data.txt")+1;
    user * p;
    p = user_list->next;
    while(p->next){p = p->next;};
    p->next = user_input;
    return 1;
}

void save_user_data(){
    FILE *f; 
    f = fopen("./user_data.txt","w");
    user * p;
    p = user_list->next;
    while(p){
        fprintf(f,"%s %s %s %d %d %d %s\n"
            ,p->name,p->zhanghao,p->mima,p->id,p->num_ji,p->num_qu
            ,p->tel);    
        p = p->next;
    }
    fclose(f);
}

void save_worker_data(){
    FILE *f; 
    f = fopen("./worker_data.txt","w");
    worker * p;
    p = worker_list->next;
    while(p){
        fprintf(f,"%s %s %s\n",p->name,p->zhanghao,p->mima);    
        p = p->next;
    }
    fclose(f);
}

void save_package_in_data(){
    FILE *f; 
    f = fopen("./package_in_data.txt","w");
    package_in * p;
    p = ruku_package->next;
    while(p){
        fprintf(f,"%f %f %s %s %s %d %d %d %s %s %ld\n",p->weight,p->volume
                    ,p->name,p->tel,p->code,p->out_address,p->in_address
                    ,p->state,p->id,p->company,p->time);    
        p = p->next;
    }
    fclose(f);

}

void save_package_daishou_data(){
    FILE *f; 
    f = fopen("./package_daishou_data.txt","w");
    package_in * p;
    p = daishou_package->next;
    while(p){
        fprintf(f,"%f %f %s %s %s %d %d %d %s %s %ld\n",p->weight,p->volume
                    ,p->name,p->tel,p->code,p->out_address,p->in_address
                    ,p->state,p->id,p->company,p->time);    
        p = p->next;
    }
    fclose(f);
}

void save_package_out_data(){
    FILE *f; 
    f = fopen("./package_out_data.txt","w");
    package_out * p;
    p = ji_package->next;
    while(p){
        fprintf(f,"%f %f %s %s %s %d %d %s %s %d %d %s %s %d\n",p->weight,p->volume
            ,p->name,p->shoujianren_tel,p->jijianren_tel,p->out_address
            ,p->in_address,p->out_name,p->in_name,p->cost,p->state
            ,p->id,p->company,p->hurry_ornot);    
        p = p->next;
    }
    fclose(f);
}