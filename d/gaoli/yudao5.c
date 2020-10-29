// /d/gaoli/yudao5
// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
这里的街道宽敞而干净，汉白玉砌的路面被雨水冲得光明如镜，街
道内侧是高大宏伟的皇城城墙。东面是高丽的武士行馆，进进出出的多
是一些高丽的武士。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"yudao7", 
                "south":__DIR__"yudao3", 
                "east":__DIR__"baihu-1", 
                "west":__DIR__"xingguan",
        ]));
       setup();
        replace_program(ROOM);
}        
