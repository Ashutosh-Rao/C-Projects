#include "def.h"

/*--------------------------------------------------------------------
 * read_shadwfile
 *--------------------------------------------------------------------*/
/*
 *      Reads the Shadow file line by line into Internal data structures
 */
void read_shadwfile(FILE *fp) {
    char oneline[120];
    char *line;

    while (line =fgets(oneline, 100, fp ) ) { 
        fill_shadw_table(oneline);
    }
}

/*--------------------------------------------------------------------
 * fill_shadw_table
 *--------------------------------------------------------------------*/
/*
 *      Fill the shadow internal data structures
 */
int fill_shadw_table(char *oneline) {

   char *cp = oneline;
   int noofItems = 0;
   char *substr, *new;
   char org_lin[100]; 

   strcpy(shadw_table[s_ent].shadw_line,oneline);
    while (*cp != '\0') {
        char *substr = strchr(cp,':');
        if (substr == 0)  {
            if (noofItems < 7) {
                shadw_table[s_ent].error = 1;
                s_ent ++;
                return 0;
            }
            strcpy(shadw_table[s_ent].expire,cp);
            shadw_table[s_ent].error = 0;
            break;
         }
         new=substr+1;
         *substr = '\0';
         if(noofItems==0) strcpy(shadw_table[s_ent].user_name,cp);
         if(noofItems==1) strcpy(shadw_table[s_ent].passwd,cp);
         if(noofItems==2) strcpy(shadw_table[s_ent].last_change,cp);
         if(noofItems==3) strcpy(shadw_table[s_ent].min,cp);
         if(noofItems==3) strcpy(shadw_table[s_ent].max,cp);
         if(noofItems==4) strcpy(shadw_table[s_ent].warn,cp);
         if(noofItems==5) strcpy(shadw_table[s_ent].inactive,cp);
         if ((noofItems >=0) && (noofItems <=5)) {
                 if (!strcmp(cp,"")) shadw_table[s_ent].error = 0;
         }
         noofItems++;
         cp = new;

     }
     s_ent++;

     return 1;
 }

/*--------------------------------------------------------------------
 * init_shadw_table
 *--------------------------------------------------------------------*/
/*
 *      Initilize the shadow table data structure
 */
void init_shadw_table() {

    for (int i=0; i< 200 ; i++ ) {
        shadw_table[i].user_name[0] =  '\0';
        shadw_table[i].passwd[0] =  '\0';
        shadw_table[i].last_change[0]=  '\0';
        shadw_table[i].min[0] = '\0';
        shadw_table[i].max[0] = '\0';
        shadw_table[i].warn[0] = '\0';
        shadw_table[i].inactive[0] = '\0';
        shadw_table[i].expire[0] =  '\0';
        shadw_table[i].error = 0;

    }

}

/*--------------------------------------------------------------------
 * print_shadw_table
 *--------------------------------------------------------------------*/
/*
 *      Print the shadow table data structure for debug purpse
 */
void print_shadw_table() {

    for (int i=0; i< s_ent ; i++ ) {
        printf("At line no %d \n",i+1);
        printf("\t Shadow Line = %s",shadw_table[i].shadw_line);
        printf("\t User Name = %s \n",shadw_table[i].user_name);
        printf("\t Password  = %s \n",shadw_table[i].passwd);
        printf("\t Last change = %s \n",shadw_table[i].last_change);
        printf("\t Min = %s \n",shadw_table[i].min);
        printf("\t Max = %s \n",shadw_table[i].max);
        printf("\t Warn = %s \n",shadw_table[i].warn);
        printf("\t Inactive = %s \n",shadw_table[i].inactive);
        printf("\t Expire = %s \n",shadw_table[i].expire);
        printf("\t Error = %d \n", shadw_table[i].error);
    }

}

/*--------------------------------------------------------------------
 * print_shadw_table_with_errors
 *--------------------------------------------------------------------*/
/*
 *      Print lines from the shadow file that has errors
 */
void print_shadw_table_with_errors() {

    for (int i=0; i< s_ent ; i++ ) {
        if (shadw_table[i].error) {
            printf("Missing entries at line no %d \n",i+1);
            printf("\t Shadow Line = %s",shadw_table[i].shadw_line);
            printf("\n");
        }
    }

}

/*--------------------------------------------------------------------
 * check_dup_in_shadw_table
 *--------------------------------------------------------------------*/
/*
 *      Checks for duplicate entries in the shadow file content
 */
void check_dup_in_shadw_table() {

    for (int i=0; i< s_ent ; i++ ) {
        for (int j=0; j < i; j++) {
            if ( !shadw_table[i].error) {
                if (strcmp(shadw_table[i].user_name ,shadw_table[j].user_name) ==0) {
                    printf("\t Dulicate entry exits for user \'%s\' at line %d and %d \n", shadw_table[i].user_name, i+1, j+1);
                    printf("\t Please correct the same and rerun this tool \n");
                }
            }
        }
   }
}

/*--------------------------------------------------------------------
 * check_user_passwd_shadw_tables
 *--------------------------------------------------------------------*/
/*
 *      Checks for user consistency in both passwd and shadow file content
 */
void check_user_passwd_shadw_tables() {

    int found, i, j ;

    printf("\nChecking user entries in Passwd file ...\n");
    for (i=0; i< p_ent ; i++ ) {
        found = 0;
        if ((!strcmp(paswd_table[i].user_name,"daemon")) || (!strcmp(paswd_table[i].user_name,"daemon,,,"))) continue;
        for (j=0; j <= s_ent; j++) {
                if (!strcmp(paswd_table[i].user_name ,shadw_table[j].user_name)) {
                    found = 1;
                }
        }
        if (!found) {
            printf("\t User entry in Password file for user \'%s\' is not consistent with Shadow file \n", paswd_table[i].user_name);
        }
    }

    printf("\nChecking user entries in Shadow file ...\n");
    for (i=0; i< s_ent ; i++ ) {
        found = 0;
        if ((!strcmp(shadw_table[i].user_name,"daemon")) || (!strcmp(shadw_table[i].user_name,"daemon,,,"))) continue;
        for (j=0; j <= p_ent; j++) {
                if (!strcmp(shadw_table[i].user_name,paswd_table[j].user_name)) {
                    found = 1;
                }
        }
        if (!found) {
            printf("\t User entry in shadow file user \'%s\' is not consistent with Password file \n", shadw_table[i].user_name);
        }
   }
}
