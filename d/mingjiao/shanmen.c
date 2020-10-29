// Room: /d/mingjiao/shanmen.c
// Date: Java 97/04/3

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "明教山门");
        set("long", @LONG
一个巨大的天然石桥横跨在两片山壁之间，石桥正上方龙盘凤舞
刻着两个大字：『明教』。字迹有些剥落，看上去年代久远。两位三
十来岁的大汉手持钢剑守在山门两侧。
LONG );
        set("exits", ([
                "westup" : __DIR__"shanlu1",
                "east" : __DIR__"tomen1",
        ]));
        set("outdoors", "mingjiao");
        set("objects",([
                __DIR__"npc/menwei1" : 2,
                __DIR__"npc/jieyinshi":1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        object *inv;
        int i;

        if (me->query_family() != "明教" &&
            me->query_family() != "武当派"  &&
            dir == "westup")
        {
                inv = all_inventory(me);
                for(i=sizeof(inv)-1; i>=0; i--)
                        if(query("weapon_prop", inv[i]) && ((string)query("equipped", inv[i])=="wielded"))
                                if(objectp(present("da han", environment(me))))
                                        return notify_fail("大汉拦住你说道：这位" +
                                                RANK_D->query_respect(me) + "请放下兵刃。我教教规严"
                                                "厉，外客不\n得持兵刃上山。请见谅。\n");
        }
        return ::valid_leave(me, dir);
}
