// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "辕门");
        set("long", @LONG
        
这是百济驻军所在的兵营的辕门，两边有数丈高的旗杆，旗杆上的
刁斗上，辕门的两旁百济士兵严阵以待，再向前走就是兵营的中军大帐
了。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"dadao5",
                "south" : __DIR__"dazhang",
        ]));
       setup();
        replace_program(ROOM);
}        
