#include "pch.h"
#include "CppUnitTest.h"
#include "../Noobie/Board.h"
#include "../Noobie/MoveGenerator.h"
#include "../noobie/Evaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(BoardTest)
	{
	public:
        // Test: Comprobar que se establece correctamente el bit en la posición deseada
        TEST_METHOD(TestSetBit) 
        {
            Board board = Board(false);
            uint64_t initialBoard = 0;  // Inicialmente todos los bits son 0
            int position = 5;           // Queremos establecer el bit en la posición 5

            uint64_t result = board.setBit(initialBoard, position);

            // Esperamos que el bit en la posición 5 se haya establecido a 1
            uint64_t expected = 1ULL << position;

            // Comprobamos si el resultado es el esperado
            Assert::AreEqual(expected, result);
        }

        // Test: Verificar que el bit ya establecido no cambia
        TEST_METHOD(TestSetBitAlreadySet)
        {
            Board board = Board(false);
            uint64_t initialBoard = 1ULL << 5;  // El bit en la posición 5 ya está establecido
            int position = 5;                    // Queremos establecer el bit en la posición 5

            uint64_t result = board.setBit(initialBoard, position);

            // El valor del tablero no debería cambiar, ya que el bit ya estaba establecido
            Assert::AreEqual(initialBoard, result);
        }

        // Test: Comprobar que se puede establecer un bit en una posición alta
        TEST_METHOD(TestSetBitHighPosition)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0;   // Inicialmente todos los bits son 0
            int position = 63;            // Establecemos el bit en la posición más alta (bit 63)

            uint64_t result = board.setBit(initialBoard, position);

            // Comprobamos si el bit en la posición 63 se ha establecido
            uint64_t expected = 1ULL << position;

            Assert::AreEqual(expected, result);
        }

        // Test: Verificar que no modifica bits que no están en la posición deseada
        TEST_METHOD(TestSetBitOtherBitsNotModified)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b1010101010101010101010101010101010101010101010101010101010101010ULL;
            int position = 7; // Establecemos el bit en la posición 7

            uint64_t result = board.setBit(initialBoard, position);

            // Creamos el valor esperado con solo el bit 7 establecido en 1
            uint64_t expected = initialBoard | (1ULL << position);

            Assert::AreEqual(expected, result);
        }

        // Test: Obtener un bit que está en 1
        TEST_METHOD(TestGetBitSet)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b10100000;  // El bit en la posición 5 está a 1
            int position = 5;  // Queremos obtener el bit en la posición 5

            uint64_t result = board.getBit(initialBoard, position);

            // Esperamos que el resultado sea 1 << 5, ya que el bit 5 está a 1
            uint64_t expected = 1ULL << position;

            Assert::AreEqual(expected, result);
        }

        // Test: Obtener un bit que está en 0
        TEST_METHOD(TestGetBitUnset)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b10000000;  // El bit en la posición 5 está en 0
            int position = 5;  // Queremos obtener el bit en la posición 5

            uint64_t result = board.getBit(initialBoard, position);

            // Esperamos que el resultado sea 0, porque el bit 5 está a 0
            uint64_t expected = 0;

            Assert::AreEqual(expected, result);
        }

        // Test: Obtener un bit en una posición fuera de rango (por ejemplo, bit 63)
        TEST_METHOD(TestGetBitHighPosition)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b1000000000000000000000000000000000000000000000000000000000000000ULL;  // Bit 63 está a 1
            int position = 63;  // Queremos obtener el bit en la posición más alta (bit 63)

            uint64_t result = board.getBit(initialBoard, position);

            // Esperamos que el resultado sea 1 << 63, ya que el bit 63 está a 1
            uint64_t expected = 1ULL << position;

            Assert::AreEqual(expected, result);
        }

        // Test: Obtener un bit que no está establecido (por ejemplo, bit 0)
        TEST_METHOD(TestGetBitPosition0)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b1111111111111111111111111111111111111111111111111111111111111110ULL;  // Bit 0 está en 0
            int position = 0;  // Queremos obtener el bit en la posición 0

            uint64_t result = board.getBit(initialBoard, position);

            // Esperamos que el resultado sea 0, porque el bit 0 está a 0
            uint64_t expected = 0;

            Assert::AreEqual(expected, result);
        }

        // Test: Verificar que no se alteran otros bits
        TEST_METHOD(TestGetBitOtherBitsNotModified)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b1010101010101010101010101010101010101010101010101010101010101010ULL; // Algunos bits ya están establecidos
            int position = 7;  // Queremos obtener el bit en la posición 7

            uint64_t result = board.getBit(initialBoard, position);

            // Creamos el valor esperado con solo el bit 7 establecido en 1
            uint64_t expected = 1ULL << position;

            Assert::AreEqual(expected, result);
        }
        TEST_METHOD(TestGetBoardIndexFromMoveGeneratorWhite) 
        {
            Board b = new Board(true);
            b.setWhiteToMove(true);
            
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::PAWN), (int)Board::W_PAWN);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::BISHOP), (int)Board::W_BISHOP);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::KNIGHT), (int)Board::W_KNIGHT);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::TOWER), (int)Board::W_TOWER);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::QUEEN), (int)Board::W_QUEEN);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::KING), (int)Board::W_KING);
        }
        TEST_METHOD(TestGetBoardIndexFromMoveGeneratorBlack)
        {
            Board b = new Board(true);
            b.setWhiteToMove(false);

            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::PAWN), (int)Board::B_PAWN);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::BISHOP), (int)Board::B_BISHOP);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::KNIGHT), (int)Board::B_KNIGHT);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::TOWER), (int)Board::B_TOWER);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::QUEEN), (int)Board::B_QUEEN);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(MoveGenerator::KING), (int)Board::B_KING);
        }
        TEST_METHOD(TestGetBoardIndexFromMoveGeneratorInvalidInput)
        {
            Board b = new Board(true);
            b.setWhiteToMove(true);

            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(12), -1);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(100), -1);
            Assert::AreEqual(b.getBoardIndexFromMoveGenerator(-1), -1);
        }
        TEST_METHOD(TestSetBitOfBoard) {
            Board b = new Board(true);

            uint64_t expected_w_pawn = 1ULL << 35;
            uint64_t expected_b_pawn = 1ULL << 23;
            uint64_t expected_w_bishop = 1ULL << 12;
            uint64_t expected_b_bishop = 1ULL << 43;
            uint64_t expected_w_knight = 1ULL << 55;
            uint64_t expected_b_knight = 1ULL << 62;
            uint64_t expected_w_tower = 1ULL << 34;
            uint64_t expected_b_tower = 1ULL << 17;
            uint64_t expected_w_queen = 1ULL << 21;
            uint64_t expected_b_queen = 1ULL << 49;
            uint64_t expected_w_king = 1ULL << 56;
            uint64_t expected_b_king = 1ULL << 38;

            b.setBitOfBoard(Board::W_PAWN, 35);
            b.setBitOfBoard(Board::B_PAWN, 23);
            b.setBitOfBoard(Board::W_BISHOP, 12);
            b.setBitOfBoard(Board::B_BISHOP, 43);
            b.setBitOfBoard(Board::W_KNIGHT, 55);
            b.setBitOfBoard(Board::B_KNIGHT, 62);
            b.setBitOfBoard(Board::W_TOWER, 34);
            b.setBitOfBoard(Board::B_TOWER, 17);
            b.setBitOfBoard(Board::W_QUEEN, 21);
            b.setBitOfBoard(Board::B_QUEEN, 49);
            b.setBitOfBoard(Board::W_KING, 56);
            b.setBitOfBoard(Board::B_KING,38);

            Assert::AreEqual(expected_w_pawn, b.getBitboardFromType(Board::W_PAWN));
            Assert::AreEqual(expected_b_pawn, b.getBitboardFromType(Board::B_PAWN));
            Assert::AreEqual(expected_w_bishop, b.getBitboardFromType(Board::W_BISHOP));
            Assert::AreEqual(expected_b_bishop, b.getBitboardFromType(Board::B_BISHOP));
            Assert::AreEqual(expected_w_knight, b.getBitboardFromType(Board::W_KNIGHT));
            Assert::AreEqual(expected_b_knight, b.getBitboardFromType(Board::B_KNIGHT));
            Assert::AreEqual(expected_w_tower, b.getBitboardFromType(Board::W_TOWER));
            Assert::AreEqual(expected_b_tower, b.getBitboardFromType(Board::B_TOWER));
            Assert::AreEqual(expected_w_queen, b.getBitboardFromType(Board::W_QUEEN));
            Assert::AreEqual(expected_b_queen, b.getBitboardFromType(Board::B_QUEEN));
            Assert::AreEqual(expected_w_king, b.getBitboardFromType(Board::W_KING));
            Assert::AreEqual(expected_b_king, b.getBitboardFromType(Board::B_KING));
        }
        TEST_METHOD(TestGetBitFromBoard) {
            Board board = new Board(true);

            board.setBitOfBoard(Board::W_PAWN, 0);
            board.setBitOfBoard(Board::W_KNIGHT, 10);
            board.setBitOfBoard(Board::B_QUEEN, 63);

            Assert::AreEqual(board.getBitFromBoard(Board::W_PAWN, 0), 1);
            Assert::AreEqual(board.getBitFromBoard(Board::W_KNIGHT, 10), 1);
            Assert::AreEqual(board.getBitFromBoard(Board::B_QUEEN, 63), 1);
            Assert::AreEqual(board.getBitFromBoard(Board::B_QUEEN, 62), 0);
        }
        TEST_METHOD(TestClearBitOfBoard) {
            Board board = new Board(true);

            board.setBitOfBoard(Board::W_PAWN, 10);

            Assert::AreEqual(board.getBitFromBoard(Board::W_PAWN, 10), 1);

            board.clearBitOfBoard(Board::W_PAWN, 10);

            Assert::AreEqual(board.getBitFromBoard(Board::W_PAWN, 10), 0);
        }
        TEST_METHOD(TestMakeMoveSimpleMove) {
            Board board = new Board(false);
            board.setBitOfBoard(Board::W_KNIGHT, 1);

            Move m{ 1, 18, MoveGenerator::KNIGHT, -1 };

            board.makeMove(m);

            Assert::AreEqual(1, board.getBitFromBoard(Board::W_KNIGHT, 18));
            Assert::AreEqual(0, board.getBitFromBoard(Board::W_KNIGHT, 1));
        }
        TEST_METHOD(TestMakeMoveCapture) {
            Board board = new Board(false);
            board.setBitOfBoard(Board::W_BISHOP, 27);
            board.setBitOfBoard(Board::B_PAWN, 36);

            Move m{ 27, 36, MoveGenerator::BISHOP, -1 };

            board.makeMove(m);

            Assert::AreEqual(1, board.getBitFromBoard(Board::W_BISHOP, 36));
            Assert::AreEqual(0, board.getBitFromBoard(Board::W_BISHOP, 27));

            Assert::AreEqual(0, board.getBitFromBoard(Board::W_PAWN, 36));

        }
        TEST_METHOD(TestMakeMoveWhiteKingCastlingFlags) {
            Board board = new Board(false);

            board.setBitOfBoard(Board::W_KING, 4);
            Assert::IsTrue(board.getWhiteCastle());

            Move m{ 4, 5, MoveGenerator::KING, -1 };

            board.makeMove(m);
            Assert::IsFalse(board.getWhiteCastle());
        }
        TEST_METHOD(TestMakeMoveBlackKingCastlingFlags) {
            Board board = new Board(false);
            board.setWhiteToMove(false);

            board.setBitOfBoard(Board::B_KING, 60);
            Assert::IsTrue(board.getBlackCastle());

            Move m{ 60, 61, MoveGenerator::KING, -1 };

            board.makeMove(m);
            Assert::IsFalse(board.getBlackCastle());
        }
        TEST_METHOD(TestMakeMoveRightWhiteTowerCastlingFlags) {
            Board board = new Board(false);
            
            board.setBitOfBoard(Board::W_TOWER, 7);
            Assert::IsTrue(board.getRightWhiteCastle());

            Move m{ 7, 6, MoveGenerator::TOWER, -1 };

            board.makeMove(m);
            Assert::IsFalse(board.getRightWhiteCastle());
        }
        TEST_METHOD(TestMakeMoveLeftWhiteTowerCastlingFlags) {
            Board board = new Board(false);

            board.setBitOfBoard(Board::W_TOWER, 0);
            Assert::IsTrue(board.getLeftWhiteCastle());

            Move m{ 0, 1, MoveGenerator::TOWER, -1 };

            board.makeMove(m);
            Assert::IsFalse(board.getLeftWhiteCastle());
        }
        TEST_METHOD(TestMakeMoveRightBlackTowerCastlingFlags) {
            Board board = new Board(false);
            board.setWhiteToMove(false);

            board.setBitOfBoard(Board::B_TOWER, 63);
            Assert::IsTrue(board.getRightBlackCastle());

            Move m{ 63, 62, MoveGenerator::TOWER, -1 };

            board.makeMove(m);
            Assert::IsFalse(board.getRightBlackCastle());
        }
        TEST_METHOD(TestMakeMoveLeftBlackTowerCastlingFlags) {
            Board board = new Board(false);
            board.setWhiteToMove(false);

            board.setBitOfBoard(Board::B_TOWER, 56);
            Assert::IsTrue(board.getLeftBlackCastle());

            Move m{ 56, 57, MoveGenerator::TOWER, -1 };

            board.makeMove(m);
            Assert::IsFalse(board.getLeftBlackCastle());
        }
        TEST_METHOD(TestMakeMovePromotion) {
            Board board = new Board(false);
            
            board.setBitOfBoard(Board::W_PAWN, 51);
            board.setBitOfBoard(Board::B_PAWN, 11);

            Move w_move{51, 59, MoveGenerator::PAWN, MoveGenerator::QUEEN};
            board.makeMove(w_move);

            Assert::AreEqual(0, board.getBitFromBoard(Board::W_PAWN, 59));
            Assert::AreEqual(1, board.getBitFromBoard(Board::W_QUEEN, 59));

            Move b_move{ 11, 3, MoveGenerator::PAWN, MoveGenerator::QUEEN };
            board.makeMove(b_move);

            Assert::AreEqual(0, board.getBitFromBoard(Board::B_PAWN, 3));
            Assert::AreEqual(1, board.getBitFromBoard(Board::B_QUEEN, 3));
        }
        TEST_METHOD(TestMakeMoveEnPassant) {
            Board board = new Board(false);
            board.setWhiteToMove(false);

            // Pawn that makes en passant
            board.setBitOfBoard(Board::W_PAWN, 36);

            // Pawn to be captured
            board.setBitOfBoard(Board::B_PAWN, 51);

            // board.printBitboard(board.getOccupiedBitBoard());
            // std::cout << "-" << std::endl;

            board.makeMove({ 51, 35, MoveGenerator::PAWN });
            
            // board.printBitboard(board.getOccupiedBitBoard());
            // std::cout << "-" << std::endl;

            board.makeMove({ 36, 43, MoveGenerator::PAWN });

            // board.printBitboard(board.getOccupiedBitBoard());
            // std::cout << "-" << std::endl;

            Assert::IsTrue(0 == board.getBitFromBoard(Board::B_PAWN, 35));
            Assert::IsTrue(1 == board.getBitFromBoard(Board::W_PAWN, 43));

            board.clearBitOfBoard(Board::W_PAWN, 43);

            // With black pieces
            board.setWhiteToMove(true);

            // Pawn that makes en passant
            board.setBitOfBoard(Board::W_PAWN, 12);

            // Pawn to be captured
            board.setBitOfBoard(Board::B_PAWN, 27);

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            board.makeMove({ 12, 28, MoveGenerator::PAWN });

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            board.makeMove({ 27, 20, MoveGenerator::PAWN });

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            Assert::IsTrue(0 == board.getBitFromBoard(Board::W_PAWN, 28));
            Assert::IsTrue(1 == board.getBitFromBoard(Board::B_PAWN, 20));
        }
        TEST_METHOD(TestMakeMoveEnPassant2Step) {
            Board board = new Board(false);
            board.setWhiteToMove(false);

            // Pawn that makes en passant
            board.setBitOfBoard(Board::W_PAWN, 28);

            // Pawn to be captured
            board.setBitOfBoard(Board::B_PAWN, 51);

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            board.makeMove({ 51, 43, MoveGenerator::PAWN });

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            board.makeMove({ 28, 36, MoveGenerator::PAWN });

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            board.makeMove({ 43, 35, MoveGenerator::PAWN });

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            board.makeMove({ 36, 43, MoveGenerator::PAWN});

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            Assert::IsTrue(1 == board.getBitFromBoard(Board::W_PAWN, 43));
            Assert::IsTrue(1 == board.getBitFromBoard(Board::B_PAWN, 35));

            // With black pieces
            board.setWhiteToMove(true);

            board.clearBitOfBoard(Board::W_PAWN, 43);
            board.clearBitOfBoard(Board::B_PAWN, 35);

            board.setBitOfBoard(Board::W_PAWN, 11);
            board.setBitOfBoard(Board::B_PAWN, 36);

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            board.makeMove({ 11, 19, MoveGenerator::PAWN });

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            board.makeMove({ 36, 28, MoveGenerator::PAWN });

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            board.makeMove({ 19, 27, MoveGenerator::PAWN });

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            board.makeMove({ 28, 19, MoveGenerator::PAWN });

            //board.printBitboard(board.getOccupiedBitBoard());
            //std::cout << "-" << std::endl;

            Assert::IsTrue(1 == board.getBitFromBoard(Board::W_PAWN, 27));
            Assert::IsTrue(1 == board.getBitFromBoard(Board::B_PAWN, 19));
        }
        TEST_METHOD(TestIsVerticalPathClear) {
            Board board = new Board(false);
            Move move;
            MoveGenerator moveGen;

            // Prueba 1: Movimiento de arriba hacia abajo con una torre bloqueada en el camino
            // Colocamos una torre en a1 y una pieza bloqueadora en a5
            board.setBitOfBoard(Board::W_TOWER, 0);  // a1 = 0
            board.setBitOfBoard(Board::B_PAWN, 32);   // a5 = 32

            // Intentamos mover la torre de a1 a a8, lo que debería fallar debido al bloqueador en a5
            move.from = 0;
            move.to = 56;
            move.piece = MoveGenerator::TOWER;

            bool resultUpToDown = moveGen.isLegal(board, move, Board::WHITE);
            Assert::IsFalse(resultUpToDown); // Esperamos que el movimiento falle debido al bloqueador en a5

            board.clearBitOfBoard(Board::W_TOWER, 0);
            board.clearBitOfBoard(Board::B_PAWN, 32);

            // Prueba 2: Movimiento de abajo hacia arriba con una torre bloqueada en el camino
            // Colocamos una torre en a8 y una pieza bloqueadora en a5
            board.setBitOfBoard(Board::W_TOWER, 56);  // a8 = 56
            board.setBitOfBoard(Board::B_PAWN, 32);   // a5 = 32

            // Intentamos mover la torre de a8 a a1, lo que debería fallar debido al bloqueador en a5
            move.from = 56;
            move.to = 0;
            move.piece = MoveGenerator::TOWER;

            bool resultDownToUp = moveGen.isLegal(board, move, Board::WHITE);
            Assert::IsFalse(resultDownToUp); // Esperamos que el movimiento falle debido al bloqueador en a5


            // Ahora probamos con una reina en lugar de una torre, lo mismo se espera para ambos casos.

            // Prueba 3: Movimiento de arriba hacia abajo con una reina bloqueada en el camino
            // Colocamos una reina en a1 y una pieza bloqueadora en a5
            board.setBitOfBoard(Board::W_QUEEN, 0);  // a1 = 0
            board.setBitOfBoard(Board::B_PAWN, 32);   // a5 = 32

            // Intentamos mover la reina de a1 a a8, lo que debería fallar debido al bloqueador en a5
            move.from = 0;
            move.to = 56;
            move.piece = MoveGenerator::QUEEN;

            bool resultUpToDownQueen = moveGen.isLegal(board, move, Board::WHITE);
            Assert::IsFalse(resultUpToDownQueen); // Esperamos que el movimiento falle debido al bloqueador en a5

            // Prueba 4: Movimiento de abajo hacia arriba con una reina bloqueada en el camino
            // Colocamos una reina en a8 y una pieza bloqueadora en a5
            board.setBitOfBoard(Board::W_QUEEN, 56);  // a8 = 56
            board.setBitOfBoard(Board::B_PAWN, 32);   // a5 = 32

            // Intentamos mover la reina de a8 a a1, lo que debería fallar debido al bloqueador en a5
            move.from = 56;
            move.to = 0;
            move.piece = MoveGenerator::QUEEN;

            bool resultDownToUpQueen = moveGen.isLegal(board, move, Board::WHITE);
            Assert::IsFalse(resultDownToUpQueen); // Esperamos que el movimiento falle debido al bloqueador en a5
        }
        TEST_METHOD(TestIsHorizontalPathClear_LeftToRight_NoBlock){
            Board board(true); 
            MoveGenerator moveGen;
            Move m1 = { 0, 3, MoveGenerator::TOWER }; // Torre moviéndose de a1 a a4 (casillas 0 a 3)

            board.setBitOfBoard(Board::W_TOWER, 0);

            bool result = moveGen.isLegal(board, m1, Board::WHITE);
            Assert::IsTrue(result);

            // Vacía la casilla
            board.clearBitOfBoard(Board::W_TOWER, 0);

            Move m2 = { 0, 3, MoveGenerator::QUEEN }; 

            board.setBitOfBoard(Board::W_QUEEN, 0);

            result = moveGen.isLegal(board, m2, Board::WHITE);
            Assert::IsTrue(result);
        }
        TEST_METHOD(testIsLegal_HorizontalPathClear_LeftToRight_WithBlock) {
            Board board(false);
            MoveGenerator moveGen;
            Move m1 = { 0, 3, MoveGenerator::TOWER }; 

            board.setBitOfBoard(Board::W_TOWER, 0);
            board.setBitOfBoard(Board::B_PAWN, 2);
            
            bool result = moveGen.isLegal(board, m1, Board::WHITE);
            Assert::IsFalse(result);

            // Vacía la casilla
            board.clearBitOfBoard(Board::W_TOWER, 0);

            Move m2 = { 0, 3, MoveGenerator::QUEEN }; 

            board.setBitOfBoard(Board::W_QUEEN, 0);

            result = moveGen.isLegal(board, m2, Board::WHITE);
            Assert::IsFalse(result); 
        }
        TEST_METHOD(testIsLegal_HorizontalPathClear_RightToLeft_NoBlock) {
            Board board(true);
            MoveGenerator moveGen;
            Move m1 = { 3, 0, MoveGenerator::TOWER };

            board.setBitOfBoard(Board::W_TOWER, 3);

            bool result = moveGen.isLegal(board, m1, Board::WHITE);
            Assert::IsTrue(result);

            // Vacía la casilla
            board.clearBitOfBoard(Board::W_TOWER, 3);

            Move m2 = { 3, 0, MoveGenerator::QUEEN };

            board.setBitOfBoard(Board::W_QUEEN, 3);

            result = moveGen.isLegal(board, m2, Board::WHITE);
            Assert::IsTrue(result);
        }
        TEST_METHOD(testIsLegal_HorizontalPathClear_RightToLeft_WithBlock) {
            Board board(false);
            MoveGenerator moveGen;
            Move m1 = { 3, 0, MoveGenerator::TOWER };

            board.setBitOfBoard(Board::W_TOWER, 3);
            board.setBitOfBoard(Board::B_PAWN, 2);

            bool result = moveGen.isLegal(board, m1, Board::WHITE);
            Assert::IsFalse(result);

            // Vacía la casilla
            board.clearBitOfBoard(Board::W_TOWER, 3);

            Move m2 = { 3, 0, MoveGenerator::QUEEN };

            board.setBitOfBoard(Board::W_QUEEN, 3);

            result = moveGen.isLegal(board, m2, Board::WHITE);
            Assert::IsFalse(result);
        }
        TEST_METHOD(testIsLegal_DiagonalPathClear_NoBlock) {
            Board board(true);
            MoveGenerator moveGen;
            Move m1 = { 27, 63, MoveGenerator::BISHOP };
            Move m2 = { 27, 48, MoveGenerator::BISHOP };
            Move m3 = { 27, 0,  MoveGenerator::BISHOP };
            Move m4 = { 27, 6,  MoveGenerator::BISHOP };

            board.setBitOfBoard(Board::W_BISHOP, 27);

            Assert::IsTrue(moveGen.isLegal(board, m1, Board::WHITE));
            Assert::IsTrue(moveGen.isLegal(board, m2, Board::WHITE));
            Assert::IsTrue(moveGen.isLegal(board, m3, Board::WHITE));
            Assert::IsTrue(moveGen.isLegal(board, m4, Board::WHITE));
        }
        TEST_METHOD(testIsLegal_DiagonalPathClear_WithBlock) {
            Board board(false);
            MoveGenerator moveGen;
            Move m1 = { 27, 63, MoveGenerator::BISHOP };
            Move m2 = { 27, 48, MoveGenerator::BISHOP };
            Move m3 = { 27, 0,  MoveGenerator::BISHOP };
            Move m4 = { 27, 6,  MoveGenerator::BISHOP };

            board.setBitOfBoard(Board::W_BISHOP, 27);
            board.setBitOfBoard(Board::B_PAWN, 41);
            board.setBitOfBoard(Board::B_PAWN, 45);
            board.setBitOfBoard(Board::B_PAWN, 13);
            board.setBitOfBoard(Board::B_PAWN, 9);

            Assert::IsFalse(moveGen.isLegal(board, m1, Board::WHITE));
            Assert::IsFalse(moveGen.isLegal(board, m2, Board::WHITE));
            Assert::IsFalse(moveGen.isLegal(board, m3, Board::WHITE));
            Assert::IsFalse(moveGen.isLegal(board, m4, Board::WHITE));
        }
        TEST_METHOD(TestIsKingInCheck) {
            Board board(true);
            MoveGenerator moveGen;

            board.setBitOfBoard(Board::W_KING, 4);
            board.setBitOfBoard(Board::W_PAWN, 15);
            board.setBitOfBoard(Board::W_PAWN, 43);
            board.setBitOfBoard(Board::B_KING, 60);
            board.setBitOfBoard(Board::B_PAWN, 55);
            board.setBitOfBoard(Board::B_PAWN, 11);

            Move illegalWhite { 15, 23, MoveGenerator::PAWN };
            Move legalWhite { 4, 11, MoveGenerator::KING };
            Move followUpBlack { 55, 47, MoveGenerator::PAWN };
            Move whiteChecksBlack {43, 51, MoveGenerator::PAWN };

            Assert::IsFalse(moveGen.isLegal(board, illegalWhite, Board::WHITE));

            Assert::IsTrue(moveGen.isLegal(board, legalWhite, Board::WHITE));
            board.makeMove(legalWhite);

            Assert::IsTrue(moveGen.isLegal(board, followUpBlack, Board::BLACK));
            board.makeMove(followUpBlack);

            Assert::IsTrue(moveGen.isLegal(board, whiteChecksBlack, Board::WHITE));
            board.makeMove(whiteChecksBlack);

            Move illegalBlack { 47, 39, MoveGenerator::PAWN };
            Move legalBlack{ 60, 51, MoveGenerator::PAWN };

            Assert::IsFalse(moveGen.isLegal(board, illegalBlack, Board::BLACK));

            Assert::IsTrue(moveGen.isLegal(board, legalBlack, Board::BLACK));
        }
        TEST_METHOD(TestStalemate) {
            Board board(false);
            MoveGenerator moveGen;

            board.setBitOfBoard(Board::W_KING, 4);
            board.setBitOfBoard(Board::B_KING, 60);

            // Piezas que ahogan al rey blanco
            board.setBitOfBoard(Board::B_TOWER, 8);
            board.setBitOfBoard(Board::B_BISHOP, 12);

            uint64_t before = board.getOccupiedBitBoard();

            Move illegalWhite{4, 5, MoveGenerator::KING};

            std::vector<Move> moves = moveGen.generateMoves(board, Board::WHITE);

            for (const auto move : moves) {
                Assert::IsFalse(moveGen.isLegal(board, move, Board::WHITE));
            }
    
            board.setStalemate(true);

            board.makeMove(illegalWhite);

            uint64_t after = board.getOccupiedBitBoard();

            Assert::IsTrue(before == after);
        }
        TEST_METHOD(TestUnmakeMove) {
            Board board(false);

            board.printBitboard(board.getOccupiedBitBoard());
            std::cout<<"-------------"<< std::endl;

            board.makeMove({11, 19, MoveGenerator::PAWN});
            board.printBitboard(board.getOccupiedBitBoard());
            std::cout << "-------------" << std::endl;

            board.makeMove({52, 36, MoveGenerator::PAWN});
            board.printBitboard(board.getOccupiedBitBoard());
            std::cout << "-------------" << std::endl;

            board.unmakeMove();
            board.printBitboard(board.getOccupiedBitBoard());
            std::cout << "-------------" << std::endl;

            board.unmakeMove();
            board.printBitboard(board.getOccupiedBitBoard());
        }
	};

    TEST_CLASS(MoveGeneratorTest) 
    {
    public:
        TEST_METHOD(TestGeneratePawnMoves) 
        {
            const int WHITE = 0;
            const int BLACK = 1;
            MoveGenerator moveGen;

            uint64_t w_pawn = 1ULL << 11;
            uint64_t b_pawn = 1ULL << 51;
            Board b(w_pawn, 0, 0, 0, 0, 0, b_pawn, 0, 0, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);

            std::vector<Move> expectedWhiteMoves = {
                {11, 19, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {11, 27, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},   
            };

            std::vector<Move> expectedBlackMoves = {
                {51, 43, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {51, 35, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedWhiteMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedWhiteMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedBlackMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedBlackMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGeneratePawnMovesRightBounds) 
        {
            const int WHITE = 0;
            const int BLACK = 1;
            MoveGenerator moveGen;

            uint64_t w_pawn = 1ULL << 15;
            uint64_t b_pawn = 1ULL << 55;
            Board b(w_pawn, 0, 0, 0, 0, 0, b_pawn, 0, 0, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, BLACK);
            
            std::vector<Move> expectedWhiteMoves = {
                {15, 23, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {15, 31, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            std::vector<Move> expectedBlackMoves = {
                {55, 47, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {55, 39, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedWhiteMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedWhiteMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedBlackMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedBlackMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGeneratePawnMovesLeftBounds) 
        {
            const int WHITE = 0;
            const int BLACK = 1;
            MoveGenerator moveGen;

            uint64_t w_pawn = 1ULL << 8;
            uint64_t b_pawn = 1ULL << 48;
            Board b(w_pawn, 0, 0, 0, 0, 0, b_pawn, 0, 0, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, BLACK);
            
            std::vector<Move> expectedWhiteMoves = {
                {8, 16, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {8, 24, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            std::vector<Move> expectedBlackMoves = {
                {48, 40, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {48, 32, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedWhiteMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedWhiteMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedBlackMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedBlackMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGeneratePawnMovesStartingPos) 
        {
            const int WHITE = 0;
            const int BLACK = 1;
            MoveGenerator moveGen;

            uint64_t w_pawn = 1ULL << 18;
            uint64_t b_pawn = 1ULL << 42;
            Board b(w_pawn, 0, 0, 0, 0, 0, b_pawn, 0, 0, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, BLACK);
            
            std::vector<Move> expectedWhiteMoves = {
                {18, 26, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            std::vector<Move> expectedBlackMoves = {
                {42, 34, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedWhiteMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedWhiteMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedBlackMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedBlackMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateBishopMovesUpAndRight)
        {
            MoveGenerator moveGen;
            uint64_t w_bishop = 1ULL;
            uint64_t b_bishop = 1ULL;
            Board b(0, w_bishop, 0, 0, 0, 0, 0, b_bishop, 0, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);

            std::vector<Move> expectedMoves = {
                {0, 9, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {0, 18, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {0, 27, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {0, 36, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {0, 45, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {0, 54, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {0, 63, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateBishopMovesDownAndLeft) 
        {
            MoveGenerator moveGen;
            uint64_t w_bishop = 1ULL << 63;
            uint64_t b_bishop = 1ULL << 63;
            Board b(0, w_bishop, 0, 0, 0, 0, 0, b_bishop, 0, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);
            
            std::vector<Move> expectedMoves = {
                {63, 54, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {63, 45, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {63, 36, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {63, 27, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {63, 18, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {63, 9, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {63, 0, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateBishopMovesUpAndLeft) 
        {
            MoveGenerator moveGen;

            uint64_t w_bishop = 1ULL << 7;
            uint64_t b_bishop = 1ULL << 7;
            Board b(0, w_bishop, 0, 0, 0, 0, 0, b_bishop, 0, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);
            
            std::vector<Move> expectedMoves = {
                {7, 14, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {7, 21, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {7, 28, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {7, 35, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {7, 42, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {7, 49, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {7, 56, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateBishopMovesDownAndRight) 
        {
            MoveGenerator moveGen;

            uint64_t w_bishop = 1ULL << 56;
            uint64_t b_bishop = 1ULL << 56;
            Board b(0, w_bishop, 0, 0, 0, 0, 0, b_bishop, 0, 0, 0, 0);
            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::WHITE);
            
            std::vector<Move> expectedMoves = {
                {56, 49, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {56, 42, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {56, 35, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {56, 28, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {56, 21, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {56, 14, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
                {56, 7, MoveGenerator::BISHOP, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateKnightMoves) 
        {
            const int WHITE = 0;
            const int BLACK = 1;
            MoveGenerator moveGen;

            uint64_t w_knight = 1ULL << 27;
            uint64_t b_knight = w_knight;
            Board b(0, 0, w_knight, 0, 0, 0, 0, 0, b_knight, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, BLACK);

            std::vector<Move> expectedMoves = {
                {27, 44, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {27, 37, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {27, 42, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {27, 33, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {27, 17, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {27, 10, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {27, 21, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {27, 12, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateKnightMovesLeftBottomCornerBounds) 
        {
            MoveGenerator moveGen;

            //Left bottom corner
            uint64_t w_knight = 1ULL;
            uint64_t b_knight = w_knight;
            Board b(0, 0, w_knight, 0, 0, 0, 0, 0, b_knight, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);

            std::vector<Move> expectedMoves = {
                {0, 10, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {0, 17, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateKnightMovesRigthBottomCornerBounds)
        {
            MoveGenerator moveGen;

            //Right bottom corner
            uint64_t w_knight = 1ULL << 7;
            uint64_t b_knight = w_knight;
            Board b(0, 0, w_knight, 0, 0, 0, 0, 0, b_knight, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);
            
            std::vector<Move> expectedMoves = {
                {7, 22, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {7, 13, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateKnightMovesRightTopCornerBounds) 
        {
            MoveGenerator moveGen;
            //Right top corner
            uint64_t w_knight = 1ULL << 63;
            uint64_t b_knight = w_knight;
            Board b(0, 0, w_knight, 0, 0, 0, 0, 0, b_knight, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);
            
            std::vector<Move> expectedMoves = {
                {63, 46, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {63, 53, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateKnightMovesLeftTopCornerBounds) 
        {
            MoveGenerator moveGen;
            //Left top corner
            uint64_t w_knight = 1ULL << 56;
            uint64_t b_knight = w_knight;
            Board b(0, 0, w_knight, 0, 0, 0, 0, 0, b_knight, 0, 0, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);
            
            std::vector<Move> expectedMoves = {
                {56, 50, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
                {56, 41, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateTowerMoves) {
            MoveGenerator moveGen;
            
            uint64_t w_tower = 1ULL << 27;
            uint64_t b_tower = w_tower;
            Board b(0, 0, 0, w_tower, 0, 0, 0, 0, 0, b_tower, 0, 0);
            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);

            std::vector<Move> expectedMoves = {
                {27, 35, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, // Upward
                {27, 43, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, 
                {27, 51, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {27, 59, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {27, 19, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, // Downward
                {27, 11, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {27, 3,  MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {27, 28, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, // Right 
                {27, 29, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {27, 30, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {27, 31, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {27, 26, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, // Left
                {27, 25, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {27, 24, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateQueenMoves) {
            MoveGenerator moveGen;
            uint64_t w_queen = 1ULL << 27;
            uint64_t b_queen = 1ULL << 27;
            Board b(0, 0, 0, 0, 0, w_queen, 0, 0, 0, 0, 0, b_queen);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);

            std::vector<Move> expectedMoves = {
                {27, 35, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE}, // Upward
                {27, 43, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 51, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 59, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 19, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE}, // Downward
                {27, 11, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 3,  MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 28, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE}, // Right
                {27, 29, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 30, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 31, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 26, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE}, // Left
                {27, 25, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 24, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 36, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE}, // Up - right
                {27, 45, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 54, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 63, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 34, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE}, // Up - left
                {27, 41, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 48, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 18, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE}, // Down - right
                {27, 9,  MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 0,  MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 20, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE}, // Down - left
                {27, 13, MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                {27, 6,  MoveGenerator::QUEEN, MoveGenerator::NULL_TYPE},
                
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());
            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

        }
        TEST_METHOD(TestGenerateKingMoves) {
            MoveGenerator moveGen;

            uint64_t w_king = 1ULL << 27;
            uint64_t b_king = w_king;
            Board b(0, 0, 0, 0, w_king, 0, 0, 0, 0, 0, b_king, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);

            std::vector<Move> expectedMoves = {
                {27, 35, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Upward
                {27, 19, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Downward
                {27, 28, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Right
                {27, 26, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Left
                {27, 36, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Up - right
                {27, 34, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Up - left
                {27, 18, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Down - right
                {27, 20, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Down - left
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());

            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());

            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateKingMovesTopBounds) {
            MoveGenerator moveGen;

            uint64_t w_king = 1ULL << 59;
            uint64_t b_king = w_king;
            Board b(0, 0, 0, 0, w_king, 0, 0, 0, 0, 0, b_king, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);

            std::vector<Move> expectedMoves = {
                {59, 51, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Downward
                {59, 60, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Right
                {59, 58, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Left
                {59, 52, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Down - right
                {59, 50, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Down - left
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());

            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());

            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
               Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateKingMovesBottomBounds) {
            MoveGenerator moveGen;

            uint64_t w_king = 1ULL << 3;
            uint64_t b_king = w_king;
            Board b(0, 0, 0, 0, w_king, 0, 0, 0, 0, 0, b_king, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);

            std::vector<Move> expectedMoves = {
                {3, 11, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Upward
                {3, 4,  MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Right
                {3, 2,  MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Left
                {3, 12, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Up - right
                {3, 10, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Up - left
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());

            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());

            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateKingMovesRightBounds) {
            MoveGenerator moveGen;

            uint64_t w_king = 1ULL << 31;
            uint64_t b_king = w_king;
            Board b(0, 0, 0, 0, w_king, 0, 0, 0, 0, 0, b_king, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);

            std::vector<Move> expectedMoves = {
                {31, 39, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Upward
                {31, 23, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Downward
                {31, 30, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Left
                {31, 38, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Up - left
                {31, 22, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Down - left
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());

            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());

            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateKingMovesLeftBounds) {
            MoveGenerator moveGen;

            uint64_t w_king = 1ULL << 24;
            uint64_t b_king = w_king;
            Board b(0, 0, 0, 0, w_king, 0, 0, 0, 0, 0, b_king, 0);

            std::vector<Move> w_moves = moveGen.generateMoves(b, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, Board::BLACK);

            std::vector<Move> expectedMoves = {
                {24, 32, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Upward
                {24, 16, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Downward
                {24, 25, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Right
                {24, 33, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Up - right
                {24, 17, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // Down - right
            };

            Assert::AreEqual(expectedMoves.size(), w_moves.size());

            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }

            Assert::AreEqual(expectedMoves.size(), b_moves.size());

            for (const auto& expectedMove : expectedMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
        }
        TEST_METHOD(TestGenerateKingMovesCastling) {
            MoveGenerator moveGen;
            Board board(true);

            board.setBitOfBoard(Board::W_KING, 4);
            board.setBitOfBoard(Board::W_TOWER, 0);
            board.setBitOfBoard(Board::W_TOWER, 7);

            board.setBitOfBoard(Board::B_KING, 60);
            board.setBitOfBoard(Board::B_TOWER, 63);
            board.setBitOfBoard(Board::B_TOWER, 56);

            std::vector<Move> w_moves = moveGen.generateMoves(board, Board::WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(board, Board::BLACK);

            std::vector<Move> expectedWhiteMoves = {
                {4, 3, MoveGenerator::KING, MoveGenerator::NULL_TYPE},  // e1 → d1
                {4, 5, MoveGenerator::KING, MoveGenerator::NULL_TYPE},  // e1 → f1

                {4, 11, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // e1 → f2
                {4, 12, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // e1 → e2
                {4, 13, MoveGenerator::KING, MoveGenerator::NULL_TYPE}, // e1 → d2
                
                {4, 6, MoveGenerator::KING, MoveGenerator::NULL_TYPE},  // e1 → g1 (enroque corto)
                {4, 2, MoveGenerator::KING, MoveGenerator::NULL_TYPE},  // e1 → c1 (enroque largo)

                // Torre en a1 (0) - Movimientos horizontales
                { 0, 1, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE }, {0, 2, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {0, 3, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},

                // Torre en a1 (0) - Movimientos verticales
                {0, 8, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, {0, 16, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {0, 24, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, {0, 32, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {0, 40, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, {0, 48, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {0, 56, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},

                // Torre en h1 (7) - Movimientos horizontales
                {7, 6, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, {7, 5, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                
                // Torre en h1 (7) - Movimientos verticales
                {7, 15, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, {7, 23, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {7, 31, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, {7, 39, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {7, 47, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}, {7, 55, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                {7, 63, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE}
            };
            std::vector<Move> expectedBlackMoves = {
                {60, 59, MoveGenerator::KING, MoveGenerator::NULL_TYPE},  // e8 → d8
                {60, 61, MoveGenerator::KING, MoveGenerator::NULL_TYPE},  // e8 → f8

                { 60, 52, MoveGenerator::KING, MoveGenerator::NULL_TYPE }, // e8 → e7
                { 60, 53, MoveGenerator::KING, MoveGenerator::NULL_TYPE }, // e8 → f7
                { 60, 51, MoveGenerator::KING, MoveGenerator::NULL_TYPE }, // e8 → d7

                {60, 62, MoveGenerator::KING, MoveGenerator::NULL_TYPE},  // e8 → g8 (enroque corto)
                {60, 58, MoveGenerator::KING, MoveGenerator::NULL_TYPE},  // e8 → c8 (enroque largo)

                // Torre en a8 (56) - Movimientos horizontales
                { 56, 57, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE }, { 56, 58, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE},
                { 56, 59, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE },

                // Torre en a8 (56) - Movimientos verticales
                { 56, 48, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE }, { 56, 40, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE },
                { 56, 32, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE }, { 56, 24, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE },
                { 56, 16, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE }, { 56, 8, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE },
                { 56, 0, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE },

                // Torre en h8 (63) - Movimientos horizontales
                { 63, 62, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE }, { 63, 61, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE },
            
                // Torre en h8 (63) - Movimientos verticales
                { 63, 55, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE }, { 63, 47, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE },
                { 63, 39, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE }, { 63, 31, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE },
                { 63, 23, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE }, { 63, 15, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE },
                { 63, 7, MoveGenerator::TOWER, MoveGenerator::NULL_TYPE }
            };

            Assert::AreEqual(expectedWhiteMoves.size(), w_moves.size());

            for (const auto& expectedMove : expectedWhiteMoves) {
                bool found = std::find(w_moves.begin(), w_moves.end(), expectedMove) != w_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
            
            Assert::AreEqual(expectedBlackMoves.size(), b_moves.size());
            /*
            for (const auto& expectedMove : expectedBlackMoves) {
                bool found = std::find(b_moves.begin(), b_moves.end(), expectedMove) != b_moves.end();
                Assert::IsTrue(found, L"Expected move not found");
            }
            */
        }
        TEST_METHOD(TestFilterMoves) {
            MoveGenerator moveGen;
            Board board(false);

            std::vector<Move> expectedWhiteMoves = {
                // Peones avanzando una casilla
                {8, 16, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},  // Peón en a2 a a3
                {9, 17, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},  // Peón en b2 a b3
                {10, 18, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en c2 a c3
                {11, 19, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en d2 a d3
                {12, 20, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en e2 a e3
                {13, 21, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en f2 a f3
                {14, 22, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en g2 a g3
                {15, 23, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en h2 a h3

                // Peones avanzando dos casillas (primer movimiento)
                {8, 24, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},  // Peón en a2 a a4
                {9, 25, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},  // Peón en b2 a b4
                {10, 26, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en c2 a c4
                {11, 27, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en d2 a d4
                {12, 28, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en e2 a e4
                {13, 29, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en f2 a f4
                {14, 30, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en g2 a g4
                {15, 31, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en h2 a h4

                // Movimientos de los caballos
                {1, 16, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE}, // Caballo b1 a a3
                {1, 18, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE}, // Caballo b1 a c3
                {6, 21, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE}, // Caballo g1 a f3
                {6, 23, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE}  // Caballo g1 a h3
            };

            std::vector<Move> expectedBlackMoves = {
                // Peones avanzando una casilla
                {48, 40, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en a7 a a6
                {49, 41, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en b7 a b6
                {50, 42, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en c7 a c6
                {51, 43, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en d7 a d6
                {52, 44, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en e7 a e6
                {53, 45, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en f7 a f6
                {54, 46, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en g7 a g6
                {55, 47, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en h7 a h6

                // Peones avanzando dos casillas (primer movimiento)
                {48, 32, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en a7 a a5
                {49, 33, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en b7 a b5
                {50, 34, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en c7 a c5
                {51, 35, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en d7 a d5
                {52, 36, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en e7 a e5
                {53, 37, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en f7 a f5
                {54, 38, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en g7 a g5
                {55, 39, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE}, // Peón en h7 a h5

                // Movimientos de los caballos
                {57, 42, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE}, // Caballo b8 a a6
                {57, 44, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE}, // Caballo b8 a c6
                {62, 47, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE}, // Caballo g8 a f6
                {62, 45, MoveGenerator::KNIGHT, MoveGenerator::NULL_TYPE}  // Caballo g8 a h6
            };

            std::vector<Move> w_moves = moveGen.generateMoves(board, Board::WHITE);
            moveGen.filterMoves(board, w_moves, Board::WHITE);

            Assert::AreEqual(expectedWhiteMoves.size(), w_moves.size());

            board.makeMove({8, 16, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE});

            std::vector<Move> b_moves = moveGen.generateMoves(board, Board::BLACK);
            moveGen.filterMoves(board, b_moves, Board::BLACK);

            Assert::AreEqual(expectedBlackMoves.size(), b_moves.size());
        }
    };

    TEST_CLASS(EvaluatorTest) {
        TEST_METHOD(TestEvaluate) {
            Board board(false);
            Assert::IsTrue(0 == Evaluator::evaluate(board));
        }
        TEST_METHOD(TestEvaluate_2) {
            Board board(true);

            board.setBitOfBoard(Board::W_PAWN, 8);
            board.setBitOfBoard(Board::W_PAWN, 9);
            board.setBitOfBoard(Board::W_PAWN, 10);
            board.setBitOfBoard(Board::W_PAWN, 11);
            board.setBitOfBoard(Board::W_PAWN, 12);
            board.setBitOfBoard(Board::W_PAWN, 13);
            board.setBitOfBoard(Board::W_PAWN, 14);
            board.setBitOfBoard(Board::W_PAWN, 15);
            board.setBitOfBoard(Board::W_BISHOP, 2);
            board.setBitOfBoard(Board::W_BISHOP, 5);
            board.setBitOfBoard(Board::W_TOWER, 0);
            board.setBitOfBoard(Board::W_TOWER, 7);
            board.setBitOfBoard(Board::W_KNIGHT, 1);
            board.setBitOfBoard(Board::W_KNIGHT, 6);
            board.setBitOfBoard(Board::W_QUEEN, 3);
            board.setBitOfBoard(Board::W_KING, 4);

            Assert::IsTrue(4000 == Evaluator::evaluate(board));
        }
        TEST_METHOD(TestEvaluate_3) {
            Board board(true);

            board.setBitOfBoard(Board::B_PAWN, 8);
            board.setBitOfBoard(Board::B_PAWN, 9);
            board.setBitOfBoard(Board::B_PAWN, 10);
            board.setBitOfBoard(Board::B_PAWN, 11);
            board.setBitOfBoard(Board::B_PAWN, 12);
            board.setBitOfBoard(Board::B_PAWN, 13);
            board.setBitOfBoard(Board::B_PAWN, 14);
            board.setBitOfBoard(Board::B_PAWN, 15);
            board.setBitOfBoard(Board::B_BISHOP, 2);
            board.setBitOfBoard(Board::B_BISHOP, 5);
            board.setBitOfBoard(Board::B_TOWER, 0);
            board.setBitOfBoard(Board::B_TOWER, 7);
            board.setBitOfBoard(Board::B_KNIGHT, 1);
            board.setBitOfBoard(Board::B_KNIGHT, 6);
            board.setBitOfBoard(Board::B_QUEEN, 3);
            board.setBitOfBoard(Board::B_KING, 4);

            Assert::IsTrue(-4000 == Evaluator::evaluate(board));
        }
    };
}
