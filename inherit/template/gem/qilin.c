// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit TESSERA;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(YEL "麒麟·土" NOR, ({"qi lin", "earth"})); /* NAME_EXIT  */
        set_weight(20);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", YEL "可用于镶嵌10LV，属性土。\n" NOR); /* DBASE_EXIT  */
                set("value", 100000);
                set("unit", "块");
                set("can_be_tessera", 1);
                set("magic/type", "earth");
                set("magic/power", 500);
        }
        setup();
}

