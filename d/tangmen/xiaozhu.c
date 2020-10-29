//xiaozhu.c                四川唐门—莲藕小筑

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "莲藕小筑");
        set("long",
"这里是距蜀中唐门不远的莲藕小筑。莲藕小筑是栋古玉色的建筑看来\n"
"雅致简朴，但有多少江湖高手为了越此一步，都尸横遍地不可得呢！一扇\n"
"厚重的大门(door)紧紧的闭着。\n"
);
        set("item_desc", ([
                "door" : "这是一扇极其厚重的大门，两个紫铜门环便足有碗口大小。\n"NOR,
        ]));
        set("area", "tangmen");
        setup();
}

void init()
{
        add_action("do_knock","knock");
        add_action("do_open","open");
}

int do_open(string arg)
{
        object ob;
        ob = this_player();

        if ( arg && arg=="door" )
        {
                message_vision(HIC "$N双手用力想推开大门，但大门显然从里面锁住了。\n" NOR, ob);
                return 1;
        }
}

int do_knock(string arg)
{
        object ob, room;

        ob = this_player();

        if ( query("exits/enter") )
                return notify_fail("门已经是开着的了。\n");

        if ( !( room = find_object(__DIR__"shuige1")) )
                room = load_object(__DIR__"shuige1");

        if ( arg && arg=="door" && objectp(room) )
        {
//                message_vision(HIC "$N伸手小心翼翼的扣动门环。\n忽听一人怩声怩气的道：“何必为难呢？有胆就进小筑里来吧，我正恭候光临哩！。\n大门悄无声息的打开了。\n" NOR, ob);
                message_vision(HIC "$N用力扣动门环，大门悄无声息的打开了。\n" NOR, ob);
                set("exits/enter", __DIR__"shuige1");
                set("exits/out", __DIR__"xiaozhu", room);
                remove_call_out("close");
                call_out("close", 5, this_object());
                return 1;
        }
        else
                return 0;
}

//void close(object room)
void close()
{
        object room;

        if ( !( room = find_object(__DIR__"shuige1")) )
                room = load_object(__DIR__"shuige1");

        if( this_object() == environment(this_player()) || room == environment(this_player()))
                message("vision",HIR"大门悄无声息的关了起来。\n"NOR, this_player());
        
        delete("exits/enter");
        if ( objectp(room) )
                delete("exits/out", room);
}        