// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m樱花[1;35m胭脂驹[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "这匹马通体红如胭脂，背部点点白色宛如洒落樱花，神骏非凡。[2;37;0m
它是佟湘玉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tong");
        set("owner_name", "佟湘玉");
        set_temp("owner", "tong");
        set_temp("owner_name", "佟湘玉");
        ::setup();
}
