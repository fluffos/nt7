// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"t_beijing"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是饮风而醉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qianmg");
        set("owner_name", "饮风而醉");
        set_temp("owner", "qianmg");
        set_temp("owner_name", "饮风而醉");
        ::setup();
}
