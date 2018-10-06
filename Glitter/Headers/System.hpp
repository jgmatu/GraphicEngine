class System {

public:

    // All systems must update each game loop
    virtual void Update (float dt) = 0;

    // It's good practice to separate the construction and initialization code.
    virtual void Init (void) = 0;

    // This recieves any messages sent to the core engine in Engine.cpp
    virtual void SendMessage (Message *msg) = 0;

    // All systems need a virtual destructor to have their destructor called
    virtual ~System() {}
};
