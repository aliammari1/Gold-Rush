# Banner & social preview — image-generation brief

This is the single, copy-paste prompt for the Gold Rush hero banner and
GitHub social preview. Generate the images with an image model (or the
`brandkit` / `imagegen-frontend-web` skills), then commit them as local
files under `assets/banner/` so they never rate-limit or 404. The README
hero references `assets/banner/banner-wide.png`.

## The prompt (copy-paste)

> Pixel-art game banner for a 2D platformer called **"GOLD RUSH"**, western
> gold-mining frontier theme, rendered on a vintage CRT arcade screen.
> A pixel-art prospector hero is **mid-jump** across a wooden mine-shaft
> gap, reaching toward a **glinting gold nugget** that throws a small
> star-shaped light glint. Background: desert mesas and a wooden mining
> rig at dusk, ore carts and pickaxes, parallax layers. Bold western
> woodtype "GOLD RUSH" wordmark across the upper third with a small
> tagline "A 2D platformer in C + SDL". Color palette: warm **amber and
> burnt-sienna gold highlights** against a **dusk-blue** evening sky and
> deep charcoal shadows. Treatment: chunky 16-bit pixel art with a subtle
> CRT scanline overlay, soft vignette, and slight chromatic aberration at
> the edges. Adventurous, nostalgic, hand-built indie mood. Wide cinematic
> composition, crisp readable text, no watermark.

**Primary size:** `1280×640` (GitHub social preview + README hero).
For a hero crop, also export a wider `1600×400` strip from the same art.

## Deliverables

| File | Size | Use |
|------|------|-----|
| `assets/banner/social-preview.png` | **1280×640** | GitHub → Settings → Social preview, and README hero |
| `assets/banner/banner-wide.png` | ~1600×400 | optional wide README strip |
| `assets/banner/icon.png` | 512×512 | square logo / docs favicon (crop the gold-nugget glint) |

## Wiring

1. Replace the TODO comment at the top of `README.md` with the banner image
   (`assets/banner/banner-wide.png`, falling back to `social-preview.png`).
2. Upload `social-preview.png` under **Settings → General → Social preview**.
3. Optionally point the MkDocs `theme.logo` / `favicon` at `icon.png`.

_Status:_ **TODO** — prompt finalized; run it to produce the files above.
