// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit TESSERA;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(HIY "黄宝石" NOR, ({ "topaz" }) );           /* NAME_EXIT  */
        set_weight(20);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", HIY "一颗黄色的宝石。\n" NOR);  /* DBASE_EXIT  */
                set("value", 50000);
                set("unit", "颗");
                set("level", 2);
                set("material", "topaz");
                set("can_be_enchased", 1);
                set("magic/type", "earth");
                set("magic/power", 120);
                set("auto_load", 1);
        }
        set("enchase/weapon_prop/add_earth", 2);
        set("enchase/rings_prop/add_earth", 2);
        set("enchase/armor_prop/reduce_water", 1);
                                 
        setup();
}

