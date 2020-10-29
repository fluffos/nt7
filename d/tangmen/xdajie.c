// Room: /tangmen/xdajie1.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long",
"一看就知道这就是唐家镇的西大街了，向西就到了西门了。这是到蜀\n"
"中唐门的必由之路。大街的北边就是有名的唐门酒楼了，唐门中人的婚宴\n"
"大多在这儿举办，老板好象是江湖上有名的一朵花唐肥。\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([ 
                "west"  : __DIR__"ximen",
                "north" : __DIR__"jiulou",
                "east"  : __DIR__"zhongxin",
        ]));

        setup();
        replace_program(ROOM);
}
