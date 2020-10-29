// /d/gaoli/yudao1
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
这里的街道宽敞而干净，汉白玉砌的路面被雨水冲得光明如镜，街
道内侧是高大宏伟的皇城城墙。墙内飘来了一阵阵喧哗。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south":__DIR__"yudao4", 
                "east":__DIR__"yudao8",
        ]));
       setup();
        replace_program(ROOM);
}        
