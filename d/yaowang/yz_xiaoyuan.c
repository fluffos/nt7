inherit ROOM;

void create()
{
        set("short", "小院子");
        set("long", @LONG
这里是一处静静的小院，院子里满是嫩绿的小草，中间是一
个石桌，上面还摆着没下玩的棋局，给人一种静谧、悠闲的感觉，
很难想象出这里就是唐门弟子没事也不愿意来的唐家堡药庄。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"yz_ku",
  "south" : __DIR__"yz_door",
  "east" : __DIR__"yz_tang",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
