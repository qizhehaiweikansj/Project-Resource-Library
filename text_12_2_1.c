#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//学生管理
int st;
struct stu* arr;
//函数返回值为结构体指针
struct stu
{
    char name[20];
    //名字
    char gender[15];
    //性别
    int age;
    //年龄
    long long identity_card;
    //身份证
    long long telephone_number;
    //电话
    char Faculties[50];
    //院系
};

void meau();

// 查找相关函数声明
void liu();
void name();
void id();
void phone();
void find();

int com_stu_name(const void* e1, const void* e2);

int com_stu_age(const void* e1, const void* e2);

int com_stu_id(const void* e1, const void* e2);

int com_stu_phone(const void* e1, const void* e2);

int com_stu_faculties(const void* e1, const void* e2);

void clean();

struct stu* Student_structure(const int* pr);

void stu(int *i);

void pri(int *i);

void print();

void create();

void Single();

void host();

void revise();

void sort();

void meau()
{
    printf("*******学生信息管理*******\n");
    printf("*********0:退出**********\n");
    printf("*********1:查找**********\n");
    printf("*********2:输入**********\n");
    printf("*********3:修改**********\n");
    printf("*********4:打印**********\n");
    printf("*********5:排序**********\n");
}
int com_stu_name(const void* e1,const void* e2)
//qsort函数要的函数指针
{
    return strcmp(((struct stu*)e1)->name,((struct stu*)e2)->name);
}
int com_stu_age(const void* e1,const void* e2)
{
    return ((struct stu*)e1)->age-((struct stu*)e2)->age;
}

int com_stu_id(const void* e1,const void* e2)
{
    return ((struct stu*)e1)->identity_card-((struct stu*)e2)->identity_card;
}

int com_stu_phone(const void* e1,const void* e2)
{
    return ((struct stu*)e1)->telephone_number-((struct stu*)e2)->telephone_number;
}

int com_stu_faculties(const void* e1,const void* e2)
{
    return strcmp(((struct stu*)e1)->Faculties,((struct stu*)e2)->Faculties);
}


void clean()
//清空输入垃圾
{
    while (getchar()!= '\n') 
    {
        ;
    }
}

struct stu*Student_structure(const int* pr)
//创建结构体指针动态分配
{
    if (pr == NULL) 
    {
        printf("传入指针为空！\n");
        return NULL;
    }
    else if (*pr <= 0) 
    {
        printf("传入的数组大小值不合理！\n");
        return NULL;
    }
    struct stu *arr = (struct stu *)malloc((*pr) * sizeof(struct stu));
    if (arr == NULL) 
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    return arr;
}
void stu(int *i)
//输入函数
{
    printf("请输入第%d个人的信息：\n",*i+1);
    printf("请输入姓名：->\n");
    scanf("%s",arr[*i].name);
    clean();
    printf("请输入性别：->\n");
    scanf("%s",arr[*i].gender);
    clean();
    printf("请输入年龄：->\n");
    scanf("%d",&arr[*i].age);
    clean();
    printf("请输入身份证：->\n");
    scanf("%lld",&arr[*i].identity_card);
    for(int j=0;j<*i;j++)
    {
        if(arr[*i].identity_card==arr[j].identity_card)
        {
            printf("身份证和第%d人重复！请重新输入！\n",j+1);
            clean();
            break;
        }
    }
    clean();
    printf("请输入电话：->\n");
    scanf("%lld",&arr[*i].telephone_number);
    clean();
    printf("请输入院系：->\n");
    scanf("%s",arr[*i].Faculties);
    clean();
}

void pri(int*i)
//打印函数
{
    printf("第%d个人的信息：\n",i+1);
    printf("姓名：%s ",arr[*i].name);
    printf("性别：%s ",arr[*i].gender);
    printf("年龄：%d ",arr[*i].age);
    printf("身份证：%lld ",arr[*i].identity_card);
    printf("电话：%lld ",arr[*i].telephone_number);
    printf("院系：%s ",arr[*i].Faculties);
    printf("\n");
}

void print()
//打印主函数
{
    if (st <= 0)
    {
        create();
    }
    else
    {
        for(int i=0;i<st;i++)
        {
            pri(&i);
        }
        printf("打印完毕！\n");
    }
    
}

void liu()
//查找函数
{
    printf("请输入查找的人的特征：->\n");
    printf("1.姓名\n");
    printf("2.身份证\n");
    printf("3.电话\n");
}

void name()
//查找姓名函数
{
    char name[30];
    printf("请输入姓名：->\n");
    scanf("%s",name);
    clean();
    for(int i=0;i<st;i++)
    {
        if(strcmp(arr[i].name,name)==0)
        {
            pri(&i);
        }
    }
}
void id()
//查找身份证函数
{
    long long id;
    printf("请输入身份证：->\n");
    scanf("%lld",&id);
    clean();
    for(int i=0;i<st;i++)
    {
        if(arr[i].identity_card==id)
        {
            pri(&i);
        }
    }
}
void phone()
//查找电话函数
{
    long long phone;
    printf("请输入电话：->\n");
    scanf("%lld",&phone);
    clean();
    for(int i=0;i<st;i++)
    {
        if(arr[i].telephone_number==phone)
        {
            pri(&i);
        }
    }
}

void find()
//查找主函数
{
    wa:
    if (st <= 0)
    {
        create();
    }
    else
    {
        liu();
        int choice;
        if(scanf("%d",&choice)!=EOF && choice > 0)
        {
            switch (choice)
            {
                case 1:
                    name();
                    break;
                case 2:
                    id();
                    break;
                case 3:
                    phone();
                    break;
                default:
                    printf("输入非法！\n");
                    break;
            }
        }
        else
        {
            printf("输入错误！\n");
            clean();
            goto wa;
        }
    }
}
void create()
//创建函数
{
    printf("未输入信息！\n");
    printf("2秒后进入学生创建！\n");
    Sleep(2000);
    host();
}
void Single()
//修改函数
{
    printf("请输入你要修改的人的序号：->\n");
        int i;
        if(scanf("%d",&i)!=EOF && i > 0)
        {
            printf("请输入你要修改的信息：\n");
            printf("0.退出\n");
            printf("1.姓名\n");
            printf("2.性别\n");
            printf("3.年龄\n");
            printf("4.身份证\n");
            printf("5.电话\n");
            printf("6.院系\n");
            int choice;
            if(scanf("%d",&choice)!=EOF && choice > 0)
            {
                switch (choice)
                {
                    case 0:
                        break;
                    case 1:
                        clean();
                        printf("请输入姓名：->\n");
                        scanf("%s",arr[i-1].name);
                        break;
                    case 2:
                        clean();
                        printf("请输入性别：->\n");
                        scanf("%s",arr[i-1].gender);
                        break;
                    case 3:
                        clean();
                        printf("请输入年龄：->\n");
                        scanf("%d",&arr[i-1].age);
                        break;
                    case 4:
                        clean();
                        printf("请输入身份证：->\n");
                        scanf("%lld",&arr[i-1].identity_card);
                        break;
                    case 5:
                        clean();
                        printf("请输入电话：->\n");
                        scanf("%lld",&arr[i-1].telephone_number);
                        break;
                    case 6:
                        clean();
                        printf("请输入院系：->\n");
                        scanf("%s",arr[i-1].Faculties);
                        break;
                    default:
                        printf("输入非法！\n");
                        break;
                }
            }
        }
        else
        {
            printf("输入错误！\n");
            clean();
        }
}

void host()
//输入主函数
{
    while(1)
    {
        printf("请输入人数：->\n");
        if(scanf("%d",&st)==1)
        {
            if (st <= 0)
            {
                printf("输入的人数必须是正整数，请重新输入！\n");
                clean();
                break;
            }
            else
            {
                struct stu* arr1 =Student_structure(&st);
                arr=arr1;
                for(int i=0;i<st;i++)
                {
                    stu(&i);
                }
                printf("输入完毕！\n");
                break;
            }
        }
        else
        {
            printf("未读取到字符！\n2秒后从新输入！\n");
            clean();
            Sleep(2000);
            
        }
    }
}

void revise()
//修改主函数
{
    if (st <= 0)
    {
        create();
    }
    else
    {
        int l =0;
        printf("改一项还是多项？\n");
        printf("1.改一项\n");
        printf("2.改多项\n");
        printf("请输入：->\n");
        scanf("%d",&l);
        switch (l)
        {
        case 1:
            Single();
            break;
        case 2:
            printf("请输入你要修改的人排名数：->\n");
            int num;
            if(scanf("%d",&num)!=EOF && num > 0)
            {
                for(int i=0;i<num;i++)
                {
                    stu(&i);
                }
            }
            else
            {
                printf("输入错误！\n");
                clean();
            }
            break;
        default:
            break;
        }

    }
}

void sort()
//排序主函数
{
    if (st <= 0)
    {
        create();
    }
    else
    {
        printf("请输入你要排序的特征：\n");
        printf("1.姓名\n");
        printf("2.年龄\n");
        printf("3.身份证\n");
        printf("4.电话\n");
        printf("5.院系\n");
        int choice;
        if(scanf("%d",&choice)!=EOF && choice > 0)
        {
            switch (choice)
            {
                case 1:
                    qsort(arr,st,sizeof(struct stu),com_stu_name);
                    //qsort库函数，排序函数，第一个参数是要排序的数组
                    //第二个参数是数组的元素个数
                    //第三个参数是每个元素的大小
                    //第四个参数是比较函数的指针地址
                    print();
                    break;
                case 2:
                    qsort(arr,st,sizeof(struct stu),com_stu_age);
                    print();
                    //输出函数
                    break;
                case 3:
                    qsort(arr,st,sizeof(struct stu),com_stu_id);
                    print();
                    break;
                case 4:
                    qsort(arr,st,sizeof(struct stu),com_stu_phone);
                    print();
                    break;
                case 5:
                    qsort(arr,st,sizeof(struct stu),com_stu_faculties);
                    print();
                    break;
                default:
                    printf("输入非法！\n");
                    break;
            }
        }
    }
}

int main()
{
    int input;
    SetConsoleOutputCP(CP_UTF8);
    //设置控制台打印编码为UTF-8
    while (1)
    {
        meau();
        printf("请输入：->\n");
        if(scanf("%d",&input)!=EOF && input > 0)
        {
            switch (input)
            {
                case 0:
                    break;
                case 1:
                    find();
                    break;
                case 2:
                    host();
                    break;
                case 3:
                    revise();
                    break;
                case 4:
                    print();
                    //打印函数
                    break;
                case 5:
                    sort();
                    break;
                default:
                    printf("输入错误！请重新输入！");
                    clean();
            }
        }
        else
        {
            printf("未读取到字符！\n");
            Sleep(1000);//延时
            printf("请重新输入\n");
            clean();
        }
    }
    printf("\n按任意键退出！\n");
    free(arr);
    system("pause");
    return 0;
}