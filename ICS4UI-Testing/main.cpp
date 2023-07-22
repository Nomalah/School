#include <array>
#include <iomanip>
#include <iostream>

typedef unsigned long long u64;

std::string convert(u64 bitBoard) {
	std::string result;
	u64 cmp = 1ULL << 63;
	for (std::size_t y = 8; y > 0; y--) {
		for (std::size_t x = 8; x > 0; x--) {
			result += bitBoard & cmp ? '1' : '0';
			cmp >>= 1;
		}
		result += '\n';
	}
	return result;
}
constexpr u64 full = 0xFFFFFFFFFFFFFFFFULL;

enum attackRayDirection {
	north = 0,
	northEast = 1,
	east = 2,
	southEast = 3,
	south = 4,
	southWest = 5,
	west = 6,
	northWest = 7
};

// constexpr testing
constexpr std::array<std::array<u64, 64>, 8> generateAttackRays() {
	std::array<std::array<u64, 64>, 8> resultRays{};
	constexpr u64 horizontal = 0xFFULL;
	constexpr u64 vertical = 0x0101010101010101ULL;
	constexpr u64 diagonal = 0x0102040810204080ULL;
	constexpr u64 antiDiagonal = 0x8040201008040201ULL;
	for (std::size_t d = attackRayDirection::north; d <= attackRayDirection::northWest; d++) {
		for (std::size_t y = 0; y < 8; y++) {
			for (std::size_t x = 0; x < 8; x++) {
				switch (d) {
					case attackRayDirection::north:	 // North
						resultRays[d][y * 8 + x] = ((vertical << x) ^ (1ULL << (y * 8 + x))) & (full << (y * 8));
						break;
					case attackRayDirection::south:	 // South
						resultRays[d][y * 8 + x] = ((vertical << x) ^ (1ULL << (y * 8 + x))) & ~(full << (y * 8));
						break;
					case attackRayDirection::east:	 // East
						resultRays[d][y * 8 + x] = ((horizontal << y * 8) ^ (1ULL << (y * 8 + x))) & ~(full << (y * 8 + x));
						break;
					case attackRayDirection::west:	 // West
						resultRays[d][y * 8 + x] = ((horizontal << y * 8) ^ (1ULL << (y * 8 + x))) & (full << (y * 8 + x));
						break;
					case attackRayDirection::northEast:	 // NorthEast
						resultRays[d][y * 8 + x] = ((x + y > 6 ? diagonal << (8 * (x + y - 7)) : diagonal >> (8 * (7 - x - y))) ^ (1ULL << (y * 8 + x))) & (full << (y * 8));
						break;
					case attackRayDirection::southWest:	 // SouthWest
						resultRays[d][y * 8 + x] = ((x + y > 6 ? diagonal << (8 * (x + y - 7)) : diagonal >> (8 * (7 - x - y))) ^ (1ULL << (y * 8 + x))) & ~(full << (y * 8));
						break;
					case attackRayDirection::southEast:	 // SouthEast
						resultRays[d][y * 8 + x] = ((y > x ? antiDiagonal << (8 * (y - x)) : antiDiagonal >> (8 * (x - y))) ^ (1ULL << (y * 8 + x))) & ~(full << (y * 8 + x));
						break;
					case attackRayDirection::northWest:	 // NorthWest
						resultRays[d][y * 8 + x] = ((y > x ? antiDiagonal << (8 * (y - x)) : antiDiagonal >> (8 * (x - y))) ^ (1ULL << (y * 8 + x))) & (full << (y * 8 + x));
						break;
				}
			}
		}
	}
	return resultRays;
}
constexpr std::array<std::array<u64, 64>, 8> attackRays = generateAttackRays();

int main() {
	for (int i = 0; i < 64; i++) {
		std::cout << convert(attackRays[0][i] | attackRays[1][i] | attackRays[2][i] | attackRays[3][i] | attackRays[4][i] | attackRays[5][i] | attackRays[6][i] | attackRays[7][i]) << std::endl;
	}
	std::cout << convert(0x0102040810204080ULL) << std::endl;
	std::cout << convert(0x8040201008040201ULL) << std::endl;

	for (int i = 0; i < 64; i++) {
	}
	/*int p = 0;
	for (std::array<u64, 64> x : perpendicularRays) {
        if(p == 0)
		for (u64 y : x) {
			std::cout << convert(y) << std::endl;
		}
	}*/
}