#include<SFML/Graphics.hpp>
#include<iostream>
#include"Windows.h"
#include <ctime>
#include <stdlib.h>     
#include <time.h> 
#include <cstdlib>
#include<conio.h>
using namespace std;
sf::RenderWindow window(sf::VideoMode(850, 850), "Rat In Maze");
int counter = 0;
template <typename t>
class stack
{
	class node
	{
		int x;   //x and y are coordinates
		int y;
		node* next;
		friend class stack<t>;
	public:
		node()
		{
			x = -1;
			y = -1;
			next = nullptr;
		}

		node(int xco, int yco, node* n)
		{
			x = xco;
			y = yco;
			next = n;
		}

		node(const node& obj)
		{
			this->x = obj.x;
			this->y = obj.y;
			this->next = obj.next;
		}
		~node()
		{
			next = nullptr;
		}
	};


	node* top;
public:
	stack();
	stack(node*);
	stack(const stack&);
	bool isempty();
	bool isfull();
	void push(int, int);
	void pop(int&, int&);
	int* topvalue();

};

template <typename t>
stack<t>::stack()
{
	top = nullptr;
}

template <typename t>
stack<t>::stack(node* pointer)
{
	top = pointer;
}

template <typename t>
stack<t>::stack(const stack& obj)
{
	this->top = obj.top;
}

template <typename t>
bool stack<t>::isempty()
{
	if (top == nullptr)
		return true;
	else
		return false;
}

template <typename t>
bool stack<t>::isfull()
{
	return false;
}

template <typename t>
void stack<t>::push(int xco, int yco)
{
	node* temp = new node;
	temp->x = xco;
	temp->y = yco;
	if (isempty())
	{
		temp->next = nullptr;
		top = temp;
	}
	else if (top != nullptr)
	{
		temp->next = top;
		top = temp;
	}
	counter++;
}

template <typename t>
void stack<t> ::pop(int& xco, int& yco)
{
	node* temp = top;
	top = top->next;
	xco = temp->x;
	yco = temp->y;
	delete temp;
	temp = nullptr;
	counter--;
}

template <typename t>
int* stack<t>::topvalue()
{
	int* arr = new int[2];
	arr[0] = this->top->x;
	arr[1] = this->top->y;
	return arr;

}



void printarr(int** arr, int r, int c)
{
	for (int i = 0;i < r;i++)
	{
		for (int j = 0;j < c;j++)
		{
			cout << arr[i][j];
		}
		cout << endl;
	}
}




void gamelogic()
{
	int r = 0, c = 0;
	int entry1 = -1, entry2 = -1;
	int destination1 = -1, destination2 = -1;
	cout << "enter rows for the maze: ";
	cin >> r;
	cout << endl;
	cout << "enter columns for the maze: ";
	cin >> c;
	cout << endl;
	int** arr = new int* [r];
	for (int i = 0;i < r;i++)
	{
		arr[i] = new int[c];
	}
	for (int i = 0;i < r;i++)
	{
		for (int j = 0;j < c;j++)
		{
			arr[i][j] = 1;               //1 shows the possibe places to visit
		}
	}
	cout << "enter row index for entry point: ";
	cin >> entry1;
	cout << endl;
	cout << "enter column index for entry point: ";
	cin >> entry2;
	cout << endl;

	cout << "enter row index for destination point: ";
	cin >> destination1;
	cout << endl;
	cout << "enter column index for destination point: ";
	cin >> destination2;
	cout << endl;

	if (r <= 8 )
	{
		sf::RectangleShape line1(sf::Vector2f(r * 100, 1));   //Vector2f(500, 1)
		line1.rotate(90);
		sf::RectangleShape line2(sf::Vector2f(c * 100, 1));
		
			for (int i = 1; i < (c * 100) + 100; i = i + 100)                  //(int i = 1; i < 600; i = i + 100)
			{

				line1.setPosition(i, 0);                               //line1.setPosition(i, 0);

				window.draw(line1);

			}
			for (int i = 0; i < (r * 100) + 100; i = i + 100)                    //(int i = 0; i < 600; i = i + 100)
			{

				line2.setPosition(0, i);                               //line2.setPosition(0, i);
				window.draw(line2);
			}


	}















	////////////////////////////////////////////////////////////////////////////


	int num;
	srand(time(0));
	int totalblocks = r * c;
	num = 0 + rand() % (totalblocks - 0 + 1);   //num is total hurdles
	num = num / 2;     //to keep the number low as compared to the free blocks
	cout << "number of hurdles: " << num << endl;
	int* numx = new int[num];
	int* numy = new int[num];
	for (int i = 0;i < num;i++)
	{
		numx[i] = 0 + rand() % (((r - 1) + 1) - 0);    //numx conatins all x coordinates for random placement
	}
	for (int i = 0;i < num;i++)
	{
		numy[i] = 0 + rand() % (((c - 1) + 1) - 0);    //numy conatins all y coordinates for random placement
	}
	for (int i = 0;i < num;i++)
	{
		arr[numx[i]][numy[i]] = 0;     //0 shows hurdles
		cout << "hurdle at: " << numx[i] << "  " << numy[i] << endl;
		//printarr(arr, r, c);

	}

	arr[entry1][entry2] = 2;           //2 shows entry point
	int temp1 = entry1;
	int temp2 = entry2;
	arr[destination1][destination2] = 3;   //2 shows destination point

	/////////////////////////////////////


	sf::Texture green;               //starting position, ending point
	if (!(green.loadFromFile("green.png")))
	{
		cout << "error\n";
	}
	sf::Sprite g;
	g.setTexture(green);
	if (r <= 8)
	{
		g.setScale(sf::Vector2f(0.16, 0.16));
		for (int i = 0;i < r;i++)
		{
			for (int j = 0;j < c;j++)
			{
				if (arr[i][j] == 2 )
				{
					g.setPosition(j * 100, i * 100);
					window.draw(g);
				}
			}
		}
	}


	if (r <= 8)    //destination
	{
		g.setScale(sf::Vector2f(0.16, 0.16));
		for (int i = 0;i < r;i++)
		{
			for (int j = 0;j < c;j++)
			{
				if (arr[i][j] == 3)
				{
					g.setPosition(j * 100, i * 100);
					window.draw(g);
				}
			}
		}
	}



	sf::Texture hurdles;
	if (!(hurdles.loadFromFile("blue.png")))
	{
		cout << "error\n";
	}
	for (int i = 0;i < r;i++)
	{
		for (int j = 0;j < c;j++)
		{
			if (arr[i][j] == 0)
			{
			
				sf::Sprite b;
				b.setTexture(hurdles);
				b.setScale(sf::Vector2f(0.08, 0.08));
				if(i==0 && j==0)
				    b.setPosition(i, j );
				else if(i==0 && j!=0)
					b.setPosition(j*100,i);
				else if(i!=0 && j==0)
					b.setPosition( j, i * 100);
				else
					b.setPosition(j*100, i*100);


				window.draw(b);

			}
		}
	}


	//window.display();  





	
	/////////////////////////////////////


	//0 for hurdles, 1 for all possible blocks , 2 for source and 3 for destination

	printarr(arr, r, c);
	cout << endl;

	stack<int>s;
	s.push(entry1, entry2);
	int* coord = new int[2];
	int popedx = -1, popedy = -1;
	bool flag = false;
	bool flagfordes = false;
	if (entry1 == destination1 && entry2 == destination2)
	{
		flagfordes = true;
		s.push(entry1, entry2);
		arr[entry1][entry2] = 9;
	}
	while (!flagfordes)
	{
		
		if (entry2 + 1 < c && arr[entry1][entry2 + 1] == 1)
		{
			s.push(entry1, entry2 + 1);
			arr[entry1][entry2 + 1] = 9;
			entry2 = entry2 + 1;
		}
		
		else if (entry2 - 1 >= 0 && arr[entry1][entry2 - 1] == 1)
		{
			s.push(entry1, entry2 - 1);
			arr[entry1][entry2 - 1] = 9;
			entry2 = entry2 - 1;

		}
	
		else if (entry1 + 1 < r && arr[entry1 + 1][entry2] == 1)
		{
			s.push(entry1 + 1, entry2);
			arr[entry1 + 1][entry2] = 9;
			entry1 = entry1 + 1;

		}
		else if (entry1 - 1 >= 0 && arr[entry1 - 1][entry2] == 1)
		{
			s.push(entry1 - 1, entry2);
			arr[entry1 - 1][entry2] = 9;
			entry1 = entry1 - 1;

		}
		//}
		else
		{
			s.pop(popedx, popedy);
			arr[popedx][popedy] = 7;         //////blocked visits
			coord = s.topvalue();
			entry1 = coord[0];
			entry2 = coord[1];
		}
		if (entry1 + 1 < r)
		{
			if (arr[entry1 + 1][entry2] == 3)
			{
				flagfordes = true;
				s.push(entry1 + 1, entry2);
				//arr[entry1 + 1][entry2] = 9;    //remove this to keep 3 in the grid
			}
		}
		if (entry1 - 1 >= 0)
		{
			if (arr[entry1 - 1][entry2] == 3)
			{
				flagfordes = true;
				s.push(entry1 - 1, entry2);
				//arr[entry1 - 1][entry2] = 9; //remove this to keep 3 in the grid

			}
		}
		if (entry2 + 1 < c)
		{
			if (arr[entry1][entry2 + 1] == 3)
			{
				flagfordes = true;
				s.push(entry1, entry2 + 1);
				//arr[entry1][entry2 + 1] = 9;  //remove this to keep 3 in the grid

			}
		}
		if (entry2 - 1 >= 0)
		{
			if (arr[entry1][entry2 - 1] == 3)
			{
				flagfordes = true;
				s.push(entry1, entry2 - 1);
				//arr[entry1][entry2 - 1] = 9;   //remove this to keep 3 in the grid

			}
		}


		cout << endl;
		printarr(arr, r, c);
		cout << endl;


	}
	//arr[temp1][temp2] = 9;    //remove this to keep 2 in grid

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	window.display();                           //the final path

	sf::Texture finalpath;
	if (!(finalpath.loadFromFile("yellow.png")))
	{
		cout << "error\n";
	}
	for (int i = 0;i < r;i++)
	{
		for (int j = 0;j < c;j++)
		{
			if (arr[i][j] == 9)
			{

				sf::Sprite y;
				y.setTexture(finalpath);
				y.setScale(sf::Vector2f(0.08, 0.08));
				if (i == 0 && j == 0)
				{
					y.setPosition(i, j);
					window.display();
					window.draw(y);
					window.display();
					//Sleep(1000);

				}
				else if (i == 0 && j != 0)
				{
					y.setPosition(j * 100, i);
					window.display();
					window.draw(y);
					window.display();
					//Sleep(1000);

				}
				else if (i != 0 && j == 0)
				{
					y.setPosition(j, i * 100);
					window.display();
					window.draw(y);
					window.display();
					//Sleep(1000);

				}
				else
				{
					y.setPosition(j * 100, i * 100);	
					window.display();
					window.draw(y);
					window.display();
					//Sleep(1000);


				}	
     		}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	window.display();
	sf::Texture cantgo;
	if (!(cantgo.loadFromFile("red.png")))
	{
		cout << "error\n";
	}
	sf::Sprite cg;
	cg.setTexture(cantgo);
	cg.setScale(sf::Vector2f(0.08, 0.08));
	cg.setScale(sf::Vector2f(0.16, 0.16));
	for (int i = 0;i < r;i++)
	{
		for (int j = 0;j < c;j++)
		{
			if (arr[i][j] == 7)
			{
				cg.setPosition(j * 100, i * 100);


				/*if (i == 0 && j == 0)
					cg.setPosition(i, j);
				else if (i == 0 && j != 0)
					cg.setPosition(j * 100, i);
				else if (i != 0 && j == 0)
					cg.setPosition(j, i * 100);
				else
					cg.setPosition(j * 100, i * 100);*/


				window.draw(cg);
				window.display();

			}
		}
	}


	//window.display();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	printarr(arr, r, c);


}


int main()
{

	gamelogic();
	window.display();
	system("pause");
	return 0;
}


