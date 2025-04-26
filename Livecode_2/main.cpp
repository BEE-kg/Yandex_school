#include <iostream>
#include <ctime>
#include <cstdint>
#include <map>
#include <set>



enum EEventPriority : uint8_t {
    MINOR = 0,
    MIDLE,
    MAJOR
};



struct EventKey {

    EEventPriority priority;
    std::time_t    timestamp;

    bool operator<(const EventKey& other) const {

        if (priority != other.priority)
            return priority < other.priority;

        return timestamp < other.timestamp;
    }
};



// TODO: implement
class EventStorage {

private:

    std::map<EventKey, std::string> events;
    std::set<EventKey> keys;

public:

    void AddEvent(const EventKey& key, const std::string& value) {

        if (events.count(key) == 0)
            keys.insert(key);

        events[key] = value;
    }

    const std::string* FindEvent(const EventKey& key) const {
        
        auto it = events.find(key);

        if (it == events.end())
            return nullptr;

        return &it -> second;
    }

    std::string LowestEvent() const {

        if (keys.empty())
            throw std::out_of_range("No events");

        return events.at(*keys.begin());
    }

    std::string HighestEvent() const {

        if (keys.empty())
            throw std::out_of_range("No events");

        return events.at(*keys.rbegin());
    }

    void RemoveEvent(const EventKey& key) {

        if (events.erase(key))
            keys.erase(key);
    }
};

int main(int, char**){
    EventStorage storage;

    // O(log(n))
    storage.AddEvent(
        {MAJOR, std::time(NULL) - 1}, "First Major Event"
    );

    storage.AddEvent(
        {MAJOR, std::time(NULL)}, "Second Major Event"
    );

    storage.AddEvent(
        {MINOR, std::time(NULL)}, "Minor Event");


    auto event = storage.FindEvent(EventKey{MAJOR, std::time(NULL) - 1});
    if(event)
        std::cout << std::endl << *event; //  "First Major Event"

    // O(1)
    // Prints "Minor Event"
    std::cout << std::endl << storage.LowestEvent();

    // O(1)
    // Prints "Second Major Event"
    std::cout << std::endl << storage.HighestEvent();

    // O(1)
    storage.RemoveEvent(EventKey{MAJOR, std::time(NULL)});

    // O(1)
    storage.RemoveEvent(EventKey{MINOR, std::time(NULL)});

    // Both
    // O(1)
    // Prints "First Major Event"
    std::cout << std::endl << storage.LowestEvent();
    std::cout << std::endl << storage.HighestEvent();

    return 0;
}
