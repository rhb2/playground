#include <iostream>
#include <vector>

using namespace std;

typedef enum animal {
	CAT,
	DOG
} animal_t;

class animal_shelter {
public:
	animal_shelter(void);
	~animal_shelter(void);

	void enqueue(animal_t);
	bool dequeue(animal_t *);
	bool dequeue_dog(animal_t *);
	bool dequeue_cat(animal_t *);

	vector<animal_t> all;
	vector<animal_t> cats;
	vector<animal_t> dogs;
};

animal_shelter::animal_shelter(void)
{}

animal_shelter::~animal_shelter(void)
{}

void
animal_shelter::enqueue(animal_t a)
{
	if (a == CAT)
		cats.push_back(a);

	if (a == DOG)
		dogs.push_back(a);

	all.push_back(a);

	assert(all.size() == (cats.size() + dogs.size()));
}

bool
animal_shelter::dequeue(animal_t *ap)
{

	assert(ap != NULL);

	if (all.size() == 0)
		return (false);

	*ap = all.front();
	all.erase(all.begin());

	if (*ap == CAT)
		cats.erase(cats.begin());

	if (*ap == DOG)
		dogs.erase(dogs.begin());

	assert(all.size() == (cats.size() + dogs.size()));

	return (true);
}

bool
animal_shelter::dequeue_cat(animal_t *ap)
{
	int i;

	assert(ap != NULL);

	if (cats.size() == 0)
		return (false);

	cats.erase(cats.begin());

	for (i = 0; i < all.size(); i++) {
		if (all.at(i) == CAT) {
			*ap = all.at(i);
			break;
		}
	}

	all.erase(all.begin() + i);
	assert(all.size() == (cats.size() + dogs.size()));

	return (true);
}

bool
animal_shelter::dequeue_dog(animal_t *ap)
{
	int i;

	if (dogs.size() == 0)
		return (false);

	dogs.erase(dogs.begin());

	for (i = 0; i < all.size(); i++) {
		if (all.at(i) == DOG) {
			*ap = all.at(i);
			break;
		}
	}

	all.erase(all.begin() + i);
	assert(all.size() == (cats.size() + dogs.size()));

	return (true);
}

ostream &
operator <<(ostream &out, const animal_t &a)
{
	if (a == DOG)
		cout << "DOG";
	else
		cout << "CAT";

	return (out);
}

ostream &
operator <<(ostream &out, const animal_shelter &as)
{
	int i;

	cout << "Cats: " << as.cats.size() << endl;
	cout << "Dogs: " << as.dogs.size() << endl;
	cout << "Total: " << as.all.size() << endl;

	for (i = 0; i < as.all.size(); i++)
		cout << as.all.at(i) << " ";

	return (out);
}

int main(int argc, char **argv)
{
	int i;
	int total = atoi(argv[1]);
	animal_shelter as;
	animal_t a;

	for (i = 0; i < total; i++) {
		a =  ((rand() % 10) > 5) ? CAT : DOG;
		as.enqueue(a);
	}

	cout << as << endl;

	while (as.dequeue_dog(&a))
		cout << as << endl << endl;
	return (0);
}
