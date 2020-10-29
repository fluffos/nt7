// wineskin.c  酒袋

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("酒壶", ({"jiuhu", "hu"}));
        set_weight(700);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一个用来装酒的酒壶，大概装得八、九两的酒。\n");
                set("unit", "个");
                set("value", 20);
                set("max_liquid", 15);
        }
          set("liquid",([
                "type": "alcohol",
                "name": "烧刀子",
                "remaining": 15,
                "drunk_supply": 15,
        ]));
}
