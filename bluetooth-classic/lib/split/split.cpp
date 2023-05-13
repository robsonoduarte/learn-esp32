#include "split.h"


String* split(String value, String delimiter, int size ){
    String* values = new String[size];
    int i = 0;
    char* token = strtok(value.begin(), delimiter.begin());
    while(token != NULL && i < size){
     values[i++] = String(token);
     token = strtok(NULL, delimiter.begin());
    }
    return values;
}
