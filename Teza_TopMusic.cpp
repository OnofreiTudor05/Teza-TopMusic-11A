#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(1000, 700), "Ribongs app", Style::Close | Style::Resize);;

Text text_de_scris;
RectangleShape dreptunghi, buton[10], pozitie_noua;
ConvexShape capat1, capat2;
Event eveniment;
Font font;
FloatRect dreptunghi_text;
Vector2u Dimensiuni;
Texture fundal_textura, logo_textura;
Sprite fundal, logo;
VertexArray gradient(Quads, 4), triunghi(Triangles, 3);
Text text_buton[10];
ContextSettings setari;
Color culoare_veche;
int i, j, indice_buton, n;
bool e_meniu, e_alegere_gen, apasat;

void Creeaza_Buton(RectangleShape &Loc_Aplicare, int marime_caracter, string nume_de_aplicat, Color culoare, Text &Aplicat, Vector2f pozitie_loc, Color culoare_buton, int Grosime_Buton, Color culoare_contur_buton){
    Aplicat.setFont(font);
    Aplicat.setCharacterSize(marime_caracter);
    Aplicat.setStyle(Text::Bold);
    Aplicat.setString(nume_de_aplicat);
    Aplicat.setFillColor(culoare);

    Loc_Aplicare.setFillColor(culoare_buton);
    Loc_Aplicare.setOutlineThickness(Grosime_Buton);
    Loc_Aplicare.setOutlineColor(culoare_contur_buton);
    Loc_Aplicare.setPosition(pozitie_loc);
    Loc_Aplicare.setSize(Vector2f(Aplicat.getLocalBounds().width+15, Aplicat.getCharacterSize()+10+Aplicat.getOutlineThickness()));
    Aplicat.setPosition((Loc_Aplicare.getPosition().x + Loc_Aplicare.getSize().x - Aplicat.getLocalBounds().width - 10), (Loc_Aplicare.getPosition().y + Loc_Aplicare.getSize().y - Aplicat.getCharacterSize())-10);
}

void Deseneaza_Triunghi(RectangleShape forma, Color Culoare, Color Culoare_Contur, int Grosime_Contur, int latime_capete, RenderWindow &fereastra, int poz){
    ConvexShape triunghi;
    triunghi.setFillColor(Culoare);
    triunghi.setOutlineThickness(Grosime_Contur);
    triunghi.setOutlineColor(Culoare_Contur);
    triunghi.setPointCount(3);
    if(poz == 1){
        triunghi.setPoint(0, Vector2f(forma.getPosition().x, forma.getPosition().y));
        triunghi.setPoint(1, Vector2f(forma.getPosition().x - latime_capete, forma.getPosition().y));
        triunghi.setPoint(2, Vector2f(forma.getPosition().x, forma.getPosition().y + forma.getSize().y/2));
    }
    if(poz == 2){
        triunghi.setPoint(0, Vector2f(forma.getPosition().x, forma.getPosition().y + forma.getSize().y/2));
        triunghi.setPoint(1, Vector2f(forma.getPosition().x - latime_capete, forma.getPosition().y + forma.getSize().y));
        triunghi.setPoint(2, Vector2f(forma.getPosition().x, forma.getPosition().y + forma.getSize().y));
    }
    if(poz == 3){
         triunghi.setPoint(0, Vector2f(forma.getPosition().x + forma.getSize().x, forma.getPosition().y));
        triunghi.setPoint(1, Vector2f(forma.getPosition().x + forma.getSize().x + latime_capete, forma.getPosition().y));
        triunghi.setPoint(2, Vector2f(forma.getPosition().x + forma.getSize().x, forma.getPosition().y + forma.getSize().y/2));
    }
    if(poz == 4){
        triunghi.setPoint(0, Vector2f(forma.getPosition().x + forma.getSize().x, forma.getPosition().y + forma.getSize().y/2));
        triunghi.setPoint(1, Vector2f(forma.getPosition().x + forma.getSize().x + latime_capete, forma.getPosition().y + forma.getSize().y));
        triunghi.setPoint(2, Vector2f(forma.getPosition().x + forma.getSize().x, forma.getPosition().y + forma.getSize().y));
    }
    fereastra.draw(triunghi);
    return ;
}

void Incarca_Fisiere(){
    e_meniu = true;
    fundal_textura.loadFromFile("Imagini/Fundal.png");
    logo_textura.loadFromFile("Imagini/Logo1.png");
    font.loadFromFile("Fonts/ScriptMTBold.ttf");
}

void Meniu_Principal(){
    Creeaza_Buton(buton[1], 42, "Start", Color::Black, text_buton[1], Vector2f(120, 500), Color(146, 39, 143), 4, Color(146, 39, 143));
    Creeaza_Buton(buton[2], 42, "Optiuni", Color::Black, text_buton[2], Vector2f(440, 500), Color(146, 39, 143), 4, Color(146, 39, 143));
    Creeaza_Buton(buton[3], 42, "Iesire", Color::Black, text_buton[3], Vector2f(800, 500), Color(146, 39, 143), 4, Color(146, 39, 143));

    gradient[0].position = Vector2f(0, 0);
    gradient[1].position = Vector2f(window.getSize().x, 0);
    gradient[2].position = Vector2f(window.getSize().x, window.getSize().y);
    gradient[3].position = Vector2f(0, window.getSize().y);
    gradient[0].color = gradient[3].color = Color(68, 14, 98);
    gradient[1].color = gradient[2].color = Color(70, 70, 70);

    logo_textura.setSmooth(true);
    logo.setTexture(logo_textura);
    logo.setPosition((window.getSize().x-logo.getLocalBounds().width)/2, (window.getSize().y - logo.getLocalBounds().height)/2 - 100);

    while(window.isOpen() && e_meniu){
        for(i = 1; i<=3; i++){
            dreptunghi_text = buton[i].getGlobalBounds();
            if(dreptunghi_text.contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
                text_buton[i].setFillColor(Color::White);
            } else{
                text_buton[i].setFillColor(Color::Black);
            }
        }
        while(window.pollEvent(eveniment)){
            switch(eveniment.type){
                default: break;
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
                for(i=1; i<=3 && !e_alegere_gen; i++){
                    dreptunghi_text = buton[i].getGlobalBounds();
                    if(eveniment.mouseButton.button == Mouse::Left && dreptunghi_text.contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
                            if(i == 3){
                        window.close();
                        return ;
                        }
                        else if(i == 1){
                            e_meniu = false;
                            e_alegere_gen = true;
                        }
                    }
            }
                break;
             break;
            }
        }
        window.clear();

        window.draw(gradient);
        window.draw(logo);
        for(i = 1; i<=3; i++){
            for(j = 1; j<=4; j++){
                Deseneaza_Triunghi(buton[i], Color::Yellow, Color::Yellow, 1, 75, window, j);
            }
            window.draw(buton[i]);
            window.draw(text_buton[i]);
        }
        window.display();
       }
    return ;
}

void Alegere_Gen(){
    n = 3;
    text_buton[1].setString("");
    text_buton[2].setString("");
    text_buton[3].setString("");
    buton[1].setSize(Vector2f(0, 0));
    buton[2].setSize(Vector2f(0, 0));
    buton[3].setSize(Vector2f(0, 0));

    gradient[0].position = Vector2f(0, 0);
    gradient[1].position = Vector2f(window.getSize().x, 0);
    gradient[2].position = Vector2f(window.getSize().x, window.getSize().y);
    gradient[3].position = Vector2f(0, window.getSize().y);
    gradient[0].color = gradient[3].color = Color(255, 0, 255);
    gradient[1].color = gradient[2].color = Color(70, 70, 70);

    Creeaza_Buton(buton[1], 42, "Rock", Color::White, text_buton[1], Vector2f(0, 75), Color::Black, 0, Color::Black);
    Creeaza_Buton(buton[2], 42, "Hip-Hop", Color::White, text_buton[2], Vector2f(0, 150), Color::Black, 0, Color::Black);
    Creeaza_Buton(buton[3], 42, "Clasic", Color::White, text_buton[3], Vector2f(0, 225), Color::Black, 0, Color::Black);

    while(window.isOpen() && e_alegere_gen){
        for(i = 1; i<=n; i++){
             dreptunghi_text = buton[i].getGlobalBounds();
             if(dreptunghi_text.contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)){
                indice_buton = i;
             }
        while(window.pollEvent(eveniment)){
             switch(eveniment.type){
                default: break;
            case Event::Closed:
                window.close();
                break;
              break;
            }
          }
        }
        window.clear();

        window.draw(gradient);
        for(i = 1; i<=n; i++){
             if(i == indice_buton){
                    Deseneaza_Triunghi(buton[i], Color::Yellow, Color::Yellow, 2, 75, window, 3);
                    Deseneaza_Triunghi(buton[i], Color::Yellow, Color::Yellow, 2, 75, window, 4);
                    window.draw(buton[i]);
                    window.draw(text_buton[i]);
                }
                else{
                    pozitie_noua.setPosition(buton[i].getPosition().x, buton[i].getPosition().y);
                    pozitie_noua.setSize(Vector2f(0, buton[i].getGlobalBounds().height + buton[i].getOutlineThickness()));
                    Deseneaza_Triunghi(pozitie_noua, Color::Yellow, Color::Yellow, 2, 75, window, 3);
                    Deseneaza_Triunghi(pozitie_noua, Color::Yellow, Color::Yellow, 2, 75, window, 4);
                }
            }
         window.display();
      }
    return ;
}

int main(){

    Incarca_Fisiere();
    Meniu_Principal();
    Alegere_Gen();

    return 0;
}

