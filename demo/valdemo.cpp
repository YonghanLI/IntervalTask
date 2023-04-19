#include <iostream>
#include "ibex.h"
using namespace std;
using namespace ibex;

double bound_maxval( Function f,IntervalVector inputbox){
    int _dim=inputbox.size();
    IntervalVector tempcheck(inputbox);
    double maxcheck[_dim];
    for(int i;i<_dim;i++){
        double up=inputbox[i].ub();
        double low=inputbox[i].lb();
        tempcheck[i]=Interval(up,up);
        double maxone=f.eval(tempcheck).ub();
        cout<<maxone<<endl;
        tempcheck[i]=Interval(low,low);
        double maxtwo=f.eval(tempcheck).ub();
        cout<<maxtwo<<endl;
        if(maxone>=maxtwo){
            maxcheck[i]=maxone;
        }
        else{
            maxcheck[i]=maxtwo;
        }
        tempcheck[i]=Interval(low,up);
    }
    double maxout=maxcheck[0];
    for(int i=0;i<_dim;i++){
        if(maxcheck[i]>=maxout){
            maxout=maxcheck[i];
        }
    }
    return maxout;

}

IntervalVector BrunchFindBox(Function myfunction , IntervalVector user_box , int boxdim){

    IntervalVector TempBox=user_box;
    Function df_func(myfunction,Function::DIFF);
    for(int i=0 ; i<boxdim ; i++){
        Function partdf=df_func[i];
        partdf.backward(0,TempBox);
        cout<<"tempbox is :" <<TempBox<<endl;
    }

    return TempBox;

}

double find_level(Function f,IntervalVector res_box){
    double level_val;
    Interval boxval=f.eval(res_box);
    level_val=boxval.ub();

    return level_val;
}

int main(int argc, const char** argv){

    // Function f("x1","x2","x3","x4","x5","pow(x1-1,2)+pow(x2-2,2)+pow(x3-3,2)+pow(x4-4,2)+pow(x5-5,2)");
    // int dimval=5;
    // IntervalVector init_box(dimval,Interval(-10,10));

    Function f("x1","x2","x3","-pow(x1,2)-exp(x2)-pow(x3-1,2)");
    int dimval=3;
    IntervalVector init_box(dimval);
    init_box[0]=Interval(-1,1);
    init_box[1]=Interval(-3,4);
    init_box[2]=Interval(-2,5);


    IntervalVector res_box=BrunchFindBox(f,init_box,dimval);
    cout<<"res box is :"<<res_box<<endl;
    
    double inner_level=find_level(f,res_box);
    cout<< "the level val is :" << inner_level <<endl;

    double bound_max=bound_maxval(f,init_box);
    cout << "the bound max is :" <<bound_max<<endl;

    return 0;
}
