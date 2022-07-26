#include "Game.h"

void Game::initVariables()
{
    this->window = nullptr;
    this->playMusic = false;


}



void Game::initWindow()
{
    this->videMode.height = 600;
    this->videMode.width = 800;
    this->window = new sf::RenderWindow(this->videMode, "Bubble shooter Game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);

    //background image
    this->bgTexture.loadFromFile("png/bg.png");
    this->bg.setTexture(this->bgTexture);

}

void Game::initFonts()
{
    if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
    {
        std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
    }
}

void Game::initText()
{
    //Score text init
    this->scoreText.setFont(this->font);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setStyle(sf::Text::Bold);
    this->scoreText.setCharacterSize(23);
    this->scoreText.setPosition(sf::Vector2f(670.f, 125.f));


    //HighScore text init
    this->highScoreText.setFont(this->font);
    this->highScoreText.setFillColor(sf::Color::White);
    this->highScoreText.setStyle(sf::Text::Bold);
    this->highScoreText.setCharacterSize(20);
    this->highScoreText.setPosition(sf::Vector2f(690.f, 222.f));

}

void Game::initButtons()
{
    //music Button 
    this->musicButton = new PushButton(sf::Vector2f(695.f, 420.f), sf::Vector2f(50, 50));

    tex.loadFromFile("png/music.png");
    tex.setSmooth(true);
    this->musicButton->setTexture(tex);



    // Restart Button
        
    this->restartButton = new PushButton(sf::Vector2f(655.f, 500.f), sf::Vector2f(50, 50));
    this->restartTEX.loadFromFile("png/restart.png");
    this->restartTEX.setSmooth(true);
    this->restartButton->setTexture(restartTEX);

    //next level button
    //Next Level
    this->nextLevel = new PushButton(sf::Vector2f(735.f, 500.f), sf::Vector2f(50, 50));
    this->nextLevelTex.loadFromFile("png/nextLeveloff.png");
    this->nextLevelTex.setSmooth(true);
    this->nextLevel->setTexture(nextLevelTex);


}


Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initButtons();
}

Game::~Game()
{
    delete this->window;
}


const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    //envent polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
        if (!this->playMusic)
        {
            if (!this->music.openFromFile("audio/music.wav"))
                cout << "erreur music" << endl; // error
            this->music.play();
            this->music.setVolume(10.f);
            this->playMusic = true;
            this->music.setLoop(true);
        }
        if (this->musicButton->isClicked(this->ev, sf::Mouse::Left))
        {
            if (this->music.getStatus() == sf::Music::Playing)
            {
                this->music.stop();
                this->tex.loadFromFile("png/musicoff.png");
                this->musicButton->setTexture(tex);
            }
            else
            {
                this->music.play();
                this->tex.loadFromFile("png/music.png");
                this->musicButton->setTexture(tex);
            }

        }

        //restart
        if (this->restartButton->isClicked(this->ev, sf::Mouse::Left))
        {
            this->arena.restartGame();
            this->player.setScore(0);
        }

        //nextLevel
        if (this->arena.isWin())
        {
            this->nextLevelTex.loadFromFile("png/nextLevelon.png");
            this->nextLevel->setTexture(nextLevelTex);

        }
        if (this->nextLevel->isClicked(this->ev, sf::Mouse::Left))
        {
            if (this->arena.isWin())
            {
                this->arena.lancerNextLevel();
                this->player.setScore(0);

            }
        }


    }
}

void Game::updateOptions(Player* p)
{
    //score
    std::stringstream ss1;
    ss1 << " Score: " << this->player.getScore() << "\n";
    this->scoreText.setString(ss1.str());


    //bg_score
    this->scoreTexture.loadFromFile("png/score.png");
    this->scoreTexture.setSmooth(true);
    this->score.setTexture(this->scoreTexture);
    this->score.setPosition(665.f, 120.f);

    // mise à jour high score
        if (this->player.getHighScore() < this->player.getScore())
        {
            this->player.setHighScore(this->player.getScore());
            ofstream myfile("highscore.txt");
            if (myfile.is_open())
            {
                myfile << this->player.getHighScore();
                myfile.close();
            }
        }


    //HighScore
    std::stringstream ss2;
    ss2 << "HighScore: " << "\n   " << this->player.getHighScore() << "\n";
    this->highScoreText.setString(ss2.str());


    //bg_score
    this->highScoreTexture.loadFromFile("png/highscore.png");
    this->highScoreTexture.setSmooth(true);
    this->highScore.setTexture(this->highScoreTexture);
    this->highScore.setPosition(665.f, 220.f);




    //arena
    this->arena.update(this->window, p);

}




void Game::update()
{
    this->pollEvents();
    this->updateOptions(&this->player);

}

void Game::renderOptions(sf::RenderTarget* target)
{
    //render score
    target->draw(this->score);
    target->draw(this->scoreText);


    //render highScore
    target->draw(this->highScore);
    target->draw(this->highScoreText);

    //render music button 
    target->draw(*this->musicButton);
    //retstart button 
    target->draw(*this->restartButton);
    
    //next level
    target->draw(*this->nextLevel);




}

void Game::render()
{
    this->window->clear();
    this->window->draw(this->bg);

    //draw game objects
    this->renderOptions(this->window);
    this->arena.render(this->window);
    this->window->display();

}