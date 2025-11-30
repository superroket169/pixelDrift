#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>


#define PI 3.14159265358979323846f

float sigmoid(float x, float mid, float y1, float y2, float k)
{
    return y1 + (y2 - y1) / (1.0f + expf(-k * (x - mid)));
}

bool button(int x, int y, int w, int h, std::string str, sf::RenderWindow &window ,sf::Color color)
{
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf");

    sf::Text boxText(str, font, 24);
    boxText.setFillColor(sf::Color::Black);
    boxText.setPosition(x + 50, y + (h/2) - 15);

    sf::RectangleShape b;
    b.setSize({(float)w, (float)h});
    b.setPosition((float)x, (float)y);
    b.setFillColor(color);
    window.draw(b);
    window.draw(boxText);

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        if (b.getGlobalBounds().contains(worldPos))
            return 1;
        
    
    return 0;
}


//eklenecekler:
//  duman çıkması izi *
//  araba lastik izi *
//  parkurdan çıkamama *
//  Menü: ADDED
//      menü * ADDED
//      parkur değişimi *
//      araba değişimi *
//            

int main()
{
    const int windowX = 1200;
    const int windowY = 800;
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "PixelDrift");

    sf::Texture carTexture;
    if(!carTexture.loadFromFile("carTexture.png")) std::cout << "file cant opened\n";

    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("backGround2.png")) std::cout << "background file cant opened\n";
    sf::Sprite backGround(bgTexture);
    backGround.scale(7, 7);

    sf::RectangleShape car(sf::Vector2f(carTexture.getSize().x, carTexture.getSize().y));
    car.setTexture(&carTexture);
    car.setScale(2, 2);
    car.setOrigin(car.getSize().x/4, car.getSize().y/2);
    car.setPosition(windowX/2, windowY/2);
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

    sf::RectangleShape driftMark1(sf::Vector2f(15 ,10));
    driftMark1.setFillColor(sf::Color::Black);
    driftMark1.setPosition(car.getPosition().x, car.getPosition().y);
    driftMark1.setOrigin(driftMark1.getSize().x/2, driftMark1.getSize().y/2);

    sf::RectangleShape driftMark2(sf::Vector2f(15 ,10));
    driftMark2.setFillColor(sf::Color::Black);
    driftMark2.setPosition(car.getPosition().x, car.getPosition().y);
    driftMark2.setOrigin(driftMark2.getSize().x/2, driftMark2.getSize().y/2);

    sf::RectangleShape driftMark3(sf::Vector2f(15 ,10));
    driftMark3.setFillColor(sf::Color::Black);
    driftMark3.setPosition(car.getPosition().x, car.getPosition().y);
    driftMark3.setOrigin(driftMark3.getSize().x/2, driftMark3.getSize().y/2);

    sf::RectangleShape driftMark4(sf::Vector2f(15 ,10));
    driftMark4.setFillColor(sf::Color::Black);
    driftMark4.setPosition(car.getPosition().x, car.getPosition().y);
    driftMark4.setOrigin(driftMark4.getSize().x/2, driftMark4.getSize().y/2);

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf");

    std::string gearStr = "Gear = 1";
    sf::Text gearText(gearStr, font, 24);
    gearText.setPosition(20, 20);
    gearText.setFillColor(sf::Color::Black);

    std::string speedometerBoxTextStr = std::to_string(10);//"0 km/h";
    sf::Text speedometerBoxText(speedometerBoxTextStr, font, 18);
    speedometerBoxText.setPosition(65, 195);
    speedometerBoxText.setFillColor(sf::Color::Black);

    std::string rpmmeterBoxTextStr = std::to_string(10) +" rpm";
    sf::Text rpmmeterBoxText(rpmmeterBoxTextStr, font, 18);
    rpmmeterBoxText.setPosition(300, 195);
    rpmmeterBoxText.setFillColor(sf::Color::Black);

    std::string handBrakeTextStr = "Hande brake off";
    sf::Text handBrakeText(handBrakeTextStr, font, 24);
    handBrakeText.setPosition(250, 20);
    handBrakeText.setFillColor(sf::Color::Black);

    float velX = 0;
    float velY = 0;

    // gear = accel (piksel / s^2)
    int gear = 1;
    int optGear = 1;
    bool isGearAuto = 0;
    bool isDrifting = 1;

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

    std::vector<sf::RectangleShape> skidMarks;

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

    sf::Clock click;

    while (window.isOpen())
    {
        if(inMenu)//menu:
        {
            window.clear(sf::Color(0, 200, 200));

            sf::Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed) window.close();
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
            }

            if(button(500, 200, 200, 100, "Play", window, sf::Color::Blue) * clock.getElapsedTime().asMilliseconds() > 100)
            {
                inMenu = 0;
                clock.restart();
            }
            if(button(500, 350, 200, 100, "Exit", window, sf::Color::Blue) * clock.getElapsedTime().asMilliseconds() > 100)
            {
                window.close();
                clock.restart();
            }
            
            window.display();
            continue;
        }

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

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) inMenu = 1;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && handbrakeTimer.getElapsedTime().asMilliseconds() > 300) // handbrake code
        {
            handbrake = handbrake ? 0 : 1;
            handbrakeTimer.restart();
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
            if(isGearAuto) gearText.setFillColor(sf::Color::Yellow);
            else if(gear != optGear) gearText.setFillColor(sf::Color::Red);
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

            velAngleDeg = std::fmod(std::atan2(velY, velX) * RAD2DEG + 360, 360);// bu lanet satırı çetgpt yaptı
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

        backGround.move(-velX * dt, -velY * dt);

        for (auto &s : skidMarks)
            s.move(-velX * dt, -velY * dt);


        //sf::Vector2f pos = car.getPosition();
        //if(pos.x >= window.getSize().x) car.setPosition(1, pos.y);
        //if(pos.y >= window.getSize().y) car.setPosition(pos.x, 1);
        //if(pos.x <= 0) car.setPosition(window.getSize().x - 1, pos.y);
        //if(pos.y <= 0) car.setPosition(pos.x, window.getSize().y - 1);

        window.clear(sf::Color(0, 100, 200));
        window.draw(backGround);
        
        for (auto &i : skidMarks) window.draw(i);
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

        {//Marking driftMark1
            driftMark1.setRotation(car.getRotation());
            driftMark1.setPosition(90*cos(DEG2RAD*(car.getRotation() + 15)) + car.getPosition().x, 90*sin(DEG2RAD*(car.getRotation() + 15)) + car.getPosition().y);
            
            driftMark2.setRotation(car.getRotation());
            driftMark2.setPosition(90*cos(DEG2RAD*(car.getRotation() - 15)) + car.getPosition().x, 90*sin(DEG2RAD*(car.getRotation() - 15)) + car.getPosition().y);
            
            driftMark3.setRotation(car.getRotation());
            driftMark3.setPosition(25*cos(DEG2RAD*(car.getRotation() + 70 + 180)) + car.getPosition().x, 25*sin(DEG2RAD*(car.getRotation() + 70 + 180)) + car.getPosition().y);
            
            driftMark4.setRotation(car.getRotation());
            driftMark4.setPosition(25*cos(DEG2RAD*(car.getRotation() - 70 + 180)) + car.getPosition().x, 25*sin(DEG2RAD*(car.getRotation() - 70 + 180)) + car.getPosition().y);
            
            
            //window.draw(driftMark1);
            //window.draw(driftMark2);
            //window.draw(driftMark3);
            //window.draw(driftMark4);

            if(isDrifting)
            {
                //auto *mark1 = new sf::RectangleShape;
                //auto *mark2 = new sf::RectangleShape;
                //auto *mark3 = new sf::RectangleShape;
                //auto *mark4 = new sf::RectangleShape;
                
                //*mark1 = driftMark1;
                //*mark2 = driftMark2;
                //*mark3 = driftMark3;
                //*mark4 = driftMark4;

                //skidMarks.push_back(*mark1);
                //skidMarks.push_back(*mark2);
                //skidMarks.push_back(*mark3);
                //skidMarks.push_back(*mark4);
                if(handbrake)
                {
                    //skidMarks.push_back(driftMark1);
                    //skidMarks.push_back(driftMark2);
                    skidMarks.push_back(driftMark3);
                    skidMarks.push_back(driftMark4);
                }

            }

        }
        
        window.display();
    }
    return 0;
}