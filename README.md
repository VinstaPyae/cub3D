*This project has been created as part of the 42 curriculum by pzaw, &lt;lwin&gt;.*

# cub3D

## Description

cub3D is a small first-person 3D maze explorer written in C, inspired by the
classic *Wolfenstein 3D* (1992). Its goal is to learn **raycasting**: drawing a
3D-looking view from a flat 2D grid map, in real time, using only the
[MiniLibX](https://github.com/42Paris/minilibx-linux) graphics library.

The program:

- reads a scene file (`.cub`) that describes the wall textures, the floor and
  ceiling colors, and the map;
- checks the file and stops with `Error` and a clear message if anything is wrong
  (missing or duplicate settings, bad colors, unreadable textures, invalid
  characters, zero or several players, a map not closed by walls, and so on);
- opens a window and draws the maze from the player's point of view, with a
  different texture for each wall direction (north, south, east, west);
- lets the player walk around and turn with the keyboard.

## Instructions

### Requirements

- Linux with an X11 desktop
- `gcc`, `make`
- X11 development packages (Debian/Ubuntu):

  ```sh
  sudo apt-get install libx11-dev libxext-dev libbsd-dev
  ```

- MiniLibX for Linux in the `minilibx-linux/` folder. The Makefile builds it
  for you.

### Build

```sh
make        # builds libft, MiniLibX and the cub3D executable
make clean  # removes object files
make fclean # removes object files and the executable
make re     # rebuilds everything
```

> **Note for GCC 15 and newer:** these versions use the C23 standard by default
> and reject MiniLibX's old-style function prototypes. If the build fails with
> `incompatible pointer type` in `mlx_loop_hook`, build with
> `make CFLAGS="-Wall -Wextra -Werror -g -std=gnu17"`.

### Run

```sh
./cub3D maps/map1.cub
./cub3D maps/dungeon.cub
```

### Controls

| Key       | Action             |
|-----------|--------------------|
| `W` / `S` | Move forward / back |
| `A` / `D` | Move left / right   |
| `←` / `→` | Turn left / right   |
| `Esc` or the window's close button | Quit |

### Scene file format (`.cub`)

```
NO textures/text/north.xpm
SO textures/text/south.xpm
WE textures/text/west.xpm
EA textures/text/east.xpm

F 220,100,0
C 225,30,0

        1111111111111
        1000000000001
111111111011000001N01
100000000011000001111
111111111111111111111
```

- `NO`, `SO`, `WE`, `EA`: path to the `.xpm` texture for each wall direction.
- `F`, `C`: floor and ceiling colors as `R,G,B` (each from 0 to 255).
- The settings can come in any order and may be separated by empty lines. The
  map must come last.
- Map characters: `1` wall, `0` empty floor, a space for empty area outside the
  map, and exactly one of `N`, `S`, `E`, `W` for the player's start position and
  the direction they face.
- The map must be fully closed by walls.

## Technical choices

- **Raycasting with DDA.** For each column of the screen, one ray is cast from
  the player. The DDA (Digital Differential Analyzer) algorithm steps through
  the grid one square at a time until the ray hits a wall. The distance to the
  wall (corrected for the fish-eye effect) sets how tall the wall slice is.
- **Camera plane.** The player has a direction vector and a camera plane
  vector. Turning rotates both with a 2D rotation matrix.
- **Textures.** The side of the wall that was hit picks the texture, and the
  exact hit point picks the texture column. Textures are 64×64 XPM images.
- **One image per frame.** Each frame is drawn into an off-screen MiniLibX image
  and then put in the window in one go, to avoid flicker.
- **Smooth movement.** Key presses and releases set flags. The game loop moves
  the player every frame while a key is held. A small margin keeps the player
  from getting too close to walls.
- **Map checking.** The map is padded into a rectangle. Every floor or player
  square must not touch a space or the edge of the map.
- Window size: 1080×720.

## Resources

- [Lode's Computer Graphics Tutorial – Raycasting](https://lodev.org/cgtutor/raycasting.html):
  the main reference for the DDA raycaster and textured walls.
- [MiniLibX for Linux (42Paris)](https://github.com/42Paris/minilibx-linux)
  and the [MiniLibX guide by harm-smits](https://harm-smits.github.io/42docs/libs/minilibx).
- [Permadi – Ray-Casting Tutorial for Game Development](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/).
- [Wolfenstein 3D (Wikipedia)](https://en.wikipedia.org/wiki/Wolfenstein_3D):
  background on the game that made this technique popular.
- The cub3D subject from 42.

### AI usage

AI (Claude) was used for:

- **Testing:** building the project, and running it with valid maps and many
  broken `.cub` files under Valgrind to find crashes and leaks. This found a
  crash when a scene file has no map, which was then fixed (the
  `Missing map` check in `cub3D.c`).
- **Documentation:** drafting this README.
