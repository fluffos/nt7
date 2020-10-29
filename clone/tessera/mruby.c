// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit TESSERA;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(HIR "神之红宝石" NOR, ({ "magic ruby" }) );  /* NAME_EXIT  */
        set_weight(20);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", HIR "一颗焕发着奇异的光彩的红宝石，给人以不同寻常的感觉。\n" NOR);  /* DBASE_EXIT  */
                set("value", 200000);
                set("unit", "颗");
                set("level", 4);
                set("material", "mruby");
                set("can_be_enchased", 1);
                set("magic/type", "fire");
                set("magic/power", 500);
                set("auto_load", 1);
        }
        set("no_identify", 1);
	setup();
}
