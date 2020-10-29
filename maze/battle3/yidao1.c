inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "城外驿道");
        set("long", @LONG
这里是通往大宋京城的驿道，由于连年来战火不止，显得格外地
荒凉，不时有来往的马匹飞奔而过，溅起一土尘烟，沿途不时有土匪
大盗出现，还是少作停留的好。
LONG );
        set("outdoors", "xiangyang");
        set("no_fly",1);

        set("exits", ([
                "east"  : "/d/xiangyang/westgate2", 
                "west"  : __DIR__"yidao2",
        ]));
        setup();
}
