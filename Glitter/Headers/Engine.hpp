class Engine {

public:

    void Update( float dt );
    void MainLoop( void );
    void Add( System *sys );

private:

    std::vector<System> m_systems;

};
