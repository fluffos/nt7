//gudao2.c

inherit ROOM;
void create()
{
        set("short","古道");
        set("long",
"一条石板古道，两边树木苍翠，山势平缓，南面是唐家镇的小树林。\n"
"远处有一片宏伟建筑，一堵里许长的红墙隔开，越过墙头可见一座高楼耸\n"
"立，好象正是蜀中唐门的门楼。\n"
);
        set("outdoors", "tangmen");
        set("exits",([ 
            "northwest"    : __DIR__"tmdamen",
            "east"    : __DIR__"gudao1",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}