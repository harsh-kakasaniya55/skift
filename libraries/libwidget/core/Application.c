#include <libsystem/assert.h>
#include <libsystem/eventloop/EventLoop.h>
#include <libsystem/eventloop/Notifier.h>
#include <libsystem/io/Connection.h>
#include <libsystem/io/Socket.h>
#include <libsystem/logger.h>
#include <libsystem/process/Process.h>

#include <libwidget/core/Application.h>

#include "Compositor/Protocol.h"

static bool _initialized = false;
static bool _running = false;
static List *_windows;
static Connection *_connection;
static Notifier *_connection_notifier;

void application_request_callback(Notifier *notifier, Connection *connection)
{
    __unused(notifier);

    Message header;
    connection_receive(connection, &header);

    CompositorMessage *message = malloc(header.size);
    connection_payload(connection, (Message *)message);

    if (message->type == COMPOSITOR_MESSAGE_WINDOW_EVENT)
    {
    }
    else
    {
        logger_warn("Got an invalid message from compositor!");
    }

    free(message);
}

void application_initialize(int argc, char **argv)
{
    __unused(argc);
    __unused(argv);

    logger_trace("Connecting to compositor...");
    _connection = socket_connect("/srv/compositor.ipc");

    if (handle_has_error(_connection))
    {
        logger_error("Failled to connect to the compositor: %s", handle_error_string(_connection));
        process_exit(-1);
    }
    else
    {
        logger_trace("Connected to compositor!");
    }

    assert(!_initialized);

    _windows = list_create();

    eventloop_initialize();

    _connection_notifier = notifier_create(HANDLE(_connection), SELECT_RECEIVE);
    _connection_notifier->on_ready_to_receive = (NotifierHandler)application_request_callback;

    _initialized = true;
}

int application_run(void)
{
    assert(_initialized);
    assert(!_running);

    return eventloop_run();
}

void application_exit(int exit_value)
{
    assert(_initialized);
    assert(_running);

    eventloop_exit(exit_value);
}

void application_dump(void)
{
    assert(_initialized);

    list_foreach(Widget, window, _windows)
    {
        widget_dump(window);
    }
}

void application_add_window(Window *window)
{
    assert(_initialized);

    logger_info("Adding %s(0x%08x)", WIDGET(window)->classname, window);

    CompositorCreateWindowMessage message = {
        .id = window->id,
        .framebuffer = window->framebuffer_handle,
        .bound = WIDGET(window)->bound,
    };

    message.header.type = COMPOSITOR_MESSAGE_CREATE_WINDOW;

    connection_send(_connection, (Message *)&message, sizeof(message));

    list_pushback(_windows, window);
}

void application_remove_window(Window *window)
{
    assert(_initialized);

    logger_info("Removing %s(0x%08x)", WIDGET(window)->classname, window);

    CompositorDestroyWindowMessage message = {
        .id = window->id,
    };

    message.header.type = COMPOSITOR_MESSAGE_DESTROY_WINDOW;

    connection_send(_connection, (Message *)&message, sizeof(CompositorDestroyWindowMessage));

    list_remove(_windows, window);
}

void application_blit_window(Window *window, Rectangle bound)
{
    assert(_initialized);

    logger_info("Blitting %s(0x%08x)", WIDGET(window)->classname, window);

    CompositorBlitWindowMessage message = {
        .id = window->id,
        .bound = bound,
    };

    message.header.type = COMPOSITOR_MESSAGE_BLIT_WINDOW;

    connection_send(_connection, (Message *)&message, sizeof(CompositorBlitWindowMessage));
}