// Room: diecong1.c

inherit ROOM;

void create()
{
        set("short", "蝶丛");
        set("long", @LONG
你现在正站在一个蝶丛里，嗯....这是一个蝶丛....满是蝴蝶和花
草....还有那沁人心脾的花的芬芳....，茂密的花草遮蔽了道路，
使你连方向都弄不清楚，一个声音在你的脑海中回荡：
        “别出去了，就留在这人间仙境吧...........!!!!”
LONG
        );
        set("outdoors", "oldpine");
        
        setup();
}

void reset()
{
        ::reset();
        set("exits", ([ /* sizeof() == 5 */
          "south" : __DIR__"diecong" + (random(6)+1),
          "north" : __DIR__"diecong" + (random(6)+1),
          "west" : __DIR__"diecong" + (random(6)+1),
          "east" : __DIR__"diecong" + (random(6)+1),
          "northwest" : "quest/liandan/hudiegu",
        ]));
}

int valid_leave(object me, string dir)
{
        write("你实在弄不清楚方向....");
        switch(dir) {
                case "north":   write("北边....北边是哪里呢？....");    break;
break;
                case "east":    write("东边....东边....");      break;
                case "south":   write("南边....哪里是南边？....");      break;
break;
                case "west":    write("西边....嗯....");        break;
                default:
                        write("该往哪里走呢....");
        }
        write("就是这个方向吧。\n");
        return 1;
}
