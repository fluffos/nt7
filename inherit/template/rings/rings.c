// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// armor.c
// 自动创建防具的基准文件。                             /* COMMENT_EXIT  */

#include <armor.h>
inherit RINGS;

#include <template/armor.h>
void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("戒指", ({ "ring", }));                /* NAME_EXIT  */ 

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "这是一枚普通的戒指。\n");  /* DBASE_EXIT  */
                set("unit", "枚");
                set("value", 200);
                set("material", "gold");
                set("armor_prop/armor", 1);
        }

        set_weight(200);
        setup();
}
