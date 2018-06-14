#include <iostream>  
#include <time.h>  
#include <vector>  
#include <math.h>  
#include <stdlib.h>  
#include <algorithm>  
#include <cstring>  
#include <windows.h>  
#include <fstream>  
using namespace std;  
  
int position = 0;      //��ǰ�ŵ�λ��  
int dis = 0;  
double average_distance = 0;  
  
void request(vector<int>&m_vec,ofstream &outfile){  
    cout<<"������ɴ������У�"<<endl;  
    int n = 0;  
    srand(time(NULL));     //������������  
    n = rand() % 20 + 1;  
    int temp = 0;  
    for(int i=0;i<n;i++){  
        temp = rand() % 100;  
        m_vec.push_back(temp);  
        cout<<temp<<" ";  
        outfile<<temp<<endl;  
    }  
    cout<<endl;  
    position = rand() % 100;  
    cout<<"��ǰ�ŵ���"<<position<<endl;  
}  
  
void compute_dis(vector<int>m_vec,int &dis,double &average_distance){  
    average_distance = (double)dis / (double)m_vec.size();  
}  
  
void FIFO(vector<int>m_vec,int position){     //�����ȷ����㷨  
    dis = 0;  
    average_distance = 0;  
    for(vector<int>::iterator it=m_vec.begin();it!=m_vec.end();it++){  
        dis += abs(position-*it);  
        Sleep(500);  
        cout<<"->"<<*it;  
        position = *it;  
    }  
    compute_dis(m_vec,dis,average_distance);  
}  
  
void SSTF(vector<int>m_vec,int position){   //���Ѱ��ʱ���㷨  
    dis = 0;  
    average_distance = 0;  
    sort(m_vec.begin(),m_vec.end());    //��С��������  
    int i = 0;  
    for(vector<int>::iterator it=m_vec.begin();it!=m_vec.end();it++){  
        if(position >= *it)  
            i++;  
    }  
    int count = 0;  
    int left = i-1;  
    int right = i;  
    while(count<m_vec.size()){  
        if((left >=0 && abs(m_vec[right]-position) > abs(m_vec[left]-position)) || right>=m_vec.size()){  
            dis += abs(m_vec[left]-position);  
            Sleep(500);  
            cout<<"->"<<m_vec[left];  
            position = m_vec[left];  
            left--;  
        }  
        else{  
            dis += abs(m_vec[right]-position);  
            Sleep(500);  
            cout<<"->"<<m_vec[right];  
            position = m_vec[right];  
            right++;  
        }  
        count++;  
    }  
    compute_dis(m_vec,dis,average_distance);  
}  
  
void SCAN(vector<int>m_vec,int position){   //���ݵ����㷨  
    dis = 0;  
    average_distance = 0;  
    sort(m_vec.begin(),m_vec.end());    //��С��������  
    int i = 0;  
    for(vector<int>::iterator it=m_vec.begin();it!=m_vec.end();it++){  
        if(position >= *it)  
            i++;      //�ҵ�position���ڵĴŵ�  
    }  
    int left = i - 1;   //�ȴ��⵽��ɨ��  
    int right = i;  
    while(left >= 0){  
        dis += abs(position - m_vec[left]);  
        Sleep(500);  
        cout<<"->"<<m_vec[left];  
        position = m_vec[left];  
        left --;  
    }  
    while(right < m_vec.size()){  
        dis += abs(position - m_vec[right]);  
        Sleep(500);  
        cout<<"->"<<m_vec[right];  
        position = m_vec[right];  
        right ++;  
    }  
    compute_dis(m_vec,dis,average_distance);  
}  
  
void CSCAN(vector<int>m_vec,int position){   //ѭ��ɨ���㷨  
    dis = 0;  
    average_distance = 0;  
    sort(m_vec.begin(),m_vec.end());    //��С��������  
    int i = 0;  
    for(vector<int>::iterator it=m_vec.begin();it!=m_vec.end();it++){  
        if(position >= *it)  
            i++;      //�ҵ�position���ڵĴŵ�  
    }  
    int left = i - 1;   //�ȴ��⵽��ɨ��  
    int right = i;  
    while(left >= 0){  
        dis += abs(position - m_vec[left]);  
        Sleep(500);  
        cout<<"->"<<m_vec[left];  
        position = m_vec[left];  
        left --;  
    }  
    position = 100;     //�����������Ĵŵ�  
    int len = m_vec.size()-1;  
    while(len >= right){  
        dis += abs(position - m_vec[len]);  
        Sleep(500);  
        cout<<"->"<<m_vec[len];  
        position = m_vec[len];  
        len --;  
    }  
    compute_dis(m_vec,dis,average_distance);  
}  
  
void FSCAN(vector<int>m_vec,int position){   //�ֲ����ݵ����㷨��������������  
    dis = 0;  
    average_distance = 0;  
    //SCAN(m_vec,position);  
    sort(m_vec.begin(),m_vec.end());    //��С��������  
    int i = 0;  
    for(vector<int>::iterator it=m_vec.begin();it!=m_vec.end();it++){  
        if(position >= *it)  
            i++;      //�ҵ�position���ڵĴŵ�  
    }  
    int left = i - 1;   //�ȴ��⵽��ɨ��  
    int right = i;  
    while(left >= 0){  
        dis += abs(position - m_vec[left]);  
        Sleep(500);  
        cout<<"->"<<m_vec[left];  
        position = m_vec[left];  
        left --;  
    }  
    while(right < m_vec.size()){  
        dis += abs(position - m_vec[right]);  
        Sleep(500);  
        cout<<"->"<<m_vec[right];  
        position = m_vec[right];  
        right ++;  
    }  
    cout<<endl;  
    cout<<"��ɨ��Ĺ������²����ķ������У�"<<endl;  
    vector<int>ve;  
    while(!ve.empty())  
        ve.pop_back();  
    int n = 0;  
    n = rand() % 20 + 1;  
    int temp = 0;  
    for(i=0;i<n;i++){  
        temp = rand() % 100;  
        cout<<temp<<"��";  
        ve.push_back(temp);  
    }  
    cout<<endl;  
    cout<<position;  
    SCAN(ve,position);  
    average_distance = (double)dis / (double)(m_vec.size()+ve.size());  
}  
  
void print(){  
    cout<<endl<<endl;  
    cout<<"�����㣬��ͷ�ƶ����ܾ���Ϊ:"<<dis<<endl;  
    cout<<"��ͷƽ���ƶ�����:"<<average_distance<<endl;  
    cout<<endl<<endl;  
}  
  
int choose_algorithm(vector<int>m_vec){  
    cout<<endl<<endl;  
    cout<<"��ʵ����õĵ����㷨������5�֣�"<<endl;  
    cout<<"1.FIFO  2.SSTF  3.SCAN  4.CSCAN  5.FSCAN  6.���������еĵ���  7.��������"<<endl;  
    int choice = 0;  
    cout<<"ѡ��"<<endl;  
    cin>>choice;  
    cout<<endl;  
    while(choice!=6 && choice!=7){  
        cout<<"��������ķ���״����"<<endl;  
        cout<<position;  
        switch(choice){  
            case 1:  
                FIFO(m_vec,position);break;  
            case 2:  
                SSTF(m_vec,position);break;  
            case 3:  
                SCAN(m_vec,position);break;  
            case 4:  
                CSCAN(m_vec,position);break;  
            case 5:  
                FSCAN(m_vec,position);break;  
            default:  
                cout<<"******�Ƿ����룡******"<<endl<<endl;break;   
        }   
        if(choice<=7 && choice>=1)   
            print();  
        cout<<"ѡ��"<<endl;  
        cin>>choice;  
    }  
    if(choice == 7)  
        return 0;  
    else  
        cout<<endl<<endl;  
    return 1;  
}  
  
int main(){  
    cout<<"---------------���̵����㷨ģ��ʵ��-----------------"<<endl;  
    ofstream outfile;  
    outfile.open("data.txt");  
    while(1){  
        vector<int> vec;  
        while(!vec.empty())  
            vec.pop_back();  
        request(vec,outfile);         //�����������   
        int flag = choose_algorithm(vec);  
        if(flag == 0)  
            break;  
    }   
    outfile.close();  
    return 0;  
}