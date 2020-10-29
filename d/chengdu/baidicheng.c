#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "白帝城" NOR );
        set("long", @LONG
朝辞白帝彩云间，千里江陵一日还。两岸猿声啼不住，千舟以过
万重山。这里就是有名的白帝城了，遥看四周，只见青山绿水，一片
大好风景。庙内塑有刘备及孔明等一干名士的雕像，凭栏怀古，心潮
汹涌，令人神怡。
LONG );
        set("exits", ([
                  "west" : __DIR__"shudao10",
                "east" : __DIR__"sanxia3",
                "north": __DIR__"shandao",
  
        ]));
        set("objects", ([
                "/d/beijing/npc/shiren" : 1,
                "/d/beijing/npc/shusheng1" : 2,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15070);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}