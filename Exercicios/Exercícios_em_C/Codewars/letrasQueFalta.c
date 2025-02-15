#include <stdio.h>

int main ()
{
  
  char phnum[15];
  char nums[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

  phnum[0]='(';
  phnum[1]=nums[0];
  phnum[2]=nums[1];
  phnum[3]=nums[2];
  phnum[4]=')';
  phnum[5]=' ';
  phnum[6]=nums[3];
  phnum[7]=nums[4];
  phnum[8]=nums[5];
  phnum[9]='-';
  phnum[10]=nums[6];
  phnum[11]=nums[7];
  phnum[12]=nums[8];
  phnum[13]=nums[9];
  phnum[14]='\0';
  
  printf("%c", *phnum);
}