#include <ansi.h>
inherit ITEM;

string book_name();
void create()
{
        set_name("不知名的书", ({"noname book"}));
        set_weight(10);
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一本破破旧旧的书，不知道是用什么文字写成的。\n");
                set("unit", "本");
                set("material", "paper");
                set("value", 2000);
                set("no_sell", 1);
                set("skill", ([
                        // "name":         (: book_name :),// name of the skill
                        "name":         "freezing-force",// name of the skill
                        "family_name":         "星宿派",// name of the family
                        "jing_cost":    100,            // jing cost every time study this
                        "difficulty":   50,             // the base int to learn this skill
                        "max_skill":    180,            // the maximum level you can learn
                ]) );
        }
}

string book_name()
{
        if( random(2) ) return "freezing-force";
        return "bingcan-duzhang";
}
