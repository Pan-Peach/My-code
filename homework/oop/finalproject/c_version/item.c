#include <stdio.h>
#include <stdlib.h>
#include "item.h"

// user * bulid_user(){
//     user *head=NULL;
//     head=(user *)malloc(sizeof(user));
//     head->next=NULL;
//     return head;
// }
// worker * bulid_worker(){
//     worker *head=NULL;
//     head=(worker *)malloc(sizeof(worker));
//     head->next=NULL;
//     return head;
// }

// package_in * bulid_package_in(){
//     package_in *head=NULL;
//     head=(package_in *)malloc(sizeof(package_in));
//     head->next=NULL;
//     return head;
// }
// package_out * bulid_package_out(){
//     package_out *head=NULL;
//     head=(package_out *)malloc(sizeof(package_out));
//     head->next=NULL;
//     return head;
// }
int distance[address_num][address_num]={
    {  0, 12, 45, 23, 34 },
    { 12,  0, 56, 78, 19 },
    { 45, 56,  0, 89, 67 },
    { 23, 78, 89,  0, 50 },
    { 34, 19, 67, 50,  0 }
};
int left_room[num_guizi];//剩余空间
int code[num_guizi][guizi_room];//取件码占用情况0未占用，1已占用
char *company[]={"SF","YG","JD"};


user* user_list;
worker* worker_list;
admin*  admin_list;
package_in* daishou_package;
package_in* nuw_package;
package_in* ruku_package;
package_out* ji_package;
