#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>

int binamount[] = {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 0};
bool playerOne = true;
GtkWidget *labels[14];
GtkWidget *statusLabel;

// Update the labels for all bins with the current values
void update_board() {
    for (int i = 0; i < 14; i++) {
        char buffer[10];
        snprintf(buffer, sizeof(buffer), "%d", binamount[i]);
        gtk_label_set_text(GTK_LABEL(labels[i]), buffer);
    }

    // Update the status label to show the current player's turn
    if (playerOne) {
        gtk_label_set_text(GTK_LABEL(statusLabel), "Player 1's Turn");
    } else {
        gtk_label_set_text(GTK_LABEL(statusLabel), "Player 2's Turn");
    }
}

// Check if the game is over
void check_game_end() {
    int playerOneBins = 0;
    int playerTwoBins = 0;

    for (int i = 0; i < 6; i++) {
        playerOneBins += binamount[i];
    }

    for (int i = 7; i < 13; i++) {
        playerTwoBins += binamount[i];
    }

    // If one player's bins are empty, the game ends
    if (playerOneBins == 0 || playerTwoBins == 0) {
        for (int i = 0; i < 6; i++) {
            binamount[6] += binamount[i];  // Add remaining Player 1 stones to their Mancala
            binamount[i] = 0;
        }
        for (int i = 7; i < 13; i++) {
            binamount[13] += binamount[i]; // Add remaining Player 2 stones to their Mancala
            binamount[i] = 0;
        }
        update_board();
        gtk_label_set_text(GTK_LABEL(statusLabel), "Game Over!");
    }
}

// Game logic function called when a bin is clicked
void on_bin_clicked(GtkWidget *widget, gpointer data) {
    int binIndex = GPOINTER_TO_INT(data);

    // Check if the chosen bin belongs to the current player
    if ((playerOne && binIndex >= 0 && binIndex <= 5) || (!playerOne && binIndex >= 7 && binIndex <= 12)) {
        if (binamount[binIndex] == 0) {
            return;  // Cannot pick from an empty bin
        }

        int stones = binamount[binIndex];
        binamount[binIndex] = 0;
        int recipient = binIndex;

        while (stones > 0) {
            recipient = (recipient + 1) % 14;
            // Skip opponent's Mancala
            if ((playerOne && recipient == 13) || (!playerOne && recipient == 6)) {
                continue;
            }
            binamount[recipient]++;
            stones--;
        }

        // Capture rule: if the last stone lands in an empty bin on the player's side
        if (playerOne && recipient >= 0 && recipient <= 5 && binamount[recipient] == 1) {
            binamount[6] += binamount[12 - recipient] + 1;
            binamount[recipient] = 0;
            binamount[12 - recipient] = 0;
        } else if (!playerOne && recipient >= 7 && recipient <= 12 && binamount[recipient] == 1) {
            binamount[13] += binamount[12 - recipient] + 1;
            binamount[recipient] = 0;
            binamount[12 - recipient] = 0;
        }

        // Switch turn unless the last stone lands in the player's Mancala
        if (!(playerOne && recipient == 6) && !(playerOne == false && recipient == 13)) {
            playerOne = !playerOne;
        }

        update_board();
        check_game_end();  // Check if the game ends
    }
}

// Function to create the game board UI
void create_board(GtkWidget *grid) {
    // Row 1: Player 2's bins
    for (int i = 12; i >= 7; i--) {
        GtkWidget *button = gtk_button_new();
        g_signal_connect(button, "clicked", G_CALLBACK(on_bin_clicked), GINT_TO_POINTER(i));
        GtkWidget *label = gtk_label_new("");
        labels[i] = label;
        gtk_container_add(GTK_CONTAINER(button), label);
        gtk_grid_attach(GTK_GRID(grid), button, 12 - i + 1, 0, 1, 1);
        gtk_widget_set_size_request(button, 120, 120); // Set button size
    }

    // Player 2's Mancala (make it larger)
    GtkWidget *mancala2 = gtk_label_new("0");
    labels[13] = mancala2;
    gtk_grid_attach(GTK_GRID(grid), mancala2, 0, 0, 1, 2); // Mancala on the left
    gtk_widget_set_size_request(mancala2, 200, 250); // Set larger size for Mancala

    // Row 2: Player 1's bins
    for (int i = 0; i <= 5; i++) {
        GtkWidget *button = gtk_button_new();
        g_signal_connect(button, "clicked", G_CALLBACK(on_bin_clicked), GINT_TO_POINTER(i));
        GtkWidget *label = gtk_label_new("");
        labels[i] = label;
        gtk_container_add(GTK_CONTAINER(button), label);
        gtk_grid_attach(GTK_GRID(grid), button, i + 1, 1, 1, 1);
        gtk_widget_set_size_request(button, 120, 120); // Set button size
    }

    // Player 1's Mancala (make it larger)
    GtkWidget *mancala1 = gtk_label_new("0");
    labels[6] = mancala1;
    gtk_grid_attach(GTK_GRID(grid), mancala1, 7, 0, 1, 2); // Mancala on the right
    gtk_widget_set_size_request(mancala1, 200, 250); // Set larger size for Mancala

    // Initialize board values
    update_board();
}

// Main function to initialize GTK and create the window
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *vbox;

    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mancala Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vbox to hold the status label and grid
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Status label for displaying whose turn it is
    statusLabel = gtk_label_new("Player 1's Turn");
    gtk_box_pack_start(GTK_BOX(vbox), statusLabel, FALSE, FALSE, 0);

    // Create a grid to hold the buttons and labels
    grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    // Create the game board
    create_board(grid);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
