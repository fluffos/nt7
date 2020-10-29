// /d/gaoli/baihu-1
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "朝阳大街");
        set("long", @LONG
你走在一条宽阔的石板大街上，西面就快到高丽皇宫了。都可以看
见皇宫的围墙拉东面是高丽的东门朝阳门,北面是一家民宅,高墙大院好
象是一个富户。南面是一家商行。运输各样的货物。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"yudao5",
                "east" : __DIR__"baihu-2",
                "north":__DIR__"dafujia1",
                "south":__DIR__"shanghang",    
        ]));
        set("objects",([
          __DIR__"npc/shusheng":1,
          ]));
       setup();
        replace_program(ROOM);
}        
