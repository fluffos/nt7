#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"擂台"NOR);
        set("long", @LONG
这是一个四方的大擂台，擂台北面挂着一张厚厚的布帘子，你感
觉到一股浓厚的杀气从布帘后散发出来，弥漫在空气里，直钻入你内
心。
LONG );

    set("no_beg",1);
    set("no_steal",1);
    set("biwu_room",1);

    set("objects",([
    ]));

    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_get","get");
    add_action("do_put","put");
    add_action("do_drop","drop");
    add_action("do_summon","summon");
}

int do_get()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在这里你想干什么？\n");
    return 1;
}

int do_drop()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在这里你想干什么？\n");
    return 1;
}

int do_put()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在这里你想干什么？\n");
    return 1;
}

int do_summon()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在这里你想干什么？\n");
    return 1;
}
