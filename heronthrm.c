#include <stdio.h>
#include <math.h>

#define sqrt(a) (a)

int main() {
    printf("Input side lengths of triangle: ");
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);
    if (a + b > c && a + c > b && b + c > a) {
        printf("Triangle is valid.\n");
        double s = (a + b + c) / 2;
        printf("Semi-Perimeter is: %lf\n", s);
        double area = s * (s - a) * (s - b) * (s - c);
        printf("Non-Rooted Area is: %lf\n", area);
        double rootedArea = sqrt(area);
        printf("Rooted Area is: %lf\n", rootedArea);
    } else {
        printf("Triangle is not valid.\n");
    }
    return 0;
}