oid move(sf::Vector2f &playerVelocity, float dt)
{
    // ...
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (onGround || inAir < maxInAir))
    {
        playerVelocity.y = -gravity;
        inAir += dt;
    }
    else
    {
        playerVelocity.y = gravity;
        inAir = maxInAir;
    }
}

We modified the arguments of the function move() by adding the float ‘dt’ in order to increase the variable inAir, which is the actual time the player is in the air.
We enable the player to jump only by pressing the ’UP’ key if the player is on ground or already in the air and the maximum time has not yet been reached.
If the above conditions have been met we set the velocity of vertical axis, y member, to -gravity and increase the inAir with the time of the frame, dt.
Otherwise we set the y value of velocity to gravity, so the player will fall down until it hits a block of grass, then we set inAir to maxInAir so the player can’t jump from air.

Last thing to do is to reset the inAir when the player is hitting the ground.
Here is the complete code:
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
	
#include <SFML/Graphics.hpp>
 
#include <vector>
 
const int gravity = 500;
bool onGround = false;
float inAir;
float maxInAir = 0.3f;
 
void move(sf::Vector2f &playerVelocity, float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerVelocity.x = -gravity;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playerVelocity.x = gravity;
    }
    else if (playerVelocity.x != 0)
    {
        playerVelocity.x = 0;
    }
 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (onGround || inAir < maxInAir))
    {
        playerVelocity.y = -gravity;
        inAir += dt;
    }
    else
    {
        playerVelocity.y = gravity;
        inAir = maxInAir;
    }
}
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "How to apply collision?");
 
    // Loading player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("player.png")) return 0;
 
    // Creating player sprite
    sf::Sprite player;
    player.setTexture(playerTexture);
 
    // Loading grass texture
    sf::Texture grassTexture;
    if (!grassTexture.loadFromFile("grass.png")) return 0;
 
    // Creating a vector because we have more blocks and we will need them into a container
    std::vector<sf::Sprite> grass;
 
    // Add 4 grass blocks to the container
    grass.resize(4);
    for (std::size_t i=0; i<3; ++i)
    {
        grass[i].setTexture(grassTexture);
        grass[i].setPosition(128 * i, 384);
    }
 
    // Last grass block will bo above the first one
    grass[3].setTexture(grassTexture);
    grass[3].setPosition(0,256);
 
    // Create a sf::Vector2f for player velocity and add to the y variable value gravity
    sf::Vector2f playerVelocity(0, gravity);
 
    sf::Clock clock;
    while (window.isOpen())
    {
        // Get the frame elapsed time and restart the clock
        float dt = clock.restart().asSeconds();
 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
 
        // Apply physics to player
        player.setPosition(player.getPosition().x + playerVelocity.x * dt, player.getPosition().y + playerVelocity.y * dt);
        onGround = false;
        for (std::size_t i=0; i<grass.size(); ++i)
        {
            // Affected area
            sf::FloatRect area;
            if (player.getGlobalBounds().intersects(grass[i].getGlobalBounds(), area))
            {
                // Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
                if (area.width > area.height)
                {
                    if (area.contains({ area.left, player.getPosition().y }))
                    {
                        // Up side crash
                        player.setPosition({ player.getPosition().x, player.getPosition().y + area.height });
                    }
                    else
                    {
                        // Down side crash
                        onGround = true;
                        inAir = 0.f;
                        player.setPosition({ player.getPosition().x, player.getPosition().y - area.height });
                    }
                }
                else if (area.width < area.height)
                {
                    if (area.contains({ player.getPosition().x + player.getGlobalBounds().width - 1.f, area.top + 1.f }))
                    {
                        //Right side crash
                        player.setPosition({ player.getPosition().x - area.width, player.getPosition().y });
                    }
                    else
                    {
                        //Left side crash
                        player.setPosition({ player.getPosition().x + area.width, player.getPosition().y });
                    }
                }
            }
        }
 
        move(playerVelocity, dt);
 
        window.clear();
         
        // Draw the grass
        for (std::size_t i=0; i<grass.size(); ++i)
        {
            window.draw(grass[i]);
        }
 
        // Draw the player
        window.draw(player);
 
        window.display();
    }   
 
    return 0;
}