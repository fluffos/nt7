// Room: /binghuo/wangpanshan.c
// Date: Oct.28 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "王盘山海滩");
        set("long", @LONG
只听得岛上号角之声呜呜吹起，岸边两人各举大旗，挥舞示意。
只见两面大旗上均绣着一头大鹰，双翅伸展，甚是威武。两面大旗之
间站着一个老者。只听他朗声说道：“玄武坛白龟寿恭迎贵客。”声
音漫长，绵绵密密，虽不响亮，却是气韵醇厚。往南是一个山谷。北
边有个港湾，桅樯高耸，停泊着十来艘大船，想是巨鲸帮、海沙派一
干人的座船。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("exits", ([
                "north":"/d/tulong/tulong/boat2",
                "south" : __DIR__"wangpangu1",
                //"east"  : __DIR__"wangpanlin",
        ]));
        set("objects", ([
                 "/d/tulong/tulong/npc/jiaozhong1": 2,
                 "/d/tulong/tulong/npc/jiaozhong2": 2,
                 "/d/tulong/tulong/npc/bai": 1,
        ]));
        setup();
}

int valid_leave(object me,string dir)
{
        object ob;
        if( !query_temp("dao", me) && dir == "south" )
        return notify_fail("一进了会场就是生死之斗，还是先砸了他们的船(break boat)以防不测。\n");

        if( query_temp("dao", me) && dir == "south" && ob=present("bai guishou") )
        {
                ob->ccommand("tnnd"+query("id", me));
                ob->ccommand("slap3"+query("id", me));
                message_vision("$N喝道：$n，去死吧！\n",ob,me);
                ob->kill_ob(me);
                ob=present("jiao zhong");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("jiao zhong 2");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("jiao zhong 3");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("jiao zhong 4");
                if (objectp(ob)) ob->kill_ob(me);
                return notify_fail("向南的路被白龟寿拦住了。\n");
        }
        return 1;
}

