#include"square.hpp"
#include"cstdlib"

Square::Square(const float& x, const float& y, const float& length){
    m_Position=glm::vec3(x,y,0.0f);
    m_Length=length;
    m_Direction=DIR_RIGHT;

    m_Color.r=(10+std::rand()%15)/25.0;
    m_Color.g=(10+std::rand()%15)/25.0;
    m_Color.b=(10+std::rand()%15)/25.0;
}
glm::vec4 Square::getColor(){ return m_Color; }
glm::vec3 Square::getPosition(){ return m_Position; }
void Square::move(){
    switch (m_Direction)
    {
    case DIR_RIGHT:
        m_Position+=glm::vec3(m_Length,0.0f,0.0f);
        break;
    case DIR_LEFT:
        m_Position-=glm::vec3(m_Length,0.0f,0.0f);
        break;
    case DIR_UP:
        m_Position+=glm::vec3(0.0f,m_Length,0.0f);
        break;
    case DIR_DOWN:
        m_Position-=glm::vec3(0.0f,m_Length,0.0f);
        break;
    
    default:
        break;
    }
}
void Square::setDirection(Square::DIRECTION newDirection){
    m_Direction=newDirection;
}