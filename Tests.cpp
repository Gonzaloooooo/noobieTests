#include "pch.h"
#include "CppUnitTest.h"
#include "../Noobie/Board.h"
#include "../Noobie/MoveGenerator.h"

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

            std::vector<Move> w_moves = moveGen.generateMoves(b, WHITE);
            std::vector<Move> b_moves = moveGen.generateMoves(b, BLACK);

            std::vector<Move> expectedWhiteMoves = {
                {11, 19, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {11, 27, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},                                
                {11, 20, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {11, 18, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            std::vector<Move> expectedBlackMoves = {
                {51, 43, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {51, 35, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {51, 42, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {51, 44, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
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
                {15, 22, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            std::vector<Move> expectedBlackMoves = {
                {55, 47, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {55, 39, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {55, 46, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
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
                {8, 17, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            std::vector<Move> expectedBlackMoves = {
                {48, 40, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {48, 32, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {48, 41, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
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
                {18, 25, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {18, 27, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
            };

            std::vector<Move> expectedBlackMoves = {
                {42, 34, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {42, 33, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
                {42, 35, MoveGenerator::PAWN, MoveGenerator::NULL_TYPE},
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
    };
}
