#include<iostream>;
using namespace std;
enum enGameChoice{Stone =1 , Paper =2 , Scissors = 3};
enum enWinner{Player =1 , Computer =2 , Draw =3};
struct stRoundInfo {
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};
struct stGameResult {
	short GameRound = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};
int Random(int From, int To) {
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}
enGameChoice GetComputerChoice() {
	return enGameChoice(Random(1, 3));
}
enWinner WhoWinTheRound(stRoundInfo RoundInfo) {
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
		return enWinner::Draw;
	switch (RoundInfo.PlayerChoice) {
	case enGameChoice::Stone: 
		return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer:enWinner::Player;
	case enGameChoice::Scissors:
		return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player;
	case enGameChoice::Paper:
		return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player;
			
	}
}
enWinner WhoWinTheGame(short PlayerWinTimes,short ComputerWinTimes) {
	if (PlayerWinTimes > ComputerWinTimes)
	{
		
		return enWinner::Player;
	}
	else if (PlayerWinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}
string ChoiceName(enGameChoice Choice) {
	string arrGameChoices[3] = { "Stone","Paper","Scissors" };
	return arrGameChoices[Choice - 1];

}
string WinnerName(enWinner winner) {
	string arrWinnerName[3] = { "Player","Computer","NoWinner" };
	return arrWinnerName[winner - 1];
}
enGameChoice ReadPlayerChoice() {
	short choice;
	do {
		cout << "\nYour Choice [1]:Stone, [2]:Paper, [3]:Scissors?";
		cin >> choice;
	} while (choice < 1 || choice > 3);
	return enGameChoice(choice);
}
void PrintRoundResults(stRoundInfo RoundInfo) {
	cout << "\n____________ Round [" << RoundInfo.RoundNumber << "]____________\n\n";
	cout << "\tPlayer Choice  : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "\tComputer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "\tRound Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "_________________________________________\n" << endl;

}
void GameOverScreen() {
	cout << "\n\n";
	cout << "\t\t                         *** G a m e  O v e r ***\n";
	cout << "\t\t-----------------------------------------------------------------------\n\n";
}
void WinnerScreenColor(enWinner winner) {
	switch (winner) {
	case enWinner::Player:
		system("color 2F");
		cout << "\a";
		break;
	case enWinner::Computer:
		system("color 4F");
		break;
	default:
		system("color 6F");
		break;
	}
}

stGameResult FillGameResult(int HowManyRounds,short DrawTimes,short PlayerWinTimes,short ComputerWinTimes) {
	stGameResult GameResult;
	GameResult.GameRound = HowManyRounds;
	GameResult.PlayerWinTimes = PlayerWinTimes;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWinTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);
	WinnerScreenColor(GameResult.GameWinner);

	return GameResult;
 }
stGameResult PlayGame(short HowManyRounds) {
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWinTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player)
		{
			PlayerWinTimes++;
			
		}
		else if (RoundInfo.Winner == enWinner::Computer)
		{
			ComputerWinTimes++;
		}
		else
		{
			DrawTimes++;
		}
		PrintRoundResults(RoundInfo);
	}
	return FillGameResult(HowManyRounds, DrawTimes, PlayerWinTimes, ComputerWinTimes);

}
void PrintGameResult(stGameResult GameResutl) {
	cout << "\t\t-----------------------------[Game Result]-----------------------------\n\n";
	cout << "\t\tGame Rounds        : " << GameResutl.GameRound << endl;
	cout << "\t\tPlayer win tiems   : " << GameResutl.PlayerWinTimes << endl;
	cout << "\t\tComputer win times : " << GameResutl.ComputerWinTimes << endl;
	cout << "\t\tDraw times         : " << GameResutl.DrawTimes << endl;
	cout << "\t\tFinal Winner       : " << GameResutl.WinnerName << endl;
	cout << "\t\t-----------------------------------------------------------------------\n\n";
}
void ResetScreen() {
	system("cls");
	system("color 0F");
}
string CheckChar(string word) {
	string Nword = "";

	for (int i = 0; i < size(word); i++) {
		if (isupper(word[i])) {
			Nword += tolower(word[i]);
		}
		else
			Nword += word[i];
	}

	return Nword;
}
short ReadManyRounds() {
	short Rounds;
	do {
		cout << "How many Rounds 1 to 10 ?\n";
		cin >> Rounds;
	} while (Rounds < 1 || Rounds > 10);
	return Rounds;
}

void StartGame()
{
	string PlayAgain  = "";
	bool result;
	do
	{
		ResetScreen();
		stGameResult GameResults = PlayGame(ReadManyRounds());
		GameOverScreen();
		PrintGameResult(GameResults);
		cout << "\n\tDo you want to play again? (Yes/No): ";
		cin >> PlayAgain;
		if (CheckChar(PlayAgain) == "yes")
			result = true;
		else if (CheckChar(PlayAgain) == "no")
			result = false;
		else
		{
			
		}

	} while (result);
}
int main() {

	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}
