const c = @cImport({
    @cInclude("SDL3/SDL.h");
    @cInclude("app.h");
    @cInclude("border.h");
});

pub fn main() error{SDL}!void {
    const app = c.App_create("Wincord", 400, 200);
    if (app == null) {
        @import("std").log.err("Failed to initialize app, {s}", .{c.SDL_GetError()});
        return error.SDL;
    }
    defer c.App_destroy(app);

    const border = c.Border_create(app.*.ctx, 2);
    defer c.Border_destroy(border);

    c.App_setBorder(app, border);
    c.App_run(app);
}
