// /d/playertown/road3.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"这是一条布满石子的小路，两边长着几颗高大的杨柳树，在小路的北\n"
"方，传来阵阵小贩的吆喝声，大概集市就在那里吧；东南面是通往村外的\n"
"路，东面的小路是深入村庄的中心。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        set("exits",([
                "east"        : __DIR__"road3",
//         "enter"  : "/data/room/chuchu/xiaoyuan",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}