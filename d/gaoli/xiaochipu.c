// /d/gaoli/xiaochipu
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "小吃店");
        set("long", @LONG
这是一家很破很旧的小店。只有三、两张桌子零乱的摆放着，桌上
还粘着一层厚厚的油垢。墙则早已被油烟熏去了原来的本色。这里不卖
其它食物，只卖一些小吃，价格低廉。
LONG
        );
set("exits", ([
               "south":__DIR__"baihu-2", 
        ]));
set("objects", ([
                "/d/gaoli/npc/li" : 1,
        ]));
       setup();
        replace_program(ROOM);
}        
