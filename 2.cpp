#include <malloc.h>//malloc()��
#include <stdio.h>//EOF(=^Z��F6),NULL
#include <process.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;
#define LIST_INIT_SIZE 10
#define LISTINCREMENT 10


typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;

Status InitList(SqList &L);
Status ListTraverse_Sq(SqList L,void(*visit)(ElemType));
Status ListInsert_Sq(SqList& L,int i,ElemType e);
Status ListDelete_Sq(SqList& L,int i,ElemType &e);
Status LocateElem(SqList L,int e);
void Merge(SqList La,SqList Lb,SqList &Lc);

//�������Ա�
Status InitList(SqList& L){

	if(!L.elem)
		exit(OVERFLOW);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	 return OK;
}

Status InitList(SqList& L,ElemType *elem){

	if(!L.elem)
		exit(OVERFLOW);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	for(int i=0;i<(sizeof(elem)/sizeof(elem[0]));i++)
    {
        L.elem[i] = elem[i];
        L.length++;
    }
	 return OK;
}
//����
Status ListTraverse_Sq(SqList L,void(*visit)(ElemType)){
	int i=0;
	for(i=0;i<L.length;i++)
		(*visit)(L.elem[i]);

}


void VISIT(ElemType e){
	printf("%d ",e);
}


//����
Status ListInsert_Sq(SqList &L,int i,ElemType e){
	int *newbase,*q,*p;
	if(i<1||i>L.length+1) return ERROR;
	if(L.length>=L.listsize){
	 newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
	 if(!newbase)exit(OVERFLOW);
	 L.elem=newbase;
	 L.listsize+=LISTINCREMENT;
	}
	q=&(L.elem[i-1]);
	for(p=&L.elem[L.length-1];p>=q-1;*(p+1)=*p){
	 *q=e;
	 ++L.length;
	 return OK;
	}
}


//ɾ��
Status ListDelete_Sq(SqList &L,int i,ElemType &e){
	int *p,*q;
	if(i<1||i>L.length+1) return ERROR;
	p=&(L.elem[-1]);
	e=*p;
	q=L.elem+L.length-1;
	for(++p;p<=q;++p)*(p-1)=*p;
	 --L.length;
	 return OK;
}



//����
/*Status LocateElem_Sq(SqList L,ElemType e,Status(*compare)(ElemType,ElemType)){
	int i,*p;
	i=1;
	p=L.elem;
	while(i<=L.length &&!(* compare)(*p++,e)) ++i;
	if(i<=L.length) return i;
	else return 0;
}*/
Status LocateElem(SqList L,int e){
	int i;
	printf("������ҵ�Ԫ�أ�");
	scanf("%d",&e);
	for(i=0;i<L.length;i++)	{
		if(L.elem[i]==e)
			printf("���ҳɹ�������Ԫ��Ϊ%d",L.elem[i]);
	}
	printf("����ʧ��");
	printf("\n");
}

//�ϲ�
void Merge(SqList La,SqList Lb,SqList &Lc){
	int *pa,*pb,*pc,*pa_last,*pb_last;
	pa=La.elem;pa=Lb.elem;
	Lc.listsize=Lc.length=La.length+Lb.length;
	pc=Lc.elem=(ElemType *)malloc(Lc.listsize*sizeof(ElemType));
	//if(!Lc.elem)
	 //return ERROR;
	pa_last=La.elem+La.length-1;
	pb_last=Lb.elem+Lb.length-1;
	while(pa<=pa_last && pb<=pb_last){
	 if(*pa<=*pb) *pc++=*pa++;
	 else *pc++=*pb++;
	}
	while(pa<=pa_last) *pc++=*pa++;
	while(pb<=pb_last) *pc++=*pb++;
}

void DestroyList(SqList &L){
	 free (&L);
 }

 int main()
{
	SqList La,Lb,Lc;
    ElemType a[]={25,12,78,34,100,88};
	ElemType e;
	Status i;
	int j;

	//1.����InitList
	printf("��ʼ��˳���La��Lb......\n");
	i=InitList(La,a);
	printf("��ʼ��La��La.elem=%u La.length=%d La.listsize=%d\n",La.elem[0],La.length,La.listsize);
	i=InitList(Lb,a);
	printf("��ʼ��Lb��Lb.elem=%u Lb.length=%d Lb.listsize=%d\n",Lb.elem[0],Lb.length,Lb.listsize);

	//2.����˳���
	printf("����˳���....\n");
	ListTraverse_Sq(La,VISIT);

	//3.����ListInsert,�ڱ�ͷλ�ò���������Ԫ��
	printf("����ListInsert,�ڱ�ͷ����������Ԫ��....\n");
	printf("����Ҫ���������");
	scanf("%d",&e) ;
	i=ListInsert_Sq(La,1,e);
	printf("����������Ԫ�غ�,˳���Ϊ��");
	ListTraverse_Sq(La,VISIT);

	//4.����ListDelete
	printf("����ListDelete...\n");
	ListDelete_Sq(La,i,e);

	//5.����LocateElem
	printf("����LocateElem....\n");
	printf("����Ҫ���ҵ�����");
	scanf("%d",&j) ;
	LocateElem(La,j);

	//6.�ϲ�˳���
	printf("�ϲ���˳���...\n");
	Merge(La,Lb,Lc);
	ListTraverse_Sq(Lc,VISIT);



	//����DestroyList
	DestroyList(La);
	printf("����La��La.elem=%u La.length=%d La.listsize=%d\n",La.elem,La.length,La.listsize);
	DestroyList(Lb);
	printf("����Lb��Lb.elem=%u Lb.length=%d Lb.listsize=%d\n",Lb.elem,Lb.length,Lb.listsize);
	return 0;
}










