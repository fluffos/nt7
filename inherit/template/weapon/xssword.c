// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// sword.c
// 自动创建剑的基准文件。                               /* COMMENT_EXIT  */

#include <weapon.h>

inherit XSWORD;

#include <template/weapon.h>

void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("萧", ({ "xssword", }));               /* NAME_EXIT  */

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "这是一柄普通的萧。\n");    /* DBASE_EXIT  */
                set("unit", "柄");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n收回。\n");
        }

//**    $function_name($argument);                      /* FUNCTION_ENTRY */
        set_weight(5000);
        init_xsword(5, 2);                              /* FUNCTION_EXIT  */
        setup();
}
