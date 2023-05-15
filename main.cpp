using namespace std;
#include <iostream>
#include <random>


class RNG {
    private:
        int min;
        int max;

    public:
        RNG(int min, int max) {
            this->min = min;
            this->max = max;
        }

        int generate() {
            std::random_device rd;     
            std::mt19937 rng(rd());    
            std::uniform_int_distribution<int> uni(this->min,this->max); 
            return uni(rng);
        };
};


class Player {
    private: 
        int position;
        int id;

    public:
        Player(int p, int i) {
            this->position = p;
            this->id = i;
        };

        int get_id() {
            return this->id;
        }

        int get_position() {
            return this->position;
        }

        void set_position(int p) {
            this->position = p;
        }
};


class Board {
    private:
        RNG dice;
        int turn = 1;
    

        int ladders[3] = {1, 7, 15};
        int snakes[3] = {5, 8, 22};
        bool exit = false;

        Player player_1; 
        Player player_2;
        Player* current_player = &player_1;

    public:
        Board(): player_1(1, 1), player_2(1, 2), dice(1, 6) {};

        void next() {
            // El número del turno (el primer turno se indica con el número 1)
            cout << "El turno es ";
            cout << turn << endl;

            // El número del jugador con el turno actual
            cout << "Turno del Jugador ";
            cout << current_player->get_id() << endl;

            // El número de casilla correspondiente a la posición actual del Jugador
            cout << "El jugador esta en la casilla ";
            cout << current_player->get_position() << endl;

            // El número obtenido al simular un dado convencional de 6 caras
            int dice_roll = this->dice.generate();

            cout << "Al tirar el dado se obtuvo ";
            cout << dice_roll << endl;

            // El tipo de casilla a la que el jugador debería moverse después de tirar el dado
            int new_position = current_player->get_position() + dice_roll;

            // find if position is ladder
            bool is_ladder = false;
            for (int i = 0; i < 3; i++) {
                int ladder_position = ladders[i];

                if (ladder_position == new_position) {
                    is_ladder = true;
                }
            }

            // find if position is snake 
            bool is_snake = false;
            for (int i = 0; i < 3; i++) {
                int snake_position = snakes[i];

                if (snake_position == new_position) {
                    is_snake = true;
                }
            }
            
            if (is_snake) {
                cout << "La nueva posicion es una serpiente! (S)" << endl;
                new_position -= 3;

            }

            if (is_ladder) {
                cout << "La nueva posicion es una escalera! (L)" << endl;
                new_position += 3;
            }

            if (!is_ladder && !is_snake) {
                cout << "La nueva posicion es normal (N)" << endl;
            }

            if (new_position < 0) {
                new_position = 0;
            }

            if (new_position > 30) {
                new_position = 30;
            }

            current_player->set_position(new_position);

            // Imprimir la posicion final
            cout << "La nueva posicion es ";
            cout << new_position << endl;

            // Cicle logic
            if (current_player == &this->player_1) {
                current_player = &this->player_2; 
            } else {
                current_player = &this->player_1;
            }

            if (new_position == 30) {
                this->exit = true;
            }

            turn++;
        };

        void play() {
            while (!this->exit) {
                cout << "-------------" << endl;
                this->next();
            }
        };
};


int main() {
    Board board;
    
    board.play();

    return 0;
}

