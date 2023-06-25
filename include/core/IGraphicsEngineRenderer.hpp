#ifndef GRAPHICS_ENGINE_RENDERER_HPP
#define GRAPHICS_ENGINE_RENDERER_HPP
// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
//
// Note that your path may be different depending on where you intalled things
//
//

#include <set>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

/**
 * This class serves as an interface to
 * the main graphics renderer for our engine.
 */
class IGraphicsEngineRenderer
{
public:
    /**
     * Constructor
     * @param w Screen width
     * @param h Screen height
     */
    IGraphicsEngineRenderer(int w, int h) : mScreenWidth(w), mScreenHeight(h){};
    /**
     * Destructor
     */
    virtual ~IGraphicsEngineRenderer(){};

    /**
     * Set the color for the background whenever
     * the color is cleared.
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    virtual void SetRenderDrawColor(int r, int g, int b, int a) = 0;
    /**
     * Clear the screen
     */
    virtual void RenderClear() = 0;
    /**
     * Render whatever is in the backbuffer to
     * the screen.
     */
    virtual void RenderPresent() = 0;

protected:
    // Screen dimension constants
    int mScreenWidth{0};
    int mScreenHeight{0};
};

/**
 * An SDL implementation of the graphics renderer.
 */
class SDLGraphicsEngineRenderer : public IGraphicsEngineRenderer
{
public:
    /**
     * Concrete implementation of constructor
     * @param w Width
     * @param h Height
     */
    SDLGraphicsEngineRenderer(int w, int h);
    /**
     * Destructor
     */
    ~SDLGraphicsEngineRenderer();

    /**
     * Set the color for the background whenever
     * the color is cleared.
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    void SetRenderDrawColor(int r, int g, int b, int a) override;
    /**
     * Clear the screen
     */
    void RenderClear() override;
    /**
     * Render whatever is in the backbuffer to
     * the screen.
     */
    void RenderPresent() override;

    /**
     * Get Pointer to Window
     * @return The pointer to the window
     */
    SDL_Window* GetWindow();

    /**
     * Get Pointer to Renderer
     * @return The pointer to the renderer
     */
    SDL_Renderer* GetRenderer();

private:
    // SDL Window
    SDL_Window* mWindow = nullptr;
    // SDL Renderer
    SDL_Renderer* mRenderer = nullptr;
};

#endif
