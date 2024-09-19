#include <iostream>
#include "ECS/Entity/EntityManager/EntityManager.hh"

int main(void)
{
    EntityManager em;
    std::cout << "Hello !" << std::endl;

    std::size_t entity1 = em.CreateEntity();
    std::size_t entity2 = em.CreateEntity();
    std::cout << "Entity 1: " << entity1 << std::endl;
    std::cout << "Entity 2: " << entity2 << std::endl;

    Signature signature1;
    signature1.set(1);
    em.SetSignature(entity1, signature1);

    Signature signature2;
    signature2.set(4);
    em.SetSignature(entity2, signature2);

    std::cout << "Entity 1 Signature: " << em.GetSignature(entity1) << std::endl;
    std::cout << "Entity 2 Signature: " << em.GetSignature(entity2) << std::endl;

    return 0;
}
