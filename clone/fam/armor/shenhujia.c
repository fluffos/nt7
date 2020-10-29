#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name(HIW "神虎战甲" NOR, ({ "shenhu zhanjia", "shenhu", "zhanjia" }));
        set_weight(6000);
        if (clonep())set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("long", HIW "\n一张投射着奇异光芒的战甲，乃天地间的极品。\n" NOR
                            HIG "有效招架修正：+ 70        有效轻功修正：+ 10\n" NOR
                            HIG "抗毒效果修正：+ 20%       防御效果等级： 220\n" NOR
                            HIG "抗毒回避修正：+ 20%\n" NOR);
                set("value", 2000000);
                set("material", "tiger");

                set("material_name", "白虎骨、白虎筋、白虎皮、如意通天镢");
                set("can_summon", 1);
                set("summon_id", "shenhujia");
                set("ctype", "护甲");
                set("summon_wear_msg", HIW "刹那间，风声骤起，山洪咆哮，天际处一道白光\n"
                                       "划过，渐渐地与$N" HIW "合为一体。\n" NOR);
                set("summon_remove_msg", HIW "风雨渐息，一只白虎腾空而起，消失在天际。\n" NOR);
                set("armor_prop/armor", 350);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 70);
                set("armor_prop/reduce_poison", 20); // 提高30%抗毒效果
                set("armor_prop/avoid_poison", 20); // 提高20%回避效果

        }
        setup();
}

int query_autoload()
{
        return 1;
}