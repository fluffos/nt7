// xuemai.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIR "血脉丹方" NOR, ({ "xuemai danfang", "miben", "xuemai", "danfang" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long", "这是一本泛黄的书籍，上面用小篆书"
                            "写着“血脉丹方”几个字。\n",

                );
                set("material", "paper");
                set("skill", ([
                        "name": "liandan-shu",
                        "jing_cost": 90,
                        "difficulty": 200,
                        "max_skill": 600,
                        "min_skill": 30,
                ]));

                set("can_make", ([
                        "xuemai1"   : 2700,        
                        "xuemai2"   : 2700,       
                        "xuemai3"   : 2700,      
                        "xuemai4"   : 3000,      
                        "xuemai5"   : 3000, 
                        "xuemai6"   : 3000,     
                        "xuemai7"   : 3300,     
                        "xuemai8"   : 3300,     
                        "xuemai9"   : 3600,     
                        "xuemai10"  : 3900,     
                ]));
        }
        setup();
}

