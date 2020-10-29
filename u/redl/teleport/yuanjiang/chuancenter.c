//redl 2015
#include <ansi.h> 
#include <room.h> 
inherit ROOM;

void create()
{
        set("short", "金船中控室");
        set("long", @LONG
这就是广成金船上的中控室，WIZ专属房间。
LONG );
                for (int i = 0; i < 50; i++) {
                        set("exits/" + (string)i , __DIR__"chuan" + (string)i);
                }
                set("exits/down"  , "/d/city/kedian4");

        set("objects", ([ 
                __DIR__"npc/qi" : 1,//npc出发点
                //__DIR__"npc/qi2" : 1,
        ])); 
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_fly", 1);
                set("no_magic", 1);
                set("no_sleep_room", 1); 
                set("no_kill",1);
        set("no_fight",1);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir=="down")
        {
                if (!playerp(me)) return 0;
        }
                
        return ::valid_leave(me, dir);
}


