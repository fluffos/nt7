inherit ROOM;

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
           "/d/emei/npc/poorman" : 2,
           "/d/emei/npc/little_monkey" : 3,
                "/clone/quarry/fu" : 3,
        ]));
        set("exits", ([
                "south" : __DIR__"jiulaodong",
                     "enter" : __DIR__"xue/bfd0", 
        ]));

        set("coor/x", -520);
        set("coor/y", -240);
        set("coor/z", 130);
        set("coor/x", -520);
        set("coor/y", -240);
        set("coor/z", 130);
        setup();
        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if (dir == "enter" && (!playerp(me)))
        {
                return -1;
        }
                
        return ::valid_leave(me, dir);
}
