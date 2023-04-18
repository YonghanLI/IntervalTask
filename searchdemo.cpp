#include <iostream>
#include "ibex.h"

using namespace std;
using namespace ibex;

IntervalVector BrunchFindBox(Function myfunction , IntervalVector user_box , int boxdim){

    IntervalVector TempBox=user_box;
    Function df_func(myfunction,Function::DIFF);
    for(int i=0 ; i<boxdim ; i++)
    {
        Function partdf=df_func[i];
        partdf.backward(0,TempBox);

    }

    return TempBox;

}

int main(int argc, const char** argv){

    Function f("x1","x2","x3","x4","x5","pow(x1-1,2)+pow(x2-2,2)+pow(x3-3,2)+pow(x4-4,2)+pow(x5-5,2)");
    IntervalVector init_box(5,Interval(-10,10));
    IntervalVector res_box=BrunchFindBox(f,init_box,5);
    cout<<"Ans is :"<<res_box<<endl;

    return 0;
}