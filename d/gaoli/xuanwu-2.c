// /d/gaoli/xuanwudajie1.c
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "玉龙大街");
        set("long", @LONG
你走在一条宽阔的石板大街上，北面是高丽的北城门玄武门，在向
南走就快到高丽皇宫了，大街的东面是一家私塾，传来阵阵读书声，西
面是一家药铺。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"xuanwumen", 
                "south":__DIR__"xuanwu-1", 
                "west":__DIR__"yaopu",
                 "east":__DIR__"sishu", 
        ]));
       setup();
        replace_program(ROOM);
}        
