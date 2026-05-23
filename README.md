# mouse-jiggler

A Windows utility written in C++ that moves the mouse cursor in a continuous circle to prevent the PC from going to sleep or triggering a screensaver. Configurable radius, speed, duration, and mouse button click.

---

## How it works

On startup, the app prompts for four parameters:

- **Duration** (seconds) — how long to run
- **Timestep** (milliseconds) — how often the cursor position updates
- **Radius** (pixels) — size of the circle the cursor moves in
- **Mouse button** — which button to click on each step (LEFT / MIDDLE / RIGHT)

The cursor position is updated each tick using polar coordinates derived from elapsed time:

```
x = cursorX + radius * cos(elapsed_seconds)
y = cursorY + radius * sin(elapsed_seconds)
```

A global low-level keyboard hook (`WH_KEYBOARD_LL`) runs on a detached thread — pressing any key terminates the application immediately, even when the window is not focused.

---

## Usage

```
How much time should the application run (in seconds)? 3600
How often should the cursor position update (in miliseconds)? 100
How big should the radius of the circle around which the cursor will rotate (in pixels)? 20
Which mouse input should the mouse execute (LEFT / MIDDLE / RIGHT)? left
```

Press any key at any time to stop early.

---

## Architecture

```
Main.cpp      — CLI prompts, input validation, entry point
Jiggler       — rotation loop, timing, early exit logic
WinAPI        — Windows API wrapper (cursor get/set, mouse input, keyboard hook)
```

`WinAPI` wraps `GetCursorPos`, `SetCursorPos`, `SendInput`, and `SetWindowsHookEx` behind a clean static interface. The keyboard hook runs in its own detached thread with a Windows message loop to avoid blocking the jiggler loop.

---

## Requirements

- Windows (uses `Windows.h`, `SendInput`, `SetWindowsHookEx`)
- C++17 or later

## Build

Compile with any Windows C++ toolchain (MSVC, MinGW):

```bash
g++ Main.cpp Jiggler.cpp WinAPI.cpp -o mouse-jiggler -luser32
```
