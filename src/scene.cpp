#include <scene.hpp>
#include <math.h>
#include <fstream>


namespace my{
    Scene::Scene(int width, int height){
        m_width = width;
        m_height = height;
        m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_width, m_height), "3D Engine");
        m_texture = std::make_unique<sf::Texture>();
        m_texture->create(m_width, m_height);
        m_sprite = std::make_unique<sf::Sprite>(*m_texture);

        Intrinsic intrinsic = { 960.0, 540.0, 960.0, 540.0 };
        Point position = { 467340.0, -60.0, 6063520.0};
        Angles angles = { 0.0,1.8,0.0 };
        m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);

        m_points = new Point[400000];
    }
    Scene::~Scene(){
        if (m_points != nullptr)
            delete[] m_points;
    }


    void Scene::LifeCycle(){
        std::cout << std::setprecision(3) << std::fixed;
        double y0 = 1;

        std::ifstream inPoints("../points.txt");
        if(!inPoints.is_open()) {
            std::cerr << "File points.txt not found";
            return;
        }

        Point* points = new Point[400000];
        Pixel* pixels = new Pixel[400000];
        int n = 0;
        int r,g,b;
        while(!inPoints.eof()){
            inPoints >> points[n].x >> points[n].y >> points[n].z >> r >> g >> b;
            pixels[n].r = static_cast<uint8_t>(r);
            pixels[n].g = static_cast<uint8_t>(g);
            pixels[n].b = static_cast<uint8_t>(b);
            n++;
        }

        while (m_window->isOpen()) {
            sf::Event event;
            while (m_window->pollEvent(event))
                if (event.type == sf::Event::Closed)
                    m_window->close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                m_camera->dZ(0.1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                m_camera->dZ(-0.1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                m_camera->dX(-0.1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                m_camera->dX(0.1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                m_camera->dPitch(-0.02);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                m_camera->dPitch(0.02);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                m_camera->dRoll(-0.02);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                m_camera->dRoll(0.02);
            }
            m_size = 0;

            for(int i = 0; i < n; i++){
                m_points[i].x = points[i].x;
                m_points[i].y = points[i].y;
                m_points[i].z = points[i].z;
                m_size++;
            }
            for (int i = 0; i < m_size; i++) {
                m_camera->ProjectPoint(m_points[i],{pixels[i].r,pixels[i].g,pixels[i].b,255});
            }
            m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
            m_camera->Clear();


            m_window->clear();
            m_window->draw(*m_sprite);

            m_window->display();

        }
    }
}