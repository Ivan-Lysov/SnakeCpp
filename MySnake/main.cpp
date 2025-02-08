#include <iostream>
#include <vector>
#include <conio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

class Snake {
private:
	std::pair<int, int> head;
	int cnt_of_links_of_the_snake;
	std::vector <std::pair<int, int>>body;
	int score;
public:
	std::pair<int, int> direction;
	Snake() : head(5, 5), cnt_of_links_of_the_snake(3), direction(1, 0), score(0) {
		for (int i = 0; i < cnt_of_links_of_the_snake; i++) {
			body.push_back({ head.first - i,head.second });
		}
	}
	std::pair<int, int> getHead() const { return head; }
	int getScore() const{ return score; }
	void ate_the_food() { cnt_of_links_of_the_snake++; }
	void move();
	void changeDirection(std::pair<int, int> NewDirection);
	std::vector < std::pair<int, int>>getBody() const;
	void grow();
};
std::vector <std::pair<int, int>>Snake::getBody() const { return body; }
void Snake::move() {
	head.first += direction.first;
	head.second += direction.second;
	body.insert(body.begin(), head);
	if (body.size() > cnt_of_links_of_the_snake) {
		body.pop_back();
	}
}
void Snake::changeDirection(std::pair<int, int> NewDirection) {
	if (direction.first + NewDirection.first == 0 || direction.second + NewDirection.second == 0) {
		return;
	}
	direction = NewDirection;
}
void Snake::grow() {
	cnt_of_links_of_the_snake++;
	score++;
}

class Food {
private:
	int fieldWidth, fieldHeight;
	std::pair<int, int> coordinatesFood;
	bool isEaten;
public:
	Food(int width, int height, Snake& snake) :fieldHeight(height), fieldWidth(width), isEaten(false) {
		generateNewPosition(snake);
	}
	void generateNewPosition(const Snake& snake);
	bool isEatens() const { return isEaten; }
	void setEaten(bool eaten, Snake& snake);
	std::pair<int, int> getCoordinatesFood() const { return coordinatesFood; }
};

void Food::generateNewPosition(const Snake& snake) {
	int x, y;
	bool isOnSnake = false;
	x = rand() % fieldWidth;
	y = rand() % fieldHeight;
	do {
		if (snake.getHead().first == x && snake.getHead().second == y) {
			isOnSnake = true;
			continue;
		}
		for (const auto& segment : snake.getBody()) {
			if (segment.first == x && segment.second == y) {
				isOnSnake = true;
				break;
			}
		}
	} while (isOnSnake);
	coordinatesFood = { x,y };
}

void Food::setEaten(bool eaten, Snake& snake) {
	if (eaten) {
		isEaten = true;
		generateNewPosition(snake);
	}
	else
		isEaten = false;
}

class field {
private:
	int width;
	int height;
	std::vector<std::vector<char>> grid;
	Snake& snake;
	Food& food;
public:
	field(int w, int h, Snake& s, Food& f) : width(w), height(h), grid(h, std::vector<char>(w, ' ')), snake(s), food(f) {}
	void draw(const Snake& snake);
	void update(Snake& snake, Food& food);
	bool checkCollision(Snake& snake, Food& food);
	std::string GameOver(const Snake& snake) const;
	std::vector<std::vector<char>> getGrid() { return grid; }
};

void field::draw(const Snake& snake) {
	system("cls");
	std::cout << "Score: " << snake.getScore() <<std::endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			bool isBodySegment = false;
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
				std::cout << '#';
			}
			else if (snake.getHead() == std::make_pair(j, i)) {
				std::cout << 'O';
			}
			else {
				for (auto& segment : snake.getBody()) {
					if (segment == std::make_pair(j, i)) {
						isBodySegment = true;
						break;
					}
				}
				if (isBodySegment) {
					std::cout << 'o';
				}
				else if (food.getCoordinatesFood() == std::make_pair(j, i)) {
					std::cout << 'X';
				}
				else {
					std::cout << ' ';
				}
			}
		}
		std::cout << '\n';
	}
}

std::string field:: GameOver(const Snake& snake) const {
	int score = snake.getScore();
	std::string result= "Game Over! You have " + std::to_string(score) + " scores! \n";
	std::cout << result;
	return result;
}

bool field::checkCollision(Snake& snake, Food& food) {
	bool isFoodEaten = false;
	if (snake.getHead() == food.getCoordinatesFood()) {
		snake.grow();
		food.generateNewPosition(snake);
		isFoodEaten = true;
	}
	bool isGameOver = false;
	if (snake.getHead().first < 0 || snake.getHead().first == width ||
		snake.getHead().second < 0 || snake.getHead().second == height) {
		isGameOver = true;
		GameOver(snake);
	}
	else {
		for (size_t i = 1; i < snake.getBody().size(); i++) {
			if (snake.getBody()[i] == snake.getHead()) {
				isGameOver = true;
				GameOver(snake);
			}
		}
	}

	return isGameOver;
}

void field::update(Snake& snake, Food& food) {
	if (_kbhit()) {
		char key = _getch();
		std::pair<int, int> newDirection = snake.direction;

		if (key == 'w' || key == 'W') {
			newDirection = { 0, -1 };
		}
		else if (key == 's' || key == 'S') {
			newDirection = { 0, 1 };
		}
		else if (key == 'a' || key == 'A') {
			newDirection = { -1, 0 };
		}
		else if (key == 'd' || key == 'D') {
			newDirection = { 1, 0 };
		}
		if (newDirection.first + snake.direction.first != 0 ||
			newDirection.second + snake.direction.second != 0) {
			snake.direction = newDirection;
		}
	}
	if (checkCollision(snake, food)) {
		std::cout << "Game Over" << std::endl;
		exit(0);
	}
	snake.move();
}

int main() {
	srand(time(0));
	int width = 25;
	int height = 15;

	Snake snake;
	Food food(width, height, snake);
	field field(width, height, snake, food);

	while (true) {
		field.draw(snake);
		field.update(snake, food);

		if (field.checkCollision(snake, food)) {
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	return 0;
}