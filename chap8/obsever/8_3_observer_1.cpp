//
// Created by Kylin on 2024/9/2.
//
#include <list>

class Subject;

// Observer Interface class
class Observer {
public:
  virtual ~Observer();
  virtual void Update(Subject *theChangeSubject) = 0;
protected:
  Observer();
};

// Subject class
class Subject {
public:
  virtual ~Subject();
  virtual void Attach(Observer*);
  virtual void Detach(Observer*);
  virtual void Notify();
protected:
  Subject();
private:
  List<Observer*> *_observers; // obeserver list
};

// attach obeserver
void Subject::Attach(Observer *o) {
  _observers->Append(o);
}

// detach obeserver
void Subject::Detach(Observer *o) {
    _observers->Detach(o);
}

// notify all observers
void Subject::Notify() {
    ListIterator<Observer*> i(_observers);

    for (i.First(); !i.IsDone(); i.Next()) {
        i.CurrentItem()->Update(this);
    }
}