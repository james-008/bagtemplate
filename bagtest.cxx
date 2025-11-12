/*
 * Sin-Yaw Wang <swang24@scu.edu>
 * Name: Isaac Amedie, Michael Tiburcio, Ryan Vattuone, Guseerat Kakar
 * Email: iamedie@scu.edu, mtiburcio@scu.edu, rvattuone@scu.edu, gkakar@scu.edu
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "person.h"
#include "bag.h"
 

using namespace std;
using namespace csen79;

inline double BMI(const double weight, const double height) {
	return (weight / (height * height)) * 703.0;
}



int main(int argc, char *argv[]) {
    Bag<Person> plist;
    Person p;
	constexpr double targetHeight = 70.0;
	constexpr double targetWeight = 150;
	const double targetBMI = BMI(targetWeight, targetHeight);
	constexpr Person::Gender targetGender = Person::Female;
	const std::pair<double, string> BMICategory[] = {{18.85, "Underweight"},
	                                         {24.99, "Normal weight"},
											 {29.99, "Overweight"},
											 {1000.0, "Obesity"}};

	std::map<string, int> BMICount = {{"Underweight", 0},
	                                         {"Normal weight", 0},
											 {"Overweight" , 0},
											 {"Obesity" , 0}};
	

	//lambda function for storting
	auto lastname_compare = [](const Person& a, const Person& b)
	{
		if(a.getGender() == b.getGender())
		{
			return a.getLName() < b.getLName();
		}
		return a.getGender() < b.getGender();
	};

	//adding poeple into our vector(plist)
    while (std::cin >> p)
        plist.insert(p);
	
	
	//cacluating bmi for each perosn in (plist)
	auto it = plist.begin();
	while(it != plist.end())
	{
		double bmi_value = BMI((*it).getWeight(), (*it).getHeight());
		//mapping a count to each BMI score
		if(bmi_value < 18.85)
		{
			BMICount["Underweight"] ++;
		}
		else if(bmi_value < 24.99)
		{
			BMICount["Normal weight"] ++;
		}
		else if(bmi_value < 29.99)
		{
			BMICount["Overweight"] ++;
		}
		else
		{
			BMICount["Obesity"] ++;
		}
		++it;
	}

	//printing out the BMI percentages
	std::cout << "BMI PERCENTAGE BY CATEGORY";
	auto st = BMICount.begin();
	while(st != BMICount.end())
	{
		string catagory = st ->first;
		int count = st -> second;
		int total_count = plist.getCount();//getCount is subsitued for size()
		double percentage = (double)count / total_count * 100.0;
		std::cout << st ->first << ": " << percentage << "%" << endl;
		++st;
	}
	
	//blank line for formatinng
	std::cout << "\n" << endl;

	//sorting the records by gender and lastname
	std::cout << "Sorting Records By Gender" << endl;
	//(plist.begin(), plist.end(), lastname_compare);
	auto ct = plist.begin();
	while(ct != plist.end())
	{
		std::cout << *ct << endl;
		++ct;
	}

	//person at target height
	for(it = plist.begin(); it != plist.end();++it)
		if((*it).getHeight() == targetHeight)
			break;
	if(it == plist.end())
		std::cout << "No such Person at target height." << std::endl;
	else
		std::cout << "Target height: " <<*it << std::endl;
	
	//person at target weight and gender
	for(it = plist.begin(); it != plist.end();++it)
		if((*it).getWeight() == targetWeight && (*it).getGender() == targetGender)
			break;
	if(it == plist.end())
		std::cout << "No such Person at target weight and gender." << std::endl;
	else
		std::cout << "Target weight and gender: " <<*it << std::endl;

	//person at or more than target BMI
	for(it = plist.begin(); it != plist.end();++it)
		if(BMI((*it).getWeight(),(*it).getHeight()) >= targetBMI)
			break;
	if(it == plist.end()){
		std::cout << "No such Person at target BMI or higher." << std::endl;
	}
	else
		std::cout << "Target BMI: " << *it << std::endl;

	


	/*
	 * Students to do:
	 * 1. Compute percentage of people within each BMI range.
	 * 2. Sort the records by gender then by last name.
	 * 3. Find the first person at or more than the target height
	 * 4. Find the person at or just more than the target weight and of the target gender
	 * 5. Find the first person at or more than the target BMI.
	 *
	 * For 1, use "std::map" to collect the count.
	 * For 2 to 5, make use of the C++ "iterator" feature.
	 *
	 * For the above, must use each of the below at least once.
	 * Function pointer, lambda function, and functor
	 */

	return EXIT_SUCCESS;
}