#include <iostream>
using namespace std;

string A = "1778998232321"; // 0x19e348ec501
string B = "1297823";       // 0x13cd9f


/**
 * 判断subA > B大，如果是 return True
 */
bool subABiggerThanB(string subA, string b) {

    // Step1: 从长度进行比较
    if (subA.length() > b.length()) {
        return true;
    } else if (b.length() > subA.length()) {
        return false;
    }
    // Step2: 长度若一样，逐位进行比较
    for (int i = 0; i < subA.length(); i ++) {
        if (subA[i] > b[i]) {
            return true;    // A 大于 B
        } else if (subA[i] < b[i]) {
            return false;   // A 小于 B
        }
    }
    return true; // A与B相等
}


/**
 * 做subA - B的操作
 */
string subtract(string subA, string B) {
    int indexB = B.length() -1;
    int indexSubA = (subA.length() > B.length()) ? indexB + 1 : indexB;
    string result (subA);
    bool lend = false; // 判断是否需要向前借位： True 需要

    // 逐位做减法
    while(indexB >= 0) {
        if (lend) {
            subA[indexSubA] = (subA[indexSubA] - '0' - 1) + '0';
        }
        if (subA[indexSubA] >= B[indexB]) {
            result[indexSubA] = (subA[indexSubA] - B[indexB]) + '0';
            lend = false;
        } else {
            result[indexSubA] = (10 - (B[indexB] - subA[indexSubA]) + '0');
            lend = true;
        }
        indexSubA -= 1;
        indexB -= 1;
    }
    if (lend) {
        result[indexSubA] = (subA[indexSubA] - '1') + '0';
    }
    if (result[0] == '0') {
        if (result.length() == 1){
            return "";
        }
        return result.substr(1);
    }
    return result;
}

/**
 * 规定 A % B
 * @param subA: 为A从高到低截取的子串
 * @param B
 * @return subA % B 的结果
 */
string modulo(string subA, string B) {
    while(subABiggerThanB(subA, B)) { // 如果 subA > B 则说明可以取模，否则返回
        subA = subtract(subA, B); // 循环减法
        if (subA == "") break;
    }
    return subA;
}

int main() {
    /**
     * 简要：规定 A % B，使用秦九昭算法: 从高到低取模
     *
     * 内存分析：
     *       main -> modulo -> （subABiggerThanB）->  subtract
     *       调用最深为3层，使用C语言指针传递，预估总内存消耗为 sizeof(A) + 2 * sizeof(B)
     *
     * @params: temp 是 当前截取的子串
     */
    string temp = A.substr(0, 1);
    for(int i = 1; i < A.length(); i ++) {
        temp = temp.append( A.substr(i, 1));  // 每次向低位截取1位
        string prev_temp (temp);

        temp = modulo(temp, B);
        printf("%s mod %s = %s\n", prev_temp.c_str() , B.c_str(),temp.c_str());
    }
    printf("\nThe Answer: %s mod %s = %s", temp.c_str());
    return 0;
}
