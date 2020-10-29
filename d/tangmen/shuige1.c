//shuige1.c                四川唐门—亭榭水阁

#include <ansi.h>
#include <room.h>
inherit ROOM;

void away(object obj);

void create()
{
        set("short", "亭榭水阁");
        set("long",
"这里是莲藕小筑的亭榭水阁。这里与莲藕小筑连为一体，同样是古玉\n"
"色的建筑。水阁四壁上绘着各色的山水鱼虫，从这里向前通向莲云阁，而\n"
"身后一扇大门紧闭着挡住了退路！\n"
);
        set("exits", ([
                "north" : __DIR__"shuige2",
                "south" : "/d/tangmen/qianyuan",
                "east" : __DIR__"chashi",
                "west" : __DIR__"menwei",
        ]));
        set("area", "tangmen");
        setup();
}
void init()
{
        add_action("do_open","open");
}

int do_open(string arg)
{
        object ob, room;
        ob = this_player();

        if ( query("exits/out") )
                return notify_fail("门已经是开着的了。\n");

        if ( !( room = find_object(__DIR__"xiaozhu")) )
                room = load_object(__DIR__"xiaozhu");

        if ( arg && arg=="door" && objectp(room) )
        {
                message_vision(HIC "你用力将大门拉开。\n" NOR, ob);
                set("exits/out", __DIR__"xiaozhu");
                set("exits/enter", __DIR__"shuige1", room);
                remove_call_out("close");
                call_out("close", 60, this_object());
                return 1;
        }
        else
                return 0;
}

void close()
{
        object room;

        if ( !( room = find_object(__DIR__"xiaozhu")) )
                room = load_object(__DIR__"xiaozhu");

        if( this_object() == environment(this_player()) || room == environment(this_player()))
                message("vision",HIR"大门悄无声息的关了起来。\n"NOR, this_player());
        delete("exits/out");
        if ( objectp(room) )
                delete("exits/enter", room);
}        

int valid_leave(object me, string dir)
{
        object obj, room;

        if ( !( room = find_object(__DIR__"menwei")) )
                room = load_object(__DIR__"menwei");

        if( (dir == "out") && (query("combat_exp", me) <= 200000) && !wizardp(me) && !query("tangmen/xin", me) )
                if ( objectp(present("men wei", environment(me)) ) )
                {
                        obj = present("men wei", environment(me));
                        message_vision("门卫对着$N大声喊道：“你的武功还不够高，别出去给唐家丢人了！”\n",me);
                        remove_call_out("away");
                        call_out("away", 60, obj);
                        return notify_fail("\n你忽然想起师傅好象曾经告诉过你，只有功夫厉害了才能被允许出门闯荡江湖。\n");
                }
                else
                        if ( objectp(room) && objectp(present("men wei", room)) )
                        {
                                obj = present("men wei", room);
                                tell_room(room, "门卫好象听到了什么声响，眉头一皱自语到：“是谁又想擅自出门！我得去看看!”\n门卫快步向东走去。\n");
                                tell_room(this_object(), "门卫快步从西边的屋中走过来。\n");
                                obj->move(__DIR__"shuige1");
                                message_vision("门卫对着$N大声喊道：“你的武功还不够高，别出去给唐家丢人了！”\n",me);
                                remove_call_out("away");
                                call_out("away", 60, obj);
                                return notify_fail("\n你忽然想起师傅好象曾经告诉过你，只有功夫厉害了才能被允许出门闯荡江湖。\n");
                        }

        return ::valid_leave(me, dir);
}

void away(object obj)
{
        string name;
        object room;

        if (! objectp(obj)) return;
        if ( !( room = find_object(__DIR__"menwei")) )
                room = load_object(__DIR__"menwei");

        if( living(obj) )
        {
                if (  !obj->busy() && !obj->is_fighting() )
                {
                        message_vision("$N摇了摇头，笑着说:“现在这些小子真不知天高地厚，可一出去就给唐家丢人。”\n$N向差房走去。\n", obj);
                        tell_room(room, "门卫快步从水阁那边走过来。\n");
                        obj->move(__DIR__ "menwei");
                }
                else
                {
                        remove_call_out("away");
                        call_out("away", 60, obj);
                }
        }
        return;
}