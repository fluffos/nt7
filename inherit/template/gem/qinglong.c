// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit TESSERA;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(HIG "青龙·木" NOR, ({"qing long", "wood"})); /* NAME_EXIT  */
        set_weight(20);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", HIG "可用于镶嵌10LV，属性木。\n" NOR); /* DBASE_EXIT  */
                set("value", 100000);
                set("unit", "块");
                set("can_be_tessera", 1);
                set("magic/type", "wood");
                set("magic/power", 500);
        }
        setup();
}

