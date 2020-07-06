#include "game.h"

Game::Game(std::size_t kScreenWidth, std::size_t kScreenHeight) : _engine(_dev()),
																  _random_x(0, static_cast<int>(kScreenWidth)),
																  _kScreenWidth(kScreenWidth), _kScreenHeight(kScreenHeight)
{
	_player = std::make_shared<Player>(100, 550);
	_virus = std::make_shared<Entity>();
}

void Game::Run(Controller const &controller, Renderer &renderer,
			   std::size_t target_frame_duration, int mode)
{
	Uint32 title_timestamp = SDL_GetTicks();
	Uint32 frame_start;
	Uint32 frame_end;
	Uint32 frame_duration;
	int frame_count = 0;
	//bool running = true;

	while (1)
	{
		frame_start = SDL_GetTicks();

		// Input for differents handle inputs
		if (mode == 2)
		{
			controller.HandleInputTracking(_player);
		}
		else
		{
			controller.HandleInput(_player);
		}

		Update();
		renderer.Render(_player, _virus);
		//std::thread t1 = std::thread(&Tracking::tracking_color, tracking);
		//t1.join();

		frame_end = SDL_GetTicks();

		// Keep track of how long each loop through the input/update/render cycle
		// takes.
		frame_count++;
		frame_duration = frame_end - frame_start;

		// After every second, update the window title.
		if (frame_end - title_timestamp >= 1000)
		{
			renderer.UpdateWindowTitle(_score, frame_count);
			frame_count = 0;
			title_timestamp = frame_end;
		}

		// If the time for this frame is too small (i.e. frame_duration is
		// smaller than the target ms_per_frame), delay the loop to
		// achieve the correct frame rate.
		if (frame_duration < target_frame_duration)
		{
			SDL_Delay(target_frame_duration - frame_duration);
		}
		//SDL_Delay(16);
	}
}

void Game::Update()
{

	if (_player->up)
	{
		_player->y -= 4;
	}

	if (_player->down)
	{
		_player->y += 4;
	}

	if (_player->left)
	{
		_player->x -= 4;
	}

	if (_player->right)
	{
		_player->x += 4;
	}

	//Choose a random position for the virus and set the movement vertically
	if (_virus->health == 0)
	{
		_virus->y = 50;
		_virus->x = _random_x(_engine);
		_virus->dx = 0;
		_virus->dy = 8;
		_virus->health = 1;
	}

	//The virus moves vertically
	_virus->x += _virus->dx;
	_virus->y += _virus->dy;

	//Calculate the distance between the player and the virus
	float dist = distance(_player->x + 75, _player->y + 30, _virus->x, _virus->y);

	//Increase the score of the player
	if (dist < 50)
		_score++;

	//Virus health is 0 when the distance with the player is less than 50
	if ((_virus->y > _kScreenHeight) || (dist < 50.0))
	{
		_virus->health = 0;
	}
}

float Game::distance(int x1, int y1, int x2, int y2)
{
	float x_diff = x1 - x2;
	float y_diff = y1 - y2;

	return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}