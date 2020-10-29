#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW"精灵物语"NOR, ({ "spirit book", "book"}));
        set_weight(0);
        /*if( clonep() )
            set_default_object(__FILE__);
        else*/ {
            set("unit", "本");
            set("long","一本薄薄的《精灵物语》，扉页上写着：\n\n      "HIC"梦与现实的交界\n\n"NOR);
            set("value", 2000000);
            set("material", "paper");
            set("skill", ([
                "name": "literate",    // name of the skill
                "exp_required": 1000,    // minimum combat experience required
                "jing_cost":    2,    // jing cost every time study this
                "difficulty":   10,    // the base int to learn this skill
                "max_skill":   160,    // the maximum level you can learn to
                "min_skill":   10,    // minimun level required
            ]) );
        }
}
int query_autoload()
{
        return 1;
}

void init()
{
    add_action("do_getblade","getblade");
}
int do_getblade(string arg)
{
  object me = this_player ();
        object ob;

        if( !query_temp("spiritagree", me) && query("id", me) != "night" )
                return notify_fail("你没得到夜辰允许，精灵界怎么会为你开启呢？\n");  
        if (  present("spirit blade", me) ) 
                return notify_fail("你身上不是有一把吗？\n");  
        if( query("jing", me)<100 )
                return notify_fail("你的精神无法集中，不要勉强！\n");
        message_vision(HIY"$N"+HIY"摊开"NOR+HIW"《精灵物语》"NOR+HIY"，口中念念有词。\n"NOR, me); 
        message_vision(HIY"光芒乍起，一柄薄如羽翼，轻如晓风的精灵刀出现在光芒中。\n"NOR, me);

         me->receive_damage("jing", 90);
        ob = new("/u/night/obj/blade");
        ob->move(me);
        return 1;
}
