inherit ROOM;
 
void create()
{
        set("short", "草地");
        set("long", @LONG
你走在一片草地。草地东边有一片墓地。
LONG );
        set("exits", ([
            "east"    : __DIR__"mudi",
            "south"    : __DIR__"fen0", 
            "north"    :__DIR__"grass2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "inn");    
        setup();
        replace_program(ROOM);
}