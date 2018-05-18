#include <stdbool.h>
#include <stdio.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

int pos_x;
int pos_y;
int pos_x2;
int pos_y2;

int main()
{
	bool done = false;
	bool draw = false;
	bool down = false;
	int width = 640;
	int height = 480;
	ALLEGRO_DISPLAY *display = NULL;
	if(!al_init())
		return -1;
	display = al_create_display(width, height);
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_install_mouse();
	al_install_keyboard();
	al_init_primitives_addon();
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue,al_get_mouse_event_source());
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_keyboard_event_source());


	while(!done)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type = ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1)
			{
				pos_x = ev.mouse.x;
				pos_y = ev.mouse.y;
				down = true;
			}
		}

		if(ev.type = ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if(ev.mouse.button & 1)
			{
				pos_x2 = ev.mouse.x;
				pos_y2 = ev.mouse.y;
				draw = true;
				down = false;
			}
		}
		else if(ev.type = ALLEGRO_EVENT_KEY_DOWN)
		{
			if(ev.keyboard.keycode = ALLEGRO_KEY_ESCAPE)
			{
				done = true;
			}
		}
		if(draw)
		{
			al_draw_line(pos_x,pos_y,pos_x2, pos_y2, al_map_rgb(0,0,0),5);
			al_flip_display();
			draw = false;
		}
		if(down)
		{
			al_draw_line(pos_x,pos_y,ev.mouse.x,ev.mouse.y,al_map_rgb(0,0,0),5);
			al_flip_display();
		}
	}
}
