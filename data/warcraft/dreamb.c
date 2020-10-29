// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m移动睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "只要躺在它背上就可以美美睡上一觉。[2;37;0m
它是风字随从的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dreamb");
        set("owner_name", "风字随从");
        set_temp("owner", "dreamb");
        set_temp("owner_name", "风字随从");
        ::setup();
}
