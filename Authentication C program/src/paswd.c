#include "def.h"

/*--------------------------------------------------------------------
 * read_paswdfile
 *--------------------------------------------------------------------*/
/*
 *      Reads the password file line by line into Internal data structures
 */
void read_paswdfile(FILE *fp) {
    char oneline[120];
    char *line;

    while (line =fgets(oneline, 100, fp ) ) { 
        fill_paswd_table(oneline);
    }
}

/*--------------------------------------------------------------------
 * fill_paswd_table
 *--------------------------------------------------------------------*/
/*
 *      Fill the Password internal data structures
 */
int fill_paswd_table(char *oneline) {

   char *cp = oneline;
   int noofItems = 0;
   char *substr, *new;
   char org_lin[100]; 

   strcpy(paswd_table[p_ent].passwd_line,oneline);
    while (*cp != '\0') {
        char *substr = strchr(cp,':');
        if (substr == 0)  {
            if (noofItems < 6) {
                paswd_table[p_ent].error = 1;
                p_ent ++;
                return 0;
            }
            strcpy(paswd_table[p_ent].shell,cp);
            paswd_table[p_ent].error = 0;
            break;
         }
         new=substr+1;
         *substr = '\0';
         if(noofItems==0) strcpy(paswd_table[p_ent].user_name,cp);
         if(noofItems==1) strcpy(paswd_table[p_ent].enc_passwd,cp);
         if(noofItems==2) strcpy(paswd_table[p_ent].uid,cp);
         if(noofItems==3) strcpy(paswd_table[p_ent].grpid,cp);
         if(noofItems==4) strcpy(paswd_table[p_ent].user_fullname,cp);
         if(noofItems==5) strcpy(paswd_table[p_ent].user_homedir,cp);
         noofItems++;
         cp = new;

    }

     p_ent++;

     return 1;
 }

/*--------------------------------------------------------------------
 * init_paswd_table
 *--------------------------------------------------------------------*/
/*
 *      Initilize the Password internal data structures
 */
void init_paswd_table() {

    for (int i=0; i< 200 ; i++ ) {
        paswd_table[i].passwd_line[0] =  '\0';
        paswd_table[i].user_name[0] =  '\0';
        paswd_table[i].enc_passwd[0] =  '\0';
        paswd_table[i].uid[0]=  '\0';
        paswd_table[i].grpid[0] = '\0';
        paswd_table[i].user_fullname[0] = '\0';
        paswd_table[i].user_homedir[0] =  '\0';
        paswd_table[i].shell[0] = '\0';
        paswd_table[i].error = 0;
    }

}

/*--------------------------------------------------------------------
 * print_paswd_table
 *--------------------------------------------------------------------*/
/*
 *      Print the password table for debug purpose
 */
void print_paswd_table() {

    for (int i=0; i< p_ent ; i++ ) {
        printf("At line no %d \n",i+1);
        printf("\t Passwd Line = %s",paswd_table[i].passwd_line);
        printf("\t User Name = %s \n",paswd_table[i].user_name);
        printf("\t Encrypted Password  = %s \n",paswd_table[i].enc_passwd);
        printf("\t User Id = %s \n",paswd_table[i].uid);
        printf("\t Group Id = %s \n",paswd_table[i].grpid);
        printf("\t User Fullname = %s \n",paswd_table[i].user_fullname);
        printf("\t User Homedir = %s \n",paswd_table[i].user_homedir);
        printf("\t Shell = %s \n",paswd_table[i].shell);
        printf("\t Error = %d \n", paswd_table[i].error);
    }

}

/*--------------------------------------------------------------------
 * print_paswd_table_with_errors
 *--------------------------------------------------------------------*/
/*
 *      Print lines from the password file that has errors
 */
void print_paswd_table_with_errors() {

    for (int i=0; i< p_ent ; i++ ) {
        if (paswd_table[i].error) {
            printf("Missing entries at line no %d \n",i+1);
            printf("\t Passwd Line = %s",paswd_table[i].passwd_line);
            printf("\n");
        }
    }

}

/*--------------------------------------------------------------------
 * check_dup_in_paswd_table
 *--------------------------------------------------------------------*/
/*
 *      Checks for duplicate entries in the password file content
 */
void check_dup_in_paswd_table() {

    for (int i=0; i< p_ent ; i++ ) {
        for (int j=0; j < i; j++) {
            if ( !paswd_table[i].error) {
                if (strcmp(paswd_table[i].user_name ,paswd_table[j].user_name) ==0) {
                    printf("\t Dulicate entry exits for user \'%s\' at line %d and %d \n", paswd_table[i].user_name, i+1, j+1);
                    printf("\t Please correct the same and rerun this tool \n");
                }
            }
        }
   }
}

/*--------------------------------------------------------------------
* check_home_dir_for_user
*--------------------------------------------------------------------*/
/*
 *      Check the existance of the home_dir
 */

void check_home_dir_for_user() {

    DIR *dfd;
    for (int i=0; i< p_ent ; i++ ) {
        if ((!paswd_table[i].error) && ((dfd = opendir(paswd_table[i].user_homedir)) == NULL)) {
            printf("Home dir %s for user %s doesn't exist. Kindly correct the same\n",paswd_table[i].user_homedir, paswd_table[i].user_name);
        }
        if (!dfd) closedir(dfd);
    }
}

