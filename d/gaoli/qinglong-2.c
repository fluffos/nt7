// /d/gaoli/zhuquedajie2
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "飞凤大街");
        set("long", @LONG
你走在一条宽阔的石板大街上，东面就快到高丽皇宫了。都可以看
见皇宫的围墙，西面是高丽的西门飞凤门，北面是高丽的驿站，南面是
高丽官方开的盐局。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"qinglongmen",
                "east" : __DIR__"qinglong-1",
                "north":__DIR__"yizhan",
                "south":__DIR__"yanju",    
        ]));
       setup();
        replace_program(ROOM);
}        
