# Grammar_Parser
 LL(1)语法分析器
 输入部分：

- 文法：通过文件输入

- 句子：通过文件输入


# 任务

1. 对文法去除左递归

- 间接左递归：将其全部转换成直接左递归

    - 使用深度优先搜索进行自上而下的推导，一边推导一边将每次遍历到的产生式除去第一个非终结符插入记录的vector<string>的开头，即存储最终得到的产生式。

    - 直至当找到间接左递归时，插入整个产生式到存储的产生式开头，并返回结果产生式。

- 直接左递归

2. 计算FIRST集合

3. 计算FOLLOW集合

4. 证明是否为LL（1）文法

5. 若是则继续可以输入需要进行语法分析的句子进行预测分析

- 需要多行输入分析

- 需要错误提示与建议
