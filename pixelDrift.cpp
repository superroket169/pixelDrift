#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define PI 3.14159265358979323846f

float sigmoid(float x, float mid, float y1, float y2, float k)
{
    return y1 + (y2 - y1) / (1.0f + expf(-k * (x - mid)));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "PixelDrift");

    sf::Texture carTexture;
    if(!carTexture.loadFromFile("carTexture.png")) std::cout << "file cant opened\n";

    sf::RectangleShape car(sf::Vector2f(carTexture.getSize().x, carTexture.getSize().y));
    car.setTexture(&carTexture);
    car.setScale(2, 2);
    car.setOrigin(car.getSize().x/4, car.getSize().y/2);
    car.setPosition(450, 450);
    car.setRotation(0); // for look up

    sf::CircleShape speedometer(100);
    speedometer.setOrigin(speedometer.getRadius(), speedometer.getRadius());
    speedometer.setPosition(110, 170);
    speedometer.setFillColor(sf::Color::Black);
    
    sf::RectangleShape speedometerBox(sf::Vector2f(100, 30));
    speedometerBox.setOrigin(speedometerBox.getSize().x, speedometerBox.getSize().y);
    speedometerBox.setPosition(160, 220);
    speedometerBox.setFillColor(sf::Color::White);
    
    sf::CircleShape rpmmeter(100);
    rpmmeter.setOrigin(rpmmeter.getRadius(), rpmmeter.getRadius());
    rpmmeter.setPosition(330, 170);
    rpmmeter.setFillColor(sf::Color::Black);

    sf::RectangleShape rpmmeterBox(sf::Vector2f(100, 30));
    speedometerBox.setOrigin(rpmmeterBox.getSize().x, rpmmeterBox.getSize().y);
    rpmmeterBox.setPosition(280, 190);
    rpmmeterBox.setFillColor(sf::Color::White);

    sf::RectangleShape NeedleSpeed(sf::Vector2f(90, 5));
    NeedleSpeed.setFillColor(sf::Color::Red);
    NeedleSpeed.setOrigin(0, NeedleSpeed.getOrigin().y / 2);
    NeedleSpeed.setPosition(speedometer.getPosition());
    NeedleSpeed.setRotation(180);

    sf::RectangleShape NeedleRpm(sf::Vector2f(90, 5));
    NeedleRpm.setFillColor(sf::Color::Red);
    NeedleRpm.setOrigin(0, NeedleRpm.getOrigin().y / 2);
    NeedleRpm.setPosition(rpmmeter.getPosition());
    NeedleRpm.setRotation(180);


    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    std::string gearStr = "Gear = 1";
    sf::Text gearText(gearStr, font, 24);
    gearText.setPosition(20, 20);
    gearText.setFillColor(sf::Color::Black);

    std::string speedometerBoxTextStr = std::to_string(10);//"0 km/h";
    sf::Text speedometerBoxText(speedometerBoxTextStr, font, 18);
    speedometerBoxText.setPosition(80, 195);
    speedometerBoxText.setFillColor(sf::Color::Black);

    std::string rpmmeterBoxTextStr = std::to_string(10) +" rpm";
    sf::Text rpmmeterBoxText(rpmmeterBoxTextStr, font, 18);
    rpmmeterBoxText.setPosition(300, 195);
    rpmmeterBoxText.setFillColor(sf::Color::Black);

    std::string handBrakeTextStr = "Hande brake off";
    sf::Text handBrakeText(handBrakeTextStr, font, 24);
    handBrakeText.setPosition(220, 20);
    handBrakeText.setFillColor(sf::Color::Black);

    float velX = 0;
    float velY = 0;

    // gear = accel (piksel / s^2)
    int gear = 1;
    int optGear = 1;
    bool isGearAuto = 0;

    const float gearR = -500;
    const float gear1 = 300;
    const float gear2 = 700;
    const float gear3 = 1200;
    const float gear4 = 1800;
    const float gear5 = 2300;
    const float gear6 = 2650;
    const float gear7 = 2900;

    const float gearMaxes[8] = {125, 300, 700, 1200, 1800, 2300, 2650, 2900};
    const float gearRtrMaxVel = 125;
    const float gearOneMaxVel = 300;
    const float gearSecMaxVel = 700;
    const float gearThiMaxVel = 1200;
    const float gearFrtMaxVel = 1800;
    const float gearFthMaxVel = 2300;
    const float gearSixMaxVel = 2650;
    const float gearSvnMaxVel = 2900;

    const float gearRtrMaxVel_kmh = 14;
    const float gearOneMaxVel_kmh = 35;
    const float gearSecMaxVel_kmh = 85;
    const float gearThiMaxVel_kmh = 143;
    const float gearFrtMaxVel_kmh = 215;
    const float gearFthMaxVel_kmh = 275;
    const float gearSixMaxVel_kmh = 320;
    const float gearSvnMaxVel_kmh = 350;


    float dirX, dirY, dampingMultiplier, velAngleDeg, VelDegfCar, speed, dt, rpm, functAccel, gearMaxVel, accel;
    const float Sigm = 0.02;
    const float damping = 1;
    const float brakeForce = 2.2;
    const float handBrakeForce = 0.3;
    const float turnAccel = 1;
    const float DEG2RAD = PI / 180;
    const float RAD2DEG = 180 / PI;
    const float turnSpeed = 0.001;
    const float maxTurnSpeed = 150;
    const float maxRPM = 7000;
    int RpmTh = rpm / 1000;
    bool handbrake = 0;
    int speedkmh;

    bool inMenu = 1;

    sf::Clock clock;
    sf::Clock gearTimer;
    sf::Clock handbrakeTimer;
    sf::Clock SteerWTimer;

    while (window.isOpen())
    {
        if(inMenu)

        velAngleDeg = std::fmod(std::atan2(velY, velX) * RAD2DEG + 360, 360);
        VelDegfCar = velAngleDeg - car.getRotation();
        speed = std::sqrt(velX*velX + velY*velY);
        if(speed < 5) speed = 0;
        speedkmh = int(speed * 0.12);

        dt = clock.restart().asSeconds();
        if (dt <= 0) dt = 1/60;// pin fps to 60

        NeedleSpeed.setRotation((speed * 0.12)/2 + 180);
        speedometerBoxTextStr = std::to_string(speedkmh) + " km/h";
        speedometerBoxText.setString(speedometerBoxTextStr);

        rpm = (speed / gearMaxVel) * maxRPM;
        RpmTh = rpm / 1000;
        NeedleRpm.setRotation((rpm / 150 * 2) + 180);
        rpmmeterBoxTextStr = std::to_string((int)(RpmTh)) + " rpm";
        rpmmeterBoxText.setString(rpmmeterBoxTextStr);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && handbrakeTimer.getElapsedTime().asMilliseconds() > 300) // handbrake code
        {
            handbrake = handbrake ? 0 : 1;
            handbrakeTimer.restart();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
        
        {//gear code
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && gear < 7 && gearTimer.getElapsedTime().asMilliseconds() > 300)
            {
                ++gear;
                gearTimer.restart();
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && gear > 0 && gearTimer.getElapsedTime().asMilliseconds() > 300)
            {
                --gear;
                gearTimer.restart();
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && gear > 0 && gearTimer.getElapsedTime().asMilliseconds() > 300)
            {
                isGearAuto = isGearAuto ? 0 : 1;
                gearTimer.restart();
            }

            switch(gear)
            {
                case 0: accel = gearR; gearStr = "Gear = R"; gearMaxVel = gearRtrMaxVel; break;
                case 1: accel = gear1; gearStr = "Gear = 1"; gearMaxVel = gearOneMaxVel; break;
                case 2: accel = gear2; gearStr = "Gear = 2"; gearMaxVel = gearSecMaxVel; break;
                case 3: accel = gear3; gearStr = "Gear = 3"; gearMaxVel = gearThiMaxVel; break;
                case 4: accel = gear4; gearStr = "Gear = 4"; gearMaxVel = gearFrtMaxVel; break;
                case 5: accel = gear5; gearStr = "Gear = 5"; gearMaxVel = gearFthMaxVel; break;
                case 6: accel = gear6; gearStr = "Gear = 6"; gearMaxVel = gearSixMaxVel; break;
                case 7: accel = gear7; gearStr = "Gear = 7"; gearMaxVel = gearSvnMaxVel; break;
            }
            if(isGearAuto == 1) gearStr += " (Auto)";
            gearText.setString(gearStr);

            if(speed < gearOneMaxVel * 3/4) optGear = 1;
            else if(speed < gearSecMaxVel * 3/4) optGear = 2;
            else if(speed < gearThiMaxVel * 3/4) optGear = 3;
            else if(speed < gearFrtMaxVel * 3/4) optGear = 4;
            else if(speed < gearFthMaxVel * 3/4) optGear = 5;
            else if(speed < gearSixMaxVel * 3/4) optGear = 6;
            else if(speed < gearSvnMaxVel * 3/4) optGear = 7;

            if(isGearAuto) gear = optGear;
            if(gear != optGear) gearText.setFillColor(sf::Color::Red);
            else gearText.setFillColor(sf::Color::Black);

        }

        {//steering code:
            float angularVel = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                angularVel = -turnSpeed * pow(speed, 1.1) * SteerWTimer.getElapsedTime().asMilliseconds();
                
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                angularVel = turnSpeed * pow(speed, 1.1) * SteerWTimer.getElapsedTime().asMilliseconds();

            else SteerWTimer.restart();

            if(abs(angularVel) > maxTurnSpeed) angularVel = maxTurnSpeed * ((angularVel > 0) ? 1 : -1);

            car.rotate(angularVel * dt);

            float angRad = car.getRotation() * DEG2RAD;
            dirX = std::cos(angRad);
            dirY = std::sin(angRad);
        }

        {//accelerator code:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                if(gear == 0) functAccel = accel;
                else functAccel = sigmoid(speed, gearMaxes[gear] / 3 , gearOneMaxVel * gearOneMaxVel/gearMaxVel, accel, 0.012);
                velX += dirX * functAccel * dt;
                velY += dirY * functAccel * dt;
            }
        }

        {//damping and brakes code:

            if(handbrake)
            {
                handBrakeTextStr = "Handbrake on";
                handBrakeText.setString(handBrakeTextStr);
                handBrakeText.setFillColor(sf::Color::Red);
            }
            else
            {
                handBrakeTextStr = "Handbrake off";
                handBrakeText.setString(handBrakeTextStr);
                handBrakeText.setFillColor(sf::Color::Black);
            }

            velAngleDeg = std::fmod(std::atan2(velY, velX) * RAD2DEG + 360, 360);
            float carAngle = std::fmod(car.getRotation() + 360, 360);
            float rel = velAngleDeg - carAngle;
            
            if (rel > 180) rel -= 360;
            if (rel < -180) rel += 360;
            
            rel = std::abs(rel);
            
            if (rel > 90) rel = 90;

            const float MaxExtra = 4;
            if(handbrake) dampingMultiplier = 1 + handBrakeForce;
            else dampingMultiplier = 1 + MaxExtra * (rel / 90);//re/90 en fazla 1 // burası en fazla 1 + 4 den 5 oluyo

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                if (speed > 0.0f)
                {
                    velX -= velX * damping * dampingMultiplier * dt * brakeForce;
                    velY -= velY * damping * dampingMultiplier * dt * brakeForce;
                }
            }
            else
            {
                velX -= velX * damping * dampingMultiplier * dt;
                velY -= velY * damping * dampingMultiplier * dt;
            }
        }

        car.move(velX * dt, velY * dt);

        sf::Vector2f pos = car.getPosition();
        if(pos.x >= window.getSize().x) car.setPosition(1, pos.y);
        if(pos.y >= window.getSize().y) car.setPosition(pos.x, 1);
        if(pos.x <= 0) car.setPosition(window.getSize().x - 1, pos.y);
        if(pos.y <= 0) car.setPosition(pos.x, window.getSize().y - 1);

        window.clear(sf::Color(0, 100, 200));
        window.draw(car);
        window.draw(gearText);
        window.draw(speedometer);
        window.draw(NeedleSpeed);
        window.draw(speedometerBox);
        window.draw(speedometerBoxText);
        window.draw(rpmmeter);
        window.draw(rpmmeterBox);
        window.draw(NeedleRpm);
        window.draw(rpmmeterBoxText);
        window.draw(handBrakeText);
        
        window.display();

        //std::cout << "dt=" << dt << " speed=" << speed << " accel=" << accel << " dir=(" << dirX << "," << dirY << ")\n";
        //std::cout << SteerWTimer.getElapsedTime().asSeconds() << " " << angularVel << "\n";
        //std::cout << speed << "\n";
        //std::cout << speed << " " << rpm << "\n";
        //std::cout << functAccel << "\n";
        //std::cout << (handbrake) << " " << optGear << "\n";
    }
    return 0;
}
