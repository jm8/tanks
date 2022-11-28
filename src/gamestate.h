class GameState {
public:
    int mouseX, mouseY;
    bool mouseDown;

    virtual void update(double dt) = 0;
    virtual void draw() = 0;
};
