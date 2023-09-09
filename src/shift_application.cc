#include "shift_application.h"

/*
    -----------------------------------------------------
    |   P   |       Julia       |       Elamination     |
    |       |                   |                       |
    --------|                   |                       |
    |   Q   |                   |                       |
    |       |                   |                       |
    -----------------------------------------------------
*/


Glib::RefPtr<ShiftApplication> ShiftApplication::create(int& argc, char**& argv) {
    return Glib::RefPtr<ShiftApplication>(new ShiftApplication());
}

ShiftApplication::ShiftApplication() : Gtk::Application("org.example") {
}

void ShiftApplication::on_activate() {
    window = new Gtk::Window();
    p_area = new PQDrawingArea();
    q_area = new PQDrawingArea();
    julia_area = new JuliaDrawingArea();
    elamination_area = new ElaminationDrawingArea();

    p_area->set_name("p_area");
    q_area->set_name("q_area");
    julia_area->set_name("julia_area");
    elamination_area->set_name("elamination_area");

    p_area->set_size_request(250, 250);
    q_area->set_size_request(250, 250);
    julia_area->set_size_request(500, 500);
    elamination_area->set_size_request(500, 500);

    Gtk::Grid* grid = Gtk::manage(new Gtk::Grid());
    window->add(*grid);
    grid->attach(*p_area, 0, 0, 1, 1);
    grid->attach(*q_area, 0, 1, 1, 1);
    grid->attach(*julia_area, 1, 0, 2, 2);
    grid->attach(*elamination_area, 3, 0, 2, 2);
	grid->show_all();

    window->set_default_size(1250, 500);
    add_window(*window);
    window->show_all();
    p_area->signal_button_press_event().connect(sigc::mem_fun(*this, &ShiftApplication::on_button_press_p));
    q_area->signal_button_press_event().connect(sigc::mem_fun(*this, &ShiftApplication::on_button_press_q));
}

bool ShiftApplication::on_button_press_p(GdkEventButton* event) {
    P = static_cast<cpx>(static_cast<double>(event->x), static_cast<double>(event->y));
    a = static_cast<double>(event->x);
    b = static_cast<double>(event->y);
    P = (a-125.0)/100.0 + (b-125.0)*I/100.0;
    p_area->on_pq_set();
    q_area->on_pq_set();
    julia_area->on_pq_set();
    elamination_area->on_pq_set();
    return true;
}

bool ShiftApplication::on_button_press_q(GdkEventButton* event) {
    a = static_cast<double>(event->x);
    b = static_cast<double>(event->y);
    Q = (a-125.0)/100.0 + (b-125.0)*I/100.0;
    p_area->on_pq_set();
    q_area->on_pq_set();
    julia_area->on_pq_set();
    elamination_area->on_pq_set();
    return true;
}

void ShiftApplication::init_app_menu() {
        auto menu = Gio::Menu::create();
        menu->append("Green Mode", "app.preferences");
        menu->append("Quit", "app.quit");
        this.set_app_menu(menu);

        add_action("green", sigc::mem_fun(*this, &ShiftApplication::set_green));
        add_action("quit", sigc::mem_fun(*this, &ShiftApplication::quit));
}
