// L13_Ex1_ABC.cpp
// By Luis Rivera

#include <iostream>
using namespace std;

class BaseConic {
	protected:
		double x;//x value of center of conic
		double y;//y value of center of conic

	public:
		// Notice the default values. They don't need to be 0
		BaseConic(double x0 = 0, double y0 = 0){x = x0; y = y0;}
		virtual ~BaseConic(){};
		void Move(double nx, double ny){x = nx; y = ny;}
		virtual double Area() = 0; // a pure virtual function ==> ABC
		virtual void display() = 0;

};

class Ellipse : public BaseConic {
	private:
		double a; 	// semi-major axis
		double b; 	// semi-minor axis
		double angle; // orientation angle
		double vertice1;
		double vertice2;
		double originX;
		double originY;

	public:
		Ellipse(double x0, double y0, double a0, double b0, double an0);
		~Ellipse(){}
		virtual double Area() {return 3.1416*a*b;}
		void Rotate(double nang){angle += nang;}
		virtual void display();
		void resize(double major, double minor);
		void calculate();
};

// Notice the default values. Those are used if no parameter is given when
// an object is created.
// Notice how the BaseConic constructor can be called. If other constructors where defined,
// those could be used instead.
Ellipse::Ellipse(double x0=1,double y0=0,double a0=0,double b0=0,double an0=0) : BaseConic(x0,y0) {
	// x and y are set in the BaseConic constuctor
	a = a0;
	b = b0;
	angle = an0;
}

void Ellipse::display() {
	cout << "x = " << x << ", y = " << y << ", a = " << a << ", b = " << b
		 << ", angle = " << angle << ", Area = " << this->Area() << endl;
}

void Ellipse::resize(double major, double minor ){
	a = major;
	b = minor;
//	display();	//test to make sure it works
}

void Ellipse::calculate(){
	vertice1 = (a/2)-x;
	vertice2 = (a/2)+x;

	cout << "left vertice is at: " << vertice1 << endl;
	cout <<"Right vertice is at: " << vertice2 << endl;
}

class Circle : public BaseConic {
	private:
		double r; 	// radius
		
	public:
		virtual double Area() {return 3.1416*r*r;}
		Circle(double x0=1,double y0=1,double r0=1) : BaseConic(x0,y0){r = r0;}
		virtual void display();
		void resize(double radius);
		bool inOrOut(double x, double y);
};
void Circle::resize(double radius){
	r = radius;
}
void Circle::display() {
	cout << "x = " << x << ", y = " << y << ", r = " << r 
		 << ", Area = " << this->Area() << endl;
}
bool Circle::inOrOut(double x, double y){
	if(x > this->x - r && x < this->x + r ){	//determine if x value is within circle
		if( y > this->y-r && y < this->y + r){	//determine if y value is within circle
			return true;
		}
	}
	else{ return false;}
}
int main(){
	//BaseConic b0;	// not possible to create an object of the ABC
	Ellipse e0, e1(1), e2(2,3), e3(4,5,6), e4(7,8,9,10), e5(0.1,0.2,0.3,0.4,0.5);
	Circle c0, c1(2,-1,5);
		
//	e0.display();	e1.display();	e2.display();
//	e3.display();	e4.display();	e5.display();
//
//	cout << "\n--------------------------------------------------------------\n" << endl;
//
//	c0.display();	c1.display();
//
//	cout << "\n--------------------------------------------------------------\n" << endl;
//
//	// You CAN use ABC pointers and references
//	BaseConic *bptr1 = &e4;
//	BaseConic *bptr2 = new Ellipse(1,1,2,3,0.5);
//	BaseConic &bref1 = e5;
//	bptr1->display();
//	bptr2->display();
//	bref1.display();
//
//	cout << "\n--------------------------------------------------------------\n" << endl;
//	BaseConic *bptr3 = &c0;
//	BaseConic *bptr4 = new Circle(-3,0,1.5);
//	BaseConic &bref2 = c1;
//	bptr3->display();
//	bptr4->display();
//	bref2.display();
	
	cout << "---TESTING LAB 8---" << endl;
	int loop = 0;

	e1.display();
	c1.display();

	while (loop != 7) {
		cout << "Choose an option:" << endl << "1) Move" << endl
				<< "2) Calculate area" << endl << "3) Resize" << endl
				<< "4) See if point is inside circle" << endl
				<< "5) Rotate Ellipse" << endl
				<< "6) Calculate Vertices of the Ellipse" << endl << "7) EXIT"
				<< endl;
		cin >> loop;

		switch(loop){
		case 1:	//move conic
			cout << "***MOVING CONICS***" << endl;
			e1.Move(5.5, 1.3);
			c1.Move(3.0, 2.0);

			e1.display();
			c1.display();
			break;
		case 2: //calculate area
			cout << "***CALACULATING AREA***" << endl;
			cout << "The area of e1 = " << e1.Area() << endl;
			cout << "The area of c1 = " << c1.Area() << endl;
			break;
		case 3:	//Resize conics
			e1.resize(5,2);
			c1.resize(5.3);

			e1.display();
			c1.display();
			break;
		case 4:	//determine if point is inside circle
			if(c1.inOrOut(0,0) == true){
				cout << "The point (0,0) is within the circle" << endl;
			}
			else{
				cout << "The point (0,0) is not within the circle" << endl;
			}
			break;
		case 5: //rotate ellipse
			e1.Rotate(12);
			e1.display();
			break;
		case 6:	//calculate vertices
			e1.calculate();
			break;
		case 7:
			break;
		}
	}
//	delete bptr2;
//	delete bptr4;
}
