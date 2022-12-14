### 表达式定义
$$
\begin{aligned}
    expression \rightarrow
    &arithmetic\_ expression |\\
    &condition\_ expression |\\
    &define\_ expression | \\
    &assign\_ expression\\
    \\
    arithmetic\_ expression \rightarrow
    & ARE\\
    ARE \rightarrow& ARE + ARE\\
    ARE \rightarrow& ARE * ARE\\
    ARE \rightarrow& ARE - ARE\\
    ARE \rightarrow& ARE / ARE\\
    ARE \rightarrow& ARE \% ARE\\
    ARE \rightarrow& ARE \& ARE\\
    ARE \rightarrow& ARE | ARE\\
    ARE \rightarrow& \overline{ARE}\\
    ARE \rightarrow& (ARE)\\
    ARE \rightarrow& id|imm\\
    \\
    condition\_ expression \rightarrow & CE\\
    CE \rightarrow& CE \&\& CE\\
    CE \rightarrow& CE || CE\\
    CE \rightarrow& !CE\\
    CE \rightarrow& id|imm|arithmetic\_ expression\\
    CE \rightarrow& CE1 \lt = CE1\\
    CE \rightarrow& CE1 \gt = CE1\\
    CE \rightarrow& CE1 \lt CE1\\
    CE \rightarrow& CE1 \gt CE1\\
    CE \rightarrow& CE1 == CE1\\
    CE1 \rightarrow& (CE \, sign \, CE) | id | imm | arithmetic\_ expression\\
    \\
    define\_ expression \rightarrow& type \, id\\
    \\
    assign\_ expression \rightarrow& define\_ expression = arithmetic\_ expression |\\
    & id=arithmetic\_ expression\\
\end{aligned}
$$
### 结构定义
$$
\begin{aligned}
    block \rightarrow
    & seq\_ block |\\
    & loop\_ block |\\
    & branch\_ block|\\
    & expression;\\
    \\
    seq\_ block \rightarrow& block \cdot block\\
    \\
    loop\_ block \rightarrow
    & while(condition\_ expression)\{block\}\\
    \\
    branch\_ block \rightarrow
    & if(condition\_ expression)\{block\} |\\
    & if(condition\_ expression)\{block\}else\{block\} |\\
    & if(condition\_ expression)\{block\}elif\_ block\{block\} |\\
    elif\_ block\_ unit \rightarrow& elseif(condition_expression)\{block\}\\
    elif\_ block \rightarrow
    & elif\_ block\_ unit \cdot elif\_ block |\\
    & elif\_ block\_ unit\\
    \\
\end{aligned}
$$

### 代码定义
$$
    G[S] = (N,\Sigma, P, S);\\
    \begin{aligned}
        S \rightarrow CODE
    \end{aligned}
$$