#include <fstream>
#include <stdexcept>
#include "Engine.h"
#include "MoveFactory.h"
#include "BinaryGameSerializer.h"
#include "CommonUtils.h"

UserInput Engine::getMoveInput(char* buffer, int lengthBuffer, std::istream& is, std::ostream& os) const
{
	if (buffer == nullptr)
	{
		throw std::invalid_argument("Buffer cannot be null");
	}

	const char END[] = "0";
	os << "Enter a move or press " << END << " to exit and save your game" << std::endl;

	is.getline(buffer, lengthBuffer);

	if (strcmp(buffer, END) == 0)
	{
		return UserInput::Exit;
	}

	return UserInput::MakeMove;
}

InputMoveResult Engine::handleMove(Game& game, std::istream& is, std::ostream& os) const
{
	PieceColor turnToMove = game.getTurnToMove();
	if (turnToMove == PieceColor::White)
	{
		os << "White";
	}
	else if (turnToMove == PieceColor::Black)
	{
		os << "Black";
	}
	os << " to move" << std::endl;
	
	const int MAX_INPUT_SIZE = 1024;
	char inputNotation[MAX_INPUT_SIZE];
	UserInput inputResult = getMoveInput(inputNotation, MAX_INPUT_SIZE, is, os);

	if (inputResult == UserInput::Exit)
	{
		return InputMoveResult::End;
	}

	try
	{
		Move* move = MoveFactory::createMove(inputNotation);

		while (!move->execute(game))
		{
			delete move;

			os << "Illegal move" << std::endl;

			inputResult = getMoveInput(inputNotation, MAX_INPUT_SIZE, is, os);
			if (inputResult == UserInput::Exit)
			{
				return InputMoveResult::End;
			}

			move = MoveFactory::createMove(inputNotation);
		}

		if (move->isCaptureMove())
		{
			game.previousPositionsUnreachable();
		}

		delete move;

		return InputMoveResult::SuccessfulMove;;
	}
	catch (const std::exception& ex)
	{
		os << ex.what() << std::endl;
	}
	catch (...)
	{
		os << "An error occurred";
	}

	return InputMoveResult::UnsuccessfulMove;
}

void Engine::serialize(const Game& game, std::istream& is, std::ostream& os) const
{
	os << "Enter location to save the game:" << std::endl;

	const int MAX_SIZE = 1024;
	char buffer[MAX_SIZE];
	is.getline(buffer, MAX_SIZE);

	std::ofstream ofs;
	ofs.open(buffer, std::ios::binary);
	while (!ofs.is_open())
	{
		os << "Couldn't open or create file with this name. Please try again" << std::endl;
		is.getline(buffer, MAX_SIZE);
		ofs.open(buffer, std::ios::binary);
	}

	BinaryGameSerializer serializer;
	if (serializer.serialize(game, ofs))
	{
		os << "Game saved successfully" << std::endl;
	}
	else
	{
		os << "Couldn't save game" << std::endl;
	}

	ofs.close();
}

void Engine::run(Game& game, std::istream& is, std::ostream& os, ChessVariant& chessVariant, const UserInterface& userInterface) const
{
	CommonUtils::clearConsole();
	const Board& board = chessVariant.getBoard();

	while (true)
	{
		userInterface.drawBoard(board);	

		InputMoveResult result = handleMove(game, is, os);
		while (true)
		{
			if (result == InputMoveResult::End)
			{
				serialize(game, is, os);
				return;
			}
			if (result == InputMoveResult::SuccessfulMove)
			{
				break;
			}

			result = handleMove(game, is, os);
		}

		CommonUtils::clearConsole();

		GameResult gameResult = game.rules().getResult(game);
		if (gameResult != GameResult::None)
		{
			userInterface.drawBoard(board);

			if (gameResult == GameResult::Win)
			{
				os << "Checkmate";
			}

			else if (gameResult == GameResult::Draw)
			{
				os << "Draw";
			}

			break;
		}

		game.changeTurn();
	}
}
