// 花丛中 huacong1.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "花丛中");
        set("long", @LONG
这里周围都是嫣红姹紫的鲜花，各种奇花异草，份外芬香。眼前
有一条小径夹杂在鲜花丛中。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "north" : __DIR__"xiaojing",
            "out" : __DIR__"shanbi",
        ]));

        setup();
}