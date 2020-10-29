// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m抱月[1;34m乌骓[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹马全身乌黑宛如锦缎，腹部有个白月牙，龙吟虎相。[2;37;0m
它是许褚的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xchu");
        set("owner_name", "许褚");
        set_temp("owner", "xchu");
        set_temp("owner_name", "许褚");
        ::setup();
}
