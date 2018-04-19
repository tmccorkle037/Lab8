#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <stdio.h>

using namespace std;

class Signal {
private:
	int length = 0;
	int max = 0;
	int min = 0;
	double average = 0;

public:
	vector<int> rawData;
	vector<double> newData;
	Signal();	//default constructor
	Signal(int fileNum);	//parametric constructor
	Signal(string name);	//parametric constructor
	void displayError();
	~Signal();	//destructor
	void offsetData(double offset);
	void scaleData(double scale);
	void normalizeData();
	void centerData();
	void getStats();
	void menu();
	void sig_info();
	void save_file();
	void operator+(double num);
	void operator*(double multiplier);
	int getLength();
	double getMax();
	int calculateMax();//changed from private to public so non-memeber operator could access
	void getMin();//changed from private to public so non-memeber operator could access
	double getAverage();//changed from private to public so non-memeber operator could access
	void setMax(double max);
};

Signal::Signal() {
	//take default file and fill in info
	//cout << "creating signal" << endl;
	string defaultFile = "Raw_data_01.txt";	//default file, user did not provide any information
	ifstream inFS;
	int i = 0;

	inFS.open(defaultFile);

	inFS >> length;
	inFS >> max;
	int valTemp;

	while (i < length) {
		inFS >> valTemp;
		rawData.push_back(valTemp);
		//cout << "inside constructor" << endl << rawData[i] << endl;
		i++;
	}

	inFS.close();
}

Signal::Signal(int fileNum) {
	string name;
	if (fileNum < 10) {
		name = "Raw_data_0" + to_string(fileNum) + ".txt";
	} else {
		name = "Raw_data_" + to_string(fileNum) + ".txt";
	}

	ifstream inFS;
	int i = 0;

	inFS.open(name);

	inFS >> length;
	inFS >> max;
	int valTemp;

	while (i < length) {
		inFS >> valTemp;
		rawData.push_back(valTemp);	//saves the data to the rawData vector
		i++;
	}
	inFS.close();
}

Signal::Signal(string fileName) {
	//add error check to make sure it's a .txt file
	string name = fileName;
	ifstream inFS;
	int i = 0;

	inFS.open(name);

	inFS >> length;
	inFS >> max;
	int valTemp;

	while (i < length) {
		inFS >> valTemp;
		rawData.push_back(valTemp);	//saves the data to the rawData vector
		i++;
	}

	inFS.close();
}

void Signal::offsetData(double offset) {
	cout << "inside offset method" << endl;
	cout << "length = " << length << endl;
	double tempVal = 0;
	newData.clear();

	for (int i = 0; i < length; i++) {
		tempVal = (rawData[i] + offset);
		cout << "Temp value: " << tempVal << endl;
		newData.push_back(tempVal);
	}
}

void Signal::scaleData(double scale) {
	cout << "inside scaling method" << endl;
	cout << "length = " << length << endl;
	double tempVal = 0;
	newData.clear();
	for (int i = 0; i < length; i++) {
		tempVal = (rawData[i] * scale);
		cout << "Temp value: " << tempVal << endl;
		newData.push_back(tempVal);
	}
}

double Signal::getAverage() {	//returns the average which is a double
	double ave = 0;
	if (newData.size() == 0) {
		for (int i = 0; i < length; i++) {
			ave += rawData[i];
		}
	}
	else {
		for (int i = 0; i < length; i++) {
			ave += newData[i];
		}
	}

	average = ave / length;
	return average;

}

int Signal::calculateMax() {	//returns the maximum number in the data
	int max = 0;

	if (newData.size() == 0) {
		for (int i = 0; i < length; i++) {
			if (rawData[i] > max) {
				max = rawData[i];
			}
		}
	} else {
		for (int i = 0; i < length; i++) {
			if (newData[i] > max) {
				max = newData[i];
			}
		}
	}

	this->max = max;
	return max;
}

void Signal::getMin() {	//returns the maximum number in the data
	int min = 0;
	for (int i = 0; i < length; i++) {
		if (rawData[i] < min) {
			min = rawData[i];
		}
	}
	this->min = min;
}

void Signal::normalizeData() {
	double tempVal = 0;
	int max = this->getMax();//calls calculateMax for the current object by using 'this' keyword
	cout << "Max: " << max << endl;
	newData.clear();

	operator*(1 / static_cast<double>(max)); //send the fraction because the multiplication operator is called
}

void Signal::centerData() {
	double tempVal = 0;
	double a = this->getAverage();//calls getAverage to get the average value of the raw data
	cout << "Average: " << a << endl;
	newData.clear();

	operator+(-a);//send negative number because your using the addition operator
}

void Signal::getStats() {
	cout << "Max = " << calculateMax() << endl;
	cout << "Average = " << getAverage() << endl;
	cout << "Raw Data:" << endl;

	for (int y = 0; y < length; y++) {
		cout << rawData[y] << "   ";
	}
	if (newData.size() != 0) {	//error check to make sure newData is not null
		cout << "\nNew Data:" << endl;
		for (int x = 0; x < length; x++) {
			cout << newData[x] << "   ";
		}
		cout << endl;
	} else
		cout << "\nNo new Data." << endl;
}

void Signal::sig_info() {
	//to  display  the  length,  the  current  maximum/minimum  values  and  the  current average of the signal.
	cout << "Current Length = " << length << endl;
	getMin();
	cout << "Current min = " << min << endl;
	cout << "Current max = " << calculateMax() << endl;
	cout << "Current average = " << getAverage() << endl;
}

void Signal::save_file() {
	string fileName;
	ofstream of;

	if (newData.size() == 0) {
		cout << "There is no current data. Run an opertation on the "
				"\noriginal signal to get new data." << endl;
	} else {
		cout << "Enter new file name : ";
		cin >> fileName;

		of.open(fileName);
		of << length << " " << max << "\n";

		for (int i = 0; i < length; i++) {
			of << newData[i] << "\n";
		}
	}
	of.close();
}

void Signal::operator +(double num) {

	for (int i = 0; i < length; i++) {
		//add a value to each signal value in the vector
		newData.push_back(rawData[i] + num);
	}
}

void Signal::operator *(double multiplier) {

	for (int i = 0; i < length; i++) {
		//add a value to each signal value in the vector
		newData.push_back(rawData[i] * multiplier);
	}
}

void Signal::menu() {
	int choice = 0;
	double offsetVal = 0;
	double scale = 0;
	int stats = 0;
	int normalize = 0;
	int center = 0;

	while (choice != 8) {
		cout << "Choose an option:" << endl << "1) Offset" << endl << "2) Scale"
				<< endl << "3) Center" << endl << "4) Normalize" << endl
				<< "5) Statistics" << endl << "6) Signal Info" << endl
				<< "7) Save Signal" << endl << "8) EXIT" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter an offset value: ";
			cin >> offsetVal;
			cout << "Offset value: " << offsetVal << endl;
			offsetData(offsetVal);
			break;
		case 2:
			cout << "Enter a scaling factor: ";
			cin >> scale;
			cout << "Scaling value: " << offsetVal << endl;
			scaleData(scale);
			break;
		case 3:
			cout << "Centering data..." << endl;
			centerData();
			cout << "Centering complete." << endl;
			break;
		case 4:
			cout << "Normalizing data..." << endl;
			normalizeData();
			cout << "Normalizing complete." << endl;
			break;
		case 5:
			cout << "Getting statistics..." << endl;
			getStats();
			break;
		case 6:
			sig_info();
			break;
		case 7:
			save_file();
			break;
		case 8:
			cout << "Goodbye!" << endl;
			break;
		default:
			cout << "Option not available, choose again" << endl;
		}
	}
}

Signal::~Signal() {
	//there is no data to free
}

int Signal::getLength() {
	return length;
}
double Signal::getMax(){
	return max;
}
void Signal::setMax(double max){
	this->max = max;
}

//non-member operator
Signal operator+(Signal sig1, Signal sig2) {
	Signal totalSig;
	int length = sig1.getLength();//both should be the same size so it doesn't matter which signal is used
	int n1;
	int n2;

	if (sig1.getLength() != sig2.getLength()) {
		cout << "Signals must be the same size" << endl;
		return 0;
	}

	for (int i = 0; i < length; i++) {
		totalSig.newData.push_back(sig1.rawData[i] + sig2.rawData[i]);
		cout <<"totalSig[" << i << "]: " << totalSig.newData[i] << endl;
	}

	if(sig1.calculateMax() > sig2.calculateMax()){
		totalSig.setMax(sig1.getMax());
	}
	else{
		totalSig.setMax(sig2.getMax());
	}
	cout << "Maximum: " << totalSig.getMax() << endl;
	cout << "Total Average: " << totalSig.getAverage() << endl;

	return totalSig;
}

int main(int argc, char **argv) {
	int fileNum = 0;
	string name = "";
	int i = 0;

	for (int c = 0; c < argc; c++) {//parse the command line to see what info the user provided
		if (strncmp(argv[i], "-n", 2) == 0) {	//if the option is -n
			fileNum = atoi(argv[i + 1]);
			cout << "file number " << fileNum << endl;
		} else if (strncmp(argv[i], "-f", 2) == 0) {
			name = argv[i + 1];
			cout << "file name:" << name << endl;
		}
		i++;
	}

	if (fileNum != 0) {	//the file num was given
		cout << "calling num constructor" << endl;
		Signal s1(fileNum);
		s1.menu();
	} else if (name != "") {	//the file name was given
		Signal s1(name);
		s1.menu();
	} else {	//use default constructor bc user enterd no data about the file
		Signal s1;
		s1.menu();
	}

	int opt = 1;
	int num1;
	int num2;

	cout << "\n----Testing non-member operator----"<< endl;

	while(opt != 0){
		cout << "\nEnter 2 file numbers: " << endl;
		cin >> num1 >> num2;

		Signal s2(num1);
		Signal s3(num2);
		Signal s4 = operator+(s2, s3);
		//cout << "s4 created" << endl;
		cout << "\nAgain? 1:Yes 0:No" << endl;
		cin >> opt;
	}

	return 0;
}