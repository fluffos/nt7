// Room: /tangmen/zhongxin.c

inherit ROOM;

void create()
{
        set("short", "唐家镇中心");
        set("long",
"这里是唐家镇的正中心，一个很宽阔的广场，铺着青石地面。往来的\n"
"行人大都是唐门的弟子，有许多来自中原的商家在这儿做一些小买卖，人\n"
"声沸腾，真是一片繁华景象。这里通向唐家镇的各条大街。\n"
);
        set("no_sleep_room",1);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"edajie",
                "south" : __DIR__"ndajie",
                "west"  : __DIR__"xdajie",
                "north" : __DIR__"bdajie1",
        ]));
        set("objects", ([
                __DIR__"npc/shangren" : 1,
                __DIR__"npc/dizi" : 1,
                __DIR__"npc/boy" : 1,
        ]));
        setup();
}
