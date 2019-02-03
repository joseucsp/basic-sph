#include "sphere.hpp"
#include <glm/glm.hpp>
#include "container.hpp"


void ContainerCollisions(Particle ParticleSystem[],Container FluidContainer[], int num_particles, float RadiusMask)
{
    float K = 20.0;
    for (int ip = 0; ip < num_particles; ip++)
    {
        ParticleSystem[ip].force = glm::vec3(0.0, -9.80665, 0.0) * 0.01f;
        for (int ic = 0; ic < 5; ic ++)
        {
            glm::vec3 delta  = ParticleSystem[ip].position - FluidContainer[ic].center;
            float normalDist = glm::dot(delta, FluidContainer[ic].normal);
                       
            if (normalDist < RadiusMask)
            {
                ParticleSystem[ip].force += (RadiusMask - normalDist) * FluidContainer[ic].normal * K;
                //ParticleSystem[ip].velocity += abs(2.0f * glm::dot(ParticleSystem[ip].velocity, FluidContainer[ic].normal))*FluidContainer[ic].normal;
            }
        } 
    }    
}
void SimulatePhysics(Particle ParticleSystem[], Container FluidContainer[], float&tSim, float& v0, int num_particles, float timeStep)
{   
    glm::vec3 aceleration;
    
     
    float     MASS    = 0.01;
    float RadiusMask  = 0.1 + 0.02;

    // Air Simulation
    glm::vec3 AirDeceleration;
    ContainerCollisions(ParticleSystem, FluidContainer, num_particles, RadiusMask);

    for (int ip = 0; ip < num_particles; ip++)
    {
        AirDeceleration = glm::normalize(ParticleSystem[ip].velocity) * 4.0f;
        aceleration  = ParticleSystem[ip].force * (1 /  MASS) - AirDeceleration;
        ParticleSystem[ip].position += ParticleSystem[ip].velocity * timeStep + aceleration * timeStep * timeStep * 0.5f;
        ParticleSystem[ip].velocity += timeStep * aceleration;
    }

    tSim += timeStep;
}
