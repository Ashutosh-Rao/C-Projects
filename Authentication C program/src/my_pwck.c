#include "def.h"

void display_file_error(char *fileName) {

    printf("Can't open file %s \n", fileName);
    exit(1); 
}

int  main(int argc, char *argv[]) {

     int usage_error = 0;     
     p_ent = s_ent = g_ent =  0;

     /* Check if the user supplied the password and shadow files */
     /* If not use the system files from /etc/passwd and /etc/shadow */

     if (argc > 3) {
         printf("Error - Usage: my_pwck [passwd [ shadow ]] \n");
         exit(1);
     }
     if (argc == 3) {   
           if ((shwd_fp = fopen(argv[2], "r")) == NULL ) display_file_error(argv[2]);
           if ((paswd_fp = fopen(argv[1], "r")) == NULL ) display_file_error(argv[1]); 
     }
     if (argc == 2) {
           if ((paswd_fp = fopen(argv[1], "r")) == NULL ) display_file_error(argv[1]); 
           if ((shwd_fp = fopen("shadw", "r")) == NULL ) display_file_error("shadw"); 
     }
     if (argc == 1) {
           if ((shwd_fp = fopen("shadw", "r")) == NULL ) display_file_error("shadw"); 
           if ((paswd_fp = fopen("passwd", "r")) == NULL )  display_file_error("passwd"); 
     }

     if ((grp_fp = fopen("group", "r")) == NULL )   display_file_error("group");


     /* Initilize the Internal Data structures */

     init_paswd_table();
     init_grp_table();
     init_shadw_table();

     /* Read the files into Internal Data structures */

     read_paswdfile(paswd_fp);
     /* print_paswd_table(); */

     read_grpfile(grp_fp);
     /* print_grp_table(); */

     read_shadwfile(shwd_fp);
     /* print_shadw_table(); */


     /* Verify integrity of password files */

     printf("Checking for duplicate entires in passwd file ....\n");
     check_dup_in_paswd_table();
     printf("Duplicate check done\n\n");

     printf("Checking for consistency in Password file entries  ....\n");
     check_home_dir_for_user();
     print_paswd_table_with_errors();
     printf("Consistency check done\n\n");
         
     printf("Checking for duplicate entires in Group file ....\n");
     check_dup_in_grp_table();
     printf("Duplicate check done\n\n");

     printf("Checking for consistency in Group File entries ....\n");
     print_grp_table_with_errors();
     printf("Consistency check done\n\n");

     printf("Checking for duplicate entires in Shadw file ....\n");
     check_dup_in_shadw_table();
     printf("Duplicate check done\n\n");

     printf("Checking for consistency in Shadow file entries ....\n");
     print_shadw_table_with_errors();
     printf("Consistency check done\n\n");

     /* Check the user group identifier   */

     printf("Checking for user group info ....\n");
     check_user_paswd_grp_tables() ;
     printf("Consistency check done\n\n");

     /* every passwd entry has a matching shadow entry i and viseversa */
     printf("Checking for user consistency in passwd and shadow files ....\n");
     check_user_passwd_shadw_tables();
     printf("Consistency check done\n\n");

     fclose (paswd_fp);
     fclose (shwd_fp);
     fclose (grp_fp);

} 
