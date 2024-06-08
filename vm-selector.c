#include <gtk/gtk.h>
#include <stdlib.h>

// Callback function to execute system commands
static void button_clicked(GtkWidget *widget, gpointer data) {
    char command[256];
    snprintf(command, sizeof(command), "ctl-%s", (char *)data);
    system(command);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *close_button;

    // Initialize GTK+
    gtk_init(&argc, &argv);

    // Create a new window, set its title and border width
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Select a VM to control");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Connect the "destroy" event to exit the GTK main loop
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a grid, center its content, and attach it to the window
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create the first button (node1) and connect it to the command execution
    button = gtk_button_new_with_label("node1");
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), "node1");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    // Create the second button (node2) and connect it to the command execution
    button = gtk_button_new_with_label("node2");
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), "node2");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

    // Create the close button
    close_button = gtk_button_new_with_label("Close");
    g_signal_connect(close_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_grid_attach(GTK_GRID(grid), close_button, 0, 1, 2, 1);

    // Show all widgets in the window
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
