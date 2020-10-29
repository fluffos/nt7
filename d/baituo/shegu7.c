// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蛇谷平地");
        set("long", @LONG
这是蛇谷的一处较平坦开阔的地带，地上满是矮小无叶的骆驼刺
和碎小的乱石。平缓的地势从这里往东边略为延伸，此外各方向都是
斑驳的林木。
LONG );

        set("exits", ([ 
            "southwest" : __DIR__"shegu8",
            "east" : __DIR__"shegu6",
            "northwest" : __DIR__"shegu20",
        ]));
        
        set("objects", ([
            __DIR__"npc/maque" : 2,
        ]));
        set("resource/grass", 1);
        set("cost", 1);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49990);
        set("coor/y", 20170);
        set("coor/z", 20);
        setup();
}