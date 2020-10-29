
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "兵营");
        set("long", @LONG
这里是兵营，密密麻麻到处都是官兵，有的在武将的指挥下列队操
练，有的独自在练功，有的坐着、躺着正在休息。南墙下坐着主帅，不
动声色地寻视着四周。看到你进来，他们全都向你包围了过来，形势看
来不太妙。
LONG);

        
        set("exits", ([
                "north" : __DIR__"bingyingdamen",
        ]));
 setup();
        replace_program(ROOM);
}        
