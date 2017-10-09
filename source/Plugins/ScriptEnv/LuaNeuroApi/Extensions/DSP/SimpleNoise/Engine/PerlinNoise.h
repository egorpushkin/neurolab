#pragma once

namespace PerlinNoise
{
	float NoisingStep(float persistence, int octaves, float zoom, int x, int y);
	void Generate(unsigned int * pData, float persistence, int octaves, unsigned int width, unsigned int height, float red, float green, float blue, int seed, 
		float zoom);
	void GenerateNormalized(unsigned int * pData, float persistence, int octaves, unsigned int width, unsigned int height, float red, float green, float blue, 
		int seed, float zoom);

	float Noise(int x, int y);
	float SmoothNoise(int x, int y);
	float Interpolate(float a, float b, float x);
	float InterpolatedNoise(float x, float y);

	extern int seed;
}