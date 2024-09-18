template <typename T>

class EntityManager {

    public:
        EntityManager();
        ~EntityManager() = default;
        void addEntity(T entity);
        void removeEntity(T entity);
        T getEntity(int id);

    protected:

    private:


};
