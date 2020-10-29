// /d/gaoli/yudao4
// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
这里的街道宽敞而干净，汉白玉砌的路面被雨水冲得光明如镜，街
道内侧是高大宏伟的皇城城墙。东面是高丽的城防衙门，进进出出的多
是一些士兵。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"yudao6", 
                "south":__DIR__"yudao2", 
                "west":__DIR__"qinglong-1", 
                "east":__DIR__"yamen",
        ]));
       setup();
        replace_program(ROOM);
}        
