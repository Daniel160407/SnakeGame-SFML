#ifndef WALL_HPP
#define WALL_HPP

class Wall {
    private:
        int width;
        int height;
        int posX;
        int posY;
    public:
        Wall();
        Wall(int width, int height, int posX, int posY);

        int getWidth() const;
        int getHeight() const;
        int getPosX() const;
        int getPosY() const;

        void setWidth(int width);
        void setHeight(int height);
        void setPosX(int posX);
        void setPosY(int posY);
};

#endif
