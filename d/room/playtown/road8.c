// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","三岔口");
        set("long",
"你走在一条曲长的小道上，这是一个三岔口，南面是一条碎石小道西\n"
"北面和东北面有两条青砖铺成的路。\n"
);

        set("outdoors","playertown");
        set("no_clean_up",0);
        
        set("exits",([
                "northwest" : __DIR__"road9",
                "northeast" : __DIR__"road10",
                "south"        : __DIR__"road7",
                "west"        : __DIR__"road17",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}