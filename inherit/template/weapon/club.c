// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// axe.c
// 自动创建斧头的基准文件。                             /* COMMENT_EXIT  */

#include <weapon.h>

inherit CLUB;

#include <template/weapon.h>

void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("棍", ({ "club", }));                  /* NAME_EXIT  */

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "这是一根普通的棍。\n");    /* DBASE_EXIT  */
                set("unit", "根");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一根$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n背到背上。\n");
        }

//**    $function_name($argument);                      /* FUNCTION_ENTRY */
        set_weight(5000);
        init_club(5, 2);                                /* FUNCTION_EXIT  */
        setup();
}
