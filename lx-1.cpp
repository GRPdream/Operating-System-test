#include<iostream>  
using namespace std;  
  
#define MAX_PEOC_ID  65536  
#define TIME_SLICE    2  
  
//���̿��ƿ�  
typedef struct PCB  
{  
    char name[10];                                      //������ id  
    char state;                                         //����״̬ W/R  
    int ArriveTime;                                     //���̵���ʱ��  
    int StartTime;                                      //���̿�ʼʱ��  
    int FinshTime;                                      //���̽���ʱ��  
    int ServiceTime;                                    //���̷���ʱ��  
    float WholeTime;                                    //��תʱ��  
    float Weight_WholeTime;                             //��Ȩ��תʱ��  
    double Average_WholeTime;                           //ƽ����תʱ��  
    double Average_Weight_WholeTime;                    //��Ȩƽ����תʱ��  
     int RunTime;                                       //�Ѿ�ռ��CPUʱ��  
     int NeedTime;                                      //��Ҫռ��CPUʱ��   
     int Prio;                                          //���ȼ�  
    struct PCB *next;  
}pcb;  
  
  
double Sum_WholeTime=0,Sum_Weight_WholeTime=0;  
int time=0;  
int Proc_Num=0;  
pcb *head = NULL;  
pcb *tail=NULL;  
  
void FCFS_RunProccess(pcb *proc)  
{  
    proc->StartTime=time;  
    cout<<"ʱ�� "<<time<<" ��ʼִ�е�ǰ��ҵ  "<<proc->name<<endl;  
    time+=proc->ServiceTime;  
    proc->state='R';  
    proc->FinshTime=time;  
    proc->WholeTime=proc->FinshTime-proc->ArriveTime;  
    proc->Weight_WholeTime=proc->WholeTime/proc->ServiceTime;  
      
    Sum_WholeTime+=proc->WholeTime;  
    Sum_Weight_WholeTime+=proc->Weight_WholeTime;  
  
    proc->Average_WholeTime=Sum_WholeTime/Proc_Num;  
    proc->Average_Weight_WholeTime=Sum_Weight_WholeTime/Proc_Num;  
	cout<<"����ʱ��:" <<proc->ArriveTime<<'\n' ;
	cout<<"��ʼʱ��:" <<proc->StartTime<<'\n' ;
	cout<<"����ʱ��:" <<proc->ServiceTime<<'\n' ;
	cout<<"���ʱ��:" <<proc->FinshTime<<'\n' ;
	cout<<"��תʱ��:" <<proc->WholeTime<<'\n' ;
	cout<<"��Ȩ��תʱ��:" <<proc->Weight_WholeTime<<'\n' ;
	cout<<"ƽ����תʱ��:" <<proc->Average_WholeTime<<'\n' ;
	cout<<"ƽ����Ȩ��תʱ��:" <<proc->Average_Weight_WholeTime<<'\n' ;
	cout<<'\n';
}  
  
void FCFS()  
{  
     pcb* cur_proc=head;  
     pcb*new_proc=NULL;  
    while(cur_proc)  
    {  
        if(cur_proc->state == 'W')  
        {  
            new_proc=cur_proc;  
            FCFS_RunProccess(new_proc);  
        }  
        cur_proc=cur_proc->next;  
        head=cur_proc;  
        free (new_proc);  
        new_proc=NULL;  
     }  
}  
  
void FCFS_CreateProccess()  
{  
    cout<<"��������̵ĸ���: ";  
    cin>>Proc_Num;  
    if(Proc_Num > MAX_PEOC_ID)  
    {  
        cout<<"sorry  I can't give you PCB \n";  
        return;  
    }  
    for(int i=1;i<=Proc_Num;++i)  
    {  
    pcb*new_proc=NULL;  
    if((new_proc=(pcb*)malloc(sizeof(pcb))) == NULL)  
        {  
            perror("malloc");  
            return;  
        }  
        cout<<"�������"<<i<<"���������� ";  
        cin>>new_proc->name;  
        cout<<"�������"<<i<<"�����̵���ʱ�䣺 ";  
        cin>>new_proc->ArriveTime;  
        cout<<"�������"<<i<<"�����̷���ʱ�䣺";  
        cin>>new_proc->ServiceTime;  
        new_proc->next=NULL;  
        if(head == NULL)  
        {  
            new_proc->next=head;  
            head=new_proc;  
            tail=head;  
            time=new_proc->ArriveTime; 
        }  
        else  
        {  
            if(head->ArriveTime>new_proc->ArriveTime)  
            {  
                new_proc->next=head;  
                head=new_proc;  
            }  
            else  
            {  
            pcb* cur_proc=head;  
            while(cur_proc->next != NULL && cur_proc->next->ArriveTime<new_proc->ArriveTime)  
            {  
                cur_proc=cur_proc->next;  
            }  
            if(cur_proc->next==NULL)  
            {  
                tail=new_proc;  
            }  
            new_proc->next=cur_proc->next;  
            cur_proc->next=new_proc;  
              
            }  
        if(new_proc->ArriveTime < time)  
            {  
                time=new_proc->ArriveTime;  
            }  
        }  
            new_proc->StartTime=0;  
            new_proc->FinshTime=0;  
            new_proc->WholeTime=0;  
            new_proc->Weight_WholeTime=0;  
            new_proc->Average_Weight_WholeTime=0;  
            new_proc->Average_WholeTime=0;  
            new_proc->state= 'W';  
            new_proc->RunTime=0;  
            new_proc->NeedTime=0;  
    }  
}  
  
  
void PrioCreateProccess()  
{  
    cout<<"��������̵ĸ���: ";  
    cin>>Proc_Num;  
    if(Proc_Num > MAX_PEOC_ID)  
    {  
        cout<<"sorry  I can't give you PCB \n";  
        return;  
    }  
    for(int i=1;i<=Proc_Num;++i)  
    {  
        pcb*new_proc=NULL;  
        if((new_proc=(pcb*)malloc(sizeof(pcb))) == NULL)  
        {  
            perror("malloc");  
            return;  
        }  
        cout<<"�������"<<i<<"���������� ";  
        cin>>new_proc->name;  
        cout<<"�������"<<i<<"�����̵���ʱ�䣺 ";  
        cin>>new_proc->ArriveTime;  
        cout<<"�������"<<i<<"�����̷���ʱ�䣺";  
        cin>>new_proc->ServiceTime;  
        cout<<"�������"<<i<<"���������ȼ�:(ֵԽС���ȼ�Խ��) ";  
        cin>>new_proc->Prio;  
        new_proc->next=NULL;  
        if(head == NULL)  
        {  
            new_proc->next=head;  
            head=new_proc;  
            tail=head;  
            time=new_proc->ArriveTime;  
              
        }  
        else  
        {  
            if(head->Prio>new_proc->Prio)  
            {  
                new_proc->next=head;  
                head=new_proc;  
            }  
            else  
            {  
                pcb* cur_proc=head;  
                while(cur_proc->next != NULL && cur_proc->next->Prio<new_proc->Prio)  
                {  
                    cur_proc=cur_proc->next;  
                }  
                if(cur_proc->next==NULL)  
                {  
                    tail=new_proc;  
                }  
                new_proc->next=cur_proc->next;  
                cur_proc->next=new_proc;  
                  
            }  
            if(new_proc->ArriveTime < time)  
            {  
                time=new_proc->ArriveTime;  
            }  
        }  
        new_proc->StartTime=0;  
        new_proc->FinshTime=0;  
        new_proc->WholeTime=0;  
        new_proc->Weight_WholeTime=0;  
        new_proc->Average_Weight_WholeTime=0;  
        new_proc->Average_WholeTime=0;  
        new_proc->state= 'W';  
        new_proc->RunTime=0;  
        new_proc->NeedTime=0;  
    }  
}  
void  RR_RunProccess(PCB *proc)  
{  
    proc->StartTime=time;  
    cout<<"ʱ�� "<<time<<" ��ʼִ�е�ǰ��ҵ  "<<proc->name<<endl;  
    proc->RunTime+=TIME_SLICE;  
    time+=TIME_SLICE;  
    proc->NeedTime=proc->ServiceTime-proc->RunTime;  
    if(proc->NeedTime <=0)  
    {  
        cout<<"ʱ�� "<<time<<" ������ҵ  "<<proc->name<<endl;  
            head=proc->next;  
            free(proc);  
            proc=NULL;  
            if(head==NULL)  
            {  
                tail=head;  
            }  
    }  
    else  
    {  
        cout<<"ʱ�� "<<time<<" ������ҵ  "<<proc->name<<endl;  
        cout<<"�Ѿ�������"<<proc->RunTime<<"�뻹��Ҫִ��"<<proc->NeedTime<<"��"<<endl;  
        if(proc->next != NULL)  
        {  
        head=proc->next;  
        proc->next=NULL;  
        tail->next=proc;  
        tail=proc;  
        }  
    }  
        
}  
  
void RoundRobin()  
{  
    pcb* cur_proc=head;  
    pcb* new_proc=NULL;  
    while(cur_proc)  
    {  
        if(cur_proc->state == 'W')  
        {  
            new_proc=cur_proc;  
            RR_RunProccess(new_proc);  
        }  
        cur_proc=head;  
    }  
}  
  
 
void main()  
{  
    int select=1;  
    while(select)  
    {  
        cout<<"1.�����ȷ����㷨\n";  
        cout<<"2.ʱ��Ƭ��ת\n";   
        cout<<"3.���ȼ�����\n";  
    cout<<"��ѡ��:> ";  
    cin>>select;  
    switch(select)  
    {  
    case 1:  
        FCFS_CreateProccess();  
        FCFS();  
        break;  
    case 2:  
        FCFS_CreateProccess();  
        RoundRobin();  
        break;  
    case 3:  
        PrioCreateProccess();  
        FCFS();  
        break;    
    default:  
        break;  
    }  
    }  
}