#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <random>

using namespace std;

// Проверка вводимого значения.
int correctInput() {
	cout << "Введите количество посетителей супермаркета на сегодня (от 1 до 1000): ";
	int input;
	while (!(cin >> input && 1 <= input && input <= 1000)) {
		cout << "Некорректный ввод данных. Повторите попытку: ";
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
		}
	}
	return input;
}

// Имена посетителей.
string names[] = { "Владислав", "Владимир", "Анастасия", "Игорь", "Мария", "Анна", "Виктория", "Екатерина", 
"Наталья", "Марина", "Вероника", "Жанна", "Светлана", "Татьяна", "Илья", "Кирилл", "Михаил", "Никита", "Денис",
"Тимур","Кристина", "Наталья", "Марк", "Константин", "Полина", "София", "Павел", "Дарья", "Руслан","Алиса", 
"Олег", "Ярослав", "Антон", "Николай", "Даниил", "Ксения", "Александра", "Елена", "Алина", "Виктория" };

static mt19937 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());

int getRandom() {
	int rand = mt_rand();
	return rand < 0? rand * -1 : rand;
}

// Посетитель супермаркета.
class Customer {
	string name; //имя посетителя
public:
	// Создаёт нового посетителя, генерируя имя.
	explicit Customer() {
		name = names[getRandom() % names->size()];
	}

	string toString() {
		return name;
	}
};

class Supermarket {
	queue<Customer> first_queue; //первая очередь
	mutex first_cashier; //первый кассир
	bool isFirstVisitorCame = false; //пришёл ли покупатель в первую очередь

	queue<Customer> second_queue; //вторая очередь
	mutex second_cashier; //второй кассир
	bool isSecondVisitorCame = false; //пришёл ли покупатель во вторую очередь

	condition_variable newVisitor;
	mutex output;
	bool isAllVisitorsCut = false; //обслужены ли все покупатели

	// Оплата покупки на кассе.
	void purchasePayment(Customer& customer) {
		this_thread::sleep_for(chrono::seconds(customer.toString().length() % 3 + 3));
	}

public:
	// Имитирует приход покупателя в супермаркет.
	void customerCome(int numberCustomers) {
		int count = 1; //порядковый номер покупателя
		while (count <= numberCustomers) {
			// Создание покупателя.
			Customer customer = Customer();
			// Посетитель пришёл в супермаркет.
			if (rand() % 2) this_thread::sleep_for(chrono::milliseconds(100));
			output.lock();
			int queue_num = getRandom() % 2; // номер очереди: в которую встаёт покупатель
			cout << "Покупатель " << customer.toString() << " встал в очередь № " << queue_num + 1 << ".\n";
			output.unlock();
			// Покупатель встаёт в очередь.
			if (queue_num == 0) {
				unique_lock<mutex> lock(first_cashier);
				first_queue.push(customer);
				isFirstVisitorCame = true;
			}
			else {
				unique_lock<mutex> lock(second_cashier);
				second_queue.push(customer);
				isSecondVisitorCame = true;
			}
			++count;
			newVisitor.notify_one();
		}
		isAllVisitorsCut = true;
		newVisitor.notify_one();
	}

	/**
	* Симуляция работы первого кассира.
    * Пока кто-то есть в очереди, ждем, пока нас разбудят.
	*/
	void firstCashierWork() {
		unique_lock<mutex> lock(first_cashier);
		while (!isAllVisitorsCut) {
			while (!isFirstVisitorCame && !isAllVisitorsCut) {
				newVisitor.wait(lock);
			}
			// Кассира разбудили: пришёл покупатель.
			while (!first_queue.empty()) { //если есть покупатели, ожидающие свою очередь
				// Кассир берёт следующего покупателя.
				Customer customer = first_queue.front(); //первый покупатель в очереди
				output.lock();
				cout << "Покупатель " << customer.toString() << " подошёл к оплате на кассу № 1.\n";
				output.unlock();
				// Кассир начинает свою работу.
				purchasePayment(customer);
				// Посетитель оплатил покупку и ушёл.
				output.lock();
				cout << "Посетитель " << customer.toString() << " оплатил покупку на кассе № 1 и ушёл.\n";
				output.unlock();
				first_queue.pop();
			}
			isFirstVisitorCame = false;
		}
	}

	/**
	* Симуляция работы второго кассира.
	* Пока кто-то есть в очереди, ждем, пока нас разбудят.
	*/
	void secondCashierWork() {
		unique_lock<mutex> lock(second_cashier);
		while (!isAllVisitorsCut) {
			while (!isSecondVisitorCame && !isAllVisitorsCut) {
				newVisitor.wait(lock);
			}
			// Кассира разбудили: пришёл покупатель.
			while (!second_queue.empty()) { //если есть покупатели, ожидающие свою очередь
				// Кассир берёт следующего покупателя.
				Customer customer = second_queue.front(); //первый покупатель в очереди
				output.lock();
				cout << "Покупатель " << customer.toString() << " подошёл к оплате на кассу № 2.\n";
				output.unlock();
				// Кассир начинает свою работу.
				purchasePayment(customer);
				// Посетитель оплатил покупку и ушёл.
				output.lock();
				cout << "Посетитель " << customer.toString() << " оплатил покупку на кассе № 2 и ушёл.\n";
				output.unlock();
				second_queue.pop();
			}
			isSecondVisitorCame = false;
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Данное приложение моделирует рабочий день супермаркета.\n";

	int number_of_visitors = correctInput();

	Supermarket supermarket;

	thread first_cashier(&Supermarket::firstCashierWork, ref(supermarket));
	thread second_cashier(&Supermarket::secondCashierWork, ref(supermarket));

	thread customers(&Supermarket::customerCome, ref(supermarket), number_of_visitors);

	customers.join();
	first_cashier.join();
	second_cashier.join();

	cout << "Все посетители ушли. Супермаркет закрывается.\n";
	return 0;
}