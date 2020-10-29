inherit __DIR__"binghuodao";

void create()
{
        set("short", "神秘火洞");
        set("long",
"这是冰火岛上隐藏的一处火洞，洞内热气腾腾，令人窒息。\n"
);
        set("exits", ([ 
                "north"   : __DIR__"shenghuotai", 
                "east"   : __DIR__"shenmihuodong2",
                "south"   : __DIR__"shenmihuodong3",
        ]));
        
        set("outdoors", 0);
        
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/huoqilin");            
        setup();
}
