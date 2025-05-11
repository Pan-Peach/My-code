#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"item.h"
#include<time.h>


//展示待收判断是否收件
void zhanshipanudan() {
    package_in* p = daishou_package->next;
    int count = 1;
    int q = -1;
    while (1) {
        system("cls");
        fflush(stdin);
        for(p = daishou_package->next; p!=NULL;p=p->next){
            printf("第%d个快递信息如下:", count);
            printf("取件地址：%d ", p->in_address);
            printf("寄件地址：%d\n", p->out_address);
            count++;
        }
        if (count == 1) {
            printf("暂无快递\n");
            return;
        }
        printf("是否收件？\n");
        printf("1.一键收件\n");
        printf("2.不收件\n");
        if (scanf("%d", &q) == -1) {
            printf("输入有误\n");
            Sleep(1000);
            return;
        }
        if (q != 1 && q != 2) {
            printf("输入有误\n");
            Sleep(1000);
            return;
        }
        if (q == 1) {
            p = daishou_package->next;
            package_in* p1 = daishou_package;
            while (p != NULL) {
                p1->next = p->next;
                p->next = nuw_package->next;
                nuw_package->next = p;
                p = p1->next;
                count--;
            }
            while (count == 1) {
                printf("已全部收件\n");
                Sleep(1000);
                return;
            }
        }
        else {
            printf("请输入要拒收的快递序号：\n");
            int n;
            if (scanf("%d", &n) == -1) {
                printf("输入错误\n");
                return;
            }
            fflush(stdin);
            if (n<1 || n>count - 1) {
                printf("输入有误\n");
                return;
            }
            p = daishou_package->next;
            package_in* p1 = daishou_package;
            for (int i = 1;i < n;i++) {
                p1 = p;
                p = p->next;
            }
            printf("拒收成功\n");
            Sleep(1000);
            p1->next = p->next;
            free(p);
            count=1;
        }
    }

}
void inti_package() {
    package_in* p = nuw_package->next;
    package_in* p1 = nuw_package;
    int c[5];
    int j = 0;
    for (int i = 0;i < 5;i++) {
        c[i] = -1;
    }
    while (p != NULL) {
        system("cls");
        float volume = p->volume;
        char gui;
        int a, b = -1;
        if (volume > 0 && volume <= 20) {
            gui = 'A';
            a = 0;
        }
        else if (volume > 20 && volume <= 40) {
            gui = 'B';
            a = 1;
        }
        else if (volume > 40 && volume <= 60) {
            gui = 'C';
            a = 2;
        }
        else if (volume > 60 && volume <= 80) {
            gui = 'D';
            a = 3;
        }
        else {
            gui = 'E';
            a = 4;
        }
        for (int i = 0;i < guizi_room;i++) {
            if (code[a][i] == 0) {
                b = i;
                break;
            }
        }
        if (b != -1) {
            char* code1 = (char*)malloc(sizeof(char) * 10);
            sprintf(code1, "%c%d", gui, b);
            p->code = code1;
            p->time = time(NULL);
            code[a][b] = 1;
            p1->next = p->next;
            p->next = ruku_package->next;
            p = p1->next;
            ruku_package->next = p;
            if (p->next == NULL) {
                printf("已入库成功\n");
                int count = 0;
                package_in* tmp = nuw_package->next;
                while (tmp) {
                    count++;
                    tmp = tmp->next;
                }
                printf("还有%d件未入库\n", count);
                Sleep(1000);
            }
        }
        else {
            // 检查是否已经提示过该柜子类型“已满”
            int already_notified = 0;
            for (int k = 0; k < j; k++) {
                if (c[k] == a) {
                    already_notified = 1;
                    break;
                }
            }

            // 如果未提示过，则输出提示信息并记录
            if (!already_notified) {
                printf("%c号柜已满\n", gui);
                printf("入库失败\n");
                Sleep(1000);
                // 记录已提示“已满”的柜子类型
                if (j < 5) {
                    c[j] = a;
                    j++;
                }
            }
            p = p->next;
            p1 = p1->next;
        }
    }
}
//查询某一指定的已入库的快递
void search() {
    system("cls");
    char id[100];
    while (1) {
        fflush(stdin);
        printf("请输入快递单号：\n");
        scanf("%s", id)；
        package_in* p = ruku_package->next;
        while (p != NULL) {
            if (strcmp(p->id, id) == 0) {
                if (p->state != 0) {
                    printf("该快递已出库\n");
                    printf("取件人:%d\n", p->state);
                    Sleep(2000);
                }
                else {
                    printf("该快递未出库\n");
                    Sleep(1000);
                }
                return;
            }
            p = p->next;
        }
        printf("未找到该快递,请重新输入\n");
        Sleep(1000);
    }
}

//空间剩余查询和预警
void space() {
    system("cls");
    int sum[5];
    for (int i = 0;i < num_guizi;i++) {
        sum[i] = 0;
    }
    for (int i = 0;i < num_guizi;i++) {
        for (int j = 0;j < guizi_room;j++) {
            if (code[i][j] == 0) {
                sum[i]++;
            }
        }
    }
    for (int i = 0;i < num_guizi;i++) {
        if (sum[i] < guizi_room / 10) {
            printf("第%d个柜子空间不足\n", i + 1);
            printf("剩余空间为：%d\n", sum[i]);
            Sleep(2000);
        }
        else {
            printf("第%d个柜子空间充足\n", i + 1);
            printf("剩余空间为：%d\n", sum[i]);
            Sleep(2000);
        }
    }
}
//发件
void send() {
    system("cls");
    int i;
    package_out* p = ji_package->next;
    for (i = 1;p != NULL;p = p->next) {
        if (p->state == 0) {
            printf("快递%d", i);
            printf("重量：%f\n", p->weight);
            printf("体积：%f\n", p->volume);
            printf("姓名：%s\n", p->name);
            printf("收件人电话：%s\n", p->shoujianren_tel);
            printf("寄件人电话：%s\n", p->jijianren_tel);
            printf("寄件地址：%d\n", p->out_address);
            printf("收件地址：%d\n", p->in_address);
            printf("快递单号：%s\n", p->id);
            printf("快递公司：%s\n", p->company);
            Sleep(3000);
        }
    }
    for (p = ji_package->next;p != NULL;p = p->next) {
        p->state = 1;
        if(p->next == NULL){
            printf("已全部寄出\n");
            Sleep(1000);
        }
    }
}
void worker_menu() {
    while (1) {
        system("cls");
        // 显示菜单
        printf("\n**********************************\n");
        printf("* 欢迎使用快递管理系统          *\n");
        printf("* 1.快递收件                    *\n");
        printf("* 2.入库                        *\n");
        printf("* 3.快递查询                    *\n");
        printf("* 4.空间剩余查询                *\n");
        printf("* 5.快递发件                    *\n");
        printf("* 6.退出                        *\n");
        printf("**********************************\n");
        printf("请输入您的选择: ");
        int choice;
        scanf("%d", &choice);
        if (scanf("%d", &choice) != 1) {
            printf("输入错误请重新输入\n");
            while (getchar() != '\n'); // 清空输入缓冲区
            continue; 
        }
        // 根据用户选择调用相应函数
        switch (choice) {
        case 1:
            zhanshipanudan(); // 快递收件
            break;
        case 2:
            inti_package(); // 入库
            break;
        case 3:
            search(); // 快递查询
            break;
        case 4:
            space(); // 空间剩余查询
            break;
        case 5:
            send(); // 快递发件
            break;
        case 6:
            printf("感谢使用，程序退出！\n");
            return; // 退出程序
        default:
            printf("无效的选择，请重新输入！\n");
            return;
        }
    }
}

