#include "StdAfx.h"

#include <cmath>
#include "PerlinNoise.h"

namespace PerlinNoise
{

	float Noise(int x, int y)
	{
		int n = x + y * 57 + seed;
		n = (n << 13) ^ n;
		return (float) (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
		//return value is always in range [-1.0, 1.0]
	}

	float SmoothNoise(int x, int y)
	{
		float corners = (Noise(x-1, y-1) + Noise(x+1, y-1) + Noise(x-1, y+1) + Noise(x+1, y+1)) / 16;
		float sides   = (Noise(x-1, y) + Noise(x+1, y) + Noise(x, y-1) + Noise(x, y+1)) / 8;
		float center  =  Noise(x, y ) / 4;
		return corners + sides + center;
	}

	float Interpolate(float a, float b, float x)
	{
		float ft = x * 3.1415927f;
		float f = (1 - std::cos(ft)) * .5f;

		return  a*(1-f) + b*f;
	}

	float InterpolatedNoise(float x, float y)
	{
		int wholePartX = (int) x;
		float fractionPartX = x - wholePartX;

		int wholePartY = (int) y;
		float fractionPartY = y - wholePartY;

		float v1 = SmoothNoise(wholePartX, wholePartY);
		float v2 = SmoothNoise(wholePartX + 1, wholePartY);
		float v3 = SmoothNoise(wholePartX, wholePartY + 1);
		float v4 = SmoothNoise(wholePartX + 1, wholePartY + 1);

		float i1 = Interpolate(v1, v2, fractionPartX);
		float i2 = Interpolate(v3, v4, fractionPartX);

		return Interpolate(i1, i2, fractionPartY);
	}

	float NoisingStep(float persistence, int octaves, float zoom, int x, int y)
	{	
		//PerlinNoise::seed = seed;

		float total = 0;
		float frequency = 1;
		float amplitude = 1;

		for (int i = 0; i < octaves; ++i)
		{
			total = total + InterpolatedNoise(x * frequency / zoom, y * frequency / zoom) * amplitude;
			frequency *= 2;
			amplitude *= persistence;
		}

		return total;
	}

	void Generate(unsigned int * pData, float persistence, int octaves, unsigned int width, unsigned int height, float red, float green, float blue, 
							int seed, float zoom)
	{	
		PerlinNoise::seed = seed;

		for (unsigned int y = 0; y < height; ++y)
		{
			for (unsigned int x = 0; x < width; ++x)
			{
				float total = 0;
				float frequency = 1;
				float amplitude = 1;

				for (int i = 0; i < octaves; ++i)
				{
					total = total + InterpolatedNoise(x * frequency / zoom, y * frequency / zoom) * amplitude;
					frequency *= 2;
					amplitude *= persistence;
				}

				pData[y * width + x] = (255 << 24) | ((unsigned char) (red * (total + 1) * 127.5) << 16) | ((unsigned char) (green * (total + 1) * 127.5) << 8) | 
					(unsigned char) (blue * (total + 1) * 127.5);
			}
		}
	}

	void GenerateNormalized(unsigned int * pData, float persistence, int octaves, unsigned int width, unsigned int height, float red, float green, 
										float blue, int seed, float zoom)
	{	
		PerlinNoise::seed = seed;

		float min = 0;
		float max = 0;
		float maxColorMultiplier;
		float * pDataFloat = new float[width * height];

		//Generate raw float data
		for (unsigned int y = 0; y < height; ++y)
		{
			for (unsigned int x = 0; x < width; ++x)
			{
				float total = 0;
				float frequency = 1;
				float amplitude = 1;

				for (int i = 0; i < octaves; ++i)
				{
					total = total + InterpolatedNoise(x * frequency / zoom, y * frequency / zoom) * amplitude;
					frequency *= 2;
					amplitude *= persistence;
				}

				pDataFloat[y * width + x] = total;

				min = total < min ? total : min;
				max = total > max ? total : max;
			}
		}

		//Normalize color multipliers
		maxColorMultiplier = red > green ? red : green;
		maxColorMultiplier = blue > maxColorMultiplier ? blue : maxColorMultiplier;
		red /= maxColorMultiplier;
		green /= maxColorMultiplier;
		blue /= maxColorMultiplier;

		//Normalize raw floats, factor in color multipliers, and convert to bitmap color format
		for (unsigned int i = 0; i < width * height; ++i)
		{
				pData[i] = (255 << 24) | ((unsigned char) (red * ((pDataFloat[i] - min) / (max - min)) * 255) << 16) | 
					((unsigned char) (green * ((pDataFloat[i] - min) / (max - min)) * 255) << 8) | (unsigned char) (blue * ((pDataFloat[i] - min) / (max - min)) * 255);
		}

		delete [] pDataFloat;
	}

	int seed = 0;

}