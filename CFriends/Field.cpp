#include "Include.h"
#include "Field.h"

void Field::init()
{
	traverse(0);
}

void Field::update(double dt)
{



}

void Field::display()
{

	setColor(255);
	for (int i = 0; i < 10; i++)
	{
		if (i % 3 == 0) 
		{
			setLineWidth(4);
		}
		else
		{
			setLineWidth(1);
		}
		line(0, i * getHeight() / 9, getWidth(), i * getHeight()/9);
		line(i * getWidth()/9, 0 , getWidth() * i / 9, getHeight());
	}
	
}

void Field::print()
{
	std::cout << "\n";
	for (int i = 0; i < 9; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < 9; j++)
		{
			std::cout << " " << field[j][i] << " ";
		}
	}

	std::cout << "\n";

}

bool Field::traverse(int pos)
{
	if (pos >= 81)
	{
		std::cout << "fertig";
		return true;
	}
	std::vector<int> valid;
	valid.assign({ 1,2,3,4,5,6,7,8,9 });
	int validSize = valid.size();

	int choice;
	do
	{
		std::cout << "\nDepth: " << pos << "\n";
		do 
		{
			if (validSize == 0) return false;
			int index = randi(0, validSize - 1);
			choice = valid.at(index);
			valid.erase(valid.begin() + index);
			validSize--;
			std::cout << " " << validSize << " ";

		} while (!isValueValid(choice, pos));
		

		
		field[pos % 9][pos / 9] = choice;
		print();
		

	} while (!traverse(pos+1));

	
	return true;

	
}




bool Field::isValueValid(int v, int pos)
{
	int x = pos % 9;
	int y = pos / 9;

	for (int i = 0; i < 9; i++)
	{
		if (i != x)
		{
			if (field[i][y] == v) return false;
		}
		
	}

	for (int i = 0; i < 9; i++)
	{
		if (i != y)
		{
			if (field[x][i] == v) return false;
		}

	}


	
	for (int i = (y/3)*3; i < (y / 3) * 3 + 3; i++)
	{
		for (int j = (x/3)*3; j < (x / 3) * 3 + 3; j++)
		{
			if (i == y && j == x) continue;
			else if (field[j][i] == v) return false;
			
		}
	}
	
	return true;

}
