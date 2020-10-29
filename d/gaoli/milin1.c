// /d/gaoli/xuanwumen
// Room in 高丽
inherit ROOM;

void create()

{
set("short", "密林");

        set("long", @LONG
你正走在一茂密的丛林之中。四周都是参天的古树，遮住了头上的
阳光。不时有几只野兔从你的身旁跑过。密林之中，隐藏了很多猛兽毒
蛇，你不禁小心起来。
LONG
        );
        

set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"shanlu2",
                "south" : __DIR__"jiangbei",
               
        ]));
       setup();
        replace_program(ROOM);
}
