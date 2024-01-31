#pragma once
void classes_conccepts_hub();

class Player {
public:
    /**
     * Constructs a new Player object.
     *
     * @param x The x-coordinate of the player.
     * @param y The y-coordinate of the player.
     * @param speed The speed of the player.
     * @param verbose Flag to enable verbose logging.
     * Example: Player player(100, 200, 50, true);
     */
    explicit Player(int x, int y, int speed, bool verbose);

    /**
     * Another Constructor without any input
     *
     */
    explicit Player(bool);

    /**
     * Copy constructor.
     * Creates a new Player object as a copy of another Player object.
     *
     * @param other The Player object to copy.
     * Example: Player playerCopy = existingPlayer;
     */
    Player(const Player& other);

    /**
     * Move constructor.
     * Moves a Player object, transferring ownership of its resources.
     *
     * @param other The Player object to move.
     * Example: Player movedPlayer = std::move(existingPlayer);
     */
    Player(Player&& other) noexcept;

    /**
     * Copy assignment operator.
     * Replaces the contents of the Player object with a copy of the contents of another.
     *
     * @param other The Player object to copy.
     * @return Reference to the current object.
     * Example: player1 = player2;
     */
    Player& operator=(const Player& other);

    /**
     * Move assignment operator.
     * Replaces the contents of the Player object with those of another by moving them.
     *
     * @param other The Player object to move.
     * @return Reference to the current object.
     * Example: player1 = std::move(player2);
     */
    Player& operator=(Player&& other) noexcept;

    /**
     * Destructor for the Player class.
     * It is called when the object goes out of scope or is explicitly deleted.
     */
    ~Player();

    // Getters and Setters
    int get_x() const;
    void set_x(int x);

    int get_y() const;
    void set_y(int y);

    int get_speed() const;
    void set_speed(int speed);

    // Display Method
    void display();

private:
    int x;
    int y;
    int speed;
    bool verbose;
    static int object_count;
    static int object_count_since_starting;
    int object_id;
};
