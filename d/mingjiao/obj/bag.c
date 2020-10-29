// bag.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("油布包", ({ "bag", "bao" }));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "个");
                set("long", "这是一个油布包裹。\n");
                set("value", 500);
                set("material", "cloth");
        }
        set("book_count", 0);
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_open", "open");
                add_action("do_open", "unpack");
                add_action("do_open", "dakai");
        }
}

int do_open(string arg)
{
        object me=this_player(), book;
        object where;

        if (! arg || ! id(arg))
                return 0;

        if( !query("jiuyang/zhang", me) )
        {
                write("什么？\n"); 
                return 1; 
        }

        if (query("book_count") < 1)
        {
                write("油布包里面什么也没有了。\n");
                return 1;
        }

        me = this_player();
        where = environment(me);
        message_vision("$N轻轻地把油布包来看时，里面原来是一本"
                       "薄薄的经书，只因油布包得紧密，虽长期藏"
                       "在猿腹之中，书页仍然完好无损。\n", me);
        book = new("/clone/book/jiuyang-book");
        book->move(file_name(where));
        addn("book_count", -1);
        return 1;
}