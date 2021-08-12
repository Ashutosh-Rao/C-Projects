#include "def.h"

/*--------------------------------------------------------------------
 * read_grpfile
 *--------------------------------------------------------------------*/
/*
 *      Reads the Group file line by line into Internal data structures
 */
void read_grpfile(FILE *fp) {
    char oneline[120];
    char *line;

    while (line =fgets(oneline, 100, fp ) ) { 
        fill_grp_table(oneline);
    }
}

/*--------------------------------------------------------------------
 * fill_grp_table
 *--------------------------------------------------------------------*/
/*
 *      Fill the Group internal data structures
 */
int fill_grp_table(char *oneline) {

   char *cp = oneline;
   int noofItems = 0;
   char *substr, *new;
   char org_lin[100]; 

   strcpy(grp_table[g_ent].grp_line,oneline);
    while (*cp != '\0') {
        char *substr = strchr(cp,':');
        if (substr == 0)  {
            if (noofItems < 3) {
                grp_table[g_ent].error = 1;
                g_ent ++;
                return 0;
            }
            strcpy(grp_table[g_ent].grp_user_list[0],cp);
            grp_table[g_ent].error = 0;
            break;
         }
         new=substr+1;
         *substr = '\0';
         if(noofItems==0) strcpy(grp_table[g_ent].grp_name,cp);
         if(noofItems==1) strcpy(grp_table[g_ent].passwd,cp);
         if(noofItems==2) strcpy(grp_table[g_ent].grpid,cp);
         noofItems++;
         cp = new;

    }

     g_ent++;

     return 1;
 }

/*--------------------------------------------------------------------
 * init_grp_table
 *--------------------------------------------------------------------*/
/*
 *   Initilize the Group internal data structures
 */
void init_grp_table() {

    for (int i=0; i< 200 ; i++ ) {
        grp_table[i].grp_line[0] =  '\0';
        grp_table[i].grp_name[0] =  '\0';
        grp_table[i].passwd[0] =  '\0';
        grp_table[i].grpid[0] = '\0';
        for (int j = 0; j < 100; j++) grp_table[i].grp_user_list[j][0] = '\0';
        grp_table[i].error = 0;
    }

}

/*--------------------------------------------------------------------
 * print_grp_table
 *--------------------------------------------------------------------*/
/*
 *   Print the Group table for debug purpose
 */
void print_grp_table() {

    for (int i=0; i< g_ent ; i++ ) {
        printf("At line no %d \n",i+1);
        printf("\t Group Line = %s",grp_table[i].grp_line);
        printf("\t Group Name = %s \n",grp_table[i].grp_name);
        printf("\t Password  = %s \n",grp_table[i].passwd);
        printf("\t Group Id = %s \n",grp_table[i].grpid);
        printf("\t Group User_list =  ");
        for (int j = 0; j < 100; j++) {
             if (grp_table[i].grp_user_list[j][0]!= '\0') {
                printf("%s \t",grp_table[i].grp_user_list[j]);
             }
        }
        printf("\n");
        printf("\t Error = %d \n", grp_table[i].error);
    }

}

/*--------------------------------------------------------------------
 * print_grp_table_with_errors
 *--------------------------------------------------------------------*/
/*
 *   Print lines from the Group file that has errors
 */
void print_grp_table_with_errors() {

    for (int i=0; i< g_ent ; i++ ) {
        if (grp_table[i].error) {
            printf("Missing entries at line no %d \n",i+1);
            printf("\t Group Line = %s",grp_table[i].grp_line);
            printf("\n");
        }
    }

}

/*--------------------------------------------------------------------
 * check_dup_in_grp_table
 *--------------------------------------------------------------------*/
/*
 *   Checks for duplicate entries in the Group file content
 */
void check_dup_in_grp_table() {

    for (int i=0; i< g_ent ; i++ ) {
        for (int j=0; j < i; j++) {
            if ( !grp_table[i].error) {
                if (strcmp(grp_table[i].grp_name ,grp_table[j].grp_name) ==0) {
                    printf("\t Dulicate entry exits for group \'%s\' at line %d and %d \n", grp_table[i].grp_name, i+1, j+1);
                    printf("\t Please correct the same and rerun this tool \n");
                }
            }
        }
   }
}


/*--------------------------------------------------------------------
 * check_user_paswd_grp_tables
 *--------------------------------------------------------------------*/
/*
 *   Checks for user consistency in both passwd and group file content
 */
void check_user_paswd_grp_tables() {

    int found, i, j ;

    for (i=0; i< p_ent ; i++ ) {
        found = 0;
        if ((!strcmp(paswd_table[i].user_name,"daemon")) || (!strcmp(paswd_table[i].user_name,"daemon,,,"))) continue;
        for (j=0; j < g_ent ; j++) {
            if (!strcmp(paswd_table[i].grpid ,grp_table[j].grpid)) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\t User group for user \'%s\' is not consistent in the Groups file \n", paswd_table[i].user_name);
        }
   }
}


