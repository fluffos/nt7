// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit TESSERA;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(HIR "红宝石" NOR, ({ "ruby" }) );           /* NAME_EXIT  */
        set_weight(20);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", HIR "一颗红色的宝石。\n" NOR);  /* DBASE_EXIT  */
                set("value", 50000);
                set("unit", "颗");
                set("level", 2);
                set("material", "ruby");
                set("can_be_enchased", 1);
                set("magic/type", "fire");
                set("magic/power", 120);
                set("auto_load", 1);
        }
        set("enchase/weapon_prop/add_fire", 2);
        set("enchase/rings_prop/add_fire", 2);
        set("enchase/armor_prop/reduce_metal", 1);
        setup();
}

