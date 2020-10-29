// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m远古猛虎[2;37;0m[2;37;0m[2;37;0m", ({"lao"}));        
        set("gender", "男性");                
        set("long", "一只凶猛的大老虎，一看就知道是远古血脉。[2;37;0m
它是萧爻的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "linen");
        set("owner_name", "萧爻");
        set_temp("owner", "linen");
        set_temp("owner_name", "萧爻");
        ::setup();
}
