#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;

#define PROCESS_NAME_LEN 32 //进程名最大长度
#define MIN_SLICE 10 //内碎片最大大小
#define DEFAULT_MEM_SIZE 1024  //总内存大小
#define DEFAULT_MEM_START 0  //内存开始分配时的起始地址

typedef pair<int, string> My_algo;
int algo = 0;
int mem_size = DEFAULT_MEM_SIZE;
bool flag = 0; //当内存以及被分配了之后，不允许更改总内存大小的flag
static int pid = 0;

struct free_block {    //空闲数据块
    int size;
    int start_addr;
    struct free_block *next;
};

struct allocated_block { //已分配的数据块
    int pid;
    int size;
    int start_addr;
    char process_name[PROCESS_NAME_LEN];
    int *data;
    struct allocated_block *next;
};

struct NewReturnValue {
    int straddr;
    int size;
};

free_block *free_block_head; //空闲数据块首指针
allocated_block *allocated_block_head = NULL; //分配块首指针

allocated_block *find_process(int id); //寻找pid为id的分配块
free_block *init_free_block(int mem_size); //空闲块初始化
void display_menu(); //显示选项菜单
void set_mem_size(); //设置内存大小
int allocate_mem(allocated_block *ab); //为制定块分配内存
void rearrange(); // 对块进行重新分配
int create_new_process(); //创建新的进程
int free_mem(allocated_block *ab); //释放分配块
void swap(int *p, int *q); //交换地址
int dispose(allocated_block *ab); //释放分配块结构体
void display_mem_usage(); //显示内存情况
void kill_process(); //杀死对应进程并释放其空间与结构体
void Usemy_algo(int id); //使用对应的分配算法
void clear();

//主函数
int main() {
    int op;
    pid = 0;
    free_block_head = init_free_block(mem_size); //初始化一个可以使用的内存块，类似与操作系统可用的总存储空间
    for (;;) {
        display_menu();
        float temp;
        fflush(stdin);
        scanf("%f", &temp);
        clear();
        op = (int)temp;
        switch (op) {
            case 1: {
                set_mem_size();
                break;
            }
            case 2: {
                puts("Please choose the algorithms\n");
                printf("0\tFirst fit\n1\tBest fit\n2\tWorse fit\n");
                scanf("%d", &algo);
                clear();
                if (!(algo == 0 || algo == 1 || algo == 2)) {
                    puts("Invalid Input!\n");
                    algo = 0;
                }
                break;
            }
            case 3: {
                create_new_process();
                break;
            }
            case 4: {
                kill_process();
                break;
            }
            case 5: {
                display_mem_usage();
                break;
            }
            case 233: {
                puts("bye....");
                return 0;
            }
            default:
                break;
        }
    }
}

void clear(){
    int c;
    int flo = 0;
    while((c = getchar()) != '\n' && c != EOF){
        if(flo == 0){
            puts("Invalid Input!\n");
            flo = 1;
        }
    }
}

allocated_block *find_process(int id) { //循环遍历分配块链表，寻找pid=id的进程所对应的块
    allocated_block *finding = allocated_block_head; //分配块首指针
    while (finding != NULL) {
        if (finding->pid == id) {
            break;
        }
        finding = finding->next;
    }
    return finding;
}

free_block *init_free_block(int mem_size) { //初始化空闲块，这里的mem_size表示允许的最大虚拟内存大小
    free_block *p;
    p = (free_block *) malloc(sizeof(free_block));
    if (p == NULL) {
        puts("No memory left");
        return NULL;
    }
    p->size = mem_size;
    p->start_addr = DEFAULT_MEM_START;
    p->next = NULL;
    return p;
}

void display_menu() {
    puts("\n\n******************menu*******************");
    printf("1) Set memory size (default = %d)\n", DEFAULT_MEM_SIZE);
    printf("2) Set memory allocation algorithm\n");
    printf("3) Create a new process\n");
    printf("4) Kill a process\n");
    printf("5) Display memory usage\n");
    printf("233) Exit\n");
}

void set_mem_size() { //更改最大内存大小
    if (flag == 1) {
        printf("Memory had been allocation. Cannot change size!");
    } else {
        int op;
        printf("Input the size you want to set:");
        fflush(stdin);
        float temp;
        scanf("%f", &temp);
        clear();
        op = (int)temp;
        if (op <= 0) {
            puts("\nInvalid input!");
            return;
        }
        mem_size = op;
        free_block_head->size = mem_size;
    }
}

int allocate_mem(allocated_block *ab) { //为块分配内存，真正的操作系统会在这里进行置换等操作
    allocated_block *pointer = allocated_block_head;
    // 没有分配的情况下
    if (pointer == NULL) {
        allocated_block_head = ab;
        return 0;
    }
    //从头分配的情况下
    if (ab->start_addr == 0) {
        allocated_block_head = ab;
        allocated_block_head->next = pointer;
        return 0;
    }

    while (pointer != NULL) {
        if (pointer->start_addr <= ab->start_addr) {
            if (pointer->next == NULL) {
                pointer->next = ab;
                ab->next = NULL;
                break;
            } else if (pointer->next->start_addr >= ab->start_addr) {
                ab->next = pointer->next;
                pointer->next = ab;
                break;
            }
        }
        pointer = pointer->next;
    }

}

struct NewReturnValue usingAlgorithm(free_block *freeBlock, int op) {
    NewReturnValue newReturnValue = NewReturnValue{-1, -1};
    free_block *freeBlockBefore = free_block_head;
    if (algo == 0) {
        while (freeBlock != NULL) {
            if (freeBlock->size >= op)
                break;
            freeBlockBefore = freeBlock;
            freeBlock = freeBlock->next;
        }
    } else {
        free_block *pointer = free_block_head;
        freeBlock = NULL;
        while (pointer != NULL) {
            int comsize = pointer->size;
            if (comsize >= op) {
                if (freeBlock == NULL) {
                    freeBlock = pointer;
                    continue;
                }
                if ((algo == 1 && freeBlock->size >= comsize) || (algo == 2 && freeBlock->size <= comsize))
                    freeBlock = pointer;
                freeBlockBefore = pointer;
                pointer = pointer->next;
            }
        }
    }
    if (freeBlock == NULL) {
        return newReturnValue;
    }
    newReturnValue.straddr = freeBlock->start_addr;
    freeBlock->start_addr += op;
    freeBlock->size -= op;

    newReturnValue.size = op;
    if (freeBlock->size <= 10) {
        newReturnValue.size += freeBlock->size;
        freeBlock->size = 0;
    }

    if (freeBlock->size == 0) {
        if (freeBlockBefore == freeBlock) {
            free_block_head = NULL;
        } else
            freeBlockBefore->next = freeBlock->next;
        free(freeBlock);
    }
    return newReturnValue;
}

int create_new_process() { //创建新进程
    int op;
    printf("Input the size of the new process:");
    float temp;
    scanf("%f", &temp);
    clear();
    fflush(stdin);
    op = (int)temp;
    if (op <= 0) {
        puts("\nInvalid input!");
        return 1;
    }
    free_block *freeBlock = free_block_head;
    NewReturnValue addr = usingAlgorithm(freeBlock, op);
    if (addr.size == -1) {
        puts("\nNo enough memory space!");
        return 1;
    }

    pid += 1;
    allocated_block *allocated_block1;
    allocated_block1 = (allocated_block *) malloc(sizeof(allocated_block));
    allocated_block1->size = addr.size;
    allocated_block1->start_addr = addr.straddr;
    allocated_block1->pid = pid;
    allocate_mem(allocated_block1);

    flag = 1;
//        display_mem_usage();
}

void swap(int *p, int *q) {
    int tmp = *p;
    *p = *q;
    *q = tmp;
    return;
}

void rearrange() { //将块按照地址大小进行排序
    free_block *tmp, *tmpx;
    tmp = free_block_head;
    while (tmp != NULL) {
        tmpx = tmp->next;
        while (tmpx != NULL) {
            if (tmpx->start_addr < tmp->start_addr) {
                swap(&tmp->start_addr, &tmpx->start_addr);
                swap(&tmp->size, &tmpx->size);
            }
            tmpx = tmpx->next;
        }
        tmp = tmp->next;
    }
}


int free_mem(allocated_block *ab) { //释放某一块的内存

    int size = ab->size;
    int startaddr = ab->start_addr;
    free_block *p;
    p = (free_block *) malloc(sizeof(free_block));
    p->size = size;
    p->start_addr = startaddr;
    p->next = NULL;
    free_block *newblock = free_block_head;
    if (newblock == NULL) {
        free_block_head = p;
    } else {
        while (newblock->next != NULL) {
            newblock = newblock->next;
        }
        newblock->next = p;
    }
    rearrange();
    newblock = free_block_head;
    while (newblock != NULL) {
        while (newblock->next != NULL &&
               newblock->next->start_addr - (newblock->start_addr + newblock->size) <= MIN_SLICE) {
            newblock->size += newblock->next->size;
            newblock->next = newblock->next->next;
        }
        newblock = newblock->next;
    }
    return 1;
}

int dispose(allocated_block *fab) { //释放结构体所占的内存
    allocated_block *pre, *ab;
    if (fab == allocated_block_head) {
        allocated_block_head = allocated_block_head->next;
        free(fab);
        return 1;
    }
    pre = allocated_block_head;
    ab = allocated_block_head->next;
    while (ab != fab) {
        pre = ab;
        ab = ab->next;
    }
    pre->next = ab->next;
    free(ab);
    return 2;
}

void display_mem_usage() {
    free_block *fb = free_block_head;
    allocated_block *ab = allocated_block_head;
    puts("*********************Free Memory*********************");
    printf("%20s %20s\n", "start_addr", "size");
    int cnt = 0;
    while (fb != NULL) {
        cnt++;
        printf("%20d %20d\n", fb->start_addr, fb->size);
        fb = fb->next;
    }
    if (!cnt) puts("No Free Memory");
    else printf("Totaly %d free blocks\n", cnt);
    puts("");
    puts("*******************Used Memory*********************");
    printf("%10s %20s %10s %20s\n", "PID", "ProcessName", "start_addr", "size");
    cnt = 0;
    while (ab != NULL) {
        cnt++;
        printf("%10d %20s %10d %20d\n", ab->pid, ab->process_name, ab->start_addr, ab->size);
        ab = ab->next;
    }
    if (!cnt) puts("No allocated block");
    else printf("Totaly %d allocated blocks\n", cnt);
    return;
}

void kill_process() { //杀死某个进程
    allocated_block *ab;
    int pid;
    puts("Please input the pid of Killed process");
    scanf("%d", &pid);
    clear();
    ab = find_process(pid);
    if (ab != NULL) {
        free_mem(ab);
        dispose(ab);
    }
}

void Usemy_algo(int id) {
    My_algo algo;
    algo = make_pair(0, "FirstFit");
    algo = make_pair(1, "BestFit");
    algo = make_pair(2, "WorseFit");
}
