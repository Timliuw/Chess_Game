#include <iostream>


int main() {
    class A {
    public:
        int x = 0;
    };
    class B {
        
        int y;
    public:
        A a; 
        void change_A(int val) {
            A new_a;
            new_a.x = val;
            a = new_a;
        }
    };

    B b;
    b.change_A(1);
    std::cout << b.a.x << std::endl;

}