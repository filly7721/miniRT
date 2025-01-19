#include "stdio.h"
# include <stdlib.h>
# include <fcntl.h> 
# include <unistd.h> 
# include <stdarg.h>
# include <math.h>
#include <assert.h>

typedef union	u_tuple
{
	struct
	{
		double	x;
		double	y;
		double	z;
		double	w;
	};
	struct
	{
		double	a;
		double	r;
		double	g;
		double	b;
	};
}	t_tuple;

typedef struct s_ray
{
	t_tuple origin;
	t_tuple direction;
} t_ray;

typedef struct s_sphere
{
	float x;
	float y;
	float z;

	float diameter;

	int r;
	int g;
	int b;

}	t_sphere;

t_ray* create_ray(t_tuple origin, t_tuple direction)
{
    t_ray*   ray;
    
    ray = malloc(sizeof(t_ray));
    if (!ray)
    {
        printf("Failed ray allocation\n");
        return (NULL);
    }
    ray->origin = origin;
    ray->direction = direction;
    return (ray);
}

t_tuple position(t_ray* ray, double t)
{
    t_tuple pos;

    pos.x = ray->origin.x + ray->direction.x * t;
    pos.y = ray->origin.y + ray->direction.y * t;
    pos.z = ray->origin.z + ray->direction.z * t;
    pos.w = ray->origin.w + ray->direction.w * t;
    return (pos);
}

void test_position_function() {
    // Define the origin and direction
    t_tuple origin = {1, 2, 3, 1};  // Point (1, 2, 3)
    t_tuple direction = {4, 5, 6, 0};  // Vector (4, 5, 6)

    // Create the ray
    t_ray* ray = create_ray(origin, direction);
    
    // Test for t = 0 (Position should be same as origin)
    t_tuple pos = position(ray, 0);
    assert(pos.x == 1.0);
    assert(pos.y == 2.0);
    assert(pos.z == 3.0);
    assert(pos.w == 1.0);
    
    // Test for t = 1 (Position should be origin + direction)
    pos = position(ray, 1);
    assert(pos.x == 5.0);
    assert(pos.y == 7.0);
    assert(pos.z == 9.0);
    assert(pos.w == 1.0);
    
    // Test for t = -1 (Position should be origin - direction)
    pos = position(ray, -1);
    assert(pos.x == -3.0);
    assert(pos.y == -3.0);
    assert(pos.z == -3.0);
    assert(pos.w == 1.0);
    
    // Test for t = 2.5 (Position should be scaled accordingly)
    pos = position(ray, 2.5);
    assert(pos.x == 11.0);
    assert(pos.y == 14.5);
    assert(pos.z == 18.0);
    assert(pos.w == 1.0);

    // If all tests pass
    printf("All tests passed successfully!\n");

    // Don't forget to free the memory when done
    free(ray);
}

// int main() {
//     test_position_function();  // Run the test case
//     return 0;
// }

t_tuple	set_tuple(double x, double y, double z, double w)
{
	t_tuple t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = w;
	return (t);
}

t_tuple add_tuples(t_tuple t1, t_tuple t2)
{
	return (set_tuple(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w));
}

t_tuple sub_tuples(t_tuple t1, t_tuple t2)
{
	return (set_tuple(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w));
}

t_tuple mul_tuple(t_tuple t, double scalar)
{
	return (set_tuple(t.x * scalar, t.y * scalar, t.z * scalar, t.w * scalar));
}

t_tuple negate_tuple(t_tuple t)
{
	return (set_tuple(-t.x, -t.y, -t.z, -t.w));
}

double	dot_tuple(t_tuple t1, t_tuple t2)
{
	return (t1.x * t2.x + t1.y * t2.y + t1.z * t2.z + t1.w * t2.w);
}

t_tuple	cross_tuple(t_tuple t1, t_tuple t2)
{
	return set_tuple(
		t1.y * t2.z - t1.z * t2.y,
		t1.z * t2.x - t1.x * t2.z,
		t1.x * t2.y - t1.y * t2.x,
		0);
}

double	mag_tuple(t_tuple t)
{
	return (sqrt(dot_tuple(t, t)));
}

t_tuple normalize_tuple(t_tuple t)
{
	return mul_tuple(t, 1 / mag_tuple(t));
}
int sphere_equation(t_ray* ray, t_sphere* sphere, double* a, double* b, double* c)
{
    t_tuple sphere_to_ray;

    sphere_to_ray = sub_tuples(ray->origin, set_tuple(sphere->x, sphere->y, sphere->z, 0));
    *a = dot_tuple(ray->direction, ray->direction);
    *b = 2 * dot_tuple(ray->direction, sphere_to_ray);
    *c = dot_tuple(sphere_to_ray, sphere_to_ray) - (sphere->diameter * sphere->diameter) / 4;;
    return (1);
}

int intersect(t_ray* ray, t_sphere* sphere, double* t1, double* t2)
{
    double a;
    double b;
    double c;
    double discrim;
    double sqrt_discrim;
    
    sphere_equation(ray, sphere, &a, &b, &c);
    discrim = (b * b) - (4 * a * c);
    if (discrim < 0)
        return (0);
    sqrt_discrim = sqrt (discrim);
    *t1 = (-b - sqrt_discrim) / (2 * a);
    *t2 = (-b + sqrt_discrim) / (2 * a);
    return (1);
}

// Assuming other necessary structures and functions are defined here

#include <stdio.h>
#include <math.h>

void test_ray_sphere_intersection() {
    t_ray ray;
    t_sphere sphere;
    double t1, t2;

    // Test Case 1: Tangent to the sphere
    ray = (t_ray){ set_tuple(0, 1, -5, 0), set_tuple(0, 0, 1, 0) };
    sphere = (t_sphere){ 0, 0, 0, 2, 255, 0, 0 }; // Center (0, 0, 0), radius = 1
    if (intersect(&ray, &sphere, &t1, &t2)) {
        printf("Test 1 Passed: t1 = %f, t2 = %f\n", t1, t2);
    } else {
        printf("Test 1 Failed: No intersection\n");
    }

    // Test Case 2: Ray intersects at two points
    ray = (t_ray){ set_tuple(0, 0, -5, 0), set_tuple(0, 0, 1, 0) };
    sphere = (t_sphere){ 0, 0, 0, 2, 255, 0, 0 }; // Center (0, 0, 0), radius = 1
    if (intersect(&ray, &sphere, &t1, &t2)) {
        printf("Test 2 Passed: t1 = %f, t2 = %f\n", t1, t2);
    } else {
        printf("Test 2 Failed: No intersection\n");
    }

    // Test Case 3: Ray misses the sphere
    ray = (t_ray){ set_tuple(0, 2, -5, 0), set_tuple(0, 0, 1, 0) };
    sphere = (t_sphere){ 0, 0, 0, 2, 255, 0, 0 }; // Center (0, 0, 0), radius = 1
    if (intersect(&ray, &sphere, &t1, &t2)) {
        printf("Test 3 Failed: Intersection at t1 = %f, t2 = %f\n", t1, t2);
    } else {
        printf("Test 3 Passed: No intersection\n");
    }
    printf("sphere: x: %f,x: %f,x: %f,x: %f, c: %i, c: %i, c: %i\n", sphere.x, sphere.y, sphere.z, sphere.diameter, sphere.r, sphere.g, sphere.b);
}

int main()
{
    test_ray_sphere_intersection();


    return 0;
}


