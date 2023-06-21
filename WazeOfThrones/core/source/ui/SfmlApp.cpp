//
// Created by tsegura on 4/13/2023.
//

#include "../../header/ui/SfmlApp.h"

SfmlApp::SfmlApp() {
    this->checkAdjacentCitiesUI = new CheckAdjacentCities();
    this->searchCity = new SearchCity();
    this->shortestRoute = new DisplayRoute();
    this->appVariables = new AppVariables();
}

void SfmlApp::CheckForCityClick(Vector2f mousePosition) {
    // Find if the user just clicked a city
    City* currentCity = appVariables->GetMap()->GetRoot();
    while (currentCity != nullptr) {
        float dist = sqrt(pow(mousePosition.x - (currentCity->GetPosX() + NODES_RADIUS), 2) + pow(mousePosition.y - (currentCity->GetPosY() + NODES_RADIUS), 2));

        if (dist <= 8.0f) {
            appVariables->GetMap()->ClearHighlights();

            if (appVariables->GetSelectCityOption() == 0) {
                appVariables->SetFromCity(currentCity->GetName());
            } else {
                appVariables->SetToCity(currentCity->GetName());
            }
        }

        currentCity = currentCity->GetNext();
    }

}

Vector2f SfmlApp::normalizeVector(Vector2f source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0) {
        return Vector2(source.x / length, source.y / length);
    }

    return source;
}

RectangleShape SfmlApp::DrawLine(Vector2f from, Vector2f to, float thickness, Color color)
{
    RectangleShape line;
    line.setFillColor(color);

    Vector2f dir = (to - from);
    float rot = atan2(dir.y, dir.x) * (180.0f / M_PI);
    float dist = sqrt(pow(from.x - to.x, 2) + pow(from.y - to.y, 2));

    line.setPosition(from);
    line.setSize(Vector2f(dist, thickness));
    line.setRotation(rot);

    return line;
}

void SfmlApp::DrawUI(RenderWindow &window, Time delta, View view) {
    // Draw UI
    ImGui::SFML::Update(window, delta);
    ImGui::Begin("Menu Principal");

    bool reset = false;

    if (ImGui::Button("Ver ciudades adyascentes", ImVec2(200, 32))) {
        reset = true;
        appVariables->SetMenuOption(0);
    }
    if (ImGui::Button("Buscar", ImVec2(200, 32))) {
        reset = true;
        appVariables->SetMenuOption(1);
    }
    if (ImGui::Button("Mostrar ruta", ImVec2(200, 32))) {
        reset = true;
        appVariables->SetMenuOption(2);
    }

    ImGui::End();

    if (reset == true) {
        appVariables->SetSelectCityOption(false);
        appVariables->SetFromCity("");
        appVariables->SetToCity("");
        appVariables->GetMap()->ClearHighlights();

        checkAdjacentCitiesUI->Clear();
        shortestRoute->Clear();
    }

    switch (appVariables->GetMenuOption()) {
        case 0:
            checkAdjacentCitiesUI->ShowUI(appVariables);
            break;
        case 1:
            searchCity->ShowUI(appVariables, window, view);
            break;
        case 2:
            shortestRoute->ShowUI(appVariables);
            break;
    }
}

void SfmlApp::Run() {
    // Constants
    Color backgroundColor = Color(200, 233, 240, 255);
    Color nodesColor = Color(177, 172, 154, 255);
    Color highlightedNodeColor = Color(230, 208, 18, 255);

    Color fromNodeColor = Color(18, 164, 230);
    Color toNodeColor = Color(37, 230, 18);

    Color routesColor = Color(145, 145, 145, 145);
    Color highlightedRouteColor = Color(18, 189, 230, 255);

    // Font variables
    Font font;
    font.loadFromFile("../resources/PoltawskiNowy-Italic-VariableFont_wght.ttf");

    // Background variables
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("../resources/WazeOfThronesMap.png");
    backgroundTexture.setSmooth(true);
    backgroundTexture.setRepeated(false);
    Sprite background(backgroundTexture);

    // Scroll variables
    Vector2f clickPosition;
    bool moving = false;
    float zoomMultiplier = 0.1f;

    Clock deltaClock;

    RenderWindow window(VideoMode(896, 504), "Waze of Thrones");
    window.setFramerateLimit(60);
    View view = window.getDefaultView();

    ImGui::SFML::Init(window);

    while (window.isOpen())
    {
        Event event;

        // Input Events
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;

                case Event::MouseButtonPressed:
                    // Save the position where the use clicked
                    if (event.mouseButton.button == 1) {
                        moving = true;
                        clickPosition = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                    }

                    if (event.mouseButton.button == 0) {
                        Vector2f mousePos = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                        CheckForCityClick(mousePos);
                    }
                    break;

                case Event::MouseButtonReleased:
                    // Stop moving
                    if (event.mouseButton.button == 1) {
                        moving = false;
                    }
                    break;

                case Event::MouseMoved:
                    if (moving == true) {
                        // Calculate movement from previous frame
                        Vector2f mousePosition = window.mapPixelToCoords(Vector2i(event.mouseMove.x, event.mouseMove.y));
                        Vector2f deltaPos = clickPosition - mousePosition;

                        // Update view
                        appVariables->SetCameraPosition(appVariables->GetCameraPosition() + deltaPos);
                    }
                    break;

                case Event::MouseWheelScrolled:
                    if (moving == false) {
                        appVariables->SetCameraZoom(appVariables->GetCameraZoom() - (event.mouseWheelScroll.delta * zoomMultiplier));
                    }

                    break;
            }
        }

        appVariables->SetCameraZoom(clamp(appVariables->GetCameraZoom(), 0.5f, 5.0f));
        view.setCenter(appVariables->GetCameraPosition().x, appVariables->GetCameraPosition().y);
        view.setSize(window.getDefaultView().getSize());
        view.zoom(appVariables->GetCameraZoom());

        window.setView(view);

        DrawUI(window, deltaClock.restart(), view);

        window.clear(backgroundColor);
        window.draw(background);

        // Draw routes or arcs
        for (int i = 0; i < CITY_CAPACITY; i++) {
            City *from = appVariables->GetMap()->CityFromIndex(i);

            if (from == nullptr) {
                continue;
            }
            for (int j = 0; j < CITY_CAPACITY; j++) {

                if (appVariables->GetMap()->GetRoutes()[i][j] == nullptr) {
                    continue;
                }

                City *to = appVariables->GetMap()->CityFromIndex(j);

                if (to != nullptr) {
                    Vector2f fromPos = Vector2f(from->GetPosX() + NODES_RADIUS, from->GetPosY() + NODES_RADIUS);
                    Vector2f toPos = Vector2f(to->GetPosX() + NODES_RADIUS, to->GetPosY() + NODES_RADIUS);

                    if (appVariables->GetMap()->GetRoutes()[i][j]->IsHighlighted()) {
                        window.draw(DrawLine(fromPos, toPos, ROUTES_THICKNESS, highlightedRouteColor));
                    } else {
                        window.draw(DrawLine(fromPos, toPos, ROUTES_THICKNESS, routesColor));
                    }

                    float x = (fromPos.x + toPos.x) / 2;
                    float y = (fromPos.y + toPos.y) / 2;

                    // Distance Text
                    Text text;
                    text.setFont(font);
                    text.setString(to_string((int)(appVariables->GetMap()->GetRoutes()[i][j]->GetDistance())));
                    text.setCharacterSize(12);
                    text.setFillColor(Color(95, 95, 95, 255));
                    text.setPosition(x, y);

                    window.draw(text);
                }
            }
        }

        // Draw cities or nodes
        City* currentCity = appVariables->GetMap()->GetRoot();
        while (currentCity != nullptr) {
            // Node
            CircleShape cityNode;
            cityNode.setPosition(currentCity->GetPosX(), currentCity->GetPosY());
            cityNode.setRadius(NODES_RADIUS);

            if (currentCity->IsHighlighted() == true) {
                cityNode.setFillColor(highlightedNodeColor);
            } else {
                if (currentCity->GetName() == *appVariables->GetFromCity()) {
                    cityNode.setFillColor(fromNodeColor);
                } else if (currentCity->GetName() == *appVariables->GetToCity()) {
                    cityNode.setFillColor(toNodeColor);
                } else {
                    cityNode.setFillColor(nodesColor);
                }
            }

            window.draw(cityNode);

            // Text
            Text text;
            text.setFont(font);
            text.setString(currentCity->GetName());
            text.setCharacterSize(18);
            text.setFillColor(Color::Black);
            text.setPosition(currentCity->GetPosX()  - (NODES_RADIUS * 4), currentCity->GetPosY() - (NODES_RADIUS * 4));

            window.draw(text);

            currentCity = currentCity->GetNext();
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}