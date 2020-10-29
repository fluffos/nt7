//Cracked by Kafei
// yideng quest room 9

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "庙前");
        set("long", @LONG
这里是深山巅峰，平地上有一座小小寺院，庙前有一个荷塘，一
座小桥横跨其上。旁边陡峭的山崖上有一条铁链和一些人工凿出来的
台阶，似乎是一条上下山的捷径。
LONG );

        set("exits", ([
                "south" : __DIR__"yideng8",
                "northup" : __DIR__"chanyuan",
                "down" : __DIR__"shanlu9",
        ]));

        set("invalid_startroom", 1);
        set("outdoors", "taoyuan");
        set("no_magic", 1);
        setup();
}