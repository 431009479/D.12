

## CSS 基础结构

```css
<style>
body {
    background-color: #abcdef; //background设置元素的背景属性； background-color设置背景颜色
}
.red {
    color: red; //设置颜色
}
#head {
    border: 5px solid #336699; 
}
</style>
```



### 选 择 器  [W3School 参考链接](https://www.w3school.com.cn/cssref/css_selectors.ASP)

> 选择器**就是用来选择要修改样式的元素。选择器，有些时候，选择的是一个元素，有些时候选择的是一组元素。示例代码中的 body 属于**标签选择器**，.red 是**类选择器**，#head 是 **id 选择器**，这三者也是最常用的三种选择器。下表中，列出了 CSS 中的一些常用的基础选择器：
>
> 选择器优先级权重越大； 优先级越高。

| 编 号 | 选 择 器                                                     | 例 子      | 说 明                                               |
| ----- | ------------------------------------------------------------ | ---------- | --------------------------------------------------- |
| 1     | [element](https://www.w3school.com.cn/cssref/selector_element.asp) | p,h1,div   | 元素选择器，直接写标签名                            |
| 2     | [.class](https://www.w3school.com.cn/cssref/selector_class.asp) | .red       | 类选择器，以点(.)作为开头                           |
| 3     | [#id](https://www.w3school.com.cn/cssref/selector_id.asp)    | #head      | id 选择器，以 # 作为开头                            |
| 4     | [:hover](https://www.w3school.com.cn/cssref/selector_hover.asp) | a:hover    | 伪类选择器，以 : 作为开头，鼠标悬浮的元素           |
| 5     | [:before](https://www.w3school.com.cn/cssref/selector_before.asp) | div:before | 伪元素选择器，以 : 作为开头，在元素内的最前插入元素 |
| 6     | [:after](https://www.w3school.com.cn/cssref/selector_after.asp) | div:after  | 伪元素选择器，以 : 作为开头，在元素内的最后插入元素 |

###### 元素选择器

```css
body {  //该元素选择器，优先级权重是 ： 1；
           background-color: #abcdef;
      }
      
body div { //该元素选择器，优先级权重是 ： 2； body + div
    	   //该元素选择器表示是 body 内的div；
            font-size: 20px;
        }
   div div {//该元素选择器表示是 div 内的div；
            height: 100px;
            width: 200px;
            border: 5px solid #336699;     
        }
```

######    类选择器

```css
 .red { //  类选择器 优先级权重是 ： 10
            color: red;
        }        
.blue {
            background-color: #336699;
            color: blue;
        }
 用法： <p class=" blue red">设置了class的p中的内容 </p>
	   <div class="red blue"> 设置了class的div中的内容</div>
```

###### id 选择器

```
  #head { // id 选择器  优先级权重是 ： 100
  		  // id 选择器  只能使用一次；
            border: 5px solid #336699; //  border设置边框样式：
        }
   用法：  <p id="head">设置了head的p中的内容 </p>
```



### 属 性 列 表

> 通过选择器，确定了一组元素以后，接下来，我们可以在大括号内，设置相关元素的样式属性，这些样式属性，可以控制元素的**颜色**、**大小**、**位置**、**形状和动画**（CSS3 新增）。先来看几个控制元素**颜色**和**大小**的属性方法：

| 编 号 | 属 性                                                        | 说 明                                           |
| ----- | ------------------------------------------------------------ | ----------------------------------------------- |
| 1     | [background](https://www.w3school.com.cn/cssref/pr_background.asp) | 设置元素的背景属性，最简单的是设置颜色          |
| 2     | [height](https://www.w3school.com.cn/cssref/pr_dim_height.asp) | 设置元素的高度                                  |
| 3     | [width](https://www.w3school.com.cn/cssref/pr_dim_width.asp) | 设置元素的宽度                                  |
| 4     | [padding](https://www.w3school.com.cn/cssref/pr_padding.asp) | 设置元素的内边距                                |
| 5     | [border](https://www.w3school.com.cn/cssref/pr_border.asp)   | 设置元素的边框                                  |
| 6     | [margin](https://www.w3school.com.cn/cssref/pr_margin.asp)   | 设置元素的外边距                                |
| 7     | [display](https://www.w3school.com.cn/css/pr_class_display.asp) | 设置元素的展示类型：block、inline、inline-block |

### 标准盒子模型

想要学习 CSS 属性设置，必须要理解的就是『**标准盒子模型**』，有标准就有非标准，非标准，也叫做『**IE 盒子模型**』，下图就是『**标准盒子模型**』:

![img](http://fe.haizeix.com/images/box_model.jpg)