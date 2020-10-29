// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// armor.c
// 自动创建防具的基准文件。                             /* COMMENT_EXIT  */

#include <armor.h>
inherit SURCOAT;

#include <template/armor.h> 
void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("披风", ({ "surcoat", }));               /* NAME_EXIT  */

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "这是一件普通的披风。\n");  /* DBASE_EXIT  */
                set("unit", "件");
                set("value", 200);
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }

        set_weight(500);
        setup();
}

