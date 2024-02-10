#ifndef MILESTONE1_TEAM16_OBJECT_H
#define MILESTONE1_TEAM16_OBJECT_H
class Object
{
private :
    char type;
public:
    Object();
    Object(char type);
    virtual ~Object();

    char getType() const;

    void setType(char type);

    friend std::ostream &operator<<(std::ostream &os, const Object &object);
};
#endif //MILESTONE1_TEAM16_OBJECT_H
