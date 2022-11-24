#include "utils/myDataOps.hpp"

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>

using namespace mydataops;

std::vector<Person> getPeopleFromFile(const std::string& fileName) {
    std::ifstream in(fileName);
    // Try opening file
    if(in.is_open())
        std::cout << "Succesfully opened '" << fileName << "' file!\n";
    else {
        std::cerr << "Could not open '" << fileName << "' file!\n";
        std::abort();
    }

    // Read data from file and save to vector of people
    std::vector<Person> people;
    std::string line;
    // Read line by line until eof. Notice this changes the in variable,
    // as the read data is being erased from the ifstream buffer
    while(std::getline(in, line)) {
        std::vector<std::string> splitLine;
        std::string part;
        std::stringstream lineStream(line);
        // Split the line by the tab delimiter/character
        // Notice this changes the lineStream variable, as the read data is
        // being erased from the stringstream buffer
        while(std::getline(lineStream, part, ' ')) {
            splitLine.push_back(part);
        }
        std::vector<int> date;
        std::string number;
        std::stringstream dateString(splitLine[2]);
        while(std::getline(dateString, number, '.')) {
            date.push_back(std::atoi(number.c_str()));
        }
        people.push_back(Person{Name{splitLine[0], splitLine[1]}, Date{date[2], date[1], date[0]}});
    }
    return people;
}

auto sortAndWriteToFileFormat1(std::vector<Person> people, const std::string& outFile,
        const std::function<bool(const Person& a, const Person& b)>& compare) -> void {
    std::sort(people.begin(), people.end(), compare);

    std::ofstream out(outFile);
    for(const auto& person : people) {
        out << person.name << ": " << person.date << "\n";
    }
    out.close();
}

auto sortAndWriteToFileFormat2(std::vector<Person> people, const std::string& outFile,
        const std::function<bool(const Person& a, const Person& b)>& compare) -> void {
    std::sort(people.begin(), people.end(), compare);

    std::ofstream out(outFile);
    for(const auto& person : people) {
        out << formatNumber(person.date.day, 2) << "." << formatNumber(person.date.month, 2) << ". "
        << person.name.surname << " " << person.name.name << " (" << formatNumber(person.date.year, 4) << ")\n";
    }
    out.close();
}

auto getDuplicateNames(const std::vector<Person>& people) -> std::vector<std::string> {
    std::unordered_map<std::string, int> peopleMap;
    std::vector<std::string> duplicateNames;
    for(const auto& person : people) {
        peopleMap[person.name.name]++;
        if(peopleMap[person.name.name] == 2)        // Save duplicate only once, no need for more
            duplicateNames.push_back(person.name.name);
    }
    return duplicateNames;
}

auto getProbablity(int n) -> double {
    double np = 1.0;
    for(int i=0; i<n; i++) {
        np *= (365.0-(double)i)/365.0;
    }
    return (1-np)*100;
}

int main() {
    constexpr auto inOefbM = "/YourHomePath/Ue06/oefbteam_m";
    constexpr auto inOefbF = "/YourHomePath/Ue06/oefbteam_f";
    constexpr auto outOefbMTxt = "/YourHomePath/Ue06/namesoutput/oefbteam_m.txt";
    constexpr auto outOefbFTxt = "/YourHomePath/Ue06/namesoutput/oefbteam_f.txt";
    constexpr auto outOefbMDat = "/YourHomePath/Ue06/namesoutput/oefbteam_m.dat";
    constexpr auto outOefbFDat = "/YourHomePath/Ue06/namesoutput/oefbteam_f.dat";
    constexpr auto outParadoxon = "/YourHomePath/Ue06/plots/GebParadoxon.dat";
    constexpr auto outOefbMBirth = "/YourHomePath/Ue06/namesoutput/oefbteam_m_geb.dat";
    constexpr auto outOefbFBirth = "/YourHomePath/Ue06/namesoutput/oefbteam_f_geb.dat";

    std::cout << "Excercise 1: " << "\n";
    auto peopleM = getPeopleFromFile(inOefbM);
    auto duplicateM = getDuplicateNames(peopleM);
    std::cout << "There are " << duplicateM.size() << " duplicate names out of " << peopleM.size() << " names :";
    for(const auto& duplicate : duplicateM)
        std::cout << " " << duplicate;
    std::cout << "\n";
    sortAndWriteToFileFormat1(peopleM, outOefbMTxt, [](const Person& a, const Person& b){ return a.name < b.name; });
    sortAndWriteToFileFormat2(peopleM, outOefbMDat, [](const Person& a, const Person& b){ return a.date < b.date; });

    auto peopleF = getPeopleFromFile(inOefbF);
    auto duplicateF = getDuplicateNames(peopleF);
    std::cout << "There are " << duplicateF.size() << " duplicate names out of " << peopleF.size() << " names :";
    for(const auto& duplicate : duplicateF)
        std::cout << " " << duplicate;
    std::cout << "\n";
    sortAndWriteToFileFormat1(peopleF, outOefbFTxt, [](const Person& a, const Person& b){ return a.name < b.name; });
    sortAndWriteToFileFormat2(peopleF, outOefbFDat, [](const Person& a, const Person& b){ return a.date < b.date; });
    std::cout << "Done exercise 1!\n";

    std::cout << "Excercise 2: " << "\n";
    std::ofstream out(outParadoxon);
    int n1 = 1, n2 = 26;
    for(int i=n1; i<=n2; i++) {
        out << i << " " << getProbablity(i) << "\n";
    }
    out.close();
    std::cout << "Done exercise 2!\n";

    std::cout << "Exercise 3:\n";
    std::ofstream outMBirth(outOefbMBirth);
    for(const auto& p : peopleM) {
        outMBirth << p.name.surname << " " << p.name.name << ": " << p.date.getWeekday() << ", "
            << formatNumber(p.date.day, 2) << "." << formatNumber(p.date.month, 2) << "." << formatNumber(p.date.year, 4) << ", "
            << Date(2022, 11, 23) - p.date << " Tage\n";
    }
    outMBirth.close();

    std::ofstream outFBirth(outOefbFBirth);
    for(const auto& p : peopleF) {
        outFBirth << p.name.surname << " " << p.name.name << ": " << p.date.getWeekday() << ", "
            << formatNumber(p.date.day, 2) << "." << formatNumber(p.date.month, 2) << "." << formatNumber(p.date.year, 4) << ", "
            << Date(2022, 11, 23) - p.date << " Tage\n";
    }
    outFBirth.close();
    std::cout << "Done exercise 3!\n";

    return 0;
}