# Sophon Engine

An exercise in what's possible.  

## Project Goals
- [x] Entry-point - launch the engine from a client
- [ ] Application Layer - app life-cycle, time, etc
	- [x] Create window
	- [ ] Subscribe to window eve
		- [x] Close
		- [ ] Resize
- [ ] Window Layers
  - [x] Basic layer and layer-stack classes
	- [x] Update layers bottom-up
	- [x] Propagate input/events top-down through layers
	- [ ] Refactor/Review
- [ ] Event System
	- [x] Basic synchronous event system (starting out)
	- [ ] Buffered event system (non-blocking)
	- [ ] Propagate through layers
- [ ] Renderer
- [ ] Render API Abstraction
- [ ] Debugging Support
	- [x] logging
	- [ ] ???
- [ ] Scripting Language - C#, Lua, ???
- [ ] Memory - allocator, tracking, etc
- [ ] Entity Component System (ECS)
- [ ] Physics
- [ ] File I/O / VFS
- [ ] Build System / Custom File Format
	- [x] PreMake
