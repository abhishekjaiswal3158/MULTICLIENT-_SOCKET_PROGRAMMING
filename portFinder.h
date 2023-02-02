#include <string>
using namespace std;

// int destination_port(string &s)       //used to extract the destination port from the string
// {
//   int i = s.size() - 2;
//   int dest_port = 0;
//   int mul = 1;
//   while (s[i] >= '0' && s[i] <= '9')
//   {
//     dest_port = dest_port + (s[i] - '0') * mul;
//     mul = mul * 10;
//     i--;
//   }
//   return dest_port;
// }
int destination_port(string &s){
    int i=0;
    int dest_port=0;
    while(i<s.size()){
        if(s[i]=='#'){
          i++;
          while(i<s.size()&&s[i]!='#'){
              if(s[i]>='0'&&s[i]<='9'){
                dest_port=dest_port*10+(s[i]-'0');
              }
              else{
                break;
              }
              i++;
          }
        }
        i++;
    }
    return dest_port;
}
int source_port(string &s)           //used to extract the source port from the string
{
  int i = s.size() - 1;
  int src_port = 0;
  int length = s.size();
  int flag = 0;
  int mul = 1;
  while (i >= 0)
  {
    int count = 0;
    while (s[i] >= '0' && s[i] <= '9')
    {
      if (flag == 0)
      {
        count++;
      }
      else
      {
        src_port = src_port + (s[i] - '0') * mul;
        mul = mul * 10;
      }
      i--;
    }
    if (count > 0)
    {
      flag = 1;
    }
    i--;
  }
  return src_port;
}