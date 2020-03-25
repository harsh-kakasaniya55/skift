#include <libsystem/cstring.h>

#include "Compositor/Client.h"
#include "Compositor/Manager.h"
#include "Compositor/Protocol.h"
#include "Compositor/Window.h"

Window *window_create(int id, Client *client, Rectangle bound, Bitmap *framebuffer)
{
    Window *window = __create(Window);

    window->id = id;
    window->client = client;
    window->bound = bound;
    window->framebuffer = framebuffer;

    manager_register_window(window);

    return window;
}

void window_destroy(Window *window)
{
    manager_unregister_window(window);

    free(window);
}

void window_send_event(Window *window, Event *event, size_t size)
{
    size_t message_size = sizeof(CompositorWindowEvent) + size;
    CompositorWindowEvent *message = malloc(message_size);

    message->id = window->id;
    message->header.type = COMPOSITOR_MESSAGE_WINDOW_EVENT;
    memcpy(&message->event[0], event, size);

    client_send_message(window->client, (Message *)message, message_size);

    free(message);
}

Rectangle window_bound(Window *window)
{
    return window->bound;
}
