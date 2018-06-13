### String match

[TOC]
#### KMP string match

---

##### Problem description

给定一个长度为$m$模式串P，长度为$n$文本字符串T，KMP 算法可以用于在文本串当中寻找模式串，其算法的复杂度为$O(m+n)$。

##### Algorithm description and certification

思路：假设当前模式串$P[i]$与文本串$T[j]$进行比较，若对比失败，保持文本串指针$j$不变，通过查next表回滚模式串指针$i$（主要是利用文本串与模式串以往成功比对所提供的信息，构建next表）。伪代码如下：

| 符号      | 含义                                                         |
| --------- | ------------------------------------------------------------ |
| $next[i]$ | 当从前往后比对，若在$T[j]$与$P[i]$比对时失败，下一个比对点应该为$T[j]$与$P[next[i]]$，也就是回退模式串 |

```cpp
// 1.build the next table
next[0] = -1; // fail at the first element, we should go back to -1
i = 1, j = next[i-1];
while (i < P.size()) 
    // reach the boundary or it equals
    if (j == -1 || P[ｉ－１] == P[j])
        i++, j++;
		next[i－1] = j;
	else
        j = next[j];

// 2. search
i = 0, j = 0;
while (i < P.size() && j < T.size())
    if (i == -1 || P[i] == T[j])
        i++, j++;
	else
        i = next[i];

// 3. return -1 if we didn't find the result
if (i == P.size())
    return j - i;
else 
    return -1;
```

* 构造$next$表

  1. 第２行：初始化$next[0]$，当在第一个符号比对失败时，我们可以假想已经匹配的**前缀P[-1]**是一个通配符(\*)，因此我们考虑用通配符去跟$T[j]$来比较，并且以此为哨兵；若下一个待比较的元素为P[-1]，我们便可以直接比较$P[0]$与$T[j]$；

  2. 第5~11行：**当前循环需要计算$next[i]$；在循环当中，$P[j]$始终是需要与$P[i-1]$比较的元素；**

     若$P[j]＝P[i-1]$或者$j=-1$，那么$next[i]=j+1$；在下一个循环当中，为了维持$j$是与$P[i－１]$比较的元素，$i, j$需要进行自增；

     否则，找到下一个需要与$P[i-1]$进行比较的元素，即为：$P[next[j]]$

* 查找
  查找的过程与构造$next$表的过程类似：

  1. 始终保持文本串的指针$j$不回退

  2. 在每一轮循环当中，始终保持当前需要比较的是：$P[i]$, $P[j]$；

     当$P[i]＝P[j]$或者$i=-1$时，表示二者匹配，指针$i, j$均往前移动一个单位；

     否则，回退指针$i$，使其指向下一个需要与$T[j]$需要比较的元素。

* 时间复杂度

  1. 对于构造$next$表，设$t=2{i}-j$，那么在每一轮循环当中，$t$总是递增的。而$t_0=3$，$t_{\infty} \leq 2m$，因此构造next表的时间复杂度为：$O(m)$;
  2. 对于查询阶段，设$t=2{j}-i$，那么在每一轮循环当中，$t$总是递增的。而$t_0=０$，$t_{\infty} \leq 2n$，因此构造next表的时间复杂度为：$O(n)$;
  3. 因此对于整个KMP算法来说，时间复杂度为：$O(m+n)$

* Example

  文本串T为：ABCABCDABABCDABCDABDE
  模式串P为：ABCDABD

  其生成的next数组如下表所示：

  | A    | B    | C    | D    | A    | B    | D    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  | -1   | 0    | 0    | 0    | 0    | 1    | 2    |

  具体的匹配过程如下表，其中删除线表示匹配失败的字符（模式串当中）：

  | 0    | 1    | 2    | 3     | 4    | 5    | 6    | 7    | 8    | 9     | 10   | 11   | 12   | 13   | 14   | 15    | 16   | 17   | 18   | 19   | 20   |
  | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- |
  | Ａ   | B    | C    | A     | B    | C    | D    | A    | B    | A     | B    | C    | D    | A    | B    | C     | D    | A    | B    | D    | E    |
  | A    | B    | C    | ~~D~~ |      |      |      |      |      |       |      |      |      |      |      |       |      |      |      |      |      |
  |      |      |      | A     | B    | C    | D    | A    | B    | ~~D~~ |      |      |      |      |      |       |      |      |      |      |      |
  |      |      |      |       |      |      |      | A    | B    | ~~C~~ |      |      |      |      |      |       |      |      |      |      |      |
  |      |      |      |       |      |      |      |      |      | A     | B    | C    | D    | A    | B    | ~~D~~ |      |      |      |      |      |
  |      |      |      |       |      |      |      |      |      |       |      |      |      | A    | B    | C     | D    | A    | B    | D    |      |

##### Code

```cpp
int32_t KmpStrStr(std::string parttern, std::string text) {
  // 1.build the next table
  std::vector<int32_t> next;
  next.resize(parttern.size());
  next[0] = -1;  // fail at the first element, we should go back to -1
  int32_t i = 1, j = next[i - 1];
  while (i < parttern.size()) {
    // reach the boundary or it equals
    if (j == -1 || parttern[i - 1] == parttern[j]) {
      i++, j++;
      next[i - 1] = j;
    } else {
      j = next[j];
    }
  }
  // print the table
  std::cout << "The input parttern string and it's next array: " << parttern
            << std::endl;
  for (auto i : next) {
    std::cout << i << "\t";
  }
  std::cout << std::endl;

  // 2. search
  i = 0, j = 0;
  while (i < int32_t(parttern.size()) && j < text.size()) {
    if (i == -1 || parttern[i] == text[j]) {
      i++, j++;
    } else {
      i = next[i];
    }
  }

  // 3. return -1 if we didn't find the result
  if (i == parttern.size()) {
    return j - i;
  } else {
    return -1;
  }
}
```

需要特别注意第26行，**需要将size_t类型转换成为int32_t**，否则当$i=-1$时，i < parttern.size()会一直返回false。

##### Reference

[数据结构](http://item.jd.com/12113082.html)
[Wikipedia](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)