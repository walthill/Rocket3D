#ifndef GAME_MSG_H
#define GAME_MSG_H

#define PURE_VIRTUAL =0

enum GameMessageType
{
	INVALID_MESSAGE_TYPE = -1,
	BUTTON_DOWN = 0
};

class GameMessage
{

	public:
		friend class GameMessageManager;

		GameMessage(GameMessageType type);
		~GameMessage();

		double getScheduledTime() const { return mScheduledTime; };
		double getSubmittedTime() const { return mSubmittedTime; };

	protected:
		GameMessageType mType;
		double mSubmittedTime;
		double mScheduledTime;

	private:
		virtual void process() PURE_VIRTUAL;

};

#endif // !GAME_MSG_H
