// mingyu.c

inherit BOOK;
inherit F_UNIQUE;
 
void create()
{
        set_name("「明玉神功」", ({ "mingyu shengong", "mingyu", "shengong" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long",
"这是一本薄薄的密集，记载着无敌于天下的明玉功秘诀。\n",
        );
                set("value", 1);
                set("no_sell", 1);
                set("no_put", 1);
                set("no_give", 1);
                set("no_get", 1);
                set("material", "paper");
                set("skill", ([
                        "name"        : "mingyu-gong",
                        "exp_required":  100000,
                        "jing_cost"   :  120,
                        "difficulty"  :  40,
                        "max_skill"   :  400,
                ]) );
        }
}

int query_autoload() { return 1; }
