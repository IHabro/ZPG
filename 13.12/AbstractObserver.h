#pragma once

#include <iostream>
#include <vector>

class Subject;

//Entity which observe a Subject
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void Update(Subject*) = 0;
};

//Subject beeing observed
class Subject
{
private:
    std::vector<Observer*> observers;

public:
    virtual ~Subject() = default;
    void Attach(Observer& o)
    {
        observers.push_back(&o);
    }

    void Detach(Observer& o)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), &o));
    }

    void Notify()
    {
        for (auto* o : observers)
        {
            //Polymorphism not implemented - this is basically useless
            //o->Update(this);
        }
    }
};

