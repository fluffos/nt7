// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit TESSERA;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(HIB "蓝宝石" NOR, ({ "sapphire" }) );           /* NAME_EXIT  */
        set_weight(20);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", HIB "一颗蓝色的宝石。\n" NOR);  /* DBASE_EXIT  */
                set("value", 50000);
                set("unit", "颗");
                set("level", 2);
                set("material", "sapphire");
                set("can_be_enchased", 1);
                set("magic/type", "water");
                set("magic/power", 120);
                set("auto_load", 1);
        }
        set("enchase/weapon_prop/add_water", 2);
        set("enchase/rings_prop/add_water", 2);
        set("enchase/armor_prop/reduce_fire", 1);
        setup();
}

