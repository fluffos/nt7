// /d/playertown/road1.c 碎石小道
// Build 1999.12.10 bmw

inherit BUILD_ROOM;

void create()
{
        set("short","碎石小道");
        set("long",
"这是一条碎石小道。北面是三岔道，南面延伸至村外的小路，而在东\n"
"面，一座小庙屹立在那，里面传来乡亲们的祷告声。\n"
);

        set("recordable_room",1);
        set("outdoors","playertown");
        set("no_clean_up",0);
        
        set("exits",([
                "north"        :        __DIR__"road8",
                "south"        :        __DIR__"road6",
                "east"        :        __DIR__"miao",
        ]));
        
        setup();
        
        // replace_program(ROOM);
        
}