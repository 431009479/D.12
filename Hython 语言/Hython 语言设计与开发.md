[TOC]

#  Hython 语言设计与开发

> 项目描述：
>
> 海贼 19-8 班 C++ 综合项目，设计一门自己的编程语言

### Anltr的基本使用：

> Antlr 4 ,它是一个非常强大的词法、语法分析器辅助生成工具.

#### Anltr的安装：

![image.png](http://ww1.sinaimg.cn/large/00882iMuly1gi2soba4n9j30k90bydgr.jpg)

```
1 wget http://www.antlr3.org/download/C/libantlr3c-3.4.tar.gz
tar -xzvf ./libantlr3c-3.4.tar.gz
2 ./configure --enable-64bit
3 make
4 sudo make install

1 wget http://www.antlr3.org/download/antlr-3.4-complete.jar
```


http://blog.csdn.net/wfp458113181wfp/article/details/9148577

http://contrapunctus.net/blog/2012/antlr-c

#### 抽象语法树:

![image.png](http://ww1.sinaimg.cn/large/00882iMuly1gi2stq64ckj30jf0c6wev.jpg)

> 源文件是文本文件是给人看。
>
> 通过编译器生成可执行文件,  抽象语法树。   编译器是. g 文件
>
> 运行 解释器(main.cpp)

>(1 +  2)字符串 +人为定义的规则 ===》 语法树
>
>程序 《== 字符串 + 人为定义的规则 ===》抽象语法树。   
>
> 人为定义的规则   是.g 文件： 包含（关键字，元素），转换抽象语法树。
>
>Anltr 中有.a文件 ： 静态链接库； .h文件 ：头文件。

#### EBNF文法文件.g的作用：

>// The suffix '^' means make it a root.   ^作用：提升至抽象语法树的根节点。
>// The suffix '!' means ignore it.   ！作用：忽略
>
>expr ：表达式。冒号后面是表达式。
>
>*号：代表:0 ～多次； +号：代表： 1 ～多次
>
>atom ： 原子操作 ： INT， ID， （ ），等。INT代表整数， ID代表标识符。
>
>stmt：代码段；  ->代表重映射。ASSIGN代表：= ；
>
>^(ASSIGN ID expr)代表：=号为根节点， ID， expr 分别：左右子树。

#### 基于Anltr的表达式求值:



main.cpp

![image.png](http://ww1.sinaimg.cn/large/00882iMuly1gi2w81u8c1j30hg097dgq.jpg)

> 以上的代码目的: 获取抽象语法树  , tree.



![image-20200825112533420](/home/dong/.config/Typora/typora-user-images/image-20200825112533420.png)

> run是成员函数,作用:递归遍历抽象语法树. 返回tree的值

run成员函数:



![image.png](http://ww1.sinaimg.cn/large/00882iMuly1gi2yw94mw1j30dn01sweg.jpg)

> 获取tree抽象语法树中的节点.



![image.png](http://ww1.sinaimg.cn/large/00882iMuly1gi2z0lkuvzj30nc0a745e.jpg)

> 以上代码: 分别表示以PUSH、MINUS、TIMES， 为根节点求左右子树上的节点再运算。
>
> ASSICG表示：以ASSICG为根节点， 左子树为标示符， 右子树为值， 再进行赋值。

![image-20200825112611975](/home/dong/.config/Typora/typora-user-images/image-20200825112611975.png)

> ExprTreeEvaluator类是作用域. memory 是存放值的map

#### 增加除法功能：

> 增加功能一般会先改变文法文件.g， 再改变解释器（main.cpp)

![image.png](http://ww1.sinaimg.cn/large/00882iMuly1gi2zcqtqlij30m301qab6.jpg)

> 以上的代码报错，说明是程序语法有错误， 程序语法识别不出来。 input.py(6) 报错。



```c++
//文法文件的修改 .g
expr: multExpr ((PLUS^ | MINUS^) multExpr)*
    ;
 
PLUS: '+';
MINUS: '-';

multExpr
    : atom ((TIMES^ | DIV^ | MOD^) atom)*  //在原来乘法的位置添加除法、取余运算。
    ;
 
TIMES: '*';
DIV: '/';
MOD: '%';
```

```c++
    //解释器（main.cpp)中修改
case DIV:
            return run(getChild(tree,0)) / run(getChild(tree,1));
 case MOD:
            return run(getChild(tree,0)) % run(getChild(tree,1));
```

### 作用域语法性质设计：

> 变量的定义和声明应该分开。 避免重复声明， 定义。 声明用def标示。

#### 文法文件：

```c
声明：DEF
defid_sub: ID^ (ASSIGN! expr)?;
defid: DEF^ defid_sub (','! defid_sub)* ';'! ;
DEF: 'def';
```

> 解释器中的DEF 代表 def。
>
> defid_sub:ID^(ASSIGN ! expr)?  代表以ID为根节点 （忽略等号， 把expr表达式的值挂到ID上）？代表（）内的可有可无。
>
> defid: DEF^ defid_sub (','! defid_sub)* ';'! ;  代表以DEF为根节点， 接一个或若干个defid_sub,  忽略，号和 末尾的；号

```c++
作用域： BLOCK
block_stmt: stmt*; 代表block_stmt由 0～N 个stmt组成。
block: '{' block_stmt '}' -> ^(BLOCK block_stmt); 把 '{'block_stmt'}' 映射成以 &的为根节点， block_stmt为子节点。
BLOCK: '&';  解释器中的BLOCK 代表 &。
```



```c++
print_stmt: PRINT ^expr ';'!;  代表以PRINT为根节点， expr为子节点的树。
PRINT: 'print';   解释器中的BLOCK 代表 'print'。
```

```c
stmt: expr ';' NEWLINE -> expr  // tree rewrite syntax  把表达式 加 ；号， 加空行； 映射 成表达式。
    | ID ASSIGN expr ';' NEWLINE -> ^(ASSIGN ID expr) // tree notation  把标识符  等号  表达式  ;号  空行  映射成  以等号为根节点，标识符， 表达式为左右子树。
    | defid NEWLINE -> defid  //把DEF 空行 映射成 DEF
    | block //作用域
    | print_stmt  //PRINT
    | ';'* NEWLINE ->   // ignore;空行
    //stmt代表代码块。
```

```c
prog //程序的开始
    : (block { //程序以block开始的。
        #ifdef INFOMSG //DEBUG判断
        pANTLR3_STRING s = $block.tree->toStringTree($block.tree);
             assert(s->chars);
             printf(" haizei tree \%s\n", s->chars);
            fflush(stdout);
        #endif    
        }
        )+
    ;
```

#### 解释器文件

```c++
//修改作用域功能
class ExprTreeEvaluator {
    map<string,int> memory;
public:
    ExprTreeEvaluator(){} //添加无参构造函数。
    ExprTreeEvaluator(ExprTreeEvaluator *next){//添加有参构造函数，参数是类指针。
        this->next = next; //子作用域指向父作用域。使作用域连成链表
    }
    int run(pANTLR3_BASE_TREE); //处理抽象语法树
    void set_param(string, int); //
    int get_param(string);
    ExprTreeEvaluator *next; //声明类指针
};
```

```c++
  case BLOCK: { //作用域
            ExprTreeEvaluator new_block(this); //定义子作用域。
            int k = tree->getChildCount(tree);
            int r = 0;
            for(int i = 0; i < k; i++) {
                r = new_block.run(getChild(tree, i)); //调用子作用域的run的函数
            }
            return r;
        }break;

       case PRINT:{ //输入
            int r = run(getChild(tree, 0));//获取PRINT的左子树的值。
            cout << r << endl;
            return r;
        }break;

case ID: {//标识符
            string var(getText(tree)); //获取var标识符ID
            return get_param(var); //使用get_param递归求标示符，求最近的作用域中的ID
        }
```

```c++
   case DEF:{
                int k = tree->getChildCount(tree); //求以DEF为根节点，有多少子节点。
                int init_val = 0; //定义初始化的val；
                for(int i = 0; i < k; i++){   //遍历def下所有的节点。
                    pANTLR3_BASE_TREE child = getChild(tree, i);
                    string var(getText(child));//获得节点的text;
                    if(child->getChildCount(child)){//判段节点下是否还有节点如： def  a = 3;
                        init_val = run(getChild(child, 0));  //init_val 就是 3；
                    }
                  //  cout << "set param val : " << var << " = " << init_val << endl;
                    def_param(var, init_val);  //通过def_param函数赋值。
                }
            return 0;
        }break;
case ASSIGN: {  //等号
            string var(getText(getChild(tree,0)));  //获得节点的text;
            get_param(var); //判断var是否在作用域中。
            int val = run(getChild(tree,1)); // 获取var 的值。
            set_param(var, val); //改变同一作用域中var的值， 统一为val。
            return val;
        }
```

### 改变主函数结构

> 改变主函数结构， 使程序可读性更好。
>
> 1、AST.h文件 实现封装 pANTLR3_INPUT_STREAM 的类、重载方法、普通方法等。
>
> 2、

#### AST.h文件

```c++
namespace haizei {  //明命空间
class ASTNode {   //封装类
public :
    ASTNode(const char *file_name);  //接收文件的字符串指针
    ASTNode(pANTLR3_BASE_TREE);  //
    int size();  //返回tree中有多少节点
    std::string text(); //返回节点的名称，如： a
    ASTNode operator[](int);  //重载[], 返回节点的值
    bool hasToken();	//返回tok
    int type();		
    void destroy();
    ~ASTNode();
    pANTLR3_COMMON_TOKEN tok;
private:
    pANTLR3_INPUT_STREAM input;
    phythonLexer lex;
    pANTLR3_COMMON_TOKEN_STREAM tokens;
    phythonParser parser;
    pANTLR3_BASE_TREE tree; //定义树。

    void init_tree(const char *file_name); //初始化树
};
} 
```

#### AST.c文件

初始化树：

```c++
void ASTNode::init_tree(const char *file_name) {
    input = antlr3FileStreamNew((pANTLR3_UINT8)file_name,ANTLR3_ENC_8BIT);
    lex = hythonLexerNew(input);
    tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT,
                                            TOKENSOURCE(lex));
    parser = hythonParserNew(tokens);
 
    hythonParser_prog_return r = parser->prog(parser);
    this->tree = r.tree;
    this->tok = this->tree->getToken(this->tree);
    return ;
}
```

重载【】：

```c++
ASTNode ASTNode::operator[](int i) {
    if (i < 0 || i >= this->size()) { //判断i 是否合法
        throw std::runtime_error("ASTNode index error");
    }
    return (pANTLR3_BASE_TREE)tree->getChild(tree, i); //返回值
    //返回值是ASTNode类型。默认调用下面的方法。
}

ASTNode::ASTNode(pANTLR3_BASE_TREE node) : tree(node) {
    parser = nullptr;
    tokens = nullptr;
    lex = nullptr;
    input = nullptr;
    tok = tree->getToken(tree);
}
```

一些方法：

```c++
int ASTNode::size() {
    return tree->getChildCount(tree);  //返回节点数目
}
std::string ASTNode::text() {
    return std::string((char *)tree->getText(tree)->chars);  //返回节点string值
}
bool ASTNode::hasToken() {
    if (tok) return true;
    return false;
}
int ASTNode::type() {
    return tok->type; //返回 如：INT，PUSH， ID，等。
}
```

### IF,  FOR, 分支控制语句

#### 文法文件：

```c++
if_expr
    : IF^ '('! condition_expr ')'! stmt ( (ELSE) => ELSE! stmt )?
    ; // if语句：condition_expr 是条件表达式，第一个节点， stmt是第二节点， ( (ELSE) => ELSE! stmt )?是else判断。

for_expr
    : FOR^ '('! init_expr ';'! condition_expr ';'! for_do_expr ')'! stmt
    ; //FOR同上；

while_expr
    : WHILE^ '('! condition_expr ')'! stmt //WHILE 同上
    | DO block WHILE '(' condition_expr ')' ';' -> ^(DOWHILE condition_expr block) //DO WHILE 会有作用域的参与，所以用block不是 stmt。 变形以DOWHILE为根， condition_expr, block 为左右节点。
    ;
```

```c++
init_expr  //for的第一个参数。
    : defid_expr -> ^(DEF defid_expr)   //def i = 2;
    | ID ASSIGN expr -> ^(ASSIGN ID expr) // i = 2;
    | -> ^(NO) //为空。
    ;

for_do_expr //for的第三个参数
    : ID ASSIGN expr -> ^(ASSIGN ID expr)  //i = 2;
    | -> ^(NO) //为空。
    ;
//从上往下优先级越高
condition_expr: andExpr (OR^ andExpr)* //   ||运算符
    ;
andExpr: cmp_atom (AND^ cmp_atom)* // &&运算符
    ;
cmp_atom: cond_atom ((GT^ | LITTLE^ | EQ^ | GE^ | LE^ | NE^) cond_atom)? //一元运算符
    ;
cond_atom 
    : expr
    ;
```

```c++
stmt: expr ';' -> expr  // tree rewrite syntax
    | defid_expr ';' -> ^(DEF defid_expr)
    | ID ASSIGN expr ';' -> ^(ASSIGN ID expr) // tree notation
    | block 
    | if_expr
    | for_expr -> ^(BLOCK for_expr)  //for循环也要加一层作用域
    | while_expr
    | PRINT^ expr (','! expr)* ';'!
    ;
```

#### 解释器文件：

```c++
case IF: {
            int ret = MasterChain::get()->valid(tree[0], this->param);
            if (ret) {
                return MasterChain::get()->valid(tree[1], this->param); 
            } else {
                if (tree.size() == 3)
                return MasterChain::get()->valid(tree[2], this->param);
            }
        }
        case WHILE: {
            while (MasterChain::get()->valid(tree[0], this->param)) {
                    MasterChain::get()->valid(tree[1], this->param);
            }
            break;
        }
        case DOWHILE: {
            do {
                MasterChain::get()->valid(tree[1], this->param);
            } while (MasterChain::get()->valid(tree[0], this->param));
            break;
        }
        case FOR: {
            MasterChain::get()->valid(tree[0], this->param);
            while (MasterChain::get()->valid(tree[1], this->param)) {
                MasterChain::get()->valid(tree[3], this->param);
                MasterChain::get()->valid(tree[2], this->param);
            }
            break;
        }
```

