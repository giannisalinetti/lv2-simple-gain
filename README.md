# LV2 Simple Gain Plugin

A basic LV2 audio plugin for learning LV2 development. This is a toy project that implements a simple gain/volume control effect.

## About This Project

This plugin demonstrates the fundamental concepts of LV2 plugin development:
- Basic LV2 plugin structure and lifecycle
- Audio and control port handling
- Real-time audio processing
- RDF/Turtle metadata description
- Plugin packaging and installation

## Features

- **Single audio input/output**: Processes mono audio signals
- **Gain control**: Adjustable volume from 0.0 (silence) to 2.0 (double volume)
- **Real-time safe**: Suitable for use in professional audio applications
- **Pure C implementation**: No C++ dependencies

## Plugin Ports

| Port | Type | Description |
|------|------|-------------|
| Input | Audio Input | Audio signal input |
| Output | Audio Output | Processed audio signal output |
| Gain | Control Input | Volume control (0.0 - 2.0, default: 1.0) |

## Building

### Prerequisites
- GCC compiler
- LV2 development headers
- Make

### Build Commands
```bash
# Build the plugin
make

# Install to user LV2 directory (~/.lv2/)
make install

# Create local bundle for testing
make bundle

# Clean build artifacts
make clean

# Complete cleanup (build + installed files)
make distclean
```

## Usage

1. Build and install the plugin:
   ```bash
   make && make install
   ```

2. Open your LV2-compatible DAW (Ardour, Qtractor, Carla, etc.)

3. Look for "Simple Gain" in the plugin list (usually under Amplifiers/Utilities)

4. Insert the plugin on an audio track

5. Adjust the Gain parameter:
   - `0.0` = Silence
   - `0.5` = Half volume (-6 dB)
   - `1.0` = Unity gain (no change)
   - `2.0` = Double volume (+6 dB)

## Project Structure

```
lv2-simple-gain/
├── simple_gain.c      # Main plugin implementation
├── simple_gain.ttl    # Plugin metadata and port descriptions
├── manifest.ttl       # Plugin discovery manifest
├── Makefile          # Build system
└── README.md         # This file
```

## Code Overview

### Core LV2 Functions

The plugin implements the essential LV2 lifecycle functions:

- **`instantiate()`**: Creates plugin instance and allocates memory
- **`connect_port()`**: Connects plugin ports to host buffers
- **`run()`**: Processes audio samples (main DSP loop)
- **`cleanup()`**: Frees plugin resources

### Audio Processing

The core audio processing is simple gain multiplication:
```c
for (uint32_t pos = 0; pos < n_samples; pos++) {
    output[pos] = input[pos] * gain;
}
```

## Learning Resources

### Official LV2 Documentation
- [LV2 Specification](http://lv2plug.in/ns/) - Complete LV2 specification
- [LV2 Book](http://lv2plug.in/book/) - Comprehensive LV2 development guide
- [LV2 Plugin Programmer's Guide](http://lv2plug.in/ns/lv2core/lv2core.html) - Core concepts

### Example Code and Tutorials
- [LV2 Example Plugins](https://gitlab.com/lv2/lv2/-/tree/master/plugins) - Official example plugins
- [Guitarix LV2 Plugins](https://github.com/brummer10/guitarix) - Real-world LV2 implementations
- [Calf Studio Gear](https://github.com/calf-studio-gear/calf) - Professional LV2 plugin suite
- [LSP Plugins](https://github.com/sadko4u/lsp-plugins) - Modern LV2 plugin collection

### Development Tools
- [lv2lint](https://open-music-kontrollers.ch/lv2/lv2lint/) - LV2 plugin validator
- [Carla](https://github.com/falkTX/Carla) - Plugin host and testing tool
- [Jalv](https://gitlab.com/drobilla/jalv) - Simple LV2 host for testing
- [lv2ls](https://gitlab.com/drobilla/lilv) - List installed LV2 plugins

### Books and Articles
- "Audio Effects: Theory, Implementation and Application" by Joshua D. Reiss
- [DSP Guide](http://www.dspguide.com/) - Digital Signal Processing fundamentals
- [JUCE Framework Documentation](https://docs.juce.com/) - Cross-platform audio development

### Advanced LV2 Topics
- [LV2 Atom](http://lv2plug.in/ns/ext/atom/) - Event handling and MIDI
- [LV2 State](http://lv2plug.in/ns/ext/state/) - Plugin state saving/loading
- [LV2 Presets](http://lv2plug.in/ns/ext/presets/) - Plugin presets
- [LV2 UI](http://lv2plug.in/ns/extensions/ui/) - Custom plugin interfaces
- [LV2 Worker](http://lv2plug.in/ns/ext/worker/) - Non-real-time operations

### Community and Support
- [LV2 Mailing List](http://lists.lv2plug.in/listinfo.cgi/devel-lv2plug.in) - Developer discussions
- [LAU (Linux Audio Users)](https://lists.linuxaudio.org/listinfo/linux-audio-user) - Linux audio community
- [LAD (Linux Audio Developers)](https://lists.linuxaudio.org/listinfo/linux-audio-dev) - Developer community

## Next Steps for Learning

1. **Add MIDI support**: Learn about LV2 Atom and MIDI events
2. **Create a filter**: Implement low-pass, high-pass, or band-pass filters
3. **Add presets**: Learn LV2 state and preset extensions
4. **Build a custom UI**: Create GTK or Qt-based plugin interfaces
5. **Implement effects**: Reverb, delay, distortion, etc.

## License

This project is released under the ISC License - see the plugin metadata for details.

## Author

**Gianni Salinetti**  
Email: gbsalinetti@gmail.com  
GitHub: [giannisalinetti](https://github.com/giannisalinetti)

---

*This is a learning project created to understand LV2 plugin development fundamentals.*
