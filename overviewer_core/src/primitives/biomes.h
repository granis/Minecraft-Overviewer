/*
 * This file is part of the Minecraft Overviewer.
 *
 * Minecraft Overviewer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * Minecraft Overviewer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with the Overviewer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#define DEFAULT_BIOME 7 /* forest, nice and green */

typedef struct {
    const char* name;

    float temperature;
    float rainfall;

    uint32_t r, g, b;
} Biome;

/* each entry in this table is yanked *directly* out of the minecraft source
 * temp/rainfall are taken from what MCP calls setTemperatureRainfall
 *
 * Some biomes, like Swamp, do a bit of post-processing by multiplying on a
 * hard-coded color. The RGB tuple used follows the temp/rainfall.
 * 255, 255, 255 is white, which means do nothing
 *
 * keep in mind the x/y coordinate in the color tables is found *after*
 * multiplying rainfall and temperature for the second coordinate, *and* the
 * origin is in the lower-right. <3 biomes.
 */
static Biome biome_table[] = {
    /* 0 */
    {"The Void", 0.5, 0.5, 255, 255, 255},
    {"Plains", 0.8, 0.4, 255, 255, 255},
    {"Sunflower Plains", 0.8, 0.4, 255, 255, 255},
    {"Snowy Plains", 0.0, 0.5, 255, 255, 255},
    {"Ice Spikes", 0.0, 0.5, 255, 255, 255},
    /* 5 */
    {"Desert", 2.0, 0.0, 255, 255, 255},
    {"Swamp", 0.8, 0.9, 205, 128, 255},
    {"Forest", 0.7, 0.8, 255, 255, 255},
    {"Flower Forest", 0.7, 0.8, 255, 255, 255},
    {"Birch Forest", 0.6, 0.6, 255, 255, 255},
    /* 10 */
    {"Dark Forest", 0.7, 0.8, 255, 255, 255},
    {"Old Growth Birch Forest", 0.6, 0.6, 255, 255, 255},
    {"Old Growth Pine Taiga", 0.3, 0.8, 255, 255, 255},
    {"Old Growth Spruce Taiga", 0.25, 0.8, 255, 255, 255},
    {"Taiga", 0.25, 0.8, 255, 255, 255},
    /* 15 */
    {"Snowy Taiga", -0.5, 0.4, 255, 255, 255},
    {"Savanna", 1.2, 0.0, 255, 255, 255},
    {"Savanna Plateau", 1.0, 0.0, 255, 255, 255},
    {"Windswept Hills", 0.2, 0.3, 255, 255, 255},
    {"Windswept Gravelly Hills", 0.2, 0.3, 255, 255, 255},
    /* 20 */
    {"Windswept Forest", 0.2, 0.3, 255, 255, 255},
    /* Values below are guesses */
    {"Windswept Savanna", 1.1, 0.0, 255, 255, 255},
    {"Jungle", 0.95, 0.9, 255, 255, 255},
    {"Sparse Jungle", 0.95, 0.8, 255, 255, 255},
    {"Bamboo Jungle", 0.95, 0.9, 255, 255, 255},
    /* 25 */
    {"Badlands", 2.0, 0.0, 144, 129, 77},
    {"Eroded Badlands", 2.0, 0.0, 144, 129, 77},
    {"Wooded Badlands", 2.0, 0.0, 144, 129, 77},
    {"Meadow", 0.5, 0.8, 255, 255, 255},
    {"Grove", -0.2, 0.8, 255, 255, 255},
    /* 30 */
    {"Snowy Slopes", -0.3, 0.9, 255, 255, 255},
    {"Frozen Peaks", -0.7, 0.9, 255, 255, 255},
    {"Jagged Peaks", -0.7, 0.9, 255, 255, 255},
    {"Stony Peaks", 1.5, 0.3, 255, 255, 255},
    {"River", 0.5, 0.5, 255, 255, 255},
    /* 35 */
    {"Frozen River", 0.0, 0.5, 255, 255, 255},
    {"Beach", 0.8, 0.4, 255, 255, 255},
    {"Snowy Beach", 0.05, 0.3, 255, 255, 255},
    {"Stony Shore", 0.2, 0.3, 255, 255, 255},
    {"Warm Ocean", 0.5, 0.5, 255, 255, 255},
    /* 40 */
    {"Lukewarm Ocean", 0.5, 0.5, 255, 255, 255},
    {"Deep Lukewarm Ocean", 0.5, 255, 255, 255},
    {"Ocean", 0.5, 0.5, 255, 255, 255},
    {"Deep Ocean", 0.5, 0.5, 255, 255, 255},
    {"Cold Ocean", 0.5, 0.5, 255, 255, 255},
    /* 45 */
    {"Deep Cold Ocean", 0.5, 0.5, 255, 255, 255},
    {"Frozen Ocean", 0.0, 0.5, 255, 255, 255},
    {"Deep Frozen Ocean", 0.5, 0.5, 255, 255, 255},
    {"Mushroom Fields", 0.9, 1.0, 255, 255, 255},
    {"Dripstone Caves", 0.8, 0.4, 255, 255, 255},
    //* 50 */
    {"Lush Caves", 0.5, 0.5, 255, 255, 255},
    {"Nether Wastes", 2.0, 0.0, 255, 255, 255},
    {"Warped Forest", 2.0, 0.0, 255, 255, 255},
    {"Crimson Forest", 2.0, 0.0, 255, 255, 255},
    {"Soul Sand Valley", 2.0, 0.0, 255, 255, 255},
    /* 55 */
    {"Basalt Deltas", 2.0, 0.0, 255, 255, 255},
    {"The End", 0.5, 0.5, 255, 255, 255},
    {"End Highlands", 0.5, 0.5, 255, 255, 255},
    {"End Midlands", 0.5, 0.5, 255, 255, 255},
    {"Small End Islands", 0.5, 0.5, 255, 255, 255},
    /* 60 */
    {"End Barrens", 0.5, 0.5, 255, 255, 255},
};

#define NUM_BIOMES (sizeof(biome_table) / sizeof(Biome))
