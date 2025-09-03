#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <unistd.h>
#include"item.h"
static int jijianidx=0;
void find_package(user a){
    system("clear");
    fflush(stdin);
    int package_num=0;
    package_in *p=ruku_package->next;
    time_t now=time(NULL);
    while(p){
        if(strcmp(p->tel,a.tel)==0&&p->state==0){
            package_num++;
            double second =difftime(now,p->time);
            int days = second / (60 * 60 * 24);
            if(days>=5){
                printf("取件码:%s  您的包裹已经存放%d天啦请尽快取走\n",p->code,days);
            }
            else{
                printf("取件码:%s\n",p->code);
            }
            
        }
        p=p->next;
    }
    printf("共有%d个包裹代取\n",package_num);
    printf("0.返回\n");
    while(1){
        char m=getchar();
        if(m=='0')break;
        else{
            fflush(stdin);
        }
    }
}
void fetch_package(user a){
    system("clear");
    fflush(stdin);
    while(1){
        int num=0;
        package_in *p=ruku_package->next;
        while(p){
            if(strcmp(p->tel,a.tel)==0&&p->state==0){
                printf("%d.取件码:%s %d\n",++num,p->code,p->state);
            }
            p=p->next;
        }
        if(num==0){
            printf("包裹已全部取走\n");
        }
        printf("0.退出\n");
        char m;
        package_in *daishan;
        while(1){
            m=getchar();
            
            int idx=m-'0';
            if(idx==0){
                break;
            }
            else if(idx>0&&idx<=num){
                int uselessint=0;
                p=ruku_package->next;
                while(uselessint<idx){
                    if(strcmp(p->tel,a.tel)==0&&p->state==0){
                        uselessint++;
                    }
                    if(uselessint==idx)
                        daishan=p;
                    p=p->next;
                }
                daishan->state=a.id;
                system("clear");
                printf("出库成功剩%d个包裹\n",--num);
                sleep(1);
                break;
            }
            else{
                fflush(stdin);
            }
        }
        if(m=='0')break;
        else system("clear");
    }
}
void daiqu_package(user a){
    system("clear");
    fflush(stdin);
    while(1){
        
        printf("1.我要帮他人取快递\n");
        printf("0.退出\n");
        char m;
        while(1){
            m=getchar();
            int xuanze=m-'0';
            if(xuanze==0){
                break;
            }
            else if(xuanze==1){
                system("clear");
                printf("请输入取件码:\n");
                char in_code[20];
                int flag=0;
                fflush(stdin);
                fgets(in_code, sizeof(in_code), stdin);
                in_code[strcspn(in_code, "\n")] = '\0';
                package_in *p=ruku_package->next;
                while(p){
                    if(strcmp(p->code,in_code)==0&&p->state==0){
                        p->state=a.id;
                        flag=1;
                        system("clear");
                        printf("代取成功\n");
                        sleep(1);
                        break;
                    }
                    p=p->next;
                }
                if(flag==0){
                    system("clear");
                    printf("没有找到包裹\n");
                    sleep(1);
                }
                break;
            }
            else{
                fflush(stdin);
            }
        }
        if(m=='0')break;
        else system("clear");
    }
    
}
void ji_package_fun(user a){
    system("clear");
    fflush(stdin);
    package_out *tail=ji_package;
    while(tail->next)tail=tail->next;
    package_out *new=(package_out*)malloc(sizeof(package_out));
    printf("请输入包裹重量\n");
    while (scanf("%f", &new->weight) != 1) {
        printf("输入无效,请重新输入\n");
        fflush(stdin);
    }
    fflush(stdin);
    printf("请输入包裹体积\n");
    while (scanf("%f", &new->volume) != 1) {
        printf("输入无效,请重新输入\n");
        fflush(stdin);
    }
    fflush(stdin);
    printf("请输入收件人电话\n");
    new->shoujianren_tel=(char *)malloc(sizeof(char)*15);
    new->jijianren_tel=(char *)malloc(sizeof(char)*15);
    while (scanf("%s", new->shoujianren_tel) != 1||strlen(new->shoujianren_tel)!=11) {
        printf("输入无效,请重新输入\n");
        fflush(stdin);
    }
    strcat(new->jijianren_tel,a.tel);
    fflush(stdin);
    printf("请选择寄出地址(1~5)\n");
    while (scanf("%d", &new->out_address) != 1||new->out_address>5||new->out_address<1) {
        printf("输入无效,请重新输入\n");
        fflush(stdin);
    }
    new->out_address-=1;
    fflush(stdin);
    printf("请选择收货地址(1~5)\n");
    while (scanf("%d", &new->in_address) != 1||new->in_address>5||new->in_address<1) {
        printf("输入无效,请重新输入\n");
        fflush(stdin);
    }
    new->in_address-=1;
    fflush(stdin);
    new->out_name=(char *)malloc(sizeof(char)*15);
    printf("请输入寄件人姓名\n");
    while (scanf("%s", new->out_name) != 1) {
        printf("输入无效,请重新输入\n");
        fflush(stdin);
    }
    fflush(stdin);
    new->in_name=(char *)malloc(sizeof(char)*15);
    printf("请输入收件人姓名\n");
    while (scanf("%s", new->in_name) != 1) {
        printf("输入无效,请重新输入\n");
        fflush(stdin);
    }
    fflush(stdin);
    printf("请选择快递公司(1.SF 2.YZ 3.JD)\n");
    int choice;
    while (scanf("%d", &choice) != 1||(choice!=1&&choice!=2&&choice!=3)) {
        printf("输入无效,请重新输入\n");
        fflush(stdin);
    }
    new->company=company[choice-1];
    fflush(stdin);
    printf("您是否需要加急?(1.需要 2.不需要)\n");
    while (scanf("%d", &new->hurry_ornot) != 1||(new->hurry_ornot!=1&&new->hurry_ornot!=2)) {
        printf("输入无效,请重新输入\n");
        fflush(stdin);
    }
    fflush(stdin);
    new->id=(char*)malloc(sizeof(char)*15);
    strcat(new->id,new->company);
    strcat(new->id,"1");
    char dizhiid[3];
    dizhiid[0]=(char)('0'+new->out_address);
    dizhiid[1]=(char)('0'+new->in_address);
    dizhiid[2]='\0';
    strcat(new->id,dizhiid);
    char bianhao[4]="000";
    int flag=jijianidx;
    int flag_idx=2;
    while(flag>0){
        bianhao[flag_idx]='0'+flag%10;
        flag/=10;
        flag_idx--;
    }
    
    strcat(new->id,bianhao);
    jijianidx++;
    tail->next=new;
    new->next=NULL;
    
    new->state=0;

    int all_cost=(3-new->hurry_ornot)*(1-0.01*a.star_level)*(10*(distance[new->out_address][new->in_address])+1.2*new->weight+1.2*new->volume);
    if(strcmp(new->company,"JD")==0)all_cost*=2;
    if(strcmp(new->company,"SF")==0)all_cost*=3;
    new->cost=all_cost;
    fflush(stdin);
    printf("您需要支付%d元\n",new->cost);
    getchar();
    system("clear");
    printf("寄件成功,请随时查看订单情况\n");
    sleep(1);

}
void look_ji_package(user a){
    system("clear");
    fflush(stdin);
    package_out *p=ji_package->next;
    int num=0;
    while(p){
        if(strcmp(p->jijianren_tel,a.tel)==0&&p->state==0){
            
            printf("%d.包裹订单号:%s 收件人:%s\n",++num,p->id,p->in_name);
            
        }
        p=p->next;
    }
    if(num==0){
        printf("没有待寄包裹\n");
    }
    printf("0.返回\n");
    while(1){
        char m=getchar();
        if(m=='0')break;
        else{
            fflush(stdin);
        }
    }
}
void user_menu(user a){
    int level=a.num_ji+a.num_qu;
    if(level>=0&&level<20)a.star_level=1;
    else if(level>=20&&level<40)a.star_level=2;
    else if(level>=40&&level<80)a.star_level=3;
    else if(level>=80&&level<200)a.star_level=4;
    else a.star_level=5;
    while(1){
    system("clear");
    fflush(stdin);
    printf("*********************************\n");
    printf("*      欢迎尊贵的%d星级用户       *\n",a.star_level);
    printf("*1.待取包裹                      *\n");
    printf("*2.取包裹                        *\n");
    printf("*3.我要代取                      *\n");
    printf("*4.我要寄件                      *\n");
    printf("*5.查看我的待寄包裹              *\n");
    printf("*0.退出                          *\n");
    printf("*********************************\n");
    char m=getchar();
    switch (m) {
        case '0':{
            break;
        }
        case '1':{
            find_package(a);
            break;
        }
        case '2':{
            fetch_package(a);
            break;
        }
        case '3':{
            daiqu_package(a);
            break;
        }
        case '4':{
            ji_package_fun(a);
            break;
        }
        case '5':{
            look_ji_package(a);
            break;
        }
    }
    if(m=='0'){
        break;
    }
    }
    
}