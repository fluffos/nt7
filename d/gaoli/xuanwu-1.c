// /d/gaoli/xuanwudajie3.c
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "玉龙大街");
        set("long", @LONG
你走在一条宽阔的石板大街上，南面就快到高丽皇宫了，北面通向
玄武门，大街的东面传来叮叮当当的打铁声，原来是一家铁匠铺，西面
是一家钱庄，在大街上就能听见，数钱的声音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"xuanwu-2", 
                "south":__DIR__"yudao8", 
                "west":__DIR__"qianzhuang",
                 "east":__DIR__"tiejiangpu", 
        ]));
set("objects",([
 __DIR__"npc/gaoli-yongshi":1,
 ]));
       setup();
        replace_program(ROOM);
}        
