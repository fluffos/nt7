// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// axe.c
// 自动创建斧头的基准文件。                             /* COMMENT_EXIT  */

#include <weapon.h>

inherit PIN;

#include <template/weapon.h>

void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("绣花针", ({ "pin", }));               /* NAME_EXIT  */

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "这是一把普通的绣花针。\n");/* DBASE_EXIT  */
                set("unit", "把");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一把$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n藏于袖间。\n");
        }

//**    $function_name($argument);                      /* FUNCTION_ENTRY */
        set_weight(50);
        init_pin(5, 2);                                 /* FUNCTION_EXIT  */
        setup();
}
