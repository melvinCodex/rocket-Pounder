#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <time.h>

class backGound
{
    sf::Vector2f pos;
    sf::Texture bGround;
    sf::Sprite bsprite;
    float red = rand()%250;
    float blue = rand()%250;
    float green = rand()%250;
    //srand(int i = 0);
    int dvcountered = 0;
    int dvcounterblue = 0;
    int dvcountergreen = 0;
    float dvred;
    float dvblue;
    float dvgreen;

    public:
    backGound(float pos_x,float pos_y){
        pos.x = pos_x;
        pos.y = pos_y;
    }
    void initBground(){
        bGround.loadFromFile("pics/background.jpg",sf::IntRect(100,100,10000,8000));
        bsprite.setTexture(bGround);
       // bsprite.setColor(sf::Color(red,blue,green,0));
        bsprite.setPosition(pos);
        float scalex =0.45;
        float scaley =0.55;
        bsprite.setScale(scalex,scaley);
    }
    void updateColor(){

        if(red <= 6 || red >= 250){
            dvcountered++;
        }
        if(dvcountered % 2 == 0){
            dvred = 5;
        }
        else{
            dvred = -5;
        }

        red += dvred;
        if(blue <= 12 || blue >= 250){
            dvcounterblue++;
        }
        if(dvcounterblue % 2 == 0){
            dvred = 5;
        }
        else{
            dvblue = -5;
        }
        blue += dvblue;

        if(green <= 10 || green >= 250){
            dvcountergreen++;
        }
        if(dvcountergreen % 2 == 0){
            dvgreen = 5;
        }
        else{
            dvgreen = -5;
        }
        green += dvgreen;

        bsprite.setColor(sf::Color(red,blue,green,165));
    }

    void render(sf::RenderWindow& wind){
        wind.draw(bsprite);
    }

};
class barriers
{
    float leftSide;
    float rightSide;
    float top;
    float bottom;
    float scalex = 0.25 * static_cast<float>(rand()%6);
    float scaley = 0.7;
    std::vector<sf::Sprite> bars;
    sf::Texture barText;
    sf::Sprite barSprite;
    int xpos[4];
    int ypos[4];
    int maxBars = 4;

    public:
    barriers(float pos_x1,float pos_y1,
             float pos_x2,float pos_y2,
             float pos_x3,float pos_y3,
             float pos_x4,float pos_y4){
                 xpos[1] = pos_x1;
                 ypos[1] = pos_y1;
                 xpos[2] = pos_x2;
                 ypos[2] = pos_y2;
                 xpos[3] = pos_x3;
                 ypos[3] = pos_y3;
                 xpos[4] = pos_x4;
                 ypos[4] = pos_y4;
    }
    void initBarrier(){
        barText.loadFromFile("pics/barrier.png",sf::IntRect(0,97,260,70));
        barSprite.setTexture(barText);
        barSprite.setColor(sf::Color(170,140,180,25));
    }
    void setBarrier(){
        for(int i = 0;i <4;i++){
         barSprite.setPosition(xpos[i],ypos[i]);
         barSprite.setScale(scalex,scaley);
         bars.push_back(barSprite);
        }
    }
    void markSides(){
            leftSide = barSprite.getPosition().x;
            rightSide = leftSide + barSprite.getGlobalBounds().width;
            top = barSprite.getPosition().y;
            bottom = top + barSprite.getGlobalBounds().height;
        }
    void render(sf::RenderWindow& wind){
        for( auto& barSprite : bars){
                wind.draw(barSprite);
            }
            }

    float get_leftside(){
        return leftSide;
    }
    float get_rightside(){
        return rightSide;
    }
    float get_top(){
        return top;
    }
    float get_bottom(){
        return bottom;
    }
};
class objectss
    {
        std::vector<sf::CircleShape> balls;
        sf::CircleShape ball;
        sf::Vector2f pos;
        sf::FloatRect ballBounds;
        float radius;
        float maxTimer = 5.f;
        float timer = 0.f;
        int maxBalls = 1000000;
        float red,blue,green ;
        int boolset = 0;
        float velx[1000],posx[1000],posy[1000];
        float dvx[1000];
        float dvy[1000];
        float gForce[1000];
        float scLeftSide,scRightSide,scTop,scBottom;
        float bLeftSide[1000],bRightSide[1000],bTop[1000],bBottom[1000];

        public:

        objectss(float radius,float pos_y){
            this->radius = radius;
            //pos.y = pos_y;
        }
        void initBall(){
           // ball.setPosition(pos);
            ball.setRadius(radius);
            ball.setPointCount(70);
            ball.setOutlineColor(sf::Color::Black);
            ball.setOutlineThickness(5.f);
            ballBounds = ball.getGlobalBounds();

        }
        void initBounceVar(sf::RenderWindow& wind){
            scLeftSide = 0;
            scRightSide = wind.getSize().x;
            scTop = 0;
            scBottom = wind.getSize().y;
        }
        void Spawnobj(){

            gForce[boolset] = 3;
            dvy[boolset] = 20;
            pos.x = static_cast<float>((rand( )*777)%770);
            pos.y = 0.f;
            posx[boolset] = pos.x;
            posy[boolset] = pos.y;
            red = rand()%255;
            blue = rand()%255;
            green = rand()%255;
            ball.setFillColor(sf::Color(red,blue,green,185));
            ball.setPosition(pos);
            balls.push_back(ball);
            boolset++;
        }
        void updateTimer(){
            if(balls.size()<maxBalls){
                if(timer >= maxTimer){
                    Spawnobj();
                    timer = 0.f;

                }

                else{
                    timer += 1.f;
                }
            }
        }
        void bounce(barriers& barSprite){
            int k = 0;
            //std::cout<<barSprite.get_rightside()<<std::endl;
            //std::cout<<barSprite.get_leftside()<<std::endl;
            //std::cout<<barSprite.get_top()<<std::endl;
            //std::cout<<barSprite.get_bottom()<<std::endl;
            //std::cout<<ball.getPosition().x<<std::endl;
           // std::cout<<bLeftSide + ball.getGlobalBounds().width<<std::endl;
            //std::cout<<ball.getPosition().y<<std::endl;
            //std::cout<<bTop + ball.getGlobalBounds().height<<std::endl;

            for(auto&e :balls){
            bLeftSide[k] = posx[k];
            bRightSide[k] = posx[k] + ball.getGlobalBounds().width;
            bTop[k] = posy[k];
            bBottom[k] = posy[k] + ball.getGlobalBounds().height;
            if(bRightSide[k] >= scLeftSide || bRightSide[k] >= barSprite.get_leftside()||
               bLeftSide[k] <= scRightSide || bLeftSide[k] <= barSprite.get_rightside()
                ){
                dvx[k] = -dvx[k] ;
            }
            //std::cout<<barSprite.get_bottom() << "  "<<barSprite.get_leftside()<<std::endl;
            if(bRightSide[k] > barSprite.get_leftside() && bLeftSide[k] < barSprite.get_rightside() &&
               bBottom[k] > barSprite.get_top() ){
                dvy[k] = -dvy[k] * 0.8;
            }
            if(bRightSide[k] > barSprite.get_leftside() && bLeftSide[k] < barSprite.get_rightside() &&
               bBottom[k] > barSprite.get_top() ){
                dvy[k] = -dvy[k] * 0.8;
            }
            //if(bRightSide[k] > barSprite.get_leftside() && bLeftSide[k] < barSprite.get_rightside() &&
              // bBottom[k] > barSprite.get_top() ){
                //dvy[k] = -dvy[k] * 0.8;
            //}
            if(bRightSide[k] > barSprite.get_leftside() && bLeftSide[k] < barSprite.get_rightside() &&
               bBottom[k] > barSprite.get_top() ){
                dvy[k] = -dvy[k] * 0.8;
            }
            k++;

            }
             std::cout<<"  "<<std::endl;
        }
        void movement(sf::RenderWindow& wind){
            int j = 0;

        for( auto&e : balls){
            if(j % 3 == 0){
                dvx[j] = -1;
            } else if(j % 3 == 1){
                dvx[j] = 1;
            } else {
                dvx[j] = 0;
            }
            dvy[j] += 1;
            velx[j] = dvx[j] * static_cast<float> (rand()%30);
            posx[j] += velx[j];
            posy[j] += dvy[j];
           e.move(velx[j],dvy[j]);
           j++;
          //std::cout<<dvy[4]<<std::endl;
            }
            }
        void render(sf::RenderWindow& wind){
        for( auto& ball : balls){
                wind.draw(ball);
                //std::cout<<dvy<<"\n";
            }
            }
    };
class rpgLauncher
{
    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f headPos;
    float charge;
    float rotation;
    float distx;
    float disty;
    float mposx;
    float mposy;
    float dist;
    float nomx;
    float nomy;

    public:
    rpgLauncher(float pos_x,float pos_y,float charge){
        pos.x = pos_x;
        pos.y = pos_y;
        charge = this->charge;
    }

    void initLauncher(){
        texture.loadFromFile("pics/launcher.png",sf::IntRect(0,0,123,403));
        sprite.setTexture(texture);
        float scalex = 0.4;
        float scaley = 0.3;
        sprite.setScale(scaley,scalex);
        sprite.setPosition(pos);
        sprite.setOrigin(51.5,201.5);
        sprite.setColor(sf::Color(255,255,255,255));
    }
    void updateRot(sf::RenderWindow &wind){
        mposx = static_cast<float>(sf::Mouse::getPosition(wind).x);
        mposy = static_cast<float>(sf::Mouse::getPosition(wind).y);
        distx = (mposx) -  sprite.getPosition().x;
        disty = sprite.getPosition().y -(mposy);
        dist = std::sqrt((distx*distx)+(disty*disty));
        nomx = distx/dist;
        nomy = disty/dist;
        headPos.x = sprite.getPosition().x + nomx * (sprite.getGlobalBounds().height/2);
        headPos.y = sprite.getPosition().y + nomy*(sprite.getGlobalBounds().height/2);
        rotation = std::atan(distx/disty)*(180/3.14159);
        sprite.setRotation(rotation);

    }
    float getRotation(){
        return rotation;
    }
    float getnomx(){
        return nomx;
    }
     float getnomy(){
        return nomy;
    }
    sf::Vector2f get_pos(){
        return pos;
    }
    sf::Vector2f get_headPos(){
        return headPos;
    }
    void render(sf::RenderWindow& wind){
        wind.draw(sprite);
    }

};
class rpGrenade
    {
    sf::Texture grenade;
    sf::Sprite gSprite;
    std::vector <sf::Sprite> grenades;
    float gForce;
    float scalex;
    float scaley;
    float cv,cb,xv,yv,rot;
    float maxTimer = 25;//static_cast<float>(rand()%25);
    float timer = 0.f;
    int maxGrenades = 1000;
    int greCounter = 0;
    bool apexR;
    float posx[1000];
    float posy[1000];
    float velx[1000];
    float vely[1000];
    float accy[1000];
    float nomx[1000];
    float nomy[1000];
    float roT[1000];
    public:
        rpGrenade(float gForce){
             this->gForce =gForce;
        }
         void initGrenade(){
            grenade.loadFromFile("pics/grenade.png" , sf::IntRect(50,9,65,305));
            gSprite.setTexture(grenade);
            gSprite.setColor(sf::Color(255,255,255,255));
            float scalex = 0.1;
            float scaley = 0.1;
            gSprite.setScale(scalex,scaley);
            gSprite.setOrigin(32.5,157.5);
        }

        void initSpawn(rpgLauncher& sprite){
            cv = sprite.getnomx();
            cb = sprite.getnomy();
            xv = sprite.get_headPos().x;
            yv = sprite.get_headPos().y;
            rot = (sprite.getRotation());
            //std::cout<<xv<<" \n "<<yv<<std::endl;
        }
         void spawnGrenade(){
            nomx[greCounter] = cv;
            nomy[greCounter] = cb;
            posx[greCounter] = 400;
            posy[greCounter] = 500;
            velx[greCounter] = nomx[greCounter] * 100;
            vely[greCounter] = nomy[greCounter] * 100;
            accy[greCounter] =  gForce;
            roT[greCounter] = rot;
            gSprite.setPosition(posx[greCounter],posy[greCounter]);
            gSprite.setRotation(roT[greCounter]);
            //std::cout<<roT[greCounter]<<"  "<<roT[greCounter]<<std::endl;
            grenades.push_back(gSprite);
            greCounter++;

        }
        void updateTimer(){
            if(grenades.size()<maxGrenades){
                if(timer = maxTimer){
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
                            spawnGrenade();
                            timer = 0.f;
                        }
                        else{
                            timer += 1.f;
                }
                }//std::cout<<timer<<"\n";
            }
        }
        void movement(){
            int i = 0;
            //float j;
            for(auto&e : grenades){
                vely[i] -= accy[i];
                //std::cout/*<<vely[i]*/<<"\n"<<gForce;
                e.move(velx[i],- vely[i]);
                i++;
                /*if(vely[i] > 0){
                    apexR = true;
                }
                if(roT[i] > 0 || apexR == true){
                    roT[i] = roT[i] + 9;
                    e.rotate(roT[i]);
                }*/
            }

        }

        void render(sf::RenderWindow& wind){
            for(auto& gSprite : grenades){
                    wind.draw(gSprite);
                    }
                    }
};
int main()
{
    objectss stuff(15,0);
    backGound bac(0,0);
    barriers bar(180,220,480,80,500,350,400,500);
    //objects obj(20);
    rpgLauncher rpl(400,500,1000);
    rpGrenade gre(9);
    sf::RenderWindow window(sf::VideoMode(800,600),"bing",sf::Style::Titlebar | sf::Style::Close );
    window.setFramerateLimit(127);
    sf::Event event;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::Escape)
                    window.close();
            }
        }
        bac.initBground();
        bac.updateColor();
        bar.initBarrier();
        bar.setBarrier();
        bar.markSides();
        /*obj.initBall();
        obj.initBounceVar(window);
        obj.Spawnobj();
        obj.updateTimer();
        obj.bounce(bar);
        obj.movement(window);*/
        rpl.initLauncher();
        rpl.updateRot(window);
        gre.initGrenade();
        gre.initSpawn(rpl);
        //gre.spawnGrenade();
        gre.updateTimer();
        gre.movement();

        //stuff.initTexture();
        stuff.initBall();
        stuff.initBounceVar(window);
        stuff.updateTimer();
        stuff.bounce(bar);
        stuff.movement(window);
        //stuff.getBallbounds();
        //stuff.setFillcolour();
        window.clear(sf::Color(255,255,255,255));
        gre.render(window);
        rpl.render(window);
        stuff.render(window);
        bac.render(window);
        //obj.render(window);
        bar.render(window);

        window.display();
    }
}
