#include <SFML/Graphics.hpp>
#include "player.h"
#include "obstacleManager.h"
#include "bonusManager.h"
#include "bonusesEffectsContext.h"
#include "laneManager.h"
#include "GameUI.h"
#include "difficultyManager.h"
#include "decoreManager.h"
using namespace sf;
using namespace std;
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Safewindows.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    const unsigned int WinWidth = 1280;
    const unsigned int WinHeight = 720;
    RenderWindow win(VideoMode({WinWidth , WinHeight }), "Lane Racers");
    Image icon;

    if (!icon.loadFromFile("Image/icon.png")) {
        std::cerr << "SFML �� ���� ��������� ������ �� �����!\n";
        
    }
    win.setIcon(48, 48, icon.getPixelsPtr());

    // ���
    const int tileHeight = 228;
    const int tileWidth = 576;
    Texture TRoadTile;
    TRoadTile.loadFromFile("Image/roadTile.png");

    vector<RectangleShape> roadTiles;
    int numTiles = (WinHeight / tileHeight) + 2;

    for (int i = 0; i < numTiles; ++i) {
        RectangleShape RoadBackgroundTile(Vector2f(tileWidth, tileHeight));
        RoadBackgroundTile.setTexture(&TRoadTile);
        RoadBackgroundTile.setPosition((WinWidth- tileWidth)/2, - tileHeight + i * tileHeight);
        roadTiles.push_back(RoadBackgroundTile);
    }
    Vector2f pos;
    Clock clock;
    float time;

    // ������� ����
    int borders = 50;
    int padding = 20;

    // ������
    bonusesEffectsContext BonusContext;

    // �����
    const int playerHeight = 135;
    const int playerWidth = 105;
    const Vector2f StartPosition = Vector2f((WinWidth - playerWidth) / 2, WinHeight - 1.5 * playerHeight);

    player Player(Vector2f(StartPosition.x, StartPosition.y), Vector2f(playerWidth, playerHeight), tileWidth, BonusContext, 1.8f);

    // �����
    decoreManager decManager(((WinWidth - tileWidth) / 2) + borders + padding, ((tileWidth - 2 * borders) / 2.8f));

    // ���������
    difficultyManager difManager;    

    // �������� �����
    laneManager LaneMng;

    // �������� �������
    bonusManager BonusManager(((WinWidth - tileWidth) / 2) + borders + padding, ((tileWidth - 2 * borders) / 2.8f), playerHeight, BonusContext, LaneMng);

    // �����������
    obstacleManager ObstacleManager(((WinWidth - tileWidth) / 2) + borders + padding, ((tileWidth - 2 * borders) / 2.8f), BonusContext, LaneMng);



    // UI
    GameUI gameUI(Vector2f(WinWidth, WinHeight));

    while (win.isOpen())
    {

        Event event;
        time = clock.getElapsedTime().asMicroseconds();
        time = time / 6000;
        clock.restart();
        
        while (win.pollEvent(event))
        {
            if (event.type == Event::Closed)
                win.close();
        }

        // �����
        if (Player.IsCanMove())
            decManager.update(time, WinWidth, difManager.GetCurrentDifficult());

        // ���������
        difManager.update(Player.GetScore());

        if (Player.IsCanMove()) {

        // �������� �������
        BonusContext.update();

        // ���������� ��������
        Player.handleInput(time);
        Player.update(time, WinWidth);

        if (BonusContext.IsShieldJustEnded()) {
            ObstacleManager.RemoveObstaclesTouched(Player);
            BonusContext.ResetShieldJustEnded();
        }

        // ���������� �������������
        if (!BonusContext.IsShieldActive() && ObstacleManager.checkCollisionsWithPlayer(Player)) {
            gameUI.SetGameOver();
            Player.ChangeMovePosible(false);
        }

        int OvertakedObstaclecount = ObstacleManager.checkPlayerOvertakedObstacle(Player);
        if (OvertakedObstaclecount > 0) {
            Player.AddScore(OvertakedObstaclecount);
        }

        ObstacleManager.checkPlayerNear(Player);

        ObstacleManager.update(time, WinHeight, difManager.GetCurrentDifficult());

        // ���������� ��������
        BonusType collectedBonus;
        if (BonusManager.checkCollisionsWithPlayer(Player, collectedBonus)) {
            switch (collectedBonus) {
            case BonusType::ShieldBoost:
                BonusContext.SetShield();
                break;
            case BonusType::ScoreBoost:
                BonusContext.SetDoubleScore();
                break;
            case BonusType::SlowBoost:
                BonusContext.SetSlowDown();
                break;
            default:
                std::cerr << "����������� �����!\n";
                break;
            }
        }

        BonusManager.update(time, WinHeight, difManager.GetCurrentDifficult());

        // ���������� ������
        gameUI.update(Player.GetScore(), BonusContext.GetActiveBonuses());

        }
        else {
            // ���������
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                Player.Reset(StartPosition);
                ObstacleManager.Reset();
                BonusManager.Reset();
                BonusContext.Reset();
                gameUI.Reset();
                difManager.Reset();
                LaneMng.Reset();
                decManager.Reset();
            }
        }

        win.clear();

        // ������ �����
        for (auto& tile : roadTiles) {
            if(Player.IsCanMove())
                tile.move(0, difManager.GetCurrentDifficult().roadSpeedMult * time);
            if (tile.getPosition().y >= WinHeight)
                tile.setPosition((WinWidth - tileWidth) / 2, tile.getPosition().y - tileHeight * roadTiles.size());
            win.draw(tile);
        }
        decManager.draw(win);
        ObstacleManager.draw(win);
        BonusManager.draw(win);
        Player.draw(win);
        gameUI.draw(win);
        win.display();
    }
}