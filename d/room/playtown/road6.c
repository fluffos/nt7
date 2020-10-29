// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"这是一条布满石子的小路，两边长着几颗高大的杨柳树，北面的路似\n"
"乎总是被白烟弥漫着，西南面是通往村外的路，在小路的西面赫然立着一\n"
"座小亭，里面依稀可见几个身影。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        
        set("exits",([
                "north" : __DIR__"road7",
                "south" : __DIR__"road5",
                "west" : __DIR__"road4",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}