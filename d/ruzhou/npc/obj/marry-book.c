// Obj: /d/ruzhou/npc/obj/marry-book.c 结婚须知
#include <ansi.h>

inherit ITEM;

void init()
{
        add_action("do_read", "fan");
}

void create()
{
        set_name("《结婚须知》", ({ "jiehun xuzhi", "xuzhi"}));
        set("weight", 600);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
                set("value", 500);
                set("material", "paper");
                set("long", "这本书上写着本MUD结婚的程序，你可以翻阅(fan)它。\n");
        }
        setup();
}

int do_read(string arg)
{
    if (!arg||(arg!="jiehun xuzhi"&&arg!="xuzhi"))
        return notify_fail("你没有这本书，乱翻口袋干什么？\n");
    this_player()->start_more(read_file("/doc/help/marry"));
    return 1;
}