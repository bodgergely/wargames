#include <fcntl.h>
#include <iostream> 
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
using namespace std;

class Human{
private:
	virtual void give_shell(){
		system("/bin/sh");
	}
protected:
	int age;
	string name;
public:
	virtual void introduce(){
		cout << "My name is " << name << endl;
		cout << "I am " << age << " years old" << endl;
	}
};

class Man: public Human{
public:
	Man(string name, int age){
		this->name = name;
		this->age = age;
        }
        virtual void introduce(){
		Human::introduce();
                cout << "I am a nice guy!" << endl;
        }
};

class Woman: public Human{
public:
        Woman(string name, int age){
                this->name = name;
                this->age = age;
        }
        virtual void introduce(){
                Human::introduce();
                cout << "I am a cute girl!" << endl;
        }
};

int print_info(void* m, void* w)
{
    printf("Man first word: %p\n", *(int *)m);
    printf("Woman first word: %p\n", *(int *)w);
}

int main(int argc, char* argv[]){
	Human* m = new Man("Jack", 25);
	Human* w = new Woman("Jill", 21);

    printf("Man allocated at:   %p, size: %u\n", m, sizeof(Man));
    printf("Woman allocated at: %p, size: %u\n", w, sizeof(Woman));
    printf("Diff: %u\n", (unsigned int)w - (unsigned int)m);
    print_info(m,w);
	size_t len;
	char* data;
	unsigned int op;
	while(1){
		cout << "1. use\n2. after\n3. free\n";
		cin >> op;

		switch(op){
			case 1:
				m->introduce();
				w->introduce();
				break;
			case 2:
				len = atoi(argv[1]);
				data = new char[len];
				read(open(argv[2], O_RDONLY), data, len);
				cout << "your data is allocated" << endl;
                printf("Your data starts at: %p and has len: %u\n", data, len);
                print_info(m,w);
				break;
			case 3:
				delete m;
				delete w;
                printf("After deleting them: \n");
                print_info(m, w);
				break;
			default:
				break;
		}
	}

	return 0;	
}
