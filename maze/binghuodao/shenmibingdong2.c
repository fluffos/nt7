inherit __DIR__"binghuodao";

void create()
{
        set("short", "神秘冰洞");
        set("long",
"这是冰火岛上隐藏的一处冰洞，冰洞内冰锥纵横，寒冷异常。\n"
);
        set("exits", ([ 
                "west"   : __DIR__"shenmibingdong", 
                "southeast"   : __DIR__"shenbingtan",
        ]));
        
        set("outdoors", 0);
        
        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/bingjiangshi");        
        setup();
}
