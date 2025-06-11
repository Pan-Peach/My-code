#include <iostream>

using namespace std;

namespace China {

      class A {

      public:

             void f( ) const { cout<<"1"; }

      };

      namespace University {

              class B {

              public:

                       void g( ) const { cout<<"2";}

              };

      }

}

int main( ) {
       using namespace China;      

       using namespace University; B  b;        //1
       b.g( );

       return 0;
}