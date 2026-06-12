# Growth & Launch Kit — Gold Rush

Ready-to-paste assets for launching Gold Rush. The hook: **a 2D platformer
written in pure C + SDL that plays in your browser via WebAssembly.** Voters
click *play now* — lead with the WASM demo everywhere.

> Prereq for launch day: the in-browser build must be live. Build it from the
> `feat/sdl2-wasm` branch (`make wasm`) and publish to Cloudflare Pages
> (`gold-rush.pages.dev`) and the itch.io HTML5 channel, plus capture a short
> gameplay GIF (see `BANNER.md`). Do not launch before the play link works.

---

## Repo metadata (GitHub → About)

**Topics** (8, all within the 20-topic cap):

```
gamedev, sdl, c, platformer, wasm, emscripten, indie-game, 2d-game
```

**About / description** (keyword-rich, <350 chars):

> A 2D platformer written in pure C + SDL that plays in your browser via
> WebAssembly (Emscripten). State-machine engine, physics movement, enemy AI,
> and a Connect Four minigame with an alpha-beta minimax opponent. Zlib.

**Website field:** `https://gold-rush.pages.dev`

---

## Show HN

**Title:**

> Show HN: I wrote a 2D platformer in pure C/SDL — it plays in your browser (WASM)

**First comment (seed immediately after posting):**

> Author here. Gold Rush is a 2D platformer written in plain C with SDL —
> no engine, no framework, just a state-machine game loop, hand-rolled
> physics (acceleration/friction/arc jumps), a tracking enemy AI, a timed
> quiz, and a Connect Four minigame whose CPU uses depth-limited alpha-beta
> (minimax).
>
> The fun part: the same C compiles to WebAssembly with the Emscripten
> toolchain (`emcc` + `-s USE_SDL`), so the whole thing runs in a browser
> tab with zero install — that's the "play now" link above. Native builds
> link the SDL 1.2 family; the browser build ports the renderer to SDL 2 +
> Emscripten on a separate branch. It's only a few thousand KB of C in total.
>
> The Connect Four AI lives in a single SDL-free file (`connect4_ai.c`) so
> it's unit-tested in CI (Unity, ASan/UBSan, Codecov gate) and provably never
> loses to weaker play. Release tarballs ship with SLSA build provenance.
>
> Happy to talk about the Emscripten setup, the SDL 1.2 → 2 port, or the
> minimax search. Code is Zlib-licensed.

**Timing:** post Tue–Thu, ~13:00–16:00 UTC. Reply to every comment within the
first hour.

---

## Reddit

**r/gamedev** — flair: *Game* / *Show & Tell*

> Title: I wrote a 2D platformer in pure C + SDL — and it plays in your browser (WASM)
>
> Body: No engine — just C, a state-machine loop, hand-rolled physics, enemy
> AI, and a Connect Four minigame with an alpha-beta minimax CPU. The same C
> compiles to WebAssembly via Emscripten, so you can play it in a browser tab
> with no install: <play link>. Source (Zlib) + the SDL 1.2→2/Emscripten notes
> are in the repo. Happy to answer questions about the port or the AI.

**r/C_Programming**

> Title: A 2D platformer in pure C + SDL, compiled to WebAssembly so it runs in the browser
>
> Body: Wanted to see how far plain C + SDL goes for a small game. Result is a
> platformer with physics, enemy AI, a quiz, and a Connect Four minigame (the
> CPU uses depth-limited alpha-beta). The interesting bit for this sub: the
> SDL-free AI module is fully unit-tested, and the whole game cross-compiles
> to WASM with Emscripten and runs in a browser — no install. Play + source:
> <repo link>.

**r/programming**

> Title: Show: A 2D platformer in pure C/SDL that plays in your browser via WebAssembly
>
> Body: <play link> — pure C compiled to WASM with Emscripten, no engine.
> Writeup of the SDL 1.2 → SDL 2 + Emscripten port and the minimax Connect
> Four AI in the README. Zlib-licensed.

> Build comment karma in each sub before posting; lead with the *play-now*
> link, not the source.

---

## Awesome-list submissions

**awesome-c** (Games section) — `oz123/awesome-c`:

```
- [Gold Rush](https://github.com/aliammari1/Gold-Rush) - 2D platformer in pure C + SDL that compiles to WebAssembly and plays in the browser; includes an alpha-beta minimax Connect Four minigame. Zlib.
```

**awesome-sdl** (Games / Examples):

```
- [Gold Rush](https://github.com/aliammari1/Gold-Rush) - 2D platformer in C with SDL, ported to SDL 2 + Emscripten for an in-browser WebAssembly build. Zlib.
```

> Submit only after the play link and gameplay GIF are live (awesome-list
> reviewers reject "coming soon" demos).

---

## itch.io devlog

**Title:** *Gold Rush now plays in your browser (pure C → WebAssembly)*

> Gold Rush is a 2D platformer written in plain C with SDL. I ported the
> renderer from SDL 1.2 to SDL 2 + Emscripten so it cross-compiles to
> WebAssembly — you can now play it right here in the browser, no download.
> Native Linux/macOS builds are still on the downloads tab. Source (Zlib) and
> the Emscripten build notes are on GitHub: <repo link>.

Tags: `platformer`, `c`, `sdl`, `webassembly`, `2d`, `open-source`.

---

## Cross-posting checklist

- [ ] WASM build live at `gold-rush.pages.dev` + itch HTML5 channel
- [ ] Gameplay GIF committed (`assets/banner/`) and shown in README
- [ ] Repo About + 8 topics + website field set
- [ ] Tagged release with native tarballs + SLSA provenance published
- [ ] Show HN posted (Tue–Thu 13:00–16:00 UTC) + first comment seeded
- [ ] r/gamedev, r/C_Programming, r/programming posts
- [ ] awesome-c + awesome-sdl PRs opened
- [ ] itch.io devlog published
- [ ] Reply to all comments within the first hour
