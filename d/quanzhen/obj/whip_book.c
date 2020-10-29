// Code of ShenZhou
// /d/zhongnan/obj/whip_book.c
inherit ITEM;

void create()
{
        set_name("丹阳鞭法谱", ({ "whip book", "book" }));
        set_weight(600);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
                set("long",
                        "「丹阳鞭法谱 -- 上卷」\n");
                set("value", 200);
                set("material", "paper");
                set("skill", ([
                        "name":         "whip",                        // name of the skill
                        "exp_required":        1000,                        // minimum combat experience required
                                                                // to learn this skill.
                        "jing_cost":    30,                        // jing cost every time study this
                        "difficulty":        30,                        // the base int to learn this skill
                                                                // modify is jing_cost's (difficulty - int)*5%
                        "max_skill":        150                        // the maximum level you can learn                                                        // from this object.
                ]) );
        }
}