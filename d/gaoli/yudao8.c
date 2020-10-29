// /d/gaoli/yudao8
// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
这里的街道宽敞而干净，汉白玉砌的路面被雨水冲得光明如镜，街
道内侧是高大宏伟的皇城城墙。南面是高丽的迎宾馆，进进出出来来往
往的有客商，还有各国使节。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"xuanwu-1", 
                "south":__DIR__"yingbinguan", 
                "west":__DIR__"yudao6", 
                "east":__DIR__"yudao7",
        ]));
       setup();
        replace_program(ROOM);
}        
