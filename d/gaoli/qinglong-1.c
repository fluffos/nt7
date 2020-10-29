// /d/gaoli/zhuquedajie2
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "飞凤大街");
        set("long", @LONG
你走在一条宽阔的石板大街上。东面就是皇城御道了，南边是兵营
的大门，里面不时传来呐喊的声音。北边是一个马房，这里可以听到马
叫的声音，非常热闹。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"qinglong-2",
                "east" : __DIR__"yudao4",
                "north":__DIR__"mafang",
                "south":__DIR__"bingyingdamen",    
        ]));
      set("objects",([
         __DIR__"npc/xiake":1,
         ]));
       setup();
        replace_program(ROOM);
}        
