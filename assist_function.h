# include <stdio.h>
# include <ctype.h>

// if value is capital letter return 2, lower capital it will return 1 if not alphabet return 0
int check_alphabet ( int num )
{
     if (( num >= 65 && num <= 90))
     {
        return 2;
     }   
     else if(( num >= 97 && num <= 122 ))
     {
      return 1;
     }
     else
     {
      return 0;
     }
}
// check whether is space if yes return 1 if not return 0
int check_space(int num)
{
  if (num == 32)
  {
    return 1;
  }
  return 0;
}
// check whether is digit if yes return 1 if not return 0
int check_digit ( int num )
{
     if (num >= 48 && num <= 57 )
     {
         return 1;
     }
     return 0;
}

//remove leading and trailing empty spaces, ' ' and new line'\n' any kind of space
void strip(char* str) {
    int len = strlen(str);
    int i = 0, j = len - 1;
    if (isspace(str[0]) == 0)
    {
        while (isspace(str[i]) && i < len) i++;
        while (isspace(str[j]) && j >= 0) j--;
        
        int new_len = j - i + 1;
        memmove(str, str + i, new_len);
        str[new_len] = '\0';
    }
}

// check user id is exist is exist return 1 if not return 0.
int check_user_id(char staffID[8])
{
    char str[100];
    char str_display[100];
    char *token;
    char confirmation[5];
    while(1)
    {   
        int flag = 0;
        FILE *fptr = fopen("staff_info.txt","r");
        if (fptr == NULL)
        {
            printf("The file cannot be open\n");
            exit(1);
        }
        rewind(fptr);
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
            fclose(fptr);
            return 1;
        }
        else
        {
            fclose(fptr);
            return 0;
        }
    }
}