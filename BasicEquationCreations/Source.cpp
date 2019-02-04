#include <iostream>
#include "Matrix.h"
#include "BasicIO.h"
#include <vector>
#include <string>
#include <math.h>

struct point
{
	float x;
	float y;
};


std::vector<point> pointsOfEquation = std::vector<point>();

void getValues(char* filename)
{
	BasicIO file(filename);

	std::string tempData = "";
	char byte = '\0';

	bool xSet = false;

	point tempPoint;

	while (!file.isEndOfFile())
	{
		byte = file.readByte();

		if (byte != ',')
		{
			tempData += byte;
		}
		else
		{
			if (xSet == false)
			{
				tempPoint.x = std::stof(tempData);
				tempData = "";
				xSet = true;
			}
			else
			{
				tempPoint.y = std::stof(tempData);
				tempData = "";
				xSet = false;

				pointsOfEquation.push_back(tempPoint);
			}
		}
	}

	file.close();
}

void createEquation()
{
	//float* values = new float[pointsOfEquation.size()];

	Matrix A = Matrix(pointsOfEquation.size(), pointsOfEquation.size());
	
	for(int i=0; i<A.getRows(); i++)
	{ 
		for (int i2 = 0; i2 < A.getCols(); i2++)
		{
			if (A.getCols() - i2-1 == 0)
			{
				A[i][i2] = 1;
			}
			else if (A.getCols() - i2-1 == -1)
			{
				A[i][i2] = pointsOfEquation[i].y;
			}
			else
			{
				A[i][i2] = pow(pointsOfEquation[i].x, A.getCols() - i2-1);
			}
		}
	}

	Matrix matrixOfY = Matrix(pointsOfEquation.size(), 1);

	for (int i = 0; i < A.getRows(); i++)
	{
		matrixOfY[i][0] = pointsOfEquation[i].y;
	}

	Matrix inverseMat = A.getInverse();

	Matrix finalAnswers = inverseMat * matrixOfY;

	for (int i = 0; i < finalAnswers.getRows(); i++)
	{
		if (finalAnswers.getRows() - 1 - i == 0)
		{
			std::cout << finalAnswers[i][0] << std::endl;
		}
		else if (finalAnswers.getRows() - 1 - i == 0)
		{
			std::cout << finalAnswers[i][0] << " X" << std::endl;
		}
		else
		{
			std::cout << finalAnswers[i][0] << " X^" << finalAnswers.getRows() - 1 - i << std::endl;
		}
	}
}

void main(int sizeOfInput, char** input)
{
	for (int i = 0; i < sizeOfInput; i++)
	{
		std::cout << input[i] << std::endl;
	}

	if (sizeOfInput > 1)
	{
		getValues(input[1]);
		createEquation();
	}
	else
	{
		std::cout << "Not enough inputs" << std::endl;
		std::cout << "Requires a file with values separated by commas with an ending comma" << std::endl;
	}

	getValues((char*)"testFile3.txt");
	createEquation();
	system("pause");
}