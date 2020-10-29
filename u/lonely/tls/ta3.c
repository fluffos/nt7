#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"无住宝塔"NOR);
        set("long",@LONG
崇圣寺三塔东塔无住，高二百余尺，八角十层，皆为实心，各层
分别雕卷龛、佛像、莲花等，华贵庄重。正面中央开卷龛，各置白色
大理石佛像一尊。
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([
                "south" : __DIR__"yz5",
        ]));	
        set("coor/x",-370);
  set("coor/y",-310);
   set("coor/z",20);
   setup();
}
