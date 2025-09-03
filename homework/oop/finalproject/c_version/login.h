#pragma once
#include<stdio.h>
#include<unistd.h>
#include"item.h"

int get_line_number(char *filename);
void show_options();
void show_login_user();
void show_login_worker();
void show_login_admin();
void input_user_account_password();
void input_worker_account_password();
void input_admin_account_password();
void login_user();
void signup_user();
int input_sign_up_user();
int match_user_account_password();
int match_worker_account_password();
int match_admin_account_password();
void save_user_data();
void save_worker_data();
void save_package_in_data();
void save_package_daishou_data();
void save_package_out_data();

extern user* user_input;
extern worker* worker_input;
extern admin* admin_input;
extern char mode_login;
extern int running;
