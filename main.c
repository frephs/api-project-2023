/*==============================================================================*/
/*                                LIBRARIES                               */
/*==============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*==============================================================================*/
/*                                CONSTANTS                               */
/*==============================================================================*/

#define RED 'R' //0
#define BLACK 'B' //1

/*==============================================================================*/
/*                                DATA STRUCTURES                               */
/*==============================================================================*/

//TODO OPT find an optimization to store the color (hide it in the pointer of the KEY, their pointers are all even)

typedef struct rbt_node_ {
    struct rbt_node_* left;
    struct rbt_node_* right;
    struct rbt_node_* parent;
    char color;
}rbt_node_t;

typedef struct list_node_ {
    struct list_node_* next;
}list_node_t;

typedef struct car_ {
    rbt_node_t node;
    int32_t autonomy;
}car_t;

typedef struct station_ {
    rbt_node_t node;
    int32_t distance;
    int32_t maxAutonomy;
    car_t* cars;
}station_t;

typedef struct route_ {
    list_node_t node;
    int32_t distance;
}route_t;

typedef struct route_cache_ {
    rbt_node_t node;
    int32_t from;
    int32_t steps;
    route_t* route;
} route_cache_t;

// Define T_nils and L_nils;
//* TREES
rbt_node_t* T_nil = NULL;
station_t* T_nil_station = NULL;
car_t* T_nil_car = NULL;
route_cache_t* T_nil_route_cache = NULL;

//* LISTS
route_t* L_nil_route = NULL;
list_node_t* L_nil_list = NULL;

/*==============================================================================*/
/*                                FUNCTION PROTOTYPES                           */
/*==============================================================================*/
//? DATA STRUCTURES
//* RBTs
rbt_node_t* rbtLeftRotateNode(rbt_node_t* t, rbt_node_t* x);
rbt_node_t* rbtRightRotateNode(rbt_node_t* t, rbt_node_t* x);
rbt_node_t* rbtInsertNode(rbt_node_t* t, rbt_node_t* z, int rbtCompareNodes(rbt_node_t* a, rbt_node_t* b), int* alreadyPresent);
rbt_node_t* rbtInsertNodeFixup(rbt_node_t* t, rbt_node_t* z);
rbt_node_t* rbtDeleteNode(rbt_node_t* t, rbt_node_t* z);
rbt_node_t* rbtDeleteNodeFixup(rbt_node_t* t, rbt_node_t* x);
rbt_node_t* rbtTransplant(rbt_node_t* t, rbt_node_t* u, rbt_node_t* v);
rbt_node_t* rbtMinimum(rbt_node_t* t);
rbt_node_t* rbtMaximum(rbt_node_t* t);
rbt_node_t* rbtSearchNode(rbt_node_t* t, int32_t key, int rbtCompareKeys(rbt_node_t* a, int32_t key));
rbt_node_t* rbtFindPredecessor(rbt_node_t* t, int32_t rbtCompareNodes(rbt_node_t* a, rbt_node_t* b));
rbt_node_t* rbtFindSuccessor(rbt_node_t* x, int32_t rbtCompareNodes(rbt_node_t* a, rbt_node_t* b));
rbt_node_t* rbtFindMostDistantSuccessor(rbt_node_t* a, rbt_node_t* b, int32_t autonomy);
rbt_node_t* rbtFindMostDistantPredecessor(rbt_node_t* a, rbt_node_t* b, int32_t autonomy);
rbt_node_t* rbtDestroy(rbt_node_t* t);
void rbtVisualizeInOrder(rbt_node_t* t, void printNode(rbt_node_t* t, char color));

//* LINKED LISTs
list_node_t* listInsertHead(list_node_t* n, list_node_t* h);
void listDestroy(list_node_t* h);

//* DEBUGGING AND VISUALIZATION
void stationPrint(rbt_node_t* t, char color);
void carPrint(rbt_node_t* t, char color);
void routePrint(route_t* r);

//? UPDATING DATA STRUCTURES
// Helper functions: they end with _ and deal with the data structure and data insertion and removal; 
// Stations
//* INSERTING AND REMOVING STATIONS and cars
int32_t stationCompare(rbt_node_t* a, rbt_node_t* b);
int32_t stationKeyCompare(rbt_node_t* a, int32_t distance);
int32_t getStationDistance(rbt_node_t* t);

station_t* stationCreate_(int32_t distance);
station_t* stationAdd_(station_t* t, int32_t distance, station_t** insertedStation, int* alreadyPresent);
station_t* stationSearch_(station_t* t, int32_t key);
station_t* stationRemove_(station_t* t, int32_t distance, int* present);

//* INSERTING AND REMOVING CARS
int32_t carCompare(rbt_node_t* a, rbt_node_t* b);
int32_t carKeyCompare(rbt_node_t* a, int32_t distance);

car_t* carParkCreate();
car_t* carCreate_(int32_t autonomy);
car_t* carSearch_(car_t* t, int32_t key);

void carAdd_(station_t* t, int32_t distance, int32_t autonomy, int* couldAdd);
void carRemove_(station_t* t, int32_t distance, int32_t autonomy, int* present);
void carRemoveAll_(station_t* s);


//? I/O HANDLING
//TODO Add input errors handling
// for code transparency i separated the actual functions that deal with input parsing
//* INPUT PARSING STATIONS
station_t* addStation(station_t* t);
station_t* removeStation(station_t* t);

//* INPUT PARSING CARS
void addCar(station_t* t);
void removeCar(station_t* t);

//* INPUT PARSING ROUTE PLANNING
void planRoute(station_t* t);

//* COMMAND PARSING MODULES  
station_t* parseCommand(station_t* t, char command);
station_t* addStationOrCar(station_t* t);

//* HELPER FUNCTIONS
void skipToChar(char c);


//? ROUTE PLANNING
//* I/O
void routePlan_(station_t* t, int32_t distanceA, int32_t distanceB);
void routePrint(route_t* r);

//* ROUTE DATA STRUCTURE
route_t* routeCreate_(station_t* station);
route_t* routeAdd_(route_t* route, station_t* station);
void routeRemove_(route_t* r);

//* MoVING ACROSS THE MOTORWAT
station_t* stationFindSuccessor(station_t* x);
station_t* stationFindPredecessor(station_t* x);

station_t* stationFindBestFurthest(station_t* a, station_t* b);
station_t* stationFindBestFurthestReverse(station_t* stationA, station_t* stationB);

//*ROUTE FINDING
void routeFind_(route_t** route, station_t* stationA, station_t* stationB);
int32_t routeFindReverse_(route_t** route, station_t* stationA, station_t* stationB);
void routeFindReverseFixup_(route_t* route, station_t* stationA);


/*==============================================================================*/
/*                                RBT FUNCTIONS                               */
/*==============================================================================*/
// Implemented from the Cormen manual --by hand-- 
// Not responsible for memory deallocation (the exercise is left to the user lmao)
// RBT IMPLEMENTATION
// T.NIL as a sentinelle (as global perchè sì.)

rbt_node_t* rbtLeftRotateNode(rbt_node_t* t, rbt_node_t* x) {
    rbt_node_t* y;
    y = x->right;
    x->right = y->left;
    if (y->left != T_nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == T_nil) {
        t = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return t;
}

rbt_node_t* rbtRightRotateNode(rbt_node_t* t, rbt_node_t* x) {
    rbt_node_t* y;
    y = x->left;
    x->left = y->right;
    if (y->right != T_nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == T_nil) {
        t = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    return t;
}

//DONE non esistono stazioni duplicate, fixare inserzione di key già esistente uguale;

rbt_node_t* rbtInsertNode(rbt_node_t* t, rbt_node_t* z, int rbtCompareNodes(rbt_node_t* a, rbt_node_t* b), int* alreadyPresent) {
    rbt_node_t* x, * y;
    int32_t delta;
    x = t;
    y = T_nil;
    while (x != T_nil) {
        y = x;
        if (rbtCompareNodes(z, x) < 0) {
            x = x->left;
        } else if (rbtCompareNodes(z, x) == 0 && alreadyPresent == 0) {
            // printf("already present\n");
            *alreadyPresent = 1;
            return t;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == T_nil) {
        t = z;
    } else {
        delta = rbtCompareNodes(z, y);
        if (delta < 0) {
            y->left = z;
        } else if (!delta) {
            z->left = y;
            t = rbtInsertNodeFixup(t, y);
            return t;
        } else {
            y->right = z;
        }
    }
    z->left = T_nil;
    z->right = T_nil;
    z->color = RED;
    // rbVisualizeInOrderStation(t);
    // printf("\n Fix\n");
    t = rbtInsertNodeFixup(t, z);
    return t;
}

rbt_node_t* rbtInsertNodeFixup(rbt_node_t* t, rbt_node_t* z) {
    rbt_node_t* y;
    while (z->parent != T_nil && z->parent->parent != T_nil && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            //aggiunto un controllo
            if (y != T_nil && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    t = rbtLeftRotateNode(t, z);
                }
                z->parent->color = RED;
                z->parent->parent->color = RED;
                t = rbtRightRotateNode(t, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y != T_nil && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    t = rbtRightRotateNode(t, z);
                }
                z->parent->color = RED;
                z->parent->parent->color = RED;
                t = rbtLeftRotateNode(t, z->parent->parent);
            }
        }
    }
    t->color = BLACK;
    return t;
}

//* z is the node to delete, you have to search it first
rbt_node_t* rbtDeleteNode(rbt_node_t* t, rbt_node_t* z) {
    rbt_node_t* y;
    rbt_node_t* x;
    char y_original_color;
    y = z;
    y_original_color = y->color;
    if (z->left == T_nil) {
        x = z->right;
        t = rbtTransplant(t, z, z->right);
    } else if (z->right == T_nil) {
        x = z->left;
        t = rbtTransplant(t, z, z->left);
    } else {
        y = rbtMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y != T_nil && y != z->right) {
            t = rbtTransplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        } else if (x != T_nil) {
            x->parent = y;
        }
        t = rbtTransplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (x != T_nil && y_original_color == BLACK) {
        t = rbtDeleteNodeFixup(t, x);
    }
    return t;
}

rbt_node_t* rbtDeleteNodeFixup(rbt_node_t* t, rbt_node_t* x) {
    rbt_node_t* w;
    w = x;
    while (w != T_nil && w->right != T_nil && w->left != T_nil && x != T_nil && x->parent != T_nil && x->left != T_nil && x->right != T_nil && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w != T_nil && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                t = rbtLeftRotateNode(t, x->parent);
                w = x->parent->right;
            }
            if (w != T_nil && w->left != T_nil && w->right != T_nil && w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else if (w != T_nil && w->right != T_nil && w->left != T_nil) {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    t = rbtRightRotateNode(t, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                t = rbtLeftRotateNode(t, x->parent);
                x = t;
            }
        } else {
            w = x->parent->left;
            if (w != T_nil && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                t = rbtRightRotateNode(t, x->parent);
                w = x->parent->left;
            }
            if (w != T_nil && w->right != T_nil && w->left != T_nil && w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else  if (w != T_nil && w->right != T_nil && w->left != T_nil) {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    t = rbtLeftRotateNode(t, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                t = rbtRightRotateNode(t, x->parent);
                x = t;
            }
        }
    }
    if (x != T_nil)
        x->color = BLACK;
    return t;
}

rbt_node_t* rbtTransplant(rbt_node_t* t, rbt_node_t* u, rbt_node_t* v) {
    if (u != T_nil) {
        if (u->parent == T_nil) {
            t = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != T_nil) {
            v->parent = u->parent;
        }
    }
    return t;
}

//* Will return T_nil if not found;
rbt_node_t* rbtSearchNode(rbt_node_t* t, int32_t key, int32_t rbtCompareKeys(rbt_node_t* a, int32_t key)) {
    int32_t delta;
    if (t != T_nil) {
        delta = rbtCompareKeys(t, key);
        if (delta > 0) {
            return rbtSearchNode(t->right, key, rbtCompareKeys);
        } else if (delta < 0) {
            return rbtSearchNode(t->left, key, rbtCompareKeys);
        } else {
            return t;
        }
    } else {
        return t;
    }
}

rbt_node_t* rbtMinimum(rbt_node_t* t) {
    while (t->left != T_nil) {
        t = t->left;
    }
    return t;
}

rbt_node_t* rbtMaximum(rbt_node_t* t) {
    while (t->right != T_nil) {
        t = t->right;
    }
    return t;
}


rbt_node_t* rbtFindPredecessor(rbt_node_t* x, int32_t rbtCompareNodes(rbt_node_t* a, rbt_node_t* b)) {
    rbt_node_t* y;
    rbt_node_t* original_x;
    original_x = x;
    if (x->left != T_nil) {
        return rbtMaximum(x->left);
    } else {
        y = x->parent;
        while (y != T_nil && x == y->left) {
            x = y;
            y = y->parent;
        }
        //return y;
        return (y != T_nil && rbtCompareNodes(y, original_x) < 0) ? y : original_x;
    }
}

rbt_node_t* rbtFindSuccessor(rbt_node_t* x, int32_t rbtCompareNodes(rbt_node_t* a, rbt_node_t* b)) {
    rbt_node_t* y;
    rbt_node_t* original_x;
    original_x = x;

    if (x->right != T_nil) {
        return rbtMinimum(x->right);
    } else {
        y = x->parent;
        while (y != T_nil && x == y->right) {
            x = y;
            y = y->parent;
        }
        // return y;
        return (y != T_nil && rbtCompareNodes(y, original_x) > 0) ? y : original_x;
    }
}

rbt_node_t* rbtDestroy(rbt_node_t* t) {
    if (t != T_nil) {
        t->left = rbtDestroy(t->left);
        t->right = rbtDestroy(t->right);
        free(t);
        //^ Removed casting to (car_t* here) is it memory safe?
    }
    return T_nil;
}

/*==============================================================================*/
/*                                LINKED LISTS                                  */
/*==============================================================================*/

list_node_t* listInsertHead(list_node_t* n, list_node_t* h) {
    list_node_t* newH;
    newH = n;
    if (h != L_nil_list)
        while (n->next != L_nil_list) {
            n = n->next;
        }
    n->next = h;
    return newH;
}

void listDestroy(list_node_t* h) {
    if (h != L_nil_list) {
        listDestroy(h->next);
        free(h);
        //^ Removed casting to (route_t* here) is it memory safe?
    }
}

/*==============================================================================*/
/*                                VISUALIZATION                               */
/*==============================================================================*/

// VISUALIZATION AND DEBUGGING
void rbtVisualizeInOrder(rbt_node_t* t, void printNode(rbt_node_t* t, char color)) {
    if (t != T_nil) {
        rbtVisualizeInOrder(t->left, printNode);
        printNode(t, t->color);
        rbtVisualizeInOrder(t->right, printNode);
    } else {
        printf("  T ");
    }
    return;
}

void stationPrint(rbt_node_t* t, char color) {
    printf("%5d%c:%d", ((station_t*)t)->distance, (color == 'R') ? 'R' : 'B', ((station_t*)t)->maxAutonomy);
}

void carPrint(rbt_node_t* t, char color) {
    printf("%5d%c ", ((car_t*)t)->autonomy, (color == 'R') ? 'R' : 'B');
}

void routePrint(route_t* r) {
    if (r != L_nil_route) {
        printf("%d", r->distance);
        if (r->node.next != (list_node_t*)L_nil_route) {
            printf(" ");
        }
        routePrint((route_t*)r->node.next);
    }
}



/*==============================================================================*/
/*                                HELPER FUNCTIONS                                          */
/*==============================================================================*/

// Input parsing     helper: 
void skipToChar(char c) {
    char command;
    command = getchar_unlocked();
    while (command != c) {
        command = getchar_unlocked();
    }
    return;
}


// COMPARING FUNCTIONS 
// pass them as function pointers to generalized rbt methods

int32_t stationCompare(rbt_node_t* a, rbt_node_t* b) {
    return ((station_t*)a)->distance - ((station_t*)b)->distance;
}

int32_t stationKeyCompare(rbt_node_t* a, int32_t distance) {
    return distance - ((station_t*)a)->distance;
}

int32_t carCompare(rbt_node_t* a, rbt_node_t* b) {
    return ((car_t*)a)->autonomy - ((car_t*)b)->autonomy;
}

int32_t carKeyCompare(rbt_node_t* a, int32_t autonomy) {
    return autonomy - ((car_t*)a)->autonomy;
}

int32_t getStationDistance(rbt_node_t* t) {
    return ((station_t*)t)->distance;
}



/*==============================================================================*/
/*                                 UPDATING STATION'S DATA STRUCTURES                                          */
/*==============================================================================*/



station_t* stationCreate_(int32_t distance) {
    station_t* z;
    rbt_node_t* t;

    z = (station_t*)malloc(sizeof(station_t));
    t = (rbt_node_t*)z;

    t->left = T_nil;
    t->right = T_nil;
    t->color = RED;

    z->maxAutonomy = 0;
    z->distance = distance;
    z->cars = T_nil_car;
    return z;
}

station_t* stationAdd_(station_t* t, int32_t distance, station_t** insertedStation, int* alreadyPresent) {
    station_t* foundStation;
    *insertedStation = stationCreate_(distance);
    foundStation = stationSearch_(t, distance);
    
    if (foundStation != T_nil_station) {
        *alreadyPresent = 1;
        free(*insertedStation);
    } else {
        t = (station_t*)rbtInsertNode((rbt_node_t*)t, (rbt_node_t*)*insertedStation, stationCompare, alreadyPresent);
    }
    return (station_t*)t;
}

station_t* stationSearch_(station_t* t, int32_t key) {
    return (station_t*)rbtSearchNode((rbt_node_t*)t, key, stationKeyCompare);
}

station_t* stationRemove_(station_t* t, int32_t distance, int* present) {
    station_t* toBeFreed;
    toBeFreed = stationSearch_(t, distance);
    if (toBeFreed != T_nil_station) {
        t = (station_t*)rbtDeleteNode((rbt_node_t*)t, (rbt_node_t*)toBeFreed);
        carRemoveAll_(toBeFreed);
        free(toBeFreed);
    } else {
        *present = 0;
    }
    return t;
}

/*==============================================================================*/
/*                                 UPDATING CARS' DATA STRUCTURES                                          */
/*==============================================================================*/

car_t* carParkCreate() {
    return T_nil_car;
}

car_t* carCreate_(int32_t autonomy) {
    car_t* z;
    rbt_node_t* t;

    z = (car_t*)malloc(sizeof(car_t));
    t = (rbt_node_t*)z;

    t->left = T_nil;
    t->right = T_nil;
    t->color = RED;

    z->autonomy = autonomy;
    return z;
}

void carAdd_(station_t* t, int32_t distance, int32_t autonomy, int* couldAdd) {
    station_t* s;
    int alreadyPresent;
    s = stationSearch_(t, distance);
    if (s != T_nil_station) {
        if (autonomy > s->maxAutonomy) {
            s->maxAutonomy = autonomy;
        }
        alreadyPresent = -1;
        s->cars = (car_t*)rbtInsertNode((rbt_node_t*)s->cars, (rbt_node_t*)carCreate_(autonomy), carCompare, &alreadyPresent);
    } else {
        *couldAdd = 0;
    }
    return;
}

car_t* carSearch_(car_t* t, int32_t key) {
    return (car_t*)rbtSearchNode((rbt_node_t*)t, key, carKeyCompare);
}

void carRemove_(station_t* t, int32_t distance, int32_t autonomy, int* present) {
    station_t* s;
    car_t* toBeFreed;
    s = stationSearch_(t, distance);
    if (s != T_nil_station) {

        toBeFreed = carSearch_(s->cars, autonomy);
        if (toBeFreed != T_nil_car) {
            s->cars = (car_t*)rbtDeleteNode((rbt_node_t*)s->cars, (rbt_node_t*)toBeFreed);
            free(toBeFreed);
        } else {
            *present = 0;
        }
        if (autonomy == s->maxAutonomy) {
            if (s->cars != T_nil_car) {
                s->maxAutonomy = ((car_t*)rbtMaximum((rbt_node_t*)s->cars))->autonomy;
            } else {
                s->maxAutonomy = 0;
            }
        }
    } else {
        *present = 0;
    }
    return;
}

void carRemoveAll_(station_t* s) {
    s->cars = (car_t*)rbtDestroy((rbt_node_t*)s->cars);
}

/*==============================================================================*/
/*                                 COLLECTING DATA                                          */
/*==============================================================================*/


station_t* addStation(station_t* t) {

    int alreadyPresent, couldAddCar;
    int32_t n_cars, distance, autonomy, i;
    station_t* s;

    alreadyPresent = 0;
    couldAddCar = 1;
    skipToChar(' ');
    (void)!scanf("%d %d", &distance, &n_cars);

    t = stationAdd_(t, distance, &s, &alreadyPresent);

    if (!alreadyPresent) {

        for (i = 0;i < n_cars;i++) {
            (void)!scanf("%d", &autonomy);
            carAdd_(s, distance, autonomy, &couldAddCar);
        }

        printf("aggiunta\n");
    } else {
        printf("non aggiunta\n");
    }
    return t;
}


station_t* removeStation(station_t* t) {
    int present;
    int32_t distance;
    skipToChar(' ');
    (void)!scanf("%d", &distance);
    present = 1;
    t = stationRemove_(t, distance, &present);
    if (present) {
        printf("demolita\n");
    } else {
        printf("non demolita\n");
    }
    return t;
}

void addCar(station_t* t) {
    int32_t distance, autonomy;
    int couldAdd;

    skipToChar(' ');
    (void)!scanf("%d %d", &distance, &autonomy);

    couldAdd = 1;
    carAdd_(t, distance, autonomy, &couldAdd);

    if (couldAdd) {
        printf("aggiunta\n");
    } else {
        printf("non aggiunta\n");
    }
    return;
}


void removeCar(station_t* t) {
    int present;
    int32_t distance, autonomy;

    skipToChar(' ');
    (void)!scanf("%d %d", &distance, &autonomy);

    present = 1;
    carRemove_(t, distance, autonomy, &present);
    if (present) {
        printf("rottamata\n");
    } else {
        printf("non rottamata\n");
    }

}


/*==============================================================================*/
/*                                  UPDATING ROUTE DATA STRUCTURE                                          */
/*==============================================================================*/
route_t* routeCreate_(station_t* station) {
    route_t* r;

    r = malloc(sizeof(route_t));
    r->node.next = (list_node_t*)L_nil_route;
    r->distance = station->distance;
    return r;
}

route_t* routeAdd_(route_t* route, station_t* station) {
    return (route_t*)listInsertHead((list_node_t*)routeCreate_(station), (list_node_t*)route);
}

void routeRemove_(route_t* r) {
    if (r != L_nil_route) {
        listDestroy((list_node_t*)r);
    }
}

/*==============================================================================*/
/*                                MOVING THROUGH THE MOTORWAY                                          */
/*==============================================================================*/
station_t* stationFindSuccessor(station_t* x) {
    return (station_t*)rbtFindSuccessor((rbt_node_t*)x, stationCompare);
}

station_t* stationFindPredecessor(station_t* x) {
    return (station_t*)rbtFindPredecessor((rbt_node_t*)x, stationCompare);
}

station_t* stationFindBestFurthest(station_t* stationA, station_t* stationB) {
    station_t* current, * next, * best;
    next = stationA;
    best = T_nil_station;
    
    do {
        current = next;
        next = stationFindSuccessor(current);
        best = (current->distance + current->maxAutonomy >= stationB->distance) ? current : best;
    } while (best == T_nil_station);

    return best;
}

station_t* stationFindBestFurthestReverse(station_t* stationA, station_t* stationB) {
    station_t* current, * next, * best;
    int32_t min_distance = stationA->distance - stationA->maxAutonomy;

    if (min_distance <= stationB->distance) {
        return stationB;
    }

    best = next = stationA;
    
    do {
        current = next;
        next = stationFindPredecessor(current);
        best = (current->distance - current->maxAutonomy <= best->distance - best->maxAutonomy) ? current : best;
    } while (next != T_nil_station && next->distance >= min_distance);

    return best;
}


/*==============================================================================*/
/*                                ROUTE FINDING                                          */
/*==============================================================================*/
void planRoute(station_t* t) {
    int32_t distanceA, distanceB;

    skipToChar(' ');
    (void)!scanf("%d %d", &distanceA, &distanceB);

    routePlan_(t, distanceA, distanceB);

}

void routePlan_(station_t* t, int32_t distanceA, int32_t distanceB) {
    station_t* stationA, * stationB;
    route_t* r;
    r = L_nil_route;
    int32_t steps;
    
    steps = 0;
    
    // handling degenerate routes
    if (distanceA == distanceB) {
        printf("%d\n", distanceA);
        return;
    }

    // looking for the stations
    stationA = stationSearch_(t, distanceA);
    stationB = stationSearch_(t, distanceB);

    // rbtVisualizeInOrder((rbt_node_t*)t, stationPrint);

    if (stationA == T_nil_station || stationB == T_nil_station) {
        printf("nessun percorso\n");
        return;
    }

    if (distanceA < distanceB) {
        routeFind_(&r, stationA, stationB);
        if (r->distance != stationB->distance) {
            r = routeAdd_(r, stationA);
            steps = 1;
        }
    } else {
        steps = routeFindReverse_(&r, stationA, stationB);
        r = routeAdd_(r, stationA);
        if (r->distance != stationB->distance) {
            routeFindReverseFixup_(r, stationA);
        }
    }

    if (steps != 0 && r != L_nil_route && r->distance != stationB->distance) {
        routePrint(r);
        printf("\n");
    } else {
        printf("nessun percorso\n");
    }
    
    listDestroy((list_node_t*)r);
}

void routeFind_(route_t** route, station_t* stationA, station_t* stationB) {
    station_t* candidateStation, *reachedStation;
    candidateStation = T_nil_station;

    *route = routeAdd_(*route, stationB);
    candidateStation = stationFindBestFurthest(stationA, stationB);
    reachedStation = stationB;

    while (candidateStation != reachedStation && candidateStation != stationA) {
        *route = routeAdd_(*route, candidateStation);
        reachedStation = candidateStation;
        candidateStation = stationFindBestFurthest(stationA, reachedStation);
    }
    
    if (candidateStation == reachedStation){
        *route = routeAdd_(*route, stationB);
    }
    return;
}


int32_t routeFindReverse_(route_t** route, station_t* stationA, station_t* stationB) {
    int32_t candidateSteps = 0;
    station_t* candidateStation;

    candidateStation = stationFindBestFurthestReverse(stationA, stationB);

    if (candidateStation == stationB) {
        *route = routeAdd_(*route, stationB);
        return 1;

    } else {

        if (candidateStation != stationA) {
            candidateSteps = routeFindReverse_(route, candidateStation, stationB);
        }

        if (candidateSteps != 0) {
            *route = routeAdd_(*route, candidateStation);
            routeFindReverseFixup_(*route, candidateStation);
            return candidateSteps + 1;
        } else {
            return 0;
        }

    }
}

void routeFindReverseFixup_(route_t* route, station_t* stationA) {
    station_t* previous;
    previous = stationA;
    route = (route_t*)route->node.next;
    if (route != L_nil_route && route->node.next != L_nil_list) {

        while (stationA->distance >= route->distance) {
            stationA = stationFindPredecessor(stationA);
        }

        while (previous->distance - previous->maxAutonomy <= stationA->distance) {
            if (stationA->distance - stationA->maxAutonomy <= ((route_t*)route->node.next)->distance) {
                route->distance = stationA->distance;
            }
            stationA = stationFindPredecessor(stationA);
        }

        previous = stationFindSuccessor(stationA);
        route = (route_t*)route->node.next;
    }
    return;
}


/*==============================================================================*/
/*                                COMMAND PARSING                                          */
/*==============================================================================*/

// INPUT PARSING (Finally)

station_t* parseCommand(station_t* t, char command) {
    switch (command) {
    case 'a': t = addStationOrCar(t); break;
    case 'd': t = removeStation(t); break;
    case 'r': removeCar(t); break;
    case 'p': planRoute(t); break;
    }
    return t;
}

station_t* addStationOrCar(station_t* t) {
    char command;
    skipToChar('-');
    command = getchar_unlocked();
    switch (command) {
    case 's': t = addStation(t); break;
    case 'a': addCar(t); break;
    }
    return t;
}


/*==============================================================================*/
/*                                MAIN                                          */
/*==============================================================================*/

int main() {
    station_t* t = T_nil_station;
    int i = 0;
    char command;
    command = getchar_unlocked();

    while (command != EOF) {
        t = parseCommand(t, command);
        skipToChar('\n');
        i++;
        command = getchar_unlocked();
    }
    return 0;
}

