inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "海滩");
        set("long",
"这里是冰火岛西岸海滩，海浪拍打着海边巨石。周围是一望无\n"
"际的大海，东边传来阵阵巨大的声响，地动山摇一般，似乎岛上的\n"
"火山在不断地喷发，释放出巨大的能量。\n"
);
        set("exits", ([ 
                "north"    : __DIR__"shadi",
        ]));
        
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("binghuo", 1);           // 表示在冰火岛    
        set("outdoors", "battle4");
        
        set("objects", ([
        ]));
        
        set("no_fight", 1);
        
        setup();
}
