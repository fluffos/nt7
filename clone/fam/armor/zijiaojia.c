#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name(NOR + MAG "紫蛟鳞甲" NOR, ({ "zijiao linjia", "zijiao", "linjia" }));
        set_weight(9000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "副");
                set("long", NOR + MAG "\n一副充满着神奇力量的鳞甲，散发着摄人心魄的寒芒。\n" NOR
                            HIC "有效招架修正：+ 50        有效轻功修正：+ 30\n" NOR
                            HIC "抗毒效果修正：+ 30%       防御效果等级： 200\n" NOR
                            HIC "抗毒回避修正：+ 15%\n" NOR);

                set("material", "dragon");
                set("material_name", "紫蛟须、紫蛟皮革、紫蛟筋、地脉血泉");
                set("can_summon", 1);
                set("summon_id", "zijiaojia");
                set("ctype", "护甲");
                set("summon_wear_msg", NOR + MAG "刹那间，天地变色，雷声大作，紫气大盛，弥漫四周。\n"
                                       "转眼间，紫气渐渐化作一条蛟龙，与$N" NOR + MAG "合为一体。\n" NOR);
                set("summon_remove_msg", NOR + MAG "雷声渐息，紫气渐散，天地恢复了平静。\n" NOR);

                set("value", 3000000);
                set("armor_prop/armor", 200);
                set("armor_prop/dodge", 30);
                set("armor_prop/parry", 50);
                set("armor_prop/reduce_poison", 30);
                set("armor_prop/avoid_poison", 15);
                set("avoid_msg", NOR + MAG "一道寒芒闪过，紫蛟鳞甲将毒质全部吸收。\n" NOR);
                set("reduce_msg", HIR "一道寒芒划过，紫蛟鳞甲吸收了部分毒质。" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}