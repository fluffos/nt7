#include <ansi.h>
inherit ROOM;
void create()
{ 
        set("short","秘室");
        set("long", @LONG
这里是明教秘道里的一间小小的秘室。
LONG );
    
        set("exits", ([
                  "down" : __DIR__"midao12",
        ]));             
        set("objects",([
                CLASS_D("mingjiao") + "/cheng" : 1,
        ]));
        setup();
}
