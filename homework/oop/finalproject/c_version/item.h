#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<time.h>
#define num_guizi 5
#define address_num 5
#define guizi_room 500
typedef struct user{
    char *name;
    char *zhanghao;
    char *mima;
    int id;//6位身份码
    int num_ji;
    int num_qu;
    char *tel;//电话号
    int star_level;//用户级别
    struct user *next;
}user;
typedef struct worker{
    char *name;
    char *zhanghao;
    char *mima;

    struct worker *next;
}worker;
typedef struct admin{
    char *zhanghao;
    char *mima;

}admin;
typedef struct package_in{
    float weight;
    float volume;
    char *name;
    char *tel;//收件人电话
    char *code;//取件码(货柜号+数组下标)
    int out_address;
    int in_address;
    int state;//0未取件，取走的话state=user.id身份码
    char *id;
    char *company;
    time_t time;//时间戳
    struct package_in *next;
}package_in;
typedef struct package_out{
    float weight;
    float volume;
    char *name;
    char *shoujianren_tel;
    char *jijianren_tel;
    int out_address;
    int in_address;
    char *out_name;
    char *in_name;
    int cost;
    int state;//0未寄出，1已寄出
    char *id;
    char *company;
    int hurry_ornot;
    struct package_out *next;
}package_out;
user * bulid_user();
worker * bulid_worker();
admin * bulid_admin();
package_in * bulid_package_in();
package_out * bulid_package_out();

extern user* user_list;
extern worker* worker_list;
extern admin*  admin_list;

extern package_in* daishou_package;
extern package_in* nuw_package;
extern package_in* ruku_package;
extern package_out* ji_package;


extern int distance[address_num][address_num];
extern int left_room[num_guizi];//剩余空间
extern int code[num_guizi][guizi_room];//取件码占用情况0未占用，1已占用
extern char *company[];