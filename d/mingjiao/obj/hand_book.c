// hand_book.c

inherit ITEM;

void create()
{
        set_name("鹰爪手法", ({ "yingzhua shoufa", "shoufa", "book" }));
        set_weight(1000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
                set("long","这是一本讲述基本手法要领的书籍。\n");
                set("value", 100);
                set("material", "paper");
                set("unique", 1);
                set("treasure",1);
                set("skill", ([
                        "name":"claw",       // name of the skill
                        "exp_required": 1000, // minimum combat experience required
                                              // to learn this skill.
                        "jing_cost": 20,      // jing cost every time study this
                        "difficulty": 20,     // the base int to learn this skill
                                              // modify is jing_cost's (difficulty - int)*5%
                        "max_skill": 30       // the maximum level you can learn
                                              // from this object.
                ]));
        }
}