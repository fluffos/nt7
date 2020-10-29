// /d/gaoli/zhuquedajie1
// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "得胜大街");
        set("long", @LONG
你走在一条宽阔的石板大街上，北面就快到高丽皇宫了。都可以看
见皇宫的围墙拉南面是高丽的南门得胜门，东面的店铺的门外挂着一个
大大的当字，进出得人有喜有忧西面传来吆五喝六的声音，是高丽的一
家赌场。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"zhuquemen",
                "north" : __DIR__"zhuque-1",
                "east":__DIR__"dangpu",
                "west":__DIR__"duchang",    
        ]));
       setup();
        replace_program(ROOM);
}        
