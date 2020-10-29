// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"你走在一条曲长的小道上，时而有从东面两三个村民结伙向北面的村\n"
"外离去，东面是一个热闹的集市，是村女每天必去的地方；西面是村长的\n"
"居所，总有一些人会登门拜访。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        set("no_clean_up",0);
        
        set("exits",([
                "north" : __DIR__"road11",
                "east" : __DIR__"road17",
                "west" : __DIR__"chunzhangjia",
                "south":        __DIR__"road2",
        ]));
                
        setup();
        
        // replace_program(ROOM);
        
}