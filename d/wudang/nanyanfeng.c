#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "南岩峰");
        set("long", @LONG
这里是武当三十六岩之最，松树翳天，木石争奇，峭壁万仞。在
悬崖之半筑有一宫宇，下临深渊，工程浩大。宫前有一石柱，自峭壁
上横出。
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/mo": 1,
        ]));

        set("exits", ([
                "eastdown" : __DIR__"langmeiyuan",
                "southdown": __DIR__"shizhu",
                "west"     : __DIR__"sheshenya",
        ]));
        set("outdoors", "wudang");
        set("coor/x", -360);
        set("coor/y", -320);
        set("coor/z", 110);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((! myfam || myfam["family_name"] != "武当派")
           && dir == "southdown"
           && objectp(present("mo shenggu", environment(me))))
                return notify_fail(CYN "莫声谷拦住你说：此处乃本派禁"
                                   "地，请止步。\n" NOR);

        return ::valid_leave(me, dir);
}