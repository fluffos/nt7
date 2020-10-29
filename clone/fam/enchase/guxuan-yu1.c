inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIB "古玄玉（1级）" NOR, ({"guxuan yu1", "yu1"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("long", HIB "这是一块通体黑色的古玉，只有不到小拇指一半的大小，拥有辟邪的作用，\n"
                                "古玄玉又称黑玉，通常镶绣于护身符之上，用于驱邪避灾，祈求神灵庇佑。\n" HIY
                                "使用方式：镶嵌于护身符上，增加气运 +1\n " NOR);
                set("value", 500000);
                set("enchase/name", "古玄玉（1级）");
                set("enchase/qy", 1);
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
