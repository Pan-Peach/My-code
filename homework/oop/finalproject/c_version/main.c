#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include"user_fun.h"
#include"item.h"
#include"login.h"
#include"admin.h"
#include"admin_interface.h"

user* user_input;
worker* worker_input;
admin* admin_input;
int mode=0; //1=用户 2=员工 3=管理者
char mode_login='0';//1=登录 2=注册
int running=0;


int main(){
    system("chcp 65001");
    user_list =  bulid_user();
    worker_list = bulid_worker();
    admin_list = bulid_admin();
    ruku_package = bulid_package_in();
    daishou_package = build_package_daishou();
    ji_package = bulid_package_out();

    user_input = (user*)malloc(sizeof(user));
    worker_input = (worker*)malloc(sizeof(worker));
    admin_input = (admin*)malloc(sizeof(admin));

    while(true){
        show_options();//显示登录界面
        scanf("%d",&mode);
        fflush(stdin);
        if (mode==1){
            running=1;
            while(running){
                show_login_user();
                printf("请选择登录/注册(输入q退出):");
                getchar();
                scanf("%c",&mode_login);
                fflush(stdin);
                if (mode_login=='1'){login_user();}
                else if (mode_login=='2'){signup_user("./user_data.txt");}
                else if (mode_login=='q'){user_input->name =NULL;running = 0;}
                else{printf("无效输入\n");sleep(2);}
            }
            if (user_input->name){user_menu(*user_input);}
            running =0;
        }
        else if (mode==2){
            running = 1;
            show_login_worker();
            while(running){
                input_worker_account_password();
                if (running && match_worker_account_password()){printf("登陆成功\n");sleep(2);}
                else if (!running){break;}
                else{printf("工号或密码错误\n");sleep(1);}
            }
        }
        else if (mode==3){
            running=1;
            while(running){
                show_login_admin();
                input_admin_account_password();
                if(match_admin_account_password()){
                    admin_choice();
                    running=0;
                }
                else{
                    printf("账号或密码错误\n");
                    sleep(2);
                }
            }
        }
        else if (mode==0){
            return 0;
        }
        else{
            printf("无效输入\n");
	        sleep(1);
        }

    }
    save_user_data();
    save_worker_data();
    save_package_in_data();
    save_package_daishou_data();
    save_package_out_data();

    return 0;
}
