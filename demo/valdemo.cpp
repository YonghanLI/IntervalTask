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
        tempcheck[i]=Interval(low,low);
        double maxtwo=f.eval(tempcheck).ub();
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
    }

    return TempBox;

}

double find_level(Function f,IntervalVector res_box){
    double level_val;
    Interval boxval=f.eval(res_box);
    level_val=boxval.ub();

    return level_val;
}

double MaxGetByBranch(Function f , IntervalVector user_box , int boxdim){
    double result;
    double bound_max  = bound_maxval(f,user_box);
    IntervalVector res_box=BrunchFindBox(f,user_box,boxdim);
    if(res_box.is_empty()==true){
        cout<< "inner value is empty"<<endl;
        cout<<" bound_max  is :"<<bound_max<<endl;
        result=bound_max;
        cout<< " Ressult is : "<<bound_max<<endl;
    }
    else{
        double inner_level= find_level(f,res_box);
        cout<< "inner value is :"<< inner_level <<endl;
        cout<<" bound_max  is :"<<bound_max<<endl;
        if(inner_level<bound_max){
            result=bound_max;
        }
        else{
            result=inner_level;
        }
        cout<< " Ressult is : "<< result <<endl;
    }
    return result;
    

}



int main(int argc, const char** argv){


    // Function f("x1","x2","x3","-pow(x1,2)-exp(x2)-pow(x3-1,2)");
    // int dimval=3;
    // IntervalVector init_box(dimval);
    // init_box[0]=Interval(-1,1);
    // init_box[1]=Interval(-3,4);
    // init_box[2]=Interval(-2,5);

    Function f("x1","x2","-x1^2 - (x2-1)^2");
    int dimval=2;
    IntervalVector init_box(dimval);
    init_box[0]=Interval(-1,1);
    init_box[1]=Interval(-3,3);


    MaxGetByBranch(f,init_box,dimval);



    return 0;
}
