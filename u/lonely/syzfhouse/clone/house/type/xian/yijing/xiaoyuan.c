// xiaoyuan.c

#include <ansi.h>
inherit "/inherit/room/house_door";

void create()
{
    set("short", "仙宅大门");
    set("long", @LONG
眼前好大一片宅院，但见楼台瑰丽，玉墙蜿蜒，不知占地有多少亩。
周遭云雾飘渺缭绕，景致似真似幻，令人如在梦中。
LONG);

    set("exits",
    ([
        "out"   : __FILE__,
        "north" : __DIR__"qianyuan",
    ]));

    set("owner_name", "某人");
    set("owner", "OWNER");
    set("huyuan", __DIR__"huyuan");
    set("outdoors", "OUTDOORS");
    set("forbid_exits", "north");
    set("max_laodu", 1000000);
    set("now_laodu", 1000000);

    setup();
    restore();
}

int valid_leave(object me, string dir)
{
    if(dir != query("forbid_exits"))
        return ::valid_leave(me, dir);

    if(!wizardp(me)
        && me->query("id") != query("owner")
        && me->query("couple/couple_id") != query("owner")
        && !me->query_temp("invited_guest/" + query("owner")))
            return notify_fail(WHT "前面似乎有一阵无形的真气挡住，"
                                   "令你再也无法前行半分。\n" NOR);

    message_vision(HIC "\n一片云雾飘来，轻轻将$N裹起，"
                       "飘飘悠悠地飞了进去。\n" NOR, me);
    return ::valid_leave(me, dir);
}
