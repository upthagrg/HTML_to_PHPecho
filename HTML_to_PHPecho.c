/*****************************************************************
**Author: Glenn Upthagrove
**Last Update: 10/28/16
**Birth Date: 10/28/16
**Description: A program that opens a file specified by the user. 
The file must be HTML code. It then takes this code and wraps it into a 
PHP echo function and escapes out all of the quotation marks. 
This is then sent to a file of the users choice. 
*****************************************************************/

#include <stdio.h>
#include <string.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include<fcntl.h>
#include <stdlib.h>

/****************************************************************
**Description: Gets the input from the user and copies it to a char*. 
****************************************************************/
void get_input(char* return_string){
  char input_buffer[128];
  scanf("%128s", input_buffer);
  strcpy(return_string, input_buffer);
}
int main(){
  char* input;
  int input_file = -1;
  int output_file = -1;
  input = malloc(sizeof(char)*128);  
  while(input_file < 0){
    memset(input, '\0', 128);
    printf("Enter the file you would like to read from> ");
    get_input(input);
    input_file = open(input, O_RDONLY);
    if(input_file < 0){
      printf("ERROR OPENING FILE\n");
    }
  }
  while(output_file < 0){
    memset(input, '\0', 128);
    printf("Enter the file you would like to write to> ");
    get_input(input);
    output_file = open(input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(input_file < 0){
      printf("ERROR OPENING FILE\n");
    )
  }
  close(input_file);
  close(output_file);
  return 0;
}
