#pragma once
#include "../../include/Board.h"
#include <fdeep/fdeep.hpp>

// template/base class for all evaluations
class Evaluation
{
public:
	Evaluation() {}

	//Pure Virtual function
	//virtual float Evaluate(Board* board, short teamColor) = 0;
	virtual float Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor) = 0;


protected:
	//short teamColor = -1;			// whites or blacks, -1 = neither
	//short oppositeTeamColor = -1;	// whites or blacks, -1 = neither
	//Board* board;					// board state
private:
};


class PossibleMovesEvaluation :
	public Evaluation
{
public:
	float Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor);
}; 

class DirectionsMovesEvaluation :
	public Evaluation
{
public:
	float Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor);

};

class CnnEvaluation :
	public Evaluation
{
public:
	float Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor);

	CnnEvaluation(std::string filepath)
	{
		if (filepath.length() <= 0)
			throw "invalid Cnn model path";

		const fdeep::model model = fdeep::load_model(filepath);
		cnnModel = model;



		//fdeep::tensor t(fdeep::tensor_shape(10, 10, 3), 0.0f);
		//const auto result = cnnModel.unsafe_get_just().predict_single_output({ t });
	}
private:
	fplus::maybe<fdeep::model> cnnModel;
};
