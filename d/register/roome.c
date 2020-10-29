// regiser: roome.c
// by Doing

inherit ROOM;

void create()
{
        set("short", "桃源竹屋");
        set("long", @LONG
这里是一间小竹屋，朴素异常，屋中立着一位气宇轩昂的大汉，正
满怀笑意的看着你。
LONG );
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/lu" : 1,
        ]));
        set("exits", ([
                "west"  : __DIR__"entry",
                "out"   : __DIR__"yanluodian",
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (! objectp(ob = present("lu tianshu", this_object())))
        {
                ob = new(__DIR__"npc/lu");
                ob->move(this_object());
        }

        ob->check_leave(me, dir);
        return ::valid_leave(me, dir);
}