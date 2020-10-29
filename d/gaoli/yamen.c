// /d/gaoli/yamen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "城防衙门");
        set("long", @LONG
这里是高丽的城防衙的官卫房，大概有三丈见方，中间有张长案，
一位将军在这里办公，这里主要负责高丽城的防务安全，以及防盗，防
火，捉拿逃犯等事物。 
LONG
        );
set("exits", ([
                "west":__DIR__"yudao4",
//                "east": "/d/clone/room/cityroom/gaoli"    
        ]));
     set("objects",([
       __DIR__"npc/guanbingc":3,
       ]));
       setup();
        replace_program(ROOM);
}        
