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
        Point position = { 0.0, 0.0, 0.0 };
        Angles angles = { 0.0,0.0,0.0 };
        m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);

        m_points = new Point[200000];

        /*double r = 1;
        for(double fi = 0; fi < 6.28; fi += 0.01)
            for (double teta = 0; teta < 1.57; teta += 0.01)
            {
                m_points[m_size].x = r * sin(teta) * cos(fi);
                m_points[m_size].y = r * sin(teta) * sin(fi) + 5;
                m_points[m_size].z = r * cos(teta);
                m_size++;
            }*/
    }
    Scene::~Scene(){
        if (m_points != nullptr)
            delete[] m_points;
    }


    void Scene::LifeCycle(){
        double y0 = 1;

        std::ifstream inPoints("../points.txt");
        if(!inPoints.is_open()) {
            std::cerr << "File points.txt not found";
            return;
        }

        std::vector<double> mas;
        double num;

        while (!inPoints.eof()) {
            inPoints >> num;
            mas.push_back(num);
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

            y0 += 0.02;
            m_size = 0;

            std::cout << std::setprecision(3) << std::fixed;
            for(int i = 0; i < mas.size(); i++){
                m_points[m_size].x = mas[i];
                m_points[m_size].y = mas[i+1];
                m_points[m_size].z = mas[i+2];
                i+=3;
            }

            for (int i = 0; i < mas.size(); i++)
                m_camera->ProjectPoint(m_points[i], {(uint8_t) mas[i + 3], (uint8_t) mas[i + 4], (uint8_t) mas[i + 5], 255});

            m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
            m_camera->Clear();


            m_window->clear();
            m_window->draw(*m_sprite);

            m_window->display();

        }
    }
}
