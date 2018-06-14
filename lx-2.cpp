#include<iostream>  
#include<iomanip>
#include<cstdlib>  
  
using namespace std;  
  
//�����������ʼ��  
    //���̵������  
    int N=10;  
    //��Դ�������  
    int M=3;  
    //��������Դ����  
    int Available[50] = {0};  
    int Available_A[50] = {0};  
    //���������  
    int Max[10][50] = {0};  
    //�ѷ�����Դ��  
    int Allocation[10][50] = {0};  
    int Allocation_A[10][50] = {0};  
    //������Դ��Ŀ  
    int Need[10][50] = {0};  
    int Need_N[10][50] = {0};  
    //������Դ����  
    int Request[100]={0};  
    //��������  
    int Work[50] = {0};  
    //��������  
    int Finish[50] = {0};  
    //��ȫ����  
    int Security[10] = {0};  
      
    //�ж�ֵ  
    int Bool = 0;  
      
    int Temp[50] = {0};  
      
    //��Դ����  
    char ZName[20] = {0};  
  
//��ʼ����Դ��ĿM������ÿһ����Դ�����ƺ���Ŀ�Լ�������ĿN   
void evaluate_1(){  
    int m,n;   
    cout<<"��������Դ��������Ŀ��";  
    cin>>m;  
    if(m<=M){  
        //����ÿһ����Դ�����ƺ���ĿAvailable  
        for(int i=1;i<=m;i++){  
            cout<<"�������"<<i<<"����Դ������(һ����ĸ��һ������)��";  
            cin>>ZName[i-1];  
            cout<<"�������"<<i<<"����Դ����Ŀ��";  
            cin>>Available[i-1];  
        }  
        cout<<endl;  
    }  
    else  
	{ cout<<"��Դ��Ŀ̫�࣬����������������"<<endl;  }
      
    cout<<"��������̵���Ŀ��";  
    cin>>n;  
    if(n<=N){  
        N=n;  
        cout<<endl;  
    }  
    else  
        cout<<"ϵͳ�޷����ɣ�����������������"<<endl;  
      
}  
  
//��������������ͷ������   
void evaluate_2(){  
      
    int i,j;  
  
    //��������������  
    cout<<"����������̵������������ֵ("<<N<<"*"<<M<<"����)[Max]:"<<endl;  
    for(i=0;i<N;i++){  
        for(j=0;j<M;j++){  
            cin>>Max[i][j];  
        }  
    }  
      
    //�����������  
    cout<<"����������̵ķ�������ֵ("<<N<<"*"<<M<<"����)[Allocation]:"<<endl;  
    for(i=0;i<N;i++){  
        for(j=0;j<M;j++){  
            cin>>Allocation[i][j];  
        }  
    }  
      
}  
  
//����ϵͳĿǰ������Դ���������  
void evaluate_4();  
void evaluate_3(){  
      
    int i,j;  
    Bool=1;  
    //�жϷ����Ƿ�������Ƿ��з�������������  
    for(i=0;i<N;i++){  
        for(j=0;j<M;j++){  
            if(Allocation[i][j]>Max[i][j]){  
                cout<<"���������"<<endl;  
                Bool=0;  
                break;  
            }  
        }  
    }     
    //����жϺ���   
    if(Bool==1){  
        //����ϵͳĿǰ������Դ  
        for(j=0;j<M;j++){  
            for(i=0;i<N;i++){  
                Temp[j] += Allocation[i][j];  
            }  
            Available[j] -= Temp[j];  
        }  
      
        //�õ��������  
        for(i=0;i<N;i++){  
            for(j=0;j<M;j++){  
                Need[i][j] = Max[i][j]-Allocation[i][j];  
            }  
        }  
    }  
    //����жϷ��䲻����   
    else  
        evaluate_4();  
}  
  
//��������  
void evaluate_4(){  
      
    int i,j;  
      
    cout<<"��������������̵ķ�������ֵ("<<N<<"*"<<M<<"����)[Allocation]:"<<endl;  
    for(i=0;i<N;i++){  
        for(j=0;j<M;j++){  
            cin>>Allocation[i][j];  
        }  
    }  
    //�����ж�   
    evaluate_3();  
}  
  
//��ʾ��Ϣ  
void show(){  
      
    cout<<"*************************************************************"<<endl;  
    cout<<"ϵͳĿǰ�ɷ�����Դ��Ŀ[Available]:"<<endl;  
      
    for(int i=0;i<M;i++){  
        cout<<setw(3)<<ZName[i];  
    }  
    cout<<endl;  
    for(int y=0;y<M;y++){  
        cout<<setw(3)<<Available[i];  
    }  
    cout<<endl;  
      
    cout<<"ϵͳ��ǰ����Դ����������£�"<<endl;  
    cout<<"           Max      Allocation     Need"<<endl;  
    cout<<"������ ";  
    for(int j=0;j<3;j++){  
        for(int i=0;i<M;i++)  
            cout<<setw(3)<<ZName[i];  
        cout<<"      ";  
    }  
    cout<<endl;  
    //��ӡ����  
    for(i=0;i<N;i++){  
        cout<<"  P"<<i<<"   ";  
        for(int j=0;j<M;j++)  
            cout<<setw(3)<<Max[i][j];  
        cout<<"      ";  
        for(int k=0;k<M;k++)  
            cout<<setw(3)<<Allocation[i][j];  
        cout<<"      ";  
        for(int l=0;l<M;l++)  
            cout<<setw(3)<<Need[i][j];  
        cout<<endl;  
    }  
}  
  
//�жϴ�ʱϵͳ�Ƿ��ǰ�ȫ��  
int test(){  
      
    int i,j;  
    for(j=0;j<M;j++){  
        Work[j] = Available[j];  
    }  
      
    int s=0;  
    //����ѭ����֤����N���Ų飬ʹ��ǰ�����Ų�����в�������Ľ����ܼ����ж�   
    for(int a=0;a<N;a++){  
        //i=0;  
        //����ѭ�����ƴ�0~N-1�����̵��ж�   
        for(i=0;i<N;i++){  
            //�жϽ�����Դ����״̬�Ƿ�Ϊδ���    
            if(Finish[i]==0){  
                //�ж�ÿһ����Դ�������Ƿ�С�ڿ���   
                j=0;  
                while(j<M){  
                    if(Need[i][j]<=Work[j]){  
                        //����������ʱ��˵�����Ϸ�����򣬽����Է���   
                        if(j==M-1){  
                            //������Դ  
                            for(int b=0;b<M;b++){  
                                Work[b] += Allocation[i][b];  
                            }  
                            //�޸�״̬   
                            Finish[i]=1;  
                            //��¼��ȫ˳��   
                            Security[s]=i;  
                            s++;  
                        }  
                        j++;  
                    }  
                    //ֻҪ��һ�������ܱ����㣬������   
                    else  
                        break;  
                }  
            }     
        }  
    }  
      
    Bool=1;  
    //�ж��Ƿ���û�еõ�����Ľ���  
    //����У�ʹBool��ֵ��Ϊ 0   
    for(j=0;j<N;j++){  
        if(Finish[j]==0){  
            Bool=0;  
            break;  
        }  
    }  
    //Bool=1��ʾ���н��̵�Finish������ 1 ����ϵͳ�ǰ�ȫ��   
    if(Bool==1){  
        cout<<"ϵͳ�ǰ�ȫ�ģ�"<<endl;  
            cout<<"����һ����ȫ�����ǣ�";  
            //�����ȫ����  
            for(int j=0;j<N;j++){  
                cout<<"P"<<Security[j];  
                if(j<N-1)  
                    cout<<"-->";  
            }  
            cout<<endl;  
            return Bool;  
    }  
    //Bool��=1��˵����û�еõ���Դ�Ľ��̣�ϵͳ����ȫ   
    else{  
        cout<<"ϵͳ���ǰ�ȫ�ģ�"<<endl;  
        return Bool;  
    }   
}  
  
//������Դ  
int allot(int p){  
      
    int j=0;  
    Bool=1;  
    //�ж�����ĺϷ���   
    for(j=0;j<M;j++){  
        //�ж������Ƿ��������   
        if(Request[j]>Need[p][j]){  
            Bool=0;  
            //����ʱ�� 0 ֵ���ظ���������   
            return Bool;  
            break;  
        }  
        //�ж������Ƿ���ڿ�����Դ   
        else if(Available[j]<Request[j]){  
            Bool=-1;  
            //����ʱ�� -1 ֵ���ظ���������   
            return Bool;  
            break;  
        }  
    }  
    //��Boolֵ���� 1 ��˵����������������   
    if(Bool==1){  
        for(j=0;j<M;j++){  
            Allocation[p][j] += Request[j];  
            Need[p][j] -= Request[j];  
            Available[j] -= Request[j];  
        }  
        return Bool;   
    }  
}  
  
//������Դ�������󲢼�������ĺ�����  
void bank(){  
      
    int i,j,p;  
      
    //���ݱ���  
    for(i=0;i<N;i++){  
        Available_A[i]=Available[i];  
        for(j=0;j<M;j++){  
            Allocation_A[i][j]=Allocation[i][j];  
            Need_N[i][j]=Need[i][j];  
        }  
    }  
      
    //��������  
    cout<<"������������Դ�Ľ�����:��0--"<<N-1<<"��"<<endl;  
    cin>>p;  
    cout<<"������������Դ�������:��1*"<<M<<"�ľ���"<<endl;  
    for(j=0;j<M;j++){  
        cin>>Request[j];  
    }  
      
    //���÷����㷨  
    int value_1=allot(p);  
    //������󲻺Ϸ�   
    if(value_1==0){  
        cout<<"�Ƿ�����"<<endl;  
        //�˳��ú���   
        return;   
    }  
    if(value_1==-1){  
        cout<<"ϵͳ��Դ���㡤����"<<endl;  
        //�˳��ú���   
        return;  
    }  
    //���������Ϲ淶   
    if(value_1==1){  
          
        //ִ�а�ȫ���㷨  
        int value_2=test();  
        //���ϰ�ȫ���㷨   
        if(value_2==1){  
            cout<<"��Դ�ѷ���"<<endl;  
            show();  
        }  
        //�����ϰ�ȫ���㷨   
        else{  
            cout<<"��������ϵͳ����ȫ�������з��䡣"<<endl;  
            //���ݻ�ԭ    
            for(i=0;i<N;i++){  
                Available[i]=Available_A[i];  
                for(j=0;j<M;j++){  
                    Allocation[i][j]=Allocation_A[i][j];  
                    Need[i][j]=Need_N[i][j];  
                }  
            }  
            show();   
        }     
    }  
}  
  
//������  
int main(){  
    char choice;      
    //����   
    evaluate_1();  
    evaluate_2();  
    evaluate_3();  
    //��ʾ   
    show();  
    //�ж������״̬�Ƿ�ȫ   
    test();  
    //����ѡ��     
    cout<<"*************************************************************"<<endl;  
    cout<<endl;  
    cout<<endl;  
    cout<<"\t-------------------���м��㷨��ʾ------------------"<<endl;  
    cout<<"                     R(r):�������   "<<endl;      
    cout<<"                     E(e):�˳�       "<<endl;  
    cout<<"\t---------------------------------------------------"<<endl;  
    cout<<"��ѡ��";  
    cin>>choice; 
	if(choice=='r'||choice=='R')
        bank();
	else if(choice=='e'||choice=='E')
        exit(1);
	return 0;
} 