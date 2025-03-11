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
        // Test: Comprobar que se establece correctamente el bit en la posici�n deseada
        TEST_METHOD(TestSetBit) 
        {
            Board board = Board(false);
            uint64_t initialBoard = 0;  // Inicialmente todos los bits son 0
            int position = 5;           // Queremos establecer el bit en la posici�n 5

            uint64_t result = board.setBit(initialBoard, position);

            // Esperamos que el bit en la posici�n 5 se haya establecido a 1
            uint64_t expected = 1ULL << position;

            // Comprobamos si el resultado es el esperado
            Assert::AreEqual(expected, result);
        }

        // Test: Verificar que el bit ya establecido no cambia
        TEST_METHOD(TestSetBitAlreadySet)
        {
            Board board = Board(false);
            uint64_t initialBoard = 1ULL << 5;  // El bit en la posici�n 5 ya est� establecido
            int position = 5;                    // Queremos establecer el bit en la posici�n 5

            uint64_t result = board.setBit(initialBoard, position);

            // El valor del tablero no deber�a cambiar, ya que el bit ya estaba establecido
            Assert::AreEqual(initialBoard, result);
        }

        // Test: Comprobar que se puede establecer un bit en una posici�n alta
        TEST_METHOD(TestSetBitHighPosition)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0;   // Inicialmente todos los bits son 0
            int position = 63;            // Establecemos el bit en la posici�n m�s alta (bit 63)

            uint64_t result = board.setBit(initialBoard, position);

            // Comprobamos si el bit en la posici�n 63 se ha establecido
            uint64_t expected = 1ULL << position;

            Assert::AreEqual(expected, result);
        }

        // Test: Verificar que no modifica bits que no est�n en la posici�n deseada
        TEST_METHOD(TestSetBitOtherBitsNotModified)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b1010101010101010101010101010101010101010101010101010101010101010ULL;
            int position = 7; // Establecemos el bit en la posici�n 7

            uint64_t result = board.setBit(initialBoard, position);

            // Creamos el valor esperado con solo el bit 7 establecido en 1
            uint64_t expected = initialBoard | (1ULL << position);

            Assert::AreEqual(expected, result);
        }

        // Test: Obtener un bit que est� en 1
        TEST_METHOD(TestGetBitSet)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b10100000;  // El bit en la posici�n 5 est� a 1
            int position = 5;  // Queremos obtener el bit en la posici�n 5

            uint64_t result = board.getBit(initialBoard, position);

            // Esperamos que el resultado sea 1 << 5, ya que el bit 5 est� a 1
            uint64_t expected = 1ULL << position;

            Assert::AreEqual(expected, result);
        }

        // Test: Obtener un bit que est� en 0
        TEST_METHOD(TestGetBitUnset)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b10000000;  // El bit en la posici�n 5 est� en 0
            int position = 5;  // Queremos obtener el bit en la posici�n 5

            uint64_t result = board.getBit(initialBoard, position);

            // Esperamos que el resultado sea 0, porque el bit 5 est� a 0
            uint64_t expected = 0;

            Assert::AreEqual(expected, result);
        }

        // Test: Obtener un bit en una posici�n fuera de rango (por ejemplo, bit 63)
        TEST_METHOD(TestGetBitHighPosition)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b1000000000000000000000000000000000000000000000000000000000000000ULL;  // Bit 63 est� a 1
            int position = 63;  // Queremos obtener el bit en la posici�n m�s alta (bit 63)

            uint64_t result = board.getBit(initialBoard, position);

            // Esperamos que el resultado sea 1 << 63, ya que el bit 63 est� a 1
            uint64_t expected = 1ULL << position;

            Assert::AreEqual(expected, result);
        }

        // Test: Obtener un bit que no est� establecido (por ejemplo, bit 0)
        TEST_METHOD(TestGetBitPosition0)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b1111111111111111111111111111111111111111111111111111111111111110ULL;  // Bit 0 est� en 0
            int position = 0;  // Queremos obtener el bit en la posici�n 0

            uint64_t result = board.getBit(initialBoard, position);

            // Esperamos que el resultado sea 0, porque el bit 0 est� a 0
            uint64_t expected = 0;

            Assert::AreEqual(expected, result);
        }

        // Test: Verificar que no se alteran otros bits
        TEST_METHOD(TestGetBitOtherBitsNotModified)
        {
            Board board = new Board(false);
            uint64_t initialBoard = 0b1010101010101010101010101010101010101010101010101010101010101010ULL; // Algunos bits ya est�n establecidos
            int position = 7;  // Queremos obtener el bit en la posici�n 7

            uint64_t result = board.getBit(initialBoard, position);

            // Creamos el valor esperado con solo el bit 7 establecido en 1
            uint64_t expected = 1ULL << position;

            Assert::AreEqual(expected, result);
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
            /*
            for (int i = 0; i < w_moves.size(); i++) {
                Move m = w_moves.at(i);
                std::string cadena = "From: " + std::to_string(m.from) + " | To: " + std::to_string(m.to);
                std::cout << cadena << std::endl;
            }
            for (int i = 0; i < b_moves.size(); i++) {
                Move m = b_moves.at(i);
                std::string cadena = "From: " + std::to_string(m.from) + " | To: " + std::to_string(m.to);
                std::cout << cadena << std::endl;
            }
            */
            Assert::AreEqual(4, (int)w_moves.size());
            Assert::AreEqual(4, (int)b_moves.size());
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
            /*
            for (int i = 0; i < w_moves.size(); i++) {
                Move m = w_moves.at(i);
                std::string cadena = "From: " + std::to_string(m.from) + " | To: " + std::to_string(m.to);
                std::cout << cadena << std::endl;
            }
            
            for (int i = 0; i < b_moves.size(); i++) {
                Move m = b_moves.at(i);
                std::string cadena = "From: " + std::to_string(m.from) + " | To: " + std::to_string(m.to);
                std::cout << cadena << std::endl;
            }
            */
            Assert::AreEqual(3, (int)w_moves.size());
            Assert::AreEqual(3, (int)b_moves.size());
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
            /*
            for (int i = 0; i < w_moves.size(); i++) {
                Move m = w_moves.at(i);
                std::string cadena = "From: " + std::to_string(m.from) + " | To: " + std::to_string(m.to);
                std::cout << cadena << std::endl;
            }
            for (int i = 0; i < b_moves.size(); i++) {
                Move m = b_moves.at(i);
                std::string cadena = "From: " + std::to_string(m.from) + " | To: " + std::to_string(m.to);
                std::cout << cadena << std::endl;
            }
            */
            Assert::AreEqual(3, (int)w_moves.size());
            Assert::AreEqual(3, (int)b_moves.size());
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
            /*
            for (int i = 0; i < w_moves.size(); i++) {
                Move m = w_moves.at(i);
                std::string cadena = "From: " + std::to_string(m.from) + " | To: " + std::to_string(m.to);
                std::cout << cadena << std::endl;
            }
            for (int i = 0; i < b_moves.size(); i++) {
                Move m = b_moves.at(i);
                std::string cadena = "From: " + std::to_string(m.from) + " | To: " + std::to_string(m.to);
                std::cout << cadena << std::endl;
            }
            */
            Assert::AreEqual(3, (int)w_moves.size());
            Assert::AreEqual(3, (int)b_moves.size());
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

            // Expected moves: All horizontal and vertical moves from d4
            std::vector<Move> expectedMoves = {
                {27, 35, -1}, {27, 43, -1}, {27, 51, -1}, {27, 59, -1},  // Upward
                {27, 19, -1}, {27, 11, -1}, {27, 3, -1},  // Downward
                {27, 28, -1}, {27, 29, -1}, {27, 30, -1}, {27, 31, -1},   // Right
                {27, 26, -1}, {27, 25, -1}, {27, 24, -1},  // Left
            };

            // Check if the generated moves match expected moves
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
                {27, 35, -1},  // Upward
                {27, 19, -1}, // Downward
                {27, 28, -1}, // Right
                {27, 26, -1}, // Left
                {27, 36, -1}, // Up - right
                {27, 34, -1}, // Up - left
                {27, 18, -1}, // Down - right
                {27, 20, -1}, // Down - left
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
                {59, 51, -1}, // Downward
                {59, 60, -1}, // Right
                {59, 58, -1}, // Left
                {59, 52, -1}, // Down - right
                {59, 50, -1}, // Down - left
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
                {3, 11, -1}, // Upward
                {3, 4, -1}, // Right
                {3, 2, -1}, // Left
                {3, 12, -1}, // Up - right
                {3, 10, -1}, // Up - left
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
                {31, 39, -1}, // Upward
                {31, 23, -1}, // Downward
                {31, 30, -1}, // Left
                {31, 38, -1}, // Up - left
                {31, 22, -1}, // Down - left
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
                {24, 32, -1}, // Upward
                {24, 16, -1}, // Downward
                {24, 25, -1}, // Right
                {24, 33, -1}, // Up - right
                {24, 17, -1}, // Down - right
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
