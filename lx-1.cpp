#include<iostream>  
using namespace std;  
  
#define MAX_PEOC_ID  65536  
#define TIME_SLICE    2  
  
//进程控制块  
typedef struct PCB  
{  
    char name[10];                                      //进程名 id  
    char state;                                         //进程状态 W/R  
    int ArriveTime;                                     //进程到达时间  
    int StartTime;                                      //进程开始时间  
    int FinshTime;                                      //进程结束时间  
    int ServiceTime;                                    //进程服务时间  
    float WholeTime;                                    //周转时间  
    float Weight_WholeTime;                             //带权周转时间  
    double Average_WholeTime;                           //平均周转时间  
    double Average_Weight_WholeTime;                    //带权平均周转时间  
     int RunTime;                                       //已经占用CPU时间  
     int NeedTime;                                      //还要占用CPU时间   
     int Prio;                                          //优先级  
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
    cout<<"时刻 "<<time<<" 开始执行当前作业  "<<proc->name<<endl;  
    time+=proc->ServiceTime;  
    proc->state='R';  
    proc->FinshTime=time;  
    proc->WholeTime=proc->FinshTime-proc->ArriveTime;  
    proc->Weight_WholeTime=proc->WholeTime/proc->ServiceTime;  
      
    Sum_WholeTime+=proc->WholeTime;  
    Sum_Weight_WholeTime+=proc->Weight_WholeTime;  
  
    proc->Average_WholeTime=Sum_WholeTime/Proc_Num;  
    proc->Average_Weight_WholeTime=Sum_Weight_WholeTime/Proc_Num;  
	cout<<"到达时间:" <<proc->ArriveTime<<'\n' ;
	cout<<"开始时间:" <<proc->StartTime<<'\n' ;
	cout<<"服务时间:" <<proc->ServiceTime<<'\n' ;
	cout<<"完成时间:" <<proc->FinshTime<<'\n' ;
	cout<<"周转时间:" <<proc->WholeTime<<'\n' ;
	cout<<"带权周转时间:" <<proc->Weight_WholeTime<<'\n' ;
	cout<<"平均周转时间:" <<proc->Average_WholeTime<<'\n' ;
	cout<<"平均带权周转时间:" <<proc->Average_Weight_WholeTime<<'\n' ;
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
    cout<<"请输入进程的个数: ";  
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
        cout<<"请输入第"<<i<<"个进程名： ";  
        cin>>new_proc->name;  
        cout<<"请输入第"<<i<<"个进程到达时间： ";  
        cin>>new_proc->ArriveTime;  
        cout<<"请输入第"<<i<<"个进程服务时间：";  
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
    cout<<"请输入进程的个数: ";  
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
        cout<<"请输入第"<<i<<"个进程名： ";  
        cin>>new_proc->name;  
        cout<<"请输入第"<<i<<"个进程到达时间： ";  
        cin>>new_proc->ArriveTime;  
        cout<<"请输入第"<<i<<"个进程服务时间：";  
        cin>>new_proc->ServiceTime;  
        cout<<"请输入第"<<i<<"个进程优先级:(值越小优先级越高) ";  
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
    cout<<"时刻 "<<time<<" 开始执行当前作业  "<<proc->name<<endl;  
    proc->RunTime+=TIME_SLICE;  
    time+=TIME_SLICE;  
    proc->NeedTime=proc->ServiceTime-proc->RunTime;  
    if(proc->NeedTime <=0)  
    {  
        cout<<"时刻 "<<time<<" 结束作业  "<<proc->name<<endl;  
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
        cout<<"时刻 "<<time<<" 挂起作业  "<<proc->name<<endl;  
        cout<<"已经运行了"<<proc->RunTime<<"秒还需要执行"<<proc->NeedTime<<"秒"<<endl;  
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
        cout<<"1.先来先服务算法\n";  
        cout<<"2.时间片轮转\n";   
        cout<<"3.优先级调度\n";  
    cout<<"请选择:> ";  
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