/*
 * Sin-Yaw Wang <swang24@scu.edu>
 * Name: Isaac Amedie, Michael Tiburcio, Awni AlQuraini
 * Email: iamedie@scu.edu, mtiburcio@scu.edu, aalquraini@scu.edu
 */
#ifndef PERSON_H
#define PERSON_H
namespace csen79 {
class Person {
    public:
        using ID = unsigned int;
        enum Gender : char {Male = 'M', Female = 'F', Other = 'O'};
        Person(): id{0}, gender(Other) {}
        Person(const Person &);
        const ID getId() const { return id; }
        const Gender getGender() const { return gender; }
        const std::string getFName() const { return fname; }
        const std::string getLName() const { return lname; }
        const double getWeight() const { return weight; }
        const double getHeight() const { return height; }
        const bool operator<(const Person &rh) const;
        const bool operator==(const Person &rh) const;
        const bool operator>(const Person &rh) const;

    private:
        ID id;
        std::string fname;
        std::string lname;
        Gender gender;
        double weight;
        double height;
    friend std::ostream & operator<<(std::ostream &, const Person &);
    friend std::istream & operator>>(std::istream &, Person &);
};
}
#endif // PERSON_H