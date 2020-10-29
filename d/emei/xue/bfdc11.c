//redl 2014
inherit __DIR__"normal.c"; 

void create()
{
                int rnd = random(100);
        set("short", "九老洞");
        set("long", @LONG
这就是峨嵋第一大洞，洞内深窈无比，神秘难测。你一走进来，
便发觉洞中叉叉洞多如迷宫，怪异莫测，似乎黝黑无底。洞里隐隐传
来鸡犬鼓乐之声，令人惊异间，忽有蝙蝠群涌而至扑熄火炬。还是快
快离开吧。
LONG );
        /*set("objects", ([
             __DIR__"npc/bianfu1" : 10,
        ]));*/
        set("exits", ([
                //"enter" : __DIR__"bfdc0",
                "south" : __DIR__"bfdc" + (string)random(20),
                "north" : __DIR__"bfdc" + (string)random(20),
                "west" : __DIR__"bfdc" + (string)random(20),
                "east" : __DIR__"bfdc" + (string)random(20),
                "up" : __DIR__"bfdc" + (string)random(20),
                "down" : __DIR__"bfdc" + (string)random(20),
        ]));

        set("n_time", 30 + random(10));  
        set("n_npc", 1 + random(3));  
        set("n_max_npc", 5 + random(4)); 
        if (rnd<10)
                set("s_npc", "/d/emei/xue/npc/bianfu7"); 
        else if (rnd<30)
                set("s_npc", "/d/emei/xue/npc/bianfu6"); 
        else
                set("s_npc", "/d/emei/xue/npc/bianfu5"); 
        setup();

                set("stop_run", random(8));
        setup();
}

