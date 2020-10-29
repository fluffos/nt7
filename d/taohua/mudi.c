#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "墓地");
        set("long", @LONG
这里是桃花岛岛主夫人的墓地。墓地周围种了一些矮矮的
花树。树上的白花星星点点。白花中间是块石碑 (bei)，碑后
是两扇坚固的石门。墓地干干净净，显然天天有人打扫。
LONG);
        set("outdoors", "taohua");
        set("exits", ([
//                "south" : __DIR__"road3",
                "east"  : __DIR__"taolin",
                "north" : __DIR__"road1",
        ]));
        set("item_desc", ([
                "bei": WHT "\n石碑上刻着：「" HIR "桃花岛女主冯氏"
                       "埋香之墓" NOR + WHT "」\n" NOR
        ]) );
        set("no_clean_up", 0);
        set("coor/x", 8970);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_push", "push");
}

void check_trigger()
{
        object room;

        if ((int)query("left_trigger") == 3
           && (int)query("right_trigger")==3
           && ! query("exits/down"))
        {
                message("vision", HIY "\n墓门忽然轧轧作响，缓缓向两边移动著，露"
                                  "出一个向下的阶梯。\n\n" NOR, this_object());
                set("exits/down", __DIR__"mudao");
                if (room = find_object(__DIR__"mudao"))
                {
                        set("exits/up", __FILE__, room);
                        message("vision", HIY "\n墓门忽然轧轧作响，缓缓向两边移"
                                          "动著，露出一个向下的阶梯。\n\n" NOR,
                                          room);
                }
                delete("left_trigger");
                delete("right_trigger");
                call_out("close_passage", 30);
        }
}

void close_passage()
{
        object room;

        if (! query("exits/down"))
                return;

        message("vision", WHT "\n墓门忽然发出轧轧的声音，缓缓合拢，将向下的通道"
                          "盖住了。\n\n" NOR, this_object());

        if (room = find_object(__DIR__"mudao"))
        {
                delete("exits/up", room);
                message("vision", WHT "\n墓门忽然发出轧轧的声音，缓缓合拢，将向"
                                  "上的通道盖住了。\n\n" NOR, room);
        }
        delete("exits/down");
}

int do_push(string arg)
{
        string dir;

        if (! arg || arg == "" )
                return 0;

        if (query("exits/down"))
        {
                write("墓门都已经开了，你还推墓碑干嘛。\n" NOR);
                return 1;
        }

        if (arg == "bei" )
        {
                write(HIC "你试著推动墓碑，发现它可以左右推动。\n" NOR);
                return 1;
        }

        if( query("max_neili", this_player())<1000 )
        {
                write("你试著推动墓碑，可怎么也推之不动。\n");
                return 1;
        }

        if (sscanf(arg, "bei %s", dir) == 1)
        {
                if (dir == "right")
                {
                        message_vision(WHT "$N" WHT "将墓碑往右推去，忽然轧轧几声"
                                       "墓碑又移回原位。\n" NOR, this_player());
                        addn("right_trigger", 1);
                        check_trigger();
                        return 1;
                } else
                if (dir == "left")
                {
                        message_vision(WHT "$N" WHT "将墓碑往左推去，忽然轧轧几声"
                                       "墓碑又移回原位。\n" NOR, this_player());
                        addn("left_trigger", 1);
                        check_trigger();
                        return 1;
                } else
                {
                        write("你要将墓碑推向那个方向？\n");
                        return 1;
                }
        }
}

void reset()
{
        ::reset();
        delete("left_trigger");
        delete("right_trigger");
}