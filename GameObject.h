#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H


/// @brief Interfaccia astratta utilizzata dalle varie implementazioni
class GameObject
{
    protected:
    int x, y, width, height;
    bool enabled = true;

    public:

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void SetPosition(int x, int y){ this->x = x; this->y = y; }
    virtual int GetX() { return x;}
    virtual int GetY() { return y;}
    virtual int GetW() { return width;}
    virtual int GetH() { return height;}
    virtual void SetEnabled(bool status){enabled = status;}
    virtual bool GetEnabled(){return enabled;}
};

class Collider
{
    public:

    static bool DetectCollision(GameObject* obj1, GameObject* obj2)
    {
        if(obj1 == nullptr || obj2 == nullptr)
        {
            return false;
        }

        //calcolo il centro del primo oggetto
        int x = obj1->GetX() + obj1->GetW()/2;
        int y = obj1->GetY() + obj1->GetW()/2;

        return CheckPointInArea(x,y, obj2);
    }

    //verifico se il punto è interno al rettangolo dell'oggetto
    static bool CheckPointInArea(int x, int y, GameObject* obj)
    {
        if( obj == nullptr) return false;

        if(x >= obj->GetX() && x <= obj->GetX() + obj->GetW())
            if(y >= obj->GetY() && y <= obj->GetY() + obj->GetH())
                return true;

        return false;

    }

};

#endif