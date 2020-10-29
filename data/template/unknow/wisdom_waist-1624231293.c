// wisdom_waist.c
// Create by TEMPLATE_D. Wed Apr  3 18:17:48 2019.
#include <ansi.h>
#include <armor.h>
inherit WAIST;

void create()
{
	set_name("[1;32m文曲星束带[2;37;0m", ({ "wisdom waist" }));

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
	set("long", "蕴含了文曲星的精元和无上智慧(神)。
");
	set("unit", "件");
	set("value", 2000000);
	set("material", "cloth");
	set("armor_prop", ([ /* sizeof() == 1 */
  "armor" : 10,
]));
        }
	set("auto_load", 1);
	set("mod_mark", "A2002");
	set("mod_level", "M2000");
	set("mod_name", "[42;1m文曲星学习套装(神)[2;37;0m");
	set("enchase", ([ /* sizeof() == 3 */
  "flute" : 2,
  "used" : 2,
  "apply_prop" : ([ /* sizeof() == 4 */
      "learn_effect" : 10,
      "int" : 8,
      "armor" : 30,
      "derive_effect" : 10,
    ]),
]));










	set("insert", ({ /* sizeof() == 2 */
  ([ /* sizeof() == 3 */
    "id" : "magic stone",
    "apply_prop" : ([ /* sizeof() == 2 */
        "int" : 8,
        "armor" : 30,
      ]),
    "name" : "[1;35m玄石[2;37;0m",
  ]),
  ([ /* sizeof() == 3 */
    "id" : "magic stone",
    "apply_prop" : ([ /* sizeof() == 2 */
        "learn_effect" : 10,
        "derive_effect" : 10,
      ]),
    "name" : "[1;35m玄石[2;37;0m",
  ])
}));


















	set("quality_level", 2);

	set("armor_type", "waist");
	set("no_sell", 1);
	set("stable", 0);
	set("consistence", 100);
	set("set_data", 1);
	set("no_store", 1);
	set("item_owner", "ovo");
        setup();
}
int receive_summon(object me)
{
        return ITEM_D->receive_summon(me, this_object());
}

// 隐藏物品
int hide_anywhere(object me)
{
        return ITEM_D->hide_anywhere(me, this_object());
}


int is_no_clone() { return 1; }

