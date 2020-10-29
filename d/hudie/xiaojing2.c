// 小径 xiaojing2.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "小径");
        set("long", @LONG
你走着走着，眼前的蝴蝶越来越多，或花或白，或黑或紫，翩翩
起舞。蝴蝶也不畏人，飞近的时候便在你的头上、肩上、手上停留。
看来已经到了蝴蝶谷了。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "northeast" : __DIR__"kongdi",
            "south" : __DIR__"xiaojing1",
        ]));

        setup();
}