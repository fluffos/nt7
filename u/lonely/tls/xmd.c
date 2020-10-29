#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"须弥殿"NOR);
        set("long",@LONG
这座殿堂规模较小，但香雾缭绕，人来人往，很是热闹，殿内供奉
着五百罗汉，佛像金身金衣，或笑口大开，或斜靠坐着，或怒目而视，
各不相同。许多香客都在数着罗汉，看哪尊会和自己有源。
LONG);       
        set("exits", ([
                "west" : __DIR__"yz3",
                "south" : __DIR__"ytd",
	]));

        set("coor/x",-340);
  set("coor/y",-290);
   set("coor/z",20);
   setup();
}