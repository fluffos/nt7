
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "「天擎秘气」" NOR, ({ "tianqing miqi", "tianqing", "miqi"}));
        set_weight(500);
        /*if (clonep())
               set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIY "\n这是一本用薄纸写成的书，封皮上写有「天擎秘气」四\n"
                                "字。你可以试着读读(readtq)看。\n\n" NOR, );
        }
}

void init()
{
        add_action("do_du", "readtq");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;

        string skill, book, msg;
        int lv;

        if (me->is_busy())
        {
                write("你现在正忙着呢。\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("你无法在战斗中专心下来研读新知！\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是个文盲，先学点文化(literate)吧。\n");
                return 1;
        }

        msg = HIG "$N" HIG "翻看秘籍，仔细研究上面所记载的内容，霎那间忽有所悟……\n" NOR;
        message_vision(msg, me); 


        write(HIW "你学会了「" HIG "天擎秘气" HIW "」特技。\n" NOR);
        me->set("special_skill/tianqing", 1);
        destruct(this_object());
        return 1;
}

