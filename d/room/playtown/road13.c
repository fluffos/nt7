// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","青砖路");
        set("long",
"这是一条非常平整的青砖铺成的小路。周围有一小片空地，景色不错\n"
"，很适合建房。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");        
        set("exits",([
                "north" : __DIR__"road14",
                "south" : __DIR__"road12",
        ]));
        setup();
        // replace_program(ROOM);
}