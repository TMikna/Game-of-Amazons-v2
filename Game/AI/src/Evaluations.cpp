#include "../include/Evaluations.h"

// Editing Evaluation formula no possible move case in AlfaBetaAI_ss should be reviewed
float PossibleMovesEvaluation::Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor)
{
	float bias = 0.5;
	if (nextMovingTeamColor == teamColor)
		bias *= -1;
	short movCount = board->countAllMoves(teamColor);
	short enemyMovCount = board->countAllMoves(oppositeTeamColor);

	// evaluation = moves difference divided by moves sum
	// evaluaion range [-1;1] 0 is neutral, is positive - player is in better possition. The closer to 1 the better. Same the more negative the worse position it is
	float evaluation = (float(movCount - enemyMovCount) + bias) / (float(movCount + enemyMovCount) + std::abs(bias));
	// bias for: it can happen that there's 0 free spaces. Then the one moving next loses
	// It might also help getting close to such position
	return evaluation; 
}

// Editing Evaluation formula no possible move case in AlfaBetaAI_ss should be reviewed
float DirectionsMovesEvaluation::Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor)
{

	float cof1 = 0.3f;
	float cof2 = 1 - cof1;

	float bias = 0.5;
	if (nextMovingTeamColor == teamColor)
		bias *= -1;
	short movCount = board->countAllMoves(teamColor);
	short enemyMovCount = board->countAllMoves(oppositeTeamColor);

	short movDirections = board->allPossibleDirections(teamColor);
	short enemyMovDirections = board->allPossibleDirections(oppositeTeamColor);

	// evaluation = moves difference divided by moves sum
	// evaluaion range [-1;1] 0 is neutral, is positive - player is in better possition. The closer to 1 the better. Same the more negative the worse position it is
	float mowEvaluation = (float(movCount - enemyMovCount) + bias) / (float(movCount + enemyMovCount) + std::abs(bias));
	// bias for: it can happen that there's 0 free spaces. Then the one moving next loses
	// It might also help getting close to such position

	float dirEvaluation = (float(movDirections - enemyMovDirections) + bias) / (float(movDirections + enemyMovDirections) + std::abs(bias));

	float evaluation = cof1 * mowEvaluation + cof2 * dirEvaluation;

	return evaluation;
}

float CnnEvaluation::Evaluate(Board* board, short nextMovingTeamColor, short teamColor, short oppositeTeamColor)
{
	float evaluation = 0;

	//auto shape = cnnModel.get_input_shapes()[0];
	/*std::cout << "sizes: " << (std::string)shape.depth_ << '\n' << shape.height_ << '\n' << shape.width_ << std::endl;*/

	//auto start = std::chrono::high_resolution_clock::now();

	fdeep::tensor t(fdeep::tensor_shape(10, 10, 3), 0.0f);

	//auto createTensor = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> createDuration = createTensor - start;

	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			for (int c = 0; c < 3; ++c)
			{
				t.set(fdeep::tensor_pos(y, x, c), (float)board->boolBoard[y][x][c]);
			}
		}
	}

	//auto fillTensor = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> fillDuration = fillTensor - createTensor;

	//std::cout << t.get(fdeep::tensor_pos(0, 6, 1)) << std::endl;
	//std::cout << t.get(fdeep::tensor_pos(0, 6, 0)) << std::endl;
	//std::cout << t.get(fdeep::tensor_pos(0, 6, 2)) << std::endl;  

	const auto result = cnnModel.unsafe_get_just().predict_single_output({ t });

	auto predict = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> predictDuration = predict - fillTensor;
	//std::chrono::duration<double> allDuration = predict - start;
	//std::cout << "All evaluation time: " << allDuration.count() << " s" << " Create tensor: " << createDuration.count() << " s"
	//	<< " Fill tensor: " << fillDuration.count() << " s" << " Predict: " << predictDuration.count() << " s" << '\n';


	std::cout << result << '\n';
	evaluation = result * 2 - 1; //convert from [0;1] to [-1;1]

	if (teamColor == BLACKS)
		evaluation *= -1;
	//std::cout << evaluation << '\n';

	return evaluation;
}