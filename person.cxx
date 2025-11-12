/*
 * Sin-Yaw Wang <swang24@scu.edu>
 * Name: Isaac Amedie, Michael Tiburcio, Awni AlQuraini
 * Email: iamedie@scu.edu, mtiburcio@scu.edu, aalquraini@scu.edu
 */
#include <iostream>
#include <iomanip>
#include "person.h"
namespace csen79 {

Person::Person(const Person &p) {
    id = p.id;
    gender = p.gender;
    fname = p.fname;
    lname = p.lname;
    weight = p.weight;
    height = p.height;
}
const bool Person::operator<(const Person &rh) const {return this->id < rh.id;}
const bool Person::operator==(const Person &rh) const {return this->id == rh.id;}
const bool Person::operator>(const Person &rh) const {return this->id > rh.id;}

std::istream & operator>>(std::istream &is, Person &p) {
    char colon;
    char GenderChar;
    is >> p.id >> colon >> GenderChar >> p.fname >> p.lname >> p.weight >> p.height;
    p.gender = static_cast<Person::Gender>(GenderChar);
    return is;
}
std::ostream & operator<<(std::ostream &os, const Person &p) {
    os << std::fixed << std::setprecision(1);
    os << p.id << ": " << p.gender << " " << p.fname << " " << p.lname << " " << p.weight << " " << p.height;
    os << std::setprecision(0);
    return os;
}

}