#include <ansi.h>
#include <armor.h>
inherit ARMOR;

void create()
{
        set_name(HIG "文曲星甲" NOR, ({ "wisdom armor", "armor", }));  
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "蕴含了文曲星的精元和无上智慧(神)。\n"); 
                set("unit", "件");
                set("value", 2000000);
                set("material", "cloth");
                set("armor_prop/armor", 100);
        }
        set("auto_load", 1); 
        set("mod_mark", "A2000");  
        set("mod_level", "M2000");  
        set("mod_name", HBGRN"文曲星学习套装(神)"NOR); 

        set("enchase", ([ 
                "flute" : 2,
                "used"  : 2,
                "apply_prop" : ([ /* sizeof() == 4 */
                        "study_effect" : 10,
                        "int" : 8,
                        "practice_effect" : 10,
                        "armor" : 30,
                ]),
        ]));

        set("insert", ({ /* sizeof() == 1 */
                ([
                        "id" : "magic stone",
                        "name" : HIM"玄石"NOR,
                        "apply_prop" : ([ /* sizeof() == 2 */
                                "armor" : 30,
                                "int" : 8,
                        ]),
                ]),
                ([
                        "id" : "magic stone",
                        "name" : HIM"玄石"NOR,
                        "apply_prop" : ([ /* sizeof() == 2 */
                                "study_effect" : 10,
                                "practice_effect" : 10,
                        ]),
                ]),
        }));
        
        set("quality_level", 2);  
       
        setup();
}
