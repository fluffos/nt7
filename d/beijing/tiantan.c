#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "天坛" NOR);
        set("long", @LONG
这里便是北京城里的最有名的名胜天坛了。天坛是世界最大的祭
天神坛。天坛南的围墙呈方型，象征地，最北的围墙呈半圆型，象征
天。南方一座叫圜丘坛，坛呈圆型。坛中心是一块圆石，外转共有九
圈扇型石板。当年皇帝们就站在圆坛的中心虔诚地祭祀苍天。中间一
座叫皇穹宇，通高七丈，是存放天神牌位的地方。著名的祈年殿在最
北方，这是天坛内最宏伟、最华丽的建筑，也是传说想象中的离天最
近的地方。皇帝离开皇穹宇，缓步来到这里，杀牲焚香和天帝『秘谈
』，祈求风调雨顺。从天坛转北通往著名的凡陛桥，向南则是一条大
道，通往永定门，出了永定门便是北京的郊外了。
LONG );
        set("exits", ([
                "south" : "/d/beijing/yongdingdao",
                "north" : "/d/beijing/tiantan_n",
        ]));
        set("objects", ([
                "/d/beijing/npc/youren" : 2,
               "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}