#include <gtk/gtk.h>

static const gchar css[] =
 ".header { -GtkWidget-window-dragging: true; }";

int
main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *header;
  GtkWidget *footer;
  GtkWidget *button;
  GtkWidget *content;
  GtkCssProvider *provider;

  gtk_init (NULL, NULL);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_widget_realize (window);
  gdk_window_set_decorations (gtk_widget_get_window (window),
                              GDK_DECOR_BORDER);

  header = gtk_header_bar_new ();
  gtk_style_context_add_class (gtk_widget_get_style_context (header),
                               "header");
  provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_data (provider, css, -1, NULL);
  gtk_style_context_add_provider_for_screen (gtk_widget_get_screen (window),
                                             GTK_STYLE_PROVIDER (provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_header_bar_set_title (GTK_HEADER_BAR (header), "Example header");

  button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

  gtk_header_bar_pack_end (GTK_HEADER_BAR (header), button);

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

  gtk_container_add (GTK_CONTAINER (window), box);

  gtk_box_pack_start (GTK_BOX (box), header, FALSE, FALSE, 0);

  footer = gtk_header_bar_new ();
  gtk_header_bar_pack_start (GTK_HEADER_BAR (footer), gtk_button_new_with_label ("Start"));
  gtk_header_bar_set_custom_title (GTK_HEADER_BAR (footer), gtk_check_button_new_with_label ("Middle"));
  gtk_header_bar_pack_end (GTK_HEADER_BAR (footer), gtk_button_new_with_label ("End"));
  gtk_box_pack_end (GTK_BOX (box), footer, FALSE, FALSE, 0);

  content = gtk_image_new_from_icon_name ("start-here-symbolic", GTK_ICON_SIZE_DIALOG);
  gtk_image_set_pixel_size (GTK_IMAGE (content), 512);

  gtk_box_pack_start (GTK_BOX (box), content, FALSE, TRUE, 0);


  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}