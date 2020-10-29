// dbshan.c 冰山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"冰山"NOR);
        set("long", @LONG
大冰山在日光的照射下发出刺眼的光芒，显得十分奇丽，这里到
处都是冰雪，冰山颇大，如陆地上之山丘，一眼望去，横百余丈，纵
长几十丈，冰山上滑不留步。海中不时有几块小浮基正在向北飘流。
LONG );
        set("outdoors", "极北");
        set("exits", ([  
              "west" : __DIR__"dbshan",
        ]));

        setup();
}
