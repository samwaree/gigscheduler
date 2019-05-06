#ifndef INSTRUMENTS_H 
#define INSTRUMENTS_H 

enum Instrument {
    TRUMPET1, TRUMPET2, TRUMPET3, BONE1, BONE2, BONE3, TUBA, DRUMS, OTHER
};

static std::string strings[] = {
    "Trumpet 1", "Trumpet 2", "Trumpet 3", "Trombone 1", 
    "Trombone 2", "Trombone 3", "Tuba", "Drums", "Other"
};

static std::string textOfEnum(Instrument inst) {
    return strings[inst];
};

#endif
