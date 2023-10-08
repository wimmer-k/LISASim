#include "util.hh"
int getfirstdigitfromstring(std::string sinput) {
  for(int i=0; i<(int)sinput.length(); i++) {
    if(isdigit(sinput[i]))
      return sinput[i]  - '0';
  }
  return -1;
}
int getfirstintegerfromstring(std::string sinput) {
  int digit = -1;
  int number = 0;
  for(int i=0; i<(int)sinput.length(); i++) {
    if(isdigit(sinput[i])){
      digit =  sinput[i]  - '0';
      number = number *10 + digit;
    }
  }
  if(digit<0)
    return -1;
  return number;
}
