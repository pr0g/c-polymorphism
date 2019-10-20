#include "stdio.h"

const float PI = 3.14159265359f;

typedef struct vec2_t {
    float x;
    float y;
} vec2_t;

struct shape_t;

typedef struct shape_vtbl_t {
    float (*area)(struct shape_t*);
    float (*perimeter)(struct shape_t*);
} shape_vtbl_t;

typedef struct shape_t {
    shape_vtbl_t vtbl_;
    vec2_t position_;
} shape_t;

typedef struct circle_t {
    shape_t shape_;
    float radius_;
} circle_t;

typedef struct rectangle_t {
    shape_t shape_;
    float width_;
    float height_;
} rectangle_t;

float circle_area(shape_t* s) {
    circle_t* self = (circle_t*)s;
    printf("%s", "circle_area: ");
    return PI * self->radius_ * self->radius_;
}

float circle_perimeter(shape_t* s) {
    circle_t* self = (circle_t*)s;
    printf("%s", "circle_perimeter: ");
    return 2.0f * PI * self->radius_;
}

float rectangle_area(shape_t* s) {
    rectangle_t* self = (rectangle_t*)s;
    printf("%s", "rectangle_area: ");
    return self->width_ * self->height_;
}

float rectangle_perimeter(shape_t* s) {
    rectangle_t* self = (rectangle_t*)s;
    printf("%s", "rectangle_perimeter: ");
    return self->width_ * 2.0f + self->height_ * 2.0f;
}

float shape_area(shape_t* s) {
    return s->vtbl_.area(s);
}

float shape_perimeter(shape_t* s) {
    return s->vtbl_.perimeter(s);
}

int main(int argc, char** argv)
{
    circle_t circle = {
        .shape_ = {
            .vtbl_ = {
                .area = circle_area,
                .perimeter = circle_perimeter
            },
            .position_ = {
                .x = 0.0f, .y = 1.0f
            }
        },
        .radius_ = 5.0f
    };

    // compound literal test
    rectangle_t rectangle;
    rectangle = (rectangle_t) {
        .shape_ = {
            .vtbl_ = {
                .area = rectangle_area,
                .perimeter = rectangle_perimeter
            },
            .position_ = {
                .x = 2.0f, .y = 1.0f
            }
        },
        .width_ = 6.0f,
        .height_ = 2.0f
    };

    shape_t* shapes[2] = {
        [0] = (shape_t*)&circle,
        [1] = (shape_t*)&rectangle
    };

    for (int i = 0; i < 2; ++i) {
        printf("%f\n", shape_area(shapes[i]));
        printf("%f\n", shape_perimeter(shapes[i]));
    }

    return 0;
}
