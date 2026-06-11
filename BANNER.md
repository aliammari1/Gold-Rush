# Banner & social preview spec

Art direction for the Gold Rush README hero and GitHub social-preview
image. Generate the assets with the `brandkit` / `imagegen-frontend-web`
skills and commit them as local files under `assets/banner/` so they never
rate-limit or 404.

## Direction: western mining, pixel-art + CRT

- **Theme:** a 19th-century gold-rush mining frontier rendered as a retro
  2D platformer — pickaxes, ore carts, wooden mine-shaft scaffolding, a
  glinting gold vein, desert mesas at sunset.
- **Treatment:** chunky pixel art with a subtle CRT scanline / vignette
  overlay and slight chromatic aberration at the edges, evoking an old
  arcade cabinet.
- **Palette:** dusty ochre and burnt sienna, gold/amber highlights, deep
  charcoal shadows, a warm sunset-orange sky. Matches the `amber` accent
  used in the docs theme.
- **Typography:** a bold western slab/woodtype "GOLD RUSH" wordmark, pixel
  or stencil styled, with a thin tagline ("A 2D platformer in C + SDL").
- **Mood:** adventurous, nostalgic, hand-built indie.

## Deliverables

| File | Size | Use |
|------|------|-----|
| `assets/banner/banner-wide.png` | ~1600×400 | README hero (top of README) |
| `assets/banner/social-preview.png` | **1280×640** | GitHub → Settings → Social preview |
| `assets/banner/icon.png` | 512×512 | square logo / favicon for the docs |

## Wiring

1. Replace the TODO comment at the top of `README.md` with the wide banner.
2. Upload `social-preview.png` under **Settings → General → Social
   preview**.
3. Point the MkDocs `theme.logo`/`favicon` at `icon.png` if desired.

_Status:_ **TODO** — referenced from the README; assets not yet generated.
