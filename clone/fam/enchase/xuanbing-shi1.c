inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "玄冰石（1级）" NOR, ({"xuanbing shi1", "shi1"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("long", HIW "这是一块通体白色的玉石，产自极北之地，传说即使是掘千尺而不可得，\n"
                                "可见玄冰石是极其的稀有，以至只有当朝达官贵人和地位显赫之人才拥有。\n"
                                "玄冰石又称白玉，通常别绣于锦囊或护身符之上，意味着地位显赫，诸神\n"
                                "庇佑。\n" HIY
                                "使用方式：镶嵌于护身符上，增加福缘 +1\n " NOR); 
                              
                set("value", 500000);
                set("enchase/name", "玄冰石（1级）");
                set("enchase/fy", 1);
                set("enchase/point", 1);
                set("enchase/type", "myheart");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );
        }
        setup();
}

int query_autoload()
{
        return 1;
}
