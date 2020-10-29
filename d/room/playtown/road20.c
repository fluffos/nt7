// /d/playertown/road2.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"这是一条布满石子的小路，两边长着几颗高大的杨柳树，周围有一小\n"
"片空地，景色不错，非常适合建房。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        set("exits",([
                "west" : __DIR__"road19",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}