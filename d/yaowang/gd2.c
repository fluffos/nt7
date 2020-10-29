
inherit ROOM;

void create()
{
        set("short", "石子小路");
        set("long", @LONG
这是一条石子小路蜿蜒在青青的绿草地中，可能是经常有人
走动，路上的石子被磨得非常光亮。前面不远是是一大片院落，
红漆大门洞开，里面影影吵吵的好像有不少人。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"fyuan",
  "south" : __DIR__"dmq",
  "west" : __DIR__"chalu",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
