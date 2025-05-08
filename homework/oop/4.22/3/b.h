

#ifndef CB
#define CB

#include"a.h"

class B 
{
    public:
          B(A& aA) { pA = &aA; }
          void Func() 
{   
               cout<<"This is member function Func()"<<endl;
          }
          void NewFunc() 
          {
              pA->OtherFunc();
          }
          
    private:
          A  *pA;
    };


#endif