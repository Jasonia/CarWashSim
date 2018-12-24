/*
 * Car Wash Simulation Program - This program will prompt the user for the amount of time to run the car wash. Cars
 * will randomly get in line (1 every 4 minutes). The program will track the number of cars washed, the average time to wait
 * in the queue, and the number of cars washed.
 *
 * Author : Jason Leong
 * Class : COMP 51
 *
*/

#include <iostream>
#include <ctime>
#include<fstream>
using namespace std;

/*
 * This class represent each car that goes through the car wash. Each car is assigned a number (counter starting from 1),
 * the time the car arrived in the queue, the time the car started to get washed, the type of wash requested, and whether
 * the car is currently in the wash or not.
 *
 * DO NOT MODIFY THIS CLASS. ALL METHODS CAN BE USED AS IS. JUST INVOKE THE METHODS FROM THE CAR WASH CLASS.
*/

class CarToWash {
public:
	CarToWash() {
		carNumber = 0;
		minuteArrival = 0;
		minuteWash = 0;
		washType = 1;
		isCarInWash = false;
	}
	// this setter function will update the car number, the arrival time, the type of wash and whether the car is in the wash all at once
	void setCar(int number, int minute, int type, bool status) {
		carNumber = number;
		minuteArrival = minute;
		isCarInWash = status;
		minuteWash = 0;
		washType = type;
	}
	void setInCarWash(bool status) {
		isCarInWash = status;
	}

	int getStart() {
		return minuteArrival;
	}
	bool getInCarWash() {
		return isCarInWash;
	}
	int getWashStart() {
		return minuteWash;

	}
	int getWashEnd() {
		int result = 0;
		switch (washType) {
		case 1:
			result = getWashStart() + 4 + 1;
			break;
		case 2:
			result = getWashStart() + 6 + 1;
			break;
		case 3:
			result = getWashStart() + 1 + 7;
			break;
		default:
			cout << "Invalid wash type = " << washType;
			system("pause");
			exit(1);
		}
		return result;
	}
	int getCarNum() {
		return carNumber;
	}
	void setWashStart(int startTime) {
		minuteWash = startTime;
	}
private:
	int carNumber;				// identifies the car number beginning with one
	int minuteArrival;			// minute the car arrive as the car wash and started waiting
	int minuteWash;				// time the car actually gets into the car wash
	int washType;				// 1 = standard, 2 = Special, 3 = Extreme
	bool isCarInWash;
};

/*
 * This is the main class for the program. See instructions for defining the properties and methods.
*/

class CarWash {
public:
	CarWash() {
		numbers = 0;
		maxQueue = 0;
		queueTime = 0;
		totalCars = 0;
		closingTime = 0;
		minutesOpen = 0;
		numberCarsExited = 0;
	}

	void openUp(int time) {
		closingTime = time;
	}

	void updateTimer(bool Car) {
		ofstream out("input.txt", ios::app);
		cout << "Time(" << minutesOpen << ")" << endl;
		out << "Time(" << minutesOpen << ")\n\n" << endl;
		bool finish = false;
		if (numbers > 0) {

			cout << "Car " << totalCars + 1 << " is being washed. " << endl;
			out << "Car " << totalCars + 1 << " is being washed.\n\n " << endl;
			if (cars[0].getWashEnd() == minutesOpen) {
				cout << "Finished car " << cars[0].getCarNum() << " at time : " << minutesOpen << std::endl;
				out << "Finished car " << cars[0].getCarNum() << " at time : " << minutesOpen << "\n\n" << std::endl;
				cars[numbers].setInCarWash(false);

				queueTime += cars[0].getWashStart() - cars[0].getStart();
				cout << "this is the getwashtime" << cars[0].getWashStart() << "\nthis is getstart time" << cars[0].getStart() << endl;
				cout << "This is the que time" << queueTime << endl;
				finish = true;
				for (int i = 1; i < numbers; i++) {
					cars[i - 1] = cars[i];
				}
				totalCars++;
				numbers--;
			}
		}

		if (Car) {
			cout << "New Car has arrived at time : " << minutesOpen << endl;
			out << "New Car has arrived at time : " << minutesOpen << "\n\n" << endl;
			//totalCars++;
			int type = rand() % 10;

			if (type < 5) {
				type = 1;
			}
			else if (type < 8) {
				type = 2;
			}
			else {
				type = 3;
			}

			if (numbers < 5) {
				if (numbers == 0) {
					cars[numbers].setCar(totalCars + numbers + 1, minutesOpen, type, true);
				}
				else {
					cars[numbers].setCar(totalCars + numbers + 1, minutesOpen, type, false);
					cout << minutesOpen << "minutes open " << endl;
					out << minutesOpen << "minutes open " << endl;
				}
				numbers++;
				if (numbers > maxQueue) {
					maxQueue = numbers;
				}
				cout << "Next Car Wash Type = " << type << endl;
				out << "Next Car Wash Type = " << type << endl;
				cout << "Cars in queue = " << numbers << endl;
				out << "Cars in queue = " << numbers << endl;
			}
			else {
				numberCarsExited++;
				cout << "\tCar wash is full, Car exited at minute : " << minutesOpen << endl;
				out << "\tCar wash is full, Car exited at minute : " << minutesOpen << endl;
			}
		}
		if (finish || (Car && numbers == 1)) {
			////
			cars[0].setWashStart(minutesOpen);

			cars[0].setInCarWash(true);
			cout << "Next car " << cars[0].getCarNum() << " started at time : " << cars[0].getWashStart() << endl;
			out << "Next car " << cars[0].getCarNum() << " started at time : " << cars[0].getWashStart() << endl;
		}
		minutesOpen++;
		cout << endl;
		out.close();
	}

	void displayStats() {
		ofstream out("input.txt", ios::app);
		cout << "Total Number of Cars Washed: " << totalCars + numbers << endl;
		out << "Total Number of Cars Washed: " << totalCars + numbers << endl;
		cout << "Cars Turned Away: " << numberCarsExited << std::endl;
		out << "Cars Turned Away: " << numberCarsExited << std::endl;
		cout << "Average Time in Queue: " << (double)queueTime / totalCars << endl;
		out << "Average Time in Queue: " << (double)queueTime / totalCars << endl;
		cout << "Max Queue Size: " << maxQueue << endl;
		out << "Max Queue Size: " << maxQueue << endl;
		out.close();
	}

private:
	int numbers;
	int maxQueue;
	int queueTime;
	int totalCars;
	int closingTime;
	int minutesOpen;
	int numberCarsExited;
	CarToWash cars[5];

};

// Returns true 25% of the time
bool arrival() {
	if ((rand() % 4) == 0)
		return true;
	else
		return false;
}
void makefile()
{
	ofstream out;
	out.open("input.txt");
	out.close();
}
/*
 * This is the main function which defines the car wash object. It prompts the user for how long to run the car wash
 * It then calls the timer function to simulate the car wash. Students should not have to change this code.
 */

int main()
{
	int runFor;
	int i;

	CarWash cw;		// main car wash variable
	srand((unsigned)time(0));
	makefile();
	ofstream out("input.txt", 'a');
	cout << "Welcome to COMP 51 Car Wash Simulator\n";
	//out << "Welcome to COMP 51 Car Wash Simulator\n" << endl;
	cout << "Please enter the number of minutes to operate: ";
	//out << "Please enter the number of minutes to operate: ";
	cin >> runFor;
	cw.openUp(runFor);

	for (i = 0; i < runFor; i++)
		cw.updateTimer(arrival());
	cw.displayStats();

	system("PAUSE");
	return 0;
}