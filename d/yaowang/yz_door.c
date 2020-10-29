inherit ROOM;

void create()
{
        set("short", "药庄小门");
        set("long", @LONG
这里是一处篱笆小门，门边有一块小木牌上写着“药庄”两
个篆字。南面是一条紫色和绿色小石子铺成的小路。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"lu1",
  "north" : __DIR__"yz_xiaoyuan",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
