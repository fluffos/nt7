// newbie.c

#include <ansi.h>
#include <command.h>

inherit ITEM;

int do_read(string arg);

void create()
{
        set_name(HIW"新手入门必读"NOR, ({"book", "newbie book"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
                set("long", "这是盘古给新手们准备的书，不管你泥龄"
                            "如何，如果进了泥潭务必看看。\n");
        }
        setup();
}

void init()
{
        add_action("do_read", "read");
}
 
int do_read(string arg)
{
        if (! arg || arg != "book")
                return notify_fail("你要读什么？要想读书请输入(read book)。\n");

        return HELP_CMD->main(this_player(), "feature");
}