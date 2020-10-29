//fangjvfang.c                四川唐门—防具房

inherit ROOM;

void create()
{
        set("short", "防具房");
        set("long",
"这里是蜀中唐门的防具房，房间很大，靠墙摆放着几个木架，上面挂\n"
"着一些防护用具，可以用来防止在练习中伤到自己。其中最具特色的，莫\n"
"过于那套唐门独有的鹿皮手套。\n"
);
        set("exits", ([
                "north" : __DIR__"nzlange2",
        ]));
        set("objects", ([
                "/d/city/npc/obj/tiejia" : 4
        ]));

        set("no_fight", 1);
        set("area", "tangmen");        
        setup();
        replace_program(ROOM);
}