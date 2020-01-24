#include "DetectCollision.h"
#include <SFML/Graphics.hpp>
using namespace sf;

inline IntRect FToIRect(const FloatRect& f) {
	return IntRect((int)f.left, (int)f.top, (int)f.width, (int)f.height);
}


bool PixelPerfectCollision(const Sprite& a, const Sprite& b, const Image& imgA, const Image& imgB) {
	IntRect boundsA(FToIRect(a.getGlobalBounds()));
	IntRect boundsB(FToIRect(b.getGlobalBounds()));
	IntRect intersection;

	if (boundsA.intersects(boundsB, intersection)) {
		const Transform& inverseA(a.getInverseTransform());
		const Transform& inverseB(b.getInverseTransform());

		const Vector2u& sizeA(imgA.getSize());
		const Vector2u& sizeB(imgB.getSize());

		const Uint8* pixA = imgA.getPixelsPtr();
		const Uint8* pixB = imgB.getPixelsPtr();

		Vector2f vecA, vecB;
		int xMax = intersection.left + intersection.width;
		int yMax = intersection.top + intersection.height;

		for (int x = intersection.left; x < xMax; x++)
			for (int y = intersection.top; y < yMax; y++) {
				vecA = inverseA.transformPoint((float)x, (float)y);
				vecB = inverseB.transformPoint((float)x, (float)y);

				int idxA = ((int)vecA.x + ((int)vecA.y)*sizeA.x) * 4 + 3;
				int idxB = ((int)vecB.x + ((int)vecB.y)*sizeB.x) * 4 + 3;

				if (vecA.x > 0 && vecA.y > 0 &&
					vecB.x > 0 && vecB.y > 0 &&
					vecA.x < sizeA.x && vecA.y < sizeA.y &&
					vecB.x < sizeB.x && vecB.y < sizeB.y &&
					pixA[idxA] > 0 &&
					pixB[idxB] > 0) {
					return true;
				}
			}
	}

	return false;
}