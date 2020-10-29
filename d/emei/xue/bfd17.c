//redl 2014
inherit BUILD_ROOM; 

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
             __DIR__"npc/bianfu1" : (random(5) ? 0 : (random(7)+3)),
        ]));
        set("exits", ([
                //"out" : "/d/emei/jldongnei",//独有0开放此行
                "south" : __DIR__"bfd" + (string)random(30),
                "north" : __DIR__"bfd" + (string)random(30),
                "west" : __DIR__"bfd" + (string)random(30),
                "east" : __DIR__"bfd" + (string)random(30),
                "up" : __DIR__"bfd" + (string)random(30),
                "down" : __DIR__"bfd" + (string)random(30),
/*                "southup" : __DIR__"bfd" + (string)random(20),
                "northup" : __DIR__"bfd" + (string)random(20),
                "westup" : __DIR__"bfd" + (string)random(20),
                "eastup" : __DIR__"bfd" + (string)random(20),
                "southdown" : __DIR__"bfd" + (string)random(20),
                "northdown" : __DIR__"bfd" + (string)random(20),
                "westdown" : __DIR__"bfd" + (string)random(20),
                "eastdown" : __DIR__"bfd" + (string)random(20),
                "southwest" : __DIR__"bfd" + (string)random(20),
                "southeast" : __DIR__"bfd" + (string)random(20),
                "northwest" : __DIR__"bfd" + (string)random(20),
                "northeast" : __DIR__"bfd" + (string)random(20),*/
        ]));

        set("stop_run", random(12));
        setup();
}


int valid_leave(object me, string dir)
{
        if (me->is_fighting())
        {
                tell_object(me, "你还是先解决目前的敌人吧！\n"); 
                return 0;
        }
                
        return ::valid_leave(me, dir);
}


void init()
{
        if ( query("stop_run") ) return;
        if ( query("env/invisible", this_player()) ) return;
        tell_object(this_player(), "\n噗哧一声你踩到坨蝙蝠屎，差点跌倒！\n\n"); 
        this_player()->start_busy(2);
}

