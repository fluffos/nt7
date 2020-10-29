#include <ansi.h>

inherit ROOM;

#define PLACE "sz"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "修罗门总坛");
        set("long", @LONG
这里是修罗门的总部，整个房间都阴森森的，正中是一个大火盆，
正喷发着幽蓝的火焰。让人觉得不颤而栗。前台摆放着一张镂金象牙
床，倒吊的竹帘，映出一个模糊的轮廓。想必就是那神秘莫测的玉罗
刹了。一侧的墙上挂着任务牌（paizi）。
LONG );

        set("objects", ([
                __DIR__"npc/boss-yu"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "out" : __DIR__"hutong3",
        ]));

        setup();
}
#include <bang_bad.h>
