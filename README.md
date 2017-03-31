# 3D Terrain Generator

## Abstract
This is a C++ implementation of a 3D Terrain Generator using Perlin Simplex
Noise. The resulting terrain is based on a height map and a moisture map. Using 
the two metrics, a biomes table can be defined.

The scope of this repository is only to generate the terrain, not to display it 
nor use it in an actual program like a game. Future updates may include a way to
visualize the terrain and other metrics for more biome diversification.

## Overview

### Terrain
This class encapsulates the whole system. The main functionalities that 
implements are the following:
  - Load a region of `nchunks` starting at a given `x` and `y`. If the chunks 
  are generated or simply loaded from disk must be transparent.
  - Unload a chunk given a set of coordinates (TODO)
  - Unload all chunks
  - Provide a vertex mesh of the height map (TODO)
  - Provide the moisture map (TODO)

### TerrainChunk
Just a chunk of the map. Currently defined as a `CHUNK_WIDTH` by `CHUNK_HEIHGT`
array of height and moisture values. This class is necessary because the system 
requires multiple chunks to be loaded and unloaded independently and, in the 
future, some may be loaded with more or less detail. Also, chunking the map 
allows for parallelization strategies when generating or displaying.

### TerrainChunkLoader
Implements the decoupling layer that provides a TerrainChunk whether it has 
been already generated or not. If the chunk has been generated and stored in 
disk, this class will read it and serve it. If, on the other hand, the chunk 
must be generated, the necessary function calls will be made.

### TerrainChunkGenerator
*Under construction*
This class uses the Perlin Simplex Noise algorithm to generate a TerrainChunk.
A later implementation will provide means to customize the generation giving 
some levels of freedom.

### SimplexGenerator
*Heavily under construction*
Implements the Perlin Simplex Noise algorithm. This class has to provide a 
method to seed the generated results and have some level of freedom to allow 
customizing parameters like frequency.