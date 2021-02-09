<!--
    Example 
    * italic sentences *
    --- lines
    - item
    * item
    + item
    <website https//....>
    [Code](#Value-Category) just example

    You can do blocks of code by surround it with 3 backticks()
    ```

    <style>
    p {
        color: orange
    }
    </style>
-->

## Value Category

- RValue reference -> type category.

- LValue reference -> type category

- RValue -> value category

- LValue -> value category

## Reference

```txt
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

__Lvalue:__ İsim formundaki yani bellekte yer tutan nesnelerin değer kategorisidir.

> Bir sol taraf referansı bir "sağ taraf değeri" ifadesine bağlanamaz.

> Bir sağ taraf referansı bir "sol taraf değeri" ifadesine bağlanamaz. Fakat const sol taraf referansı "sağ taraf değeri" ifadesine bağlanabilir.

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


```C++
int  foo();
int& func();
int main() {
    int& a = func(); // valid
    int b = foo();   // valid
    int& c = func(); // invalid(Lvalue ref. can't bind r value)
    const int& d = foo(); //valid. [*]
}
```

`const int& d = foo()` şeklinde belirtilen kodun geçerli olmasının sebebi compiler `const int temp = foo();` şekilinde bir kod üretir ve daha sonra `const int& d = temp` olarakoluşturul    böylece lvalue referans sol değer ifadesinebağlanır. 

> Bir ifadenin data type başka value category'si başkadır.
````C++
int&& ref = 10;
//ref ---> isim formu olduğu için L value expr.
//data type ise sağ taraf referansıdır.(RValue reference)
````

> const lvalue reference tipinde bir değişkene sağ taraf değeri ile ilk değer vermenin en önemli kullanımı move schematic'tir. Sınıf yapılarında bunu tekrar inceleyeceğiz.

```C++
double dval{2.456};
const int& x = dval; //valid
const int& y(dval); //valid
const int& z{dval}; //invalid. Narrowing conservion
```

- `int x(10);` &#8594; direct initialization
- `int x{};`   &#8594; value, uniform, bracet initialization
- `int x{10};` &#8594; direct list initialization

**Uniform initialization neden ekledi?**
1. Neye ilk değer verirsen ver her zaman kullanılabilir.
1. Narrowing conversion durumunu engellemek için.
1. Most vexing parse(Scott Meyers tarafından dile ekledi)

__Most vexig parse__
```C++
#include <iostream>

struct A {

};

struct B {
    B(A) {
        std::cout << "B constructor\n"; 
    }
};

int main() {
    B b(A()); //function decleration
}
```
Yukarıdaki örnekte derleyici nesne bildirimi yerine önceliği fonksiyon bildirimine verir. Tipik bir `most verxing parse` örneğidir. Fakat `B b{A()}`şeklinde olsaydı bu bir nesne bildirimi olacak ve standart outputa ***B constructor*** yazacaktı. 

---


## Auto Type Deduction

**Acronym:** Kelimelerin baş harfleriyle oluşturulur.

* AAA --> Almost Always Auto

* VIP --> Very Important Person

Auto aşağıdaki şekillerdeki gibi kullanılabilir.
````C++
auto x = expr;
auto& x = expr;
auto&& x = expr;
````

Aşağıdaki şekilde kullanılması durumda eğer reference ve const varsa her ikiside düşer.
```C++
const int x = 10;
auto y = x; // int y = x;

int& r = x;
auto y2 = r; // int y2 = r;

const int& z = x;
auto y3 = z; // int y3 = z;
```
> __İstisna:__ `auto p = "enes";` ilk değer verme kullanılması durumunda derleyici `const char* temp = "enes";` şeklinde bir kod üretir. Daha sonra [auto](#Auto-Type-Deduction) ifadesi yerine `const char* p = temp` gelecektir. 

Reference ile kullanılması durumda
```C++
int x = 10;
int& r = x;
auto& y = r; // int& y = r;

const int& r2 = x;
auto& y2 = r2; // const int& y2 = x;
```

Son olarak `auto&& x = expr` için aşağıdaki durumların olması durumu sırası ile inceleyelim.

- İlk değer veren ifade pr value expression ise,

- İlk değer veren ifade r value expression ise,

- İlk değer veren ifade x value expression ise

| expr |  auto  | çıkarım(x) |
| -- | --- | -- |
| T& |  &  | T& |
| T& |  && | T& |
| T&& |  &  | T& |
| T&& |  &&  | T&& |

__NOT:__ Basit olarak çıkarımı şu şekilde yapabiliriz. Eğer `expr` sol taraf ifadesi ise `x` sol taraf referansı, eğer `expr` sağ taraf ifadesi ise `x` sağ taraf referansı olacaltır.

```C++
int y = 10;
auto&& r = 10; // sağ taraf ifadesi bu yüzden int&& r = 10 olacaktır.
auto&& r2 = y; // sol taraf ifadesi bu yüzden int& r2 = y; olacaktır.
```

Eğer ki `auto&&` bir sol taraf ifadesine bağlanılması durumunda `T& &&` çıkarımı yapılır. Burada referans bozulması(reference collapsing) olur. Böylece reference düşer `T&`şeklini alır.


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

__İstisna:__ C'de variadic fonksiyonlar sadece *elipsis(...)* kullanılarak tanımlanamaz. C++ bu gerçerlidir.

```C++
//variadic func.
void func(...); // 1
void func(int x, ...); // 2
void func(int x, int y, ...); // 3

int main()
{
    funcR(1,2,3,4,5); // 3 çağrılır.
}
```

2. **User-defined Convertion**

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

3. __Standard Convertion__

    - int    &#8594; double
    
    - double &#8594; int
    
    - double &#8594; char
    
    - enum   &#8594; int
    
    - int*   &#8594; void*
    
    gibi bazı dönüşümler derleyicinin implicitly     dönüşümlerine örnektir.
    
    ```C++
    void func(int);    // 1
    void func(double); // 2
    void func(char);   // 3
    int main() {
        func(12.f); // 2
    }
    ```
    > **func(double)** çağrılacaktır. Çünkü float'tan double'a promotion vardır.

<!--
-->

1. exact match(tam uyum)

2. promotion(terfi-yükseltme)

3. conversion

Yukarıdaki 3 durum içerisinde fonksiyon sırası ile uygun olan fonksiyonu derleyici arar.(exact match > promotion > convertion)

Eğer ki exact match yok ise promortion'a bakılır o da yok ise conversiona bakılır. Eğer ki birden fazla aynı işlevde conversion olacak fonksiyon varsa ambiguity olur.

### Exact-Match
- LValue to rvalue conversion

- T* to const T* conversion

- Function to pointer conversion 

exact match'tir.

Örneğin;
```C++
void func(int a);
int main() {
    int x = 10;
    func(x); //Lvalue to rvalue exact-match olacktır.
}
```

### Promotion

- Integral promotion

    int'ten küçük türlerden int türüne yapılan dönüşeme denir.

    - char &#8594; int
    - signed char &#8594; int
    - unsigned char &#8594; int
    - bool &#8594; int
    - signed short &#8594; int

float &#8594; double

__C ve C++ dillerinde__

1. Fonksiyonların parametre değişkenleri dizi (array) olmaz.
2. Fonksiyonların geri dönüş değer türleri dizi(array) olmaz.

```C++
//function redecleration
void func(int);
void func(const int);
```
**const overloading**
```C++
 //function overloading
 void func(int*);
 void func(const int*);
```

---

<br></br>

## Numaralandırma Türleri

#### Enum:

> C'den farklı olarak underlying type vardır.

```C++
enum Color : char {
WHITE,
GREEN,
RED,
BLACK
};
```
#### Enum classes:
> Underlying type vardır.

> Forward decleration vardır.

```C++
enum class Color : char;
```

[Enum class](#Enum-classes) 'ların avantajları;

- Underlying type
- Implicit cast yok
- Scope resolution var

```C++
enum class Color {
    White,
    Black,
    Green,
    //...
};
int main() {
    Color mycolor = White; //Geçersiz çünkü white, enum Color kapsama alanında
    Color mycolor = Color::White; // Geçerli
}
```

---

## Tür Dönüşüm Operatörleri:

- static_cast
- const_cast
- reinterpret_cast
- dynamic_cast

#### C-style casting
Tüm cast işlemlerinde `()` parantez operandı içerisinde hedef tip belirtilerek yapılır(`(type target)expr`).

````C++
//C style casting
const int x = 10;
int* ptr = (int*)&x;
*ptr = 48; //Valid but undefined behaviour
````

#### static_cast
-  int*'dan void*'a implicit type convertion vardır.

- int*'dan void*'a veya void*'dan int*'a hem static_cast hem de reinterpret_cast kullanılabilir.

````C++
int x = 10;
void* sptr = static_cast<void*>(&x);
void* rptr = reinterpret_cast<void*>(&x);
````

#### const_cast
````C++
const int x = 10;
int* ptr = const_cast<int*>(&x);
*ptr = 48; //Valid but undefined behaviour
````
C'de kullanılan `strchr` fonksiyonu buna en güzel örnek olabilir.

```C++
char* Strchr(const char* p, int c) {
    while(*p++) {
        if(*p == c) {
            return const_cast<char*>(p);
        }
    }
    if(c == '\0')
        return const_cast<char*>(p);
    return nullptr;
}
```

#### reinterpret_cast
```C++
int x = 145981;
char* c = reinterpret_cast<char*>(&x);
for(int i = 0; i < sizeof(x); ++i) {
    std::cout << c[i] << "\n";
}
int* y = reinterpret_cast<int*>(c);
```

---

#### Extern "C" Bildirimi

C'de derlenmiş kütüphaneleri C++'da kullanabilmek için belirtilir.

```C++
extern "C" void f1();
extern "C" void f2();
```

```C++
extern "C" {
void f1();
void f2();
} 
```
Aşağıdaki şekilde ön tanımlı sembolik sabit(`predefining symboling constant`) makrosı ile sarmalanır.

```C++
#ifdef _cplusplus
extern "C" {
#endif
    void f1();
    void f2();
    void f3();
    void f4();
#ifdef _cplusplus
}
#endif
```


### Classes

```C++
class Myclass {
    // class members
    // data members(veri elemanları/öğeleri)
    // member function
    // type member

    int mx;           // data member
    typedef int Word; // type member
    void func(int);   // member function
}
```

C++ scope'lar aşağıdaki gibidir.
- Namescape scope
- Block scope
- Function prototype scope
- Function scope
- Class scope

> Sınıfın üye fonksiyonları(member func.) sınıf içerisinde yer kaplamazlar.

Sınıf veri elemanları(data members)
- non-static member
- static member &#8594; global

olabilir.

Access specifier,

- public
- private
- protected

olmak üzere 3 tanedir.

```C++
// Class decleration
// Forward decleration
// Incomplete type
class Myclass;
```

__const üye fonksiyonlar__

```C++
void func(T*);       // setter, mutator
void func(const T*); // getter, accessor
```
```C++
class Myclass {
public:
    void func();      // func(Myclass*)
    void foo()const;  // foo(const Myclass*) const member func.
}
```

Sınıfın const üye işlevleri const olmayan üye işlevlerini çağırmamlı.

```C++
void Myclass::func()
{
    foo(); // Geçersiz T* --> const T* dönüşüm vardır.
}

void Myclass::foo() const
{
    func(); // Geçersiz const T* --> T* dönüşüm yoktur.
    // func(Myclass*)
    // foo(const Myclass*)
}
```
__NOT:__ const bir sınıf nesnesi ile sadece const üye işlevleri çağırabilir.


```C++
int main() {
    const Myclass m;
    //&m = const Myclass*
    m.func(); // Geçersiz sentaks hatası const T* --> T*
}
```
#### Mutable

Sınıfın const bir üye fonksiyonunun sınıfın static olmayan veri elemanlarını değiştirebilmesi için veri elemanının `mutable` olması gerekir.

```C++
class Date {
public:
    int day_of_year()const;
private:
    int md,mm,my;
    mutable debug_count{};
}
int Date::day_of_year() const {
    ++debug_count; // Geçerli  debug_count mutable
    // ...
    return md;
}
```

#### One Defination Rule(ODR)

Bir proje içerisinde aynı varlığın birden fazla tanımı olmaz. Eğer bu varlığın tanımı aynı kaynak dosyası içerisinde olursa sentaks hatası olur. Farklı kaynaklarda olursa sentaks hatası değil fakat ill-formed  olur.


> C++ dilinde yazılımsal öyle varlıklar var ki bu varlıkların projeyi oluşturan farklı kaynak dosyalarda birden fazla kez tanımlanması(token by token aynı olması) durumunda ill-formed değildir.

```C++
// a.cpp
class A {
    int x,y;
    void func();
}

// b.cpp
class A {
    int x,y;
    void func();
}
```
Farklı kaynak dosyalarında tanımlandıkları halde token-by-token aynı oldukları için ill-formed değil well-formed olurlar.
Nitekim başlık dosyalarında oluşturduğumuz class tanımını a.hpp yi a.cpp de include ettiğimiz takdirde bu geçerli olmasaydı ill-formed olurdu.

__ODR'a  uyanlar;__
- class definations
- inline functions definations
- inline variable definations
- class template definations
- ...

#### inline fonksiyonlar

compiler optimizasyonu,

1. Derleyici compile time'da kod seçerek

1. Kod optimizasyonu yaparak

gerçekleştirebilir.

```C++
inline int func(int x) { return x*x+5; }
// fonksiyona giriş kodu
a = func(5); // a = x*x+5 yapabilir.
// fonksiyondan çıkış kodları
```

C++ inline ile C'deki inline kurallarının farklılıkları vardır.

inline fonksiyonlar;
- tanımını (sağlıklı biçimde) başlık dosyasına koyduk böylece derleyiciye inline expansion olağanı verdik.
- kodu expose eder.

` free function = standalone function = global function `

Class içerisinde fonksiyonu belirtirsek implicit inline olur.

Hangi fonksiyonlar inline olarak tanımlanır?
1. Sınıfın non-static üye işlevleri
1. Sınıfın static üye işlevleri
1. Sınıfın friendlik verdiği işlevler

#### Sınıfların özel üye fonksiyonları(Special member functions)
- default constructor
- deconstructor
- copy constructor
- move constructor (C++11)
- copy assignment
- move assignment (C++11)


#### Constructor(Kurucu fonksiyon)

Statik ömürlü global nesneler için constructor main'den önce çağrılır.

- static initialization fiasce
- static initialization problem

#### Deconstructor(Yıkıcı fonksiyon)

Bir sınıfın sadece bir tane deconstructor'u vardır ve hiçbir parametre almaz.

```C++
class Myclass {
    ~Myclass();
}
```

Bir fonksiyonun sonuna `delete` anahtar kelimesi eklenerek delete edilebilir.

`void func() = delete;`

En önemlisi delete edilen fonksiyonlar, function overloading resolution sürecine katılır.

```C++
void func();
void func(int);
void func(double) = delete;

func();    // Geçerli
func(12);  // Geçerli
func(2.4); // Geçersiz function deleted.
```

#### Constructor initialization list

```C++
class Myclass {
public:
    Myclass() : u(expr), t(expr)
    {
    }
private:
    T t;
    U u;
}
```

Class içerisindeki üye elemanlarının sırası ile kurucu ilklendirme listesi(constructor initialization list) aynı sırada olması iyi bir alışkanlıktır. Fakat yukarıdaki sınıfda sıraya uyulmuş olunmasada derleyici ilk olarak t'yi daha sonra u'yi ilklendirir.


#### Default member initializer

Class içerisinde parantez`()` atomu ile üye elemanları ilklendirme(`default initialize`) yapılamaz.

```C++
class Myclass {
    int mx(3);      // Geçersiz
    // T t = expr;  // Geçerli
    // T t{ expr }; // Geçerli
    // T t(expr);   // Geçersiz
}
```

Eğer programlayıcı sınıf için hiç bir constructor yazmaz ise derleyici sınıfın default constructor'ını default eder.

Derleyicinin yazdığı(default ettiği) default constructor

1. Sınıfın non-static public inline fonksiyonudur.
1. Bu fonksiyon sınıfın tüm veri elemanları default initialize eder.
1. Ancak eğer bir veri elamanı için default member initialize kullanılmış ise bu durumda derleyici bu init'ı kullanır.

![](images/defaultspecialmember.png)

__Implicitly declared__
```C++
class Myclass {

};
```

__User declared__
```C++
class Myclass {
public:
    Myclass();
    Myclass() = default;
    Myclass() = delete;
};
```
__Not declared__
```C++
class Myclass {
public:
    Myclass(int);
};
```

Eğer derleyici durumdan vazife çıkartarak sınıfın özel bir üye fonksiyonunu default ederse (yani bu özel üye fonk. implicitly declared ise) eğer bu fonksiyonun derleyici tarafından yazımında bir sentaks hatası oluşursa derleyici bu fonksiyonu delete eder.

```C++
class Myclass {
public:

private:
    const int mx;
};

Myclass m; // Hata ctor deleted 
```

```C++
class Myclass {
public:

private:
    int& r;
};

Myclass m; // Hata ctor deleted
```

Sentaks hatası const bir değişken ve referanslar ilk değer başlatılmak zorunda.


#### Copy constructor

Bir sınıf nesnesi hayata değerini aynı türden bir sınıf nesnesinden alarak geldiğinde, derleyicinin Myclass sınıfı için yazdığı copy ctor

1. sınıfın non-static public inline fonksiyonudur.

1. parametrik yapısı `Myclass(const Myclass&);`

```C++
class Myclass {
public:
    Myclass(const Myclass& other) : tx(other.tx), ux(other.ux)
    {
    }
private:
    T tx;
    U ux;
} 
```

Hangi durumlarda copy constructor yazmak gerekir?

İdeali derleyicinin bu fonksiyonları kendisinin yazması, buna rule of zero denmektedir.

- Dinamik bir veri elemanı olması durumunda
- Pointer veri elamanı olması durumunda

Kopyalamayı derleyici yapıyorsa shallow copy(sığ kopyalama) yapar. Bu durumda dinamik veri elmanı veya pointer üye elemanımız varsa bu kopyalamayla aynı bellek alanını başka bir nesne ile paylaşmış olacağız böylece bir nesnenin ömrünün sona ermesiyle diğer kopyasını alan nesnenin sona ermesi durumunda free edilen bellek adresi tekrar free edilmeye çalışıldığından run time çalışma hatası olacaktır.

- Bir nesnenin kendine atanmasına self assigment denilir. Bu durumda tanımsız davranış oluşur.

- Copy Ctr'yi siz yazacaksınız sınıfın tüm öğelerinden siz sorumlusunuz. Sadece pointer için yazıp, diğer primitif türler için yazmazsak o öğeler çöp değerler ile başlar.

```cpp
class A {
public:
private:
	T *mp; 
	U x, y, z; // Bu öğeler içinde copy ctr içerisinde atama yapman gerekiyor.
```


```Cpp
class Name
{
private:
	char *mp;
	size_t mlen;
public:
	Name(const char *p) : mlen{std::strlen(p) }
	{
			mp = static_cast<char*>(std::malloc(mlen + 1));
			if (!mp) {
				std::cerr << "bellek yetersiz !\n";
				std::exit(EXIT_FAILURE);
			}
			std::strcpy(mp, p);
	}

	Name(const Name &other) : mlen(other.mlen)
	{
			mp = static_cast<char*>(std::malloc(mlen + 1));
			if (!mp) {
				std::cerr << "bellek yetersiz !\n";
				std::exit(EXIT_FAILURE);
			}
			std::strcpy(mp, p);
	}

	Name &operator=(const Name &r)
	{
		if (this == &r)  // self assignment kontrol ediliyor
				return *this;

		mlen = r.mlen;
		free(mp);
		
		mp = static_cast<char*>(std::malloc(mlen + 1));
		if (!mp) {
				std::cerr << "bellek yetersiz !\n";
				std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	void print()const
	{
		std::cout << "(" << mp << ")\n";
	}

	size_t length() const
	{
		return mlen;
	}

	~Name()
	{	
		free(mp);		
	}
};
```

#### Move Constructor

Hayatı bitecek bir nesne ile başka bir nesneyi hayata getirecek isek, kaynakları kopyalamak yerine hayatı bitecek o nesnenin kaynaklarını alabiliriz. Modern C++ ile dile eklenen bu sağ taraf referanslarının gücü ile bunu yapabiliriz. Sınıfımıza move semantiğini ekleyeceğiz. Tipik move ctr'si önce gidip diğer nesnenin kaynağını çalıyor, sonra fonksiyona gelen nesneyi destruct edilebilir ama kaynağı olmayan durumda bırakıyor. Eğer bunu derleyicinin yazımına bırakırsak şöyle olmak zorunda.

```cpp
class Myclass {
	T x;
	U y;
public:
	Myclass(Myclass &&r) : x(move(r.x)), y(move(r.y))
	{
		
	}
//move fonksiyonu, sol taraf değeri türünün sağ taraf değerine dönüştürür.
};

```
```cpp
class Name
{
private:
	char *mp;
	size_t mlen;
public:
	Name(const char *p) : mlen{std::strlen(p) }
	{
			mp = static_cast<char*>(std::malloc(mlen + 1));
			if (!mp) {
				std::cerr << "bellek yetersiz !\n";
				std::exit(EXIT_FAILURE);
			}
			std::strcpy(mp, p);
	}

	Name(const Name &other) : mlen(other.mlen)
	{
			mp = static_cast<char*>(std::malloc(mlen + 1));
			if (!mp) {
				std::cerr << "bellek yetersiz !\n";
				std::exit(EXIT_FAILURE);
			}
			std::strcpy(mp, p);
	}

	Name(Name &&r) : mlen{r.mlen}, mp {r.mp} //
	{
		r.mp = nullptr;
	}

	Name &operator=(Name &&r)
	{
			if (this == &r) //self-assignment kontrolü
			{
				return *this;				
			}
			free(mp);
			mp = r.mp;
			mlen = r.mlen;
			r.mp = nullptr;
			return *this;
	}

	Name &operator=(const Name &r)
	{
		if (this == &r)
				return *this;

		mlen = r.mlen;
		free(mp);
		
		mp = static_cast<char*>(std::malloc(mlen + 1));
		if (!mp) {
				std::cerr << "bellek yetersiz !\n";
				std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	void print()const
	{
		std::cout << "(" << mp << ")\n";
	}

	size_t length() const
	{
		return mlen;
	}
	~Name()
	{
        // free edilen kaynağı tekrar free etme!
		if(mp)
		{
			free(mp);
		}
	}
};
```

#### Temporary Object (Geçici Nesne)

Geçici nesne oluşturma ifadeleri __sağ taraf değeri__ ifadesidir.

```cpp
void func(Name x)
{
	
}

func(Name{"Enes"}); // Name(const char *p) ctor çağrılır
Name x{"Enes"};     // Name(const char *p) ctor çağrılır
func(std::move(x)); // move ctor çağrılır.
```

`move == static_cast<T &&>(y)` gibi bir dönüşüm gerçekleşiyor diyebiliriz.

<!--
-->

![](images/specialmembers.svg)
