#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Data structures for Password file content */
typedef struct paswd {
       char passwd_line[500]; 			// reads the entire line from the file as input 
       char user_name[32];  			// stores the username
       char enc_passwd[200];			// stores the encrypted password
       char uid[10];				// stores the user ID
       char grpid[10];				// stores the group ID
       char user_fullname[100];			// Stores the fullname of the user
       char user_homedir[100];			// stores the home directory of the user
       char shell[50];			        // shell
       int error;			        // marks the line number where the error is found
} paswd_t;

paswd_t paswd_table[200];

/* Data structures for Shadow file content */
typedef struct shadw {
       char shadw_line[500];
       char user_name[32];
       char passwd[300];
       char last_change[10];
       char min[10];
       char max[10];
       char warn[10];
       char inactive[10];
       char expire[10];
       int error;
} shadw_t;

shadw_t shadw_table[200];

/* Data structures for Group file content */
typedef struct grpp {
       char grp_line[500];
       char grp_name[32];
       char passwd[100];
       char grpid[10];
       char grp_user_list[100][100];
       int error;
} grp_t;

grp_t grp_table[200];

FILE *paswd_fp, *shwd_fp, *grp_fp;

/* global variables to track the no of entries in each file */
int p_ent, s_ent, g_ent;

/* Functions that the project uses */
void init_paswd_table();
void init_shadw_table();
void init_grp_table();
void read_paswdfile(FILE *fp); 
void read_shadwfile(FILE *fp); 
void read_grpfile(FILE *fp); 
int fill_paswd_table(char *oneline);
int fill_shadw_table(char *oneline);
int fill_grp_table(char *oneline);
void print_paswd_table();
void print_shadw_table();
void print_grp_table();
void print_paswd_table_with_errors();
void print_shadw_table_with_errors();
void print_grp_table_with_errors();
void check_dup_in_paswd_table();
void check_dup_in_shadw_table();
void check_dup_in_grp_table();
void check_user_passwd_shadw_tables();
void check_user_passwd_grp_tables();
void check_user_paswd_grp_tables() ;
void check_home_dir_for_user();


