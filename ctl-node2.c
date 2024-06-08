#include <gtk/gtk.h>
#include <stdlib.h>

void on_status_clicked(GtkWidget *widget, gpointer label) {
    system("sudo virsh list --all | grep node2 | awk '{print $3}' > /tmp/.vm2_status.txt");
    FILE *fp = fopen("/tmp/.vm2_status.txt", "r");
    if (fp) {
        char status[100];
        fgets(status, sizeof(status), fp);
        fclose(fp);

        // Remove trailing newline character
        status[strcspn(status, "\n")] = 0;

        if (strcmp(status, "running") == 0) {
            strcpy(status, "ACTIVE");
        } else if (strcmp(status, "shut") == 0) {
            strcpy(status, "INACTIVE");
        }

        gtk_label_set_text(GTK_LABEL(label), status);
    }
}

void on_start_clicked(GtkWidget *widget, gpointer data) {
    system("sudo virsh start node2");
}

void on_reboot_clicked(GtkWidget *widget, gpointer data) {
    system("sudo virsh reset node2");
}

void on_shutdown_clicked(GtkWidget *widget, gpointer data) {
    system("sudo virsh shutdown node2");
}

void on_hard_reboot_clicked(GtkWidget *widget, gpointer data) {
    system("echo node2");
}

void on_console_clicked(GtkWidget *widget, gpointer data) {
    system("sudo virt-viewer node2");
}

void on_rebuild_clicked(GtkWidget *widget, gpointer data) {
    system("echo node2");
}

void on_close_clicked(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *status_button, *start_button, *reboot_button, *shutdown_button;
    GtkWidget *hard_reboot_button, *console_button, *rebuild_button, *close_button;
    GtkWidget *status_label;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Exam VM Control");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    status_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), status_label, 0, 0, 1, 1);

    status_button = gtk_button_new_with_label("Status node2 VM");
    g_signal_connect(status_button, "clicked", G_CALLBACK(on_status_clicked), status_label);
    gtk_grid_attach(GTK_GRID(grid), status_button, 0, 1, 1, 1);

    start_button = gtk_button_new_with_label("Start node2 VM");
    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), start_button, 0, 2, 1, 1);

    reboot_button = gtk_button_new_with_label("Reboot node2 VM");
    g_signal_connect(reboot_button, "clicked", G_CALLBACK(on_reboot_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), reboot_button, 0, 3, 1, 1);

    shutdown_button = gtk_button_new_with_label("Shutdown node2 VM");
    g_signal_connect(shutdown_button, "clicked", G_CALLBACK(on_shutdown_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), shutdown_button, 0, 4, 1, 1);

    hard_reboot_button = gtk_button_new_with_label("Hard Reboot node2 VM");
    g_signal_connect(hard_reboot_button, "clicked", G_CALLBACK(on_hard_reboot_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), hard_reboot_button, 0, 5, 1, 1);

    console_button = gtk_button_new_with_label("Console node2 VM");
    g_signal_connect(console_button, "clicked", G_CALLBACK(on_console_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), console_button, 0, 6, 1, 1);

    rebuild_button = gtk_button_new_with_label("Rebuild node2 VM");
    g_signal_connect(rebuild_button, "clicked", G_CALLBACK(on_rebuild_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), rebuild_button, 0, 7, 1, 1);

    close_button = gtk_button_new_with_label("Close");
    g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), close_button, 0, 8, 1, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
