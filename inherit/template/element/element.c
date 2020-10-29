// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit ITEM;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(YEL "元素" NOR, ({ "element" }));              /* NAME_EXIT  */
        set_weight(10);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", YEL "从特殊的水晶中粹取出来的元素粉末。\n" NOR); /* DBASE_EXIT  */
                set("value", 100);
                set("unit", "颗");
        }
        setup();
}

