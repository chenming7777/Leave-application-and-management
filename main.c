// TP068804 Teh Chen Ming C programming leave application system
// Strip fucntion is used to clear all leading and trailing whitespace.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "calendar.h"

// This structure is for the add staff.
struct staff
{   
    char username[50];
    char name[50];
    char* calendar;
    char phone_number[20];
    char email[50];
    char password[50];
    char confirm_password[50];
    char department[10];
    char annual_leave[5];
    char compassionate_leave[5];
    char emergency_leave[5];
    char maternity_leave[5];
    char medical_leave[5];
    char staffID[10];
    char gender[10];
};
// This is the calendar function for user to enter date.
char* calendar();

// For Admin
int admin_login();
int admin_UI();
int admin_function();
int new_staff();
int upt_leave_bal();
int search_staff_leave();
int monthly_report();
int show_staff();
// For Staff
char *staff_login();
int staff_UI();
int staff_function();
char check_info(char *staffID);
char apply_leave(char *staffID);
char cancel_leave(char *staffID);
char leave_status(char *staffID);
char leave_info(char *staffID);
// For Approver
int approver_login();
int approver_function();
int approver_UI();
int approval_leave();
int check_leave_date();
int check_all_leave();
// For main
int main();
int main_UI();
int main_function();

// admin section
// for admin to login
int admin_login()
{
    // this attempt is to calculate the how many time user has tried to enter the account.
    int attempt = 0;
    while(attempt < 3)
    {
        FILE *fptr = fopen("admin_info.txt","r");
        if (fptr == NULL)
        {
            printf("File cannot be open\n");
            fclose(fptr);
            main_function();
        }
        // this is to ensure the file is not empty
        int size = 0;
        if(fptr!=NULL)
        {
            fseek (fptr, 0, SEEK_END);

            size = ftell (fptr);
            rewind(fptr);
        }
        if (size==0)
        {
            printf("There is no information in this file\n");
            fclose(fptr);
            main_function();
        }
        // real function code start here.
        char username[100];
        char password[100];
        char line[50];
        char *token;
        char *file_password;
        char *file_username;
        int flag = 0;
        // prompt user to enter username and password and check whether the password is correct.
        printf("Please enter your username:");
        fgets(username, sizeof(username), stdin);
        strip(username);
        printf("Please enter your password:");
        fgets(password, sizeof(password), stdin);
        strip(password);
        while(!feof(fptr))
        {
            fgets(line,sizeof(line),fptr);
            token = strtok(line,"|");
            file_username = token;
            token = strtok(NULL,"|");
            file_password = token;
            if(strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            fclose(fptr);
            break;
        }
        else
        {
            fclose(fptr);
            attempt++;
            // This will detect whether the attempt has exceed 3
            if(attempt == 3)
            {
                fclose(fptr);
                main_function();
            }
            printf("This is your %d attempt\n",attempt);
            continue;
        }
    }
}
// Show admin selection after successfully logged in
int admin_UI()
{   
    int choice;
    char temp[10];
    // The admin UI
    printf("Please enter your selection\n");
    while(1)
    {
        printf("==============================\n");
        printf("1.Add new staff\n");
        printf("2.Update leave balance\n");
        printf("3.Search staff's leave and personal information\n");
        printf("4.Generate monthly report of leave statistics for each department\n");
        printf("5.Check all available staffID\n");
        printf("6.Logout\n");
        printf("Your choice:");
        gets(temp);
        if (strlen(temp) != 1)
        {
            printf("Please only enter one digit\n");
            continue;
        }
        choice = atoi(temp);
        if(1 <= choice && choice <= 6)
        {
            break;
        }
        else
        {
            printf("Please enter a valid selection\n");
            continue;
        }
    }
        return choice;
}
// This will be the back-end function of the admin fucntion.
int admin_function()
{
    int choice;
    admin_login();
    while(1)
    {
        choice = admin_UI();
        if (choice == 1)
        {
            new_staff();
        }
        else if (choice == 2)
        {
            upt_leave_bal();
        }
        else if (choice == 3)
        {
            search_staff_leave();
        }
        else if (choice == 4)
        {
            monthly_report();
        }
        else if (choice == 5)
        {
            show_staff();
        }
        else
        {
            main_function();
        }
    }
}
// This is for admin to add new staff
int new_staff()
{   
    char temp[100];
    char line[100];
    char line_token[100];
    char *token;
    // This will open a file in append mode
    FILE *fp = fopen("staff_info.txt","a");
    // This wil check whether this file can be open.
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    struct staff S1;
    while(1)
    {   
        int flag5 = 0, flag6 = 0;
        rewind(fp);
        printf("Please enter create staff ID('S' + six nums):");
        fgets(temp, sizeof(temp), stdin);
        strip(temp);
        // check whether the staffID is exist.
        if(check_user_id(temp) == 1)
        {
            printf("The staffID is already exist, please enter the again\n");
            continue;
        }
        // check whether the staffID starts with 'S'
        if(temp[0] != 'S')
        {
            printf("Please enter an actual staff ID\n");
            continue;
        }
        // check whether length of StaffID only with 7
        if (strlen(temp) != 7)
        {
            printf("Please only enter a staff with 6 digits\n");
            continue;
        }
        // check is all staffID is digit after the 'S'
        for(int i = 1; i <= strlen(temp) - 2; i++)
        {
            if(check_digit(temp[i]) == 0)
            {
                flag5 = 1;
                break;
            }
        }
        if (flag5 == 1)
        {
            printf("Please enter an actual staff ID\n");
            continue;
        }
        else
        {
            strcpy(S1.staffID,temp);
            break;
        }
    }
    // this will let admin to enter the name
    while(1)
    {
        int flag1 = 1;
        printf("Please enter the staff's full name:");
        fgets(temp, sizeof(temp), stdin);
        strip(temp);
        for(int i = 0; i <= strlen(temp) - 1; ++i)
            {
                if(check_alphabet(temp[i]) == 0 && check_space(temp[i]) == 0 ) 
                {
                    printf("Please enter only space or alphabet.\n");
                    flag1 = 0;
                    break;
                }
            }
        if (flag1 == 0)
        {
            continue;
        }
        else
        {
            strcpy(S1.name,temp);
            break;
        }
    }   
    // this will let admin enter the staff starting date
    printf("Please enter the staff's start working date\n");
    S1.calendar = calendar();
    // this will let admin enter the staff contact number
    while(1)
    {   
        int flag2 = 1;
        printf("Please enter staff contact number:");
        fgets(temp, sizeof(temp), stdin);
        strip(temp);
        if (!(strlen(temp) == 10 || strlen(temp) == 11))
        {
            printf("Please only enter 10 or 11 digits\n");
            continue;
        }
        for (int i = 0; i <= strlen(temp) - 1; i++)
        {
            if(check_digit(temp[i]) == 0) // is digit then return 1
            {
                printf("Please enter a actual phone number\n");
                flag2 = 0;
                break;
            }
        }
        if (flag2 == 0)
        {
            continue;
        }
        else
        {
            strcpy(S1.phone_number,temp);
            break;
        }
    }
    // This will let staff enter email
    while(1)
    {
        int flag3 = 0, check_symbol = 0;
        printf("Please enter staff's email:");
        fgets(temp, sizeof(temp), stdin);
        strip(temp);
        for(int i = 0; i <= strlen(temp) - 1; i++)
        {
            if (temp[i] == '|')
            {
                check_symbol = 1;
            }
            if (temp[i] == '@') 
            {
                flag3 = 1;
            }
        }
        if (check_symbol == 1)
        {
            printf("Please do not include '|' in your email\n");
            continue;
        }
        if(flag3 == 1)
        {
            strcpy(S1.email,temp);
            break;
        }
        else
        {
            printf("Please enter a proper email\n");
            continue;
        }
    }
    // This will check the user enter password. User should enter capital letter,
    // lower letter, special character, digit in the password.
    while(1)
    {
        int cap_letter = 0, lower_letter = 0, digit = 0,special_char = 0,flag4 = 0,final = 0;
        printf("Please enter staff's password(password must contain upper letter, lower letter special character and digit):");
        fgets(temp, sizeof(temp),stdin);
        strip(temp);
        for (int i = 0; i <= strlen(temp) - 1; i++)
        {
            if (temp[i] == '|')
            {
                flag4  = 1;
                break;
            }
            if(isblank(temp[i]))
            {
                flag4 = 1;
                break;
            }
            if(check_alphabet(temp[i]) == 2)
            {
                cap_letter = 1;
            }
            if(check_alphabet(temp[i]) == 1)
            {
                lower_letter = 1;
            }
            if(check_digit(temp[i]) == 1)
            {
                digit = 1;
            }
            if(check_digit(temp[i]) == 0 && check_alphabet(temp[i]) == 0)
            {
                special_char = 1;
            }
        }
        if (flag4 == 1)
        {
            printf("Do not enter space or '|' while creating password\n");
            continue;
        }
        if (cap_letter == 1 && lower_letter == 1 && digit == 1 && special_char == 1)
        {
            printf("Please confirm the password again:");
            fgets(S1.confirm_password, sizeof(S1.confirm_password), stdin);
            strip(S1.confirm_password);
            if(strcmp(temp,S1.confirm_password) == 0)
            {
                strcpy(S1.password, temp);
                break;
            }
        } 
        else
        {
            printf("Please make sure your password contain upper letter, lower letter special character and digit\n");
            continue;
        }
    }
    // check gender 
    while(1)
    {
        printf("Please enter staff's gender(Enter:male or female):");
        fgets(temp,sizeof(temp),stdin);
        strip(temp);
        if(strcmp(temp,"male") == 0 || strcmp(temp,"female") == 0)
        {
            strcpy(S1.gender,temp);
            break;
        }
        else
        {
            printf("Please enter an actual gender\n");
            continue;
        }
    }
    // this will check the user department and assign leave for them
    while(1)
    {   
        int choice;
        char ans[5];
        char acd[] = "Academic";
        char adm[] = "Admin";
        char mngt[] = "Management";
        char tech[] = "Technical";
        printf("Please select the department for the new staff\n");
        printf("******************************************************\n");
        printf("1)%s department-\n",acd);
        printf("This department will provide ");
        printf("7 days of annual leave, ");
        printf("7 days of compassionate leave\n");
        printf("3 days of emergency leave, ");
        printf("0 days of maternity leave, ");
        printf("14 days of medical leave.\n\n");
        printf("2)%s department-\n",adm);
        printf("This department will provide ");
        printf("6 days of annual leave, ");
        printf("5 days of compassionate leave\n");
        printf("3 days of emergency leave, ");
        printf("0 days of maternity leave, ");
        printf("14 days of medical leave.\n\n");
        printf("3)%s department-\n",mngt);
        printf("This department will provide ");
        printf("5 days of annual leave, ");
        printf("5 days of compassionate leave\n");
        printf("3 days of emergency leave, ");
        printf("0 days of maternity leave, ");
        printf("14 days of medical leave.\n\n");
        printf("4)%s department-\n",tech);
        printf("This department will provide ");
        printf("3 days of annual leave, ");
        printf("3 days of compassionate leave\n");
        printf("3 days of emergency leave, ");
        printf("0 days of maternity leave, ");
        printf("14 days of medical leave.\n");
        printf("Your choice:");
        fgets(temp,sizeof(temp),stdin);
        strip(temp);
        if (strlen(temp) != 1)
        {
            printf("Please only enter one digit\n");
            continue;
        }
        choice = atoi(temp);
        if (!(1 <= choice && choice <= 4))
        {
            printf("Please enter a valid selection\n");
            continue;
        }
        if (choice == 1)
        {
            printf("Is (%s) your selection?\n",acd);
            printf("Answer 'y' to confirm or any input to select again:");
            fgets(ans,sizeof(ans),stdin);
            strip(ans);
            if (ans[0] == 'y')
            {
                strcpy(S1.department,acd);
                strcpy(S1.annual_leave,"7");
                strcpy(S1.compassionate_leave,"7");
                strcpy(S1.emergency_leave,"3");
                strcpy(S1.maternity_leave,"0");
                strcpy(S1.medical_leave,"14");
                break;
            }
            else
            {
                printf("You may select again\n");
                continue;
            }
        }
        else if(choice == 2)
        {
            printf("Is (%s) your selection?\n",adm);
            printf("Answer 'y' to confirm or any input to select again:");
            fgets(ans,sizeof(ans),stdin);
            if (ans[0] == 'y')
            {
                strcpy(S1.department,adm);
                strcpy(S1.annual_leave,"6");
                strcpy(S1.compassionate_leave,"5");
                strcpy(S1.emergency_leave,"3");
                strcpy(S1.maternity_leave,"0");
                strcpy(S1.medical_leave,"14");
                break;
            }
            else
            {
                printf("You may select again\n");
            }
        }
        else if(choice == 3)
        {
            printf("Is (%s) your selection?\n",mngt);
            printf("Answer 'y' to confirm or any input to select again:");
            fgets(ans,sizeof(ans),stdin);
            if (ans[0] == 'y')
            {
                strcpy(S1.department,mngt);
                strcpy(S1.annual_leave,"5");
                strcpy(S1.compassionate_leave,"5");
                strcpy(S1.emergency_leave,"3");
                strcpy(S1.maternity_leave,"0");
                strcpy(S1.medical_leave,"14");
                break;
            }
            else
            {
                printf("You may select again\n");
            }
        }
        else
        {
            printf("Is (%s) your selection?\n",tech);
            printf("Answer 'y' to confirm or any input to select again:");
            fgets(ans,sizeof(ans),stdin);
            if (ans[0] == 'y')
            {
                strcpy(S1.department,tech);
                strcpy(S1.annual_leave,"3");
                strcpy(S1.compassionate_leave,"3");
                strcpy(S1.emergency_leave,"3");
                strcpy(S1.maternity_leave,"0");
                strcpy(S1.medical_leave,"14");
                break;
            }
            else
            {
                printf("You may select again\n");
            }
        }   
    }
    // This will show the staff detail for final confirmation
    while(1)
    {   
        char ans[5];
        printf("This is your staff information please check\n");
        printf("=====================================================================\n");
        printf("StaffID:%s\n",S1.staffID);
        printf("Password:%s\n",S1.password);
        printf("Gender:%s\n",S1.gender);
        printf("Name:%s\n",S1.name);
        printf("Starting date:%s\n",S1.calendar);
        printf("Phone number:%s\n",S1.phone_number);
        printf("Email:%s\n",S1.email);
        printf("Department:%s\n",S1.department);
        printf("Annual Leave:%s\n",S1.annual_leave);
        printf("Compassionate Leave:%s\n",S1.compassionate_leave);
        printf("Emergency Leave:%s\n",S1.emergency_leave);
        printf("Maternity Leave:%s\n",S1.maternity_leave);
        printf("Medical Leave:%s\n",S1.medical_leave);
        printf("Do you want to save these info?\n");
        printf("Answer 'y' to confirm or any input to go back to admin main page:");
        fgets(ans,sizeof(ans),stdin);
        if (ans[0] == 'y')
        {
            int size = 0;
            if(fp!=NULL)
            {
                fseek (fp, 0, SEEK_END);

                size = ftell (fp);
                rewind(fp);
            }
            if (size != 0)
            {
                fputs("\n",fp);
            }
            fprintf(fp, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s",S1.staffID,S1.password,S1.gender,S1.name,
            S1.calendar,S1.phone_number,S1.email,S1.department,S1.annual_leave,S1.compassionate_leave,
            S1.emergency_leave,S1.maternity_leave,S1.medical_leave);
            fclose(fp);
            break;
        }
        else
        {
            fclose(fp);
            break;
        }

    }


}
// This is for admin to update staff leave balance
int upt_leave_bal()
{
    char staffID[100];
    char line[100];
    char line_token[100];
    char target_line[100];
    char new_change[100];
    char *token;
    char *annual;
    char *compassionate;
    char *emergency;
    char *maternity;
    char *medical;
    char *gender;
    char ans[5];
    int choice;
    char lastline[100];
    char temp[100];
    int flag1 = 1;
    // This will check all the file
    FILE *fsource = fopen("staff_info.txt","r");
    FILE *fdest = fopen("temp.txt","w");
    if(fsource == NULL || fdest == NULL)
    {
        printf("File cannot be open.\n");
        fclose(fsource);
        fclose(fdest);
        admin_function();
    }
    int size = 0;
    if(fsource!=NULL)
    {
        fseek (fsource, 0, SEEK_END);

        size = ftell (fsource);
        rewind(fsource);
    }
    if (size==0)
    {
        printf("There is no staff saved in this file\n");
        fclose(fsource);
        fclose(fdest);
        remove("temp.txt");
        admin_function();
    }
    // The main function start on here.
    // This will prompt user to enter the staffID and check is it exist.
    printf("Please enter the StaffID you wanted to update the leave balance:");
    fgets(staffID, sizeof(staffID), stdin);
    strip(staffID);
    while(!feof(fsource))
        {
            fgets(line,sizeof(line),fsource);
            strip(line);
            strcpy(line_token,line);
            token = strtok(line_token,"|");
            if(strcmp(staffID,token) != 0)
            {
                fputs(line,fdest);
                fputs("\n",fdest);
            }
            else
            {
                strcpy(target_line,line);
                flag1 = 0;
            }
        }
    // flag1 is 1 means staffID is not exist
    if(flag1)
    {
        printf("Staff is not exist\n");
        fclose(fsource);
        fclose(fdest);
        remove("temp.txt");
        upt_leave_bal();
    }
    else
    {
        token = strtok(target_line,"|");
        fprintf(fdest,"%s",token);
        token = strtok(NULL,"|");
        fprintf(fdest,"|%s",token);
        token = strtok(NULL,"|");
        fprintf(fdest,"|%s",token);
        gender = token;
        for(int i = 0; i < 5; i++)
        {
            // This is to save the unnecessary user info back the file.
            token = strtok(NULL,"|");
            fprintf(fdest,"|%s",token);
        }
        token = strtok(NULL,"|");
        annual = token;
        token = strtok(NULL,"|");
        compassionate = token;
        token = strtok(NULL,"|");
        emergency = token;
        token = strtok(NULL,"|");
        maternity = token;
        token = strtok(NULL,"|");
        medical = token;
        // This will show all the leave the staff have.
        while(1)
        {
            printf("This is the staff %s leave balance.\n",staffID);
            printf("1.annual leave:%s\n",annual);
            printf("2.compassionate leave:%s\n",compassionate);
            printf("3.emergency leave:%s\n",emergency);
            printf("4.maternity leave:%s\n",maternity);
            printf("5.medical leave:%s\n",medical);
            printf("Please enter your selection:");
            fflush(stdin);
            fgets(temp,sizeof(temp),stdin);
            strip(temp);
            choice = atoi(temp);
            if ( 1 <= choice && choice <= 5)
            {
                break;
            }
            else
            {
                printf("Please enter a valid selection\n");
                continue;
                
            }
        }
        // enter the new date
        while(1)
        {
            int flag2 = 1;
            fflush(stdin);
            printf("Please enter your new day:");
            fgets(new_change, sizeof(new_change), stdin);
            strip(new_change);
            for (int i = 0; new_change[i] != '\0';i++)
            {
                if(check_digit(new_change[i]) == 0)
                {
                    flag2 = 0;
                    break;
                }
            }
            if(flag2 == 0)
            {
                printf("please enter a valid date\n");
                continue;
            }
            else
            {
                break;
            }
        }
        if(choice == 1)
        {
            annual = new_change;
        }
        else if (choice == 2)
        {
            compassionate = new_change;
        }
        else if (choice == 3)
        {
            emergency = new_change;
        }
        else if (choice == 4)
        {
            if (strcmp(gender, "male") == 0)
            {
                printf("Male cannot add maternity leave\n");
            }
            else
            {
                maternity = new_change;
            }
        }
        else if (choice == 5)
        {
            medical = new_change;
        }
        else
        {
            printf("Please enter a valid selection\n");
        }
        // this will save the info back to file.
        fprintf(fdest,"|%s|%s|%s|%s|%s",annual,compassionate,emergency,maternity,medical);
        fclose(fsource);
        fclose(fdest);
        remove("staff_info.txt");
        rename("temp.txt","staff_info.txt");
    }
}
// This will show all the staffID in the "staff_info.txt"
int show_staff()
{
    char line[100];
    char *token;
    char staffID[100];
    // check file availability
    FILE *fptr = fopen("staff_info.txt","r");
    if (fptr == NULL)
    {
        printf("The file cannot be open");
        fclose(fptr);
        main_function();
    }
    int size = 0;
    if(fptr!=NULL)
    {
        fseek (fptr, 0, SEEK_END);

        size = ftell (fptr);
        rewind(fptr);
    }
    if (size==0)
    {
        printf("There is no staff saved in this file\n");
        fclose(fptr);
        main_function();
    }
    rewind(fptr);
    // show all the exist staffID
    printf("This is the available staffID in this company\n");
    while(!feof(fptr))
    {
        fgets(line,sizeof(line),fptr);
        if(strlen(line) == 8)
        {
            break;
        }
        token = strtok(line,"|");
        printf("%s\n",token);
    }
    fclose(fptr);
}
// This will show the staff information based on what admin have entered
int search_staff_leave()
{
    char str[100];
    char str_display[100];
    char *token;
    char staffID[100];
    char confirmation[5];
    // Check all the file
    // This loop will loop until user enough to search the staff information
    while(1)
    {   
        int flag = 0;
        FILE *fptr = fopen("staff_info.txt","r");
        if (fptr == NULL)
        {
            printf("The file cannot be open");
            break;
        }
        int size = 0;
        if(fptr!=NULL)
        {
            fseek (fptr, 0, SEEK_END);

            size = ftell (fptr);
            rewind(fptr);
        }
        if (size==0)
        {
            printf("There is no staff saved in this file\n");
            break;
        }
        // code function start here
        printf("Please enter the staffID you want to search:");
        fgets(staffID,sizeof(staffID),stdin);
        strip(staffID);
        while(!feof(fptr))
        {
            fgets(str,sizeof(str),fptr);
            strip(str);
            strcpy(str_display,str);
            token = strtok(str,"|");
            if(strcmp(staffID,token) == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag)
        {
            printf("StaffID:%s\n",token);
            token = strtok(NULL,"|");
            printf("Password:%s\n",token);
            token = strtok(NULL,"|");
            printf("Gender:%s\n",token);
            token = strtok(NULL,"|");
            printf("Full name:%s\n",token);
            token = strtok(NULL,"|");
            printf("Working start date:%s\n",token);
            token = strtok(NULL,"|");
            printf("Phone number:%s\n",token);
            token = strtok(NULL,"|");
            printf("Email:%s\n",token);
            token = strtok(NULL,"|");
            printf("Department:%s\n",token);
            token = strtok(NULL,"|");
            printf("Annual leave:%s\n",token);
            token = strtok(NULL,"|");
            printf("Compassionate leave:%s\n",token);
            token = strtok(NULL,"|");
            printf("Emergency leave:%s\n",token);
            token = strtok(NULL,"|");
            printf("Maternity leave:%s\n",token);
            token = strtok(NULL,"|");
            printf("Medical leave:%s\n",token);
        }
        else
        {
            printf("The staffID is not exist\n");
        }
        fclose(fptr);
        // check whether user want to search again.
        printf("Do you want to enter again?\n");
        printf("Enter 'y' to search again or other input to exit:");
        fgets(confirmation,sizeof(confirmation),stdin);
        strip(confirmation);
        if(strcmp(confirmation,"y") != 0)
        {
            break;
        }
    }
}
// This will generate a monthly report of leave statistic from each department.
int monthly_report()
{
    // Check file availability
    FILE *fptr = fopen("leave_detail.txt","r");
    FILE *freport = fopen("monthly_report.txt","w");
    FILE *fstaff = fopen("staff_info.txt","r");
    if (fptr == NULL || freport == NULL)
    {
        printf("File cannot open\n");
        fclose(freport);
        fclose(fstaff);
        fclose(fptr);
        admin_function();
    }
    int size = 0;
    if(fptr!=NULL)
    {
        fseek (fptr, 0, SEEK_END);

        size = ftell (fptr);
        rewind(fptr);
    }
    if (size==0)
    {
        printf("There is no leave on this month\n");
        fclose(freport);
        fclose(fstaff);
        fclose(fptr);
        admin_UI();
    }
    size = 0;
    if(fstaff != NULL)
    {
        fseek (fstaff, 0, SEEK_END);

        size = ftell (fstaff);
        rewind(fstaff);
    }
    if (size==0)
    {
        printf("There is no leave on this month\n");
        fclose(freport);
        fclose(fstaff);
        fclose(fptr);
        admin_UI();
    }
    // code function start on here
    char line[100];
    char line_display[100];
    char *token;
    int month;
    int year;
    char staffID[100];
    char user_year[100];
    char user_month[100];
    char temp[100];
    char file_month[100];
    char file_year[100];
    char check_staffID[100];
    char department[100];
    int acd = 0;
    int admin = 0;
    int tech = 0;
    int mngt = 0;
    // code fucntion start on here, user need to enter year and month to get the monthly report
    while(1)
    {
        printf("Please enter your report year:");
        fgets(temp, sizeof(temp),stdin);
        strip(temp);
        if (strlen(temp) != 4)
        {
            printf("Please only enter 4 number\n");
            continue;
        }
        year = atoi(temp);
        if (1900 <= year && year <= 2023)
        {
            break;
        }
        else
        {
            printf("Please enter a valid year\n");
            continue;
        }
    }
    while(1)
    {
        printf("Please enter your month(1,2,11):");
        fgets(temp,sizeof(temp),stdin);
        strip(temp);
        if (!(strlen(temp) == 1 || strcmp(temp,"10") == 0 || strcmp(temp, "11") == 0 || strcmp(temp, "12") == 0))
        {
            printf("Please enter a valid month\n");
            continue;
        }
        month = atoi(temp);
        if(1 <= month && month <= 12)
        {
            break;
        }
        else
        {
            printf("Please enter a valid month\n");
            continue;
        }
    }
    // changing the int to string.
    sprintf(user_year,"%d",year);
    sprintf(user_month,"%d",month);
    while(!feof(fptr))
    {
        fgets(line,sizeof(line),fptr);
        strip(line);
        // Since the string length of one line is fix so this function can prevent error line crash the program
        if(strlen(line) != 61)
        {
            break;
        }
        strcpy(line_display,line);
        token = strtok(line,"| "); // this is the staffID
        strcpy(staffID,token);
        token = strtok(NULL,"| "); // this is the date
        strcpy(temp,token);
        token = strtok(temp,"/");
        token = strtok(NULL,"/");
        strcpy(file_month, token);
        token = strtok(NULL,"/");
        strcpy(file_year,token);
        // this will check the data which match the user month and year
        if(strcmp(file_month,user_month) == 0 && strcmp(file_year,user_year) == 0)
        {
            rewind(fstaff);
            while(!feof(fstaff))
            {
                fgets(line,sizeof(line),fstaff);
                strip(line);
                if(strlen(line) == 8)
                {
                    break;
                }
                strcpy(line_display,line);
                token = strtok(line,"|");
                strcpy(check_staffID,token);
                if(strcmp(check_staffID,staffID) == 0)
                {
                    for(int i = 0; i < 6; i++)
                    {
                        token = strtok(NULL,"|");
                    }
                    token = strtok(NULL, "|");
                    strcpy(department,token);
                    if(strcmp(department,"Academic") == 0)
                    {
                        acd++;
                    }
                    else if(strcmp(department,"Admin") == 0)
                    {
                        admin++;
                    }
                    else if(strcmp(department,"Management") == 0)
                    {
                        mngt++;
                    }
                    else if(strcmp(department,"Technical") == 0)
                    {
                        tech++;
                    }
                }
            }
        }
    }
    // this will design the file and how the data is saved.
    fprintf(freport,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    fprintf(freport,"x     (%2s/%4s) monthly leave report for each department    x\n",user_month,user_year);
    fprintf(freport,"=============================================================\n");
    fprintf(freport,"|Department     |                         |Leave numbers    |\n");
    fprintf(freport,"=============================================================\n");
    fprintf(freport,"|Academic       |                         |%-17d|\n",acd);
    fprintf(freport,"|Admin          |                         |%-17d|\n",admin);
    fprintf(freport,"|Management     |                         |%-17d|\n",mngt);
    fprintf(freport,"|Technical      |                         |%-17d|\n",tech);
    fprintf(freport,"=============================================================\n");
    printf("Generating the monthly report...\n");
    Sleep(500);
    printf("Done!\n");
    fclose(fstaff);
    fclose(fptr);
    fclose(freport);
}

// staff section
// This will let staff to login
char *staff_login()
{
    char *value = (char*)malloc(50);
    int attempt = 0;
    // This will check the attempt has been used by the staff
    while(attempt < 3)
    {
        // Check file
        FILE *fptr = fopen("staff_info.txt","r");
        if (fptr == NULL)
        {
            printf("File cannot be open\n");
            fclose(fptr);
            main_function();
        }
        int size = 0;
        if(fptr!=NULL)
        {
            fseek (fptr, 0, SEEK_END);

            size = ftell (fptr);
            rewind(fptr);
        }
        if (size==0)
        {
            printf("There is no staff saved in this file\n");
            fclose(fptr);
            main_function();
        }
        char username[100];
        char password[100];
        char line[50];
        char *token;
        char *file_password;
        char *file_username;
        int flag = 0;
        printf("Please enter your username:");
        fgets(username, sizeof(username), stdin);
        strip(username);
        printf("Please enter your password:");
        fgets(password, sizeof(password), stdin);
        strip(password);
        while(!feof(fptr))
        {
            fgets(line,sizeof(line),fptr);
            token = strtok(line,"|");
            file_username = token;
            token = strtok(NULL,"|");
            file_password = token;
            // Check the user name and password is matched with the file
            if(strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            fclose(fptr);
            strcpy(value,username);
            return value;
        }
        else
        {
            fclose(fptr);
            attempt++;
            if(attempt == 3)
            {
                main_function();
            }
            printf("This is your %d attempt\n",attempt);
        }
    }
}
//  This will show the main page of the staff and let them to choose
int staff_UI()
{
    int choice;
    char temp[10];
    printf("Please choose your selection\n");
    // this is the main UI for staff
    while(1)
    {
        printf("==============================\n");
        printf("1. Apply leave\n");
        printf("2. Cancel leave\n");
        printf("3. Check today leave status\n");
        printf("4. Check the total leave you have applied\n");
        printf("5. Check your personal information\n");
        printf("6. Logout\n");
        printf("Your choice:");
        gets(temp);
        if (strlen(temp) != 1)
        {
            printf("Please only enter a digit\n");
            continue;
        }
        choice = atoi(temp);
        if(1 <= choice && choice <= 6)
        {
            break;
        }
        else;
        {
            printf("Please enter a valid selection\n");
            continue;
        }
    }
    return choice;
}
// This will be the back-end function of the staff function.
int staff_function()
{
    int choice;
    char *staffID = staff_login();
    while(1)
    {
        choice = staff_UI();
        if(choice == 1)
        {
            apply_leave(staffID);
        }
        else if(choice == 2)
        {
            cancel_leave(staffID);
        }
        else if(choice == 3)
        {
            leave_status(staffID);
        }
        else if(choice == 4)
        {
            leave_info(staffID);
        }   
        else if (choice == 5)
        {
            check_info(staffID);
        }
        else
        {
            main_function();
        }
    }
}
// This is for staff to apply leave
char apply_leave(char *staffID)
{
    // to open and check all file
    FILE *fptr = fopen("leave_detail.txt","r");
    FILE *fread = fopen("staff_info.txt","r");
    FILE *fwrite = fopen("temp.txt","w");
    if (fptr == NULL || fread == NULL)
    {
        printf("File cannot be open\n");
    }
    else
    {
        char *leave;
        char status[] = "pending";
        char confirmation[5];
        char line[100];
        char line_target[100];
        char line_save[100];
        char *token;
        char *annual;
        char *compassionate;
        char *emergency;
        char *maternity;
        char *medical;
        char selection[5];
        int new_change;
        char leave_type[100];
        // main code start on here
        while(!feof(fread))
        {
            fgets(line,sizeof(line),fread);
            strip(line);
            strcpy(line_save,line);
            token = strtok(line,"|");
            if (strcmp(token,staffID) == 0)
            {
                strcpy(line_target,line_save);
            }
            else
            {
                fprintf(fwrite,"%s\n",line_save);
            }
        }
        token = strtok(line_target,"|");
        fprintf(fwrite,"%s",token);
        for(int i = 0; i < 7; i++)
        {
            token = strtok(NULL,"|");
            fprintf(fwrite,"|%s",token);
        }
        token = strtok(NULL,"|");
        annual = token;
        token = strtok(NULL,"|");
        compassionate = token;
        token = strtok(NULL,"|");
        emergency = token;
        token = strtok(NULL,"|");
        maternity = token;
        token = strtok(NULL,"|");
        medical = token;
        char *calendar_check;
        char *staffID_check;
        // this will check whether the date user apply is applied before whether it is rejected
        // approved or pending
        while(1)
        {
            int flag = 0;
            printf("Please enter the date you want to apply a leave\n");
            leave = calendar();
            rewind(fptr);
            while(!feof(fptr))
            {
                fgets(line,sizeof(line),fptr);
                strip(line);
                if (strlen(line) != 61)
                {
                    break;
                }
                token = strtok(line,"| ");
                staffID_check = token;
                token = strtok(NULL,"| ");
                calendar_check = token;
                if(strcmp(staffID_check,staffID) == 0 && strcmp(calendar_check,leave) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag)
            {
                printf("You have applied a same leave date before\n");
                continue;
            }
            // this will prompt user to choose which type of leave he want to enter
            printf("This is your leave balance\n");
            printf("1)Annual:%s\n",annual);
            printf("2)Compassionate:%s\n",compassionate);
            printf("3)Emergency:%s\n",emergency);
            printf("4)Maternity:%s\n",maternity);
            printf("5)Medical:%s\n",medical);
            printf("What kind of leave you are going to apply(enter 1 to 5):");
            fgets(selection,sizeof(selection),stdin);
            strip(selection);
            printf("Your leave we be on %s, you confirm?",leave);
            printf("(enter y to enter or other input to apply again):");
            fgets(confirmation,sizeof(confirmation), stdin);
            strip(confirmation);
            if (strcmp(confirmation,"y") == 0)
            {
                // this will auto minus 1 from the leave the staff have applied
                if (strcmp(selection,"1") == 0)
                {
                    new_change = atoi(annual) - 1;
                    if(new_change > 0)
                    {
                        strcpy(leave_type, "annual");
                        sprintf(annual,"%d",new_change);
                    }
                    else
                    {
                        printf("You cannot apply this leave\n");
                        continue;
                    }
                }
                else if (strcmp(selection, "2") == 0)
                {
                    new_change = atoi(compassionate) - 1;
                    if(new_change > 0)
                    {
                        strcpy(leave_type, "compassionate");
                        sprintf(compassionate,"%d",new_change);
                    }
                    else
                    {
                        printf("You cannot apply this leave\n");
                        continue;
                    }
                }
                else if (strcmp(selection, "3") == 0)
                {
                    new_change = atoi(emergency) - 1;
                    if(new_change > 0)
                    {
                        strcpy(leave_type, "emergency");
                        sprintf(emergency,"%d",new_change);
                    }
                    else
                    {
                        printf("You cannot apply this leave\n");
                        continue;
                    }
                }
                else if (strcmp(selection,"4") == 0)
                {
                    new_change = atoi(maternity) - 1;
                    if(new_change > 0)
                    {
                        strcpy(leave_type, "maternity");
                        sprintf(maternity,"%d",new_change);
                    }
                    else
                    {
                        printf("You cannot apply this leave\n");
                        continue;
                    }
                }
                else if (strcmp(selection, "5") == 0)
                {
                    new_change = atoi(medical) - 1;
                    if(new_change > 0)
                    {
                        strcpy(leave_type, "medical");
                        sprintf(medical,"%d",new_change);
                    }
                    else
                    {
                        printf("You cannot apply this leave\n");
                        continue;
                    }
                }
                else
                {
                    printf("Please enter a valid selection");
                    continue;
                }
                break;
            }
            else
            {
                continue;
            }
        }
        // this will save the data back to the file
        fclose(fptr);
        FILE *fleave = fopen("leave_detail.txt","a");
        fprintf(fwrite,"|%s|%s|%s|%s|%s",annual,compassionate,emergency,maternity,medical);
        fprintf(fptr,"|%-14s|%-14s|%-14s|%-14s|\n",staffID,leave,status,leave_type);
        fclose(fptr);
        fclose(fread);
        fclose(fwrite);
        remove("staff_info.txt");
        rename("temp.txt","staff_info.txt"); 
    }
}
// This is for user to cancel leave, cancalled leave will delete be from the record"
// rejected or past leave cannot be cancel.
char cancel_leave(char *staffID)
{
    char *file_staffID;
    char *file_date;
    char *file_status;
    char *file_type;
    char line[100];
    char display_line[100];
    char target_line[100];
    // Opening and checking all the required file.
    FILE *fsource = fopen("leave_detail.txt","r");
    FILE *fdest = fopen("temp.txt","w");
    FILE *fread = fopen("staff_info.txt","r");
    FILE *fwrite = fopen("temp_staff.txt","w");
    if (fsource == NULL || fdest == NULL || fread == NULL || fwrite == NULL)
    {
        printf("File cannot open\n");
        main_function();
    }
    int size = 0;
    if(fread!=NULL)
    {
        fseek (fread, 0, SEEK_END);

        size = ftell (fread);
        rewind(fread);
    }
    if (size==0)
    {
        printf("You have no leave record\n");
        fclose(fread);
        fclose(fwrite);
        fclose(fsource);
        fclose(fdest);
        main_function();
    }
    size = 0;
    if(fsource!=NULL)
    {
        fseek (fsource, 0, SEEK_END);

        size = ftell (fsource);
        rewind(fsource);
    }
    if (size==0)
    {
        printf("You have no leave record\n");
        fclose(fread);
        fclose(fwrite);
        fclose(fsource);
        fclose(fdest);
        admin_UI();
    }
    // prompt user to enter the leave date.
    printf("Please enter the leave date you want to cancel\n");
    int flag = 0;
    char *apply_date = calendar();
    strip(apply_date);
    rewind(fsource);
    while(!feof(fsource))
    {
        fgets(line,sizeof(line),fsource);
        strip(line);
        if (strlen(line) != 61)
        {
            break;
        }
        strcpy(display_line,line);
        file_staffID = strtok(line, "| ");
        file_date = strtok(NULL, "| ");
        file_status = strtok(NULL, "| ");
        file_type = strtok(NULL, "| ");
        //only approved and pending leave can be cancelled
        if((strcmp(file_staffID,staffID) == 0) && (strcmp(file_date,apply_date) == 0) && (strcmp(file_status,"rejected") != 0))
        {
            strcpy(target_line,display_line);
            // tell user the leave is cancelled
            printf("The leave is cancelled\n");
            flag = 1;
        }
        else
        {
            fprintf(fdest,"%s\n",display_line);
        }
    }
    if(flag == 0)
    {
        // if rejected or not exist then close the file end this function
        printf("The leave is not applied yet or already been rejected\n");
        fclose(fread);
        fclose(fwrite);
        fclose(fdest);
        fclose(fsource);
    }
    else
    {
        // adding back the leave balance to the particular leave type for the staff
        fclose(fdest);
        fclose(fsource);
        char *annual;
        char *compassionate;
        char *emergency;
        char *maternity;
        char *medical;
        char *token;
        int new_change;
        char type[100];
        char *final_staffID;
        token = strtok(target_line,"| ");
        token = strtok(NULL,"| ");
        token = strtok(NULL,"| ");
        file_type = strtok(NULL,"| ");
        strcpy(type,file_type);
        strip(type);
        rewind(fread);
        while(!feof(fread))
        {
            fgets(line,sizeof(line),fread);
            strip(line);
            strcpy(display_line,line);
            if(strlen(line) == 8) // this is to catch the new line
            {
                break;
            }
            token = strtok(line,"|");
            final_staffID = token;
            if(strcmp(final_staffID,staffID) == 0)
            {
                strcpy(target_line,display_line);
            }
            else
            {
                fprintf(fwrite,"%s\n",display_line);
            }
        }
        token = strtok(target_line,"|");
        fprintf(fwrite,"%s|",token);
        for(int i = 0; i < 7; i++)
        {
            token = strtok(NULL,"|");
            fprintf(fwrite,"%s|",token);
        }
        annual = strtok(NULL,"|");
        compassionate = strtok(NULL,"|");
        emergency = strtok(NULL,"|");
        maternity = strtok(NULL,"|");
        medical = strtok(NULL,"|");
        // this is to adding back the leave balance back to the leave type
        if(strcmp(type,"annual") == 0)
        {
            new_change = atoi(annual) + 1;
            sprintf(annual,"%d",new_change);
        }
        else if (strcmp(type,"compassionate") == 0)
        {
            new_change = atoi(compassionate) + 1;
            sprintf(compassionate,"%d",new_change);
        }
        else if (strcmp(type,"emergency") == 0)
        {
            new_change = atoi(emergency) + 1;
            sprintf(emergency,"%d",new_change);
        }
        else if (strcmp(type,"maternity") == 0)
        {
            new_change = atoi(maternity) + 1;
            sprintf(maternity,"%d",new_change);
        }
        else if (strcmp(type,"medical") == 0)
        {
            new_change = atoi(medical) + 1;
            sprintf(medical,"%d",new_change);
        }
        fprintf(fwrite,"%s|%s|%s|%s|%s",annual,compassionate,emergency,maternity,medical);
        fclose(fread);
        fclose(fwrite);
        remove("staff_info.txt");
        remove("leave_detail.txt");
        rename("temp.txt","leave_detail.txt");
        rename("temp_staff.txt","staff_info.txt");
    }
}
// Check today leave status.whether no status , pending , approved or rejected
char leave_status(char *staffID)
{
    // this is the real time function
    time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    char current_date[255];
    snprintf(current_date, sizeof(current_date),"%d/%d/%d",current_time->tm_mday,current_time->tm_mon + 1,current_time->tm_year + 1900);
    // this is to open and check the file
    FILE *fptr = fopen("leave_detail.txt","r");
    if (fptr == NULL)
        {
            printf("File cannot be open\n");
            fclose(fptr);
            main_function();
        }
    int size = 0;
    if(fptr!=NULL)
    {
        fseek (fptr, 0, SEEK_END);

        size = ftell (fptr);
        rewind(fptr);
    }
    if (size==0)
    {
        printf("There is no information in this file\n");
        fclose(fptr);
        main_function();
    }
    char line[100];
    char *file_staffID;
    char *file_date;
    char *file_status;
    int flag = 0;
    // actual code function start on here
    while(!feof(fptr))
    {
        fgets(line,sizeof(line),fptr);
        strip(line);
        if (strlen(line) != 61) // prevent other type of error line crash the program
        {
            break;
        }
        file_staffID = strtok(line,"|");
        strip(file_staffID);
        file_date = strtok(NULL,"|");
        strip(file_date);
        file_status = strtok(NULL,"|");
        if(strcmp(file_staffID,staffID) == 0 && strcmp(file_date,current_date) == 0)
        {
            flag = 1;
            printf("Your leave status for today is:%s\n",file_status);
            Sleep(700);
            break;
        }
    }
    if (flag == 0)
    {
        printf("Your have no leave status\n");
        Sleep(700);
    }
    fclose(fptr);
}
// Check all the leave that staff have all applied.
char leave_info(char *staffID)
{
    // open and check all the file
    FILE *fptr = fopen("leave_detail.txt","r");
    if (fptr == NULL)
    {
        printf("File cannot open\n");
    }
    else
    {
        int size = 0;
        if(fptr!=NULL)
        {
            fseek (fptr, 0, SEEK_END);

            size = ftell (fptr);
            rewind(fptr);
        }
        if (size==0)
        {
            printf("There is no applying leave\n");
            fclose(fptr);
            admin_UI();
        }
        char line[100];
        char line_display[100];
        char *token;
        char *date;
        char *status;
        char *type;
        int flag = 0;
        // actual code fucntion start in here
        printf("=============================================================\n");
        printf("|StaffID       |Leave date    |Leave status  |Leave type    |\n");
        printf("=============================================================\n");
        while(!feof(fptr))
        {
            // Is have leave will display leave
            fgets(line,sizeof(line),fptr);
            strip(line);
            strcpy(line_display,line);
            token = strtok(line,"| ");
            if(strcmp(staffID,token) == 0 && strlen(line_display) > 10)
            {
                flag = 1;
                printf("%s\n",line_display);
            }
        }
        if (flag == 0)
        {
            // if not leave then will only show this
            printf("You have not applied any leave yet\n");
        }
        fclose(fptr);
        printf("=============================================================\n");
        
    }
}
// Check all the personal information and all leave balance.
char check_info(char *staffID)
{
    char str[100];
    char str_display[100];
    char *token;
    char confirmation[5]; 
    // open and check all the file used
    FILE *fptr = fopen("staff_info.txt","r");
    if (fptr == NULL)
    {
        printf("The file cannot be open\n");
        fclose(fptr);
        main_function();
    }
    int size = 0;
    if(fptr!=NULL)
    {
        fseek (fptr, 0, SEEK_END);

        size = ftell (fptr);
        rewind(fptr);
    }
    if (size==0)
    {
        printf("There is no staff saved in this file\n");
        fclose(fptr);
        main_function();
    }
    // actual code fucntion start on here
    while(!feof(fptr))
    {
        fgets(str,sizeof(str),fptr);
        strip(str);
        strcpy(str_display,str);
        token = strtok(str,"|");
        if(strcmp(staffID,token) == 0)
        {
            break;
        }
    }
    // show all the info of the staff
    printf("==========================\n");
    printf("StaffID:%s\n",token);
    token = strtok(NULL,"|");
    printf("Password:%s\n",token);
    token = strtok(NULL,"|");
    printf("Gender:%s\n",token);
    token = strtok(NULL,"|");
    printf("Full name:%s\n",token);
    token = strtok(NULL,"|");
    printf("Working start date:%s\n",token);
    token = strtok(NULL,"|");
    printf("Phone number:%s\n",token);
    token = strtok(NULL,"|");
    printf("Email:%s\n",token);
    token = strtok(NULL,"|");
    printf("Department:%s\n",token);
    token = strtok(NULL,"|");
    printf("Annual leave:%s\n",token);
    token = strtok(NULL,"|");
    printf("Compassionate leave:%s\n",token);
    token = strtok(NULL,"|");
    printf("Emergency leave:%s\n",token);
    token = strtok(NULL,"|");
    printf("Maternity leave:%s\n",token);
    token = strtok(NULL,"|");
    printf("Medical leave:%s\n",token);
    printf("==========================\n");
    fclose(fptr);
}

// approver section
// This will let approver to login.
int approver_login()
{
    int attempt = 0;
    while(attempt < 3)
    {
        // open and check the file
        FILE *fptr = fopen("approver_info.txt","r");
        if (fptr == NULL)
        {
            printf("File cannot be open\n");
            fclose(fptr);
            main_function();
        }
        int size = 0;
        if(fptr!=NULL)
        {
            fseek (fptr, 0, SEEK_END);

            size = ftell (fptr);
            rewind(fptr);
        }
        if (size==0)
        {
            printf("There is no information in this file\n");
            fclose(fptr);
            main_function();
        }
        char username[100];
        char password[100];
        char line[50];
        char *token;
        char *file_password;
        char *file_username;
        int flag = 0;
        // prompt user to enter the username and password
        printf("Please enter your username:");
        fgets(username, sizeof(username), stdin);
        strip(username);
        printf("Please enter your password:");
        fgets(password, sizeof(password), stdin);
        strip(password);
        // this will indicate whether the username and password is same as the file one
        while(!feof(fptr))
        {
            fgets(line,sizeof(line),fptr);
            token = strtok(line,"|");
            file_username = token;
            token = strtok(NULL,"|");
            file_password = token;
            if(strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            fclose(fptr);
            break;
        }
        else
        {
            fclose(fptr);
            attempt++;
            if(attempt == 3)
            {
                fclose(fptr);
                main_function();
            }
            printf("This is your %d attempt\n",attempt);
            continue;
        }
    }
}
// approver will choose the function they want to use on here.
int approver_UI()
{
    // show all the approver function and let them to pick
    int choice;
    char temp[50];
    printf("Please enter your selection\n");
    while(1)
    {
        printf("==============================\n");
        printf("1.Manage leave application\n");
        printf("2.Check leave on specific date\n");
        printf("3.Check all leave\n");
        printf("4.Logout\n");
        printf("Your choice:");
        gets(temp);
        if (strlen(temp) != 1)
        {
            printf("Please only enter a digit\n");
            continue;
        }
        choice = atoi(temp);
        if(1 <= choice && choice <= 4)
        {
            break;
        }
        else
        {
            printf("Please enter a valid selection\n");
            continue;
        }
    }
    return choice;
}
// This will be the back-end function of the approver function
int approver_function()
{
    approver_login();
    int choice;
    while(1)
    {
        choice = approver_UI();
        if(choice == 1)
        {
            approval_leave();
        }
        else if (choice == 2)
        {
            check_leave_date();
        }
        else if (choice == 3)
        {
            check_all_leave();
        }
        else
        {
            main_function();
        }
    }
}
// This will let approver to manage the leave applied from staff
int approval_leave()
{
    // open all the file and check them all
    printf("This is all the leave that required to approve\n");
    FILE *fsource = fopen("leave_detail.txt","r");
    FILE *fdest = fopen("temp.txt","w");
    FILE *fread = fopen("staff_info.txt","r");
    FILE *fwrite = fopen("temp_staff.txt","w");
    if (fsource == NULL || fdest == NULL)
    {
        printf("File cannot open\n");
        admin_UI();
    }
    int size = 0;
    if(fsource!=NULL)
    {
        fseek (fsource, 0, SEEK_END);

        size = ftell (fsource);
        rewind(fsource);
    }
    if (size==0)
    {
        printf("You have no leave record\n");
        fclose(fwrite);
        fclose(fread);
        fclose(fsource);
        fclose(fdest);
        admin_UI();
    }
    char line[100];
    char line_display[100];
    char line_target[100];
    char *token;
    char *date;
    char *status;
    char *type;
    char staffID[100];
    char *date_approve;
    // code fucntion start on here
    while(1)
    {
        rewind(fsource);
        printf("=============================================================\n");
        printf("|StaffID       |Leave date    |Leave status  |Leave type    |\n");
        printf("=============================================================\n");
        while(!feof(fsource))
        {
            fgets(line,sizeof(line),fsource);
            strip(line);
            if(strlen(line) != 61) // prevent abnormal data kill the program
            {
                break;
            }
            strcpy(line_display,line);
            token = strtok(line,"| ");
            token = strtok(NULL,"| ");
            token = strtok(NULL,"| ");
            if(strcmp("pending",token) == 0 && strlen(line_display) > 10)
            {
                printf("%s\n",line_display);
            }
        }
        printf("=============================================================\n");
        // this part need to prompt user to enter staffID and date so can change pending to approve or reject.
        printf("Please enter the staffID and date that you want to approve\n");
        printf("staffID:");
        fgets(staffID,sizeof(staffID),stdin);
        strip(staffID);
        date_approve = calendar();
        rewind(fsource);
        char file_staffID[100];
        char file_date_approve[100];
        char file_status[100];
        int flag = 0;
        while(!feof(fsource))
        {
            fgets(line,sizeof(line),fsource);
            strip(line);
            strcpy(line_display,line);
            if(strlen(line) != 61)
            {
                break;
            }
            token = strtok(line,"| ");//staffID
            strcpy(file_staffID, token);
            token = strtok(NULL,"| ");//leave date
            strcpy(file_date_approve, token);
            token = strtok(NULL,"| "); //leave status
            strcpy(file_status, token);
            if((strcmp(file_staffID,staffID) == 0) && (strcmp(file_date_approve,date_approve) == 0) && (strcmp(file_status,"pending") == 0))
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            // is the staffID and date is not exist in the file then will show this
            printf("Please enter a proper staffID and date\n");
            continue;
        }
        rewind(fsource);
        while(!feof(fsource))
        {
            fgets(line,sizeof(line),fsource);
            strip(line);
            strcpy(line_display,line);
            if(strlen(line) != 61)
            {
                break;
            }
            token = strtok(line,"| ");// this is the file staffID
            strcpy(file_staffID, token);
            token = strtok(NULL,"| ");//this is the file date;
            if(strcmp(file_staffID,staffID) == 0 && strcmp(token,date_approve) == 0)
            {
                strcpy(line_target,line_display);
            }
            else
            {
                fprintf(fdest,"%s\n",line_display);
            }
        }
        if(flag)
        {
            break;
        }
    }
    char *final_staffID;
    char *final_date;
    char *final_status;
    char *final_type;
    char answer[50];
    char confirmation[10];
    final_staffID = strtok(line_target,"| ");
    final_date = strtok(NULL,"| ");
    final_status = strtok(NULL, "| ");
    final_type = strtok(NULL,"| ");
    while(1)
    {
        // let approver to manage the leave
        printf("You want to approve or reject the leave(enter 'approved' or 'rejected')?:");
        fgets(answer,sizeof(answer),stdin);
        strip(answer);
        if(strcmp(answer,"rejected") == 0 || strcmp(answer,"approved") == 0)
        {
            strcpy(final_status,answer);
            break;
        }
        else
        {
            continue;
        }
    }
    // enter the data back to file
    fprintf(fdest,"|%-14s|%-14s|%-14s|%-14s|\n",final_staffID,final_date,final_status,final_type);
    fclose(fsource);
    fclose(fdest);
    remove("leave_detail.txt");
    rename("temp.txt","leave_detail.txt");
    char leave_type[100];
    strcpy(leave_type,final_type);
    strip(leave_type);
    char *annual;
    char *compassionate;
    char *emergency;
    char *maternity;
    char *medical;
    int new_change;
    // if rejected then it will add back the leave balance to the user
    if (strcmp(final_status,"rejected") == 0)
    {
        rewind(fread);
        while(!feof(fread))
        {
            fgets(line,sizeof(line),fread);
            strip(line);
            strcpy(line_display,line);
            if(strlen(line) == 8)
            {
                break;
            }
            token = strtok(line,"|");
            final_staffID = token;
            if(strcmp(final_staffID,staffID) == 0)
            {
                strcpy(line_target,line_display);
            }
            else
            {
                fprintf(fwrite,"%s\n",line_display);
            }
        }
        token = strtok(line_target,"|");
        fprintf(fwrite,"%s|",token);
        for(int i = 0; i < 7; i++)
        {
            token = strtok(NULL,"|");
            fprintf(fwrite,"%s|",token);
        }
        annual = strtok(NULL,"|");
        compassionate = strtok(NULL,"|");
        emergency = strtok(NULL,"|");
        maternity = strtok(NULL,"|");
        medical = strtok(NULL,"|");
        // indicate which type of leave they are saving
        if(strcmp(leave_type,"annual") == 0)
        {
            new_change = atoi(annual) + 1;
            sprintf(annual,"%d",new_change);
        }
        else if (strcmp(leave_type,"compassionate") == 0)
        {
            new_change = atoi(compassionate) + 1;
            sprintf(compassionate,"%d",new_change);
        }
        else if (strcmp(leave_type,"emergency") == 0)
        {
            new_change = atoi(emergency) + 1;
            sprintf(emergency,"%d",new_change);
        }
        else if (strcmp(leave_type,"maternity") == 0)
        {
            new_change = atoi(maternity) + 1;
            sprintf(maternity,"%d",new_change);
        }
        else if (strcmp(leave_type,"medical") == 0)
        {
            new_change = atoi(medical) + 1;
            sprintf(medical,"%d",new_change);
        }
        fprintf(fwrite,"%s|%s|%s|%s|%s",annual,compassionate,emergency,maternity,medical);
        fclose(fread);
        fclose(fwrite);
        remove("staff_info.txt");
        rename("temp_staff.txt","staff_info.txt");    
    }
    else
    {
        fclose(fread);
        fclose(fwrite);
    }
}
// This will let approver to check the leaves on entered date.
int check_leave_date()
{
    // open and check the file
    FILE *fptr = fopen("leave_detail.txt","r");
    if (fptr == NULL)
    {
        printf("File cannot open\n");
    }
    else
    {
        int size = 0;
        if(fptr!=NULL)
        {
            fseek (fptr, 0, SEEK_END);

            size = ftell (fptr);
            rewind(fptr);
        }
        if (size==0)
        {
            printf("There is no leave today\n");
            fclose(fptr);
            admin_UI();
        }
        // real code start on here
        char line[100];
        char line_display[100];
        char *token;
        char *date;
        int flag = 0;
        date = calendar();
        printf("=============================================================\n");
        printf("|StaffID       |Leave date    |Leave status  |Leave type    |\n");
        printf("=============================================================\n");
        while(!feof(fptr))
        {
            fgets(line,sizeof(line),fptr);
            strip(line);
            if(strlen(line) != 61)
            {
                break;
            }
            strcpy(line_display,line);
            token = strtok(line,"| ");
            token = strtok(NULL,"| "); // this is the date
            if(strcmp(date,token) == 0 && strlen(line_display) > 10)
            {
                flag = 1;
                printf("%s\n",line_display);
            }
        }
        if (flag == 0)
        {
            // if no leave it will show this message
            printf("There is no leave on that day\n");
        }
        printf("=============================================================\n");
        fclose(fptr);
    }
}
// This will directly show all the leaves from user.
int check_all_leave()
{
    // open and check the file
    FILE *fptr = fopen("leave_detail.txt","r");
    if (fptr == NULL)
    {
        printf("File cannot open\n");
    }
    else
    {
        int size = 0;
        if(fptr!=NULL)
        {
            fseek (fptr, 0, SEEK_END);

            size = ftell (fptr);
            rewind(fptr);
        }
        if (size==0)
        {
            printf("There is no leave today\n");
            fclose(fptr);
            admin_UI();
        }
        // code function start on here
        char line[100];
        char *token;
        printf("=============================================================\n");
        printf("|StaffID       |Leave date    |Leave status  |Leave type    |\n");
        printf("=============================================================\n");
        while(!feof(fptr))
        {
            fgets(line,sizeof(line),fptr);
            strip(line);
            if(strlen(line) != 61)
            {
                break;
            }
            printf("%s\n",line);
        }
        printf("=============================================================\n");
        fclose(fptr);
    }
}

// main section
int main_UI()
{
    int choice;
    char temp[50];
    // this is the start of everything everyone will face this function
    while(1)
    {
        printf("===========================================\n");
        printf("  LEAVE APPLICATION AND MANAGEMENT SYSTEM\n");
        printf("===========================================\n");
        printf("Please choose your role\n");
        printf("1.Admin\n2.Staff\n3.Leave Approver\n4.Exit\n");
        printf("Your choice:");
        gets(temp);
        if (strlen(temp) != 1)
        {
            printf("Please enter only one digit\n");
            continue;
        }
        choice = atoi(temp);
        if (1 <= choice && choice <= 4)
        {
            break;
        }
        else
        {
            printf("Please enter a valid selection\n");
            continue;
        }
    }  
    return choice;
}
int main_function()
{
    int choice;
    // this will managa the back-end of the main function.
    while(1)
    {   
        choice = main_UI();
        switch (choice)
        {
        case 1:
            admin_function();
            break;
        case 2:
            staff_function();
            break;
        case 3:
            approver_function();
            break;
        default:
            exit(1);
            break;
        }
    }
}
int main()
{
    // function start on here
    main_function();
}