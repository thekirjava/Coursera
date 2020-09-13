#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

// Напишите реализацию функции
class Rectangle : public IShape {
public:
    Rectangle() = default;

    Rectangle(const Point &point, const Size &size, const shared_ptr<ITexture> &ptr) : position(point), sz(size) {
        texture = ptr;
    }

    unique_ptr<IShape> Clone() const override {
        return make_unique<Rectangle>(position, sz, texture);
    }

    void SetPosition(Point point) override {
        position = point;
    }

    Point GetPosition() const override {
        return position;
    }

    void SetSize(Size size) override {
        sz = size;
    }

    Size GetSize() const override {
        return sz;
    }

    void SetTexture(std::shared_ptr<ITexture> ptr) override {
        texture = ptr;
    }

    ITexture *GetTexture() const override {
        return texture.get();
    }

    void Draw(Image &image) const override {
        for (int i = position.y;
             i < min(static_cast<size_t>(position.y + sz.height), image.size()); i++) { //проверить размеры картинки
            for (int j = position.x; j < min(static_cast<size_t>(position.x + sz.width), image[i].size()); j++) {
                if (texture != nullptr) {
                    if ((i < position.y + texture->GetSize().height) && (j < position.x + texture->GetSize().width)) {
                        image[i][j] = texture->GetImage()[i - position.y][j - position.x];
                        continue;
                    }
                }
                image[i][j] = '.';
            }
        }
    }

private:
    Point position;
    Size sz;
    shared_ptr<ITexture> texture;
};

class Ellipse : public IShape {
public:
    Ellipse() = default;

    Ellipse(const Point &point, const Size &size, const shared_ptr<ITexture> &ptr) : position(point), sz(size) {
        texture = ptr;
    }

    unique_ptr<IShape> Clone() const override {
        return make_unique<Ellipse>(position, sz, texture);
    }

    void SetPosition(Point point) override {
        position = point;
    }

    Point GetPosition() const override {
        return position;
    }

    void SetSize(Size size) override {
        sz = size;
    }

    Size GetSize() const override {
        return sz;
    }

    void SetTexture(std::shared_ptr<ITexture> ptr) override {
        texture = ptr;
    }

    ITexture *GetTexture() const override {
        return texture.get();
    }

    void Draw(Image &image) const override {
        for (int i = position.y;
             i < min(static_cast<size_t>(position.y + sz.height), image.size()); i++) { //проверить размеры картинки
            for (int j = position.x; j < min(static_cast<size_t>(position.x + sz.width), image[i].size()); j++) {
                if (!IsPointInEllipse({j - position.x, i - position.y}, sz)) {
                    continue;
                }
                if (texture != nullptr) {
                    if ((i < position.y + texture->GetSize().height) && (j < position.x + texture->GetSize().width)) {
                        image[i][j] = texture->GetImage()[i - position.y][j - position.x];
                        continue;
                    }
                }
                image[i][j] = '.';
            }
        }
    }

private:
    Point position;
    Size sz;
    shared_ptr<ITexture> texture;
};

unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    switch (shape_type) {
        case ShapeType::Rectangle:
            return make_unique<Rectangle>();
        case ShapeType::Ellipse:
            return make_unique<Ellipse>();
    }
    return nullptr;
}