#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<set>
#include<utility>
using namespace std;
 
int main(int argc, char* argv[]) {
    
    FILE * input=fopen(argv[1],"r");//测试输入
	FILE * ans=fopen(argv[2],"r");//测试输出
	FILE * user_out=fopen(argv[3],"r");//用户输出
	int ret=0; //AC=0,WA=1
	
	/*****spj代码区域*******/
	int T,n;
	fscanf(input,"%d",&T);
	while(T--)
	{
		double a,b;
		int n;
		fscanf(input,"%d",&n);
		fscanf(ans,"%lf",&a);
		fscanf(user_out,"%lf",&b);
		if(fabs(a-b)>1e-6) //WA 
		{
			ret=1;
			break;
		}
	}
	
	/*****spj-end********/ 
	        fprintf(stdout,"hhhhhhhhhhhhh");

    fclose(input);
    fclose(ans);
    fclose(user_out);
    return ret;
}