inherit ROOM;

void create()
{
        set("short", "练武场");
        set("long", @LONG
这里就是药王谷的弟子平时练功的地方，不少弟子在这里打拳
踢腿。正中是一副一人多高的梅花桩(zhuang)，你可以跳(jump)
上去走桩练习轻功。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"tulu1",
]));

        set("NO_NPC", 1);

        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();
        string out;

        if(arg != "zhuang" && arg != "梅花桩")
        {
                write("你要跳到哪里？\n");
                return 1;
        }

        out = "$N纵身跳上梅花桩。\n";

        if(me->query_skill("dodge", 1) < 30)
        {
                out += "身子晃了几下，摔了下来。\n";
                message_vision(out, me);
                me->receive_wound("qi",query("max_qi", me)/4,"trip");
                me->start_busy(2);
                return 1;
        }

        message_vision(out, me);
        if(!me->move(__DIR__"zhuang1"))
        {
                tell_object(me, "你看了看上面人太多，又跳了回去。\n");
                tell_room(__FILE__, me->name()+"跳了下来。\n", ({me}));
                return 1;
        }

        me->start_busy(2);
        return 1;
}
