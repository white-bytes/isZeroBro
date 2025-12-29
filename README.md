# isZeroBro Project

An Astro-based documentation site using Starlight for the ZeroBro ESP32 Multi-Tool project.

[Project Tracking](https://wordparticles.monday.com/docs/18393297026?blockId=e0432743-ee66-4fbe-a01a-e185f61f07ee)

## Purpose
> [!IMPORTANT]
> This project is a work in progress and is not yet ready for production use. I am building this out of curiosity and
> hope to learn more network security and how to protect against other like-minded individuals. 🌈 😎.

## Quick Start

### Prerequisites
- Node.js 18+ 
- Yarn 1.22.22+

### Installation

```bash
# Install dependencies
yarn install

# Start development server
yarn dev

# Build for production
yarn build

# Preview production build
yarn preview
```

## Project Structure

```
├── src/
│   ├── components/         # Astro components
│   ├── config/            # JSON configuration files
│   ├── content/           # Documentation content
│   └── styles/            # CSS files
├── public/                # Static assets
├── componets-esp/         # ESP32 hardware documentation
└── dist/                  # Build output (generated)
```

## Configuration

- **Site settings:** `src/config/config.json`
- **Theme:** `src/config/theme.json`
- **Navigation:** `src/config/sidebar.json`
- **Social links:** `src/config/social.json`
- **Localization:** `src/config/locals.json`

## Recent Updates

✅ All critical issues resolved! See [NEXT_STEPS.md](./NEXT_STEPS.md) for details.

- Fixed deprecated import syntax
- Added missing font configuration
- Resolved build-time network dependency
- Added sitemap generation support

## Next Steps

See [NEXT_STEPS.md](./NEXT_STEPS.md) for a comprehensive list of completed fixes and recommended improvements.

**Before deployment:** Update the site URL in `astro.config.mjs` from `'https://example.com'` to your actual domain.

## License

MIT - See LICENSE file for details.

## Author

Brandon West