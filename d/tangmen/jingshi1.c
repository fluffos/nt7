//jingshi1.c                四川唐门—静室

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "静室");
        set("long",
"这是一间静室。这里是唐门弟子吐纳、打坐的地方，这里非常安静，\n"
"没有一丝声音。屋中没有任何摆设，只是在地上扔着十几个蒲团有几名弟\n"
"子正盘坐在上面用心练功。\n"
);
        set("no_steal", "1");
        set("no_fight", "1");
        set("exits", ([
                "south" : __DIR__"nzlangw2",
        ]));
        set("area", "tangmen");
        setup();
        replace_program(ROOM);
}