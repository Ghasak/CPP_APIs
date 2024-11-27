

void PointTypicalStructTesting();

/**
 * @brief A struct representing a 2D point with verbose constructors and destructors.
 */
struct Point2D {
    double x;
    double y;
    bool verbose;

    /**
     * @brief Constructor for Point2D struct
     *
     * @param x `double`     : The x-coordinate of the point.
     * @param y `double`     : The y-coordinate of the point.
     * @param verbose `bool` :  if true, constructor message will be printed.
     */
    Point2D(double x, double y, bool verbose = false);

    /**
     * @brief Copy Constructor for  Point2D sturct
     *
     * @param other `Point2D`: The point-object to be moved.
     */
    Point2D(const Point2D& other);
};


void meaning_of_pointers();
