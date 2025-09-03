#include "admin_interface.h"
#include <windows.h>

void admin_choice(){
    SetConsoleOutputCP(65001);
    int choice;
    system("cls");
    while(1){
        printf("1.员工操作\n");
        printf("2.用户操作\n");
        printf("3.入库包裹操作\n");
        printf("4.退出\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                admin_worker_operation();
                break;
            case 2:
                admin_user_operation();
                break;
            case 3:
                admin_ruku_package_operation();
                break;
            case 4:
                return;
            default:
                printf("选择错误\n");
        }
        system("pause");
        system("cls");
    }
}

void admin_worker_operation(){
    int choice;
    system("cls");
    while(1){
        printf("1.添加员工\n");
        printf("2.删除员工\n");
        printf("3.查看所有员工\n");
        printf("4.查找员工\n");
        printf("5.退出\n");
        scanf("%d", &choice);
        switch(choice){
            case 1: {
                char name[100];
                char password[100];
                printf("输入姓名和密码\n");
                scanf("%99s%99s", name, password);
                add_worker(name, password);
                break;
            }
            case 2:{
                char account[100];
                printf("输入账号\n");
                scanf("%99s", account);
                delete_worker(account);
                break;
            }    
            case 3:
                view_all_worker();
                break;
            case 4:{
                char account[100];
                printf("输入账号\n");
                scanf("%99s", account);
                find_worker(account);
                break;
            }     
            case 5:
                return;
            default:
                printf("选择错误\n");
        }
        system("pause"); 
        system("cls");
    }
}

void admin_user_operation(){
    int choice;
    system("cls");
    while(1){
        printf("1.查看所有用户\n");
        printf("2.查找用户\n");
        printf("3.退出\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                view_all_user();
                break;
            case 2:{
                char account[100];
                printf("输入账号\n");
                scanf("%99s", account);
                find_user(account);
                break;
            }     
            case 3:
                return;
            default:
                printf("选择错误\n");
        }
        system("pause"); 
        system("cls");
    }
}

void admin_daishou_package_operation(){
    // 保留函数，但不在菜单中使用
}

void admin_nuw_package_operation(){
    // 保留函数，但不在菜单中使用
}

void admin_ruku_package_operation(){
    int choice;
    system("cls");
    while(1){
        printf("1.查看所有入库包裹\n");
        printf("2.查找入库包裹\n");
        printf("3.退出\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                view_all_ruku_package();
                break;
            case 2:{
                char code[100];
                printf("输入代码\n");
                scanf("%99s", code);
                find_ruku_package(code);
                break;
            }
            case 3:
                return;
            default:
                printf("选择错误\n");
        }
        system("pause");
        system("cls");
    }
}