#include <limits.h>
#include <stdio.h>
#include <math.h>
#define size 50


int numberTranslator(char* number, int base, int* equivalent) {
   int length = 0;
   int temp = 0;
   while (true) {
      if (number[length] == '\0') {
         break;
      }
      else {
         temp = (int)number[length];
         if (48 <= temp && temp <= 57) {
            temp -= 48;
         }
         else if (65 <= temp && temp <= 90) {
            temp -= 55;
         }
         else if (97 <= temp && temp <= 122) {
            temp -= 87;
         }
         if (temp > base) {
            printf("Number outside of base!");
            return 0;
         }
         equivalent[length] = temp;
         length++;
      }
   }
   return length;
}

long long int baseTenTranslator(long long int base, long long int length, int* equivalent) {
   int temp = 0;
   long long int tester;
   long long int output = 0;
   temp = 0;
   auto m = LONG_LONG_MAX;
   tester = pow(base, length-1);
   while (temp < length) {
      output = output + (long long int)(equivalent[temp])*tester;
      temp++;
      tester = tester/base;
   }
   return output;
}


long long int findingTempForLast2(long long int output, long long int base_out) {
   long long int temp_for_last2;
   temp_for_last2 = 0;
   while (true) {
      if (output == 0){
         break;
      }
      else {
         output = output/base_out;
         temp_for_last2 = temp_for_last2+1;
      }
   }
   return temp_for_last2;
}

bool theOutput(long long int output, long long int base_out, char* number, int temp_for_last2){
   if (temp_for_last2 > size) {
      printf("Number is too big!");
      return false;
   }
   long long int temp_base_out = base_out;
   int counter = 0;
   long long int return_value = 0;
   char temp;
   while (counter < temp_for_last2) {
      return_value = (output%temp_base_out)/(temp_base_out/base_out);
      temp_base_out = base_out*temp_base_out;
      output = output - return_value;

      if (return_value < 10){
         number[counter] = (char)('0'+return_value);
      }
      else {
         number[counter] = (char)('A'+return_value-10);
      }
      counter++;
   }
   return_value = 0; // Now it's another counter bc we won't need it anymore, but we still need counter
   while (return_value <= (counter-return_value)) {
      temp = number[return_value];
      number[return_value] = number[counter-1-return_value];
      number[counter-1-return_value] = temp;
      return_value++;
   }
   return_value = 0;
   while (return_value < (counter)) {
      printf("%c", number[return_value]);
      return_value++;
   }

}

int main(void) {
   int initial_base;
   int output_base;
   char number[50];
   char number_out[size];
   int equivalent[50];
   long long int base_ten;
   printf("Input base you want your number to be translated from: ");
   scanf("%d", &initial_base);
   printf("Input base you want your number to be translated to: ");
   scanf("%d", &output_base);
   if (initial_base < 2 || initial_base > 30 || output_base < 2 || output_base > 30) {
      printf("Unable to translate");
   }
   else {
      printf("Input your number: ");
      scanf("%s", number);
      base_ten = baseTenTranslator(initial_base, numberTranslator(number, initial_base, equivalent), equivalent);
      theOutput(base_ten, output_base, number_out, findingTempForLast2(base_ten, output_base));
   }
}