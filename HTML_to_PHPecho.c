/****************************************************************************
 * **Author: Glenn Upthagrove
 * **Last Update: 11/08/16
 * **Birth Date: 10/28/16
 * **Description: A program that opens a file specified by the user. 
 * The file must be HTML code. It then takes this code and wraps it into a 
 * PHP echo function and escapes out all of the quotation marks. 
 * This is then sent to a file of the users choice. 
 * *************************************************************************/

#include <stdio.h>
#include <string.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/**********************************************************************
 **Description: Gets the input from the user and copies it to a char*. 
 *********************************************************************/
void get_input(char* return_string){
  char input_buffer[128];
  scanf("%128s", input_buffer);
  strcpy(return_string, input_buffer);
}
/*******************************************************************
**Description: reads the input file and places it in its entirety 
**into the return_string. 
*******************************************************************/
void get_full_file(int file, char* return_string, int file_size){
  int bytes_read;
  bytes_read = read(file, return_string, sizeof(char)*file_size);
  if(bytes_read < 0){
    printf("ERROR READING FILE\n");
    exit(1);
  }
}
/****************************************************************************
**Description: Uses strtok() to parse each part of the full_file string 
**Then writes the individual parts and escape characters to the output file. 
****************************************************************************/
void parse_file(char* file_string, int output_file){
  int bytes = 0;
  char* write_string;
  char* returned = NULL;
  write_string = malloc(sizeof(char)*(strlen(file_string)+1)); 
  bytes = write(output_file, "echo \"\n", 7);
  do{
    memset(write_string, '\0', sizeof(char)*(strlen(file_string)+1));
    if(returned == NULL){
      returned = strtok(file_string, "\"");
    }
    else{
      returned = strtok(NULL, "\"");
    }
    if(returned != NULL){
      strcpy(write_string, returned);
      bytes = write(output_file, write_string, strlen(write_string)); 
      bytes = write(output_file, "\\", 1);
      bytes = write(output_file, "\"", 1);
    }
  }while(returned != NULL);
  lseek(output_file, -2, SEEK_END);
  bytes = write(output_file, "\";" , 2);
  free(write_string);
}
/*********************************************************************************
**Description: gets the input for the input and output files form the user,
**opens and closes both files, calls other functions, and frees allocated memory.  
*********************************************************************************/
int main(){
  char* input;
  int input_file = -1;
  int output_file = -1;
  struct stat input_file_stat;
  struct stat output_file_stat; 
  char* file_string;

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
  stat(input, &input_file_stat);

  while(output_file < 0){
    memset(input, '\0', 128);
    printf("Enter the file you would like to write to> ");
    get_input(input);
    output_file = open(input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(input_file < 0){
      printf("ERROR OPENING FILE\n");
    }
  }
  stat(input, &output_file_stat);
  
  file_string = malloc(sizeof(char)*input_file_stat.st_size);
  memset(file_string, '\0', sizeof(char)*input_file_stat.st_size);
  get_full_file(input_file, file_string, input_file_stat.st_size);
  parse_file(file_string, output_file);

  free(input);
  free(file_string);
  close(input_file);
  close(output_file);
  return 0;
}
