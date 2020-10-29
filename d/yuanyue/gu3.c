// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{       
        object con, item;
        set("short", "精舍前");
        set("long", @LONG
此处一片空旷，浅草如茵，整齐如剪。一片新绿之上，罗列着十
数件白玉色的琴几，玉墩，棋案之属。红尘间的烟火喧嚷，似乎早以
被群山所阻。
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "eastup" : __DIR__"gu2",
                "westdown" : __DIR__"gu4",
 
        ])); 
        set("objects", ([
                __DIR__"obj/qinji" : 1,
                CLASS_D("mojiao") + "/first" : 1,
        ])); 
        set("outdoors","wansong");              
         
        set("coor/x",100);
        set("coor/y",10);
        set("coor/z",0);
        setup(); 
}   
