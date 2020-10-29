// advance_unarmed.c

inherit BOOK;

void create()
{
        set_name("本草纲目", ({ "bencao gangmu", "book" }));
        set_weight(600);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long",
"封面上写著「本草纲目」，是一个医学的百科全书。\n");
                set("value", 2000);
                set("material", "paper");
                set("skill", ([
                        "name":         "medical",
                        "exp_required": 1000,
                        "jing_cost":    30,
                        "difficulty":   25,
                        "max_skill":    2100,
                ]));
        }
}
