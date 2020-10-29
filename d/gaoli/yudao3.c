// /d/gaoli/yudao1
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
这里的街道宽敞而干净，汉白玉砌的路面被雨水冲得光明如镜，街
道内侧是高大宏伟的皇城城墙。墙内飘来了一阵阵的花香。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"yudao5", 
                "west":__DIR__"yudao1",
        ]));
set("objects",([
 __DIR__"npc/jianke":1,
 ]));
       setup();
        replace_program(ROOM);
}        
