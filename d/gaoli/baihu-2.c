// /d/gaoli/baihuuedajie3
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "朝阳大街");
        set("long", @LONG
你走在一条宽阔的石板大街上，西面就快到高丽皇宫了。都可以看
见皇宫的围墙，东面是高丽的东门朝阳门，北面是一家小吃铺，店虽不
大，可东西却不少，南面是一间小茶馆，不少人在里面听书喝茶。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"baihu-1",
                "east" : __DIR__"baihumen",
                "north":__DIR__"xiaochipu",
                "south":__DIR__"chaguan",    
        ]));
set("objects",([
 __DIR__"npc/dipi":1,
 ]));
       setup();
        replace_program(ROOM);
}        
