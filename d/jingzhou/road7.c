#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","小路");
        set("long", @LONG
一条崎岖的黄土小路，路旁杂草丛生，西边可以看见荆州的官道，
向东去则可一到达武昌。
LONG );
        set("exits", ([
                  "east" : __DIR__"road6",
                  "west" : __DIR__"guandao1",
          ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -390);
        set("coor/y", -200);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
