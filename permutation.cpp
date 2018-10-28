#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;

const int n_iterator = 1;
int method;
int num;
int a[15];

void usage1(){
    printf("please input a number (1-6):\n"
            "(1)Recursive\n"
            "(2)Directionary\n"
            "(3)SJT\n"
            "(4)Incremental\n"
            "(5)Decremental\n"
            "(6)Adjacent\n");
}

void usage2(){
    printf("please input a number (1-9) as the scale of permutation\n");
}

void input(){
    while(1){
        usage1();
        scanf("%d", &method);
        if(method >= 1 && method <= 6) break;
        printf("%d is out of range of (1-6), please input again!\n", method);
    }
    while(1){
        usage2();
        scanf("%d", &num);
        if(num >= 1 && num <= 9) break;
        printf("%d is out of range of (1-9), please input again!\n", num);
    }
}

//recursive algorithm, the complexity is O(n!)
void do_recursive(string s, int output){
    if(s.size() == num){
        if(output) cout<<s<<endl;
        return;
    }
    int n = s.size() + 1;
    // insert n into s
    for(int i = 0; i < s.size(); i++){
        string ss = s.substr(0, i);
        ss += (char)(n + '0');
        ss += s.substr(i, s.size() - i);
        do_recursive(ss, output);
    }
    string ss = s + (char)(n + '0');
    do_recursive(ss, output);
}

//directionary algorithm
void do_directionary(int output){
    char s[15];
    int i, j;
    //initialize
    for(i = 1; i <= num; i++){
        s[i - 1] = (char)(i + '0');
    }
    s[num] = 0;
    while(1){
        if(output) printf("%s\n", s);
        // find the first down and sort
        for(i = num - 2; i >= 0; i--){
            if(s[i] < s[i + 1]){
                for(j = i; j < num - 1; j++){
                    if(s[j + 1] < s[i]) break;
                }
                swap(s[i], s[j]);
                sort(s + i + 1, s + num);
                break;
            }
        }
        if(i < 0) break;
    }
}

void do_sjt(int output){
    // initialize the first permutation and direction 
    string s = "";
    int dir[15];
    for(int i = 1; i <= num; i++){
        s += (char)(i + '0');
        dir[i - 1] = -1;
    }
    while(1){
        if(output) cout<<s<<endl;
        //max number can move
        int i, j, maxn = -1, maxnitem = 0;
        for(i = 0; i < num; i++){
            if(i + dir[i] >= 0 && i + dir[i] < num){
                if(s[i + dir[i]] < s[i]){
                    if(s[i] - '0' > maxnitem){
                        maxnitem = s[i] - '0';
                        maxn = i;
                    }
                }
            }
        }
        if(maxn != -1){
            // change the direction
            for(j = 0; j < num; j++){
                if(s[j] > s[maxn]) dir[j] = -dir[j];
            }
            swap(s[maxn], s[maxn + dir[maxn]]);
            swap(dir[maxn], dir[maxn + dir[maxn]]);
        }
        else break;
    }
}

bool incre_add(){
    int flag = 0;
    // continue or stop
    for(int i = 2; i <= num; i++){
        if(a[i] < i - 1){
            flag = 1;
            break;
        }
    }
    if(flag){
        //add 1
        int add = 1;
        for(int i = 2; i <= num; i++){
            if(add == 0) break;
            int tmp = (a[i] + add) / i;
            a[i] = (a[i] + add) % i;
            add = tmp;
        }
        return true;
    }
    return false;
}
void do_increase_base(int output){
    // initialize the first permutation and intermediate number
    string s = "";
    for(int i = 1; i <= num; i++){
        s += (char)(i + '0');
        a[i] = 0;
    }
    // loop to calculate permutation
    while(1){
        if(output) cout<<s<<endl;
        //increase base counting method
        if(!incre_add()) break;
        int vis[15] = {0};
        // generate permutation
        for(int i = num; i >= 1; i--){
            int emptynum = 0;
            for(int j = num - 1; j >= 0; j--){
                if(vis[j] == 0){
                    if(emptynum == a[i]){
                        vis[j] = 1;
                        s[j] = (char)(i + '0');
                        break;
                    }
                    else{
                        emptynum++;
                    }
                }
            }
        }
    }
}

bool decre_add(){
    int flag = 0;
    // continue or stop
    for(int i = num; i > 0; i--){
        if(a[i] < i - 1){
            flag = 1;
            break;
        }
    }
    if(flag){
        // add 1
        int add = 1;
        for(int i = num; i >= 2; i--){
        //for(int i = 2; i <= num; i++){
            if(add == 0) break;
            int tmp = (a[i] + add) / i;
            a[i] = (a[i] + add) % i;
            add = tmp;
        }
        return true;
    }
    return false;
}

void do_decrease_base(int output){
    // initialize the first permutation and intermediate number
    string s = "";
    for(int i = 1; i <= num; i++){
        s += (char)(i + '0');
        a[i] = 0;
    }
    // loop to calculate permutation
    while(1){
        if(output) cout<<s<<endl;
        //decrease base counting method
        if(!decre_add()) break;
        int vis[15] = {0};
        // generate permutation
        for(int i = num; i >= 1; i--){
            int emptynum = 0;
            for(int j = num - 1; j >= 0; j--){
                if(vis[j] == 0){
                    if(emptynum == a[i]){
                        vis[j] = 1;
                        s[j] = (char)(i + '0');
                        break;
                    }
                    else{
                        emptynum++;
                    }
                }
            }
        }
    }
}

void do_neighbour_exchange(int output){
    // initialize the first permutation and intermediate number
    string s = "";
    for(int i = 1; i <= num; i++){
        s += (char)(i + '0');
        a[i] = 0;
    }
    // loop to calculate permutation
    while(1){
        if(output) cout<<s<<endl;
        //decrease base counting method
        if(!decre_add()) break;
        int dir[15];
        int vis[15] = {0};
        // calculate direction
        dir[2] = -1;
        for(int i = 3; i <= num; i++){
            if(i % 2 == 1){
                if(a[i - 1] % 2) dir[i] = 1;
                else dir[i] = -1;
            }
            else{
                if((a[i - 1] + a[i - 2]) % 2) dir[i] = 1;
                else dir[i] = -1;
            }
        }
        // generate permutation
        for(int i = num; i > 0; i--){
            int emptynum = 0;
            if(dir[i] == 1){
                for(int j = 0; j < num; j++){
                    if(vis[j] == 0){
                        if(emptynum == a[i]){
                            s[j] = (char)(i + '0');
                            vis[j] = 1;
                            break;
                        }
                        else emptynum++;
                    }
                }
            }
            else{
                for(int j = num - 1; j >= 0; j--){
                    if(vis[j] == 0){
                        if(emptynum == a[i]){
                            s[j] = (char)(i + '0');
                            vis[j] = 1;
                            break;
                        }
                        else emptynum++;
                    }
                }
            }
        }
    }
}


void do_permutation(){
    // choose corresponding method
    char name[30];
    switch(method){
        case 1:
            snprintf(name, 30, "recursive_%d", num);
            freopen(name, "w", stdout);
            do_recursive("1", 1);
            fclose(stdout);
            break;
        case 2:
            snprintf(name, 30, "directionary_%d", num);
            freopen(name, "w", stdout);
            do_directionary(1);
            fclose(stdout);
            break;
        case 3:
            snprintf(name, 30, "sjt_%d", num);
            freopen(name, "w", stdout);
            do_sjt(1);
            fclose(stdout);
            break;
        case 4:
            snprintf(name, 30, "increase_base_%d", num);
            freopen(name, "w", stdout);
            do_increase_base(1);
            fclose(stdout);
            break;
        case 5:
            snprintf(name, 30, "decrease_base_%d", num);
            freopen(name, "w", stdout);
            do_decrease_base(1);
            fclose(stdout);
            break;
        case 6:
            snprintf(name, 30, "neighbour_exchange_%d", num);
            freopen(name, "w", stdout);
            do_neighbour_exchange(1);
            fclose(stdout);
            break;
    }
}

//test average time of 1-6 algorithm 
void test_time(){
    freopen("evaluation___2", "w", stdout);
    for(int j = 1; j <= 10; j++){
        clock_t start, end;
        num = j;
        printf("length of permutation: %d\n", num);
        //do recursive
        //warm up
        do_recursive("1", 0);
        start = clock();
        for(int i = 0; i < n_iterator; i++){
            do_recursive("1", 0);
        }
        end = clock();
        printf("average runtime of recursive: %.2f ms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);
        
        //do_directionary
        //warm_up
        do_directionary(0);
        start = clock();
        for(int i = 0; i < n_iterator; i++){
            do_directionary(0);
        }
        end = clock();
        printf("average runtime of directionary: %.2f ms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);

        //do_sjt
        //warm up
        do_sjt(0);
        start = clock();
        for(int i = 0; i < n_iterator; i++){
            do_sjt(0);
        }
        end = clock();
        printf("average runtime of sjt: %.2f ms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);
        
        //do_increase_base
        //warm up
        do_increase_base(0);
        start = clock();
        for(int i = 0; i < n_iterator; i++){
            do_increase_base(0);
        }
        end = clock();
        printf("average runtime of increase_base: %.2f ms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);

        //do_decrease_base
        //warm up
        do_decrease_base(0);
        start = clock();
        for(int i = 0; i < n_iterator; i++){
            do_decrease_base(0);
        }
        end = clock();
        printf("average runtime of decreate_base: %.2f ms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);

        //do_neighbour_exchange
        //warm up 
        do_neighbour_exchange(0);
        start = clock();
        for(int i = 0; i < n_iterator; i++){
            do_neighbour_exchange(0);
        }
        end = clock();
        printf("average runtime of neighbour_exchange: %.2f ms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);
    }

    fclose(stdout);
}
int main(){
    //input();
    //do_permutation();
    test_time();
    return 0;
}