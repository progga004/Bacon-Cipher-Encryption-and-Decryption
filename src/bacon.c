
#include "bacon.h"
#include <string.h>
#include <stdio.h>
//#include<ctype.h>
// Add other #includes here if you want.

int encrypt(const char *plaintext, char *ciphertext)
{
    //taking the input of bacon codes as array of strings
    char *baconCodes[] = {"000000", "000001", "000010", "000011", "000100", "000101", "000110", "000111", "001000", "001001", "001010","001011",
                                                                                                                             
                          "001100", "001101", "001110", "001111", "010000", "010001", "010010", "010011", "010100", "010101", "010110", "010111","011000",
                                                                                                                                                 
                          "011001","011010","011011","011100","011101","011110","011111","100000","100001","100010","100011","100100","100101","100110","100111","101000","101001",   // only the letters A-Z
                          "101010","101011","101100","101101","101110","101111","110000","110001","110010","110011","110100"};
    
     int length_1 = strlen(plaintext); //length of the plaintext
     int length_2 = strlen(ciphertext); // length of the cipher text
      int countWithoutSpaces = 0;
      
    for (int i = 0; ciphertext[i] != '\0'; i++)
    {
        if (ciphertext[i]>=' '&& ciphertext[i]<='/'|| ciphertext[i]>='0'&& ciphertext[i]<='9')
        {
            countWithoutSpaces = countWithoutSpaces + 1;
        }
    }// counting how many spcaes, special symbols are there( not included special symbols)
    countWithoutSpaces = length_2 - countWithoutSpaces; // counting the character without spcaes
    int necessary_baconwords = countWithoutSpaces - 6; // substracting the EOM
    int words = necessary_baconwords / 6; // how many words are needed from plaintext to encrypt 
    if(words>=length_1)
    {
        words=length_1; // checking the condition if the words are greater than the length of the plaintext, so its going to take all
    }
    int cipertextpos=0; // track the ciphertextposition in ciphertext
    char str1[length_2];
    char str2[length_2];
    char str3[length_1];
    int k = 0;
    int n=0;
    // for another pointer to point out the new string
   
    for (  n = 0; ciphertext[n] != '\0'; n++)
    {
       
        str2[n]=ciphertext[n];
    }
    str2[n]!='\0';
    for (  n = 0; ciphertext[n] != '\0'; n++)
    {
       if(ciphertext[n]>='A'&& ciphertext[n]<='Z')

       {ciphertext[n]=(ciphertext[n]+32);}
       else
       {
        ciphertext[n]=ciphertext[n];
       }
    }
    int m=0;
     for (  m = 0; plaintext[m] != '\0'; m++)
    {
        
        str3[m]=plaintext[m];
    }
    str3[m]='\0'; // creating all uppercase letters string named str3 from plaintext
    for (  m = 0; str3[m] != '\0'; m++)
    {
        
       if(str3[m]>='a'&& str3[m]<='z')

       {str3[m]=(str3[m]-32);}
       else
       {
        str3[m]=str3[m];
       }
    }
    if(countWithoutSpaces<6)
    {
        return -1;
    }
    else{
    for (int i = 0; i < words; i++)
    { char *ptr; // creating a pointer to store the specific character value 6 bits from plaintext
       if (str3[i] >= 'A' && str3[i] <= 'Z')
        {int index = str3[i] - 'A';
         ptr = baconCodes[index];
        } // finding out the value from the baconCodes index if the letter is between A-Z
        else 
        {   if(str3[i]>='*' && str3[i]<=';'){
              int index=str3[i]-6-2;
              ptr=baconCodes[index];
            }// if the value is from upper 44 (42,43) not included
            else if(str3[i]=='?')
            {
                int index=str3[i]-11;
                ptr=baconCodes[index];
            }
            else
            {
                 int index=str3[i]-6;
                 ptr=baconCodes[index];
            }// just substract 6 if its between ascii code 32-41
        }
        int j = 0;
        while (j <= 5) // loop through the 6 bits and find out the uppercase letters
        {
            if ((ptr[j] == '0') ) // if the value is 0
            {
                if(ciphertext[cipertextpos]>=' ' && ciphertext[cipertextpos]<='9') // confusion here// going through the lowercase str2
                {
                    ciphertext[k]=ciphertext[cipertextpos];
                    k++;
                    cipertextpos++;
                }// excluding the values of special symbols and digits
                else
                {
                     ciphertext[k] = ciphertext[cipertextpos];
                     cipertextpos = cipertextpos + 1;
                      j++;
                      k++;
                }// special for the case in I can count three chaarcters
            }
            else // if the value is 1
            {
                if (ciphertext[cipertextpos]>=' ' && ciphertext[cipertextpos]<='9') // again checking the ciphertext if there is any special symbols or digits
                {
                    ciphertext[k] = ciphertext[cipertextpos];
                    cipertextpos++;
                    k++;
                }// exclude them
                else
                {
                    // making the character case upper and input them
                    char c = ciphertext[cipertextpos];
                    char p = c - 32;
                    ciphertext[k] = p;
                    cipertextpos++;
                    j++;
                    k++;
                    
                }
            }
        }
    }
    int p=0;
    while(ciphertext[cipertextpos]!='\0') // now adds the EOM 
    {
        while(p<=5)// going through the 6 bits and make them uppercase
        {
            if(ciphertext[cipertextpos]>=' ' && ciphertext[cipertextpos]<='9') // exclude them
            {
                ciphertext[k]=ciphertext[cipertextpos];
                cipertextpos++;
                k++;
            }
            else
            {
                if(ciphertext[cipertextpos]>='a'&& ciphertext[cipertextpos]<='z') // if the character is lower, make them upper
                {
                 ciphertext[k]=ciphertext[cipertextpos]-32;
                 cipertextpos++;
                 k++;
                 p++;}
                else
                {
                   ciphertext[k]=ciphertext[cipertextpos]; // if the character is upper, stay them in that way
                   cipertextpos++;
                   k++;
                   p++; 
                }
            }
               
            
        }
        ciphertext[k]=str2[cipertextpos];// if there is still something to count just put them
        cipertextpos++;
         k++;
         
    }
    return words;
    }
     
     
     // return the words encrypted from plaintext
}

int decrypt(const char *ciphertext, char *plaintext)
{
    char bconcodes[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ','!','"',
      '#','$','%','&','\'','(',')',',','-','.','/','0','1','2','3','4','5','6','7','8','9',':',':','?'};
     int length_1 = strlen(plaintext); //length of the plaintext
     int length_2 = strlen(ciphertext); // length of the cipher text
     int countWithoutSpaces = 0;
     char str1[length_2];
     int i,j=0;
     for (i = 0; ciphertext[i] != '\0'; i++) // creating the countwithout space
    {
        if (ciphertext[i]>=' '&& ciphertext[i]<='/'|| ciphertext[i]>='0'&& ciphertext[i]<='9')
        {
            countWithoutSpaces = countWithoutSpaces + 1;
        }
        else
        {
            str1[j]=ciphertext[i];
            j++;
        }
       
    }
     
    str1[j]='\0';
    int index=0;
    int cipertextpos=0;
    int count=0;
    int plaintextpos=0;
    
  if(strlen(ciphertext)>=6){
   for(int p=0;p<strlen(str1) && cipertextpos<=strlen(str1);p=p+6)
   {
       int ptr[6]={0,0,0,0,0,0};
       int j=0;
       int sum=0;
      
       while(j<=5)
       {
           if(str1[cipertextpos]>='A' && str1[cipertextpos]<='Z')
           {
           
               ptr[j]=1;
               j++;
               cipertextpos++;
           }
           else
           {
            
               ptr[j]=0;
               j++;
               cipertextpos++;
           }
         
       }
      
       int new_one=32;
       for(int k=0;k<6;k++)
      {
          sum=sum+ptr[k]*new_one;
          new_one=new_one/2;
      }
      
    
      index=sum;
      if(index==63 )
      {
          break;
      }
      
      else{
      if(index>=0 && index<=52)
      {
       char c= bconcodes[index];
       plaintext[plaintextpos]=c;
        plaintextpos++;
          count++;
      }
      else
      {
          return -3;
         
      }
      }
      
    }
    
    plaintext[plaintextpos]='\0';
    }
    if(strlen(plaintext)==0 && strlen(ciphertext)>=6)
    {
        plaintext[plaintextpos]='\0';
        return -1;
    }
    
    if(strlen(ciphertext)<6)
    {
               plaintext[plaintextpos]='\0';
               return -2;
                
    }
    
    return count; 
}
// int main()
// {

// }
    
 