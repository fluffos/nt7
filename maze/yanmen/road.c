
inherit DEMONROOM;

void create()
{ 
        set("short", "山道"); 
        set("long", 
"这里已经快到雁门关了，满眼望去，尽是曲曲折折的山道，大军行到 
此处，人畜都开始有些吃力起来。\n" 
); 
        set("outdoors", "yanmen"); 
        set("no_fly",1); 
        set("exits", ([ 
                "south"  : __DIR__"luanshi1", 
        ])); 
        set("n_time", 30); 
        set("n_npc", 5); 
        set("n_max_npc", 15);
        set("s_npc", __DIR__"npc/qidanbing");

        setup();
}
