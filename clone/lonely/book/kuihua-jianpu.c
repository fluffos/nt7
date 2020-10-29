#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(HIW "「葵花剑谱」" NOR, ({ "kuihua jianpu", "kuihua", "jianpu"}));
        set_weight(500);
        /*if (clonep())
               set_default_object(__FILE__); 
        else*/ {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIW "\n这是一本用薄纸写成的书，封皮上写有「葵花剑"
                            "谱」四\n字。你可以试着读读(read)看。\n\n" NOR, );
        }
}

void init()
{
        add_action("do_du", "read");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;

        string skill, book, msg;
        int lv;

        if (! arg)
        {
                write("研读葵花剑谱指令格式：read <技能> from <葵花剑谱>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        {
                write("研读葵花剑谱指令格式：read <技能> from <葵花剑谱>\n");
                return 1;
        }

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

        if( query("no_fight", where )
            && query("doing", me) != "scheme" )
        {
                write("你无法在这里静下心来研读葵花剑谱。\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是个文盲，先学点文化(literate)吧。\n");
                return 1;
        }

        if (! id(book))
        {
                write("这里没有这本书。\n");
                return 1;
        }

        if (skill != "辟邪劍影" && skill != "辟邪剑影")
        {
                write("葵花剑谱上并没有记载你打算研究的内容。\n" NOR);
                return 1;
        }

        if (me->query_skill("pixie-jian", 1) < 1000)
        {
                write("你辟邪剑法修为不足，无法领悟到其中奥妙。\n");
                return 1;
        }
        
        if (me->query_skill("dodge", 1) < 1000)
        {
                write("你基本轻功修为不足，无法领悟到其中奥妙。\n");
                return 1;
        }
                
        if( !query("yuanshen_level", me) )
        {
                write("你未修炼成元神，无法领悟其中奥妙。\n");
                return 1;                
        }
        
        if( query("combat_exp", me)<10000000 )
        {
                write("你的实战经验不足，再怎么读也没用。\n");
                return 1;
        }

        if( query("jing", me)<100
            || query("qi", me)<100
            || query("neili", me)<200 )
        {
                write("你现在过于疲倦，无法专心下来研读新知。\n");
                return 1;
        }

        write(HIW "你学会了「" HIG "辟邪劍影" HIW "」。\n" NOR);
        set("can_perform/pixie-jian/jian", 1, me);
        destruct(this_object());
        return 1;

}
