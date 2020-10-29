// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。再往西边走就是高丽的北城监狱了。西边就是
北城监狱的大门了。有几名官兵在那里把守着，用严厉的眼神看着你。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"shanlu15",
                       "west":__DIR__"jianju",
        ]));
       setup();
        
}

