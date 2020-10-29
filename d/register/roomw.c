// regiser: roome.c
// by Doing

inherit ROOM;

void create()
{
        set("short", "桃源石屋");
        set("long", @LONG
这里是一间小石屋，看不出有什么特别，屋中立着一位正气凛然的
大汉，正盯着你看。
LONG );
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/hua" : 1,
        ]));
        set("exits", ([
                "east"  : __DIR__"entry",
                "out"   : __DIR__"yanluodian",
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (! objectp(ob = present("hua tiegan", this_object())))
        {
                ob = new(__DIR__"npc/hua");
                ob->move(this_object());
        }

        ob->check_leave(me, dir);
        return ::valid_leave(me, dir);
}