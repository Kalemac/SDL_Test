#include "Game.h"

Game* game = nullptr;

void playAudio(void* data, Uint8* stream, int length);

void Soundtrack(static Uint8* wav_buff);

static Uint8* audioPoint;	// global pointer audio buffer
static Uint32 audioLength;	// lenght that remains of audio


int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	//std::thread AudioThread(Soundtrack);

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		exit(-1);
	}
	/*
	std::cout << "Starting Audio" << std::endl;
	static Uint32 wavLength; // length of the audio file
	static Uint8* wav_buff;	// buffer with the file
	static SDL_AudioSpec wav_spec;

	if (SDL_LoadWAV("starstrike.wav", &wav_spec, &wav_buff, &wavLength) == NULL)
	{
		exit(-1);
	}

	wav_spec.callback = playAudio;	// assign the function to wav_spec
	wav_spec.userdata = NULL;	// user data is NULL

	audioPoint = wav_buff; // copy sound buffer
	audioLength = wavLength; // copy file length

	if (SDL_OpenAudio(&wav_spec, NULL) == -1)	// if you cant open the audio
	{
		exit(-1);
	}

	SDL_PauseAudio(0);
	*/
	static Uint8* wav_buff;	// buffer with the file

	Soundtrack(wav_buff);

	game = new Game();

	game->init("Star Strike", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 30 * 32 + 150, 20 * 32 + 100, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();


		game->eventHandler();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
		if (audioLength <= 0)	// Stop Audio when its done playing
		{
			SDL_CloseAudio();
			SDL_FreeWAV(wav_buff);
			Soundtrack(wav_buff);
		}
	}
	//AudioThread.join();
	game->clean();

	return 0;

}

void Soundtrack(static Uint8* wav_buff)
{

	std::cout << "Starting Audio" << std::endl;
	static Uint32 wavLength; // length of the audio file
	static SDL_AudioSpec wav_spec;

	if (SDL_LoadWAV("starstrike.wav", &wav_spec, &wav_buff, &wavLength) == NULL)
	{
		exit(-1);
	}

	wav_spec.callback = playAudio;	// assign the function to wav_spec
	wav_spec.userdata = NULL;	// user data is NULL

	audioPoint = wav_buff; // copy sound buffer
	audioLength = wavLength; // copy file length

	if (SDL_OpenAudio(&wav_spec, NULL) == -1)	// if you cant open the audio
	{
		exit(-1);
	}

	SDL_PauseAudio(0);
}

void playAudio(void* data, Uint8* audioStream, int length)
{

	if (audioLength == 0)	// No more audio remaining
	{
		return;
	}

	length = (length > audioLength ? audioLength : length);
	SDL_memcpy(audioStream, audioPoint, length); 					// simply copy from one buffer into the other

	audioPoint += length;
	audioLength -= length;
}
