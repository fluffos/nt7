// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "三岔路口");
        set("long", @LONG
        
这是一个三岔路口，向西走不远就是高丽城了，向南就是百济地界
了，东北就是新罗地界，因为打仗的原因来往的行人非常少。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"dadao4",
                "south" : __DIR__"dadao5",
                "northeast" : __DIR__"shaoqia",
        ]));
       setup();
        replace_program(ROOM);
}        
