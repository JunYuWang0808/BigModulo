# BigModulo

简要：规定 A % B，使用秦九昭算法: 从高到低取模
 
内存分析：
     调用链为：main -> modulo -> （subABiggerThanB）->  subtract
     调用最深为3层，使用C语言指针传递，预估总内存消耗为 sizeof(A) + 2 * sizeof(B)
    
     符合64k内存要求
     
