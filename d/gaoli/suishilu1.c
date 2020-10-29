// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "碎石路");
        set("long", @LONG        
这里是一条碎石路，北边是一条宽敞的青石路。这里绿树环绕，空
气清新。从这里可以隐约听到敲钟的声音，看来不远处有一个寺院。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northeast" : __DIR__"dadao9",
                "west":__DIR__"suishilu2",
               ]));
       setup();
        replace_program(ROOM);
}        
