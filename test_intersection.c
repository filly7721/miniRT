#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <assert.h> // Include this line for the assert function
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
}	t_ray;

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


typedef enum e_shapeType
{
	sphere,
	plane,
	cylinder
}	t_shapeType;

typedef struct s_shape
{
	t_shapeType	type;
	union
	{
		t_sphere	*sphere;
		// t_plane		*plane;
		// t_cylinder	*cylinder;
	};
}	t_shape;

typedef struct s_intersection
{
	double	t;
	t_shape* shape;
	struct s_intersection* next;
}	t_intersection;

// t_tuple set_tuple(double x, double y, double z, double w)
// {
//     t_tuple t = { .x = x, .y = y, .z = z, .w = w };
//     return t;
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
    // *c = dot_tuple(sphere_to_ray, sphere_to_ray) - (sphere->diameter * sphere->diameter) / 4;;
    *c = dot_tuple(sphere_to_ray, sphere_to_ray) - (sphere->diameter / 2) * (sphere->diameter / 2);  // Use radius instead of diameter

    return (1);
}

// Assuming all required structs and functions (t_ray, t_sphere, etc.) are defined above
t_intersection* create_node(t_shape* shape, double t)
{
    t_intersection* node;

    node = malloc(sizeof(t_intersection));
    if (!node)
    {
        printf("Failed allocation intersection node\n");
        return (NULL);
    }
    node->t = t;
    node->shape = shape;
    node->next = NULL;
        printf("Created node: t = %.6f, object = %p\n", t, shape);  // Debug print

    return (node);
}

void add_node(t_intersection** head, t_intersection* new_node)
{
    if (new_node)
    {
        new_node->next = *head;
        *head = new_node;
    }
}

int calculate_intersect(t_ray* ray, t_sphere* sphere, double* t1, double* t2)
{
    double a;
    double b;
    double c;
    double discrim;
    double sqrt_discrim;
    
    sphere_equation(ray, sphere, &a, &b, &c);
        printf("Sphere Equation: a = %.6f, b = %.6f, c = %.6f\n", a, b, c);

    discrim = (b * b) - (4 * a * c);
        printf("Discriminant: %.6f\n", discrim);

    if (discrim < 0)
        return (0);
    sqrt_discrim = sqrt (discrim);
    *t1 = (-b - sqrt_discrim) / (2 * a);
    *t2 = (-b + sqrt_discrim) / (2 * a);
        printf("t1 = %.6f, t2 = %.6f\n", *t1, *t2);

    return (1);
}
void print_tuple(t_tuple t) 
{ 
    printf("Tuple: (%f, %f, %f, %f)\n", t.x, t.y, t.z, t.w);
} 
void print_ray_debug(t_ray* ray) 
{ 
    printf("Ray Origin: "); 
    print_tuple(ray->origin); 
    printf("Ray Direction: "); 
    print_tuple(ray->direction); 
} 
void print_sphere_debug(t_sphere* sphere) 
{ 
    printf("Sphere Center: (%f, %f, %f), Radius: %f\n", sphere->x, sphere->y, sphere->z, sphere->diameter / 2.0);
} 
t_intersection* intersect(t_ray* ray, t_sphere* _sphere)
{
    double t1;
    double t2;

    t_intersection* head;
    t_intersection* node;
    t_shape shape;

    head = NULL;
    shape.type = sphere;
    shape.sphere = _sphere;
    ray->direction = normalize_tuple(ray->direction); // Normalize the direction
    if(!calculate_intersect(ray, _sphere, &t1, &t2))
        return (NULL);
    if (t1 >= 0)
    {
        node = create_node(&shape, t1);
        add_node(&head, node);
    }
    if(t2 >= 0)
    {
        node = create_node(&shape, t2);
        add_node(&head, node);
    }
    return (head);
}

int count_nodes(t_intersection* head)
{
    int count = 0;
    t_intersection* current = head;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

void test_create_and_add_nodes()
{
    t_shape shape;
    shape.type = 1; // Assuming 1 represents a sphere type
    shape.sphere = NULL; // Replace with an actual sphere if necessary

    t_intersection* head = NULL;

    // Test creating and adding the first node
    t_intersection* node1 = create_node(&shape, 1.0);
    if (node1 == NULL)
    {
        printf("Failed to create node1\n");
        return;
    }
    add_node(&head, node1);

    // Test creating and adding the second node
    t_intersection* node2 = create_node(&shape, 2.0);
    if (node2 == NULL)
    {
        printf("Failed to create node2\n");
        return;
    }
    add_node(&head, node2);

    // Verify the linked list
    if (head == node2 && head->next == node1 && node1->next == NULL)
    {
        printf("Nodes created and added successfully\n");
    }
    else
    {
        printf("Failed to add nodes correctly\n");
    }
    // Count the nodes in the list 
    int node_count = count_nodes(head);
     printf("Number of nodes in the list: %d\n", node_count);
}

// int main()
// {
//     test_create_and_add_nodes();
//     return 0;
// }
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
void test_ray_sphere_intersection()
{
    // Define and initialize test ray and sphere
    t_tuple ray_origin = {0, 0, 0, 1}; // Point at origin
    t_tuple ray_direction = {0, 0, 1, 0}; // Direction along z-axis

    t_ray *test_ray = create_ray(ray_origin, ray_direction);

    t_sphere test_sphere;
    test_sphere.x = 0;
    test_sphere.y = 0;
    test_sphere.z = 5; // Center of sphere at (0, 0, 5)
    test_sphere.diameter = 2.0; // Diameter of 2.0

    // Create a shape for the sphere
    t_shape shape;
    shape.type = sphere;
    shape.sphere = &test_sphere;

    // Call the intersect function
    t_intersection *intersections = intersect(test_ray, &test_sphere);

    // Verify the results
    if (intersections == NULL)
    {
        printf("No intersections found\n");
    }
    else
    {
        int count = 0;
        t_intersection *current = intersections;
        while (current != NULL)
        {
            printf("Intersection %d: t = %f\n", count + 1, current->t);
            current = current->next;
            count++;
        }
        printf("Total intersections found: %d\n", count);
    }

    // Free the allocated memory
    t_intersection *current = intersections;
    while (current != NULL)
    {
        t_intersection *next = current->next;
        free(current);
        current = next;
    }

    // Free the test ray memory
    free(test_ray);
}

// Test function for ray-sphere non-intersection
void test_ray_sphere_no_intersection()
{
    // Define and initialize test ray and sphere
    t_tuple ray_origin = {0, 0, 0, 1}; // Point at origin
    t_tuple ray_direction = {1, 0, 0, 0}; // Direction along the x-axis

    t_ray *test_ray = create_ray(ray_origin, ray_direction);

    t_sphere test_sphere;
    test_sphere.x = 0;
    test_sphere.y = 5; // Move the sphere along the y-axis
    test_sphere.z = 0;
    test_sphere.diameter = 2.0; // Diameter of 2.0

    // Create a shape for the sphere
    t_shape shape;
    shape.type = sphere;
    shape.sphere = &test_sphere;

    // Call the intersect function
    t_intersection *intersections = intersect(test_ray, &test_sphere);

    // Verify the results
    if (intersections == NULL)
    {
        printf("No intersections found\n");
    }
    else
    {
        int count = 0;
        t_intersection *current = intersections;
        while (current != NULL)
        {
            printf("Intersection %d: t = %f\n", count + 1, current->t);
            current = current->next;
            count++;
        }
        printf("Total intersections found: %d\n", count);
    }

    // Free the allocated memory
    t_intersection *current = intersections;
    while (current != NULL)
    {
        t_intersection *next = current->next;
        free(current);
        current = next;
    }

    // Free the test ray memory
    free(test_ray);
}
// Test function for ray intersecting multiple spheres
void test_ray_multiple_spheres_intersection()
{
    // Define and initialize test ray
    t_tuple ray_origin = {0, 0, 0, 1}; // Point at origin
    t_tuple ray_direction = {0, 0, 1, 0}; // Direction along the z-axis

    t_ray *test_ray = create_ray(ray_origin, ray_direction);

    // Define and initialize multiple spheres
    t_sphere spheres[5];
    for (int i = 0; i < 5; i++)
    {
        spheres[i].x = 0;
        spheres[i].y = 0;
        spheres[i].z = 5 + (i * 10); // Place each sphere 10 units apart along the z-axis
        spheres[i].diameter = 2.0; // Diameter of 2.0
    }

    // Create shapes for each sphere
    t_shape shapes[5];
    for (int i = 0; i < 5; i++)
    {
        shapes[i].type = sphere;
        shapes[i].sphere = &spheres[i];
    }

    // Collect all intersections
    t_intersection *head = NULL;
    for (int i = 0; i < 5; i++)
    {
        t_intersection *intersections = intersect(test_ray, &spheres[i]);
        while (intersections != NULL)
        {
            t_intersection *next = intersections->next;
            add_node(&head, intersections);
            intersections = next;
        }
    }

    // Verify the results
    if (head == NULL)
    {
        printf("No intersections found\n");
    }
    else
    {
        int count = 0;
        t_intersection *current = head;
        while (current != NULL)
        {
            printf("Intersection %d: t = %f\n", count + 1, current->t);
            current = current->next;
            count++;
        }
        printf("Total intersections found: %d\n", count);
    }

    // Free the allocated memory
    t_intersection *current = head;
    while (current != NULL)
    {
        t_intersection *next = current->next;
        free(current);
        current = next;
    }

    // Free the test ray memory
    free(test_ray);
}


void test_intersection_encapsulates_t_and_object()
{
    t_sphere sphere1;
    sphere1.x = 0;
    sphere1.y = 0;
    sphere1.z = 0;
    sphere1.diameter = 2.0;

    t_shape shape;
    shape.type = sphere;
    shape.sphere = &sphere1;

    t_intersection i = {3.5, &shape, NULL};

    printf("Test: Intersection Encapsulates t and Object\n");
    printf("i.t = %f, expected = 3.5\n", i.t);
    printf("i.shape = %p, expected = %p\n", (void*)i.shape, (void*)&shape);
}
void test_aggregating_intersections()
{
    t_sphere sphere1;
    sphere1.x = 0;
    sphere1.y = 0;
    sphere1.z = 0;
    sphere1.diameter = 2.0;

    t_shape shape;
    shape.type = sphere;
    shape.sphere = &sphere1;

    t_intersection i1 = {1, &shape, NULL};
    t_intersection i2 = {2, &shape, NULL};

    t_intersection* xs = NULL;
    add_node(&xs, &i2);
    add_node(&xs, &i1);

    printf("Test: Aggregating Intersections\n");
    printf("xs.count = %d, expected = 2\n", count_nodes(xs));
    printf("xs[0].t = %f, expected = 1\n", xs->t);
    printf("xs[1].t = %f, expected = 2\n", xs->next->t);
}

void test_intersect_sets_object()
{
    t_tuple ray_origin = {0, 0, -5, 1};
    t_tuple ray_direction = {0, 0, 1, 0};
    t_ray *r = create_ray(ray_origin, ray_direction);

    t_sphere sphere1;
    sphere1.x = 0;
    sphere1.y = 0;
    sphere1.z = 0;
    sphere1.diameter = 2.0;

    t_shape shape;
    shape.type = sphere;
    shape.sphere = &sphere1;

    t_intersection* xs = intersect(r, &sphere1);

    printf("Test: Intersect Sets the Object on the Intersection\n");
    printf("xs.count = %d, expected = 2\n", count_nodes(xs));
    if (xs != NULL)
    {
        printf("xs[0].object = %p, expected = %p\n", (void*)xs->shape->sphere, (void*)&sphere1);
        printf("xs[1].object = %p, expected = %p\n", (void*)xs->next->shape->sphere, (void*)&sphere1);

        if (xs->shape->sphere == &sphere1 && xs->next->shape->sphere == &sphere1)
        {
            printf("Intersect function set the objects correctly\n");
        }
        else
        {
            printf("Intersect function did not set the objects correctly\n");
        }
    }

    // Free the allocated memory
    t_intersection* current = xs;
    while (current != NULL)
    {
        t_intersection* next = current->next;
        free(current);
        current = next;
    }
    free(r);
}
t_intersection* hit(t_intersection* inter)
{
    t_intersection* current;
    t_intersection* hit;

    current = inter;
    hit = NULL;
    while (current != NULL)
    {
        if (current->t >= 0 && (hit == NULL || current->t < hit->t))
            hit = current;
        current = current->next;
    }
    return hit;
} 

void test_hit_some_negative()
{
    t_sphere sphere1;
    sphere1.x = 0;
    sphere1.y = 0;
    sphere1.z = 0;
    sphere1.diameter = 2.0;

    t_shape shape;
    shape.type = sphere;
    shape.sphere = &sphere1;

    t_intersection i1 = {-1, &shape, NULL};
    t_intersection i2 = {1, &shape, NULL};
    
    t_intersection* xs = NULL;
    add_node(&xs, &i2);
    add_node(&xs, &i1);

    t_intersection* i = hit(xs);

    printf("Test: The hit, when some intersections have negative t\n");
    printf("Hit: t = %f, expected = 1.0\n", i->t);
    printf("Hit: object = %p, expected = %p\n", (void*)i->shape->sphere, (void*)&sphere1);
}
void test_hit_all_negative()
{
    t_sphere sphere1;
    sphere1.x = 0;
    sphere1.y = 0;
    sphere1.z = 0;
    sphere1.diameter = 2.0;

    t_shape shape;
    shape.type = sphere;
    shape.sphere = &sphere1;

    t_intersection i1 = {-2, &shape, NULL};
    t_intersection i2 = {-1, &shape, NULL};
    
    t_intersection* xs = NULL;
    add_node(&xs, &i2);
    add_node(&xs, &i1);

    t_intersection* i = hit(xs);

    printf("Test: The hit, when all intersections have negative t\n");
    printf("Hit: %p, expected = NULL\n", (void*)i);
}
void test_hit_lowest_nonnegative()
{
    t_sphere sphere1;
    sphere1.x = 0;
    sphere1.y = 0;
    sphere1.z = 0;
    sphere1.diameter = 2.0;

    t_shape shape;
    shape.type = sphere;
    shape.sphere = &sphere1;

    t_intersection i1 = {5, &shape, NULL};
    t_intersection i2 = {7, &shape, NULL};
    t_intersection i3 = {-3, &shape, NULL};
    t_intersection i4 = {2, &shape, NULL};
    
    t_intersection* xs = NULL;
    add_node(&xs, &i4);
    add_node(&xs, &i3);
    add_node(&xs, &i2);
    add_node(&xs, &i1);

    t_intersection* i = hit(xs);

    printf("Test: The hit is always the lowest nonnegative intersection\n");
    printf("Hit: t = %f, expected = 2.0\n", i->t);
    printf("Hit: object = %p, expected = %p\n", (void*)i->shape->sphere, (void*)&sphere1);
}

int main()
{
    // test_hit_some_negative();
    // test_hit_all_negative();
    test_hit_lowest_nonnegative();
    return 0;
}
