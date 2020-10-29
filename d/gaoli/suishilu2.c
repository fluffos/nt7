// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "碎石路");
        set("long", @LONG        
这里是一条碎石路，这里已经是高丽城的南郊了。西边有一片草地。
从这里向西望去，可以看到一个寺庙了。不时有上香的人从你的身旁走过。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"suishilu1",
                "northwest":__DIR__"caodi1",
               ]));
       setup();
        replace_program(ROOM);
}        
