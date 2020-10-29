//redl 2014
inherit __DIR__"normal.c"; 

void create()
{
        set("short", "九老洞");
        set("long", @LONG
这就是峨嵋第一大洞，洞内深窈无比，神秘难测。你一走进来，
便发觉洞中叉叉洞多如迷宫，怪异莫测，似乎黝黑无底。洞里隐隐传
来鸡犬鼓乐之声，令人惊异间，忽有蝙蝠群涌而至扑熄火炬。还是快
快离开吧。
LONG );
        set("objects", ([
             __DIR__"npc/jianxia" : 1,
        ]));
        set("exits", ([
                "out" : __DIR__"bfd29",
                "south" : __DIR__"bfdb" + (string)random(30),
                "north" : __DIR__"bfdb" + (string)random(30),
                "west" : __DIR__"bfdb" + (string)random(30),
                "east" : __DIR__"bfdb" + (string)random(30),
                "up" : __DIR__"bfdb" + (string)random(30),
                "down" : __DIR__"bfdb" + (string)random(30),
        ]));

        set("n_time", 14400);  
        set("n_npc", 1);  
        set("n_max_npc", 1); 
                set("s_npc", "/d/emei/xue/npc/yu"); 
                set("stop_run", random(10));
        setup();
}


void init()
{
        object me = this_player();
        //不改short_name是为了避免玩家利用walk指令过迷宫
        tell_object(me, "\n你来到了九老洞第二层的入口。\n\n"); 
        return ::init();
}

