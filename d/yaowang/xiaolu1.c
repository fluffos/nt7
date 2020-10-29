#include <room.h>

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
这是一条小土路，两旁杂草丛生，非常荒凉，看样子很少有
人来这里。南面是一扇小木门，背面是一片荆棘丛。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"jingji1",
  "south" : __DIR__"tulu3",
]));

        set("outdoors", "yaowang");
        setup();
        create_door("south", "木门", "north", DOOR_CLOSED);
}
