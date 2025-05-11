#pragma once
#include<string.h>
#include"item.h"

extern const int account_len;//工号长度 ps:如果数字长度超过len会自动加长

//worker operations
void worker_account_init();
void find_worker();
void view_all_worker();
void add_worker();
void delete_worker();

//user operations
void find_user();
void view_all_user();

//packege_in operations

//daisou_package operations
void find_daishou_package();//参数是code
void view_all_daishou_package();

//nuw_package operations
void find_nuw_package();
void view_all_nuw_package();

//rukou_package operations
void find_ruku_package();
void view_all_ruku_package();
