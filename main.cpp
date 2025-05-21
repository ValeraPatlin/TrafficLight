#include <iostream>
#include <memory>


class YellowLight;
class GreenLight;


// Интерфейс
class TrafficLightState
{
public:
    virtual ~TrafficLightState() = default;

    virtual std::shared_ptr<TrafficLightState> nextState() = 0;
    virtual void handle() = 0;
};


// Красный свет
class RedLight : public TrafficLightState
{
public:
    std::shared_ptr<TrafficLightState> nextState() override;

    void handle() override
    {
        std::cout << "Traffic light: Red!" << std::endl;
    }
};


// Желтый свет
class YellowLight : public TrafficLightState
{
public:
    std::shared_ptr<TrafficLightState> nextState() override;

    void handle() override
    {
        std::cout << "Traffic light: Yellow!" << std::endl;
    }
};


// Зеленый свет
class GreenLight : public TrafficLightState
{
public:
    std::shared_ptr<TrafficLightState> nextState() override;

    void handle() override
    {
        std::cout << "Traffic light: Green!" << std::endl;
    }
};


// -------------------
std::shared_ptr<TrafficLightState> RedLight::nextState()
{
    return std::make_shared<YellowLight>();
}

std::shared_ptr<TrafficLightState> YellowLight::nextState()
{
    return std::make_shared<GreenLight>();
}

std::shared_ptr<TrafficLightState> GreenLight::nextState()
{
    return std::make_shared<RedLight>();
}
// -----------------


// Сам светофор
class TrafficLight
{
private:
    std::shared_ptr<TrafficLightState> state;

public:
    TrafficLight() : state(std::make_shared<RedLight>())
    {}

    void change()
    {
        state = state->nextState(); // Переход к следующему цвету
    }

    void handle()
    {
        state->handle();
    }
};



int main()
{
    TrafficLight trafficLight;

    for (int i = 0; i < 6; ++i)
    {
        trafficLight.handle();
        trafficLight.change();
    }

    return 0;
}
