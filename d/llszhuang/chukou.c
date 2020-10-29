// chukou.c

#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "墓林");
  set("long",
"这里是丧生在山庄里的江湖侠客的墓林,一块块墓碑(mubei)立在路边\n"
".\n似乎是在告诉来这里的人RED~~~千万要小心啊!~~~NOR\n"
);
        set("item_desc", ([
            "mubei": HIG "\n上面写着--赶快走吧,这里不是久留之地啊!(leave here)\n" NOR,
    ]));
        set("no_fight",1);
        set("no_die",1);
        setup();
}

int init()
{
        add_action("do_leave","leave");
}
int do_leave(string arg)
{
        object me;
        object *inv;
        int i;
        me = this_player();
        inv = all_inventory(me);
    if ( !arg || arg !="here" )
        return notify_fail("你真的要走?是leave here \n");

        for( i=0;i<sizeof(inv);i++)
{
                if( inv[i]->is_character() )
                   return notify_fail("你不能背着人进去!\n");
}
       write(YEL"你终于离开了这鬼地方!\n"NOR);
        me->move("/d/city/wumiao");
        return 1;
}
