// /d/gaoli/yudao1
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
这里的街道宽敞而干净，汉白玉砌的路面被雨水冲得光明如镜，街
道内侧是高大宏伟的皇城城墙。北面通向皇城的正门，东西两面围绕皇
宫的皇城御道。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"gongmen", 
                "south":__DIR__"zhuque-1",
                "west":__DIR__"yudao2",
                 "east":__DIR__"yudao3",
        ]));
       setup();
        replace_program(ROOM);
}        
