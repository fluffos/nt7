// /d/gaoli/qianzhuang
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "高丽钱庄");
        set("long", @LONG
这是高丽规模最大的一家钱庄，钱庄的门口挂着一块很大的金字招
牌，“高丽钱庄”长长的柜台，都打扫的干干净净。柜台后几个账房先
生与小活计正在忙的焦头烂额。
LONG
        );
set("exits", ([
               "east":__DIR__"xuanwu-1", 
        ]));
   set("objects", ([
                "/d/gaoli/npc/jin" : 1,
        ]));
       setup();
        replace_program(ROOM);
}        
