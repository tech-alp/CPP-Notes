## Value Category

- RValue reference -> type category.

- LValue reference -> type category

- RValue -> value category

- LValue -> value category

```
                          expersion
                           /     \ 
                          /       \
                         /         \
                    glvalue       rvalue
                      / \          / \
                     /   \        /   \
                    /     \      /     \
                lvalue     xvalue     prvalue
```
**Rvalue:** Taşınabilir fakat bellekte herhangi bir adresi yok.

__Lvalue:__ güvenli bir şekilde çalışmaz.

> Sol taraf referansları ilk değer ile başlatılmak zorundadır.

```C++
int x = 10;
int& r = x; 
```

> Referanslar rebindable değildir. "T* const ptr" gibidirler.

```C++
int x = 10;
int y = 5;
int& r = x;
r = y; //Error refrence not rebindable
```

> Bir sol taraf referansı bir "sağ taraf değeri" ifadesine 
bağlanamaz.
````C++
int& r = 10; //Error Lvalue reference can not bind rvalue
````

> Bir const sol taraf referansı bir "sağ taraf değeri" 
ifadesine bağlanabilir.

> İsim formundaki tüm ifadelerin değer kategorisi Lvalue
expersion'dır.

> Bir ifadenin data type başka value category'si başkadır.
````C++
int&& ref = 10;
//ref ---> isim formu olduğu için L value expr.
//data type ise sağ taraf referansıdır.(RValue reference)
````

<!--
    Example 
    * italic sentences *
    "---" lines
    - item
    * item
    + item
    <website https//....>
    [Code](#Value-Category) just example

    You can do blocks of code by surround it with 3 backticks()

    <style>
    p {
        color: orange
    }
    </style>
-->

---


## Auto Type Deduction

**Acronym:** Kelimelerin baş harfleriyle oluşturulur.

* AAA --> Almost Always Auto

* VIP --> Very Important Person

````C++
auto x = expr;
auto& x = expr;
auto&& x = expr;
````

---

## Decltype

Eğer decltype operatörünün operandı olan ifade bir isim
formunda değil ise ifadenin value kategorisine bakılacak.

- İfade Lvalue ise elde edilen tür  __T &__

- İfade PRvalue ise elde edilen tür __T__

- İfade Xvalue ise elde edilen tür  __T &&__

---

## constexpr

En önemli kullanımı fonksiyonların geri dönüş değeri 
olarak kullanımıdır.

````C++
constexpr int sum_square(int a, int b)
{
    return a*a + b*b;
}
int main() {
int x = 5, y = 4;
sum_square(x,y); // Geçerli
constexpr int z = sum_square(x,y); //Geçersiz
}
````
__Sum_square__ fonksiyonunun operandına sabit olmayan
değişkenler girildiğinde normal bir fonksiyon gibi davranır.
Yani run time'da çalışır. Bu yüzden "constexpr int z" sadece
sabit bir ifade ile başlayacağından geçersiz olacaktır.

> constexpr fonksiyonlar başlık dosyalarında implicit inline
olarak tanımlanır.

---


## Function Overloading

Aynı isimli işlevler aynı kapsamda(scope) olmalıdır.
Aynı kapsamdaki aynı isimli işlevlerin imzaları farkı olacak.

#### Function Redeclaretion
```C++
void func(int a, int b);
void func(int, int);
```

#### Syntax Error
```C++
void func(int a, int b);
int func(int, int);
```

#### Function Overloading
```C++
void func(int a, int b);
void func(int);
```

1. **Variadic convertion**

    void func(...); //variadic func.

1. **User-defined Convertion**

Programlayıcı tarafından tanımlanan dönüşümlere denir.
```C++
struct Data  {
    Data() = default;
    Data(int);
}
int main() {
    Data mydata;
    mydata = 10; //user-defined type
}
```

3. Standard Convertion

- int    ---> double

- double ---> int

- double ---> char

- enum   ---> int

- int*   ---> void*

gibi bazı dönüşümler derleyicinin implicitly dönüşümlerine örnektir.

```C++
void func(int);
void func(double);
void func(char);
int main() {
    func(12.f); //Hangi func. çağrılır.
}
```
**func(double)** çağrılacaktır. Çünkü float'tan double'a promotion vardır.


1. exact match(tam uyum)

2. promotion(terfi-yükseltme)

3. convertion

Yukarıdaki 3 durum içerisinde fonksiyon sırası ile uygun olan
fonksiyonu arar(exact match > promotion > convertion)

### Exact-Match
✔LValue to rvalue convertion

✔T* to const T* convertion

✔function to pointer convertion 

exact match'tir.

Örneğin;
```C++
void func(int a);
int main() {
    int x = 10;
    func(x); //Lvalue to rvalue exact-match olacktır.
}
```

