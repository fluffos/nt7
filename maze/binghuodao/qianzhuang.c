inherit __DIR__"binghuodao";

void create()
{
        set("short", "冰火岛钱庄");
        set("long",
"这里是冰火岛的钱庄，专门为天下第一帮的玩家提供钱庄服务。\n"
);
        set("exits", ([ 
                "north"   : __DIR__"shadi", 
        ]));
        
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("binghuo", 1);           // 表示在冰火岛
                
        set("no_fight", 1);     
        set("outdoors", 0);
        
        set("objects", ([
                __DIR__"npc/qianzhuang" : 1,
        ]));
                
        setup();
}
