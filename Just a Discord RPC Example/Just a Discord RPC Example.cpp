#include <Windows.h>//GetAsyncKeyState.
#include <chrono>//We will use chrono for the elapsed time.

//Discord SDK Stuff.
#include "DiscordSDK/include/discord_rpc.h"
#include "DiscordSDK/include/discord_register.h"

static bool gInit, gRPC = true;

void SetupDiscord()
{
	if (gRPC)
	{
		DiscordEventHandlers handlers;
		memset(&handlers, 0, sizeof(handlers));
		Discord_Initialize("1234567890", &handlers, 1, "0");
	}
	else
	{
		Discord_Shutdown();
	}
}


static void UpdateDiscord()
{
	static int64_t StartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	if (gRPC)
	{
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));
		discordPresence.state = "I am the RPC Title.";
		discordPresence.details = "I am just a simple bio.";
		discordPresence.startTimestamp = StartTime;
		discordPresence.endTimestamp = NULL;
		discordPresence.largeImageKey = "LargeImage";
		discordPresence.largeImageText = "LargeImageText";
		discordPresence.smallImageKey = "SmallImage";
		discordPresence.smallImageText = "SmallImageText";
		discordPresence.instance = 1;

		Discord_UpdatePresence(&discordPresence);
	}
	else
	{
		Discord_ClearPresence();
	}
}

int main()
{
	printf("Discord RPC Example\r\n");
	printf("Hit SHIFT to togle On/Off\r\n");

	if (GetAsyncKeyState(VK_SHIFT))
	{
		gRPC = !gRPC;
	}

	if (gInit)//Initialize the RPC.
	{
		SetupDiscord();
		gInit = false;
	}

	UpdateDiscord();//Update it.

    getchar();
}