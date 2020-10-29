// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "青石大道");
        set("long", @LONG
        
你走在一条青石大道上，因为战争的原因，越向前走行人越来越少，
不时有人骑着马匆匆而过。大道往北进入新罗境内。南边通向百济,
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"sanchalu",
                "south" : __DIR__"yuanmen",
        ]));
       setup();
        replace_program(ROOM);
}        
