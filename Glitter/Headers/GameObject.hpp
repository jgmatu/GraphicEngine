class GameObject {

public:

    Component *GetComponent( id );
    void AddComponent( Component *comp );
    bool HasComponent( id );

private:

    std::vector<Component *> m_components;

};
