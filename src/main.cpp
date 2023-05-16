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

        // https://stackoverflow.com/a/19728404/15165564
        // Q: Generating a random integer from a range
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

        Player player_1; 
        Player player_2;
        Player* current_player = &player_1;

    public:
        Board(): player_1(1, 1), player_2(1, 2), dice(1, 6) {};

        bool check_continue() {
            if (this->turn == 1) {
                return true;
            };

            if (current_player->get_position() == 30) {
                return false;
            }

            string c;
            cin >> c;
            if (c == "C") {
                return true;
            }

            if (c == "E") {
                return false;
            }

            cout << "Invalid option, please press C to continue next turn or E to end the game" << endl;

            return this->check_continue();
        };

        void next() {
            int dice_roll = this->dice.generate();
            int new_position = current_player->get_position() + dice_roll;

            bool is_ladder = false;
            for (int i = 0; i < 3; i++) {
                int ladder_position = ladders[i];

                if (ladder_position == new_position) {
                    is_ladder = true;
                }
            }

            bool is_snake = false;
            for (int i = 0; i < 3; i++) {
                int snake_position = snakes[i];

                if (snake_position == new_position) {
                    is_snake = true;
                }
            }

            cout << turn << " ";
            cout << current_player->get_id() << " ";;
            cout << current_player->get_position() << " ";
            cout << dice_roll << " ";


            if (is_snake) {
                cout << "S ";
                new_position -= 3;

            }

            if (is_ladder) {
                cout << "L ";
                new_position += 3;
            }

            if (!is_ladder && !is_snake) {
                cout << "N ";
            }

            if (new_position < 0) {
                new_position = 0;
            }

            if (new_position > 30) {
                new_position = 30;
            }

            current_player->set_position(new_position);

            cout << new_position << endl;

            if (!(new_position == 30)) {
                if (current_player == &this->player_1) {
                    current_player = &this->player_2; 
                } else {
                    current_player = &this->player_1;
                }
            } 

            turn++;
        };

        void start() {
            cout << "Press C to continue next turn, or E to end the game:" << endl;

            while (this->check_continue()) {
                this->next();
            }
            
            cout << "-- GAME OVER --" << endl;

            if (current_player->get_position() == 30) {
                cout << "Player " << current_player->get_id() << " is the winner" << endl;
            }
        };
};


int main() {
    Board board;

    board.start();

    return 0;
}

