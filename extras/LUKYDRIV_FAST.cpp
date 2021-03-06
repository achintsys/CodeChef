#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

// scanfs
#define SUL(x) scanf("%lu", &x)
#define SLL(x) scanf("%lld", &x)
#define SULL(x) scanf("%llu", &x)

/////////////////////
////// INPUT ////////
////////////////////
class INPUT {
  static const int BUFSIZE = 1<<16;
  static char buffer[];
  char *bufpos;
  char *bufend;
  void grabBuffer();
  public:
  INPUT() { grabBuffer(); }
  bool eof() { return bufend==buffer; }
  char nextChar() { return *bufpos; }
  inline char readChar();
  inline void skipWS();
  unsigned readUnsigned();
  int readInt();
};

char INPUT::buffer[INPUT::BUFSIZE];

void INPUT::grabBuffer() {
  bufpos = buffer;
  bufend = buffer + fread( buffer, 1,BUFSIZE,stdin);
}

char INPUT::readChar() {
  char res = *bufpos++;
  if(bufpos==bufend) grabBuffer();
  return res;
}

inline bool myisspace(char c) { return c<=' '; }

void INPUT::skipWS() {
  while(!eof() && myisspace(nextChar())) readChar();
}

unsigned INPUT::readUnsigned() {
  skipWS();
  unsigned res = 0;
  while(!eof() && isdigit(nextChar())) {
    res = 10u * res + (readChar()-'0');
  }
  return res;
}

int INPUT::readInt() {
  skipWS();
  bool neg = false;
  if(!eof() && nextChar()=='-') { neg=true; readChar(); }
  int res = static_cast<int>(readUnsigned());
  if(neg) res = -res;
  return res;
}

/////////////////////
////// OUTPUT //////
////////////////////

class OUTPUT {
  static const int BUFSIZE = 1<<16;
  static char buffer[];
  char *bufpos;
  char *BUFLIMIT;
  void flushBuffer();
  public:
  OUTPUT():bufpos(buffer),BUFLIMIT(buffer+BUFSIZE-100) {}
  ~OUTPUT() { flushBuffer(); }
  inline void operator()(char c);
  inline void operator()(unsigned x);
  inline void operator()(int x);
  inline void operator()(unsigned long long int x);
  inline void operator()(long long int x);
  inline void operator()(const char*s);
  void operator()(const string&s) { operator()(s.c_str()); }
  template<class A,class B>
    void operator()(const A& a,const B& b) {
      operator()(a); operator()(b);
    }
  template<class A,class B,class C>
    void operator()(const A& a,const B& b,const C&c) {
      operator()(a); operator()(b); operator()(c);
    }
  template<class A,class B,class C,class D>
    void operator()(const A& a,const B& b,const C&c,const D&d) {
      operator()(a); operator()(b); operator()(c); operator()(d);
    }
  template<class A,class B,class C,class D,class E>
    void operator()(const A& a,const B& b,const C&c,const D&d,const E&e) {
      operator()(a); operator()(b); operator()(c); operator()(d); operator()(e);
    }
  template<class A,class B,class C,class D,class E,class F>
    void operator()(const A& a,const B& b,const C&c,const D&d,const E&e,const F&f) {
      operator()(a); operator()(b); operator()(c); operator()(d); operator()(e); operator()(f);
    }
};

char OUTPUT::buffer[OUTPUT::BUFSIZE];

void OUTPUT::flushBuffer() {
  char *p = buffer;
  while(p < bufpos) {
    p += fwrite( p,1, bufpos-p,stdout);
  }
  bufpos = buffer;
}

void OUTPUT::operator()(char c) {
  *bufpos = c;
  ++bufpos;
  if(bufpos >= BUFLIMIT) flushBuffer();
}

void OUTPUT::operator()(unsigned x) {
  char *old = bufpos;
  do {
    *bufpos = char('0' + x % 10u);
    x /= 10u;
    ++bufpos;
  } while(x);
  reverse(old, bufpos);
  if(bufpos >= BUFLIMIT) flushBuffer();
}

void OUTPUT::operator()(int x) {
  if(x<0) { operator()('-'); x = -x; }
  operator()(static_cast<unsigned>(x));
}

void OUTPUT::operator()(unsigned long long int x) {
  char *old = bufpos;
  do {
    *bufpos = char('0' + x % 10u);
    x /= 10u;
    ++bufpos;
  } while(x);
  reverse(old, bufpos);
  if(bufpos >= BUFLIMIT) flushBuffer();
}

void OUTPUT::operator()(long long int x) {
  if(x<0) { operator()('-'); x = -x; }
  operator()(static_cast<unsigned long long int>(x));
}

void OUTPUT::operator()(const char*s) {
  while(*s) operator()(*s++);
}

INPUT input;
OUTPUT output;

string array[] = {"9",
"09",
"18",
"27",
"36",
"45",
"99",
"009",
"018",
"027",
"036",
"045",
"099",
"117",
"126",
"135",
"144",
"189",
"225",
"234",
"279",
"288",
"333",
"369",
"378",
"459",
"468",
"477",
"558",
"567",
"666",
"999",
"0009",
"0018",
"0027",
"0036",
"0045",
"0099",
"0117",
"0126",
"0135",
"0144",
"0189",
"0225",
"0234",
"0279",
"0288",
"0333",
"0369",
"0378",
"0459",
"0468",
"0477",
"0558",
"0567",
"0666",
"0999",
"1116",
"1125",
"1134",
"1179",
"1188",
"1224",
"1233",
"1269",
"1278",
"1359",
"1368",
"1377",
"1449",
"1458",
"1467",
"1557",
"1566",
"1899",
"2223",
"2259",
"2268",
"2277",
"2349",
"2358",
"2367",
"2448",
"2457",
"2466",
"2556",
"2799",
"2889",
"3339",
"3348",
"3357",
"3366",
"3447",
"3456",
"3555",
"3699",
"3789",
"3888",
"4446",
"4455",
"4599",
"4689",
"4779",
"4788",
"5589",
"5679",
"5688",
"5778",
"6669",
"6678",
"6777",
"9999"};

unsigned int hist[10];
unsigned int temp[10];
unsigned int local[10];

int main( int argc, char** argv)
{
  int T;

  T = input.readInt();
  input.readChar();
  while(T--)
  {
    for( int i=0; i<10; i++)
      hist[i] = 0;

    char s = input.readChar();
    while( s != '\n')
    {
      hist[s - '0'] += 1;
      s = input.readChar();
    }

    unsigned long long int sum = 0;
    unsigned long long int prod = 1;

    for(int j=0; j<112; j++)
    {
      for(int i=0; i<10; i++)
      {
        temp[i] = hist[i];
        local[i] = 0;
      }
      int len = array[j].size();
      prod = 1;
      for( int k=0; k<len; k++)
      {
        int index = (int) array[j][k] - '0';
        prod *= temp[index];
        temp[index] -= 1;
        local[index] += 1;
      }
      if( prod > 0)
      {
        for( int i=0; i<10; i++)
          if( local[i] > 0)
          {
            if( local[i] == 4)
              prod /= 24;
            else if( local[i] == 3)
              prod /= 6;
            else
              prod /= local[i];
          }
        sum = (sum +prod) % 1000000007;
      }
    }
    output( sum, "\n");
  }
  return 0;
}
