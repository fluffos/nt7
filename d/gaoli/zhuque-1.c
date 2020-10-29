// /d/gaoli/zhuquedajie1
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "得胜大街");
        set("long", @LONG
你走在一条宽阔的石板大街上，北面就快到高丽皇宫了。都可以看
见皇宫的围墙拉南面是高丽的南门得胜门，东面是高丽最大的酒楼，西
面是一家珠宝店，专卖各式各样的首饰。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"zhuque-2",
                "north" : __DIR__"yudao1",
                "east":__DIR__"jiulou",
                "west":__DIR__"zhubaodian",    
        ]));
       setup();
        replace_program(ROOM);
}        
