#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int binamount[] = {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 0};
bool playerOne = true;
GtkWidget *labels[14];

// Update the labels for all bins with the current values
void update_board() {
    for (int i = 0; i < 14; i++) {
        char buffer[10];
        snprintf(buffer, sizeof(buffer), "%d", binamount[i]);
        gtk_label_set_text(GTK_LABEL(labels[i]), buffer);  // Only update the text
    }
}

// Game logic function called when a bin is clicked
void on_bin_clicked(GtkWidget *widget, gpointer data) {
    int binIndex = GPOINTER_TO_INT(data);
    int chosenBin = binIndex;
    
    // Check if it's player one's turn and the bin is in the correct range
    if (playerOne && binIndex >= 0 && binIndex <= 5) {
        chosenBin = binIndex;
    } else if (!playerOne && binIndex >= 7 && binIndex <= 12) {
        chosenBin = binIndex;
    } else {
        // Invalid move for the current player
        return;
    }

    // Check if the chosen bin is non-empty
    if (binamount[chosenBin] == 0) {
        return; // Invalid move: bin is empty
    }

    int giveawayPile = binamount[chosenBin];
    binamount[chosenBin] = 0;
    int recipient = chosenBin;

    while (giveawayPile > 0) {
        recipient = (recipient + 1) % 14;
        if ((playerOne && recipient == 13) || (!playerOne && recipient == 6)) {
            continue; // Skip opponent's mancala
        }
        binamount[recipient]++;
        giveawayPile--;
    }

    // Check last recipient and handle the game rules
    if (playerOne && recipient == 6) {
        playerOne = true;  // Player gets another turn
    } else if (!playerOne && recipient == 13) {
        playerOne = false;  // Player 2 gets another turn
    } else {
        playerOne = !playerOne;  // Switch turns
    }

    // Update the board with the new values
    update_board();
}

// Function to create the game board UI
void create_board(GtkWidget *grid) {
    // Row 1: Player 2's bins
    for (int i = 12; i >= 7; i--) {
        GtkWidget *button = gtk_button_new();  // Create button without a label
        g_signal_connect(button, "clicked", G_CALLBACK(on_bin_clicked), GINT_TO_POINTER(i));
        GtkWidget *label = gtk_label_new("");  // Create a label for the button
        labels[i] = label;  // Store the label for future updates
        gtk_container_add(GTK_CONTAINER(button), label);  // Add label to button
        gtk_grid_attach(GTK_GRID(grid), button, 12 - i, 0, 1, 1);
    }

    // Player 2's Mancala
    GtkWidget *mancala2 = gtk_label_new("0");
    labels[13] = mancala2;
    gtk_grid_attach(GTK_GRID(grid), mancala2, 6, 0, 1, 2);

    // Row 2: Player 1's bins
    for (int i = 0; i <= 5; i++) {
        GtkWidget *button = gtk_button_new();  // Create button without a label
        g_signal_connect(button, "clicked", G_CALLBACK(on_bin_clicked), GINT_TO_POINTER(i));
        GtkWidget *label = gtk_label_new("");  // Create a label for the button
        labels[i] = label;  // Store the label for future updates
        gtk_container_add(GTK_CONTAINER(button), label);  // Add label to button
        gtk_grid_attach(GTK_GRID(grid), button, i, 1, 1, 1);
    }

    // Player 1's Mancala
    GtkWidget *mancala1 = gtk_label_new("0");
    labels[6] = mancala1;
    gtk_grid_attach(GTK_GRID(grid), mancala1, 6, 1, 1, 2);

    // Initialize board values
    update_board();
}

// Main function to initialize GTK and create the window
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;

    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mancala Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a grid to hold the buttons and labels
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create the game board
    create_board(grid);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
